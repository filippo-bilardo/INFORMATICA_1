# Deployment Troubleshooting Guide

## Common Deployment Issues & Solutions

### 1. Build Failures

#### Problem: Build Fails in Production
```bash
# Common error scenarios

# ❌ Environment-specific build failures
npm run build
# Error: Cannot resolve module './config/production.js'
# File exists locally but not in production

# ❌ Memory issues during build
FATAL ERROR: Ineffective mark-compacts near heap limit Allocation failed - JavaScript heap out of memory
```

#### Solution: Build Environment Setup
```bash
# ✅ Check Node.js version consistency
# package.json
{
    "engines": {
        "node": ">=18.0.0",
        "npm": ">=8.0.0"
    }
}

# ✅ Production build configuration
# webpack.config.js
module.exports = (env, argv) => {
    const isProduction = argv.mode === 'production';
    
    return {
        mode: isProduction ? 'production' : 'development',
        optimization: {
            minimizer: isProduction ? [
                new TerserPlugin({
                    parallel: true,
                    terserOptions: {
                        compress: { drop_console: true }
                    }
                })
            ] : []
        },
        
        // Increase memory for large builds
        performance: {
            maxAssetSize: 512000,
            maxEntrypointSize: 512000
        }
    };
};

# ✅ Docker build optimization
# Dockerfile
FROM node:18-alpine AS builder

# Set memory limit
ENV NODE_OPTIONS="--max_old_space_size=4096"

WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production

COPY . .
RUN npm run build

# Multi-stage build for smaller image
FROM nginx:alpine
COPY --from=builder /app/dist /usr/share/nginx/html
```

### 2. Environment Configuration Issues

#### Problem: Missing Environment Variables
```javascript
// ❌ Runtime errors due to missing env vars
const config = {
    database: {
        host: process.env.DB_HOST,        // undefined in production
        port: process.env.DB_PORT,        // undefined
        user: process.env.DB_USER         // undefined
    }
};

// Connection fails silently or with cryptic errors
```

#### Solution: Environment Management
```javascript
// ✅ Environment validation
function validateEnvironment() {
    const required = [
        'DB_HOST',
        'DB_PORT', 
        'DB_USER',
        'DB_PASSWORD',
        'JWT_SECRET',
        'API_BASE_URL'
    ];
    
    const missing = required.filter(env => !process.env[env]);
    
    if (missing.length > 0) {
        console.error('Missing required environment variables:', missing);
        process.exit(1);
    }
}

// Call during app startup
validateEnvironment();

// ✅ Environment-specific configuration
// config/index.js
const config = {
    development: {
        database: {
            host: process.env.DB_HOST || 'localhost',
            port: parseInt(process.env.DB_PORT) || 5432,
            user: process.env.DB_USER || 'dev_user'
        }
    },
    
    production: {
        database: {
            host: process.env.DB_HOST,     // Required in production
            port: parseInt(process.env.DB_PORT),
            user: process.env.DB_USER,
            ssl: { rejectUnauthorized: false }
        }
    }
};

module.exports = config[process.env.NODE_ENV] || config.development;
```

#### Environment File Management
```bash
# ✅ Environment file templates
# .env.example
DB_HOST=localhost
DB_PORT=5432
DB_USER=your_username
DB_PASSWORD=your_password
JWT_SECRET=your_secret_key
API_BASE_URL=http://localhost:3000

# ✅ Docker environment setup
# docker-compose.yml
version: '3.8'
services:
  app:
    build: .
    environment:
      - NODE_ENV=production
      - DB_HOST=${DB_HOST}
      - DB_PORT=${DB_PORT}
    env_file:
      - .env.production

# ✅ Kubernetes secrets
apiVersion: v1
kind: Secret
metadata:
  name: app-secrets
type: Opaque
data:
  DB_PASSWORD: <base64-encoded-password>
  JWT_SECRET: <base64-encoded-secret>
```

### 3. Database Migration Issues

