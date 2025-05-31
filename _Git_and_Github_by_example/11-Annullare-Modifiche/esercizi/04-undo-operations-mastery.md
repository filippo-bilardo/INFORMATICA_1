# Esercizio: Mastery di Operazioni di Undo

## 📚 Obiettivo dell'Esercizio

Sviluppare competenze di livello maestro nelle operazioni di undo Git attraverso scenari complessi che combinano multiple tecniche, automazione di recovery, e gestione di repository enterprise. Questo esercizio simula situazioni reali dove la scelta della tecnica di undo appropriata è critica per il successo del progetto.

## 🎯 Competenze Sviluppate

- **Strategic Undo Planning**: Pianificazione strategica di operazioni di undo
- **Enterprise Recovery**: Gestione undo in ambienti enterprise complessi
- **Automation**: Automazione di procedure di undo e recovery
- **Risk Assessment**: Valutazione dei rischi nelle operazioni di undo
- **Performance Impact**: Analisi dell'impatto prestazionale delle operazioni
- **Compliance**: Conformità a standard aziendali e audit trail

## ⚙️ Setup Ambiente Enterprise

### Fase 1: Simulazione Repository Enterprise

```bash
# Creare ambiente enterprise multi-team
mkdir git-undo-mastery
cd git-undo-mastery

# Setup repository principale
git init
git config user.name "Enterprise Admin"
git config user.email "admin@enterprise.com"

# Creare struttura enterprise complessa
mkdir -p {microservices,shared-libs,infrastructure,docs}/{src,tests,config}
mkdir -p {monitoring,security,compliance}/{logs,policies,reports}
mkdir -p scripts/{deployment,maintenance,recovery}

# Setup microservizio di autenticazione
cat > microservices/auth-service/src/auth.js << 'EOF'
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import { UserRepository } from '../../../shared-libs/src/repositories/user.js';

export class AuthService {
    constructor() {
        this.userRepo = new UserRepository();
        this.tokenSecret = process.env.JWT_SECRET || 'dev-secret';
        this.tokenExpiry = '24h';
    }
    
    async authenticate(username, password) {
        const user = await this.userRepo.findByUsername(username);
        if (!user) {
            throw new Error('User not found');
        }
        
        const isValid = await bcrypt.compare(password, user.passwordHash);
        if (!isValid) {
            throw new Error('Invalid credentials');
        }
        
        return this.generateToken(user);
    }
    
    generateToken(user) {
        return jwt.sign(
            { userId: user.id, username: user.username },
            this.tokenSecret,
            { expiresIn: this.tokenExpiry }
        );
    }
    
    verifyToken(token) {
        return jwt.verify(token, this.tokenSecret);
    }
}
EOF

# Setup servizio di pagamenti
cat > microservices/payment-service/src/payment.js << 'EOF'
import Stripe from 'stripe';
import { TransactionRepository } from '../../../shared-libs/src/repositories/transaction.js';

export class PaymentService {
    constructor() {
        this.stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
        this.transactionRepo = new TransactionRepository();
    }
    
    async processPayment(amount, currency, paymentMethodId) {
        try {
            const paymentIntent = await this.stripe.paymentIntents.create({
                amount: amount * 100, // Convert to cents
                currency: currency,
                payment_method: paymentMethodId,
                confirm: true,
                return_url: process.env.RETURN_URL
            });
            
            await this.transactionRepo.create({
                stripePaymentIntentId: paymentIntent.id,
                amount: amount,
                currency: currency,
                status: paymentIntent.status,
                createdAt: new Date()
            });
            
            return paymentIntent;
        } catch (error) {
            console.error('Payment processing failed:', error);
            throw error;
        }
    }
}
EOF

# Setup libreria condivisa critica
cat > shared-libs/src/repositories/base.js << 'EOF'
import { Database } from '../database/connection.js';

export class BaseRepository {
    constructor(tableName) {
        this.tableName = tableName;
        this.db = new Database();
    }
    
    async findById(id) {
        const query = `SELECT * FROM ${this.tableName} WHERE id = ?`;
        return await this.db.query(query, [id]);
    }
    
    async create(data) {
        const fields = Object.keys(data).join(', ');
        const placeholders = Object.keys(data).map(() => '?').join(', ');
        const values = Object.values(data);
        
        const query = `INSERT INTO ${this.tableName} (${fields}) VALUES (${placeholders})`;
        return await this.db.query(query, values);
    }
    
    async update(id, data) {
        const setClause = Object.keys(data).map(key => `${key} = ?`).join(', ');
        const values = [...Object.values(data), id];
        
        const query = `UPDATE ${this.tableName} SET ${setClause} WHERE id = ?`;
        return await this.db.query(query, values);
    }
    
    async delete(id) {
        const query = `DELETE FROM ${this.tableName} WHERE id = ?`;
        return await this.db.query(query, [id]);
    }
}
EOF

# Setup script di deployment critico
cat > scripts/deployment/deploy.sh << 'EOF'
#!/bin/bash

# Enterprise Deployment Script v2.1
# Critical: This script handles production deployments

set -euo pipefail

ENVIRONMENT=${1:-staging}
VERSION=${2:-latest}
ROLLBACK_ENABLED=${3:-true}

echo "🚀 Starting deployment to $ENVIRONMENT..."
echo "📦 Version: $VERSION"
echo "🔄 Rollback enabled: $ROLLBACK_ENABLED"

# Pre-deployment checks
check_dependencies() {
    command -v docker >/dev/null 2>&1 || { echo "Docker is required"; exit 1; }
    command -v kubectl >/dev/null 2>&1 || { echo "kubectl is required"; exit 1; }
}

# Database migration
run_migrations() {
    echo "🗄️  Running database migrations..."
    kubectl exec -n $ENVIRONMENT deployment/database -- ./migrate.sh up
}

# Deploy microservices
deploy_services() {
    echo "🔧 Deploying microservices..."
    
    # Auth service
    kubectl set image deployment/auth-service auth-service=auth:$VERSION -n $ENVIRONMENT
    kubectl rollout status deployment/auth-service -n $ENVIRONMENT --timeout=300s
    
    # Payment service
    kubectl set image deployment/payment-service payment-service=payment:$VERSION -n $ENVIRONMENT
    kubectl rollout status deployment/payment-service -n $ENVIRONMENT --timeout=300s
}

# Health checks
health_check() {
    echo "🏥 Running health checks..."
    
    for service in auth-service payment-service; do
        if ! curl -f "http://$service.$ENVIRONMENT.svc.cluster.local/health"; then
            echo "❌ Health check failed for $service"
            return 1
        fi
    done
    
    echo "✅ All health checks passed"
}

# Main deployment flow
main() {
    check_dependencies
    
    if [[ "$ENVIRONMENT" == "production" ]]; then
        echo "⚠️  Production deployment requires additional confirmation"
        read -p "Are you sure? (yes/no): " confirm
        [[ "$confirm" == "yes" ]] || exit 1
    fi
    
    run_migrations
    deploy_services
    health_check
    
    echo "🎉 Deployment completed successfully!"
}

main "$@"
EOF

chmod +x scripts/deployment/deploy.sh

# Setup configurazione di monitoraggio
cat > monitoring/config/alerts.yaml << 'EOF'
alerts:
  - name: "High Error Rate"
    condition: "error_rate > 5%"
    severity: "critical"
    notification:
      - slack: "#alerts"
      - email: "oncall@enterprise.com"
  
  - name: "Database Connection Issues"
    condition: "db_connection_failures > 10"
    severity: "high"
    notification:
      - slack: "#database-team"
  
  - name: "Payment Service Down"
    condition: "payment_service_availability < 99%"
    severity: "critical"
    notification:
      - slack: "#payment-team"
      - pagerduty: "payment-escalation"
EOF

# Setup policy di sicurezza
cat > security/policies/access-control.md << 'EOF'
# Access Control Policy v3.2

## Branch Protection Rules

### Production Branch (main)
- Require pull request reviews: 2
- Dismiss stale reviews: true
- Require status checks: true
- Required checks:
  - CI/CD pipeline
  - Security scan
  - Code quality gate
- Restrict pushes: admin only
- Allow force pushes: false

### Development Branches
- Require pull request reviews: 1
- Required checks:
  - Unit tests
  - Integration tests

## Deployment Permissions

### Production
- Only release managers
- Requires security approval
- Must include rollback plan

### Staging
- Development team leads
- QA team
- DevOps engineers
EOF

# Commit iniziale
git add .
git commit -m "feat: initial enterprise repository setup

- Add authentication microservice with JWT handling
- Add payment service with Stripe integration
- Add shared repository base classes
- Add deployment scripts with health checks
- Add monitoring and security configurations
- Establish enterprise-grade project structure"

echo "✅ Enterprise repository setup completed"
```

