# Esempio 4: Gestione Branch Remoti - Collaborazione Multi-Team

## 📋 Scenario
Simuliamo la gestione di branch remoti in un progetto e-commerce con team distribuiti che lavorano su diverse funzionalità. Gestiremo la sincronizzazione, i conflitti e la collaborazione tra team.

## 🎯 Obiettivi
- Gestire branch remoti e tracking
- Sincronizzare il lavoro tra team diversi
- Risolvere conflitti di collaborazione
- Implementare workflow di team distribuite

## 🏗️ Setup Iniziale

### 1. Creazione Repository Principale
```bash
# Repository principale (origin)
mkdir ecommerce-platform
cd ecommerce-platform
git init
git config user.name "Project Lead"
git config user.email "lead@company.com"

# Struttura iniziale
mkdir -p {frontend/{components,pages,styles},backend/{api,models,middleware},database}
echo "# E-commerce Platform" > README.md
echo "node_modules/" > .gitignore
echo "*.log" >> .gitignore

# Primo commit
git add .
git commit -m "feat: initial project structure"
```

### 2. Simulazione Repository Remoto
```bash
# Creiamo un repository "remoto" (simulato in locale)
cd ..
git clone --bare ecommerce-platform ecommerce-platform.git

# Repository per Team Frontend
git clone ecommerce-platform.git frontend-team
cd frontend-team
git config user.name "Frontend Team"
git config user.email "frontend@company.com"

# Repository per Team Backend
cd ..
git clone ecommerce-platform.git backend-team
cd backend-team
git config user.name "Backend Team"
git config user.email "backend@company.com"

# Repository per Team DevOps
cd ..
git clone ecommerce-platform.git devops-team
cd devops-team
git config user.name "DevOps Team"
git config user.email "devops@company.com"
```

## 🚀 Sviluppo Parallelo Multi-Team

### Team Frontend - Feature: Product Catalog

```bash
cd frontend-team

# Creazione branch feature
git checkout -b feature/product-catalog
git push -u origin feature/product-catalog

# Sviluppo componenti prodotto
cat > frontend/components/ProductCard.js << 'EOF'
import React from 'react';

const ProductCard = ({ product }) => {
  return (
    <div className="product-card">
      <img src={product.image} alt={product.name} />
      <h3>{product.name}</h3>
      <p className="price">${product.price}</p>
      <button onClick={() => addToCart(product)}>
        Add to Cart
      </button>
    </div>
  );
};

export default ProductCard;
EOF

cat > frontend/pages/ProductCatalog.js << 'EOF'
import React, { useState, useEffect } from 'react';
import ProductCard from '../components/ProductCard';

const ProductCatalog = () => {
  const [products, setProducts] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetchProducts();
  }, []);

  const fetchProducts = async () => {
    try {
      const response = await fetch('/api/products');
      const data = await response.json();
      setProducts(data);
    } catch (error) {
      console.error('Error fetching products:', error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="product-catalog">
      <h1>Product Catalog</h1>
      {loading ? (
        <div>Loading products...</div>
      ) : (
        <div className="product-grid">
          {products.map(product => (
            <ProductCard key={product.id} product={product} />
          ))}
        </div>
      )}
    </div>
  );
};

export default ProductCatalog;
EOF

git add .
git commit -m "feat: add product catalog components"
git push origin feature/product-catalog
```

### Team Backend - Feature: API Endpoints

