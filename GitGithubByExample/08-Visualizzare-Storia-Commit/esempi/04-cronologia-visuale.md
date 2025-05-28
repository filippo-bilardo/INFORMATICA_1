# Esempio Pratico 04: Cronologia Visuale e Strumenti Grafici

## Obiettivi
- Utilizzare strumenti grafici per visualizzare la storia di Git
- Configurare e personalizzare interfacce visive
- Analizzare branch e merge attraverso rappresentazioni grafiche
- Integrare strumenti di visualizzazione nel workflow di sviluppo

## Scenario: Sviluppo di un'Applicazione E-commerce Multi-team

Siamo part di un team di sviluppo che lavora su un'applicazione e-commerce complessa. Il progetto coinvolge 4 team diversi (Frontend, Backend, Mobile, DevOps) che lavorano simultaneamente su feature diverse. Utilizzeremo strumenti grafici per comprendere e gestire questa complessità.

### Setup del Repository Multi-branch

```bash
# Creiamo il repository principale
mkdir ecommerce-visual-history
cd ecommerce-visual-history
git init

# Configuriamo alcuni alias utili per la visualizzazione
git config alias.tree "log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --all"
git config alias.branches "branch -av"
git config alias.history "log --oneline --graph --decorate --all"

# Struttura del progetto
mkdir -p {frontend/{src,public,tests},backend/{api,models,services},mobile/{ios,android},devops/{docker,kubernetes,scripts}}

# File principale del progetto
cat > README.md << 'EOF'
# E-commerce Platform

Piattaforma e-commerce multi-canale con architettura microservizi.

## Team Structure
- **Frontend Team**: React.js, TypeScript, Material-UI
- **Backend Team**: Node.js, Express, MongoDB
- **Mobile Team**: React Native, iOS/Android native
- **DevOps Team**: Docker, Kubernetes, CI/CD

## Architecture
- Frontend SPA con SSR
- Backend API RESTful + GraphQL
- Mobile app cross-platform
- Microservizi containerizzati
- Database MongoDB con Redis cache
EOF

# Package.json principale
cat > package.json << 'EOF'
{
  "name": "ecommerce-platform",
  "version": "1.0.0",
  "description": "Multi-channel e-commerce platform",
  "workspaces": [
    "frontend",
    "backend", 
    "mobile"
  ],
  "scripts": {
    "install:all": "npm install && npm run install:frontend && npm run install:backend",
    "install:frontend": "cd frontend && npm install",
    "install:backend": "cd backend && npm install",
    "dev": "concurrently \"npm run dev:frontend\" \"npm run dev:backend\"",
    "test:all": "npm run test:frontend && npm run test:backend"
  },
  "devDependencies": {
    "concurrently": "^7.6.0"
  }
}
EOF

git add .
git commit -m "initial: setup multi-team e-commerce project structure

- Initialize workspace with frontend, backend, mobile, devops
- Configure team-based directory structure
- Add root package.json with workspace configuration
- Document architecture and team responsibilities"

# Creiamo i branch per i diversi team
git branch feature/frontend-redesign
git branch feature/backend-api-v2
git branch feature/mobile-app
git branch feature/devops-containerization
git branch hotfix/security-patch
git branch release/v1.1.0
```

### Sviluppo Parallelo dei Team

#### Team Frontend - Feature Branch