### Fase 2: Creazione Storia Complessa con Branch

```bash
# Creare branch per diverse feature
git checkout -b feature/enhanced-auth
cat > microservices/auth-service/src/auth.js << 'EOF'
import bcrypt from 'bcrypt';
import jwt from 'jsonwebtoken';
import { UserRepository } from '../../../shared-libs/src/repositories/user.js';
import { AuditLogger } from '../../../shared-libs/src/logging/audit.js';

export class AuthService {
    constructor() {
        this.userRepo = new UserRepository();
        this.auditLogger = new AuditLogger();
        this.tokenSecret = process.env.JWT_SECRET || 'dev-secret';
        this.tokenExpiry = '24h';
        this.maxFailedAttempts = 5;
        this.lockoutDuration = 15 * 60 * 1000; // 15 minutes
    }
    
    async authenticate(username, password, ipAddress) {
        const user = await this.userRepo.findByUsername(username);
        if (!user) {
            await this.auditLogger.log('auth_failed', { username, ipAddress, reason: 'user_not_found' });
            throw new Error('Invalid credentials');
        }
        
        // Check if account is locked
        if (this.isAccountLocked(user)) {
            await this.auditLogger.log('auth_blocked', { username, ipAddress, reason: 'account_locked' });
            throw new Error('Account temporarily locked');
        }
        
        const isValid = await bcrypt.compare(password, user.passwordHash);
        if (!isValid) {
            await this.incrementFailedAttempts(user);
            await this.auditLogger.log('auth_failed', { username, ipAddress, reason: 'invalid_password' });
            throw new Error('Invalid credentials');
        }
        
        // Reset failed attempts on successful login
        await this.resetFailedAttempts(user);
        await this.auditLogger.log('auth_success', { username, ipAddress });
        
        return this.generateToken(user);
    }
    
    isAccountLocked(user) {
        if (!user.failedAttempts || user.failedAttempts < this.maxFailedAttempts) {
            return false;
        }
        
        const lockoutExpiry = new Date(user.lastFailedAttempt).getTime() + this.lockoutDuration;
        return Date.now() < lockoutExpiry;
    }
    
    async incrementFailedAttempts(user) {
        const failedAttempts = (user.failedAttempts || 0) + 1;
        await this.userRepo.update(user.id, {
            failedAttempts,
            lastFailedAttempt: new Date()
        });
    }
    
    async resetFailedAttempts(user) {
        await this.userRepo.update(user.id, {
            failedAttempts: 0,
            lastFailedAttempt: null
        });
    }
    
    generateToken(user) {
        return jwt.sign(
            { 
                userId: user.id, 
                username: user.username,
                roles: user.roles || [],
                iat: Math.floor(Date.now() / 1000)
            },
            this.tokenSecret,
            { expiresIn: this.tokenExpiry }
        );
    }
    
    verifyToken(token) {
        try {
            return jwt.verify(token, this.tokenSecret);
        } catch (error) {
            this.auditLogger.log('token_verification_failed', { error: error.message });
            throw error;
        }
    }
}
EOF

git add .
git commit -m "feat(auth): add enhanced security features

- Add account lockout mechanism after failed attempts
- Add audit logging for authentication events
- Add IP address tracking
- Add role-based JWT tokens
- Improve error handling and security logging

BREAKING CHANGE: authenticate method now requires ipAddress parameter"

# Continuare con payment service enhancement
cat > microservices/payment-service/src/payment.js << 'EOF'
import Stripe from 'stripe';
import { TransactionRepository } from '../../../shared-libs/src/repositories/transaction.js';
import { NotificationService } from '../../../shared-libs/src/services/notification.js';
import { FraudDetection } from '../../../shared-libs/src/services/fraud-detection.js';

export class PaymentService {
    constructor() {
        this.stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
        this.transactionRepo = new TransactionRepository();
        this.notificationService = new NotificationService();
        this.fraudDetection = new FraudDetection();
    }
    
    async processPayment(amount, currency, paymentMethodId, userId, metadata = {}) {
        // Fraud detection
        const fraudScore = await this.fraudDetection.analyze({
            amount,
            currency,
            userId,
            paymentMethodId,
            metadata
        });
        
        if (fraudScore > 0.8) {
            await this.notificationService.sendAlert('high_fraud_risk', {
                userId,
                amount,
                fraudScore
            });
            throw new Error('Payment flagged for review');
        }
        
        try {
            const paymentIntent = await this.stripe.paymentIntents.create({
                amount: amount * 100, // Convert to cents
                currency: currency,
                payment_method: paymentMethodId,
                confirm: true,
                return_url: process.env.RETURN_URL,
                metadata: {
                    ...metadata,
                    userId: userId.toString(),
                    fraudScore: fraudScore.toString()
                }
            });
            
            const transaction = await this.transactionRepo.create({
                stripePaymentIntentId: paymentIntent.id,
                userId: userId,
                amount: amount,
                currency: currency,
                status: paymentIntent.status,
                fraudScore: fraudScore,
                metadata: metadata,
                createdAt: new Date()
            });
            
            // Send confirmation notification
            if (paymentIntent.status === 'succeeded') {
                await this.notificationService.sendPaymentConfirmation(userId, {
                    transactionId: transaction.id,
                    amount: amount,
                    currency: currency
                });
            }
            
            return {
                paymentIntent,
                transaction,
                fraudScore
            };
        } catch (error) {
            console.error('Payment processing failed:', error);
            
            // Log failed payment attempt
            await this.transactionRepo.create({
                userId: userId,
                amount: amount,
                currency: currency,
                status: 'failed',
                errorMessage: error.message,
                fraudScore: fraudScore,
                metadata: metadata,
                createdAt: new Date()
            });
            
            throw error;
        }
    }
    
    async refundPayment(transactionId, amount = null, reason = '') {
        const transaction = await this.transactionRepo.findById(transactionId);
        if (!transaction) {
            throw new Error('Transaction not found');
        }
        
        const refundAmount = amount || transaction.amount;
        
        try {
            const refund = await this.stripe.refunds.create({
                payment_intent: transaction.stripePaymentIntentId,
                amount: refundAmount * 100,
                reason: reason || 'requested_by_customer'
            });
            
            await this.transactionRepo.update(transactionId, {
                refundId: refund.id,
                refundAmount: refundAmount,
                refundStatus: refund.status,
                refundReason: reason,
                refundedAt: new Date()
            });
            
            // Send refund notification
            await this.notificationService.sendRefundConfirmation(transaction.userId, {
                transactionId: transactionId,
                refundAmount: refundAmount,
                currency: transaction.currency
            });
            
            return refund;
        } catch (error) {
            console.error('Refund processing failed:', error);
            throw error;
        }
    }
}
EOF

git add .
git commit -m "feat(payment): add fraud detection and enhanced processing

- Add fraud detection analysis before payment processing
- Add notification service integration
- Add comprehensive transaction logging
- Add refund processing capabilities
- Improve error handling and audit trail

This enhances security and user experience significantly."

git checkout main
git merge feature/enhanced-auth

# Creare branch hotfix critico
git checkout -b hotfix/security-vulnerability
cat > shared-libs/src/repositories/base.js << 'EOF'
import { Database } from '../database/connection.js';
import { SecurityValidator } from '../security/validator.js';

export class BaseRepository {
    constructor(tableName) {
        this.tableName = this.validateTableName(tableName);
        this.db = new Database();
        this.validator = new SecurityValidator();
    }
    
    validateTableName(tableName) {
        // Prevent SQL injection through table names
        if (!/^[a-zA-Z_][a-zA-Z0-9_]*$/.test(tableName)) {
            throw new Error('Invalid table name format');
        }
        return tableName;
    }
    
    async findById(id) {
        // Validate input
        this.validator.validateId(id);
        
        const query = `SELECT * FROM ${this.tableName} WHERE id = ?`;
        return await this.db.query(query, [id]);
    }
    
    async create(data) {
        // Validate all input data
        this.validator.validateCreateData(data);
        
        const fields = Object.keys(data).join(', ');
        const placeholders = Object.keys(data).map(() => '?').join(', ');
        const values = Object.values(data);
        
        const query = `INSERT INTO ${this.tableName} (${fields}) VALUES (${placeholders})`;
        return await this.db.query(query, values);
    }
    
    async update(id, data) {
        // Validate inputs
        this.validator.validateId(id);
        this.validator.validateUpdateData(data);
        
        const setClause = Object.keys(data).map(key => `${key} = ?`).join(', ');
        const values = [...Object.values(data), id];
        
        const query = `UPDATE ${this.tableName} SET ${setClause} WHERE id = ?`;
        return await this.db.query(query, values);
    }
    
    async delete(id) {
        // Validate input
        this.validator.validateId(id);
        
        const query = `DELETE FROM ${this.tableName} WHERE id = ?`;
        return await this.db.query(query, [id]);
    }
    
    // New method for safe bulk operations
    async bulkCreate(dataArray) {
        if (!Array.isArray(dataArray) || dataArray.length === 0) {
            throw new Error('Data array must be non-empty array');
        }
        
        const results = [];
        for (const data of dataArray) {
            results.push(await this.create(data));
        }
        return results;
    }
}
EOF

# Aggiungere security validator
mkdir -p shared-libs/src/security
cat > shared-libs/src/security/validator.js << 'EOF'
export class SecurityValidator {
    validateId(id) {
        if (typeof id !== 'number' && typeof id !== 'string') {
            throw new Error('ID must be number or string');
        }
        
        if (typeof id === 'string' && !/^[a-zA-Z0-9-_]+$/.test(id)) {
            throw new Error('Invalid ID format');
        }
        
        if (typeof id === 'number' && (id <= 0 || !Number.isInteger(id))) {
            throw new Error('ID must be positive integer');
        }
    }
    
    validateCreateData(data) {
        if (!data || typeof data !== 'object') {
            throw new Error('Data must be non-empty object');
        }
        
        // Check for dangerous keys
        const dangerousKeys = ['__proto__', 'constructor', 'prototype'];
        for (const key of Object.keys(data)) {
            if (dangerousKeys.includes(key)) {
                throw new Error(`Dangerous key not allowed: ${key}`);
            }
        }
    }
    
    validateUpdateData(data) {
        this.validateCreateData(data);
        
        // Additional checks for updates
        if ('id' in data) {
            throw new Error('Cannot update ID field');
        }
    }
}
EOF

git add .
git commit -m "fix: critical security vulnerability in BaseRepository

- Add input validation to prevent SQL injection
- Add SecurityValidator for comprehensive data validation
- Add table name validation to prevent injection attacks
- Add bulk operation support with validation
- SECURITY: Prevents potential data breaches

CVE-2024-XXXX: SQL injection vulnerability in repository layer"

git tag -a v2.1.1 -m "Security hotfix v2.1.1"

# Simulare problema: push accidentale di credenziali
cat > .env << 'EOF'
# Database Configuration
DB_HOST=localhost
DB_PORT=5432
DB_NAME=enterprise_app
DB_USER=admin
DB_PASSWORD=super_secret_password_123!

# JWT Configuration
JWT_SECRET=very_secret_jwt_key_do_not_share

# Stripe Configuration
STRIPE_SECRET_KEY=sk_live_51234567890abcdef
STRIPE_PUBLISHABLE_KEY=pk_live_51234567890abcdef

# AWS Configuration
AWS_ACCESS_KEY_ID=AKIAIOSFODNN7EXAMPLE
AWS_SECRET_ACCESS_KEY=wJalrXUtnFEMI/K7MDENG/bPxRfiCYEXAMPLEKEY

# Production URLs
DATABASE_URL=postgresql://admin:super_secret_password_123!@prod-db.example.com:5432/enterprise_app
REDIS_URL=redis://admin:redis_password_456@prod-redis.example.com:6379
EOF

git add .
git commit -m "chore: add environment configuration for production deployment"

echo "❌ OOPS! Committed sensitive credentials to repository!"
```

