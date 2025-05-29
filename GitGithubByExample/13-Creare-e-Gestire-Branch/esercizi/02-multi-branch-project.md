# Esercizio 2: Multi-Branch Project - E-commerce Dashboard

## 📋 Descrizione
Sviluppare un dashboard e-commerce completo utilizzando una strategia avanzata di branching con più team che lavorano contemporaneamente su frontend, backend, database e DevOps. Sperimenterai workflow di collaborazione reali con branch paralleli e integrazione continua.

## 🎯 Obiettivi di Apprendimento
- Gestire branch paralleli con team multipli
- Coordinare sviluppo frontend/backend simultaneo
- Implementare strategie di merge complesse
- Praticare risoluzione conflitti in progetti grandi
- Utilizzare branch per hotfix e release

## ⏱️ Durata Stimata
90-120 minuti

## 🏗️ Architettura del Progetto

### Team Structure
- **Frontend Team**: React dashboard, componenti UI
- **Backend Team**: API REST, microservizi
- **Database Team**: Schema, migrations, seeds
- **DevOps Team**: Docker, CI/CD, monitoring

### Branch Strategy
```
main
├── develop
├── release/v1.0
├── hotfix/critical-fix
├── feature/frontend-dashboard
├── feature/backend-api
├── feature/database-schema
└── feature/devops-setup
```

## 🚀 Setup Progetto Multi-Team

### 1. Struttura Iniziale
```bash
# Creazione progetto principale
mkdir ecommerce-dashboard
cd ecommerce-dashboard
git init

# Configurazione
git config user.name "Project Lead"
git config user.email "lead@ecommerce.com"

# Struttura directory
mkdir -p {
    frontend/{src/{components,pages,services,utils},public,tests},
    backend/{src/{controllers,models,routes,middleware},tests},
    database/{migrations,seeds,schemas},
    devops/{docker,scripts,configs},
    docs
}
```

### 2. File di Configurazione Base

**package.json** (root):
```json
{
  "name": "ecommerce-dashboard",
  "version": "1.0.0",
  "description": "Multi-team e-commerce dashboard",
  "workspaces": [
    "frontend",
    "backend"
  ],
  "scripts": {
    "install:all": "npm install && npm run install:frontend && npm run install:backend",
    "install:frontend": "cd frontend && npm install",
    "install:backend": "cd backend && npm install",
    "dev": "concurrently \"npm run dev:backend\" \"npm run dev:frontend\"",
    "dev:frontend": "cd frontend && npm start",
    "dev:backend": "cd backend && npm run dev",
    "build": "npm run build:frontend && npm run build:backend",
    "test": "npm run test:frontend && npm run test:backend"
  },
  "devDependencies": {
    "concurrently": "^7.6.0"
  }
}
```