```bash
cd ../backend-team

# Sincronizzazione con remote
git fetch origin
git checkout -b feature/product-api
git push -u origin feature/product-api

# Sviluppo API prodotti
cat > backend/models/Product.js << 'EOF'
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true,
    trim: true
  },
  description: {
    type: String,
    required: true
  },
  price: {
    type: Number,
    required: true,
    min: 0
  },
  category: {
    type: String,
    required: true
  },
  image: {
    type: String,
    required: true
  },
  stock: {
    type: Number,
    required: true,
    min: 0
  },
  isActive: {
    type: Boolean,
    default: true
  }
}, {
  timestamps: true
});

productSchema.index({ category: 1, isActive: 1 });
productSchema.index({ name: 'text', description: 'text' });

module.exports = mongoose.model('Product', productSchema);
EOF

cat > backend/api/products.js << 'EOF'
const express = require('express');
const Product = require('../models/Product');
const router = express.Router();

// GET /api/products - Lista prodotti
router.get('/', async (req, res) => {
  try {
    const { 
      category, 
      search, 
      minPrice, 
      maxPrice, 
      page = 1, 
      limit = 20 
    } = req.query;

    const query = { isActive: true };
    
    if (category) query.category = category;
    if (search) query.$text = { $search: search };
    if (minPrice || maxPrice) {
      query.price = {};
      if (minPrice) query.price.$gte = parseFloat(minPrice);
      if (maxPrice) query.price.$lte = parseFloat(maxPrice);
    }

    const skip = (page - 1) * limit;
    const products = await Product.find(query)
      .sort({ createdAt: -1 })
      .skip(skip)
      .limit(parseInt(limit));

    const total = await Product.countDocuments(query);

    res.json({
      products,
      pagination: {
        currentPage: parseInt(page),
        totalPages: Math.ceil(total / limit),
        totalItems: total
      }
    });
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

// POST /api/products - Crea prodotto
router.post('/', async (req, res) => {
  try {
    const product = new Product(req.body);
    await product.save();
    res.status(201).json(product);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
});

// GET /api/products/:id - Dettaglio prodotto
router.get('/:id', async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);
    if (!product) {
      return res.status(404).json({ error: 'Product not found' });
    }
    res.json(product);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

module.exports = router;
EOF

git add .
git commit -m "feat: add product API endpoints and models"
git push origin feature/product-api
```

### Team DevOps - Feature: Docker Configuration

```bash
cd ../devops-team

# Fetch e creazione branch
git fetch origin
git checkout -b feature/docker-setup
git push -u origin feature/docker-setup

# Docker configuration
cat > Dockerfile << 'EOF'
# Multi-stage build per applicazione Node.js
FROM node:18-alpine AS builder

WORKDIR /app

# Copy package files
COPY package*.json ./
RUN npm ci --only=production

# Copy source code
COPY . .

# Build frontend se necessario
RUN npm run build

# Production stage
FROM node:18-alpine AS production

WORKDIR /app

# Create non-root user
RUN addgroup -g 1001 -S nodejs && \
    adduser -S nextjs -u 1001

# Copy built application
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/package*.json ./
COPY --from=builder /app/backend ./backend
COPY --from=builder /app/frontend/build ./frontend/build

# Set ownership
RUN chown -R nextjs:nodejs /app
USER nextjs

EXPOSE 3000

CMD ["npm", "start"]
EOF

cat > docker-compose.yml << 'EOF'
version: '3.8'

services:
  app:
    build: .
    ports:
      - "3000:3000"
    environment:
      - NODE_ENV=production
      - MONGODB_URI=mongodb://mongo:27017/ecommerce
      - REDIS_URL=redis://redis:6379
    depends_on:
      - mongo
      - redis
    networks:
      - ecommerce-network

  mongo:
    image: mongo:6
    volumes:
      - mongo-data:/data/db
    environment:
      - MONGO_INITDB_ROOT_USERNAME=admin
      - MONGO_INITDB_ROOT_PASSWORD=password
    networks:
      - ecommerce-network
    healthcheck:
      test: ["CMD", "mongosh", "--eval", "db.adminCommand('ping')"]
      interval: 30s
      timeout: 10s
      retries: 3

  redis:
    image: redis:7-alpine
    volumes:
      - redis-data:/data
    networks:
      - ecommerce-network
    healthcheck:
      test: ["CMD", "redis-cli", "ping"]
      interval: 30s
      timeout: 10s
      retries: 3

  nginx:
    image: nginx:alpine
    ports:
      - "80:80"
      - "443:443"
    volumes:
      - ./nginx.conf:/etc/nginx/nginx.conf
      - ./ssl:/etc/ssl
    depends_on:
      - app
    networks:
      - ecommerce-network

volumes:
  mongo-data:
  redis-data:

networks:
  ecommerce-network:
    driver: bridge
EOF

cat > nginx.conf << 'EOF'
events {
    worker_connections 1024;
}

http {
    upstream app {
        server app:3000;
    }

    server {
        listen 80;
        server_name localhost;
        return 301 https://$server_name$request_uri;
    }

    server {
        listen 443 ssl;
        server_name localhost;

        ssl_certificate /etc/ssl/cert.pem;
        ssl_certificate_key /etc/ssl/key.pem;

        location / {
            proxy_pass http://app;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;
        }

        location /health {
            access_log off;
            return 200 "healthy\n";
            add_header Content-Type text/plain;
        }
    }
}
EOF

git add .
git commit -m "feat: add Docker configuration and nginx setup"
git push origin feature/docker-setup
```