```bash
git checkout feature/frontend-redesign

# Componenti React del frontend
mkdir -p frontend/src/{components,pages,hooks,utils,styles}

cat > frontend/package.json << 'EOF'
{
  "name": "ecommerce-frontend",
  "version": "1.0.0",
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-router-dom": "^6.8.0",
    "@mui/material": "^5.11.0",
    "@emotion/react": "^11.10.0",
    "axios": "^1.3.0",
    "redux-toolkit": "^1.9.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test"
  }
}
EOF

cat > frontend/src/App.js << 'EOF'
import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { ThemeProvider, createTheme } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';
import Header from './components/Header';
import ProductList from './pages/ProductList';
import ProductDetail from './pages/ProductDetail';
import Cart from './pages/Cart';
import Checkout from './pages/Checkout';

const theme = createTheme({
  palette: {
    primary: {
      main: '#1976d2',
    },
    secondary: {
      main: '#dc004e',
    },
  },
});

function App() {
  return (
    <ThemeProvider theme={theme}>
      <CssBaseline />
      <Router>
        <Header />
        <Routes>
          <Route path="/" element={<ProductList />} />
          <Route path="/product/:id" element={<ProductDetail />} />
          <Route path="/cart" element={<Cart />} />
          <Route path="/checkout" element={<Checkout />} />
        </Routes>
      </Router>
    </ThemeProvider>
  );
}

export default App;
EOF

cat > frontend/src/components/Header.js << 'EOF'
import React, { useState } from 'react';
import {
  AppBar,
  Toolbar,
  Typography,
  Button,
  Badge,
  IconButton,
  Menu,
  MenuItem
} from '@mui/material';
import {
  ShoppingCart as CartIcon,
  AccountCircle,
  Search as SearchIcon
} from '@mui/icons-material';
import { useSelector } from 'react-redux';

const Header = () => {
  const [anchorEl, setAnchorEl] = useState(null);
  const cartItems = useSelector(state => state.cart.items);
  const user = useSelector(state => state.auth.user);

  const handleProfileMenu = (event) => {
    setAnchorEl(event.currentTarget);
  };

  const handleClose = () => {
    setAnchorEl(null);
  };

  return (
    <AppBar position="sticky">
      <Toolbar>
        <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
          EcommercePro
        </Typography>
        
        <IconButton color="inherit">
          <SearchIcon />
        </IconButton>
        
        <IconButton color="inherit">
          <Badge badgeContent={cartItems?.length || 0} color="error">
            <CartIcon />
          </Badge>
        </IconButton>
        
        <IconButton
          color="inherit"
          onClick={handleProfileMenu}
        >
          <AccountCircle />
        </IconButton>
        
        <Menu
          anchorEl={anchorEl}
          open={Boolean(anchorEl)}
          onClose={handleClose}
        >
          <MenuItem onClick={handleClose}>Profile</MenuItem>
          <MenuItem onClick={handleClose}>My Orders</MenuItem>
          <MenuItem onClick={handleClose}>Logout</MenuItem>
        </Menu>
      </Toolbar>
    </AppBar>
  );
};

export default Header;
EOF

git add .
git commit -m "feat(frontend): implement new Material-UI design system

- Add React 18 with TypeScript support
- Implement responsive header with cart badge
- Add routing for main e-commerce pages
- Configure Material-UI theme with brand colors
- Set up Redux toolkit for state management
- Add search and user profile functionality

Components added:
- Header with navigation and user menu
- App with routing configuration
- Theme provider with custom colors"

# Aggiornamento del design system
cat > frontend/src/styles/theme.js << 'EOF'
import { createTheme } from '@mui/material/styles';

export const lightTheme = createTheme({
  palette: {
    mode: 'light',
    primary: {
      main: '#1976d2',
      light: '#42a5f5',
      dark: '#1565c0',
    },
    secondary: {
      main: '#dc004e',
      light: '#ff5983',
      dark: '#9a0036',
    },
    background: {
      default: '#f5f5f5',
      paper: '#ffffff',
    },
  },
  typography: {
    fontFamily: '"Roboto", "Helvetica", "Arial", sans-serif',
    h1: {
      fontWeight: 300,
      fontSize: '6rem',
    },
    h4: {
      fontWeight: 600,
    },
    subtitle1: {
      fontSize: '1.1rem',
    },
  },
  shape: {
    borderRadius: 8,
  },
  components: {
    MuiButton: {
      styleOverrides: {
        root: {
          textTransform: 'none',
          borderRadius: 8,
          fontWeight: 600,
        },
      },
    },
    MuiCard: {
      styleOverrides: {
        root: {
          boxShadow: '0 4px 6px rgba(0, 0, 0, 0.1)',
          '&:hover': {
            boxShadow: '0 8px 25px rgba(0, 0, 0, 0.15)',
          },
        },
      },
    },
  },
});

export const darkTheme = createTheme({
  palette: {
    mode: 'dark',
    primary: {
      main: '#90caf9',
    },
    secondary: {
      main: '#f48fb1',
    },
    background: {
      default: '#121212',
      paper: '#1e1e1e',
    },
  },
});
EOF

git add .
git commit -m "feat(frontend): enhance design system with light/dark themes

- Create comprehensive theme configuration
- Add custom component overrides for buttons and cards
- Implement hover effects and shadows
- Configure typography scale for better readability
- Add dark theme variant for user preference
- Set up consistent border radius and spacing"
```

#### Team Backend - API Development

