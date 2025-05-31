# 02 - Feature Collaboration

## 🎯 Obiettivo

Imparare a collaborare su feature complesse che richiedono contributi da più membri del team, gestendo dipendenze e coordinando sviluppo parallelo.

## 🛠️ Scenario: User Authentication System

Il team Budget Tracker deve implementare un sistema completo di autenticazione che coinvolge:
- **Backend**: API authentication endpoints
- **Frontend**: Login/signup interfaces
- **Mobile**: Native authentication flow
- **QA**: Security and usability testing

## 📋 Fase 1: Planning e Task Breakdown

### Analisi Requirements (Team Lead)

```bash
# Alex analizza i requirements e crea task breakdown
cd budget-tracker-app
git checkout develop
git checkout -b feature/auth-system

# Documentazione del piano di lavoro
mkdir -p docs/features/authentication
cat > docs/features/authentication/requirements.md << 'EOF'
# Authentication System Requirements

## 🎯 Business Goals
- Secure user registration and login
- Multi-device session management  
- Social media authentication (Google, Apple)
- Password reset and recovery
- User profile management

## 🏗️ Technical Architecture

### Backend Components (Alex)
- [ ] User model and database schema
- [ ] JWT token management system
- [ ] Password hashing and validation
- [ ] Email verification system
- [ ] OAuth 2.0 integration (Google, Apple)
- [ ] Session management API
- [ ] Security middleware

### Frontend Components (Sara)
- [ ] Login/Register forms with validation
- [ ] Password strength indicator
- [ ] Social login buttons
- [ ] Password reset flow
- [ ] User profile dashboard
- [ ] Session timeout handling
- [ ] Responsive design for all devices

### Mobile Components (Marco)
- [ ] Native authentication screens
- [ ] Biometric authentication (Face ID, Touch ID)
- [ ] Deep linking for email verification
- [ ] Secure token storage
- [ ] OAuth flow integration
- [ ] Background session refresh

### Testing & Security (Lisa)
- [ ] Unit tests for all auth functions
- [ ] Integration tests for auth flow
- [ ] Security vulnerability testing
- [ ] Performance testing under load
- [ ] Accessibility compliance testing
- [ ] Cross-platform compatibility tests

## 🔗 Dependencies
1. Backend API → Frontend/Mobile integration
2. OAuth setup → Social login implementation  
3. Security testing → All component validation
4. Email service → Verification system

## ⏱️ Timeline
- **Week 1**: Backend API + Database
- **Week 2**: Frontend forms + Mobile screens
- **Week 3**: OAuth integration + Testing
- **Week 4**: Security review + Production deploy

## 🎯 Success Criteria
- [ ] User can register with email verification
- [ ] Secure login with session management
- [ ] Social authentication working
- [ ] Mobile biometric authentication
- [ ] 100% critical path test coverage
- [ ] Security audit passed
EOF

# Issue tracking setup
cat > docs/features/authentication/tasks.md << 'EOF'
# Authentication Tasks

## 🔴 Critical Path (Must complete in order)

### Phase 1: Foundation
- **Task 1**: Database schema & User model (Alex) - 2 days
- **Task 2**: Basic JWT authentication (Alex) - 2 days
- **Task 3**: Registration/Login API endpoints (Alex) - 1 day

### Phase 2: Frontend Development  
- **Task 4**: Login form UI (Sara) - 1 day
- **Task 5**: Registration form with validation (Sara) - 2 days
- **Task 6**: API integration (Sara) - 1 day

### Phase 3: Mobile Development
- **Task 7**: Authentication screens (Marco) - 2 days
- **Task 8**: API integration mobile (Marco) - 1 day
- **Task 9**: Biometric integration (Marco) - 2 days

### Phase 4: Advanced Features
- **Task 10**: OAuth backend setup (Alex) - 2 days
- **Task 11**: Social login frontend (Sara) - 1 day
- **Task 12**: Social login mobile (Marco) - 1 day

### Phase 5: Testing & Security
- **Task 13**: Security testing (Lisa) - 2 days
- **Task 14**: Performance testing (Lisa) - 1 day
- **Task 15**: E2E user flows (Lisa) - 2 days

## 🟡 Parallel Work (Can work simultaneously)
- Email service setup (Alex)
- Password reset flow (Sara)
- Deep linking setup (Marco)
- Accessibility testing (Lisa)

## 🔵 Nice to Have (If time permits)
- Two-factor authentication
- Login activity logging
- Advanced password policies
- Account deactivation/deletion
EOF

git add docs/
git commit -m "docs(auth): create authentication system requirements and task breakdown

- Define comprehensive auth system requirements
- Break down tasks by team member and dependencies
- Establish timeline and success criteria
- Plan parallel work streams to optimize velocity

Includes backend API, frontend UI, mobile native, and security testing components"

echo "✅ Alex ha pianificato la feature authentication"
```