## 🔄 Gestione Sincronizzazione e Conflitti

### 1. Aggiornamento Branch con Conflitti

```bash
# Team Frontend - aggiorna il file README
cd ../frontend-team
git checkout main
echo -e "\n## Frontend Team\n- React components\n- User interface" >> README.md
git add README.md
git commit -m "docs: add frontend team info"
git push origin main

# Team Backend - modifica lo stesso file
cd ../backend-team
git checkout main
echo -e "\n## Backend Team\n- API endpoints\n- Database models" >> README.md
git add README.md
git commit -m "docs: add backend team info"

# Tentativo di push (fallirà)
git push origin main || echo "Push rejected - need to pull first"

# Risoluzione conflitto
git pull origin main --no-ff

# Il file avrà conflitti - risolviamo manualmente
cat > README.md << 'EOF'
# E-commerce Platform

Multi-team collaboration project for e-commerce platform development.

## Frontend Team
- React components
- User interface

## Backend Team
- API endpoints
- Database models
EOF

git add README.md
git commit -m "docs: merge team documentation"
git push origin main
```

### 2. Gestione Branch Feature Complessi

```bash
# Merge feature nel main tramite Pull Request simulation
cd ../frontend-team

# Aggiornamento con main
git checkout main
git pull origin main
git checkout feature/product-catalog
git rebase main

# Test prima del merge
echo "Running tests..." && sleep 2
echo "All tests passed ✅"

# Merge feature
git checkout main
git merge --no-ff feature/product-catalog -m "feat: merge product catalog feature"
git push origin main

# Cleanup branch locale
git branch -d feature/product-catalog
git push origin --delete feature/product-catalog
```

### 3. Tracking Branch Remoti

```bash
# Lista tutti i branch remoti
git branch -r

# Track nuovo branch remoto
git checkout --track origin/feature/product-api

# Visualizza tracking info
git branch -vv

# Setup tracking per branch esistente
git branch --set-upstream-to=origin/feature/docker-setup feature/docker-setup
```

## 📊 Monitoring e Status Branch

### 1. Dashboard Branch Status

```bash
# Script per monitoring branch
cat > monitor-branches.sh << 'EOF'
#!/bin/bash

echo "🔍 BRANCH MONITORING DASHBOARD"
echo "================================"

echo -e "\n📍 Current Branch:"
git branch --show-current

echo -e "\n🌲 Local Branches:"
git branch -v

echo -e "\n🌐 Remote Branches:"
git branch -r -v

echo -e "\n🔗 Tracking Information:"
git branch -vv

echo -e "\n📈 Branch Status vs Origin:"
for branch in $(git branch --format='%(refname:short)'); do
    if [ "$branch" != "main" ]; then
        ahead=$(git rev-list --count origin/main..$branch 2>/dev/null || echo "0")
        behind=$(git rev-list --count $branch..origin/main 2>/dev/null || echo "0")
        echo "  $branch: +$ahead/-$behind commits vs main"
    fi
done

echo -e "\n🏷️ Recent Activity:"
git for-each-ref --format='%(refname:short) %(committerdate) %(authorname)' \
    --sort=-committerdate refs/heads refs/remotes | head -10

echo -e "\n⚠️ Branches Need Attention:"
git for-each-ref --format='%(refname:short) %(committerdate)' \
    --sort=committerdate refs/heads | head -5
EOF

chmod +x monitor-branches.sh
./monitor-branches.sh
```

### 2. Cleanup Script Branch Obsoleti