```bash
git checkout feature/backend-api-v2

mkdir -p backend/{controllers,models,routes,middleware,config,services}

cat > backend/package.json << 'EOF'
{
  "name": "ecommerce-backend",
  "version": "2.0.0",
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^6.9.0",
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0",
    "cors": "^2.8.5",
    "helmet": "^6.0.0",
    "express-rate-limit": "^6.7.0",
    "joi": "^17.7.0",
    "morgan": "^1.10.0",
    "compression": "^1.7.4"
  },
  "scripts": {
    "start": "node server.js",
    "dev": "nodemon server.js",
    "test": "jest"
  }
}
EOF

cat > backend/server.js << 'EOF'
const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const helmet = require('helmet');
const compression = require('compression');
const rateLimit = require('express-rate-limit');

const authRoutes = require('./routes/auth');
const productRoutes = require('./routes/products');
const orderRoutes = require('./routes/orders');
const userRoutes = require('./routes/users');

const app = express();

// Security middleware
app.use(helmet());
app.use(cors({
  origin: process.env.FRONTEND_URL || 'http://localhost:3000',
  credentials: true
}));

// Rate limiting
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 100 // limit each IP to 100 requests per windowMs
});
app.use('/api/', limiter);

// Body parsing middleware
app.use(express.json({ limit: '10mb' }));
app.use(express.urlencoded({ extended: true }));
app.use(compression());

// Database connection
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/ecommerce', {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

// Routes
app.use('/api/auth', authRoutes);
app.use('/api/products', productRoutes);
app.use('/api/orders', orderRoutes);
app.use('/api/users', userRoutes);

// Health check
app.get('/health', (req, res) => {
  res.status(200).json({
    status: 'healthy',
    timestamp: new Date().toISOString(),
    uptime: process.uptime()
  });
});

// Error handling middleware
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(err.status || 500).json({
    message: err.message || 'Internal Server Error',
    ...(process.env.NODE_ENV === 'development' && { stack: err.stack })
  });
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

module.exports = app;
EOF

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
  verified: {
    type: Boolean,
    default: false
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
    maxlength: 2000
  },
  price: {
    type: Number,
    required: true,
    min: 0
  },
  salePrice: {
    type: Number,
    min: 0
  },
  category: {
    type: String,
    required: true,
    enum: ['electronics', 'clothing', 'books', 'home', 'sports', 'toys']
  },
  tags: [{
    type: String,
    lowercase: true
  }],
  images: [{
    url: String,
    alt: String,
    isPrimary: Boolean
  }],
  inventory: {
    quantity: {
      type: Number,
      required: true,
      min: 0
    },
    reserved: {
      type: Number,
      default: 0,
      min: 0
    },
    lowStockThreshold: {
      type: Number,
      default: 10
    }
  },
  specifications: {
    weight: Number,
    dimensions: {
      length: Number,
      width: Number,
      height: Number
    },
    color: String,
    material: String,
    brand: String
  },
  reviews: [reviewSchema],
  averageRating: {
    type: Number,
    default: 0,
    min: 0,
    max: 5
  },
  totalReviews: {
    type: Number,
    default: 0
  },
  status: {
    type: String,
    enum: ['active', 'inactive', 'discontinued'],
    default: 'active'
  },
  featured: {
    type: Boolean,
    default: false
  },
  seo: {
    title: String,
    description: String,
    keywords: [String]
  }
}, {
  timestamps: true,
  toJSON: { virtuals: true },
  toObject: { virtuals: true }
});

// Virtual for available inventory
productSchema.virtual('availableInventory').get(function() {
  return this.inventory.quantity - this.inventory.reserved;
});

// Virtual for sale percentage
productSchema.virtual('salePercentage').get(function() {
  if (this.salePrice && this.price) {
    return Math.round(((this.price - this.salePrice) / this.price) * 100);
  }
  return 0;
});

// Indexes for performance
productSchema.index({ name: 'text', description: 'text' });
productSchema.index({ category: 1, status: 1 });
productSchema.index({ price: 1 });
productSchema.index({ averageRating: -1 });
productSchema.index({ createdAt: -1 });
productSchema.index({ featured: 1, status: 1 });

// Update average rating when reviews change
productSchema.methods.updateRating = function() {
  const reviews = this.reviews.filter(review => review.rating);
  this.totalReviews = reviews.length;
  
  if (reviews.length > 0) {
    this.averageRating = reviews.reduce((sum, review) => sum + review.rating, 0) / reviews.length;
  } else {
    this.averageRating = 0;
  }
  
  return this.save();
};

module.exports = mongoose.model('Product', productSchema);
EOF

git add .
git commit -m "feat(backend): implement comprehensive product API v2

- Add Express.js server with security middleware
- Implement detailed Product model with reviews and inventory
- Add rate limiting and CORS protection
- Configure MongoDB with optimized indexes
- Add health check endpoint and error handling
- Support for product specifications and SEO

Features:
- Advanced product schema with reviews system
- Inventory management with reservation support
- Search functionality with text indexes
- Performance optimizations with strategic indexing
- Virtual fields for computed properties
- Comprehensive validation and error handling"

# Implementazione del sistema di ordini
cat > backend/models/Order.js << 'EOF'
const mongoose = require('mongoose');

const orderItemSchema = new mongoose.Schema({
  product: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Product',
    required: true
  },
  quantity: {
    type: Number,
    required: true,
    min: 1
  },
  price: {
    type: Number,
    required: true,
    min: 0
  },
  // Snapshot of product details at time of order
  productSnapshot: {
    name: String,
    image: String,
    sku: String
  }
});

const shippingAddressSchema = new mongoose.Schema({
  fullName: { type: String, required: true },
  addressLine1: { type: String, required: true },
  addressLine2: String,
  city: { type: String, required: true },
  state: { type: String, required: true },
  postalCode: { type: String, required: true },
  country: { type: String, required: true, default: 'Italy' },
  phone: String
});

const orderSchema = new mongoose.Schema({
  orderNumber: {
    type: String,
    unique: true,
    required: true
  },
  user: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User',
    required: true
  },
  items: [orderItemSchema],
  totalAmount: {
    type: Number,
    required: true,
    min: 0
  },
  subtotal: {
    type: Number,
    required: true,
    min: 0
  },
  tax: {
    type: Number,
    default: 0,
    min: 0
  },
  shipping: {
    cost: {
      type: Number,
      default: 0,
      min: 0
    },
    method: {
      type: String,
      enum: ['standard', 'express', 'overnight', 'pickup'],
      default: 'standard'
    },
    estimatedDelivery: Date,
    trackingNumber: String
  },
  shippingAddress: shippingAddressSchema,
  billingAddress: shippingAddressSchema,
  paymentInfo: {
    method: {
      type: String,
      enum: ['credit_card', 'paypal', 'bank_transfer', 'cash_on_delivery'],
      required: true
    },
    transactionId: String,
    status: {
      type: String,
      enum: ['pending', 'completed', 'failed', 'refunded'],
      default: 'pending'
    },
    paidAt: Date
  },
  status: {
    type: String,
    enum: ['pending', 'confirmed', 'processing', 'shipped', 'delivered', 'cancelled', 'returned'],
    default: 'pending'
  },
  notes: String,
  statusHistory: [{
    status: String,
    timestamp: { type: Date, default: Date.now },
    note: String,
    updatedBy: {
      type: mongoose.Schema.Types.ObjectId,
      ref: 'User'
    }
  }]
}, {
  timestamps: true,
  toJSON: { virtuals: true },
  toObject: { virtuals: true }
});

// Generate order number
orderSchema.pre('save', async function(next) {
  if (this.isNew && !this.orderNumber) {
    const date = new Date();
    const year = date.getFullYear().toString().slice(-2);
    const month = (date.getMonth() + 1).toString().padStart(2, '0');
    const day = date.getDate().toString().padStart(2, '0');
    
    // Find last order of the day
    const lastOrder = await this.constructor.findOne({
      orderNumber: new RegExp(`^ORD${year}${month}${day}`)
    }).sort({ orderNumber: -1 });
    
    let sequence = 1;
    if (lastOrder) {
      const lastSequence = parseInt(lastOrder.orderNumber.slice(-4));
      sequence = lastSequence + 1;
    }
    
    this.orderNumber = `ORD${year}${month}${day}${sequence.toString().padStart(4, '0')}`;
  }
  next();
});

// Add status change to history
orderSchema.methods.updateStatus = function(newStatus, note, updatedBy) {
  this.status = newStatus;
  this.statusHistory.push({
    status: newStatus,
    note: note,
    updatedBy: updatedBy
  });
  return this.save();
};

// Virtual for total items count
orderSchema.virtual('totalItems').get(function() {
  return this.items.reduce((total, item) => total + item.quantity, 0);
});

// Indexes
orderSchema.index({ user: 1, createdAt: -1 });
orderSchema.index({ orderNumber: 1 });
orderSchema.index({ status: 1 });
orderSchema.index({ 'paymentInfo.status': 1 });
orderSchema.index({ createdAt: -1 });

module.exports = mongoose.model('Order', orderSchema);
EOF

git add .
git commit -m "feat(backend): implement advanced order management system

- Add comprehensive Order model with status tracking
- Implement automatic order number generation
- Add detailed shipping and billing address support
- Create payment processing integration points
- Add order status history with audit trail
- Support multiple payment methods and shipping options

Order Features:
- Automatic order numbering (ORDYYMMDDxxxx format)
- Product snapshot for historical accuracy
- Status workflow management (pending → delivered)
- Payment status tracking with transaction IDs
- Shipping cost calculation and tracking
- Comprehensive audit trail for status changes

Performance optimizations:
- Strategic indexing for common queries
- Virtual fields for computed properties
- Efficient status update methods"
```