**README.md**:
```markdown
# E-commerce Dashboard

Multi-team project for comprehensive e-commerce management dashboard.

## Teams & Responsibilities

### 🎨 Frontend Team
- React-based dashboard
- Component library
- User experience

### ⚙️ Backend Team  
- REST API development
- Business logic
- Authentication

### 💾 Database Team
- Schema design
- Data migrations
- Performance optimization

### 🐳 DevOps Team
- Containerization
- CI/CD pipelines
- Infrastructure

## Quick Start

```bash
git clone <repository>
npm run install:all
npm run dev
```

## Branch Strategy
- `main`: Production ready code
- `develop`: Integration branch
- `feature/*`: Feature development
- `release/*`: Release preparation
- `hotfix/*`: Critical fixes
```

### 3. Commit Iniziale e Develop Branch
```bash
git add .
git commit -m "feat: initial multi-team project structure"

# Crea develop branch
git checkout -b develop
git push -u origin develop
```

## 🎨 Frontend Team Development

### Esercizio 2.1: Frontend Dashboard (25 minuti)

#### Setup Frontend Team
```bash
# Branch frontend
git checkout develop
git checkout -b feature/frontend-dashboard

# Frontend package.json
cat > frontend/package.json << 'EOF'
{
  "name": "ecommerce-frontend",
  "version": "1.0.0",
  "private": true,
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-router-dom": "^6.8.0",
    "axios": "^1.3.0",
    "recharts": "^2.5.0",
    "@mui/material": "^5.11.0",
    "@emotion/react": "^11.10.0",
    "@emotion/styled": "^11.10.0"
  },
  "scripts": {
    "start": "react-scripts start",
    "build": "react-scripts build",
    "test": "react-scripts test"
  },
  "devDependencies": {
    "react-scripts": "5.0.1"
  }
}
EOF
```

#### Dashboard Components

**frontend/src/components/Dashboard.js**:
```javascript
import React, { useState, useEffect } from 'react';
import { Grid, Paper, Typography, Box } from '@mui/material';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from 'recharts';

const Dashboard = () => {
  const [stats, setStats] = useState({
    totalOrders: 0,
    totalRevenue: 0,
    totalUsers: 0,
    conversionRate: 0
  });

  const [chartData, setChartData] = useState([]);

  useEffect(() => {
    // Simulazione chiamata API
    fetchDashboardData();
  }, []);

  const fetchDashboardData = async () => {
    try {
      // Dati mock per development
      const mockStats = {
        totalOrders: 1247,
        totalRevenue: 89532.45,
        totalUsers: 3421,
        conversionRate: 3.2
      };

      const mockChartData = [
        { name: 'Gen', orders: 400, revenue: 24000 },
        { name: 'Feb', orders: 300, revenue: 13980 },
        { name: 'Mar', orders: 520, revenue: 31200 },
        { name: 'Apr', orders: 278, revenue: 16680 },
        { name: 'Mag', orders: 189, revenue: 11340 },
        { name: 'Giu', orders: 239, revenue: 14340 }
      ];

      setStats(mockStats);
      setChartData(mockChartData);
    } catch (error) {
      console.error('Error fetching dashboard data:', error);
    }
  };

  return (
    <Box sx={{ flexGrow: 1, p: 3 }}>
      <Typography variant="h4" gutterBottom>
        E-commerce Dashboard
      </Typography>
      
      <Grid container spacing={3}>
        {/* Stats Cards */}
        <Grid item xs={12} sm={6} md={3}>
          <Paper sx={{ p: 2, textAlign: 'center' }}>
            <Typography variant="h6" color="primary">
              Ordini Totali
            </Typography>
            <Typography variant="h4">
              {stats.totalOrders.toLocaleString()}
            </Typography>
          </Paper>
        </Grid>
        
        <Grid item xs={12} sm={6} md={3}>
          <Paper sx={{ p: 2, textAlign: 'center' }}>
            <Typography variant="h6" color="primary">
              Fatturato
            </Typography>
            <Typography variant="h4">
              €{stats.totalRevenue.toLocaleString()}
            </Typography>
          </Paper>
        </Grid>
        
        <Grid item xs={12} sm={6} md={3}>
          <Paper sx={{ p: 2, textAlign: 'center' }}>
            <Typography variant="h6" color="primary">
              Utenti Registrati
            </Typography>
            <Typography variant="h4">
              {stats.totalUsers.toLocaleString()}
            </Typography>
          </Paper>
        </Grid>
        
        <Grid item xs={12} sm={6} md={3}>
          <Paper sx={{ p: 2, textAlign: 'center' }}>
            <Typography variant="h6" color="primary">
              Tasso Conversione
            </Typography>
            <Typography variant="h4">
              {stats.conversionRate}%
            </Typography>
          </Paper>
        </Grid>

        {/* Chart */}
        <Grid item xs={12}>
          <Paper sx={{ p: 2 }}>
            <Typography variant="h6" gutterBottom>
              Andamento Vendite
            </Typography>
            <ResponsiveContainer width="100%" height={300}>
              <LineChart data={chartData}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="name" />
                <YAxis />
                <Tooltip />
                <Line type="monotone" dataKey="orders" stroke="#8884d8" />
                <Line type="monotone" dataKey="revenue" stroke="#82ca9d" />
              </LineChart>
            </ResponsiveContainer>
          </Paper>
        </Grid>
      </Grid>
    </Box>
  );
};

export default Dashboard;
```

**frontend/src/components/ProductList.js**:
```javascript
import React, { useState, useEffect } from 'react';
import {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableHead,
  TableRow,
  Paper,
  Chip,
  Button,
  Box,
  Typography
} from '@mui/material';