## 📋 Fase 2: Backend Foundation (Alex)

### Database Schema e API Base

```bash
# Alex sviluppa il backend authentication
git checkout -b feature/auth-backend

# Setup database schema
mkdir -p backend/src/{models,controllers,middleware,utils,config}

cat > backend/src/models/User.js << 'EOF'
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

class User {
  constructor(userData) {
    this.id = userData.id;
    this.email = userData.email;
    this.password = userData.password;
    this.firstName = userData.firstName;
    this.lastName = userData.lastName;
    this.isVerified = userData.isVerified || false;
    this.createdAt = userData.createdAt || new Date();
    this.lastLogin = userData.lastLogin;
    this.profilePicture = userData.profilePicture;
  }

  // Hash password before saving
  async hashPassword() {
    if (this.password) {
      this.password = await bcrypt.hash(this.password, 12);
    }
  }

  // Verify password
  async verifyPassword(plainPassword) {
    return bcrypt.compare(plainPassword, this.password);
  }

  // Generate JWT token
  generateAuthToken() {
    const payload = {
      id: this.id,
      email: this.email,
      isVerified: this.isVerified
    };
    
    return jwt.sign(payload, process.env.JWT_SECRET, {
      expiresIn: process.env.JWT_EXPIRES_IN || '24h'
    });
  }

  // Generate refresh token
  generateRefreshToken() {
    const payload = {
      id: this.id,
      type: 'refresh'
    };
    
    return jwt.sign(payload, process.env.JWT_REFRESH_SECRET, {
      expiresIn: '30d'
    });
  }

  // Generate email verification token
  generateVerificationToken() {
    const payload = {
      id: this.id,
      email: this.email,
      type: 'verification'
    };
    
    return jwt.sign(payload, process.env.JWT_SECRET, {
      expiresIn: '24h'
    });
  }

  // Sanitize user data for client
  toJSON() {
    return {
      id: this.id,
      email: this.email,
      firstName: this.firstName,
      lastName: this.lastName,
      isVerified: this.isVerified,
      profilePicture: this.profilePicture,
      createdAt: this.createdAt,
      lastLogin: this.lastLogin
    };
  }
}

module.exports = User;
EOF

# Authentication Controller
cat > backend/src/controllers/authController.js << 'EOF'
const User = require('../models/User');
const { sendVerificationEmail, sendPasswordResetEmail } = require('../utils/emailService');
const { validateRegistration, validateLogin } = require('../utils/validation');

class AuthController {
  
  // Register new user
  async register(req, res) {
    try {
      const { email, password, firstName, lastName } = req.body;
      
      // Validate input
      const validation = validateRegistration(req.body);
      if (!validation.isValid) {
        return res.status(400).json({
          success: false,
          message: 'Validation failed',
          errors: validation.errors
        });
      }

      // Check if user already exists
      const existingUser = await User.findByEmail(email);
      if (existingUser) {
        return res.status(409).json({
          success: false,
          message: 'User already exists with this email'
        });
      }

      // Create new user
      const userData = { email, password, firstName, lastName };
      const user = new User(userData);
      await user.hashPassword();
      
      // Save user to database
      const savedUser = await User.create(user);
      
      // Generate verification token and send email
      const verificationToken = savedUser.generateVerificationToken();
      await sendVerificationEmail(email, verificationToken);

      // Generate auth tokens
      const authToken = savedUser.generateAuthToken();
      const refreshToken = savedUser.generateRefreshToken();

      res.status(201).json({
        success: true,
        message: 'User registered successfully. Please check your email for verification.',
        data: {
          user: savedUser.toJSON(),
          tokens: {
            access: authToken,
            refresh: refreshToken
          }
        }
      });

    } catch (error) {
      console.error('Registration error:', error);
      res.status(500).json({
        success: false,
        message: 'Internal server error during registration'
      });
    }
  }

  // Login user
  async login(req, res) {
    try {
      const { email, password } = req.body;
      
      // Validate input
      const validation = validateLogin(req.body);
      if (!validation.isValid) {
        return res.status(400).json({
          success: false,
          message: 'Validation failed',
          errors: validation.errors
        });
      }

      // Find user by email
      const user = await User.findByEmail(email);
      if (!user) {
        return res.status(401).json({
          success: false,
          message: 'Invalid email or password'
        });
      }

      // Verify password
      const isPasswordValid = await user.verifyPassword(password);
      if (!isPasswordValid) {
        return res.status(401).json({
          success: false,
          message: 'Invalid email or password'
        });
      }

      // Update last login
      await User.updateLastLogin(user.id);

      // Generate tokens
      const authToken = user.generateAuthToken();
      const refreshToken = user.generateRefreshToken();

      res.json({
        success: true,
        message: 'Login successful',
        data: {
          user: user.toJSON(),
          tokens: {
            access: authToken,
            refresh: refreshToken
          }
        }
      });

    } catch (error) {
      console.error('Login error:', error);
      res.status(500).json({
        success: false,
        message: 'Internal server error during login'
      });
    }
  }

  // Verify email
  async verifyEmail(req, res) {
    try {
      const { token } = req.params;
      
      // Verify token
      const decoded = jwt.verify(token, process.env.JWT_SECRET);
      if (decoded.type !== 'verification') {
        return res.status(400).json({
          success: false,
          message: 'Invalid verification token'
        });
      }

      // Update user verification status
      await User.updateVerificationStatus(decoded.id, true);

      res.json({
        success: true,
        message: 'Email verified successfully'
      });

    } catch (error) {
      console.error('Email verification error:', error);
      res.status(400).json({
        success: false,
        message: 'Invalid or expired verification token'
      });
    }
  }

  // Refresh access token
  async refreshToken(req, res) {
    try {
      const { refreshToken } = req.body;
      
      if (!refreshToken) {
        return res.status(401).json({
          success: false,
          message: 'Refresh token required'
        });
      }

      // Verify refresh token
      const decoded = jwt.verify(refreshToken, process.env.JWT_REFRESH_SECRET);
      
      // Find user
      const user = await User.findById(decoded.id);
      if (!user) {
        return res.status(401).json({
          success: false,
          message: 'Invalid refresh token'
        });
      }

      // Generate new access token
      const newAuthToken = user.generateAuthToken();

      res.json({
        success: true,
        data: {
          accessToken: newAuthToken
        }
      });

    } catch (error) {
      console.error('Token refresh error:', error);
      res.status(401).json({
        success: false,
        message: 'Invalid or expired refresh token'
      });
    }
  }

  // Logout user
  async logout(req, res) {
    try {
      // In a real app, you'd blacklist the token or remove from database
      res.json({
        success: true,
        message: 'Logged out successfully'
      });
    } catch (error) {
      console.error('Logout error:', error);
      res.status(500).json({
        success: false,
        message: 'Error during logout'
      });
    }
  }
}

module.exports = new AuthController();
EOF

# Authentication middleware
cat > backend/src/middleware/auth.js << 'EOF'
const jwt = require('jsonwebtoken');
const User = require('../models/User');

// Verify JWT token middleware
const authenticateToken = async (req, res, next) => {
  try {
    const authHeader = req.headers.authorization;
    const token = authHeader && authHeader.split(' ')[1]; // Bearer TOKEN

    if (!token) {
      return res.status(401).json({
        success: false,
        message: 'Access token required'
      });
    }

    // Verify token
    const decoded = jwt.verify(token, process.env.JWT_SECRET);
    
    // Find user
    const user = await User.findById(decoded.id);
    if (!user) {
      return res.status(401).json({
        success: false,
        message: 'Invalid token - user not found'
      });
    }

    // Attach user to request
    req.user = user;
    next();

  } catch (error) {
    console.error('Auth middleware error:', error);
    
    if (error.name === 'TokenExpiredError') {
      return res.status(401).json({
        success: false,
        message: 'Token expired'
      });
    }
    
    return res.status(401).json({
      success: false,
      message: 'Invalid token'
    });
  }
};

// Check if user is verified
const requireVerified = (req, res, next) => {
  if (!req.user.isVerified) {
    return res.status(403).json({
      success: false,
      message: 'Email verification required'
    });
  }
  next();
};

// Rate limiting for auth endpoints
const authRateLimit = (req, res, next) => {
  // In a real app, implement proper rate limiting
  // This is a placeholder for demonstration
  next();
};

module.exports = {
  authenticateToken,
  requireVerified,
  authRateLimit
};
EOF

# Validation utilities
cat > backend/src/utils/validation.js << 'EOF'
const validator = require('validator');

const validateRegistration = (data) => {
  const errors = [];
  
  // Email validation
  if (!data.email) {
    errors.push('Email is required');
  } else if (!validator.isEmail(data.email)) {
    errors.push('Please provide a valid email');
  }
  
  // Password validation
  if (!data.password) {
    errors.push('Password is required');
  } else if (data.password.length < 8) {
    errors.push('Password must be at least 8 characters long');
  } else if (!validator.isStrongPassword(data.password, {
    minLength: 8,
    minLowercase: 1,
    minUppercase: 1,
    minNumbers: 1,
    minSymbols: 1
  })) {
    errors.push('Password must contain uppercase, lowercase, number and special character');
  }
  
  // Name validation
  if (!data.firstName || data.firstName.trim().length < 2) {
    errors.push('First name must be at least 2 characters');
  }
  
  if (!data.lastName || data.lastName.trim().length < 2) {
    errors.push('Last name must be at least 2 characters');
  }
  
  return {
    isValid: errors.length === 0,
    errors
  };
};

const validateLogin = (data) => {
  const errors = [];
  
  if (!data.email) {
    errors.push('Email is required');
  } else if (!validator.isEmail(data.email)) {
    errors.push('Please provide a valid email');
  }
  
  if (!data.password) {
    errors.push('Password is required');
  }
  
  return {
    isValid: errors.length === 0,
    errors
  };
};

module.exports = {
  validateRegistration,
  validateLogin
};
EOF

git add .
git commit -m "feat(backend): implement authentication system foundation

Backend Auth Components:
- User model with password hashing and JWT generation
- Auth controller with register/login/verify endpoints
- Security middleware for token validation and verification
- Input validation utilities with strong password requirements

Features:
✅ Secure password hashing with bcrypt
✅ JWT access and refresh token system
✅ Email verification workflow
✅ Comprehensive input validation
✅ Error handling and security best practices

Ready for frontend/mobile integration"

git push -u origin feature/auth-backend

echo "✅ Alex ha completato il backend authentication"
```

