# Esercizio 1: Implementazione Completa Git Flow

## Obiettivo
Implementare un workflow Git Flow completo per gestire lo sviluppo di un'applicazione e-commerce, dalla pianificazione delle feature fino alla gestione dei hotfix in produzione.

## Scenario del Progetto
Il team sviluppa "ShopFlow", un'applicazione e-commerce con le seguenti caratteristiche:
- **Frontend**: React application
- **Backend**: Node.js API
- **Database**: MongoDB
- **Team**: 4 developers + 1 PM
- **Release cycle**: Ogni 2 settimane
- **Supporto**: Multiple versioni in produzione

## Fase 1: Setup Git Flow Environment

### 1.1 Installazione Git Flow Tools
```bash
# Per macOS
brew install git-flow-avh

# Per Ubuntu/Debian
sudo apt-get install git-flow

# Per Windows
# Scarica Git Flow AVH edition da GitHub

# Verifica installazione
git flow version
```

### 1.2 Creazione Repository e Inizializzazione
```bash
# Crea repository ShopFlow
git init shopflow-project
cd shopflow-project

# Setup struttura iniziale
mkdir -p src/{frontend,backend,shared} docs tests scripts
touch README.md .gitignore package.json

# Commit iniziale
git add .
git commit -m "Initial project structure

- Setup frontend, backend, and shared directories
- Add project documentation structure
- Initialize package.json for dependencies
- Add comprehensive .gitignore"

# Inizializza Git Flow
git flow init

# Configurazione branches (default values):
# Production branch: main
# Development branch: develop  
# Feature prefix: feature/
# Release prefix: release/
# Hotfix prefix: hotfix/
# Support prefix: support/
```

### 1.3 Setup Initial Project Structure

**package.json**:
```json
{
  "name": "shopflow-ecommerce",
  "version": "0.0.0",
  "description": "Modern e-commerce platform with React frontend and Node.js backend",
  "main": "src/backend/server.js",
  "scripts": {
    "dev:frontend": "cd src/frontend && npm start",
    "dev:backend": "cd src/backend && npm run dev", 
    "dev": "concurrently \"npm run dev:frontend\" \"npm run dev:backend\"",
    "build": "npm run build:frontend && npm run build:backend",
    "build:frontend": "cd src/frontend && npm run build",
    "build:backend": "cd src/backend && npm run build",
    "test": "npm run test:frontend && npm run test:backend",
    "test:frontend": "cd src/frontend && npm test",
    "test:backend": "cd src/backend && npm test",
    "lint": "eslint src/",
    "start": "cd src/backend && npm start"
  },
  "repository": {
    "type": "git",
    "url": "git+https://github.com/[team]/shopflow-project.git"
  },
  "keywords": ["ecommerce", "react", "nodejs", "mongodb"],
  "author": "ShopFlow Team",
  "license": "MIT",
  "devDependencies": {
    "concurrently": "^7.6.0",
    "eslint": "^8.0.0"
  }
}
```

**README.md**:
```markdown
# ShopFlow E-commerce Platform

Modern, scalable e-commerce platform built with React and Node.js.

## Features Roadmap

### v1.0.0 - MVP (Target: Week 2)
- [ ] User authentication and registration
- [ ] Product catalog with search
- [ ] Shopping cart functionality
- [ ] Basic checkout process
- [ ] Admin panel for product management

### v1.1.0 - Enhanced UX (Target: Week 4)  
- [ ] Product reviews and ratings
- [ ] Wishlist functionality
- [ ] Advanced search filters
- [ ] Email notifications
- [ ] Mobile responsive design

### v1.2.0 - Advanced Features (Target: Week 6)
- [ ] Payment gateway integration
- [ ] Inventory management
- [ ] Analytics dashboard
- [ ] Multi-language support
- [ ] SEO optimization

## Git Flow Workflow

This project follows Git Flow methodology:

- **main**: Production-ready code
- **develop**: Development integration branch
- **feature/***: New features under development
- **release/***: Release preparation branches
- **hotfix/***: Emergency fixes for production

## Quick Start

```bash
# Clone repository
git clone [repo-url]
cd shopflow-project

# Install dependencies
npm install

# Start development
npm run dev
```

## Team

- **Alice Chen** - Frontend Lead (alice@shopflow.com)
- **Bob Rivera** - Backend Lead (bob@shopflow.com)  
- **Carol Kim** - Full Stack Developer (carol@shopflow.com)
- **David Park** - DevOps Engineer (david@shopflow.com)
- **Emma Wilson** - Project Manager (emma@shopflow.com)
```

