# Esercizio: Pianificazione e Gestione Release con Git Flow

## Obiettivo
Praticare la pianificazione e gestione di release complete utilizzando Git Flow, simulando un ambiente di sviluppo enterprise con team multipli e release coordinate.

## Scenario
Sei il Release Manager di un'azienda di software che sviluppa un'applicazione e-commerce. Devi gestire una release trimestrale (v2.3.0) che include:
- 3 feature team che lavorano in parallelo
- Fix critici da applicare
- Dipendenze esterne da coordinare
- Testing multi-ambiente
- Rollback strategies

## Preparazione Ambiente

### Setup Repository
```bash
# Clona il repository di esempio
git clone https://github.com/example/ecommerce-platform.git
cd ecommerce-platform

# Configura Git Flow
git flow init

# Setup branch protection rules (simulated)
echo "Setup branch protection per main e develop"
```

### Struttura Iniziale
```
ecommerce-platform/
├── src/
│   ├── frontend/
│   ├── backend/
│   ├── mobile/
│   └── shared/
├── tests/
├── docs/
├── deployment/
└── scripts/
```

## Parte 1: Pianificazione Release (30 minuti)

### 1.1 Definizione Release Plan
Crea un documento di pianificazione release:

```markdown
# Release Plan v2.3.0 - Q4 2024

## Timeline
- **Sprint 1 (Nov 1-15)**: Feature Development
- **Sprint 2 (Nov 16-30)**: Feature Integration  
- **Sprint 3 (Dec 1-15)**: Testing & Bug Fixes
- **Sprint 4 (Dec 16-31)**: Release Preparation

## Features Pianificate
1. **User Authentication Redesign** (Team Alpha)
2. **Payment Gateway Integration** (Team Beta) 
3. **Mobile App Performance** (Team Gamma)

## Dependencies
- External API updates
- Database migrations
- Security audit completion
```

### 1.2 Setup Feature Branches
```bash
# Team Alpha - Authentication
git flow feature start auth-redesign-v2

# Team Beta - Payment Gateway  
git flow feature start payment-gateway-stripe

# Team Gamma - Mobile Performance
git flow feature start mobile-performance-boost
```

### 1.3 Sprint Planning Integration
```bash
# Crea milestone e labels
git tag -a "sprint-1-start" -m "Sprint 1 Development Start"
git tag -a "feature-freeze" -m "Feature Freeze Deadline"
git tag -a "release-candidate" -m "Release Candidate"
```

## Parte 2: Sviluppo Parallelo Features (45 minuti)