## 📋 Fase 3: Frontend Integration (Sara) - Parallel Work

### Login e Registration Forms

```bash
# Sara lavora in parallelo sul frontend
git checkout develop
git checkout -b feature/auth-frontend

# Authentication service per API calls
mkdir -p frontend/src/services
cat > frontend/src/services/authService.js << 'EOF'
const API_BASE_URL = process.env.REACT_APP_API_URL || 'http://localhost:3001/api';

class AuthService {
  constructor() {
    this.token = localStorage.getItem('accessToken');
    this.refreshToken = localStorage.getItem('refreshToken');
  }

  // Set authentication headers
  getAuthHeaders() {
    return {
      'Content-Type': 'application/json',
      ...(this.token && { 'Authorization': `Bearer ${this.token}` })
    };
  }

  // Register new user
  async register(userData) {
    try {
      const response = await fetch(`${API_BASE_URL}/auth/register`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(userData)
      });

      const data = await response.json();

      if (data.success) {
        // Store tokens
        this.setTokens(data.data.tokens);
        return { success: true, user: data.data.user };
      } else {
        return { success: false, message: data.message, errors: data.errors };
      }
    } catch (error) {
      console.error('Registration error:', error);
      return { success: false, message: 'Network error during registration' };
    }
  }

  // Login user
  async login(credentials) {
    try {
      const response = await fetch(`${API_BASE_URL}/auth/login`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify(credentials)
      });

      const data = await response.json();

      if (data.success) {
        this.setTokens(data.data.tokens);
        return { success: true, user: data.data.user };
      } else {
        return { success: false, message: data.message };
      }
    } catch (error) {
      console.error('Login error:', error);
      return { success: false, message: 'Network error during login' };
    }
  }

  // Logout user
  async logout() {
    try {
      await fetch(`${API_BASE_URL}/auth/logout`, {
        method: 'POST',
        headers: this.getAuthHeaders()
      });
    } catch (error) {
      console.error('Logout error:', error);
    } finally {
      this.clearTokens();
    }
  }

  // Refresh access token
  async refreshAccessToken() {
    try {
      const response = await fetch(`${API_BASE_URL}/auth/refresh`, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({ refreshToken: this.refreshToken })
      });

      const data = await response.json();

      if (data.success) {
        this.token = data.data.accessToken;
        localStorage.setItem('accessToken', this.token);
        return true;
      } else {
        this.clearTokens();
        return false;
      }
    } catch (error) {
      console.error('Token refresh error:', error);
      this.clearTokens();
      return false;
    }
  }

  // Store tokens
  setTokens(tokens) {
    this.token = tokens.access;
    this.refreshToken = tokens.refresh;
    localStorage.setItem('accessToken', tokens.access);
    localStorage.setItem('refreshToken', tokens.refresh);
  }

  // Clear tokens
  clearTokens() {
    this.token = null;
    this.refreshToken = null;
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
  }

  // Check if user is authenticated
  isAuthenticated() {
    return !!this.token;
  }

  // Get current user from token
  getCurrentUser() {
    if (!this.token) return null;
    
    try {
      const payload = JSON.parse(atob(this.token.split('.')[1]));
      return payload;
    } catch (error) {
      console.error('Error parsing token:', error);
      return null;
    }
  }
}

export default new AuthService();
EOF

# Login Component
cat > frontend/src/components/LoginForm.js << 'EOF'
import React, { useState } from 'react';
import authService from '../services/authService';
import './AuthForms.css';

const LoginForm = ({ onSuccess, onSwitchToRegister }) => {
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  const [errors, setErrors] = useState({});
  const [isLoading, setIsLoading] = useState(false);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
    
    // Clear error when user starts typing
    if (errors[name]) {
      setErrors(prev => ({
        ...prev,
        [name]: ''
      }));
    }
  };

  const validateForm = () => {
    const newErrors = {};
    
    if (!formData.email) {
      newErrors.email = 'Email is required';
    } else if (!/\S+@\S+\.\S+/.test(formData.email)) {
      newErrors.email = 'Please enter a valid email';
    }
    
    if (!formData.password) {
      newErrors.password = 'Password is required';
    }
    
    setErrors(newErrors);
    return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    if (!validateForm()) return;
    
    setIsLoading(true);
    
    try {
      const result = await authService.login(formData);
      
      if (result.success) {
        onSuccess(result.user);
      } else {
        setErrors({ general: result.message });
      }
    } catch (error) {
      setErrors({ general: 'An unexpected error occurred' });
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className="auth-form">
      <div className="auth-header">
        <h2>Welcome Back!</h2>
        <p>Sign in to your account</p>
      </div>
      
      <form onSubmit={handleSubmit} className="form">
        {errors.general && (
          <div className="error-banner">
            {errors.general}
          </div>
        )}
        
        <div className="form-group">
          <label htmlFor="email">Email Address</label>
          <input
            type="email"
            id="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
            placeholder="Enter your email"
            className={errors.email ? 'error' : ''}
            disabled={isLoading}
          />
          {errors.email && <span className="error-text">{errors.email}</span>}
        </div>
        
        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            id="password"
            name="password"
            value={formData.password}
            onChange={handleChange}
            placeholder="Enter your password"
            className={errors.password ? 'error' : ''}
            disabled={isLoading}
          />
          {errors.password && <span className="error-text">{errors.password}</span>}
        </div>
        
        <button 
          type="submit" 
          className="btn-primary"
          disabled={isLoading}
        >
          {isLoading ? 'Signing In...' : 'Sign In'}
        </button>
        
        <div className="form-footer">
          <a href="#forgot-password" className="link">Forgot your password?</a>
          <p>
            Don't have an account?{' '}
            <button 
              type="button" 
              className="link-button"
              onClick={onSwitchToRegister}
            >
              Sign up here
            </button>
          </p>
        </div>
      </form>
    </div>
  );
};

export default LoginForm;
EOF

# Registration Component
cat > frontend/src/components/RegisterForm.js << 'EOF'
import React, { useState } from 'react';
import authService from '../services/authService';
import PasswordStrengthIndicator from './PasswordStrengthIndicator';
import './AuthForms.css';

const RegisterForm = ({ onSuccess, onSwitchToLogin }) => {
  const [formData, setFormData] = useState({
    firstName: '',
    lastName: '',
    email: '',
    password: '',
    confirmPassword: ''
  });
  const [errors, setErrors] = useState({});
  const [isLoading, setIsLoading] = useState(false);

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
    
    // Clear error when user starts typing
    if (errors[name]) {
      setErrors(prev => ({
        ...prev,
        [name]: ''
      }));
    }
  };

  const validateForm = () => {
    const newErrors = {};
    
    if (!formData.firstName.trim()) {
      newErrors.firstName = 'First name is required';
    } else if (formData.firstName.trim().length < 2) {
      newErrors.firstName = 'First name must be at least 2 characters';
    }
    
    if (!formData.lastName.trim()) {
      newErrors.lastName = 'Last name is required';
    } else if (formData.lastName.trim().length < 2) {
      newErrors.lastName = 'Last name must be at least 2 characters';
    }
    
    if (!formData.email) {
      newErrors.email = 'Email is required';
    } else if (!/\S+@\S+\.\S+/.test(formData.email)) {
      newErrors.email = 'Please enter a valid email';
    }
    
    if (!formData.password) {
      newErrors.password = 'Password is required';
    } else if (formData.password.length < 8) {
      newErrors.password = 'Password must be at least 8 characters';
    }
    
    if (formData.password !== formData.confirmPassword) {
      newErrors.confirmPassword = 'Passwords do not match';
    }
    
    setErrors(newErrors);
    return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    if (!validateForm()) return;
    
    setIsLoading(true);
    
    try {
      const result = await authService.register({
        firstName: formData.firstName.trim(),
        lastName: formData.lastName.trim(),
        email: formData.email,
        password: formData.password
      });
      
      if (result.success) {
        onSuccess(result.user);
      } else {
        if (result.errors) {
          const errorObj = {};
          result.errors.forEach(error => {
            errorObj.general = error;
          });
          setErrors(errorObj);
        } else {
          setErrors({ general: result.message });
        }
      }
    } catch (error) {
      setErrors({ general: 'An unexpected error occurred' });
    } finally {
      setIsLoading(false);
    }
  };

  return (
    <div className="auth-form">
      <div className="auth-header">
        <h2>Create Account</h2>
        <p>Join Budget Tracker today</p>
      </div>
      
      <form onSubmit={handleSubmit} className="form">
        {errors.general && (
          <div className="error-banner">
            {errors.general}
          </div>
        )}
        
        <div className="form-row">
          <div className="form-group">
            <label htmlFor="firstName">First Name</label>
            <input
              type="text"
              id="firstName"
              name="firstName"
              value={formData.firstName}
              onChange={handleChange}
              placeholder="First name"
              className={errors.firstName ? 'error' : ''}
              disabled={isLoading}
            />
            {errors.firstName && <span className="error-text">{errors.firstName}</span>}
          </div>
          
          <div className="form-group">
            <label htmlFor="lastName">Last Name</label>
            <input
              type="text"
              id="lastName"
              name="lastName"
              value={formData.lastName}
              onChange={handleChange}
              placeholder="Last name"
              className={errors.lastName ? 'error' : ''}
              disabled={isLoading}
            />
            {errors.lastName && <span className="error-text">{errors.lastName}</span>}
          </div>
        </div>
        
        <div className="form-group">
          <label htmlFor="email">Email Address</label>
          <input
            type="email"
            id="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
            placeholder="Enter your email"
            className={errors.email ? 'error' : ''}
            disabled={isLoading}
          />
          {errors.email && <span className="error-text">{errors.email}</span>}
        </div>
        
        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            id="password"
            name="password"
            value={formData.password}
            onChange={handleChange}
            placeholder="Create a strong password"
            className={errors.password ? 'error' : ''}
            disabled={isLoading}
          />
          {formData.password && (
            <PasswordStrengthIndicator password={formData.password} />
          )}
          {errors.password && <span className="error-text">{errors.password}</span>}
        </div>
        
        <div className="form-group">
          <label htmlFor="confirmPassword">Confirm Password</label>
          <input
            type="password"
            id="confirmPassword"
            name="confirmPassword"
            value={formData.confirmPassword}
            onChange={handleChange}
            placeholder="Confirm your password"
            className={errors.confirmPassword ? 'error' : ''}
            disabled={isLoading}
          />
          {errors.confirmPassword && <span className="error-text">{errors.confirmPassword}</span>}
        </div>
        
        <button 
          type="submit" 
          className="btn-primary"
          disabled={isLoading}
        >
          {isLoading ? 'Creating Account...' : 'Create Account'}
        </button>
        
        <div className="form-footer">
          <p>
            Already have an account?{' '}
            <button 
              type="button" 
              className="link-button"
              onClick={onSwitchToLogin}
            >
              Sign in here
            </button>
          </p>
        </div>
      </form>
    </div>
  );
};

export default RegisterForm;
EOF

# Password Strength Indicator
cat > frontend/src/components/PasswordStrengthIndicator.js << 'EOF'
import React from 'react';

const PasswordStrengthIndicator = ({ password }) => {
  const calculateStrength = (password) => {
    let score = 0;
    const checks = {
      length: password.length >= 8,
      lowercase: /[a-z]/.test(password),
      uppercase: /[A-Z]/.test(password),
      numbers: /\d/.test(password),
      symbols: /[!@#$%^&*(),.?":{}|<>]/.test(password)
    };
    
    score = Object.values(checks).filter(Boolean).length;
    
    return { score, checks };
  };

  const { score, checks } = calculateStrength(password);
  
  const getStrengthText = (score) => {
    if (score < 2) return 'Very Weak';
    if (score < 3) return 'Weak';
    if (score < 4) return 'Fair';
    if (score < 5) return 'Strong';
    return 'Very Strong';
  };

  const getStrengthColor = (score) => {
    if (score < 2) return '#e74c3c';
    if (score < 3) return '#f39c12';
    if (score < 4) return '#f1c40f';
    if (score < 5) return '#27ae60';
    return '#2ecc71';
  };

  return (
    <div className="password-strength">
      <div className="strength-bar">
        <div 
          className="strength-fill"
          style={{
            width: `${(score / 5) * 100}%`,
            backgroundColor: getStrengthColor(score)
          }}
        />
      </div>
      <div className="strength-info">
        <span 
          className="strength-text"
          style={{ color: getStrengthColor(score) }}
        >
          {getStrengthText(score)}
        </span>
        <div className="requirements">
          <small className={checks.length ? 'met' : 'unmet'}>
            8+ characters
          </small>
          <small className={checks.lowercase ? 'met' : 'unmet'}>
            lowercase
          </small>
          <small className={checks.uppercase ? 'met' : 'unmet'}>
            uppercase
          </small>
          <small className={checks.numbers ? 'met' : 'unmet'}>
            number
          </small>
          <small className={checks.symbols ? 'met' : 'unmet'}>
            symbol
          </small>
        </div>
      </div>
    </div>
  );
};

export default PasswordStrengthIndicator;
EOF

# CSS Styles
cat > frontend/src/components/AuthForms.css << 'EOF'
.auth-form {
  max-width: 400px;
  margin: 2rem auto;
  padding: 2rem;
  background: #ffffff;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
}

.auth-header {
  text-align: center;
  margin-bottom: 2rem;
}

.auth-header h2 {
  color: #2c3e50;
  margin-bottom: 0.5rem;
}

.auth-header p {
  color: #7f8c8d;
  margin: 0;
}

.form {
  display: flex;
  flex-direction: column;
  gap: 1rem;
}

.form-row {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1rem;
}

.form-group {
  display: flex;
  flex-direction: column;
}

.form-group label {
  margin-bottom: 0.5rem;
  color: #2c3e50;
  font-weight: 500;
}

.form-group input {
  padding: 0.75rem;
  border: 1px solid #bdc3c7;
  border-radius: 4px;
  font-size: 1rem;
  transition: border-color 0.3s ease;
}

.form-group input:focus {
  outline: none;
  border-color: #3498db;
  box-shadow: 0 0 0 2px rgba(52, 152, 219, 0.2);
}

.form-group input.error {
  border-color: #e74c3c;
}

.error-text {
  color: #e74c3c;
  font-size: 0.875rem;
  margin-top: 0.25rem;
}

.error-banner {
  background: #fdf2f2;
  border: 1px solid #e74c3c;
  color: #e74c3c;
  padding: 0.75rem;
  border-radius: 4px;
  margin-bottom: 1rem;
}

.btn-primary {
  background: #3498db;
  color: white;
  border: none;
  padding: 0.75rem;
  border-radius: 4px;
  font-size: 1rem;
  cursor: pointer;
  transition: background-color 0.3s ease;
}

.btn-primary:hover:not(:disabled) {
  background: #2980b9;
}

.btn-primary:disabled {
  background: #bdc3c7;
  cursor: not-allowed;
}

.form-footer {
  text-align: center;
  margin-top: 1rem;
}

.link {
  color: #3498db;
  text-decoration: none;
}

.link:hover {
  text-decoration: underline;
}

.link-button {
  background: none;
  border: none;
  color: #3498db;
  cursor: pointer;
  text-decoration: underline;
  font: inherit;
}

.link-button:hover {
  color: #2980b9;
}

/* Password Strength Indicator */
.password-strength {
  margin-top: 0.5rem;
}

.strength-bar {
  height: 4px;
  background: #ecf0f1;
  border-radius: 2px;
  overflow: hidden;
  margin-bottom: 0.5rem;
}

.strength-fill {
  height: 100%;
  transition: all 0.3s ease;
}

.strength-info {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.strength-text {
  font-size: 0.875rem;
  font-weight: 500;
}

.requirements {
  display: flex;
  gap: 0.5rem;
}

.requirements small {
  font-size: 0.75rem;
}

.requirements .met {
  color: #27ae60;
}

.requirements .unmet {
  color: #95a5a6;
}

/* Responsive */
@media (max-width: 480px) {
  .auth-form {
    margin: 1rem;
    padding: 1.5rem;
  }
  
  .form-row {
    grid-template-columns: 1fr;
  }
}
EOF

git add .
git commit -m "feat(frontend): implement authentication UI components

Frontend Auth Components:
- AuthService for API communication and token management
- LoginForm with validation and error handling
- RegisterForm with password strength indicator
- Responsive CSS styling with accessibility considerations

Features:
✅ Real-time form validation
✅ Password strength visualization
✅ Automatic token management and refresh
✅ Loading states and error handling
✅ Mobile-responsive design
✅ Accessibility compliance

Ready for backend integration and testing"

git push -u origin feature/auth-frontend

echo "✅ Sara ha completato l'interfaccia di autenticazione"
```