#### Team Mobile - React Native App

```bash
git checkout feature/mobile-app

mkdir -p mobile/{src/{components,screens,navigation,services,utils},ios,android}

cat > mobile/package.json << 'EOF'
{
  "name": "ecommerce-mobile",
  "version": "1.0.0",
  "dependencies": {
    "react-native": "^0.71.0",
    "@react-navigation/native": "^6.1.0",
    "@react-navigation/stack": "^6.3.0",
    "@react-navigation/bottom-tabs": "^6.5.0",
    "react-native-vector-icons": "^9.2.0",
    "@reduxjs/toolkit": "^1.9.0",
    "react-redux": "^8.0.0",
    "react-native-async-storage": "^1.17.0",
    "react-native-image-picker": "^5.0.0",
    "react-native-push-notification": "^8.1.0"
  }
}
EOF

cat > mobile/App.js << 'EOF'
import React from 'react';
import { Provider } from 'react-redux';
import { NavigationContainer } from '@react-navigation/native';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import { createStackNavigator } from '@react-navigation/stack';
import Icon from 'react-native-vector-icons/MaterialIcons';

import { store } from './src/store/store';
import HomeScreen from './src/screens/HomeScreen';
import ProductListScreen from './src/screens/ProductListScreen';
import ProductDetailScreen from './src/screens/ProductDetailScreen';
import CartScreen from './src/screens/CartScreen';
import ProfileScreen from './src/screens/ProfileScreen';

const Tab = createBottomTabNavigator();
const Stack = createStackNavigator();

const ProductStack = () => (
  <Stack.Navigator>
    <Stack.Screen name="ProductList" component={ProductListScreen} />
    <Stack.Screen name="ProductDetail" component={ProductDetailScreen} />
  </Stack.Navigator>
);

const MainTabs = () => (
  <Tab.Navigator
    screenOptions={({ route }) => ({
      tabBarIcon: ({ color, size }) => {
        let iconName;
        switch (route.name) {
          case 'Home':
            iconName = 'home';
            break;
          case 'Products':
            iconName = 'shopping-bag';
            break;
          case 'Cart':
            iconName = 'shopping-cart';
            break;
          case 'Profile':
            iconName = 'person';
            break;
          default:
            iconName = 'help';
        }
        return <Icon name={iconName} size={size} color={color} />;
      },
      tabBarActiveTintColor: '#1976d2',
      tabBarInactiveTintColor: 'gray',
    })}
  >
    <Tab.Screen name="Home" component={HomeScreen} />
    <Tab.Screen name="Products" component={ProductStack} />
    <Tab.Screen name="Cart" component={CartScreen} />
    <Tab.Screen name="Profile" component={ProfileScreen} />
  </Tab.Navigator>
);

const App = () => {
  return (
    <Provider store={store}>
      <NavigationContainer>
        <MainTabs />
      </NavigationContainer>
    </Provider>
  );
};

export default App;
EOF

cat > mobile/src/screens/HomeScreen.js << 'EOF'
import React, { useEffect, useState } from 'react';
import {
  View,
  Text,
  ScrollView,
  StyleSheet,
  RefreshControl,
  TouchableOpacity,
  Image
} from 'react-native';
import { useDispatch, useSelector } from 'react-redux';

const HomeScreen = ({ navigation }) => {
  const [refreshing, setRefreshing] = useState(false);
  const dispatch = useDispatch();
  const { featuredProducts, loading } = useSelector(state => state.products);

  const onRefresh = React.useCallback(() => {
    setRefreshing(true);
    // Dispatch action to refresh data
    setTimeout(() => setRefreshing(false), 2000);
  }, []);

  const renderFeaturedProduct = (product) => (
    <TouchableOpacity
      key={product.id}
      style={styles.productCard}
      onPress={() => navigation.navigate('Products', {
        screen: 'ProductDetail',
        params: { productId: product.id }
      })}
    >
      <Image source={{ uri: product.image }} style={styles.productImage} />
      <View style={styles.productInfo}>
        <Text style={styles.productName} numberOfLines={2}>
          {product.name}
        </Text>
        <Text style={styles.productPrice}>€{product.price}</Text>
        {product.salePrice && (
          <Text style={styles.originalPrice}>€{product.originalPrice}</Text>
        )}
      </View>
    </TouchableOpacity>
  );

  return (
    <ScrollView
      style={styles.container}
      refreshControl={
        <RefreshControl refreshing={refreshing} onRefresh={onRefresh} />
      }
    >
      <View style={styles.header}>
        <Text style={styles.welcomeText}>Benvenuto in EcommercePro</Text>
        <Text style={styles.subText}>Trova i migliori prodotti</Text>
      </View>

      <View style={styles.section}>
        <Text style={styles.sectionTitle}>Prodotti in Evidenza</Text>
        <ScrollView horizontal showsHorizontalScrollIndicator={false}>
          {featuredProducts?.map(renderFeaturedProduct)}
        </ScrollView>
      </View>

      <View style={styles.section}>
        <Text style={styles.sectionTitle}>Categorie Popolari</Text>
        <View style={styles.categoryGrid}>
          {['Elettronica', 'Abbigliamento', 'Casa', 'Sport'].map(category => (
            <TouchableOpacity
              key={category}
              style={styles.categoryCard}
              onPress={() => navigation.navigate('Products', { category })}
            >
              <Text style={styles.categoryText}>{category}</Text>
            </TouchableOpacity>
          ))}
        </View>
      </View>
    </ScrollView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#f5f5f5',
  },
  header: {
    padding: 20,
    backgroundColor: '#1976d2',
  },
  welcomeText: {
    fontSize: 24,
    fontWeight: 'bold',
    color: 'white',
    marginBottom: 5,
  },
  subText: {
    fontSize: 16,
    color: '#e3f2fd',
  },
  section: {
    marginVertical: 20,
  },
  sectionTitle: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 15,
    marginHorizontal: 20,
    color: '#333',
  },
  productCard: {
    width: 160,
    marginHorizontal: 10,
    backgroundColor: 'white',
    borderRadius: 8,
    elevation: 3,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
  },
  productImage: {
    width: '100%',
    height: 120,
    borderTopLeftRadius: 8,
    borderTopRightRadius: 8,
  },
  productInfo: {
    padding: 12,
  },
  productName: {
    fontSize: 14,
    fontWeight: '600',
    marginBottom: 5,
    color: '#333',
  },
  productPrice: {
    fontSize: 16,
    fontWeight: 'bold',
    color: '#1976d2',
  },
  originalPrice: {
    fontSize: 12,
    textDecorationLine: 'line-through',
    color: '#888',
  },
  categoryGrid: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    justifyContent: 'space-around',
    paddingHorizontal: 20,
  },
  categoryCard: {
    width: '45%',
    height: 100,
    backgroundColor: 'white',
    borderRadius: 8,
    justifyContent: 'center',
    alignItems: 'center',
    marginBottom: 15,
    elevation: 2,
  },
  categoryText: {
    fontSize: 16,
    fontWeight: '600',
    color: '#333',
  },
});

export default HomeScreen;
EOF

git add .
git commit -m "feat(mobile): implement React Native e-commerce app

- Set up React Native project with navigation structure
- Implement bottom tab navigation with stack navigators
- Add Home screen with featured products and categories
- Configure Redux store for state management
- Add responsive design with proper styling
- Implement pull-to-refresh functionality

Mobile Features:
- Bottom tab navigation (Home, Products, Cart, Profile)
- Featured products horizontal scroll
- Category grid for easy browsing
- Material Design icons integration
- Optimized for both iOS and Android
- Redux integration for state management

UI/UX:
- Material Design color scheme
- Card-based layout for products
- Responsive grid system
- Touch-friendly interface design
- Loading states and refresh controls"
```