### 2.1 Feature Team Alpha - Authentication
```bash
# Switch al branch feature
git checkout feature/auth-redesign-v2

# Simula sviluppo authentication
mkdir -p src/auth/v2
cat > src/auth/v2/auth-service.js << 'EOF'
class AuthServiceV2 {
    constructor() {
        this.provider = 'oauth2';
        this.version = '2.0';
    }

    async authenticate(credentials) {
        // New OAuth 2.0 implementation
        const token = await this.generateToken(credentials);
        return this.validateToken(token);
    }

    async generateToken(credentials) {
        // Enhanced security with JWT
        return {
            token: `jwt_${Date.now()}`,
            expires: Date.now() + 3600000,
            scope: credentials.scope
        };
    }

    async validateToken(token) {
        // Multi-factor validation
        return {
            valid: true,
            user: token.user,
            permissions: token.scope
        };
    }
}

module.exports = AuthServiceV2;
EOF

# Aggiungi test per authentication
mkdir -p tests/auth
cat > tests/auth/auth-service.test.js << 'EOF'
const AuthServiceV2 = require('../../src/auth/v2/auth-service');

describe('AuthServiceV2', () => {
    let authService;

    beforeEach(() => {
        authService = new AuthServiceV2();
    });

    test('should authenticate user with valid credentials', async () => {
        const credentials = {
            username: 'testuser',
            password: 'securepass',
            scope: ['read', 'write']
        };

        const result = await authService.authenticate(credentials);
        expect(result.valid).toBe(true);
        expect(result.permissions).toEqual(['read', 'write']);
    });

    test('should generate valid JWT token', async () => {
        const credentials = { scope: ['admin'] };
        const token = await authService.generateToken(credentials);
        
        expect(token.token).toMatch(/^jwt_/);
        expect(token.expires).toBeGreaterThan(Date.now());
    });
});
EOF

# Commit incrementali
git add src/auth/v2/
git commit -m "feat(auth): implement OAuth 2.0 service foundation

- Add AuthServiceV2 class with JWT support
- Implement token generation and validation
- Add multi-factor authentication support"

git add tests/auth/
git commit -m "test(auth): add comprehensive test suite for AuthServiceV2

- Test authentication flow
- Test token generation and validation
- Cover edge cases and error scenarios"

# Aggiungi documentazione
mkdir -p docs/auth
cat > docs/auth/oauth2-migration.md << 'EOF'
# OAuth 2.0 Migration Guide

## Overview
Migration from legacy authentication to OAuth 2.0 with enhanced security.

## Breaking Changes
- Legacy session tokens deprecated
- New JWT format required
- Multi-factor authentication mandatory

## Implementation Timeline
- Phase 1: Parallel implementation
- Phase 2: Gradual migration
- Phase 3: Legacy deprecation
EOF

git add docs/auth/
git commit -m "docs(auth): add OAuth 2.0 migration guide

- Document breaking changes and migration path
- Add implementation timeline
- Include security considerations"
```