## 🎯 Scenari di Undo Mastery

### Scenario 1: Rimozione Credenziali Sensibili

```bash
# PROBLEMA: Hai appena committato credenziali sensibili
# OBIETTIVO: Rimuovere completamente dalla storia

echo "🚨 EMERGENCY: Sensitive credentials committed!"
echo "📋 Task: Remove .env file and rewrite history safely"

# Analizzare la situazione
git log --oneline -5
git show HEAD --name-only

# SOLUZIONE 1: Se non ancora pushato (scenario più comune)
echo "🔧 Solution 1: Local history rewrite"

# Rimuovere file sensibile dalla working directory
rm .env
echo "*.env" >> .gitignore

# Modificare l'ultimo commit
git add .gitignore
git commit --amend -m "chore: add environment configuration template

- Add .gitignore to exclude sensitive files
- Environment variables should be set via deployment tools"

# Verificare che le credenziali siano rimosse
git show HEAD --name-only
echo "✅ Credentials removed from latest commit"

# SOLUZIONE 2: Se già pushato (scenario più complesso)
echo "🔧 Solution 2: Advanced history rewrite for pushed commits"

# Prima, creare backup
git tag backup-before-cleanup

# Usare filter-branch per rimuovere file dalla storia completa
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch .env' \
  --prune-empty --tag-name-filter cat -- --all

# Pulire riferimenti
git for-each-ref --format='delete %(refname)' refs/original | git update-ref --stdin
git reflog expire --expire=now --all
git gc --prune=now --aggressive

echo "✅ History cleaned, but requires force push coordination with team"
```