#### Problem: Migration Failures
```sql
-- ❌ Migration fails in production
ALTER TABLE users ADD COLUMN avatar_url VARCHAR(255) NOT NULL;
-- Error: Column cannot be NOT NULL without default value

-- ❌ Data loss during migration
DROP TABLE old_user_profiles;
-- Data is permanently lost
```

#### Solution: Safe Migration Practices
```sql
-- ✅ Safe column addition
ALTER TABLE users ADD COLUMN avatar_url VARCHAR(255);
UPDATE users SET avatar_url = 'default-avatar.png' WHERE avatar_url IS NULL;
ALTER TABLE users ALTER COLUMN avatar_url SET NOT NULL;

-- ✅ Backup before destructive operations
-- migration_backup.sql
CREATE TABLE old_user_profiles_backup AS SELECT * FROM old_user_profiles;
-- Then proceed with DROP TABLE

-- ✅ Rollback scripts
-- up.sql
ALTER TABLE users ADD COLUMN new_field VARCHAR(100);

-- down.sql  
ALTER TABLE users DROP COLUMN new_field;
```

#### Migration Automation
```javascript
// ✅ Migration validation script
const { Pool } = require('pg');

async function runMigrations() {
    const pool = new Pool({ connectionString: process.env.DATABASE_URL });
    
    try {
        // Check if migration table exists
        await pool.query(`
            CREATE TABLE IF NOT EXISTS migrations (
                id SERIAL PRIMARY KEY,
                filename VARCHAR(255) UNIQUE,
                executed_at TIMESTAMP DEFAULT NOW()
            )
        `);
        
        // Get pending migrations
        const pendingMigrations = await getPendingMigrations(pool);
        
        for (const migration of pendingMigrations) {
            console.log(`Running migration: ${migration.filename}`);
            
            // Begin transaction
            const client = await pool.connect();
            await client.query('BEGIN');
            
            try {
                // Execute migration
                await client.query(migration.sql);
                
                // Record successful migration
                await client.query(
                    'INSERT INTO migrations (filename) VALUES ($1)',
                    [migration.filename]
                );
                
                await client.query('COMMIT');
                console.log(`✅ Migration completed: ${migration.filename}`);
            } catch (error) {
                await client.query('ROLLBACK');
                console.error(`❌ Migration failed: ${migration.filename}`, error);
                throw error;
            } finally {
                client.release();
            }
        }
    } finally {
        await pool.end();
    }
}
```

### 4. SSL/TLS Certificate Issues

#### Problem: HTTPS Configuration
```bash
# ❌ Certificate errors
curl https://yourapp.com
# curl: (60) SSL certificate problem: certificate verify failed

# ❌ Mixed content errors
# HTTPS page loading HTTP resources
```

#### Solution: Proper SSL Setup
```nginx
# ✅ Nginx SSL configuration
server {
    listen 443 ssl http2;
    server_name yourapp.com www.yourapp.com;
    
    # SSL certificates
    ssl_certificate /etc/letsencrypt/live/yourapp.com/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/yourapp.com/privkey.pem;
    
    # SSL security settings
    ssl_protocols TLSv1.2 TLSv1.3;
    ssl_ciphers ECDHE-RSA-AES256-GCM-SHA384:ECDHE-RSA-AES128-GCM-SHA256;
    ssl_prefer_server_ciphers off;
    
    # Security headers
    add_header Strict-Transport-Security "max-age=31536000; includeSubDomains";
    add_header X-Frame-Options DENY;
    add_header X-Content-Type-Options nosniff;
    
    location / {
        proxy_pass http://localhost:3000;
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}

# Redirect HTTP to HTTPS
server {
    listen 80;
    server_name yourapp.com www.yourapp.com;
    return 301 https://$server_name$request_uri;
}
```

#### Let's Encrypt Automation
```bash
# ✅ Automated certificate renewal
#!/bin/bash
# renew-ssl.sh

certbot renew --nginx --quiet

# Test nginx configuration
nginx -t

if [ $? -eq 0 ]; then
    systemctl reload nginx
    echo "SSL certificate renewed successfully"
else
    echo "Nginx configuration test failed"
    exit 1
fi

# Crontab entry for automatic renewal
# 0 3 * * * /path/to/renew-ssl.sh
```

