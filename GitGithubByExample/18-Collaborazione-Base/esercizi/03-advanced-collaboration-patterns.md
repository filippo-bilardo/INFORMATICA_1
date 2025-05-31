# Esercizio 03: Advanced Collaboration Patterns

## 🎯 Obiettivo
Implementare pattern di collaborazione avanzati utilizzando GitHub per gestire un progetto con multiple team, code review rigoroso, e workflow enterprise-grade per lo sviluppo di un sistema di e-commerce modulare.

## ⏱️ Durata Stimata
**90-120 minuti**

## 📋 Prerequisiti
- Esperienza con collaborazione base Git/GitHub
- Conoscenza di JavaScript/Node.js
- Familiarità con REST API
- Account GitHub con repository access

## 🚀 Scenario
Sei parte di un team di sviluppo di una startup fintech che sta costruendo una piattaforma e-commerce. Il progetto richiede coordinazione tra Frontend Team, Backend Team, DevOps Team e QA Team utilizzando GitHub per gestire workflow complessi.

## 👥 Struttura Team (4-6 persone)

### Product Owner & Scrum Master
- **Responsabilità**: Requirements, sprint planning, stakeholder communication
- **GitHub Role**: Admin
- **Tasks**: Issues creation, milestone management, release planning

### Frontend Team Lead
- **Responsabilità**: UI/UX implementation, client-side architecture
- **GitHub Role**: Maintainer
- **Tasks**: Component development, styling, responsive design

### Backend Team Lead  
- **Responsabilità**: API development, database design, business logic
- **GitHub Role**: Maintainer
- **Tasks**: Microservices, data models, authentication

### DevOps Engineer
- **Responsabilità**: CI/CD, infrastructure, monitoring
- **GitHub Role**: Maintainer
- **Tasks**: GitHub Actions, deployment, environment management

### QA Engineer
- **Responsabilità**: Testing, quality assurance, bug tracking
- **GitHub Role**: Write access
- **Tasks**: Test automation, bug reports, quality gates

### Junior Developer
- **Responsabilità**: Support tasks, learning, code review participation
- **GitHub Role**: Write access
- **Tasks**: Feature implementation, documentation, testing

## 📝 Task Implementation Sequence

### Phase 1: Advanced Repository Setup (Product Owner)

#### 1.1 Repository Architecture
```bash
# Crea repository principale con struttura enterprise
mkdir ecommerce-platform
cd ecommerce-platform

# Inizializza con enterprise structure
git init
git branch -M main

# Crea struttura modulare
mkdir -p {frontend,backend,shared,devops,docs,tests}
mkdir -p frontend/{components,pages,utils,styles,assets}
mkdir -p backend/{api,models,services,middleware,config}
mkdir -p shared/{types,utils,constants}
mkdir -p devops/{docker,k8s,scripts,monitoring}
mkdir -p docs/{api,architecture,deployment,user}
mkdir -p tests/{unit,integration,e2e,performance}

# Root configuration files
cat > package.json << 'EOF'
{
  "name": "ecommerce-platform",
  "version": "1.0.0",
  "description": "Modern e-commerce platform with microservices architecture",
  "private": true,
  "workspaces": [
    "frontend",
    "backend",
    "shared"
  ],
  "scripts": {
    "install:all": "npm install && npm run install:frontend && npm run install:backend",
    "install:frontend": "cd frontend && npm install",
    "install:backend": "cd backend && npm install",
    "start:dev": "concurrently \"npm run start:backend\" \"npm run start:frontend\"",
    "start:frontend": "cd frontend && npm start",
    "start:backend": "cd backend && npm start",
    "test": "npm run test:frontend && npm run test:backend",
    "test:frontend": "cd frontend && npm test",
    "test:backend": "cd backend && npm test",
    "build": "npm run build:frontend && npm run build:backend",
    "build:frontend": "cd frontend && npm run build",
    "build:backend": "cd backend && npm run build",
    "lint": "npm run lint:frontend && npm run lint:backend",
    "lint:frontend": "cd frontend && npm run lint",
    "lint:backend": "cd backend && npm run lint"
  },
  "devDependencies": {
    "concurrently": "^7.6.0",
    "eslint": "^8.45.0",
    "prettier": "^3.0.0",
    "husky": "^8.0.3",
    "lint-staged": "^13.2.3"
  },
  "husky": {
    "hooks": {
      "pre-commit": "lint-staged",
      "pre-push": "npm test"
    }
  },
  "lint-staged": {
    "*.{js,jsx,ts,tsx}": ["eslint --fix", "prettier --write"],
    "*.{css,scss,md}": ["prettier --write"]
  }
}
EOF

# Shared types and utilities
cat > shared/types/index.js << 'EOF'
// Common TypeScript-like type definitions for JavaScript
const ProductTypes = {
  PHYSICAL: 'physical',
  DIGITAL: 'digital',
  SERVICE: 'service'
};

const OrderStatus = {
  PENDING: 'pending',
  PROCESSING: 'processing',
  SHIPPED: 'shipped',
  DELIVERED: 'delivered',
  CANCELLED: 'cancelled'
};

const UserRoles = {
  CUSTOMER: 'customer',
  VENDOR: 'vendor',
  ADMIN: 'admin',
  MODERATOR: 'moderator'
};

module.exports = {
  ProductTypes,
  OrderStatus,
  UserRoles
};
EOF

cat > shared/utils/validation.js << 'EOF'
class ValidationUtils {
  static validateEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
  }

  static validatePassword(password) {
    // At least 8 characters, 1 uppercase, 1 lowercase, 1 number
    const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d@$!%*?&]{8,}$/;
    return passwordRegex.test(password);
  }

  static validatePrice(price) {
    const numPrice = parseFloat(price);
    return !isNaN(numPrice) && numPrice > 0 && numPrice < 1000000;
  }

  static validateProductName(name) {
    return typeof name === 'string' && name.length >= 3 && name.length <= 100;
  }

  static sanitizeInput(input) {
    if (typeof input !== 'string') return input;
    return input.replace(/[<>\"']/g, '').trim();
  }
}

module.exports = ValidationUtils;
EOF

# Project documentation
cat > README.md << 'EOF'
# E-Commerce Platform

## 🏢 Project Overview
Modern, scalable e-commerce platform built with microservices architecture, supporting multiple vendors, comprehensive product management, and advanced user experience.

## 🏗️ Architecture
- **Frontend**: React.js with modern UI components
- **Backend**: Node.js with Express.js REST API
- **Database**: MongoDB for flexibility and scalability  
- **Authentication**: JWT-based with role management
- **Payment**: Stripe integration for secure processing
- **Deployment**: Docker containers with Kubernetes orchestration

## 👥 Team Structure
- **Product Owner**: Requirements and sprint coordination
- **Frontend Team**: UI/UX implementation and client-side logic
- **Backend Team**: API development and business logic
- **DevOps Team**: Infrastructure and deployment automation
- **QA Team**: Testing and quality assurance

## 🚀 Quick Start
```bash
# Install all dependencies
npm run install:all