### Scenario 2: Merge Conflict Resolution con Recovery

```bash
# Simulare merge conflict complesso
git checkout main
git checkout -b feature/payment-improvements

# Modificare payment service in modo conflittuale
cat > microservices/payment-service/src/payment.js << 'EOF'
import Stripe from 'stripe';
import { TransactionRepository } from '../../../shared-libs/src/repositories/transaction.js';

export class PaymentService {
    constructor() {
        this.stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
        this.transactionRepo = new TransactionRepository();
        this.timeout = 30000; // 30 second timeout
    }
    
    async processPayment(amount, currency, paymentMethodId) {
        // Simplified approach - conflicting with fraud detection branch
        const paymentIntent = await this.stripe.paymentIntents.create({
            amount: amount * 100,
            currency: currency,
            payment_method: paymentMethodId,
            confirm: true,
            return_url: process.env.RETURN_URL
        });
        
        return paymentIntent;
    }
}
EOF

git add .
git commit -m "feat: simplify payment processing for better performance"

# Tentare merge che fallirà
git checkout main
echo "🔄 Attempting merge that will create conflicts..."
git merge feature/payment-improvements

echo "💥 MERGE CONFLICT DETECTED!"
echo "📋 Task: Resolve conflict while preserving both improvements"

# SOLUZIONE: Smart conflict resolution
echo "🔧 Smart Conflict Resolution Process"

# 1. Analizzare i conflitti
git status
git diff --name-only --diff-filter=U

# 2. Vedere le tre versioni
echo "📊 Analyzing three-way merge:"
echo "BASE (common ancestor):"
git show :1:microservices/payment-service/src/payment.js | head -20

echo "OURS (main branch):"
git show :2:microservices/payment-service/src/payment.js | head -20

echo "THEIRS (feature branch):"
git show :3:microservices/payment-service/src/payment.js | head -20

# 3. Creare soluzione combinata manuale
cat > microservices/payment-service/src/payment.js << 'EOF'
import Stripe from 'stripe';
import { TransactionRepository } from '../../../shared-libs/src/repositories/transaction.js';
import { NotificationService } from '../../../shared-libs/src/services/notification.js';
import { FraudDetection } from '../../../shared-libs/src/services/fraud-detection.js';

export class PaymentService {
    constructor() {
        this.stripe = new Stripe(process.env.STRIPE_SECRET_KEY);
        this.transactionRepo = new TransactionRepository();
        this.notificationService = new NotificationService();
        this.fraudDetection = new FraudDetection();
        this.timeout = 30000; // 30 second timeout - from feature branch
    }
    
    async processPayment(amount, currency, paymentMethodId, userId, metadata = {}) {
        // Combine both approaches: fraud detection + performance optimization
        
        // Quick fraud check with timeout
        const fraudPromise = this.fraudDetection.analyze({
            amount, currency, userId, paymentMethodId, metadata
        });
        
        const timeoutPromise = new Promise((_, reject) => 
            setTimeout(() => reject(new Error('Fraud detection timeout')), 5000)
        );
        
        let fraudScore = 0;
        try {
            fraudScore = await Promise.race([fraudPromise, timeoutPromise]);
            
            if (fraudScore > 0.8) {
                await this.notificationService.sendAlert('high_fraud_risk', {
                    userId, amount, fraudScore
                });
                throw new Error('Payment flagged for review');
            }
        } catch (error) {
            if (error.message === 'Fraud detection timeout') {
                console.warn('Fraud detection timed out, proceeding with caution');
                fraudScore = 0.5; // Default moderate risk
            } else {
                throw error;
            }
        }
        
        // Optimized payment processing
        try {
            const paymentIntent = await this.stripe.paymentIntents.create({
                amount: amount * 100,
                currency: currency,
                payment_method: paymentMethodId,
                confirm: true,
                return_url: process.env.RETURN_URL,
                metadata: {
                    ...metadata,
                    userId: userId.toString(),
                    fraudScore: fraudScore.toString()
                }
            });
            
            // Async transaction logging for better performance
            this.transactionRepo.create({
                stripePaymentIntentId: paymentIntent.id,
                userId: userId,
                amount: amount,
                currency: currency,
                status: paymentIntent.status,
                fraudScore: fraudScore,
                metadata: metadata,
                createdAt: new Date()
            }).catch(error => {
                console.error('Transaction logging failed:', error);
                // Continue processing, don't fail payment for logging issues
            });
            
            return {
                paymentIntent,
                fraudScore
            };
        } catch (error) {
            console.error('Payment processing failed:', error);
            throw error;
        }
    }
}
EOF

git add .
git commit -m "feat: merge payment improvements with fraud detection

- Combine fraud detection with performance optimizations
- Add timeout handling for fraud detection service
- Make transaction logging asynchronous for better performance
- Preserve security features while improving speed

Resolves conflict between security and performance requirements"

echo "✅ Conflict resolved with combined solution"
```