#### Team DevOps - Containerization

```bash
git checkout feature/devops-containerization

mkdir -p devops/{docker,kubernetes,scripts,monitoring}

cat > docker-compose.yml << 'EOF'
version: '3.8'

services:
  frontend:
    build:
      context: ./frontend
      dockerfile: Dockerfile
    ports:
      - "3000:3000"
    environment:
      - REACT_APP_API_URL=http://localhost:5000/api
    depends_on:
      - backend
    volumes:
      - ./frontend:/app
      - /app/node_modules
    networks:
      - ecommerce-network

  backend:
    build:
      context: ./backend
      dockerfile: Dockerfile
    ports:
      - "5000:5000"
    environment:
      - NODE_ENV=development
      - MONGODB_URI=mongodb://mongo:27017/ecommerce
      - JWT_SECRET=your-jwt-secret-key
      - REDIS_URL=redis://redis:6379
    depends_on:
      - mongo
      - redis
    volumes:
      - ./backend:/app
      - /app/node_modules
    networks:
      - ecommerce-network

  mongo:
    image: mongo:6.0
    ports:
      - "27017:27017"
    environment:
      - MONGO_INITDB_ROOT_USERNAME=admin
      - MONGO_INITDB_ROOT_PASSWORD=password123
      - MONGO_INITDB_DATABASE=ecommerce
    volumes:
      - mongo_data:/data/db
      - ./devops/docker/mongo-init.js:/docker-entrypoint-initdb.d/mongo-init.js:ro
    networks:
      - ecommerce-network

  redis:
    image: redis:7-alpine
    ports:
      - "6379:6379"
    command: redis-server --appendonly yes
    volumes:
      - redis_data:/data
    networks:
      - ecommerce-network

  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./devops/docker/nginx.conf:/etc/nginx/nginx.conf:ro
      - ./devops/docker/ssl:/etc/nginx/ssl:ro
    depends_on:
      - frontend
      - backend
    networks:
      - ecommerce-network

  prometheus:
    image: prom/prometheus:latest
    ports:
      - "9090:9090"
    volumes:
      - ./devops/monitoring/prometheus.yml:/etc/prometheus/prometheus.yml:ro
      - prometheus_data:/prometheus
    command:
      - '--config.file=/etc/prometheus/prometheus.yml'
      - '--storage.tsdb.path=/prometheus'
      - '--web.console.libraries=/etc/prometheus/console_libraries'
      - '--web.console.templates=/etc/prometheus/consoles'
    networks:
      - ecommerce-network

  grafana:
    image: grafana/grafana:latest
    ports:
      - "3001:3000"
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=admin123
    volumes:
      - grafana_data:/var/lib/grafana
      - ./devops/monitoring/grafana/dashboards:/var/lib/grafana/dashboards
      - ./devops/monitoring/grafana/provisioning:/etc/grafana/provisioning
    depends_on:
      - prometheus
    networks:
      - ecommerce-network

volumes:
  mongo_data:
  redis_data:
  prometheus_data:
  grafana_data:

networks:
  ecommerce-network:
    driver: bridge
EOF

cat > devops/kubernetes/namespace.yaml << 'EOF'
apiVersion: v1
kind: Namespace
metadata:
  name: ecommerce
  labels:
    name: ecommerce
    environment: production
---
apiVersion: v1
kind: ResourceQuota
metadata:
  name: ecommerce-quota
  namespace: ecommerce
spec:
  hard:
    requests.cpu: "4"
    requests.memory: 8Gi
    limits.cpu: "8"
    limits.memory: 16Gi
    persistentvolumeclaims: "10"
    services: "10"
    pods: "20"
EOF

cat > devops/kubernetes/frontend-deployment.yaml << 'EOF'
apiVersion: apps/v1
kind: Deployment
metadata:
  name: frontend
  namespace: ecommerce
  labels:
    app: frontend
    tier: frontend
spec:
  replicas: 3
  selector:
    matchLabels:
      app: frontend
  template:
    metadata:
      labels:
        app: frontend
        tier: frontend
    spec:
      containers:
      - name: frontend
        image: ecommerce/frontend:latest
        ports:
        - containerPort: 3000
        env:
        - name: REACT_APP_API_URL
          value: "https://api.ecommerce.com"
        resources:
          requests:
            memory: "256Mi"
            cpu: "250m"
          limits:
            memory: "512Mi"
            cpu: "500m"
        livenessProbe:
          httpGet:
            path: /
            port: 3000
          initialDelaySeconds: 30
          periodSeconds: 10
        readinessProbe:
          httpGet:
            path: /
            port: 3000
          initialDelaySeconds: 5
          periodSeconds: 5
---
apiVersion: v1
kind: Service
metadata:
  name: frontend-service
  namespace: ecommerce
spec:
  selector:
    app: frontend
  ports:
  - protocol: TCP
    port: 80
    targetPort: 3000
  type: ClusterIP
---
apiVersion: networking.k8s.io/v1
kind: Ingress
metadata:
  name: frontend-ingress
  namespace: ecommerce
  annotations:
    kubernetes.io/ingress.class: "nginx"
    cert-manager.io/cluster-issuer: "letsencrypt-prod"
    nginx.ingress.kubernetes.io/force-ssl-redirect: "true"
spec:
  tls:
  - hosts:
    - ecommerce.com
    - www.ecommerce.com
    secretName: frontend-tls
  rules:
  - host: ecommerce.com
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: frontend-service
            port:
              number: 80
  - host: www.ecommerce.com
    http:
      paths:
      - path: /
        pathType: Prefix
        backend:
          service:
            name: frontend-service
            port:
              number: 80
EOF

cat > devops/scripts/deploy.sh << 'EOF'
#!/bin/bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
DOCKER_REGISTRY="your-registry.com"
IMAGE_TAG=${1:-latest}
ENVIRONMENT=${2:-staging}

echo -e "${YELLOW}Starting deployment process...${NC}"

# Build and push Docker images
echo -e "${YELLOW}Building Docker images...${NC}"

# Frontend
echo "Building frontend image..."
docker build -t ${DOCKER_REGISTRY}/ecommerce-frontend:${IMAGE_TAG} ./frontend
docker push ${DOCKER_REGISTRY}/ecommerce-frontend:${IMAGE_TAG}

# Backend  
echo "Building backend image..."
docker build -t ${DOCKER_REGISTRY}/ecommerce-backend:${IMAGE_TAG} ./backend
docker push ${DOCKER_REGISTRY}/ecommerce-backend:${IMAGE_TAG}

echo -e "${GREEN}Docker images built and pushed successfully${NC}"

# Deploy to Kubernetes
echo -e "${YELLOW}Deploying to Kubernetes (${ENVIRONMENT})...${NC}"

# Apply namespace and base resources
kubectl apply -f devops/kubernetes/namespace.yaml

# Update image tags in deployment files
sed -i "s|image: ecommerce/frontend:.*|image: ${DOCKER_REGISTRY}/ecommerce-frontend:${IMAGE_TAG}|g" devops/kubernetes/frontend-deployment.yaml
sed -i "s|image: ecommerce/backend:.*|image: ${DOCKER_REGISTRY}/ecommerce-backend:${IMAGE_TAG}|g" devops/kubernetes/backend-deployment.yaml

# Apply deployments
kubectl apply -f devops/kubernetes/ -n ecommerce

# Wait for deployments to be ready
echo -e "${YELLOW}Waiting for deployments to be ready...${NC}"
kubectl wait --for=condition=available --timeout=300s deployment/frontend -n ecommerce
kubectl wait --for=condition=available --timeout=300s deployment/backend -n ecommerce

# Run database migrations
echo -e "${YELLOW}Running database migrations...${NC}"
kubectl exec -it deployment/backend -n ecommerce -- npm run migrate

# Health check
echo -e "${YELLOW}Running health checks...${NC}"
FRONTEND_URL=$(kubectl get ingress frontend-ingress -n ecommerce -o jsonpath='{.spec.rules[0].host}')
BACKEND_URL=$(kubectl get ingress backend-ingress -n ecommerce -o jsonpath='{.spec.rules[0].host}')

# Check frontend
if curl -f -s "https://${FRONTEND_URL}" > /dev/null; then
    echo -e "${GREEN}Frontend health check: PASS${NC}"
else
    echo -e "${RED}Frontend health check: FAIL${NC}"
    exit 1
fi

# Check backend
if curl -f -s "https://${BACKEND_URL}/health" > /dev/null; then
    echo -e "${GREEN}Backend health check: PASS${NC}"
else
    echo -e "${RED}Backend health check: FAIL${NC}"
    exit 1
fi

echo -e "${GREEN}Deployment completed successfully!${NC}"
echo -e "${GREEN}Frontend URL: https://${FRONTEND_URL}${NC}"
echo -e "${GREEN}Backend URL: https://${BACKEND_URL}${NC}"

# Show deployment status
echo -e "${YELLOW}Deployment Status:${NC}"
kubectl get pods -n ecommerce -o wide
EOF

chmod +x devops/scripts/deploy.sh

git add .
git commit -m "feat(devops): implement complete containerization and orchestration

Docker Compose Setup:
- Multi-service architecture with frontend, backend, databases
- Nginx reverse proxy with SSL termination
- MongoDB and Redis for data persistence
- Prometheus and Grafana for monitoring
- Volume management for data persistence

Kubernetes Configuration:
- Production-ready deployment manifests
- Resource quotas and limits for cost optimization
- Health checks and readiness probes
- Horizontal Pod Autoscaling configuration
- Ingress with SSL/TLS termination
- Multi-environment support (staging/production)

DevOps Automation:
- Automated deployment script with health checks
- Docker image building and registry push
- Database migration execution
- Comprehensive error handling and logging
- Color-coded output for better visibility

Security Features:
- Network policies for pod communication
- Secret management for sensitive data
- RBAC configuration for service accounts
- Container security scanning integration
- SSL/TLS encryption for all external traffic

Monitoring & Observability:
- Prometheus metrics collection
- Grafana dashboards for visualization
- Application performance monitoring
- Infrastructure health monitoring
- Alerting configuration for critical events"
```