### 2.2 Feature Team Beta - Payment Gateway
```bash
# Switch al branch feature payment
git checkout feature/payment-gateway-stripe

# Simula integrazione Stripe
mkdir -p src/payment/stripe
cat > src/payment/stripe/stripe-service.js << 'EOF'
const stripe = require('stripe');

class StripePaymentService {
    constructor(apiKey) {
        this.stripe = stripe(apiKey);
        this.webhook_secret = process.env.STRIPE_WEBHOOK_SECRET;
    }

    async createPaymentIntent(amount, currency = 'eur') {
        try {
            const paymentIntent = await this.stripe.paymentIntents.create({
                amount: amount * 100, // Stripe uses cents
                currency: currency,
                metadata: {
                    integration_check: 'accept_a_payment',
                    timestamp: Date.now()
                }
            });

            return {
                clientSecret: paymentIntent.client_secret,
                id: paymentIntent.id,
                status: paymentIntent.status
            };
        } catch (error) {
            throw new PaymentError(`Failed to create payment intent: ${error.message}`);
        }
    }

    async confirmPayment(paymentIntentId, paymentMethod) {
        try {
            const paymentIntent = await this.stripe.paymentIntents.confirm(
                paymentIntentId,
                { payment_method: paymentMethod }
            );

            return {
                status: paymentIntent.status,
                amount: paymentIntent.amount_received,
                currency: paymentIntent.currency
            };
        } catch (error) {
            throw new PaymentError(`Payment confirmation failed: ${error.message}`);
        }
    }

    async handleWebhook(payload, signature) {
        try {
            const event = this.stripe.webhooks.constructEvent(
                payload, signature, this.webhook_secret
            );

            switch (event.type) {
                case 'payment_intent.succeeded':
                    return this.handlePaymentSuccess(event.data.object);
                case 'payment_intent.payment_failed':
                    return this.handlePaymentFailure(event.data.object);
                default:
                    console.log(`Unhandled event type: ${event.type}`);
            }
        } catch (error) {
            throw new WebhookError(`Webhook handling failed: ${error.message}`);
        }
    }

    async handlePaymentSuccess(paymentIntent) {
        // Update order status, send confirmation
        return {
            processed: true,
            orderId: paymentIntent.metadata.order_id,
            amount: paymentIntent.amount_received
        };
    }

    async handlePaymentFailure(paymentIntent) {
        // Handle failed payment, notify user
        return {
            processed: false,
            reason: paymentIntent.last_payment_error?.message,
            retryable: true
        };
    }
}

class PaymentError extends Error {
    constructor(message) {
        super(message);
        this.name = 'PaymentError';
    }
}

class WebhookError extends Error {
    constructor(message) {
        super(message);
        this.name = 'WebhookError';
    }
}

module.exports = { StripePaymentService, PaymentError, WebhookError };
EOF

# Aggiungi configurazione ambiente
cat > src/payment/config/stripe-config.js << 'EOF'
const stripeConfig = {
    development: {
        publishableKey: process.env.STRIPE_DEV_PUBLISHABLE_KEY,
        secretKey: process.env.STRIPE_DEV_SECRET_KEY,
        webhookSecret: process.env.STRIPE_DEV_WEBHOOK_SECRET
    },
    staging: {
        publishableKey: process.env.STRIPE_STAGING_PUBLISHABLE_KEY,
        secretKey: process.env.STRIPE_STAGING_SECRET_KEY,
        webhookSecret: process.env.STRIPE_STAGING_WEBHOOK_SECRET
    },
    production: {
        publishableKey: process.env.STRIPE_PROD_PUBLISHABLE_KEY,
        secretKey: process.env.STRIPE_PROD_SECRET_KEY,
        webhookSecret: process.env.STRIPE_PROD_WEBHOOK_SECRET
    }
};

module.exports = stripeConfig;
EOF

git add src/payment/
git commit -m "feat(payment): implement Stripe payment gateway integration

- Add StripePaymentService with payment intent creation
- Implement payment confirmation and webhook handling
- Add environment-specific configuration
- Include error handling and custom exceptions"

# Aggiungi test
mkdir -p tests/payment
cat > tests/payment/stripe-service.test.js << 'EOF'
const { StripePaymentService, PaymentError } = require('../../src/payment/stripe/stripe-service');

// Mock Stripe
jest.mock('stripe', () => {
    return jest.fn().mockImplementation(() => ({
        paymentIntents: {
            create: jest.fn(),
            confirm: jest.fn()
        },
        webhooks: {
            constructEvent: jest.fn()
        }
    }));
});

describe('StripePaymentService', () => {
    let paymentService;
    let mockStripe;

    beforeEach(() => {
        paymentService = new StripePaymentService('test_key');
        mockStripe = paymentService.stripe;
    });

    describe('createPaymentIntent', () => {
        test('should create payment intent successfully', async () => {
            mockStripe.paymentIntents.create.mockResolvedValue({
                client_secret: 'pi_test_client_secret',
                id: 'pi_test_123',
                status: 'requires_payment_method'
            });

            const result = await paymentService.createPaymentIntent(99.99, 'eur');

            expect(result).toEqual({
                clientSecret: 'pi_test_client_secret',
                id: 'pi_test_123',
                status: 'requires_payment_method'
            });
            expect(mockStripe.paymentIntents.create).toHaveBeenCalledWith({
                amount: 9999,
                currency: 'eur',
                metadata: expect.objectContaining({
                    integration_check: 'accept_a_payment'
                })
            });
        });

        test('should handle payment intent creation failure', async () => {
            mockStripe.paymentIntents.create.mockRejectedValue(
                new Error('Invalid amount')
            );

            await expect(
                paymentService.createPaymentIntent(-10)
            ).rejects.toThrow(PaymentError);
        });
    });

    describe('confirmPayment', () => {
        test('should confirm payment successfully', async () => {
            mockStripe.paymentIntents.confirm.mockResolvedValue({
                status: 'succeeded',
                amount_received: 9999,
                currency: 'eur'
            });

            const result = await paymentService.confirmPayment(
                'pi_test_123', 
                'pm_card_visa'
            );

            expect(result).toEqual({
                status: 'succeeded',
                amount: 9999,
                currency: 'eur'
            });
        });
    });
});
EOF

git add tests/payment/
git commit -m "test(payment): add comprehensive test suite for Stripe integration

- Test payment intent creation and confirmation
- Mock Stripe API responses
- Cover error scenarios and edge cases
- Add webhook testing setup"
```