### Scenario 3: Repository Corruption Recovery

```bash
echo "🗄️ SCENARIO: Repository Corruption Simulation"

# Simulare corruzione accidentale
echo "💥 Simulating repository corruption..."

# Corrompere oggetti Git (ATTENZIONE: solo per simulazione!)
cd .git/objects
find . -name "*.git" -type d -exec rm -rf {} + 2>/dev/null || true

# Tentare operazioni Git
cd ../..
echo "🔍 Testing repository state..."
git status 2>&1 || echo "Repository corrupted detected"

echo "🚑 EMERGENCY RECOVERY PROCEDURE"

# RECOVERY STEP 1: Diagnosi
echo "📊 Step 1: Repository Diagnosis"
git fsck --full 2>&1 | tee repository-health.log || true
git log --oneline 2>&1 | head -10 || echo "Log access failed"

# RECOVERY STEP 2: Backup esistente
echo "💾 Step 2: Create emergency backup"
cp -r . ../emergency-backup-$(date +%Y%m%d-%H%M%S) 2>/dev/null || true

# RECOVERY STEP 3: Recupero da remote (se disponibile)
echo "🌐 Step 3: Recovery from remote"
# Simulare remote recovery
git remote -v 2>/dev/null || echo "No remotes configured"

# In caso reale:
# git fetch origin
# git reset --hard origin/main

# RECOVERY STEP 4: Ricostruzione da backup locale
echo "🔧 Step 4: Local reconstruction"

# Reinizializzare repository
rm -rf .git
git init
git config user.name "Recovery Admin"
git config user.email "recovery@enterprise.com"

# Aggiungere tutti i file attuali
git add .
git commit -m "emergency: repository reconstruction after corruption

- Rebuilt repository from working directory
- Recovered from corruption incident
- All current files preserved
- History may be incomplete - requires team sync"

echo "✅ Repository reconstructed"
echo "⚠️  Action required: Coordinate with team for history restoration"
```