const ProductList = () => {
  const [products, setProducts] = useState([]);

  useEffect(() => {
    fetchProducts();
  }, []);

  const fetchProducts = async () => {
    // Mock data
    const mockProducts = [
      {
        id: 1,
        name: 'Smartphone Pro',
        category: 'Electronics',
        price: 899.99,
        stock: 45,
        status: 'active'
      },
      {
        id: 2,
        name: 'Laptop Gaming',
        category: 'Electronics',
        price: 1299.99,
        stock: 12,
        status: 'active'
      },
      {
        id: 3,
        name: 'Wireless Headphones',
        category: 'Audio',
        price: 199.99,
        stock: 0,
        status: 'out_of_stock'
      }
    ];

    setProducts(mockProducts);
  };

  const getStatusColor = (status) => {
    switch (status) {
      case 'active': return 'success';
      case 'out_of_stock': return 'error';
      default: return 'default';
    }
  };

  return (
    <Box sx={{ p: 3 }}>
      <Typography variant="h4" gutterBottom>
        Gestione Prodotti
      </Typography>
      
      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>ID</TableCell>
              <TableCell>Nome Prodotto</TableCell>
              <TableCell>Categoria</TableCell>
              <TableCell>Prezzo</TableCell>
              <TableCell>Stock</TableCell>
              <TableCell>Status</TableCell>
              <TableCell>Azioni</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {products.map((product) => (
              <TableRow key={product.id}>
                <TableCell>{product.id}</TableCell>
                <TableCell>{product.name}</TableCell>
                <TableCell>{product.category}</TableCell>
                <TableCell>€{product.price}</TableCell>
                <TableCell>{product.stock}</TableCell>
                <TableCell>
                  <Chip 
                    label={product.status}
                    color={getStatusColor(product.status)}
                    size="small"
                  />
                </TableCell>
                <TableCell>
                  <Button size="small" variant="outlined">
                    Modifica
                  </Button>
                </TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Box>
  );
};

export default ProductList;
```

**frontend/src/App.js**:
```javascript
import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import { ThemeProvider, createTheme } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';
import Dashboard from './components/Dashboard';
import ProductList from './components/ProductList';

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
        <Routes>
          <Route path="/" element={<Navigate to="/dashboard" />} />
          <Route path="/dashboard" element={<Dashboard />} />
          <Route path="/products" element={<ProductList />} />
        </Routes>
      </Router>
    </ThemeProvider>
  );
}

export default App;
```

#### Commit Frontend
```bash
git add .
git commit -m "feat(frontend): implement dashboard and product list components"
```

## ⚙️ Backend Team Development

### Esercizio 2.2: Backend API (25 minuti)

```bash
# Nuovo branch backend (da develop)
git checkout develop
git checkout -b feature/backend-api
```

#### Backend Setup

**backend/package.json**:
```json
{
  "name": "ecommerce-backend",
  "version": "1.0.0",
  "main": "src/server.js",
  "scripts": {
    "start": "node src/server.js",
    "dev": "nodemon src/server.js",
    "test": "jest"
  },
  "dependencies": {
    "express": "^4.18.0",
    "mongoose": "^7.0.0",
    "cors": "^2.8.5",
    "helmet": "^6.0.0",
    "dotenv": "^16.0.0",
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0"
  },
  "devDependencies": {
    "nodemon": "^2.0.0",
    "jest": "^29.0.0"
  }
}
```

#### API Implementation

**backend/src/server.js**:
```javascript
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 5000;

// Middleware
app.use(helmet());
app.use(cors());
app.use(express.json());

// Routes
app.use('/api/dashboard', require('./routes/dashboard'));
app.use('/api/products', require('./routes/products'));
app.use('/api/orders', require('./routes/orders'));

// Health check
app.get('/health', (req, res) => {
  res.json({ 
    status: 'OK', 
    timestamp: new Date().toISOString(),
    version: '1.0.0'
  });
});

// Error handler
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).json({ error: 'Something went wrong!' });
});

app.listen(PORT, () => {
  console.log(`Backend server running on port ${PORT}`);
});

module.exports = app;
```

**backend/src/routes/dashboard.js**:
```javascript
const express = require('express');
const router = express.Router();