### 2.3 Feature Team Gamma - Mobile Performance
```bash
# Switch al branch feature mobile
git checkout feature/mobile-performance-boost

# Simula ottimizzazioni mobile
mkdir -p src/mobile/performance
cat > src/mobile/performance/cache-manager.js << 'EOF'
class MobileCacheManager {
    constructor(options = {}) {
        this.maxCacheSize = options.maxCacheSize || 50 * 1024 * 1024; // 50MB
        this.ttl = options.ttl || 3600000; // 1 hour
        this.cache = new Map();
        this.cacheStats = {
            hits: 0,
            misses: 0,
            evictions: 0
        };
    }

    set(key, value, customTtl = null) {
        const ttl = customTtl || this.ttl;
        const entry = {
            value,
            timestamp: Date.now(),
            ttl,
            size: this.calculateSize(value)
        };

        // Check if we need to evict entries
        this.evictIfNeeded(entry.size);

        this.cache.set(key, entry);
        this.cleanupExpired();
    }

    get(key) {
        const entry = this.cache.get(key);
        
        if (!entry) {
            this.cacheStats.misses++;
            return null;
        }

        // Check if entry has expired
        if (Date.now() - entry.timestamp > entry.ttl) {
            this.cache.delete(key);
            this.cacheStats.misses++;
            return null;
        }

        this.cacheStats.hits++;
        return entry.value;
    }

    evictIfNeeded(newEntrySize) {
        const currentSize = this.getCurrentCacheSize();
        
        if (currentSize + newEntrySize > this.maxCacheSize) {
            // LRU eviction strategy
            const entries = Array.from(this.cache.entries())
                .sort((a, b) => a[1].timestamp - b[1].timestamp);

            let freedSpace = 0;
            for (const [key, entry] of entries) {
                this.cache.delete(key);
                freedSpace += entry.size;
                this.cacheStats.evictions++;
                
                if (freedSpace >= newEntrySize) break;
            }
        }
    }

    getCurrentCacheSize() {
        return Array.from(this.cache.values())
            .reduce((total, entry) => total + entry.size, 0);
    }

    calculateSize(value) {
        return JSON.stringify(value).length * 2; // Rough estimation
    }

    cleanupExpired() {
        const now = Date.now();
        for (const [key, entry] of this.cache.entries()) {
            if (now - entry.timestamp > entry.ttl) {
                this.cache.delete(key);
            }
        }
    }

    getCacheStats() {
        const hitRate = this.cacheStats.hits / 
            (this.cacheStats.hits + this.cacheStats.misses) * 100;
        
        return {
            ...this.cacheStats,
            hitRate: isNaN(hitRate) ? 0 : hitRate.toFixed(2),
            currentSize: this.getCurrentCacheSize(),
            entryCount: this.cache.size
        };
    }

    clear() {
        this.cache.clear();
        this.cacheStats = { hits: 0, misses: 0, evictions: 0 };
    }
}

module.exports = MobileCacheManager;
EOF

# Aggiungi ottimizzazioni immagini
cat > src/mobile/performance/image-optimizer.js << 'EOF'
class MobileImageOptimizer {
    constructor() {
        this.supportedFormats = ['webp', 'jpeg', 'png'];
        this.qualitySettings = {
            high: 85,
            medium: 70,
            low: 50
        };
    }

    async optimizeForMobile(imageUrl, options = {}) {
        const {
            targetWidth = 800,
            quality = 'medium',
            format = 'webp',
            progressive = true
        } = options;

        try {
            // Simulated image optimization
            const optimizedImage = {
                originalUrl: imageUrl,
                optimizedUrl: this.generateOptimizedUrl(imageUrl, options),
                reduction: this.calculateReduction(options),
                format: format,
                dimensions: {
                    width: targetWidth,
                    height: Math.round(targetWidth * 0.75) // Assume 4:3 ratio
                }
            };

            return optimizedImage;
        } catch (error) {
            throw new Error(`Image optimization failed: ${error.message}`);
        }
    }

    generateOptimizedUrl(originalUrl, options) {
        const params = new URLSearchParams({
            w: options.targetWidth || 800,
            q: this.qualitySettings[options.quality] || 70,
            f: options.format || 'webp',
            auto: 'compress'
        });

        return `${originalUrl}?${params.toString()}`;
    }

    calculateReduction(options) {
        const quality = options.quality || 'medium';
        const format = options.format || 'webp';
        
        let reduction = 0;
        
        // Format savings
        if (format === 'webp') reduction += 25;
        else if (format === 'jpeg') reduction += 10;
        
        // Quality savings
        if (quality === 'low') reduction += 40;
        else if (quality === 'medium') reduction += 25;
        else if (quality === 'high') reduction += 15;
        
        return Math.min(reduction, 80); // Max 80% reduction
    }

    async createResponsiveSet(imageUrl, sizes = [320, 640, 800, 1200]) {
        const responsiveSet = await Promise.all(
            sizes.map(async (width) => {
                const optimized = await this.optimizeForMobile(imageUrl, {
                    targetWidth: width,
                    quality: width <= 640 ? 'medium' : 'high'
                });
                
                return {
                    width,
                    url: optimized.optimizedUrl,
                    descriptor: `${width}w`
                };
            })
        );

        return {
            srcset: responsiveSet.map(img => `${img.url} ${img.descriptor}`).join(', '),
            sizes: '(max-width: 640px) 100vw, (max-width: 1200px) 50vw, 33vw',
            images: responsiveSet
        };
    }
}

module.exports = MobileImageOptimizer;
EOF

git add src/mobile/performance/
git commit -m "feat(mobile): implement advanced caching and image optimization

- Add MobileCacheManager with LRU eviction strategy
- Implement intelligent cache size management
- Add MobileImageOptimizer for responsive images
- Include cache statistics and performance monitoring"

# Aggiungi test performance
mkdir -p tests/mobile
cat > tests/mobile/cache-manager.test.js << 'EOF'
const MobileCacheManager = require('../../src/mobile/performance/cache-manager');

describe('MobileCacheManager', () => {
    let cacheManager;

    beforeEach(() => {
        cacheManager = new MobileCacheManager({
            maxCacheSize: 1024, // 1KB for testing
            ttl: 1000 // 1 second
        });
    });

    test('should store and retrieve values', () => {
        cacheManager.set('key1', 'value1');
        expect(cacheManager.get('key1')).toBe('value1');
    });

    test('should return null for non-existent keys', () => {
        expect(cacheManager.get('nonexistent')).toBeNull();
    });

    test('should handle TTL expiration', (done) => {
        cacheManager.set('key1', 'value1', 100); // 100ms TTL
        
        setTimeout(() => {
            expect(cacheManager.get('key1')).toBeNull();
            done();
        }, 150);
    });

    test('should evict entries when cache is full', () => {
        // Fill cache beyond limit
        for (let i = 0; i < 10; i++) {
            cacheManager.set(`key${i}`, 'x'.repeat(200)); // Large values
        }

        const stats = cacheManager.getCacheStats();
        expect(stats.evictions).toBeGreaterThan(0);
    });

    test('should track cache statistics', () => {
        cacheManager.set('key1', 'value1');
        cacheManager.get('key1'); // hit
        cacheManager.get('key2'); // miss

        const stats = cacheManager.getCacheStats();
        expect(stats.hits).toBe(1);
        expect(stats.misses).toBe(1);
        expect(parseFloat(stats.hitRate)).toBe(50.00);
    });
});
EOF

git add tests/mobile/
git commit -m "test(mobile): add comprehensive cache manager test suite

- Test basic cache operations
- Test TTL expiration behavior
- Test LRU eviction strategy
- Test cache statistics tracking"
```