### Scenario 4: Advanced Reset Strategies

```bash
echo "🎯 SCENARIO: Advanced Reset Strategies"

# Creare situazione complessa con multiple branch
git checkout -b feature/advanced-monitoring
mkdir -p monitoring/src/collectors

cat > monitoring/src/collectors/metrics.js << 'EOF'
export class MetricsCollector {
    constructor() {
        this.metrics = new Map();
        this.interval = 60000; // 1 minute
    }
    
    collect(name, value, tags = {}) {
        const key = `${name}:${JSON.stringify(tags)}`;
        this.metrics.set(key, {
            name,
            value,
            tags,
            timestamp: Date.now()
        });
    }
    
    getMetrics() {
        return Array.from(this.metrics.values());
    }
}
EOF

git add .
git commit -m "feat: add metrics collection system"

cat > monitoring/src/collectors/logs.js << 'EOF'
export class LogCollector {
    constructor() {
        this.logs = [];
        this.maxSize = 10000;
    }
    
    log(level, message, metadata = {}) {
        this.logs.push({
            level,
            message,
            metadata,
            timestamp: new Date().toISOString()
        });
        
        if (this.logs.length > this.maxSize) {
            this.logs.shift();
        }
    }
    
    getLogs(level = null) {
        return level 
            ? this.logs.filter(log => log.level === level)
            : this.logs;
    }
}
EOF

git add .
git commit -m "feat: add log collection system"

# Commit problematico
cat > monitoring/src/collectors/bad-code.js << 'EOF'
// This code has serious problems
export class BadCollector {
    constructor() {
        // Memory leak - never cleared
        this.dataCache = [];
        setInterval(() => {
            this.dataCache.push(new Array(1000000).fill('data'));
        }, 1000);
    }
    
    // Synchronous blocking operation
    processData() {
        for (let i = 0; i < 1000000; i++) {
            Math.random();
        }
    }
}
EOF

git add .
git commit -m "feat: add data collector - DO NOT USE IN PRODUCTION"

git checkout main
git merge feature/advanced-monitoring

echo "🚨 PROBLEMA: Merged problematic code into main!"
echo "📋 Task: Use different reset strategies to fix"

# STRATEGIA 1: Soft Reset (preserva modifiche)
echo "🔧 Strategy 1: Soft Reset"
git log --oneline -5

# Reset mantiene modifiche in staging
git reset --soft HEAD~2

echo "📊 After soft reset:"
git status
echo "✅ Changes preserved in staging area"

# Ricommit in modo pulito
git commit -m "feat: add clean monitoring system

- Add metrics collection with proper resource management
- Add log collection with size limits
- Remove problematic data collector

Cleaned up merge to remove performance issues"

# STRATEGIA 2: Mixed Reset (default)
echo "🔧 Strategy 2: Mixed Reset"

# Creare altro commit problematico
echo "console.log('debug info');" >> monitoring/src/collectors/metrics.js
git add .
git commit -m "debug: add temporary debug output"

# Mixed reset
git reset HEAD~1

echo "📊 After mixed reset:"
git status
echo "✅ Changes moved to working directory"

# Pulire e ricommit
git restore monitoring/src/collectors/metrics.js
echo "✅ Debug code cleaned without committing"

# STRATEGIA 3: Hard Reset (attenzione!)
echo "🔧 Strategy 3: Hard Reset (with safety)"

# Prima creare backup
git stash push -m "backup before hard reset"

# Creare commit da eliminare
echo "temporary change" > temp-file.txt
git add .
git commit -m "temp: temporary commit to be removed"

# Hard reset
git reset --hard HEAD~1

echo "📊 After hard reset:"
git status
echo "✅ All changes completely removed"

# STRATEGIA 4: Interactive Reset
echo "🔧 Strategy 4: Interactive Reset for Precise Control"

# Creare multiple commit
echo "feature 1" > feature1.txt
git add .
git commit -m "feat: add feature 1"

echo "feature 2" > feature2.txt
git add .
git commit -m "feat: add feature 2"

echo "bug fix" > bugfix.txt
git add .
git commit -m "fix: important bug fix"

# Reset interattivo (simulato)
echo "📝 Interactive reset would allow choosing which commits to keep"
git log --oneline -5

# Simulare reset selettivo
git reset --hard HEAD~2  # Rimuove feature 2 e bugfix
git cherry-pick HEAD@{1}  # Riprende solo il bugfix

echo "✅ Selectively preserved important changes"
```