### Visualizzazione Complessa della Storia

Ora utilizziamo strumenti grafici per analizzare questa cronologia complessa:

#### 1. Visualizzazione con Git Log Grafico

```bash
# Torniamo al branch main per vedere tutto
git checkout main

# Visualizzazione completa dell'albero di sviluppo
git log --graph --all --format=format:'%C(bold blue)%h%C(reset) - %C(bold green)(%ar)%C(reset) %C(white)%s%C(reset) %C(dim white)- %an%C(reset)%C(bold yellow)%d%C(reset)' --abbrev-commit

# Output mostra la struttura ramificata del progetto:
# * 3f7a2b1 - (2 hours ago) feat(devops): implement complete containerization... - DevOps Team (HEAD -> feature/devops-containerization)
# | * 8e5c3d9 - (3 hours ago) feat(mobile): implement React Native e-commerce app - Mobile Team (feature/mobile-app)
# |/  
# | * 2a9f1e7 - (4 hours ago) feat(backend): implement advanced order management... - Backend Team (feature/backend-api-v2)
# | * 1c4b8a3 - (5 hours ago) feat(backend): implement comprehensive product API v2 - Backend Team
# |/  
# | * 9d8e2c1 - (6 hours ago) feat(frontend): enhance design system with themes - Frontend Team (feature/frontend-redesign)
# | * 7f5a1b9 - (7 hours ago) feat(frontend): implement new Material-UI design - Frontend Team
# |/  
# * 4a3c7e5 - (8 hours ago) initial: setup multi-team e-commerce project structure - Project Lead (main)
```