### 5. Performance Issues in Production

#### Problem: Slow Application Response
```javascript
// ❌ N+1 query problems
async function getUsers() {
    const users = await User.findAll();
    
    // This creates N+1 queries
    for (const user of users) {
        user.posts = await Post.findAll({ where: { userId: user.id } });
    }
    
    return users;
}

// ❌ No caching for expensive operations
app.get('/api/dashboard', async (req, res) => {
    const data = await generateComplexDashboardData(); // Takes 5 seconds
    res.json(data);
});
```

#### Solution: Performance Optimization
```javascript
// ✅ Optimized database queries
async function getUsers() {
    return await User.findAll({
        include: [{
            model: Post,
            as: 'posts'
        }]
    });
}

// ✅ Caching implementation
const Redis = require('redis');
const client = Redis.createClient(process.env.REDIS_URL);

app.get('/api/dashboard', async (req, res) => {
    const cacheKey = `dashboard:${req.user.id}`;
    
    // Try cache first
    const cached = await client.get(cacheKey);
    if (cached) {
        return res.json(JSON.parse(cached));
    }
    
    // Generate data if not cached
    const data = await generateComplexDashboardData();
    
    // Cache for 5 minutes
    await client.setex(cacheKey, 300, JSON.stringify(data));
    
    res.json(data);
});

// ✅ Connection pooling
const pool = new Pool({
    connectionString: process.env.DATABASE_URL,
    max: 20,                // Maximum connections
    idleTimeoutMillis: 30000,
    connectionTimeoutMillis: 2000
});
```

### 6. Monitoring & Logging Issues

#### Problem: Insufficient Observability
```javascript
// ❌ Poor error handling and logging
app.post('/api/users', async (req, res) => {
    try {
        const user = await createUser(req.body);
        res.json(user);
    } catch (error) {
        console.log('Error:', error); // Insufficient logging
        res.status(500).json({ error: 'Something went wrong' });
    }
});
```

#### Solution: Comprehensive Monitoring
```javascript
// ✅ Structured logging
const winston = require('winston');

const logger = winston.createLogger({
    level: process.env.LOG_LEVEL || 'info',
    format: winston.format.combine(
        winston.format.timestamp(),
        winston.format.errors({ stack: true }),
        winston.format.json()
    ),
    defaultMeta: { service: 'user-api' },
    transports: [
        new winston.transports.File({ filename: 'error.log', level: 'error' }),
        new winston.transports.File({ filename: 'combined.log' })
    ]
});

app.post('/api/users', async (req, res) => {
    const requestId = req.headers['x-request-id'] || generateId();
    
    try {
        logger.info('Creating user', {
            requestId,
            userId: req.user?.id,
            email: req.body.email
        });
        
        const user = await createUser(req.body);
        
        logger.info('User created successfully', {
            requestId,
            newUserId: user.id
        });
        
        res.json(user);
    } catch (error) {
        logger.error('Failed to create user', {
            requestId,
            error: error.message,
            stack: error.stack,
            input: req.body
        });
        
        res.status(500).json({ 
            error: 'Failed to create user',
            requestId 
        });
    }
});
```

#### Health Checks and Metrics
```javascript
// ✅ Health check endpoint
app.get('/health', async (req, res) => {
    const health = {
        status: 'ok',
        timestamp: new Date().toISOString(),
        uptime: process.uptime(),
        environment: process.env.NODE_ENV
    };
    
    try {
        // Check database connection
        await pool.query('SELECT 1');
        health.database = 'connected';
    } catch (error) {
        health.database = 'disconnected';
        health.status = 'error';
    }
    
    try {
        // Check Redis connection
        await client.ping();
        health.cache = 'connected';
    } catch (error) {
        health.cache = 'disconnected';
    }
    
    const statusCode = health.status === 'ok' ? 200 : 503;
    res.status(statusCode).json(health);
});

// ✅ Application metrics
const promClient = require('prom-client');

const httpRequestDuration = new promClient.Histogram({
    name: 'http_request_duration_seconds',
    help: 'Duration of HTTP requests in seconds',
    labelNames: ['method', 'route', 'status']
});

app.use((req, res, next) => {
    const start = Date.now();
    
    res.on('finish', () => {
        const duration = (Date.now() - start) / 1000;
        httpRequestDuration
            .labels(req.method, req.route?.path || req.url, res.statusCode)
            .observe(duration);
    });
    
    next();
});

app.get('/metrics', (req, res) => {
    res.set('Content-Type', promClient.register.contentType);
    res.end(promClient.register.metrics());
});
```