### Scenario 5: Automation Recovery Scripts

```bash
echo "🤖 SCENARIO: Automated Recovery Scripts"

# Creare script di recovery automatizzato
cat > scripts/recovery/auto-recovery.sh << 'EOF'
#!/bin/bash

# Git Auto-Recovery Script v1.0
# Handles common Git disaster scenarios automatically

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOG_FILE="$SCRIPT_DIR/recovery.log"
BACKUP_DIR="$SCRIPT_DIR/../../.recovery-backups"

log() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" | tee -a "$LOG_FILE"
}

create_backup() {
    local backup_name="backup-$(date +%Y%m%d-%H%M%S)"
    mkdir -p "$BACKUP_DIR"
    
    log "Creating backup: $backup_name"
    cp -r .git "$BACKUP_DIR/$backup_name.git" 2>/dev/null || true
    
    # Export current state
    git bundle create "$BACKUP_DIR/$backup_name.bundle" --all 2>/dev/null || true
    
    echo "$backup_name"
}

detect_problem() {
    local problem=""
    
    # Check for repository corruption
    if ! git status >/dev/null 2>&1; then
        problem="corruption"
    # Check for detached HEAD
    elif git status | grep -q "HEAD detached"; then
        problem="detached_head"
    # Check for uncommitted changes before potentially destructive operation
    elif ! git diff-index --quiet HEAD -- 2>/dev/null; then
        problem="uncommitted_changes"
    # Check for unmerged paths
    elif git status | grep -q "Unmerged paths"; then
        problem="merge_conflict"
    fi
    
    echo "$problem"
}

recover_corruption() {
    log "RECOVERY: Repository corruption detected"
    
    # Try to repair
    git fsck --full 2>&1 | tee -a "$LOG_FILE" || true
    
    # If severe corruption, try to recover from remote
    if git remote get-url origin >/dev/null 2>&1; then
        log "Attempting recovery from remote"
        git fetch origin 2>&1 | tee -a "$LOG_FILE" || true
        git reset --hard origin/$(git symbolic-ref --short HEAD 2>/dev/null || echo "main") 2>&1 | tee -a "$LOG_FILE" || true
    fi
}

recover_detached_head() {
    log "RECOVERY: Detached HEAD detected"
    
    local current_commit=$(git rev-parse HEAD)
    local branch_name="recovery-$(date +%H%M%S)"
    
    # Create branch from current position
    git checkout -b "$branch_name"
    log "Created recovery branch: $branch_name"
    
    # Try to determine original branch
    local original_branch=$(git for-each-ref --format='%(refname:short)' refs/heads | head -1)
    if [[ -n "$original_branch" ]]; then
        log "Merging back to $original_branch"
        git checkout "$original_branch"
        git merge "$branch_name"
    fi
}

recover_uncommitted_changes() {
    log "RECOVERY: Uncommitted changes detected"
    
    # Stash changes with timestamp
    local stash_message="auto-recovery-$(date +%Y%m%d-%H%M%S)"
    git stash push -m "$stash_message"
    log "Stashed changes as: $stash_message"
    
    # List stashes for user reference
    git stash list | tee -a "$LOG_FILE"
}

recover_merge_conflict() {
    log "RECOVERY: Merge conflict detected"
    
    # Analyze conflict
    git status | tee -a "$LOG_FILE"
    
    # Create backup of conflict state
    cp -r . "$BACKUP_DIR/conflict-state-$(date +%Y%m%d-%H%M%S)" 2>/dev/null || true
    
    # Abort merge to return to safe state
    git merge --abort 2>&1 | tee -a "$LOG_FILE" || true
    log "Merge aborted, returned to pre-merge state"
}

main() {
    log "=== Git Auto-Recovery Started ==="
    
    # Create backup before any recovery
    local backup_name=$(create_backup)
    log "Backup created: $backup_name"
    
    # Detect and handle problems
    local problem=$(detect_problem)
    
    case "$problem" in
        "corruption")
            recover_corruption
            ;;
        "detached_head")
            recover_detached_head
            ;;
        "uncommitted_changes")
            recover_uncommitted_changes
            ;;
        "merge_conflict")
            recover_merge_conflict
            ;;
        "")
            log "No problems detected"
            ;;
        *)
            log "Unknown problem: $problem"
            ;;
    esac
    
    log "=== Git Auto-Recovery Completed ==="
    log "Backup available at: $BACKUP_DIR/$backup_name"
}

main "$@"
EOF

chmod +x scripts/recovery/auto-recovery.sh

# Creare script per undo intelligente
cat > scripts/recovery/smart-undo.sh << 'EOF'
#!/bin/bash

# Smart Undo Script - Chooses best undo strategy automatically

analyze_situation() {
    local commits_ahead=$(git rev-list --count @{u}..HEAD 2>/dev/null || echo "0")
    local has_staged=$(git diff-index --cached --quiet HEAD -- && echo "false" || echo "true")
    local has_unstaged=$(git diff-files --quiet && echo "false" || echo "true")
    local last_commit_age=$(git log -1 --format="%cr" | grep -o '[0-9]*')
    
    echo "commits_ahead:$commits_ahead"
    echo "has_staged:$has_staged" 
    echo "has_unstaged:$has_unstaged"
    echo "last_commit_age:$last_commit_age"
}

smart_undo() {
    local target=${1:-"last"}
    local situation=$(analyze_situation)
    
    echo "🔍 Analyzing situation..."
    echo "$situation"
    
    if echo "$situation" | grep -q "commits_ahead:0"; then
        echo "✅ Safe to use destructive operations (not pushed)"
        
        if [[ "$target" == "last" ]]; then
            if echo "$situation" | grep -q "has_staged:true\|has_unstaged:true"; then
                echo "💾 Preserving working changes"
                git reset --soft HEAD~1
            else
                echo "🔥 Complete removal"
                git reset --hard HEAD~1
            fi
        fi
    else
        echo "⚠️  Commits already pushed, using safe revert"
        git revert HEAD --no-edit
    fi
}

smart_undo "$@"
EOF

chmod +x scripts/recovery/smart-undo.sh

git add .
git commit -m "feat: add automated recovery and smart undo scripts

- Add auto-recovery script for common Git disasters
- Add smart undo that chooses appropriate strategy
- Include backup creation before recovery operations
- Support for corruption, conflicts, and detached HEAD recovery

These scripts provide enterprise-grade safety nets."

echo "✅ Automation scripts created"
```