```bash
# Push initial setup
git remote add origin https://github.com/[team]/shopflow-project.git
git push -u origin main
git push -u origin develop
```

## Fase 2: Feature Development Workflow

### 2.1 Sviluppo Feature 1: User Authentication

**Alice** (Frontend Lead) inizia sviluppo autenticazione:

```bash
# Inizia nuova feature
git flow feature start user-authentication

# Verifica branch corrente
git branch
# * feature/user-authentication
# develop
# main

# Setup frontend structure
mkdir -p src/frontend/src/{components,pages,services,hooks,utils}
mkdir -p src/frontend/src/components/{Auth,Common,Layout}
```

**Frontend Components** (Alice):

**src/frontend/src/components/Auth/LoginForm.jsx**:
```jsx
import React, { useState } from 'react';
import { useAuth } from '../../hooks/useAuth';
import './AuthForms.css';

const LoginForm = ({ onSwitchToRegister }) => {
  const [formData, setFormData] = useState({
    email: '',
    password: ''
  });
  const [errors, setErrors] = useState({});
  const { login, loading } = useAuth();

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
      newErrors.email = 'Email is invalid';
    }
    
    if (!formData.password) {
      newErrors.password = 'Password is required';
    } else if (formData.password.length < 6) {
      newErrors.password = 'Password must be at least 6 characters';
    }
    
    setErrors(newErrors);
    return Object.keys(newErrors).length === 0;
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    
    if (!validateForm()) return;
    
    try {
      await login(formData.email, formData.password);
    } catch (error) {
      setErrors({ submit: error.message });
    }
  };

  return (
    <div className="auth-form">
      <h2>Login to ShopFlow</h2>
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="email">Email</label>
          <input
            type="email"
            id="email"
            name="email"
            value={formData.email}
            onChange={handleChange}
            className={errors.email ? 'error' : ''}
            disabled={loading}
          />
          {errors.email && <span className="error-message">{errors.email}</span>}
        </div>

        <div className="form-group">
          <label htmlFor="password">Password</label>
          <input
            type="password"
            id="password"
            name="password"
            value={formData.password}
            onChange={handleChange}
            className={errors.password ? 'error' : ''}
            disabled={loading}
          />
          {errors.password && <span className="error-message">{errors.password}</span>}
        </div>

        {errors.submit && (
          <div className="error-message submit-error">
            {errors.submit}
          </div>
        )}

        <button 
          type="submit" 
          className="btn-primary"
          disabled={loading}
        >
          {loading ? 'Logging in...' : 'Login'}
        </button>
      </form>

      <div className="auth-switch">
        <p>
          Don't have an account?{' '}
          <button 
            type="button" 
            className="link-button"
            onClick={onSwitchToRegister}
          >
            Register here
          </button>
        </p>
      </div>
    </div>
  );
};

export default LoginForm;
```

**Bob** (Backend Lead) sviluppa API parallelo:

```bash
# Bob lavora sulla stessa feature ma file diversi
git flow feature start user-authentication
# Se feature già esiste: git checkout feature/user-authentication

# Setup backend structure  
mkdir -p src/backend/src/{controllers,models,middleware,routes,services,utils}
```