## 📋 Fase 4: Integrazione e Testing Coordinato

### Alex coordina l'integrazione

```bash
# Alex torna per integrare le modifiche del team
cd budget-tracker-app
git checkout develop

# Prima controlla il progresso del team
echo "📊 Checking team progress..."
git log --oneline --graph --all -10

# Merge delle feature completate
echo "🔄 Integrating backend authentication..."
git merge --no-ff feature/auth-backend -m "Merge feature/auth-backend into develop

✅ Backend authentication system integrated
- JWT-based authentication with refresh tokens
- Secure password hashing and validation
- Email verification system
- Comprehensive security middleware

Backend API endpoints ready for frontend integration
Reviewed-by: Alex <alex@budgetapp.com>"

echo "🔄 Integrating frontend authentication..."  
git merge --no-ff feature/auth-frontend -m "Merge feature/auth-frontend into develop

✅ Frontend authentication UI integrated
- Login and registration forms with validation
- Password strength indicator and UX improvements
- Token management and API service layer
- Responsive design with accessibility features

Frontend ready for end-to-end user testing
Reviewed-by: Alex <alex@budgetapp.com>"

# Update della documentazione con progress
cat >> docs/features/authentication/progress.md << 'EOF'
# Authentication System - Implementation Progress

## ✅ Completed Components

### Backend (Alex) - 100% Complete
- [x] User model with secure password hashing
- [x] JWT token generation and validation
- [x] Authentication middleware and security
- [x] Registration and login API endpoints
- [x] Email verification system
- [x] Input validation and error handling

### Frontend (Sara) - 100% Complete  
- [x] Authentication service with API integration
- [x] Login form with validation
- [x] Registration form with password strength
- [x] Token management and auto-refresh
- [x] Responsive CSS and accessibility
- [x] Error handling and loading states

### Integration Status
- [x] Backend API endpoints functional
- [x] Frontend consuming backend APIs
- [x] Token-based authentication flow working
- [x] Error handling end-to-end
- [x] Responsive design implemented

## 🔄 Next Steps (Pending Marco and Lisa)

### Mobile (Marco) - In Progress
- [ ] Native authentication screens
- [ ] API integration with existing backend
- [ ] Biometric authentication (Face ID/Touch ID)
- [ ] Secure token storage
- [ ] Deep linking for email verification

### Testing (Lisa) - Ready to Start
- [ ] Unit tests for auth components
- [ ] Integration tests for auth flow
- [ ] Security testing and vulnerability scanning
- [ ] Performance testing under load
- [ ] Accessibility compliance verification

## 🎯 Success Metrics

### Technical Metrics
- **API Response Time**: <200ms average
- **Password Hash Time**: <100ms
- **Token Validation**: <50ms
- **Form Validation**: Real-time (<100ms)

### User Experience
- **Registration Flow**: <2 minutes
- **Login Time**: <10 seconds
- **Password Recovery**: <5 minutes
- **Mobile Responsiveness**: 100% viewports

### Security Standards
- **Password Strength**: Enforced strong passwords
- **Token Security**: 24h access, 30d refresh
- **Input Validation**: Server-side validation
- **XSS Protection**: Sanitized inputs
EOF

git add docs/
git commit -m "docs: update authentication implementation progress

- Document completed backend and frontend components
- Track integration status and success metrics
- Plan remaining mobile and testing work
- Set performance and security benchmarks

Team velocity: 2/4 major components completed
Ready for Marco (mobile) and Lisa (testing) contributions"

echo "🎉 Authentication system core implementation complete!"
echo "📱 Waiting for Marco (mobile) and Lisa (testing)..."
```