## 🏆 Certificazione Mastery

### Test Finale di Competenza

```bash
echo "🏆 FINAL MASTERY TEST"
echo "Complete these challenges to prove your undo mastery:"

cat > MASTERY-CERTIFICATION.md << 'EOF'
# Git Undo Operations Mastery Certification

## Challenge 1: Emergency Credential Removal (30 points)
- Commit sensitive credentials
- Remove them completely from history
- Ensure no traces remain in any refs
- Document the complete process

## Challenge 2: Complex Merge Resolution (25 points)
- Create conflicting branches with advanced features
- Resolve conflicts preserving both enhancements
- Demonstrate understanding of three-way merge
- Use appropriate commit messages

## Challenge 3: Corruption Recovery (25 points)
- Simulate repository corruption
- Recover using multiple strategies
- Minimize data loss
- Document recovery procedures

## Challenge 4: Strategic Reset Planning (20 points)
- Analyze repository state
- Choose appropriate reset strategy
- Preserve important changes
- Automate the decision process

## Scoring:
- 90-100: Undo Master
- 80-89: Undo Expert
- 70-79: Undo Professional
- <70: Needs improvement

## Evidence Required:
- Screenshots of commands
- Before/after repository states
- Recovery scripts
- Documentation of decisions
EOF

echo "📋 Certification challenges documented"
echo "🎯 Complete all scenarios to achieve mastery level"
```

## 📚 Risorse per il Completamento

### Script di Verifica

```bash
echo "🔍 VERIFICATION SCRIPT"

cat > scripts/verify-mastery.sh << 'EOF'
#!/bin/bash

# Verify mastery completion

echo "📊 Git Undo Mastery Verification"
echo "================================"

# Check understanding of concepts
echo "✅ Concepts learned:"
echo "  - Emergency credential removal"
echo "  - Smart merge conflict resolution"
echo "  - Repository corruption recovery"
echo "  - Strategic reset planning"
echo "  - Automation of recovery procedures"

# Check tools mastered
echo "✅ Tools mastered:"
echo "  - git commit --amend"
echo "  - git reset (soft/mixed/hard)"
echo "  - git revert"
echo "  - git restore"
echo "  - git filter-branch"
echo "  - git fsck"
echo "  - git reflog"
echo "  - git cherry-pick"

# Check scenarios completed
echo "✅ Scenarios completed:"
ls esercizi/ | grep -E '\.md$' | wc -l
echo "  scenarios available"

echo "🏆 Mastery achievement unlocked!"
EOF

chmod +x scripts/verify-mastery.sh

git add .
git commit -m "docs: add mastery certification and verification

- Complete certification framework
- Verification scripts for self-assessment
- Documentation of all learned concepts
- Ready for enterprise application

ACHIEVEMENT: Undo Operations Mastery completed!"

echo "🎉 MASTERY EXERCISE COMPLETED!"
echo "📝 You have developed expert-level skills in:"
echo "   • Strategic undo planning"
echo "   • Emergency recovery procedures"
echo "   • Automation of recovery processes"
echo "   • Enterprise-grade safety practices"
echo ""
echo "🏆 You are now ready to handle any Git undo scenario!"
```

## 🔚 Riepilogo delle Competenze

Questo esercizio ti ha preparato per:

- **Gestione emergenze**: Risposta rapida a situazioni critiche
- **Automazione recovery**: Script per automatizzare procedure di recupero
- **Strategia undo**: Scelta della tecnica appropriata per ogni scenario
- **Enterprise safety**: Pratiche sicure per ambienti di produzione
- **Team coordination**: Gestione undo in team distribuiti

⏱️ **Durata completamento**: 90-120 minuti
🎯 **Livello di competenza**: Expert/Master
🏆 **Certificazione**: Git Undo Operations Mastery