# Start development environment
npm run start:dev

# Run tests
npm test

# Build for production
npm run build
```

## 📋 Development Workflow
1. **Issues**: Use GitHub Issues for feature requests and bug reports
2. **Branches**: Feature branches from `develop`, merged via Pull Request
3. **Code Review**: Minimum 2 approvals required for merging
4. **Testing**: Automated testing in CI/CD pipeline
5. **Deployment**: Automated deployment to staging and production

## 🔗 Links
- [API Documentation](docs/api/README.md)
- [Architecture Guide](docs/architecture/README.md)
- [Deployment Guide](docs/deployment/README.md)
- [Contributing Guidelines](CONTRIBUTING.md)
EOF

# Contributing guidelines
cat > CONTRIBUTING.md << 'EOF'
# Contributing Guidelines

## 🔄 Workflow Process

### 1. Issue Creation
- Use appropriate issue templates
- Add labels for categorization
- Assign to appropriate team member
- Link to project milestones

### 2. Branch Strategy
- `main`: Production-ready code
- `develop`: Integration branch for features
- `feature/*`: New features and enhancements
- `hotfix/*`: Emergency fixes for production
- `release/*`: Preparation for new releases

### 3. Pull Request Process
- Create PR from feature branch to `develop`
- Use PR template and fill all sections
- Request review from appropriate team members
- Ensure all CI checks pass
- Minimum 2 approvals required

### 4. Code Review Guidelines
- Review for functionality, performance, and security
- Check code style and documentation
- Test locally if needed
- Provide constructive feedback
- Approve only when fully satisfied

### 5. Merge Requirements
- All CI checks must pass
- Code coverage must be maintained
- No merge conflicts
- Approved by at least 2 reviewers
- Updated documentation if needed

## 🏷️ Labels and Tags
- `feature`: New functionality
- `bug`: Bug fixes
- `enhancement`: Improvements to existing features
- `documentation`: Documentation updates
- `critical`: High priority issues
- `good-first-issue`: Suitable for new contributors

## 💻 Development Standards
- Follow ESLint and Prettier configurations
- Write unit tests for new features
- Update documentation for API changes
- Use semantic commit messages
- Keep PRs focused and small
EOF

git add .
git commit -m "feat: initialize e-commerce platform with enterprise architecture

- Setup monorepo structure with workspaces
- Add shared utilities and type definitions
- Configure linting, testing, and development scripts
- Create comprehensive documentation and contributing guidelines
- Implement team workflow and collaboration processes
- Add validation utilities and common constants"
```

#### 1.2 GitHub Advanced Configuration
```bash
# Push initial setup
git remote add origin https://github.com/USERNAME/ecommerce-platform.git
git push -u origin main

# Create and push develop branch
git checkout -b develop
git push -u origin develop

# Go back to main
git checkout main
```

**GitHub Web Interface Tasks (Product Owner):**

1. **Repository Settings**:
   - Enable Issues and Projects
   - Configure branch protection rules:
     - Protect `main` and `develop` branches
     - Require pull request reviews (minimum 2)
     - Require status checks to pass
     - Require branches to be up to date
     - Restrict push access

2. **Team Management**:
   - Invite all team members
   - Assign appropriate roles and permissions
   - Create teams: `frontend-team`, `backend-team`, `devops-team`, `qa-team`

3. **Issue Templates**:
   Create `.github/ISSUE_TEMPLATE/` with templates for:
   - Feature Request
   - Bug Report  
   - Epic/User Story
   - Technical Debt

4. **PR Template**:
   Create `.github/pull_request_template.md`

5. **Project Board**:
   - Create project board with columns: Backlog, Sprint Planning, In Progress, Review, Testing, Done
   - Add automation rules for issue and PR management

### Phase 2: Frontend Development (Frontend Team Lead)

#### 2.1 Frontend Setup and Component Architecture
```bash
# Checkout develop and create frontend feature branch
git checkout develop
git pull origin develop
git checkout -b feature/frontend-setup

# Frontend package.json
cat > frontend/package.json << 'EOF'
{
  "name": "ecommerce-frontend",
  "version": "1.0.0",
  "private": true,
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-router-dom": "^6.14.0",
    "react-scripts": "5.0.1",
    "axios": "^1.4.0",
    "@mui/material": "^5.14.0",
    "@emotion/react": "^11.11.0",
    "@emotion/styled": "^11.11.0",
    "react-query": "^3.39.3",
    "react-hook-form": "^7.45.0",
    "web-vitals": "^3.3.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test",
    "eject": "react-scripts eject",
    "lint": "eslint src/ --ext .js,.jsx,.ts,.tsx",
    "lint:fix": "eslint src/ --ext .js,.jsx,.ts,.tsx --fix"
  },
  "eslintConfig": {
    "extends": [
      "react-app",
      "react-app/jest"
    ]
  },
  "browserslist": {
    "production": [
      ">0.2%",
      "not dead",
      "not op_mini all"
    ],
    "development": [
      "last 1 chrome version",
      "last 1 firefox version",
      "last 1 safari version"
    ]
  },
  "devDependencies": {
    "@testing-library/jest-dom": "^5.16.5",
    "@testing-library/react": "^13.4.0",
    "@testing-library/user-event": "^14.4.3"
  }
}
EOF

# Main App component
cat > frontend/src/App.js << 'EOF'
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { QueryClient, QueryClientProvider } from 'react-query';
import { ThemeProvider, createTheme } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';

// Components
import Navigation from './components/Navigation/Navigation';
import Home from './pages/Home/Home';
import Products from './pages/Products/Products';
import ProductDetail from './pages/ProductDetail/ProductDetail';
import Cart from './pages/Cart/Cart';
import Checkout from './pages/Checkout/Checkout';
import Profile from './pages/Profile/Profile';
import Admin from './pages/Admin/Admin';

// Theme configuration
const theme = createTheme({
  palette: {
    primary: {
      main: '#2563eb',
    },
    secondary: {
      main: '#7c3aed',
    },
  },
  typography: {
    fontFamily: '"Inter", "Roboto", "Helvetica", "Arial", sans-serif',
  },
});

// React Query client
const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      retry: 3,
      staleTime: 5 * 60 * 1000, // 5 minutes
    },
  },
});

function App() {
  return (
    <QueryClientProvider client={queryClient}>
      <ThemeProvider theme={theme}>
        <CssBaseline />
        <Router>
          <div className="App">
            <Navigation />
            <main>
              <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/products" element={<Products />} />
                <Route path="/products/:id" element={<ProductDetail />} />
                <Route path="/cart" element={<Cart />} />
                <Route path="/checkout" element={<Checkout />} />
                <Route path="/profile" element={<Profile />} />
                <Route path="/admin" element={<Admin />} />
              </Routes>
            </main>
          </div>
        </Router>
      </ThemeProvider>
    </QueryClientProvider>
  );
}

export default App;
EOF

# Navigation component
mkdir -p frontend/src/components/Navigation
cat > frontend/src/components/Navigation/Navigation.js << 'EOF'
import React, { useState } from 'react';
import {
  AppBar,
  Toolbar,
  Typography,
  Button,
  IconButton,
  Badge,
  Menu,
  MenuItem,
  Box,
  InputBase,
  styled,
  alpha
} from '@mui/material';
import {
  ShoppingCart as CartIcon,
  Search as SearchIcon,
  AccountCircle,
  Menu as MenuIcon
} from '@mui/icons-material';
import { Link, useNavigate } from 'react-router-dom';

// Styled components
const Search = styled('div')(({ theme }) => ({
  position: 'relative',
  borderRadius: theme.shape.borderRadius,
  backgroundColor: alpha(theme.palette.common.white, 0.15),
  '&:hover': {
    backgroundColor: alpha(theme.palette.common.white, 0.25),
  },
  marginRight: theme.spacing(2),
  marginLeft: 0,
  width: '100%',
  [theme.breakpoints.up('sm')]: {
    marginLeft: theme.spacing(3),
    width: 'auto',
  },
}));

const SearchIconWrapper = styled('div')(({ theme }) => ({
  padding: theme.spacing(0, 2),
  height: '100%',
  position: 'absolute',
  pointerEvents: 'none',
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
}));

const StyledInputBase = styled(InputBase)(({ theme }) => ({
  color: 'inherit',
  '& .MuiInputBase-input': {
    padding: theme.spacing(1, 1, 1, 0),
    paddingLeft: `calc(1em + ${theme.spacing(4)})`,
    transition: theme.transitions.create('width'),
    width: '100%',
    [theme.breakpoints.up('md')]: {
      width: '20ch',
    },
  },
}));

function Navigation() {
  const [anchorEl, setAnchorEl] = useState(null);
  const [cartItems] = useState(3); // Mock cart count
  const navigate = useNavigate();

  const handleProfileMenuOpen = (event) => {
    setAnchorEl(event.currentTarget);
  };

  const handleMenuClose = () => {
    setAnchorEl(null);
  };

  const handleSearch = (event) => {
    if (event.key === 'Enter') {
      const searchTerm = event.target.value;
      navigate(`/products?search=${encodeURIComponent(searchTerm)}`);
    }
  };

  return (
    <AppBar position="sticky">
      <Toolbar>
        <Typography
          variant="h6"
          component={Link}
          to="/"
          sx={{
            flexGrow: 0,
            textDecoration: 'none',
            color: 'inherit',
            fontWeight: 'bold'
          }}
        >
          E-Shop
        </Typography>

        <Search>
          <SearchIconWrapper>
            <SearchIcon />
          </SearchIconWrapper>
          <StyledInputBase
            placeholder="Search products..."
            inputProps={{ 'aria-label': 'search' }}
            onKeyPress={handleSearch}
          />
        </Search>

        <Box sx={{ flexGrow: 1 }} />

        <Button color="inherit" component={Link} to="/products">
          Products
        </Button>

        <IconButton
          color="inherit"
          component={Link}
          to="/cart"
          aria-label={`show ${cartItems} items in cart`}
        >
          <Badge badgeContent={cartItems} color="secondary">
            <CartIcon />
          </Badge>
        </IconButton>

        <IconButton
          edge="end"
          aria-label="account of current user"
          aria-controls="primary-search-account-menu"
          aria-haspopup="true"
          onClick={handleProfileMenuOpen}
          color="inherit"
        >
          <AccountCircle />
        </IconButton>

        <Menu
          anchorEl={anchorEl}
          anchorOrigin={{
            vertical: 'top',
            horizontal: 'right',
          }}
          keepMounted
          transformOrigin={{
            vertical: 'top',
            horizontal: 'right',
          }}
          open={Boolean(anchorEl)}
          onClose={handleMenuClose}
        >
          <MenuItem onClick={handleMenuClose} component={Link} to="/profile">
            Profile
          </MenuItem>
          <MenuItem onClick={handleMenuClose} component={Link} to="/admin">
            Admin
          </MenuItem>
          <MenuItem onClick={handleMenuClose}>
            Logout
          </MenuItem>
        </Menu>
      </Toolbar>
    </AppBar>
  );
}

export default Navigation;
EOF

# Product card component
mkdir -p frontend/src/components/ProductCard
cat > frontend/src/components/ProductCard/ProductCard.js << 'EOF'
import React from 'react';
import {
  Card,
  CardMedia,
  CardContent,
  CardActions,
  Typography,
  Button,
  Chip,
  Box,
  Rating
} from '@mui/material';
import { AddShoppingCart, Favorite, FavoriteBorder } from '@mui/icons-material';
import { Link } from 'react-router-dom';

function ProductCard({ product, onAddToCart, onToggleFavorite, isFavorite = false }) {
  const handleAddToCart = (e) => {
    e.preventDefault();
    e.stopPropagation();
    onAddToCart(product);
  };

  const handleToggleFavorite = (e) => {
    e.preventDefault();
    e.stopPropagation();
    onToggleFavorite(product.id);
  };

  return (
    <Card 
      sx={{ 
        height: '100%', 
        display: 'flex', 
        flexDirection: 'column',
        '&:hover': {
          transform: 'translateY(-4px)',
          boxShadow: 4
        },
        transition: 'all 0.3s ease-in-out'
      }}
      component={Link}
      to={`/products/${product.id}`}
      style={{ textDecoration: 'none' }}
    >
      <CardMedia
        component="img"
        height="200"
        image={product.image || `https://picsum.photos/300/200?random=${product.id}`}
        alt={product.name}
        sx={{ objectFit: 'cover' }}
      />
      
      <CardContent sx={{ flexGrow: 1 }}>
        <Box display="flex" justifyContent="space-between" alignItems="flex-start" mb={1}>
          <Typography gutterBottom variant="h6" component="h2" noWrap>
            {product.name}
          </Typography>
          <Chip 
            label={product.category} 
            size="small" 
            color="primary" 
            variant="outlined"
          />
        </Box>
        
        <Typography variant="body2" color="text.secondary" sx={{ mb: 1 }}>
          {product.description.length > 100 
            ? `${product.description.substring(0, 100)}...` 
            : product.description
          }
        </Typography>
        
        <Box display="flex" alignItems="center" gap={1} mb={1}>
          <Rating value={product.rating || 4.5} precision={0.5} size="small" readOnly />
          <Typography variant="body2" color="text.secondary">
            ({product.reviewCount || 0})
          </Typography>
        </Box>
        
        <Typography variant="h6" color="primary" fontWeight="bold">
          ${product.price.toFixed(2)}
        </Typography>
        
        {product.originalPrice && product.originalPrice > product.price && (
          <Typography 
            variant="body2" 
            color="text.secondary" 
            sx={{ textDecoration: 'line-through' }}
          >
            ${product.originalPrice.toFixed(2)}
          </Typography>
        )}
      </CardContent>
      
      <CardActions>
        <Button
          size="small"
          startIcon={<AddShoppingCart />}
          onClick={handleAddToCart}
          variant="contained"
          fullWidth
          disabled={!product.inStock}
        >
          {product.inStock ? 'Add to Cart' : 'Out of Stock'}
        </Button>
        
        <Button
          size="small"
          onClick={handleToggleFavorite}
          color="secondary"
        >
          {isFavorite ? <Favorite /> : <FavoriteBorder />}
        </Button>
      </CardActions>
    </Card>
  );
}

export default ProductCard;
EOF

git add .
git commit -m "feat(frontend): implement core navigation and product components

- Add React Router navigation with Material-UI design
- Create responsive navigation bar with search functionality
- Implement ProductCard component with hover effects
- Add shopping cart and favorites functionality
- Configure theme and global styles
- Setup React Query for state management
- Add user profile and admin navigation"

git push -u origin feature/frontend-setup
```

### Phase 3: Backend Development (Backend Team Lead)

#### 3.1 API Foundation and Data Models
```bash
# Create backend feature branch from develop
git checkout develop
git pull origin develop
git checkout -b feature/backend-api

# Backend package.json
cat > backend/package.json << 'EOF'
{
  "name": "ecommerce-backend",
  "version": "1.0.0",
  "description": "E-commerce platform REST API",
  "main": "server.js",
  "scripts": {
    "start": "node server.js",
    "dev": "nodemon server.js",
    "test": "jest",
    "test:watch": "jest --watch",
    "test:coverage": "jest --coverage",
    "lint": "eslint . --ext .js",
    "lint:fix": "eslint . --ext .js --fix"
  },
  "dependencies": {
    "express": "^4.18.2",
    "mongoose": "^7.4.0",
    "cors": "^2.8.5",
    "helmet": "^7.0.0",
    "morgan": "^1.10.0",
    "compression": "^1.7.4",
    "express-rate-limit": "^6.8.1",
    "bcryptjs": "^2.4.3",
    "jsonwebtoken": "^9.0.1",
    "joi": "^17.9.2",
    "dotenv": "^16.3.1",
    "express-async-handler": "^1.2.0"
  },
  "devDependencies": {
    "nodemon": "^3.0.1",
    "jest": "^29.6.1",
    "supertest": "^6.3.3",
    "eslint": "^8.45.0"
  }
}
EOF

# Main server setup
cat > backend/server.js << 'EOF'
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const compression = require('compression');
const rateLimit = require('express-rate-limit');
require('dotenv').config();

// Import routes
const productRoutes = require('./api/routes/products');
const userRoutes = require('./api/routes/users');
const orderRoutes = require('./api/routes/orders');
const authRoutes = require('./api/routes/auth');

// Import middleware
const errorHandler = require('./middleware/errorHandler');
const { authenticateToken } = require('./middleware/auth');

const app = express();
const PORT = process.env.PORT || 5000;

// Rate limiting
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 100, // limit each IP to 100 requests per windowMs
  message: 'Too many requests from this IP, please try again later.'
});

// Middleware
app.use(helmet());
app.use(compression());
app.use(cors({
  origin: process.env.FRONTEND_URL || 'http://localhost:3000',
  credentials: true
}));
app.use(morgan('combined'));
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));
app.use('/api/', limiter);

// Health check endpoint
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'healthy',
    timestamp: new Date().toISOString(),
    uptime: process.uptime(),
    environment: process.env.NODE_ENV || 'development'
  });
});

// API routes
app.use('/api/auth', authRoutes);
app.use('/api/products', productRoutes);
app.use('/api/users', authenticateToken, userRoutes);
app.use('/api/orders', authenticateToken, orderRoutes);

// Error handling middleware
app.use(errorHandler);

// 404 handler
app.use('*', (req, res) => {
  res.status(404).json({
    success: false,
    message: 'API endpoint not found'
  });
});

// Start server
app.listen(PORT, () => {
  console.log(`🚀 Server running on port ${PORT}`);
  console.log(`📖 API Documentation: http://localhost:${PORT}/api/docs`);
  console.log(`🔍 Health Check: http://localhost:${PORT}/health`);
});

module.exports = app;
EOF

# Product model
mkdir -p backend/models
cat > backend/models/Product.js << 'EOF'
const mongoose = require('mongoose');

const reviewSchema = new mongoose.Schema({
  user: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User',
    required: true
  },
  rating: {
    type: Number,
    required: true,
    min: 1,
    max: 5
  },
  comment: {
    type: String,
    required: true,
    maxlength: 500
  },
  helpful: {
    type: Number,
    default: 0
  }
}, { timestamps: true });

const productSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    trim: true,
    maxlength: 100
  },
  description: {
    type: String,
    required: true,
    maxlength: 1000
  },
  price: {
    type: Number,
    required: true,
    min: 0
  },
  originalPrice: {
    type: Number,
    min: 0
  },
  category: {
    type: String,
    required: true,
    enum: ['electronics', 'clothing', 'books', 'home', 'sports', 'beauty', 'toys']
  },
  subcategory: {
    type: String,
    required: true
  },
  brand: {
    type: String,
    required: true
  },
  sku: {
    type: String,
    required: true,
    unique: true
  },
  images: [{
    url: String,
    alt: String,
    isPrimary: Boolean
  }],
  specifications: {
    type: Map,
    of: String
  },
  inventory: {
    quantity: {
      type: Number,
      required: true,
      min: 0
    },
    lowStockThreshold: {
      type: Number,
      default: 10
    },
    trackInventory: {
      type: Boolean,
      default: true
    }
  },
  dimensions: {
    length: Number,
    width: Number,
    height: Number,
    weight: Number,
    unit: {
      type: String,
      enum: ['cm', 'inch'],
      default: 'cm'
    }
  },
  shipping: {
    free: {
      type: Boolean,
      default: false
    },
    weight: Number,
    dimensions: {
      length: Number,
      width: Number,
      height: Number
    }
  },
  reviews: [reviewSchema],
  rating: {
    average: {
      type: Number,
      default: 0,
      min: 0,
      max: 5
    },
    count: {
      type: Number,
      default: 0
    }
  },
  tags: [String],
  status: {
    type: String,
    enum: ['active', 'inactive', 'discontinued'],
    default: 'active'
  },
  featured: {
    type: Boolean,
    default: false
  },
  vendor: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User',
    required: true
  }
}, {
  timestamps: true,
  toJSON: { virtuals: true },
  toObject: { virtuals: true }
});

// Virtual for computed fields
productSchema.virtual('inStock').get(function() {
  return this.inventory.quantity > 0;
});

productSchema.virtual('onSale').get(function() {
  return this.originalPrice && this.originalPrice > this.price;
});

// Indexes for performance
productSchema.index({ name: 'text', description: 'text' });
productSchema.index({ category: 1, subcategory: 1 });
productSchema.index({ price: 1 });
productSchema.index({ 'rating.average': -1 });
productSchema.index({ featured: 1 });
productSchema.index({ status: 1 });

// Middleware to update rating when reviews change
productSchema.methods.updateRating = function() {
  if (this.reviews.length > 0) {
    const totalRating = this.reviews.reduce((sum, review) => sum + review.rating, 0);
    this.rating.average = totalRating / this.reviews.length;
    this.rating.count = this.reviews.length;
  } else {
    this.rating.average = 0;
    this.rating.count = 0;
  }
};

module.exports = mongoose.model('Product', productSchema);
EOF

# Product API routes
mkdir -p backend/api/routes
cat > backend/api/routes/products.js << 'EOF'
const express = require('express');
const asyncHandler = require('express-async-handler');
const Product = require('../../models/Product');
const { validateProduct, validateProductUpdate } = require('../../middleware/validation');
const { authenticateToken, requireRole } = require('../../middleware/auth');

const router = express.Router();

// @desc    Get all products with filtering, sorting, and pagination
// @route   GET /api/products
// @access  Public
router.get('/', asyncHandler(async (req, res) => {
  const page = parseInt(req.query.page) || 1;
  const limit = parseInt(req.query.limit) || 12;
  const skip = (page - 1) * limit;

  // Build query
  let query = { status: 'active' };

  // Category filter
  if (req.query.category) {
    query.category = req.query.category;
  }

  // Price range filter
  if (req.query.minPrice || req.query.maxPrice) {
    query.price = {};
    if (req.query.minPrice) query.price.$gte = parseFloat(req.query.minPrice);
    if (req.query.maxPrice) query.price.$lte = parseFloat(req.query.maxPrice);
  }

  // Search functionality
  if (req.query.search) {
    query.$text = { $search: req.query.search };
  }

  // In stock filter
  if (req.query.inStock === 'true') {
    query['inventory.quantity'] = { $gt: 0 };
  }

  // Build sort
  let sort = {};
  switch (req.query.sort) {
    case 'price_asc':
      sort.price = 1;
      break;
    case 'price_desc':
      sort.price = -1;
      break;
    case 'rating':
      sort['rating.average'] = -1;
      break;
    case 'newest':
      sort.createdAt = -1;
      break;
    default:
      sort.featured = -1;
      sort.createdAt = -1;
  }

  const products = await Product.find(query)
    .sort(sort)
    .skip(skip)
    .limit(limit)
    .populate('vendor', 'name email')
    .select('-reviews'); // Exclude reviews for performance

  const total = await Product.countDocuments(query);

  res.json({
    success: true,
    data: products,
    pagination: {
      page,
      limit,
      total,
      pages: Math.ceil(total / limit),
      hasNext: page < Math.ceil(total / limit),
      hasPrev: page > 1
    }
  });
}));

// @desc    Get single product
// @route   GET /api/products/:id
// @access  Public
router.get('/:id', asyncHandler(async (req, res) => {
  const product = await Product.findById(req.params.id)
    .populate('vendor', 'name email')
    .populate('reviews.user', 'name');

  if (!product) {
    return res.status(404).json({
      success: false,
      message: 'Product not found'
    });
  }

  res.json({
    success: true,
    data: product
  });
}));

// @desc    Create new product
// @route   POST /api/products
// @access  Private (Vendor/Admin)
router.post('/', 
  authenticateToken, 
  requireRole(['vendor', 'admin']), 
  validateProduct, 
  asyncHandler(async (req, res) => {
    const productData = {
      ...req.body,
      vendor: req.user.id
    };

    const product = await Product.create(productData);

    res.status(201).json({
      success: true,
      data: product
    });
  })
);

// @desc    Update product
// @route   PUT /api/products/:id
// @access  Private (Vendor/Admin)
router.put('/:id', 
  authenticateToken, 
  requireRole(['vendor', 'admin']), 
  validateProductUpdate,
  asyncHandler(async (req, res) => {
    let product = await Product.findById(req.params.id);

    if (!product) {
      return res.status(404).json({
        success: false,
        message: 'Product not found'
      });
    }

    // Check if user owns the product or is admin
    if (product.vendor.toString() !== req.user.id && req.user.role !== 'admin') {
      return res.status(403).json({
        success: false,
        message: 'Not authorized to update this product'
      });
    }

    product = await Product.findByIdAndUpdate(
      req.params.id,
      req.body,
      { new: true, runValidators: true }
    );

    res.json({
      success: true,
      data: product
    });
  })
);

// @desc    Delete product
// @route   DELETE /api/products/:id
// @access  Private (Vendor/Admin)
router.delete('/:id', 
  authenticateToken, 
  requireRole(['vendor', 'admin']), 
  asyncHandler(async (req, res) => {
    const product = await Product.findById(req.params.id);

    if (!product) {
      return res.status(404).json({
        success: false,
        message: 'Product not found'
      });
    }

    // Check if user owns the product or is admin
    if (product.vendor.toString() !== req.user.id && req.user.role !== 'admin') {
      return res.status(403).json({
        success: false,
        message: 'Not authorized to delete this product'
      });
    }

    await Product.findByIdAndDelete(req.params.id);

    res.json({
      success: true,
      message: 'Product deleted successfully'
    });
  })
);

// @desc    Add product review
// @route   POST /api/products/:id/reviews
// @access  Private
router.post('/:id/reviews', 
  authenticateToken, 
  asyncHandler(async (req, res) => {
    const { rating, comment } = req.body;

    const product = await Product.findById(req.params.id);

    if (!product) {
      return res.status(404).json({
        success: false,
        message: 'Product not found'
      });
    }

    // Check if user already reviewed this product
    const existingReview = product.reviews.find(
      review => review.user.toString() === req.user.id
    );

    if (existingReview) {
      return res.status(400).json({
        success: false,
        message: 'You have already reviewed this product'
      });
    }

    const review = {
      user: req.user.id,
      rating: Number(rating),
      comment
    };

    product.reviews.push(review);
    product.updateRating();

    await product.save();

    res.status(201).json({
      success: true,
      message: 'Review added successfully'
    });
  })
);

module.exports = router;
EOF

git add .
git commit -m "feat(backend): implement comprehensive product API

- Create Express.js server with security middleware
- Implement Product model with reviews and inventory
- Add product CRUD operations with authentication
- Include search, filtering, and pagination
- Add product review system
- Implement role-based access control
- Add comprehensive validation and error handling
- Include performance optimizations with indexes"

git push -u origin feature/backend-api
```

### Phase 4: Advanced Collaboration - Pull Request Workflow

#### 4.1 Create Pull Requests for Code Review
```bash
# Frontend team creates PR
# Go to GitHub web interface and create PR from feature/frontend-setup to develop
# Title: "feat(frontend): implement core navigation and product components"
# Use PR template and request reviews from backend team and QA

# Backend team creates PR
# Go to GitHub web interface and create PR from feature/backend-api to develop
# Title: "feat(backend): implement comprehensive product API"
# Request reviews from frontend team and DevOps
```

#### 4.2 Simulate Code Review Process
**Code Review Guidelines for Teams:**

1. **Frontend Team Review**:
   - Check component structure and reusability
   - Verify responsive design implementation
   - Test accessibility features
   - Review performance optimizations

2. **Backend Team Review**:
   - Verify API security and validation
   - Check database performance and indexes
   - Review error handling and logging
   - Test authentication and authorization

3. **DevOps Team Review**:
   - Check Docker and deployment configurations
   - Verify environment variable usage
   - Review CI/CD pipeline compatibility
   - Check monitoring and logging setup

4. **QA Team Review**:
   - Verify test coverage and quality
   - Check edge cases and error scenarios
   - Review API documentation
   - Test integration points

### Phase 5: Integration and Conflict Resolution

#### 5.1 Merge Conflicts and Resolution
```bash
# After PRs are approved, merge to develop creates conflicts
git checkout develop
git pull origin develop

# If there are conflicts between frontend and backend integration
git checkout -b feature/integration-fixes

# Create integration layer
mkdir -p frontend/src/services
cat > frontend/src/services/api.js << 'EOF'
import axios from 'axios';

const API_BASE_URL = process.env.REACT_APP_API_URL || 'http://localhost:5000/api';

// Create axios instance with defaults
const api = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    'Content-Type': 'application/json',
  },
  timeout: 10000,
});

// Request interceptor to add auth token
api.interceptors.request.use(
  (config) => {
    const token = localStorage.getItem('authToken');
    if (token) {
      config.headers.Authorization = `Bearer ${token}`;
    }
    return config;
  },
  (error) => {
    return Promise.reject(error);
  }
);

// Response interceptor for error handling
api.interceptors.response.use(
  (response) => response.data,
  (error) => {
    if (error.response?.status === 401) {
      localStorage.removeItem('authToken');
      window.location.href = '/login';
    }
    
    return Promise.reject({
      message: error.response?.data?.message || 'An error occurred',
      status: error.response?.status,
      data: error.response?.data
    });
  }
);

// Product API methods
export const productAPI = {
  getAll: (params = {}) => api.get('/products', { params }),
  getById: (id) => api.get(`/products/${id}`),
  create: (data) => api.post('/products', data),
  update: (id, data) => api.put(`/products/${id}`, data),
  delete: (id) => api.delete(`/products/${id}`),
  addReview: (id, review) => api.post(`/products/${id}/reviews`, review),
};

// User API methods
export const userAPI = {
  getProfile: () => api.get('/users/profile'),
  updateProfile: (data) => api.put('/users/profile', data),
  getOrders: () => api.get('/users/orders'),
};

// Auth API methods
export const authAPI = {
  login: (credentials) => api.post('/auth/login', credentials),
  register: (userData) => api.post('/auth/register', userData),
  logout: () => api.post('/auth/logout'),
  refreshToken: () => api.post('/auth/refresh'),
};

export default api;
EOF

# Resolve any package.json conflicts
cat > package.json << 'EOF'
{
  "name": "ecommerce-platform",
  "version": "1.0.0",
  "description": "Modern e-commerce platform with microservices architecture",
  "private": true,
  "workspaces": [
    "frontend",
    "backend",
    "shared"
  ],
  "scripts": {
    "install:all": "npm install && npm run install:frontend && npm run install:backend",
    "install:frontend": "cd frontend && npm install",
    "install:backend": "cd backend && npm install",
    "start:dev": "concurrently \"npm run start:backend\" \"npm run start:frontend\"",
    "start:frontend": "cd frontend && npm start",
    "start:backend": "cd backend && npm run dev",
    "test": "npm run test:frontend && npm run test:backend",
    "test:frontend": "cd frontend && npm test -- --coverage --passWithNoTests",
    "test:backend": "cd backend && npm test",
    "build": "npm run build:frontend && npm run build:backend",
    "build:frontend": "cd frontend && npm run build",
    "build:backend": "cd backend && npm run build",
    "lint": "npm run lint:frontend && npm run lint:backend",
    "lint:frontend": "cd frontend && npm run lint",
    "lint:backend": "cd backend && npm run lint",
    "deploy:staging": "npm run build && npm run deploy:staging:run",
    "deploy:production": "npm run build && npm run deploy:prod:run"
  },
  "devDependencies": {
    "concurrently": "^7.6.0",
    "eslint": "^8.45.0",
    "prettier": "^3.0.0",
    "husky": "^8.0.3",
    "lint-staged": "^13.2.3"
  },
  "husky": {
    "hooks": {
      "pre-commit": "lint-staged",
      "pre-push": "npm test"
    }
  },
  "lint-staged": {
    "*.{js,jsx,ts,tsx}": ["eslint --fix", "prettier --write"],
    "*.{css,scss,md}": ["prettier --write"]
  }
}
EOF

git add .
git commit -m "feat(integration): resolve frontend-backend integration conflicts

- Create unified API service layer for frontend
- Resolve package.json conflicts between frontend and backend
- Add proper error handling and authentication interceptors
- Update scripts for development and production workflows
- Ensure compatibility between frontend and backend dependencies"

git push -u origin feature/integration-fixes
```

## 📊 Advanced Collaboration Assessment

### Team Performance Metrics

**Pull Request Quality:**
- [ ] All PRs have descriptive titles and detailed descriptions
- [ ] Code changes are focused and atomic
- [ ] Proper branching strategy followed (feature/* from develop)
- [ ] All CI checks pass before merge requests

**Code Review Excellence:**
- [ ] Minimum 2 reviewers per PR with meaningful feedback
- [ ] Security and performance concerns addressed
- [ ] Code style and documentation standards maintained
- [ ] Integration testing considerations included

**Communication Effectiveness:**
- [ ] Issues are well-documented with acceptance criteria
- [ ] Team discussions are captured in PR comments
- [ ] Conflicts resolved through collaborative discussion
- [ ] Knowledge sharing evident in code comments

**Workflow Mastery:**
- [ ] Advanced Git operations (rebase, cherry-pick) used appropriately
- [ ] Merge conflicts resolved cleanly with proper testing
- [ ] Release branching and tagging implemented correctly
- [ ] Emergency hotfix procedures demonstrated

## 🎯 Collaboration Excellence Challenges

### Challenge 1: Cross-Team Feature Implementation
Implement a complex feature (e.g., real-time inventory updates) that requires coordination across all teams with tight integration points.

### Challenge 2: Emergency Production Fix
Simulate a critical production bug that requires immediate hotfix while maintaining code quality and review standards.

### Challenge 3: Scalability Refactoring
Plan and execute a major refactoring (e.g., microservices migration) with multiple teams working on dependent components.

## 📚 Advanced Resources

### Collaboration Tools and Practices
- [GitHub Flow](https://guides.github.com/introduction/flow/) - Lightweight branching model
- [Code Review Best Practices](https://github.com/features/code-review/) - Effective review techniques
- [Team Collaboration](https://docs.github.com/en/organizations) - Organization and team management

### Enterprise Git Workflows
- [Git Flow](https://nvie.com/posts/a-successful-git-branching-model/) - Advanced branching strategies
- [Conventional Commits](https://conventionalcommits.org/) - Standardized commit messaging
- [Semantic Versioning](https://semver.org/) - Version management strategies

## 🔄 Navigazione

- [⬅️ Esercizio Precedente](02-conflict-simulation.md)
- [📚 Torna alla Sezione Esercizi](README.md)
- [🏠 Torna al Modulo Collaborazione Base](../README.md)
- [➡️ Prossimo Modulo: Fork e Pull Request](../../19-Fork-e-Pull-Request/README.md)

---

*Questo esercizio sviluppa competenze enterprise-level nella collaborazione software, preparando i partecipanti per ambienti di sviluppo professionali complessi.*