### 7. Rollback Strategies

#### Problem: Failed Deployment Recovery
```bash
# ❌ No rollback plan
# Deployment fails, application is down
# Manual intervention required to restore service
```

#### Solution: Automated Rollback
```bash
# ✅ Blue-Green deployment script
#!/bin/bash
# deploy.sh

BLUE_PORT=3000
GREEN_PORT=3001
HEALTH_CHECK_URL="http://localhost"

# Determine current active environment
CURRENT_PORT=$(nginx -T | grep "proxy_pass.*:300" | grep -o "300[0-9]")

if [ "$CURRENT_PORT" = "$BLUE_PORT" ]; then
    DEPLOY_PORT=$GREEN_PORT
    ACTIVE_COLOR="blue"
    DEPLOY_COLOR="green"
else
    DEPLOY_PORT=$BLUE_PORT
    ACTIVE_COLOR="green" 
    DEPLOY_COLOR="blue"
fi

echo "Deploying to $DEPLOY_COLOR environment (port $DEPLOY_PORT)"

# Deploy to inactive environment
docker stop app-$DEPLOY_COLOR || true
docker rm app-$DEPLOY_COLOR || true

docker run -d \
    --name app-$DEPLOY_COLOR \
    -p $DEPLOY_PORT:3000 \
    --env-file .env.production \
    myapp:latest

# Health check
echo "Performing health check..."
for i in {1..30}; do
    if curl -f "$HEALTH_CHECK_URL:$DEPLOY_PORT/health"; then
        echo "Health check passed"
        break
    fi
    
    if [ $i -eq 30 ]; then
        echo "Health check failed, rolling back"
        docker stop app-$DEPLOY_COLOR
        exit 1
    fi
    
    sleep 10
done

# Switch traffic
echo "Switching traffic to $DEPLOY_COLOR"
sed -i "s/:$CURRENT_PORT/:$DEPLOY_PORT/" /etc/nginx/sites-available/default
nginx -t && systemctl reload nginx

# Stop old environment
sleep 30  # Grace period
docker stop app-$ACTIVE_COLOR

echo "Deployment to $DEPLOY_COLOR completed successfully"
```

#### Database Rollback Strategy
```sql
-- ✅ Migration rollback plan
-- Create rollback scripts for each migration

-- Migration 001_add_user_fields.up.sql
ALTER TABLE users ADD COLUMN avatar_url VARCHAR(255);
ALTER TABLE users ADD COLUMN bio TEXT;

-- Migration 001_add_user_fields.down.sql
ALTER TABLE users DROP COLUMN bio;
ALTER TABLE users DROP COLUMN avatar_url;

-- Rollback automation
#!/bin/bash
# rollback_migration.sh
MIGRATION_ID=$1

if [ -z "$MIGRATION_ID" ]; then
    echo "Usage: $0 <migration_id>"
    exit 1
fi

echo "Rolling back migration $MIGRATION_ID"
psql $DATABASE_URL -f "migrations/${MIGRATION_ID}.down.sql"

# Remove from migrations table
psql $DATABASE_URL -c "DELETE FROM migrations WHERE filename LIKE '${MIGRATION_ID}%'"

echo "Migration $MIGRATION_ID rolled back successfully"
```

Questa guida fornisce soluzioni pratiche per i problemi di deployment più comuni, assicurando deployments affidabili e recupero rapido in caso di problemi.