## 🎯 Risultati della Collaborazione

### ✅ Coordinamento Efficace
- **Dipendenze gestite**: Backend completato prima dell'integrazione frontend
- **Lavoro parallelo**: Sara ha lavorato su frontend mentre Alex faceva backend
- **Standards condivisi**: Codice consistente tra team members
- **Documentation**: Progresso tracciato e comunicato

### ✅ Qualità Tecnica
- **API Design**: RESTful endpoints ben documentati
- **Security**: Password hashing, JWT tokens, input validation
- **UX**: Forms responsive con feedback in tempo reale
- **Error Handling**: Gestione errori end-to-end

### ✅ Team Efficiency
- **Task Breakdown**: Lavoro diviso per expertise
- **Timeline Rispettato**: Milestone raggiunti on-time
- **Code Review**: Merge con review del team lead
- **Knowledge Sharing**: Documentation per onboarding

## 💡 Pattern di Collaborazione

### Communication
- **Commit Messages**: Dettagliati con scope e impact
- **Branch Naming**: Convenzioni chiare (feature/auth-backend)
- **Documentation**: Progress tracking condiviso

### Workflow
- **Feature Branches**: Isolamento del lavoro individuale
- **Review Process**: Merge attraverso team lead
- **Integration Testing**: Verifica compatibilità tra componenti

### Quality Assurance
- **Standards Enforcement**: Linting e validation automatica
- **Security Focus**: Best practices implement da inizio
- **Performance**: Metriche definite e monitorate

## 🔗 Prossimi Passi

1. **[Issue Management →](03-issue-management.md)** - Gestire bug e feature requests
2. **[Mobile Integration →](../guide/03-mobile-collaboration.md)** - Coordinare sviluppo mobile
3. **[Security Testing →](../guide/04-security-collaboration.md)** - Validazione sicurezza

---

[← Esempio Precedente](01-team-setup.md) | [Torna agli Esempi](README.md) | [Esempio Successivo →](03-issue-management.md)