// GET /api/dashboard/stats
router.get('/stats', async (req, res) => {
  try {
    // Simulazione query database
    const stats = {
      totalOrders: Math.floor(Math.random() * 2000) + 1000,
      totalRevenue: Math.floor(Math.random() * 100000) + 50000,
      totalUsers: Math.floor(Math.random() * 5000) + 2000,
      conversionRate: (Math.random() * 5 + 1).toFixed(1)
    };

    res.json(stats);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// GET /api/dashboard/chart-data
router.get('/chart-data', async (req, res) => {
  try {
    const chartData = [];
    const months = ['Gen', 'Feb', 'Mar', 'Apr', 'Mag', 'Giu'];
    
    months.forEach(month => {
      chartData.push({
        name: month,
        orders: Math.floor(Math.random() * 500) + 100,
        revenue: Math.floor(Math.random() * 30000) + 10000
      });
    });

    res.json(chartData);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

module.exports = router;
```

**backend/src/routes/products.js**:
```javascript
const express = require('express');
const router = express.Router();

// Mock database
let products = [
  {
    id: 1,
    name: 'Smartphone Pro',
    description: 'Latest smartphone with advanced features',
    category: 'Electronics',
    price: 899.99,
    stock: 45,
    status: 'active',
    createdAt: new Date('2024-01-01')
  },
  {
    id: 2,
    name: 'Laptop Gaming',
    description: 'High-performance gaming laptop',
    category: 'Electronics',
    price: 1299.99,
    stock: 12,
    status: 'active',
    createdAt: new Date('2024-01-02')
  },
  {
    id: 3,
    name: 'Wireless Headphones',
    description: 'Premium wireless headphones',
    category: 'Audio',
    price: 199.99,
    stock: 0,
    status: 'out_of_stock',
    createdAt: new Date('2024-01-03')
  }
];

// GET /api/products
router.get('/', (req, res) => {
  const { category, status, page = 1, limit = 10 } = req.query;
  
  let filteredProducts = [...products];
  
  if (category) {
    filteredProducts = filteredProducts.filter(p => p.category === category);
  }
  
  if (status) {
    filteredProducts = filteredProducts.filter(p => p.status === status);
  }
  
  const startIndex = (page - 1) * limit;
  const endIndex = startIndex + parseInt(limit);
  const paginatedProducts = filteredProducts.slice(startIndex, endIndex);
  
  res.json({
    products: paginatedProducts,
    pagination: {
      currentPage: parseInt(page),
      totalPages: Math.ceil(filteredProducts.length / limit),
      totalItems: filteredProducts.length
    }
  });
});

// POST /api/products
router.post('/', (req, res) => {
  const newProduct = {
    id: products.length + 1,
    ...req.body,
    createdAt: new Date()
  };
  
  products.push(newProduct);
  res.status(201).json(newProduct);
});

// PUT /api/products/:id
router.put('/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const productIndex = products.findIndex(p => p.id === id);
  
  if (productIndex === -1) {
    return res.status(404).json({ error: 'Product not found' });
  }
  
  products[productIndex] = {
    ...products[productIndex],
    ...req.body,
    updatedAt: new Date()
  };
  
  res.json(products[productIndex]);
});

// DELETE /api/products/:id
router.delete('/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const productIndex = products.findIndex(p => p.id === id);
  
  if (productIndex === -1) {
    return res.status(404).json({ error: 'Product not found' });
  }
  
  products.splice(productIndex, 1);
  res.status(204).send();
});

module.exports = router;
```

**backend/src/routes/orders.js**:
```javascript
const express = require('express');
const router = express.Router();

// Mock orders data
const orders = [
  {
    id: 1,
    userId: 101,
    products: [
      { productId: 1, quantity: 2, price: 899.99 },
      { productId: 3, quantity: 1, price: 199.99 }
    ],
    total: 1999.97,
    status: 'completed',
    createdAt: new Date('2024-01-15')
  },
  {
    id: 2,
    userId: 102,
    products: [
      { productId: 2, quantity: 1, price: 1299.99 }
    ],
    total: 1299.99,
    status: 'processing',
    createdAt: new Date('2024-01-16')
  }
];

// GET /api/orders
router.get('/', (req, res) => {
  const { status, userId, page = 1, limit = 10 } = req.query;
  
  let filteredOrders = [...orders];
  
  if (status) {
    filteredOrders = filteredOrders.filter(o => o.status === status);
  }
  
  if (userId) {
    filteredOrders = filteredOrders.filter(o => o.userId === parseInt(userId));
  }
  
  res.json({
    orders: filteredOrders,
    pagination: {
      currentPage: parseInt(page),
      totalPages: Math.ceil(filteredOrders.length / limit),
      totalItems: filteredOrders.length
    }
  });
});

module.exports = router;
```

#### Commit Backend
```bash
git add .
git commit -m "feat(backend): implement REST API for dashboard, products and orders"
```

## 💾 Database Team Development

### Esercizio 2.3: Database Schema (20 minuti)

```bash
# Database branch
git checkout develop
git checkout -b feature/database-schema
```

#### Database Schema e Migrations

**database/schemas/products.sql**:
```sql
-- Product Schema
CREATE TABLE products (
    id BIGSERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    category VARCHAR(100) NOT NULL,
    price DECIMAL(10,2) NOT NULL CHECK (price >= 0),
    stock INTEGER NOT NULL DEFAULT 0 CHECK (stock >= 0),
    status VARCHAR(20) NOT NULL DEFAULT 'active' 
        CHECK (status IN ('active', 'inactive', 'out_of_stock')),
    image_url VARCHAR(512),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Indexes
CREATE INDEX idx_products_category ON products(category);
CREATE INDEX idx_products_status ON products(status);
CREATE INDEX idx_products_created_at ON products(created_at);

-- Full-text search
CREATE INDEX idx_products_search ON products 
    USING GIN(to_tsvector('english', name || ' ' || description));
```

**database/schemas/users.sql**:
```sql
-- Users Schema
CREATE TABLE users (
    id BIGSERIAL PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password_hash VARCHAR(255) NOT NULL,
    first_name VARCHAR(100),
    last_name VARCHAR(100),
    phone VARCHAR(20),
    is_active BOOLEAN DEFAULT true,
    is_admin BOOLEAN DEFAULT false,
    last_login TIMESTAMP,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Indexes
CREATE INDEX idx_users_email ON users(email);
CREATE INDEX idx_users_username ON users(username);
CREATE INDEX idx_users_active ON users(is_active);
```

**database/schemas/orders.sql**:
```sql
-- Orders Schema
CREATE TABLE orders (
    id BIGSERIAL PRIMARY KEY,
    user_id BIGINT NOT NULL REFERENCES users(id),
    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount >= 0),
    status VARCHAR(20) NOT NULL DEFAULT 'pending'
        CHECK (status IN ('pending', 'processing', 'shipped', 'delivered', 'cancelled')),
    shipping_address TEXT NOT NULL,
    billing_address TEXT,
    payment_method VARCHAR(50),
    payment_status VARCHAR(20) DEFAULT 'pending'
        CHECK (payment_status IN ('pending', 'completed', 'failed', 'refunded')),
    notes TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Order Items
CREATE TABLE order_items (
    id BIGSERIAL PRIMARY KEY,
    order_id BIGINT NOT NULL REFERENCES orders(id) ON DELETE CASCADE,
    product_id BIGINT NOT NULL REFERENCES products(id),
    quantity INTEGER NOT NULL CHECK (quantity > 0),
    unit_price DECIMAL(10,2) NOT NULL CHECK (unit_price >= 0),
    total_price DECIMAL(10,2) NOT NULL CHECK (total_price >= 0),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Indexes
CREATE INDEX idx_orders_user_id ON orders(user_id);
CREATE INDEX idx_orders_status ON orders(status);
CREATE INDEX idx_orders_created_at ON orders(created_at);
CREATE INDEX idx_order_items_order_id ON order_items(order_id);
CREATE INDEX idx_order_items_product_id ON order_items(product_id);
```

#### Database Migrations

**database/migrations/001_initial_schema.sql**:
```sql
-- Migration: Initial Schema Setup
-- Date: 2024-01-01
-- Description: Create initial database structure

BEGIN;

-- Create products table
\i schemas/products.sql

-- Create users table  
\i schemas/users.sql

-- Create orders tables
\i schemas/orders.sql

-- Create audit trigger function
CREATE OR REPLACE FUNCTION update_updated_at_column()
RETURNS TRIGGER AS $$
BEGIN
    NEW.updated_at = CURRENT_TIMESTAMP;
    RETURN NEW;
END;
$$ language 'plpgsql';

-- Add triggers for updated_at
CREATE TRIGGER update_products_updated_at 
    BEFORE UPDATE ON products 
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_users_updated_at 
    BEFORE UPDATE ON users 
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

CREATE TRIGGER update_orders_updated_at 
    BEFORE UPDATE ON orders 
    FOR EACH ROW EXECUTE FUNCTION update_updated_at_column();

COMMIT;
```

#### Seed Data

**database/seeds/sample_data.sql**:
```sql
-- Sample Data for Development
BEGIN;

-- Insert sample users
INSERT INTO users (username, email, password_hash, first_name, last_name, is_admin) VALUES
('admin', 'admin@ecommerce.com', '$2b$12$hash_here', 'Admin', 'User', true),
('john_doe', 'john@example.com', '$2b$12$hash_here', 'John', 'Doe', false),
('jane_smith', 'jane@example.com', '$2b$12$hash_here', 'Jane', 'Smith', false);

-- Insert sample products
INSERT INTO products (name, description, category, price, stock, image_url) VALUES
('Smartphone Pro', 'Latest smartphone with advanced features', 'Electronics', 899.99, 45, '/images/smartphone-pro.jpg'),
('Laptop Gaming', 'High-performance gaming laptop', 'Electronics', 1299.99, 12, '/images/laptop-gaming.jpg'),
('Wireless Headphones', 'Premium wireless headphones', 'Audio', 199.99, 0, '/images/headphones.jpg'),
('Smart Watch', 'Fitness tracking smartwatch', 'Wearables', 299.99, 25, '/images/smartwatch.jpg'),
('Tablet Pro', 'Professional tablet for creative work', 'Electronics', 699.99, 18, '/images/tablet-pro.jpg');

-- Insert sample orders
INSERT INTO orders (user_id, total_amount, status, shipping_address, payment_method, payment_status) VALUES
(2, 1999.97, 'completed', '123 Main St, City, State 12345', 'credit_card', 'completed'),
(3, 1299.99, 'processing', '456 Oak Ave, Town, State 67890', 'paypal', 'completed');

-- Insert order items
INSERT INTO order_items (order_id, product_id, quantity, unit_price, total_price) VALUES
(1, 1, 2, 899.99, 1799.98),
(1, 3, 1, 199.99, 199.99),
(2, 2, 1, 1299.99, 1299.99);

COMMIT;
```

#### Database Management Scripts

**database/scripts/migrate.js**:
```javascript
const fs = require('fs');
const path = require('path');
const { Pool } = require('pg');

const pool = new Pool({
  host: process.env.DB_HOST || 'localhost',
  port: process.env.DB_PORT || 5432,
  database: process.env.DB_NAME || 'ecommerce',
  user: process.env.DB_USER || 'postgres',
  password: process.env.DB_PASSWORD || 'password'
});

async function runMigrations() {
  try {
    console.log('🔄 Running database migrations...');
    
    const migrationsDir = path.join(__dirname, '../migrations');
    const files = fs.readdirSync(migrationsDir).sort();
    
    for (const file of files) {
      if (file.endsWith('.sql')) {
        console.log(`📄 Running migration: ${file}`);
        const sql = fs.readFileSync(path.join(migrationsDir, file), 'utf8');
        await pool.query(sql);
        console.log(`✅ Migration ${file} completed`);
      }
    }
    
    console.log('🎉 All migrations completed successfully');
  } catch (error) {
    console.error('❌ Migration failed:', error);
    process.exit(1);
  } finally {
    await pool.end();
  }
}

if (require.main === module) {
  runMigrations();
}

module.exports = { runMigrations };
```

#### Commit Database
```bash
git add .
git commit -m "feat(database): implement complete database schema with migrations and seeds"
```

## 🐳 DevOps Team Development

### Esercizio 2.4: DevOps Setup (20 minuti)

```bash
# DevOps branch
git checkout develop  
git checkout -b feature/devops-setup
```

#### Docker Configuration

**devops/docker/Dockerfile.frontend**:
```dockerfile
# Multi-stage build for React frontend
FROM node:18-alpine AS builder

WORKDIR /app
COPY frontend/package*.json ./
RUN npm ci --only=production

COPY frontend/ ./
RUN npm run build

# Production stage
FROM nginx:alpine
COPY --from=builder /app/build /usr/share/nginx/html
COPY devops/configs/nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]
```

**devops/docker/Dockerfile.backend**:
```dockerfile
FROM node:18-alpine

# Create app directory
WORKDIR /app

# Create non-root user
RUN addgroup -g 1001 -S nodejs && \
    adduser -S nodeuser -u 1001

# Copy package files
COPY backend/package*.json ./
RUN npm ci --only=production && npm cache clean --force

# Copy source code
COPY backend/ ./

# Set ownership
RUN chown -R nodeuser:nodejs /app
USER nodeuser

EXPOSE 5000

HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
  CMD node healthcheck.js

CMD ["npm", "start"]
```

#### Docker Compose

**docker-compose.yml**:
```yaml
version: '3.8'

services:
  # Frontend Service
  frontend:
    build:
      context: .
      dockerfile: devops/docker/Dockerfile.frontend
    ports:
      - "3000:80"
    environment:
      - REACT_APP_API_URL=http://localhost:5000/api
    depends_on:
      - backend
    networks:
      - ecommerce-network
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost"]
      interval: 30s
      timeout: 10s
      retries: 3

  # Backend Service
  backend:
    build:
      context: .
      dockerfile: devops/docker/Dockerfile.backend
    ports:
      - "5000:5000"
    environment:
      - NODE_ENV=production
      - DB_HOST=postgres
      - DB_PORT=5432
      - DB_NAME=ecommerce
      - DB_USER=postgres
      - DB_PASSWORD=password
      - JWT_SECRET=your-super-secret-jwt-key
    depends_on:
      postgres:
        condition: service_healthy
      redis:
        condition: service_healthy
    networks:
      - ecommerce-network
    volumes:
      - ./logs:/app/logs

  # PostgreSQL Database
  postgres:
    image: postgres:15-alpine
    environment:
      - POSTGRES_DB=ecommerce
      - POSTGRES_USER=postgres
      - POSTGRES_PASSWORD=password
    volumes:
      - postgres_data:/var/lib/postgresql/data
      - ./database/migrations:/docker-entrypoint-initdb.d
    networks:
      - ecommerce-network
    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U postgres"]
      interval: 30s
      timeout: 10s
      retries: 5

  # Redis Cache
  redis:
    image: redis:7-alpine
    command: redis-server --appendonly yes
    volumes:
      - redis_data:/data
    networks:
      - ecommerce-network
    healthcheck:
      test: ["CMD", "redis-cli", "ping"]
      interval: 30s
      timeout: 10s
      retries: 3

  # Nginx Load Balancer
  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./devops/configs/nginx-lb.conf:/etc/nginx/nginx.conf
      - ./devops/ssl:/etc/ssl
    depends_on:
      - frontend
      - backend
    networks:
      - ecommerce-network

volumes:
  postgres_data:
  redis_data:

networks:
  ecommerce-network:
    driver: bridge
```

#### CI/CD Pipeline

**devops/scripts/deploy.sh**:
```bash
#!/bin/bash

# E-commerce Dashboard Deployment Script
set -e

echo "🚀 Starting deployment process..."

# Configuration
PROJECT_NAME="ecommerce-dashboard"
BACKUP_DIR="/backups/$(date +%Y%m%d_%H%M%S)"
LOG_FILE="/var/log/deploy.log"

# Functions
log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a $LOG_FILE
}

cleanup() {
    log "🧹 Cleaning up temporary files..."
    docker system prune -f
}

# Pre-deployment checks
log "🔍 Running pre-deployment checks..."

# Check if Docker is running
if ! docker info > /dev/null 2>&1; then
    log "❌ Docker is not running"
    exit 1
fi

# Check available disk space
AVAILABLE=$(df / | tail -1 | awk '{print $4}')
if [ $AVAILABLE -lt 1000000 ]; then
    log "⚠️ Low disk space: ${AVAILABLE}KB available"
fi

# Database backup
log "💾 Creating database backup..."
mkdir -p $BACKUP_DIR
docker-compose exec -T postgres pg_dump -U postgres ecommerce > $BACKUP_DIR/database.sql

# Stop current services
log "🛑 Stopping current services..."
docker-compose down

# Pull latest images
log "📥 Pulling latest images..."
docker-compose pull

# Build and start services
log "🔨 Building and starting services..."
docker-compose up -d --build

# Health checks
log "🏥 Running health checks..."
sleep 30

# Check frontend
if curl -f http://localhost:3000 > /dev/null 2>&1; then
    log "✅ Frontend is healthy"
else
    log "❌ Frontend health check failed"
    exit 1
fi

# Check backend
if curl -f http://localhost:5000/health > /dev/null 2>&1; then
    log "✅ Backend is healthy"
else
    log "❌ Backend health check failed"
    exit 1
fi

# Run database migrations
log "🔄 Running database migrations..."
docker-compose exec backend npm run migrate

# Final cleanup
cleanup

log "🎉 Deployment completed successfully!"
log "📊 Access dashboard at: http://localhost:3000"
log "🔧 API available at: http://localhost:5000"

# Send notification (optional)
if command -v mail &> /dev/null; then
    echo "Deployment completed successfully at $(date)" | mail -s "Deployment Success" admin@ecommerce.com
fi
```

#### Monitoring Configuration

**devops/configs/prometheus.yml**:
```yaml
global:
  scrape_interval: 15s
  evaluation_interval: 15s

rule_files:
  - "alert_rules.yml"

scrape_configs:
  - job_name: 'ecommerce-frontend'
    static_configs:
      - targets: ['frontend:80']
    metrics_path: '/metrics'
    scrape_interval: 30s

  - job_name: 'ecommerce-backend'
    static_configs:
      - targets: ['backend:5000']
    metrics_path: '/api/metrics'
    scrape_interval: 15s

  - job_name: 'postgres'
    static_configs:
      - targets: ['postgres:5432']

  - job_name: 'redis'
    static_configs:
      - targets: ['redis:6379']

alerting:
  alertmanagers:
    - static_configs:
        - targets:
          - alertmanager:9093
```

#### Commit DevOps
```bash
git add .
git commit -m "feat(devops): implement Docker configuration, CI/CD pipeline and monitoring"
```

## 🔄 Integration e Conflict Resolution

### Esercizio 2.5: Merge Complesso e Hotfix (20 minuti)

#### 1. Merge Feature Branches in Develop
```bash
# Torna a develop
git checkout develop

# Merge frontend (primo - dovrebbe essere semplice)
git merge feature/frontend-dashboard
log "✅ Frontend merged successfully"

# Merge backend (potrebbe avere conflitti in package.json root)
git merge feature/backend-api
# Se ci sono conflitti, risolvi e continua

# Merge database
git merge feature/database-schema

# Merge devops (possibili conflitti in docker-compose.yml)
git merge feature/devops-setup
```

#### 2. Simulazione Hotfix Critico
```bash
# Hotfix branch dal main (non da develop!)
git checkout main
git checkout -b hotfix/security-vulnerability

# Fix di sicurezza critico
cat > backend/src/middleware/security.js << 'EOF'
const rateLimit = require('express-rate-limit');
const helmet = require('helmet');

// Rate limiting
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 100, // limit each IP to 100 requests per windowMs
  message: 'Too many requests from this IP'
});

// Security headers
const securityHeaders = helmet({
  contentSecurityPolicy: {
    directives: {
      defaultSrc: ["'self'"],
      styleSrc: ["'self'", "'unsafe-inline'"],
      scriptSrc: ["'self'"],
      imgSrc: ["'self'", "data:", "https:"],
    },
  },
});

module.exports = { limiter, securityHeaders };
EOF

# Aggiorna server.js per usare il middleware di sicurezza
cat > backend/src/server.js << 'EOF'
const express = require('express');
const cors = require('cors');
const { limiter, securityHeaders } = require('./middleware/security');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 5000;

// Security middleware
app.use(securityHeaders);
app.use(limiter);

// Standard middleware
app.use(cors());
app.use(express.json({ limit: '10mb' }));

// Routes
app.use('/api/dashboard', require('./routes/dashboard'));
app.use('/api/products', require('./routes/products'));
app.use('/api/orders', require('./routes/orders'));

// Health check
app.get('/health', (req, res) => {
  res.json({ 
    status: 'OK', 
    timestamp: new Date().toISOString(),
    version: '1.0.1'  // Bumped version
  });
});

// Error handler
app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).json({ error: 'Something went wrong!' });
});