#### 2. Utilizzo di Gitk per Analisi Visuale

```bash
# Avviamo gitk per visualizzazione grafica completa
gitk --all &

# Gitk mostra:
# - Grafico a albero con tutte le branch
# - Commit details nel pannello inferiore
# - File changes con diff colorati
# - Ricerca per autore, messaggio, file
```

#### 3. Configurazione di Git GUI Tools

```bash
# Installiamo e configuriamo Git GUI tools
sudo apt-get install git-gui gitk

# Configuriamo Git GUI
git config --global gui.fontui "Ubuntu 11"
git config --global gui.fontdiff "Ubuntu Mono 10"
git config --global gui.editor "code"

# Configuriamo colori per terminale
git config --global color.ui auto
git config --global color.branch.current "yellow reverse"
git config --global color.branch.local "yellow"
git config --global color.branch.remote "green"
git config --global color.diff.meta "yellow bold"
git config --global color.diff.frag "magenta bold"
git config --global color.diff.old "red bold"
git config --global color.diff.new "green bold"

# Avviamo Git GUI
git gui &
```

#### 4. Utilizzo di VS Code Git Extensions

Per VS Code, installiamo estensioni utili:

```bash
# Estensioni raccomandate per visualizzazione Git
code --install-extension eamodio.gitlens
code --install-extension mhutchie.git-graph
code --install-extension donjayamanne.githistory
code --install-extension huizhou.githd

# Configurazione GitLens
cat > .vscode/settings.json << 'EOF'
{
  "gitlens.advanced.messages": {
    "suppressCommitHasNoPreviousCommitWarning": false,
    "suppressCommitNotFoundWarning": false,
    "suppressFileNotUnderSourceControlWarning": false,
    "suppressGitVersionWarning": false,
    "suppressLineUncommittedWarning": false,
    "suppressNoRepositoryWarning": false
  },
  "gitlens.codeLens.enabled": true,
  "gitlens.codeLens.authors.enabled": true,
  "gitlens.codeLens.recentChange.enabled": true,
  "gitlens.currentLine.enabled": true,
  "gitlens.hovers.enabled": true,
  "gitlens.blame.format": "${author}, ${agoOrDate}",
  "gitlens.blame.heatmap.enabled": true,
  "gitlens.views.fileHistory.enabled": true,
  "gitlens.views.lineHistory.enabled": true,
  "gitlens.gitExplorer.enabled": true,
  "git-graph.repository.fetchAndPrune": true,
  "git-graph.repository.showRemoteBranches": true,
  "git-graph.graph.colours": [
    "#0085d1",
    "#d73027", 
    "#f46d43",
    "#fdae61",
    "#fee08b",
    "#e6f598",
    "#abdda4",
    "#66c2a5",
    "#3288bd"
  ]
}
EOF
```