## Parte 3: Integration e Testing (30 minuti)

### 3.1 Pre-Release Integration
```bash
# Torna su develop per integrazioni
git checkout develop

# Merge sequenziale delle feature (simulate review)
git flow feature finish auth-redesign-v2
git flow feature finish payment-gateway-stripe
git flow feature finish mobile-performance-boost

# Avvia release branch
git flow release start 2.3.0
```

### 3.2 Testing e Bug Fixes
```bash
# Sul release branch, aggiungi integration tests
mkdir -p tests/integration
cat > tests/integration/e2e-release.test.js << 'EOF'
const request = require('supertest');
const app = require('../../src/app');

describe('Release 2.3.0 Integration Tests', () => {
    describe('Authentication Flow', () => {
        test('should authenticate with new OAuth2 system', async () => {
            const response = await request(app)
                .post('/api/auth/login')
                .send({
                    username: 'testuser',
                    password: 'password123'
                });

            expect(response.status).toBe(200);
            expect(response.body.token).toMatch(/^jwt_/);
        });
    });

    describe('Payment Processing', () => {
        test('should process payment with Stripe', async () => {
            const response = await request(app)
                .post('/api/payments/create-intent')
                .send({
                    amount: 99.99,
                    currency: 'eur'
                });

            expect(response.status).toBe(200);
            expect(response.body.clientSecret).toBeDefined();
        });
    });

    describe('Mobile Performance', () => {
        test('should return optimized images for mobile', async () => {
            const response = await request(app)
                .get('/api/images/optimize')
                .query({
                    url: 'https://example.com/image.jpg',
                    width: 640
                });

            expect(response.status).toBe(200);
            expect(response.body.optimizedUrl).toContain('w=640');
        });
    });
});
EOF

# Simula fix di bug trovati durante testing
cat > src/shared/utils/validation.js << 'EOF'
class ValidationUtils {
    static validatePaymentAmount(amount) {
        if (typeof amount !== 'number' || amount <= 0) {
            throw new Error('Payment amount must be a positive number');
        }
        if (amount > 999999) {
            throw new Error('Payment amount too large');
        }
        return true;
    }

    static validateImageUrl(url) {
        const urlPattern = /^https?:\/\/.+\.(jpg|jpeg|png|gif|webp)$/i;
        if (!urlPattern.test(url)) {
            throw new Error('Invalid image URL format');
        }
        return true;
    }

    static validateCacheKey(key) {
        if (typeof key !== 'string' || key.length === 0) {
            throw new Error('Cache key must be a non-empty string');
        }
        if (key.length > 250) {
            throw new Error('Cache key too long');
        }
        return true;
    }
}

module.exports = ValidationUtils;
EOF

git add tests/integration/ src/shared/
git commit -m "test: add comprehensive integration tests for v2.3.0

- Add E2E tests for authentication, payments, and mobile features
- Add validation utilities for improved error handling
- Ensure cross-feature compatibility"

# Simula hotfix durante release
echo "console.log('Debug mode disabled for production');" > src/shared/debug.js
git add src/shared/debug.js
git commit -m "fix: disable debug mode in production build

- Remove debug logging from production bundle
- Improve application performance
- Address security concern about information disclosure"
```