```bash
cat > cleanup-branches.sh << 'EOF'
#!/bin/bash

echo "🧹 BRANCH CLEANUP UTILITY"
echo "========================="

echo -e "\n1. Merged branches (safe to delete):"
git branch --merged main | grep -v "main\|master" | while read branch; do
    echo "  - $branch (merged)"
done

echo -e "\n2. Stale branches (>30 days):"
git for-each-ref --format='%(refname:short) %(committerdate)' refs/heads | \
    while read branch date time; do
        if [ "$branch" != "main" ]; then
            if [ $(date -d "$date $time" +%s) -lt $(date -d "30 days ago" +%s) ]; then
                echo "  - $branch ($date)"
            fi
        fi
    done

echo -e "\n3. Remote tracking branches without remote:"
git branch -vv | grep ': gone]' | awk '{print $1}' | while read branch; do
    echo "  - $branch (remote deleted)"
done

read -p "Run cleanup? (y/N): " -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo -e "\n🗑️ Cleaning up..."
    
    # Delete merged branches
    git branch --merged main | grep -v "main\|master" | xargs -r git branch -d
    
    # Delete tracking branches with gone remotes
    git branch -vv | grep ': gone]' | awk '{print $1}' | xargs -r git branch -D
    
    # Prune remote references
    git remote prune origin
    
    echo "✅ Cleanup completed!"
fi
EOF

chmod +x cleanup-branches.sh
```

## 🎯 Workflow di Team Collaboration

### 1. Feature Integration Workflow

```bash
# Template per feature integration
cat > feature-workflow.md << 'EOF'
# Feature Integration Workflow

## 1. Preparazione Feature
```bash
git checkout main
git pull origin main
git checkout -b feature/nome-feature
git push -u origin feature/nome-feature
```

## 2. Sviluppo
```bash
# Sviluppo iterativo
git add .
git commit -m "feat: descrizione incrementale"
git push origin feature/nome-feature

# Sync periodico con main
git fetch origin
git rebase origin/main
```

## 3. Review e Test
```bash
# Code review checklist
- [ ] Tests passano
- [ ] Code style rispettato
- [ ] Documentazione aggiornata
- [ ] Performance accettabili
- [ ] Security review fatto
```

## 4. Merge
```bash
git checkout main
git pull origin main
git merge --no-ff feature/nome-feature
git push origin main
git branch -d feature/nome-feature
git push origin --delete feature/nome-feature
```
EOF
```

### 2. Hotfix Emergency Workflow

```bash
cat > hotfix-workflow.md << 'EOF'
# Emergency Hotfix Workflow

## 1. Identificazione Issue
- Severità: CRITICA
- Impact: Produzione down
- Timeline: Fix in <2 ore

## 2. Hotfix Branch
```bash
git checkout main
git pull origin main
git checkout -b hotfix/emergency-fix
```

## 3. Fix e Test Rapido
```bash
# Fix minimale e mirato
# Test essenziali
# Validation deployment
```

## 4. Deploy Emergency
```bash
git add .
git commit -m "hotfix: fix critical production issue"
git push origin hotfix/emergency-fix

# Direct deploy to production
git checkout main
git merge hotfix/emergency-fix
git push origin main
git tag -a v1.0.1 -m "Emergency hotfix v1.0.1"
git push origin v1.0.1
```

## 5. Post-Mortem
- Root cause analysis
- Prevention measures
- Process improvements
EOF
```

## 📈 Risultati e Verifiche

### 1. Verifica Stato Finale

```bash
echo "📊 FINAL REPOSITORY STATUS"
echo "=========================="

cd ../frontend-team
echo -e "\n👥 Frontend Team Repository:"
git log --oneline -5
git branch -a

cd ../backend-team
echo -e "\n⚙️ Backend Team Repository:"
git log --oneline -5
git branch -a

cd ../devops-team
echo -e "\n🐳 DevOps Team Repository:"
git log --oneline -5
git branch -a
```

### 2. Network Graph Simulation

```bash
echo -e "\n🌐 Network Graph Visualization:"
git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit --all
```

## 🎯 Competenze Acquisite

### ✅ Gestione Branch Remoti
- Setup tracking branches
- Sincronizzazione team distribuiti
- Risoluzione conflitti collaborativi
- Monitoring stato branch

### ✅ Workflow Collaboration
- Feature development in team
- Code review e integration
- Emergency hotfix procedures
- Branch cleanup e maintenance

### ✅ Best Practices Professionali
- Naming conventions branch
- Commit message standards
- Automated testing integration
- Documentation maintenance

## 🔗 Navigazione

← [Esempio 3: Sperimentazione](03-sperimentazione.md) | [Modulo 13](../README.md) | [Esercizio 1: Feature Development →](../esercizi/01-feature-development.md)

---

**Durata**: 90-120 minuti | **Livello**: Avanzato | **Prerequisiti**: Git basics, branch concepts