app.listen(PORT, () => {
  console.log(`Backend server running on port ${PORT}`);
});

module.exports = app;
EOF

# Commit hotfix
git add .
git commit -m "hotfix: add security middleware and rate limiting"

# Merge hotfix in main
git checkout main
git merge hotfix/security-vulnerability

# Tag release
git tag -a v1.0.1 -m "Security hotfix v1.0.1"

# Merge hotfix in develop anche
git checkout develop
git merge hotfix/security-vulnerability
```

#### 3. Risoluzione Conflitti Complessi
Se durante i merge ci sono conflitti, ecco come gestirli:

```bash
# Esempio di conflitto in package.json root
git status  # Mostra file in conflitto

# Risolvi conflitti manualmente
# Poi:
git add .
git commit -m "resolve: merge conflicts between features"
```

## 📊 Test e Verifica Finale

### Esercizio 2.6: Testing e Deployment (10 minuti)

#### 1. Test Integration
```bash
# Build completo del progetto
npm run install:all
npm run build

# Test con Docker
docker-compose up -d
sleep 30

# Verify services
curl http://localhost:3000  # Frontend
curl http://localhost:5000/health  # Backend

# Test API endpoints
curl http://localhost:5000/api/dashboard/stats
curl http://localhost:5000/api/products

# Cleanup
docker-compose down
```

#### 2. Branch Cleanup
```bash
# Lista branch
git branch -a

# Delete feature branches
git branch -d feature/frontend-dashboard
git branch -d feature/backend-api  
git branch -d feature/database-schema
git branch -d feature/devops-setup
git branch -d hotfix/security-vulnerability

# Final git status
git log --oneline --graph --all -10
```

## 🎯 Competenze Acquisite

### ✅ Multi-Team Collaboration
- Coordinamento sviluppo parallelo
- Branch strategy in progetti grandi
- Integration testing e deployment

### ✅ Conflict Resolution
- Merge complessi tra team
- Hotfix in ambiente production
- Branch management avanzato

### ✅ Professional Workflows
- CI/CD pipeline implementation
- Docker containerization
- Database migration strategies

## 📈 Risultati Finali

Al completamento dovresti avere:
- Dashboard e-commerce completo e funzionante
- API backend con endpoints RESTful
- Database schema con migrations
- Setup DevOps completo con Docker
- Esperienza pratica con workflow multi-team

## 🔗 Navigazione

← [Esercizio 1: Feature Development](01-feature-development.md) | [Modulo 13](../README.md) | [Esercizio 3: Team Simulation →](03-team-simulation.md)

---

**Durata**: 90-120 minuti | **Livello**: Avanzato | **Tipo**: Progetto Completo