**src/backend/src/models/User.js**:
```javascript
const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');

const userSchema = new mongoose.Schema({
  firstName: {
    type: String,
    required: [true, 'First name is required'],
    trim: true,
    maxlength: [50, 'First name cannot exceed 50 characters']
  },
  lastName: {
    type: String,
    required: [true, 'Last name is required'],
    trim: true,
    maxlength: [50, 'Last name cannot exceed 50 characters']
  },
  email: {
    type: String,
    required: [true, 'Email is required'],
    unique: true,
    lowercase: true,
    match: [/^\S+@\S+\.\S+$/, 'Please enter a valid email']
  },
  password: {
    type: String,
    required: [true, 'Password is required'],
    minlength: [6, 'Password must be at least 6 characters'],
    select: false // Don't include password in queries by default
  },
  role: {
    type: String,
    enum: ['customer', 'admin'],
    default: 'customer'
  },
  isActive: {
    type: Boolean,
    default: true
  },
  lastLogin: {
    type: Date
  },
  resetPasswordToken: String,
  resetPasswordExpire: Date,
  emailVerified: {
    type: Boolean,
    default: false
  },
  emailVerificationToken: String
}, {
  timestamps: true,
  toJSON: { virtuals: true },
  toObject: { virtuals: true }
});

// Virtual for full name
userSchema.virtual('fullName').get(function() {
  return `${this.firstName} ${this.lastName}`;
});

// Index for performance
userSchema.index({ email: 1 });
userSchema.index({ createdAt: -1 });

// Hash password before saving
userSchema.pre('save', async function(next) {
  // Only hash password if it's modified
  if (!this.isModified('password')) return next();
  
  try {
    // Hash password with cost of 12
    const salt = await bcrypt.genSalt(12);
    this.password = await bcrypt.hash(this.password, salt);
    next();
  } catch (error) {
    next(error);
  }
});

// Compare password method
userSchema.methods.comparePassword = async function(candidatePassword) {
  return await bcrypt.compare(candidatePassword, this.password);
};

// Generate JWT token
userSchema.methods.generateAuthToken = function() {
  return jwt.sign(
    { 
      id: this._id,
      email: this.email,
      role: this.role 
    },
    process.env.JWT_SECRET,
    { 
      expiresIn: process.env.JWT_EXPIRE || '7d' 
    }
  );
};

// Generate password reset token
userSchema.methods.generateResetToken = function() {
  const crypto = require('crypto');
  const resetToken = crypto.randomBytes(20).toString('hex');
  
  // Hash token and save to database
  this.resetPasswordToken = crypto
    .createHash('sha256')
    .update(resetToken)
    .digest('hex');
    
  // Set expire time (10 minutes)
  this.resetPasswordExpire = Date.now() + 10 * 60 * 1000;
  
  return resetToken;
};

module.exports = mongoose.model('User', userSchema);
```

### 2.2 Collaboration sul Feature Branch

**Coordinamento tramite commit:**

```bash
# Alice commit frontend changes
git add src/frontend/
git commit -m "feat(auth): implement login and register forms

- Add LoginForm component with validation
- Add RegisterForm component
- Implement useAuth hook for state management
- Add AuthForms.css for styling
- Add form validation with error handling

BREAKING CHANGE: None
Closes: #12"

# Bob commit backend changes
git add src/backend/
git commit -m "feat(auth): implement user authentication API

- Add User model with bcrypt password hashing
- Implement JWT token generation and validation
- Add authentication middleware
- Create auth controller with register/login endpoints
- Add password reset functionality

BREAKING CHANGE: None
Closes: #13"

# Entrambi push al feature branch
git push origin feature/user-authentication
```

### 2.3 Finalizzazione Feature

```bash
# Test integration locale
npm install
npm run test

# Carol (Full Stack) aggiunge integration tests
git checkout feature/user-authentication

# Carol aggiunge test e2e
mkdir -p tests/e2e
# Aggiunge test di integrazione frontend-backend...

git add tests/
git commit -m "test(auth): add integration tests for authentication flow

- Add end-to-end tests for login/register
- Add API integration tests  
- Add frontend component tests
- Setup test database configuration

Closes: #14"

# Finalizza feature quando tutto è pronto
git flow feature finish user-authentication

# Questo merge la feature in develop automaticamente
```

## Fase 3: Release Preparation

### 3.1 Preparazione Release v1.0.0

Dopo completamento di multiple features:

```bash
# Verifica che develop sia stabile
git checkout develop
git pull origin develop

# Esegui test completi
npm run test
npm run lint
npm run build

# Inizia release branch
git flow release start v1.0.0

# Verifica branch corrente  
git branch
# develop
# main
# * release/v1.0.0
```

### 3.2 Release Hardening

**Attività su release branch:**

**Update versioni:**
```bash
# Aggiorna package.json
npm version 1.0.0 --no-git-tag-version

# Aggiorna version in altre parti del codice
echo "v1.0.0" > VERSION
```

**Update documentation:**
```markdown
# CHANGELOG.md
## [1.0.0] - 2024-01-15

### Added
- User authentication and registration system
- Product catalog with search functionality
- Shopping cart with persistent storage
- Basic checkout process
- Admin panel for product management
- Responsive mobile design
- Email notification system

### Changed
- Improved search performance with indexing
- Enhanced form validation across all components
- Updated UI theme for better accessibility

### Fixed
- Cart persistence issue on page refresh
- Search pagination bug
- Mobile layout overflow issues

### Security
- Implemented JWT token authentication
- Added password hashing with bcrypt
- Added rate limiting for authentication endpoints
```

**Final testing e bugfix:**
```bash
# Emma (PM) coordina final testing
# Fix eventuali bug trovati durante release testing

git add .
git commit -m "release(v1.0.0): prepare release v1.0.0

- Update version numbers across project
- Add comprehensive CHANGELOG
- Fix minor bugs found during release testing
- Update documentation for v1.0.0 features
- Prepare deployment configurations"
```