## Parte 4: Release Deployment (20 minuti)

### 4.1 Pre-Production Testing
```bash
# Aggiungi deployment scripts
mkdir -p deployment/scripts
cat > deployment/scripts/pre-release-checks.sh << 'EOF'
#!/bin/bash

echo "🔍 Running pre-release validation checks..."

# Database migration check
echo "Checking database migrations..."
npm run db:check-migrations

# Security audit
echo "Running security audit..."
npm audit --audit-level moderate

# Performance tests
echo "Running performance benchmarks..."
npm run test:performance

# Integration tests
echo "Running integration test suite..."
npm run test:integration

# Bundle size analysis
echo "Analyzing bundle size..."
npm run build:analyze

echo "✅ Pre-release checks completed"
EOF

chmod +x deployment/scripts/pre-release-checks.sh

# Aggiungi changelog
cat > CHANGELOG.md << 'EOF'
# Changelog

## [2.3.0] - 2024-12-15

### Added
- **Authentication**: New OAuth 2.0 implementation with JWT support
- **Payments**: Stripe payment gateway integration with webhook support
- **Mobile**: Advanced caching system and image optimization
- **Security**: Multi-factor authentication support
- **Performance**: Responsive image delivery system

### Changed
- Migrated from legacy session-based auth to OAuth 2.0
- Improved mobile app performance by 40%
- Enhanced payment processing reliability

### Security
- Added secure token validation
- Implemented webhook signature verification
- Enhanced user credential protection

### Performance
- Reduced mobile bundle size by 25%
- Implemented intelligent image caching
- Added progressive image loading
EOF

git add deployment/ CHANGELOG.md
git commit -m "release: prepare v2.3.0 deployment configuration

- Add pre-release validation scripts
- Include comprehensive changelog
- Setup deployment automation"

# Finisci release
git flow release finish 2.3.0

# Tag e push
git tag -a v2.3.0 -m "Release v2.3.0 - Enhanced Authentication, Payments & Mobile Performance"
```