#### 5. Analisi con Strumenti Web-based

```bash
# Setup di GitWeb per visualizzazione web
sudo apt-get install gitweb apache2

# Configurazione GitWeb
sudo cat > /etc/gitweb.conf << 'EOF'
$git_temp = "/tmp";
$projectroot = "/var/git";
$projects_list = "/var/git/projects.list";
$feature{'highlight'}{'default'} = [1];
$feature{'blame'}{'default'} = [1];
$feature{'pickaxe'}{'default'} = [1];
$feature{'search'}{'default'} = [1];
$feature{'grep'}{'default'} = [1];
$feature{'avatar'}{'default'} = ['gravatar'];
EOF

# Creiamo un repository bare per GitWeb
git clone --bare . /var/git/ecommerce-platform.git
echo "ecommerce-platform.git" > /var/git/projects.list

# GitWeb sarà disponibile su http://localhost/gitweb
```

#### 6. Metriche e Statistiche Visuali

```bash
# Statistiche dei commit per autore
git shortlog -sn --all
# Output:
#     15    Frontend Team
#     12    Backend Team
#     8     Mobile Team
#     10    DevOps Team
#     2     Project Lead

# Attività per data con formato grafico
git log --all --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --date=relative

# Analisi dei file più modificati
git log --all --format=format: --name-only | egrep -v '^$' | sort | uniq -c | sort -rg | head -10

# Heatmap delle modifiche
git log --all --format="%ad" --date=short | sort | uniq -c | sort -rn | head -20
```

## Utilizzo Avanzato di Git Graph Extensions

### 1. GitLens Features

- **Code Lens**: Mostra autore e data dell'ultima modifica inline
- **Git Blame**: Visualizzazione completa della cronologia del file
- **Hover Information**: Dettagli del commit al passaggio del mouse
- **File History**: Cronologia completa delle modifiche al file
- **Interactive Rebase**: Riorganizzazione visuale dei commit

### 2. Git Graph Extension

- **Branch Visualization**: Grafico interattivo di tutte le branch
- **Commit Details**: Pannello dettagliato per ogni commit
- **File Changes**: Visualizzazione delle modifiche per commit
- **Branch Operations**: Merge, rebase, cherry-pick con interface grafica

### 3. Workflows Visuali Raccomandati

```bash
# Workflow per code review visuale
git log --graph --oneline feature/frontend-redesign..main
git difftool --dir-diff feature/frontend-redesign main

# Analisi impact delle feature
git log --graph --stat --since="1 week ago" --all

# Tracking delle performance changes
git log --grep="performance" --grep="optimization" --all --oneline
```

## Conclusioni sulla Visualizzazione

Questo esempio dimostra l'importanza di utilizzare strumenti grafici per:

1. **Comprendere la Complessità**: Progetti multi-team richiedono visualizzazione chiara
2. **Identificare Pattern**: Trends di sviluppo e aree di conflitto
3. **Facilitare Collaboration**: Team diversi possono capire il lavoro degli altri
4. **Debugging Visuale**: Identificare rapidamente quando e dove sono stati introdotti problemi
5. **Project Management**: Monitoraggio del progresso e pianificazione

La combinazione di strumenti da terminale, GUI desktop e estensioni IDE fornisce una vista completa e flessibile della cronologia del progetto, essenziale per progetti complessi con team distribuiti.

---

**Navigazione:**
- [← Esempio Precedente: Analisi delle Modifiche](03-analisi-modifiche.md)
- [→ Prossimo: Esercizi Pratici](../esercizi/01-esplorazione-repository.md)
- [↑ Torna all'Indice del Modulo](../README.md)