### 3.3 Release Deployment

```bash
# Finalizza release
git flow release finish v1.0.0

# Questo automaticamente:
# 1. Merge release/v1.0.0 in main
# 2. Tag v1.0.0 su main  
# 3. Merge release/v1.0.0 in develop
# 4. Cancella release/v1.0.0 branch

# Push tutti i branch e tag
git push origin main
git push origin develop  
git push origin --tags

# Deploy in produzione da main branch
# (questo dipende dalla pipeline CI/CD)
```

## Fase 4: Hotfix Management

### 4.1 Scenario: Critical Bug in Production

**Situazione**: Dopo il deploy di v1.0.0, si scopre un bug critico nella validazione del checkout che permette ordini con prezzo $0.

```bash
# David (DevOps) identifica il problema
# Bug report: Checkout validation bypass allows $0 orders

# Inizia hotfix da main branch
git checkout main
git pull origin main
git flow hotfix start checkout-validation-fix

# Verifica branch corrente
git branch
# develop
# main
# * hotfix/checkout-validation-fix
```

### 4.2 Fix Urgente

**src/backend/src/controllers/orderController.js**:
```javascript
// Fix critico - aggiunge validazione mancante
const createOrder = async (req, res) => {
  try {
    const { items, shippingAddress, paymentMethod } = req.body;
    
    // CRITICAL FIX: Validate order total
    let totalAmount = 0;
    
    for (const item of items) {
      // Recupera prezzo attuale dal database (non dal client)
      const product = await Product.findById(item.productId);
      if (!product) {
        return res.status(400).json({
          success: false,
          message: `Product ${item.productId} not found`
        });
      }
      
      // SECURITY: Use database price, not client price
      const itemTotal = product.price * item.quantity;
      totalAmount += itemTotal;
      
      // Validate quantity
      if (item.quantity <= 0) {
        return res.status(400).json({
          success: false,
          message: 'Invalid quantity for product ' + product.name
        });
      }
      
      // Check stock availability
      if (item.quantity > product.stock) {
        return res.status(400).json({
          success: false,
          message: `Insufficient stock for ${product.name}`
        });
      }
    }
    
    // CRITICAL: Ensure order total is above minimum
    if (totalAmount <= 0) {
      return res.status(400).json({
        success: false,
        message: 'Order total must be greater than $0'
      });
    }
    
    // Create order with validated total
    const order = new Order({
      user: req.user.id,
      items: items.map(item => ({
        product: item.productId,
        quantity: item.quantity,
        price: product.price // Use database price
      })),
      totalAmount,
      shippingAddress,
      paymentMethod,
      status: 'pending'
    });
    
    await order.save();
    
    res.status(201).json({
      success: true,
      order
    });
    
  } catch (error) {
    console.error('Order creation error:', error);
    res.status(500).json({
      success: false,
      message: 'Order creation failed'
    });
  }
};
```

**Test per validare fix:**
```javascript
// tests/hotfix/checkout-validation.test.js
describe('Checkout Validation Hotfix', () => {
  test('should reject orders with $0 total', async () => {
    const response = await request(app)
      .post('/api/orders')
      .set('Authorization', `Bearer ${userToken}`)
      .send({
        items: [
          { productId: 'product1', quantity: 0 }
        ],
        shippingAddress: validAddress,
        paymentMethod: 'credit_card'
      });
      
    expect(response.status).toBe(400);
    expect(response.body.message).toContain('must be greater than $0');
  });
  
  test('should use database prices not client prices', async () => {
    // Test che il prezzo viene preso dal database
    const maliciousRequest = {
      items: [
        { 
          productId: 'product1', 
          quantity: 1,
          price: 0.01 // Client tenta di modificare prezzo
        }
      ],
      shippingAddress: validAddress,
      paymentMethod: 'credit_card'
    };
    
    const response = await request(app)
      .post('/api/orders')
      .set('Authorization', `Bearer ${userToken}`)
      .send(maliciousRequest);
      
    expect(response.status).toBe(201);
    // Verifica che il prezzo usato sia quello del database
    expect(response.body.order.totalAmount).toBe(29.99); // Database price
  });
});
```

### 4.3 Deploy Hotfix