### 4.2 Post-Release Monitoring
```bash
# Setup monitoring e rollback plan
mkdir -p deployment/monitoring
cat > deployment/monitoring/release-monitor.js << 'EOF'
const monitoring = {
    healthChecks: [
        {
            name: 'Authentication Service',
            endpoint: '/api/health/auth',
            threshold: 200,
            timeout: 5000
        },
        {
            name: 'Payment Gateway', 
            endpoint: '/api/health/payments',
            threshold: 200,
            timeout: 3000
        },
        {
            name: 'Mobile API',
            endpoint: '/api/health/mobile',
            threshold: 200,
            timeout: 2000
        }
    ],

    errorThresholds: {
        errorRate: 0.05, // 5%
        responseTime: 2000, // 2 seconds
        uptime: 0.99 // 99%
    },

    rollbackTriggers: [
        'auth_failure_rate > 0.1',
        'payment_failure_rate > 0.02',
        'mobile_crash_rate > 0.05',
        'avg_response_time > 5000'
    ]
};

module.exports = monitoring;
EOF

cat > deployment/rollback-plan.md << 'EOF'
# Emergency Rollback Plan v2.3.0

## Trigger Conditions
- Authentication failure rate > 10%
- Payment processing failure rate > 2%
- Mobile app crash rate > 5%
- Average response time > 5 seconds

## Rollback Procedure

### 1. Immediate Actions (0-5 minutes)
```bash
# Switch traffic to previous version
kubectl set image deployment/app app=app:v2.2.1

# Revert database migrations if needed
npm run db:rollback --to=v2.2.1
```

### 2. Validation (5-10 minutes)
- Check health endpoints
- Verify payment processing
- Test authentication flow
- Monitor error rates

### 3. Communication (10-15 minutes)
- Notify stakeholders
- Update status page
- Document incident

## Recovery Testing
After rollback, test:
- User authentication
- Payment processing
- Mobile app functionality
- Data integrity
EOF

git add deployment/monitoring/ deployment/rollback-plan.md
git commit -m "ops: add comprehensive monitoring and rollback procedures

- Setup health check monitoring for all services
- Define error thresholds and rollback triggers
- Create emergency rollback procedures
- Add post-deployment validation steps"
```

## Parte 5: Post-Release Analysis (15 minuti)

### 5.1 Release Metrics
Crea un report di analisi:

```markdown
# Release 2.3.0 - Post-Release Analysis

## Delivery Metrics
- **Planning Time**: 2 settimane
- **Development Time**: 6 settimane  
- **Testing Time**: 2 settimane
- **Total Lead Time**: 10 settimane
- **Team Efficiency**: 3 feature teams in parallelo

## Quality Metrics
- **Bug Escape Rate**: 0.2% (2 bugs in production)
- **Rollback Required**: No
- **Performance Impact**: +15% improvement
- **Security Issues**: 0

## Team Collaboration
- **Merge Conflicts**: 3 (risolti in < 2 ore)
- **Code Review Coverage**: 100%
- **Documentation Updated**: Yes
- **Knowledge Transfer**: Complete

## Lessons Learned
1. **Git Flow Efficace**: Branching strategy ha facilitato sviluppo parallelo
2. **Testing Integration**: Testing automatizzato ha individuato 95% dei bug
3. **Communication**: Daily sync tra team ha ridotto conflitti
4. **Release Planning**: Timeline realistic ha evitato crunch

## Recommendations
1. Aumentare automated testing coverage al 90%
2. Implementare feature flags per deployment graduale
3. Aggiungere monitoring proattivo
4. Migliorare documentation automation
```

### 5.2 Repository Cleanup
```bash
# Cleanup branch residui
git branch -d feature/auth-redesign-v2
git branch -d feature/payment-gateway-stripe  
git branch -d feature/mobile-performance-boost
git branch -d release/2.3.0

# Cleanup tag
git tag -d sprint-1-start feature-freeze release-candidate

# Archive release artifacts
mkdir -p archives/v2.3.0
git archive --format=tar.gz --prefix=release-v2.3.0/ v2.3.0 > archives/v2.3.0/source-code.tar.gz
```

## Deliverables

### 1. Repository Stato Finale
- **Main branch**: Codice v2.3.0 in produzione
- **Develop branch**: Preparato per v2.4.0
- **Tag**: v2.3.0 con changelog completo
- **Documentation**: Aggiornata per nuove feature

### 2. Artifacts Prodotti
- [ ] Release plan completo
- [ ] 3 feature branch completamente implementate
- [ ] Integration test suite
- [ ] Deployment automation
- [ ] Monitoring e rollback procedures
- [ ] Post-release analysis

### 3. Git Flow Workflow Documentato
- [ ] Feature development in parallelo
- [ ] Release branch management
- [ ] Hotfix procedures
- [ ] Tag e versioning strategy

### 4. Quality Assurance
- [ ] Code review completo
- [ ] Automated testing
- [ ] Security validation
- [ ] Performance benchmarking

## Criteri di Valutazione

### Eccellente (90-100%)
- Tutte le feature implementate correttamente
- Git Flow seguito perfettamente
- Zero conflitti non risolti
- Documentation completa
- Monitoring implementato

### Buono (70-89%)
- Feature implementate con minor issues
- Git Flow generalmente seguito
- Conflitti risolti efficientemente
- Documentation adeguata

### Sufficiente (60-69%)
- Feature base implementate
- Branching strategy utilizzata
- Alcuni conflitti o problemi
- Documentation minima

### Tempo Stimato
**3-4 ore** per completare l'intero esercizio, suddiviso in:
- 30 min: Planning e setup
- 90 min: Development features
- 60 min: Integration e testing
- 30 min: Deployment e monitoring
- 30 min: Analysis e cleanup

## Note per il Formatore

### Supporto Durante l'Esercizio
1. **Setup Phase**: Aiutare con configurazione Git Flow
2. **Development**: Monitorare sviluppo parallelo
3. **Integration**: Assistere con merge conflicts
4. **Deployment**: Validare deployment procedures

### Punti di Discussione
1. **Branching Strategy**: Confronto Git Flow vs GitHub Flow
2. **Merge vs Rebase**: Quando usare ogni strategia
3. **Release Planning**: Come coordinare team multipli
4. **Quality Gates**: Testing e validation strategies

### Varianti Avanzate
- **Hotfix Simulation**: Aggiungi emergency fix durante release
- **Multi-Environment**: Deploy staging → production
- **Feature Flags**: Implementa progressive rollout
- **Security Audit**: Aggiungi security scanning

Questo esercizio simula un ambiente enterprise realistico e insegna la gestione completa di release complex con Git Flow.