```bash
# Commit fix
git add .
git commit -m "hotfix(checkout): fix critical validation bypass vulnerability

CRITICAL SECURITY FIX:
- Add server-side price validation using database prices
- Prevent $0 orders through client manipulation
- Add quantity validation for all order items
- Add stock availability checks
- Add comprehensive error handling

IMPACT: Prevents revenue loss from $0 orders
SECURITY: Fixes price manipulation vulnerability

Fixes: #45 (Critical: Checkout allows $0 orders)
CVE: Pending assignment"

# Test hotfix
npm run test:hotfix
npm run build

# Finalizza hotfix
git flow hotfix finish checkout-validation-fix

# Questo automaticamente:
# 1. Merge hotfix in main
# 2. Tag v1.0.1 
# 3. Merge hotfix in develop
# 4. Cancella hotfix branch

# Push urgente
git push origin main
git push origin develop
git push origin --tags

# Deploy immediato in produzione
# Notifica team del deploy urgente
```

## Fase 5: Advanced Git Flow Scenarios

### 5.1 Multiple Release Branches

**Scenario**: Gestione di due release parallele.

```bash
# Release v1.1.0 in preparazione
git flow release start v1.1.0

# Contemporaneamente, patch release per v1.0.x
git checkout main
git flow hotfix start v1.0.2-security-patch

# Lavoro su entrambe le release...
```

### 5.2 Support Branches

**Scenario**: Supporto lungo termine per versione enterprise.

```bash
# Crea support branch per v1.0.x
git checkout v1.0.0  # Tag della release
git checkout -b support/v1.0.x
git push origin support/v1.0.x

# Bugfix specifici per enterprise clients
git checkout support/v1.0.x
git checkout -b bugfix/enterprise-specific-fix

# Fix e merge in support branch
# Tag release patch v1.0.3-enterprise
```

### 5.3 Integration con CI/CD

**.github/workflows/gitflow.yml**:
```yaml
name: Git Flow CI/CD

on:
  push:
    branches: [main, develop]
    tags: ['v*']
  pull_request:
    branches: [develop]

jobs:
  test:
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/develop' || startsWith(github.ref, 'refs/heads/feature/')
    steps:
      - uses: actions/checkout@v3
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
      - name: Install dependencies
        run: npm ci
      - name: Run tests
        run: npm run test:ci
      - name: Run linting
        run: npm run lint

  release-test:
    runs-on: ubuntu-latest
    if: startsWith(github.ref, 'refs/heads/release/')
    steps:
      - uses: actions/checkout@v3
      - name: Release testing
        run: |
          npm ci
          npm run test:integration
          npm run test:e2e
          npm run build
          npm run security-audit

  production-deploy:
    runs-on: ubuntu-latest
    if: github.ref == 'refs/heads/main'
    needs: [test]
    steps:
      - uses: actions/checkout@v3
      - name: Deploy to production
        run: |
          echo "Deploying to production..."
          # Deploy script here

  hotfix-deploy:
    runs-on: ubuntu-latest
    if: startsWith(github.ref, 'refs/tags/v') && contains(github.ref, 'hotfix')
    steps:
      - uses: actions/checkout@v3
      - name: Emergency deploy
        run: |
          echo "Emergency hotfix deployment..."
          # Emergency deploy script
```

## Deliverables dell'Esercizio

### Cosa Consegnare:

1. **Repository ShopFlow** con:
   - Git Flow structure implementata
   - Almeno 3 feature complete
   - 1 release completa (v1.0.0)
   - 1 hotfix deployato (v1.0.1)
   - 20+ commit significativi
   - Tag versioning corretto

2. **Documentazione Workflow** contenente:
   - Diagramma Git Flow utilizzato
   - Convenzioni di naming branch
   - Process per feature/release/hotfix
   - Team responsibilities matrix

3. **Report di Gestione Release** con:
   - Planning notes per release v1.0.0
   - Test results e quality metrics  
   - Post-mortem del hotfix
   - Lessons learned e improvements

4. **Codice Funzionante**:
   - Frontend React funzionante
   - Backend API funzionante
   - Database integration
   - Test suite completa

### Criteri di Valutazione:

- **Git Flow Implementation** (35%): Correct branching strategy
- **Code Quality** (25%): Clean, tested, documented code
- **Release Management** (20%): Proper versioning and deployment
- **Team Collaboration** (15%): Effective coordination e communication  
- **Documentation** (5%): Clear process documentation

### Timeline Suggerito:
- **Week 1**: Setup e prime 2 feature
- **Week 2**: Release v1.0.0 preparation
- **Week 3**: Hotfix simulation e advanced scenarios
- **Week 4**: Documentation e presentation

Questo esercizio fornisce esperienza pratica completa con Git Flow in un ambiente che simula progetti enterprise reali.
