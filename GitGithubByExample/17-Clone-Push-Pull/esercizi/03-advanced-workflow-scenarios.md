# Esercizio 03: Advanced Workflow Scenarios

## 🎯 Obiettivo
Padroneggiare scenari avanzati di Clone, Push e Pull in contesti enterprise e progetti distribuiti, incluso gestione di multiple remote, branching strategies complesse e operazioni di recupero.

## ⏱️ Durata Stimata
**60-90 minuti**

## 📋 Prerequisiti
- Padronanza di operazioni Git base
- Account GitHub con SSH configurato
- Conoscenza di branching e merging
- Esperienza con conflict resolution

## 🚀 Scenario
Sei Senior DevOps Engineer in un'azienda fintech che gestisce multiple ambiente (development, staging, production) e coordina contribuzioni da team interni, contractor esterni e community open source.

## 📝 Task Sequence

### Task 1: Multi-Environment Repository Setup (Enterprise Scenario)

#### 1.1 Inizializzazione Progetto FinTech
```bash
# Crea struttura progetto enterprise
mkdir fintech-payment-system
cd fintech-payment-system

# Inizializza con struttura enterprise
git init
git branch -M main

# Crea struttura completa
mkdir -p {src/{api,frontend,shared},tests/{unit,integration,e2e},docs,config/{dev,staging,prod},scripts}

# Setup documentazione enterprise
cat > README.md << 'EOF'
# FinTech Payment System

## Architecture Overview
Enterprise-grade payment processing system with microservices architecture.

## Environments
- **Development**: Local development environment
- **Staging**: Pre-production testing environment  
- **Production**: Live production environment

## Security Compliance
- PCI DSS compliant
- SOX compliance for financial reporting
- GDPR compliant data handling

## Getting Started
See [Development Setup](docs/development-setup.md) for local environment configuration.
EOF

# API Core Module
cat > src/api/payment-processor.js << 'EOF'
class PaymentProcessor {
  constructor(config) {
    this.config = config;
    this.environment = config.environment || 'development';
  }

  async processPayment(paymentData) {
    // Validate payment data
    if (!this.validatePaymentData(paymentData)) {
      throw new Error('Invalid payment data');
    }

    // Environment-specific processing
    switch (this.environment) {
      case 'production':
        return await this.processProductionPayment(paymentData);
      case 'staging':
        return await this.processStagingPayment(paymentData);
      default:
        return await this.processTestPayment(paymentData);
    }
  }

  validatePaymentData(data) {
    return data && data.amount && data.currency && data.cardToken;
  }

  async processProductionPayment(data) {
    // Production payment processing with full security
    console.log('Processing production payment:', data.amount);
    return { status: 'success', transactionId: this.generateTransactionId() };
  }

  async processStagingPayment(data) {
    // Staging environment with logging
    console.log('Staging payment:', data.amount, data.currency);
    return { status: 'success', transactionId: 'staging_' + Date.now() };
  }

  async processTestPayment(data) {
    // Development/test environment
    return { status: 'test_success', transactionId: 'test_' + Date.now() };
  }

  generateTransactionId() {
    return 'prod_' + Date.now() + '_' + Math.random().toString(36).substring(7);
  }
}

module.exports = PaymentProcessor;
EOF

# Frontend Core
cat > src/frontend/payment-form.js << 'EOF'
class PaymentForm {
  constructor(apiEndpoint) {
    this.apiEndpoint = apiEndpoint;
    this.setupEventListeners();
  }

  setupEventListeners() {
    document.addEventListener('DOMContentLoaded', () => {
      const form = document.getElementById('payment-form');
      if (form) {
        form.addEventListener('submit', (e) => this.handleSubmit(e));
      }
    });
  }

  async handleSubmit(event) {
    event.preventDefault();
    
    const formData = new FormData(event.target);
    const paymentData = {
      amount: formData.get('amount'),
      currency: formData.get('currency'),
      cardToken: formData.get('cardToken')
    };

    try {
      const response = await fetch(`${this.apiEndpoint}/process-payment`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(paymentData)
      });

      const result = await response.json();
      this.displayResult(result);
    } catch (error) {
      this.displayError(error.message);
    }
  }

  displayResult(result) {
    console.log('Payment result:', result);
    // Update UI with result
  }

  displayError(error) {
    console.error('Payment error:', error);
    // Display error to user
  }
}

// Environment-specific initialization
const API_ENDPOINTS = {
  development: 'http://localhost:3000/api',
  staging: 'https://staging-api.fintech.com/api',
  production: 'https://api.fintech.com/api'
};

const environment = process.env.NODE_ENV || 'development';
new PaymentForm(API_ENDPOINTS[environment]);
EOF

# Configuration files
cat > config/dev/app.config.js << 'EOF'
module.exports = {
  environment: 'development',
  database: {
    host: 'localhost',
    port: 5432,
    name: 'fintech_dev'
  },
  api: {
    port: 3000,
    ssl: false
  },
  logging: {
    level: 'debug'
  }
};
EOF

cat > config/staging/app.config.js << 'EOF'
module.exports = {
  environment: 'staging',
  database: {
    host: 'staging-db.fintech.com',
    port: 5432,
    name: 'fintech_staging'
  },
  api: {
    port: 443,
    ssl: true
  },
  logging: {
    level: 'info'
  }
};
EOF

cat > config/prod/app.config.js << 'EOF'
module.exports = {
  environment: 'production',
  database: {
    host: 'prod-db.fintech.com',
    port: 5432,
    name: 'fintech_production'
  },
  api: {
    port: 443,
    ssl: true
  },
  logging: {
    level: 'error'
  },
  security: {
    encryptionKey: process.env.ENCRYPTION_KEY,
    pciCompliance: true
  }
};
EOF

# Test suites
cat > tests/unit/payment-processor.test.js << 'EOF'
const PaymentProcessor = require('../../src/api/payment-processor');

describe('PaymentProcessor', () => {
  let processor;

  beforeEach(() => {
    processor = new PaymentProcessor({ environment: 'test' });
  });

  test('should validate payment data correctly', () => {
    const validData = { amount: 100, currency: 'USD', cardToken: 'abc123' };
    expect(processor.validatePaymentData(validData)).toBe(true);
  });

  test('should reject invalid payment data', () => {
    const invalidData = { amount: 100 }; // missing currency and cardToken
    expect(processor.validatePaymentData(invalidData)).toBe(false);
  });

  test('should process test payment correctly', async () => {
    const paymentData = { amount: 100, currency: 'USD', cardToken: 'test123' };
    const result = await processor.processTestPayment(paymentData);
    expect(result.status).toBe('test_success');
    expect(result.transactionId).toContain('test_');
  });
});
EOF

git add .
git commit -m "feat: initialize FinTech payment system

- Add enterprise-grade payment processing core
- Implement environment-specific configurations
- Create frontend payment form with API integration
- Add comprehensive test suite for payment validation
- Setup multi-environment architecture (dev/staging/prod)
- Implement PCI DSS compliance framework"
```

#### 1.2 Setup Multiple Remote Environments
```bash
# Aggiungi multiple remote per ambienti diversi
git remote add origin git@github.com:USERNAME/fintech-payment-system.git
git remote add staging git@github.com:COMPANY/fintech-staging.git
git remote add production git@github.com:COMPANY/fintech-production.git

# Verifica setup remote
git remote -v

# Push iniziale su origin (development)
git push -u origin main

# Crea e configura branch per staging
git checkout -b staging
git push -u staging staging

# Crea e configura branch per production
git checkout -b production
git push -u production production

# Torna su main
git checkout main
```

### Task 2: Complex Feature Development with Multiple Contributors

#### 2.1 Simulate Multiple Developer Workflow
```bash
# Simula sviluppatore 1: Feature payment validation
git checkout -b feature/enhanced-payment-validation

# Migliora validazione pagamenti
cat > src/shared/validation-utils.js << 'EOF'
class ValidationUtils {
  static validateCreditCard(cardNumber) {
    // Implementa algoritmo Luhn per validazione carte di credito
    const sanitized = cardNumber.replace(/\D/g, '');
    
    if (sanitized.length < 13 || sanitized.length > 19) {
      return false;
    }

    let sum = 0;
    let isEven = false;

    for (let i = sanitized.length - 1; i >= 0; i--) {
      let digit = parseInt(sanitized[i]);

      if (isEven) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }

      sum += digit;
      isEven = !isEven;
    }

    return sum % 10 === 0;
  }

  static validateAmount(amount, currency) {
    const numericAmount = parseFloat(amount);
    
    if (isNaN(numericAmount) || numericAmount <= 0) {
      return { valid: false, error: 'Amount must be a positive number' };
    }

    // Currency-specific validations
    const currencyRules = {
      'USD': { min: 0.01, max: 10000 },
      'EUR': { min: 0.01, max: 8500 },
      'GBP': { min: 0.01, max: 7500 }
    };

    const rules = currencyRules[currency];
    if (!rules) {
      return { valid: false, error: 'Unsupported currency' };
    }

    if (numericAmount < rules.min || numericAmount > rules.max) {
      return { 
        valid: false, 
        error: `Amount must be between ${rules.min} and ${rules.max} ${currency}` 
      };
    }

    return { valid: true };
  }

  static validateBillingAddress(address) {
    const required = ['street', 'city', 'postalCode', 'country'];
    const missing = required.filter(field => !address[field]);
    
    if (missing.length > 0) {
      return { valid: false, error: `Missing required fields: ${missing.join(', ')}` };
    }

    // Postal code validation by country
    const postalCodePatterns = {
      'US': /^\d{5}(-\d{4})?$/,
      'UK': /^[A-Z]{1,2}\d[A-Z\d]? ?\d[A-Z]{2}$/i,
      'CA': /^[A-Z]\d[A-Z] ?\d[A-Z]\d$/i
    };

    const pattern = postalCodePatterns[address.country];
    if (pattern && !pattern.test(address.postalCode)) {
      return { valid: false, error: 'Invalid postal code format' };
    }

    return { valid: true };
  }
}

module.exports = ValidationUtils;
EOF

# Aggiorna payment processor per usare nuove validazioni
cat > src/api/enhanced-payment-processor.js << 'EOF'
const PaymentProcessor = require('./payment-processor');
const ValidationUtils = require('../shared/validation-utils');

class EnhancedPaymentProcessor extends PaymentProcessor {
  constructor(config) {
    super(config);
    this.fraudDetection = config.fraudDetection || false;
  }

  validatePaymentData(data) {
    // Basic validation
    if (!super.validatePaymentData(data)) {
      return false;
    }

    // Enhanced validation
    if (!ValidationUtils.validateCreditCard(data.cardNumber)) {
      throw new Error('Invalid credit card number');
    }

    const amountValidation = ValidationUtils.validateAmount(data.amount, data.currency);
    if (!amountValidation.valid) {
      throw new Error(amountValidation.error);
    }

    if (data.billingAddress) {
      const addressValidation = ValidationUtils.validateBillingAddress(data.billingAddress);
      if (!addressValidation.valid) {
        throw new Error(addressValidation.error);
      }
    }

    return true;
  }

  async processPayment(paymentData) {
    // Enhanced fraud detection
    if (this.fraudDetection && await this.detectFraud(paymentData)) {
      throw new Error('Transaction flagged for manual review');
    }

    return super.processPayment(paymentData);
  }

  async detectFraud(paymentData) {
    // Simulate fraud detection logic
    const riskFactors = [];

    // Check for unusual amounts
    if (paymentData.amount > 5000) {
      riskFactors.push('high_amount');
    }

    // Check for rapid successive transactions
    if (this.hasRecentTransactions(paymentData.cardToken)) {
      riskFactors.push('rapid_transactions');
    }

    // Geographic anomalies
    if (this.isUnusualLocation(paymentData.billingAddress)) {
      riskFactors.push('unusual_location');
    }

    return riskFactors.length >= 2;
  }

  hasRecentTransactions(cardToken) {
    // Simulate checking recent transaction history
    return Math.random() < 0.1; // 10% chance of recent transactions
  }

  isUnusualLocation(address) {
    // Simulate geographic risk assessment
    const highRiskCountries = ['XX', 'YY', 'ZZ'];
    return address && highRiskCountries.includes(address.country);
  }
}

module.exports = EnhancedPaymentProcessor;
EOF

git add .
git commit -m "feat(validation): implement enhanced payment validation

- Add Luhn algorithm for credit card validation
- Implement currency-specific amount validation
- Add billing address validation with postal code patterns
- Create enhanced payment processor with fraud detection
- Add risk assessment for high-value transactions
- Implement geographic anomaly detection"

# Push feature branch
git push -u origin feature/enhanced-payment-validation
```

#### 2.2 Simulate Second Developer: API Enhancement
```bash
# Simula secondo sviluppatore che lavora su API
git checkout main
git checkout -b feature/api-monitoring

# Aggiungi sistema di monitoring
cat > src/api/monitoring.js << 'EOF'
class APIMonitoring {
  constructor() {
    this.metrics = {
      requestCount: 0,
      errorCount: 0,
      responseTimeAvg: 0,
      responseTimes: []
    };
    this.alerts = [];
  }

  logRequest(method, endpoint, statusCode, responseTime) {
    this.metrics.requestCount++;
    this.metrics.responseTimes.push(responseTime);
    
    // Update average response time
    this.metrics.responseTimeAvg = 
      this.metrics.responseTimes.reduce((a, b) => a + b, 0) / 
      this.metrics.responseTimes.length;

    if (statusCode >= 400) {
      this.metrics.errorCount++;
    }

    // Alert on high error rate
    const errorRate = this.metrics.errorCount / this.metrics.requestCount;
    if (errorRate > 0.05) { // 5% error rate threshold
      this.createAlert('high_error_rate', `Error rate: ${(errorRate * 100).toFixed(2)}%`);
    }

    // Alert on slow responses
    if (responseTime > 5000) { // 5 second threshold
      this.createAlert('slow_response', `Slow response: ${responseTime}ms for ${method} ${endpoint}`);
    }

    console.log(`API Request: ${method} ${endpoint} - ${statusCode} (${responseTime}ms)`);
  }

  createAlert(type, message) {
    const alert = {
      id: Date.now(),
      type,
      message,
      timestamp: new Date().toISOString(),
      severity: this.getAlertSeverity(type)
    };

    this.alerts.push(alert);
    
    if (alert.severity === 'critical') {
      console.error(`CRITICAL ALERT: ${message}`);
      // In production: send to alerting system
    }
  }

  getAlertSeverity(type) {
    const severityMap = {
      'high_error_rate': 'critical',
      'slow_response': 'warning',
      'unusual_activity': 'info'
    };
    return severityMap[type] || 'info';
  }

  getMetrics() {
    return {
      ...this.metrics,
      errorRate: this.metrics.errorCount / this.metrics.requestCount,
      alerts: this.alerts.filter(alert => 
        Date.now() - new Date(alert.timestamp).getTime() < 3600000 // Last hour
      )
    };
  }

  generateReport() {
    const metrics = this.getMetrics();
    return `
=== API Monitoring Report ===
Total Requests: ${metrics.requestCount}
Error Count: ${metrics.errorCount}
Error Rate: ${(metrics.errorRate * 100).toFixed(2)}%
Average Response Time: ${metrics.responseTimeAvg.toFixed(2)}ms
Active Alerts: ${metrics.alerts.length}

Recent Alerts:
${metrics.alerts.map(alert => 
  `- [${alert.severity.toUpperCase()}] ${alert.message} (${alert.timestamp})`
).join('\n')}
    `;
  }
}

module.exports = APIMonitoring;
EOF

# Middleware per Express
cat > src/api/middleware/monitoring-middleware.js << 'EOF'
const APIMonitoring = require('../monitoring');

const monitoring = new APIMonitoring();

function createMonitoringMiddleware() {
  return (req, res, next) => {
    const startTime = Date.now();

    // Override res.end to capture metrics
    const originalEnd = res.end;
    res.end = function(...args) {
      const responseTime = Date.now() - startTime;
      monitoring.logRequest(req.method, req.path, res.statusCode, responseTime);
      originalEnd.apply(this, args);
    };

    next();
  };
}

// Health check endpoint
function healthCheck(req, res) {
  const metrics = monitoring.getMetrics();
  const isHealthy = metrics.errorRate < 0.1 && metrics.responseTimeAvg < 2000;

  res.status(isHealthy ? 200 : 503).json({
    status: isHealthy ? 'healthy' : 'unhealthy',
    metrics: {
      requestCount: metrics.requestCount,
      errorRate: `${(metrics.errorRate * 100).toFixed(2)}%`,
      avgResponseTime: `${metrics.responseTimeAvg.toFixed(2)}ms`,
      alerts: metrics.alerts.length
    },
    timestamp: new Date().toISOString()
  });
}

// Metrics endpoint
function getMetrics(req, res) {
  res.json(monitoring.getMetrics());
}

// Report endpoint
function getReport(req, res) {
  res.type('text/plain').send(monitoring.generateReport());
}

module.exports = {
  createMonitoringMiddleware,
  healthCheck,
  getMetrics,
  getReport,
  monitoring
};
EOF

git add .
git commit -m "feat(monitoring): add comprehensive API monitoring system

- Implement request/response time tracking
- Add error rate monitoring with automatic alerts
- Create health check endpoint for service monitoring
- Add metrics collection and reporting endpoints
- Implement middleware for automatic request logging
- Add severity-based alert system for operational awareness"

git push -u origin feature/api-monitoring
```

### Task 3: Complex Merge Scenarios and Conflict Resolution

#### 3.1 Advanced Conflict Simulation
```bash
# Ritorna su main per simulare conflitto
git checkout main

# Simula modifica concorrente al payment processor
cat > src/api/payment-processor.js << 'EOF'
class PaymentProcessor {
  constructor(config) {
    this.config = config;
    this.environment = config.environment || 'development';
    this.retryAttempts = config.retryAttempts || 3;
  }

  async processPayment(paymentData) {
    // Enhanced validation with retry logic
    if (!this.validatePaymentData(paymentData)) {
      throw new Error('Invalid payment data');
    }

    // Retry mechanism for failed payments
    for (let attempt = 1; attempt <= this.retryAttempts; attempt++) {
      try {
        return await this.attemptPayment(paymentData, attempt);
      } catch (error) {
        if (attempt === this.retryAttempts) {
          throw new Error(`Payment failed after ${this.retryAttempts} attempts: ${error.message}`);
        }
        console.log(`Payment attempt ${attempt} failed, retrying...`);
        await this.delay(1000 * attempt); // Exponential backoff
      }
    }
  }

  async attemptPayment(paymentData, attempt) {
    // Environment-specific processing with attempt tracking
    console.log(`Payment attempt ${attempt} for amount: ${paymentData.amount}`);
    
    switch (this.environment) {
      case 'production':
        return await this.processProductionPayment(paymentData);
      case 'staging':
        return await this.processStagingPayment(paymentData);
      default:
        return await this.processTestPayment(paymentData);
    }
  }

  validatePaymentData(data) {
    return data && data.amount && data.currency && data.cardToken;
  }

  async processProductionPayment(data) {
    // Production payment with enhanced logging
    console.log('Processing production payment:', data.amount, 'in', data.currency);
    return { 
      status: 'success', 
      transactionId: this.generateTransactionId(),
      processingTime: Date.now()
    };
  }

  async processStagingPayment(data) {
    // Staging environment with comprehensive logging
    console.log('Staging payment processing:', data);
    return { 
      status: 'success', 
      transactionId: 'staging_' + Date.now(),
      environment: 'staging'
    };
  }

  async processTestPayment(data) {
    // Development/test environment
    return { 
      status: 'test_success', 
      transactionId: 'test_' + Date.now(),
      testMode: true
    };
  }

  generateTransactionId() {
    return 'prod_' + Date.now() + '_' + Math.random().toString(36).substring(7);
  }

  delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }
}

module.exports = PaymentProcessor;
EOF

git add .
git commit -m "feat(core): add retry mechanism and enhanced logging

- Implement exponential backoff for failed payments
- Add comprehensive logging for all environments
- Include processing time tracking for production
- Add attempt-based error handling
- Enhance transaction ID generation with timestamps"

# Ora prova a fare merge del primo feature branch
git merge feature/enhanced-payment-validation
```

*A questo punto ci sarà un conflitto nel file payment-processor.js che dovrai risolvere manualmente*

#### 3.2 Advanced Conflict Resolution
```bash
# Visualizza conflitti
git status
git diff

# Risolvi conflitto manualmente creando versione unificata
cat > src/api/payment-processor.js << 'EOF'
const ValidationUtils = require('../shared/validation-utils');

class PaymentProcessor {
  constructor(config) {
    this.config = config;
    this.environment = config.environment || 'development';
    this.retryAttempts = config.retryAttempts || 3;
    this.fraudDetection = config.fraudDetection || false;
  }

  async processPayment(paymentData) {
    // Enhanced validation with fraud detection
    if (!this.validatePaymentData(paymentData)) {
      throw new Error('Invalid payment data');
    }

    // Enhanced fraud detection
    if (this.fraudDetection && await this.detectFraud(paymentData)) {
      throw new Error('Transaction flagged for manual review');
    }

    // Retry mechanism for failed payments
    for (let attempt = 1; attempt <= this.retryAttempts; attempt++) {
      try {
        return await this.attemptPayment(paymentData, attempt);
      } catch (error) {
        if (attempt === this.retryAttempts) {
          throw new Error(`Payment failed after ${this.retryAttempts} attempts: ${error.message}`);
        }
        console.log(`Payment attempt ${attempt} failed, retrying...`);
        await this.delay(1000 * attempt); // Exponential backoff
      }
    }
  }

  validatePaymentData(data) {
    // Basic validation
    if (!data || !data.amount || !data.currency || !data.cardToken) {
      return false;
    }

    // Enhanced validation using ValidationUtils
    try {
      if (!ValidationUtils.validateCreditCard(data.cardNumber)) {
        throw new Error('Invalid credit card number');
      }

      const amountValidation = ValidationUtils.validateAmount(data.amount, data.currency);
      if (!amountValidation.valid) {
        throw new Error(amountValidation.error);
      }

      if (data.billingAddress) {
        const addressValidation = ValidationUtils.validateBillingAddress(data.billingAddress);
        if (!addressValidation.valid) {
          throw new Error(addressValidation.error);
        }
      }

      return true;
    } catch (error) {
      console.error('Validation error:', error.message);
      return false;
    }
  }

  async attemptPayment(paymentData, attempt) {
    // Environment-specific processing with attempt tracking
    console.log(`Payment attempt ${attempt} for amount: ${paymentData.amount}`);
    
    switch (this.environment) {
      case 'production':
        return await this.processProductionPayment(paymentData);
      case 'staging':
        return await this.processStagingPayment(paymentData);
      default:
        return await this.processTestPayment(paymentData);
    }
  }

  async processProductionPayment(data) {
    // Production payment with enhanced logging
    console.log('Processing production payment:', data.amount, 'in', data.currency);
    return { 
      status: 'success', 
      transactionId: this.generateTransactionId(),
      processingTime: Date.now(),
      environment: 'production'
    };
  }

  async processStagingPayment(data) {
    // Staging environment with comprehensive logging
    console.log('Staging payment processing:', data);
    return { 
      status: 'success', 
      transactionId: 'staging_' + Date.now(),
      environment: 'staging'
    };
  }

  async processTestPayment(data) {
    // Development/test environment
    return { 
      status: 'test_success', 
      transactionId: 'test_' + Date.now(),
      testMode: true,
      environment: 'test'
    };
  }

  async detectFraud(paymentData) {
    // Simulate fraud detection logic
    const riskFactors = [];

    // Check for unusual amounts
    if (paymentData.amount > 5000) {
      riskFactors.push('high_amount');
    }

    // Check for rapid successive transactions
    if (this.hasRecentTransactions(paymentData.cardToken)) {
      riskFactors.push('rapid_transactions');
    }

    // Geographic anomalies
    if (this.isUnusualLocation(paymentData.billingAddress)) {
      riskFactors.push('unusual_location');
    }

    return riskFactors.length >= 2;
  }

  hasRecentTransactions(cardToken) {
    // Simulate checking recent transaction history
    return Math.random() < 0.1; // 10% chance of recent transactions
  }

  isUnusualLocation(address) {
    // Simulate geographic risk assessment
    const highRiskCountries = ['XX', 'YY', 'ZZ'];
    return address && highRiskCountries.includes(address.country);
  }

  generateTransactionId() {
    return 'prod_' + Date.now() + '_' + Math.random().toString(36).substring(7);
  }

  delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
  }
}

module.exports = PaymentProcessor;
EOF

# Finalizza merge
git add .
git commit -m "merge: integrate enhanced validation with retry mechanism

- Combine fraud detection with retry logic
- Unified payment validation using ValidationUtils
- Maintain comprehensive logging across all environments
- Preserve both enhanced security and reliability features
- Add environment tracking to all payment responses"

# Merge del secondo feature branch
git merge feature/api-monitoring

# Se ci sono conflitti, risolvili e committa
git add .
git commit -m "merge: integrate API monitoring with payment system

- Add comprehensive monitoring to payment processing
- Include health checks and metrics endpoints
- Maintain payment validation and retry mechanisms
- Combine fraud detection with performance monitoring"
```

### Task 4: Advanced Remote Operations and Recovery Scenarios

#### 4.1 Emergency Recovery Procedures
```bash
# Simula scenario di emergenza: push sbagliato in production
git checkout production

# Simula configurazione di produzione danneggiata
cat > config/prod/app.config.js << 'EOF'
module.exports = {
  environment: 'production',
  database: {
    host: 'WRONG-DB-HOST',  // Host errato!
    port: 5432,
    name: 'fintech_production'
  },
  api: {
    port: 443,
    ssl: true
  },
  logging: {
    level: 'debug'  // Troppo verboso per produzione!
  },
  security: {
    encryptionKey: 'hardcoded-key-DO-NOT-USE',  // GRAVE ERRORE DI SICUREZZA!
    pciCompliance: false  // Disabilitata per errore!
  }
};
EOF

git add .
git commit -m "EMERGENCY: fix production database connection"
git push production production

# REALIZZA L'ERRORE! Devi fare rollback immediato
echo "🚨 EMERGENCY: Configurazione production compromessa!"
echo "Iniziando procedura di rollback..."

# Opzione 1: Revert del commit problematico
git revert HEAD --no-edit

# Correggi configurazione production
cat > config/prod/app.config.js << 'EOF'
module.exports = {
  environment: 'production',
  database: {
    host: process.env.DB_HOST || 'prod-db.fintech.com',
    port: process.env.DB_PORT || 5432,
    name: process.env.DB_NAME || 'fintech_production',
    ssl: true,
    connectionTimeout: 30000
  },
  api: {
    port: process.env.PORT || 443,
    ssl: true,
    corsOrigins: process.env.CORS_ORIGINS?.split(',') || []
  },
  logging: {
    level: process.env.LOG_LEVEL || 'error',
    destination: process.env.LOG_DESTINATION || '/var/log/fintech/app.log'
  },
  security: {
    encryptionKey: process.env.ENCRYPTION_KEY,
    pciCompliance: true,
    sessionTimeout: 15 * 60 * 1000, // 15 minutes
    maxLoginAttempts: 3
  },
  monitoring: {
    healthCheckPath: '/health',
    metricsPath: '/metrics',
    alertWebhook: process.env.ALERT_WEBHOOK_URL
  }
};
EOF

git add .
git commit -m "fix: restore secure production configuration

- Use environment variables for sensitive data
- Enable PCI compliance and proper security settings
- Set appropriate logging level for production
- Add connection timeouts and security measures
- Include monitoring endpoints for operations team"

git push production production

echo "✅ Emergency rollback completed!"
```

#### 4.2 Advanced Remote Management
```bash
# Torna su main e sincronizza tutti gli ambienti
git checkout main

# Pull da tutte le remote per sincronizzare
git fetch --all

# Verifica stato di tutti i branch
git branch -a
git log --oneline --graph --all --decorate

# Force push scenario (uso responsabile)
echo "Preparazione per force push controllato..."

# Crea branch di backup
git branch backup-before-force-push

# Simula necessità di riscrittura della storia
git reset --hard HEAD~2

# Aggiungi commit consolidato
cat > DEPLOYMENT_GUIDE.md << 'EOF'
# Deployment Guide - FinTech Payment System

## Quick Reference
- **Development**: automatic deployment on merge to main
- **Staging**: manual deployment for testing
- **Production**: approval-required deployment

## Emergency Procedures

### Rollback Production
```bash
# Immediate rollback to previous version
git checkout production
git reset --hard HEAD~1
git push --force production production

# Alternative: Revert specific commit
git revert COMMIT_HASH
git push production production
```

### Database Migrations
```bash
# Apply migrations in order
npm run migrate:dev    # Development
npm run migrate:staging # Staging (after testing)
npm run migrate:prod   # Production (with approval)
```

### Configuration Management
- All environment variables must be set in CI/CD
- Never commit secrets to repository
- Use separate config files per environment
- Validate configuration on startup

### Monitoring and Alerts
- Health check: GET /health
- Metrics: GET /metrics  
- Logs: Structured JSON logging
- Alerts: Automatic via webhook

## Security Checklist
- [ ] Environment variables configured
- [ ] Database connections encrypted
- [ ] PCI compliance enabled
- [ ] Session timeouts configured
- [ ] Rate limiting enabled
- [ ] Input validation active
- [ ] Audit logging enabled
EOF

git add .
git commit -m "docs: add comprehensive deployment and emergency procedures

- Document rollback procedures for all environments
- Add database migration workflow
- Include security checklist for deployments
- Provide monitoring and alerting guidelines
- Add configuration management best practices"

# Force push con warning (solo dopo backup!)
echo "🚨 ATTENTION: About to force push. Backup created at backup-before-force-push"
git push --force-with-lease origin main

# Verifica che il force push sia andato a buon fine
git log --oneline -5
```

### Task 5: Advanced Branching Strategies with Multiple Remotes

#### 5.1 GitFlow con Multiple Environments
```bash
# Implementa GitFlow completo
git checkout main

# Crea develop branch
git checkout -b develop
git push -u origin develop

# Crea release branch
git checkout -b release/v1.0.0
git push -u origin release/v1.0.0

# Prepara versione per release
cat > package.json << 'EOF'
{
  "name": "fintech-payment-system",
  "version": "1.0.0",
  "description": "Enterprise payment processing system",
  "main": "src/api/payment-processor.js",
  "scripts": {
    "start": "node src/api/server.js",
    "test": "jest",
    "test:coverage": "jest --coverage",
    "lint": "eslint src/",
    "lint:fix": "eslint src/ --fix",
    "deploy:staging": "npm run build && npm run deploy:staging:run",
    "deploy:production": "npm run build && npm run deploy:prod:run"
  },
  "keywords": ["fintech", "payments", "security", "enterprise"],
  "author": "FinTech Team",
  "license": "PROPRIETARY",
  "dependencies": {
    "express": "^4.18.0",
    "helmet": "^6.0.0",
    "cors": "^2.8.5",
    "rate-limiter-flexible": "^2.4.0",
    "winston": "^3.8.0"
  },
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "supertest": "^6.3.0"
  }
}
EOF

# Crea changelog per release
cat > CHANGELOG.md << 'EOF'
# Changelog

## [1.0.0] - 2024-01-15

### Added
- Enterprise-grade payment processing system
- Enhanced credit card validation with Luhn algorithm
- Fraud detection system with risk assessment
- Comprehensive API monitoring and health checks
- Multi-environment configuration management
- Retry mechanism with exponential backoff
- PCI DSS compliance framework
- Geographic anomaly detection
- Structured logging and alerting system

### Security
- Environment-based configuration separation
- Secure credential management
- Input validation and sanitization
- Rate limiting and session management
- Audit logging for all transactions

### Documentation
- Comprehensive deployment guide
- Emergency rollback procedures
- Security compliance checklist
- API documentation and monitoring guides

### Infrastructure
- Multi-environment deployment pipeline
- Automated health checks and monitoring
- Database migration management
- CI/CD integration ready
EOF

git add .
git commit -m "release: prepare v1.0.0 for production deployment

- Add package.json with production dependencies
- Create comprehensive changelog
- Document all features and security enhancements
- Prepare deployment scripts and procedures
- Include version management and release notes"

# Merge release to main (production)
git checkout main
git merge release/v1.0.0 --no-ff
git tag -a v1.0.0 -m "Production release v1.0.0 - Enterprise payment system"

# Deploy to production
git push production main
git push production v1.0.0

# Merge release to develop
git checkout develop
git merge release/v1.0.0 --no-ff
git push origin develop

# Cleanup release branch
git branch -d release/v1.0.0
git push origin --delete release/v1.0.0
```

#### 5.2 Hotfix Emergency Procedure
```bash
# Simula bug critico in produzione che richiede hotfix immediato
git checkout main
git checkout -b hotfix/security-patch-v1.0.1

# Fix critico di sicurezza
cat > src/api/security-patch.js << 'EOF'
class SecurityPatch {
  static sanitizeInput(input) {
    if (typeof input !== 'string') {
      return input;
    }
    
    // Remove potentially dangerous characters
    return input
      .replace(/[<>\"']/g, '') // Remove HTML/script chars
      .replace(/javascript:/gi, '') // Remove javascript protocol
      .replace(/data:/gi, '') // Remove data protocol
      .replace(/vbscript:/gi, '') // Remove vbscript protocol
      .trim();
  }

  static validateApiKey(apiKey) {
    if (!apiKey || typeof apiKey !== 'string') {
      return false;
    }

    // API key must be exactly 32 characters, alphanumeric
    const apiKeyPattern = /^[a-zA-Z0-9]{32}$/;
    return apiKeyPattern.test(apiKey);
  }

  static rateLimit(req) {
    // Simple rate limiting by IP
    const ip = req.ip || req.connection.remoteAddress;
    const now = Date.now();
    
    if (!this.requestCounts) {
      this.requestCounts = new Map();
    }

    const requests = this.requestCounts.get(ip) || [];
    const recentRequests = requests.filter(time => now - time < 60000); // Last minute

    if (recentRequests.length >= 100) { // 100 requests per minute limit
      return false;
    }

    recentRequests.push(now);
    this.requestCounts.set(ip, recentRequests);
    return true;
  }

  static logSecurityEvent(event, details) {
    const logEntry = {
      timestamp: new Date().toISOString(),
      event,
      details,
      severity: 'HIGH',
      ip: details.ip || 'unknown'
    };

    console.error('SECURITY EVENT:', JSON.stringify(logEntry));
    
    // In production: send to security monitoring system
    if (process.env.SECURITY_WEBHOOK) {
      // Send to security team webhook
    }
  }
}

module.exports = SecurityPatch;
EOF

# Applica patch al payment processor
cat > src/api/payment-processor-patched.js << 'EOF'
const PaymentProcessor = require('./payment-processor');
const SecurityPatch = require('./security-patch');

class PatchedPaymentProcessor extends PaymentProcessor {
  validatePaymentData(data) {
    // Apply security patches
    if (data.cardNumber) {
      data.cardNumber = SecurityPatch.sanitizeInput(data.cardNumber);
    }
    
    if (data.billingAddress) {
      Object.keys(data.billingAddress).forEach(key => {
        data.billingAddress[key] = SecurityPatch.sanitizeInput(data.billingAddress[key]);
      });
    }

    return super.validatePaymentData(data);
  }

  async processPayment(paymentData, req) {
    // Security validations
    if (!SecurityPatch.rateLimit(req)) {
      SecurityPatch.logSecurityEvent('rate_limit_exceeded', { ip: req.ip });
      throw new Error('Rate limit exceeded');
    }

    return super.processPayment(paymentData);
  }
}

module.exports = PatchedPaymentProcessor;
EOF

git add .
git commit -m "hotfix: critical security patches for input validation

SECURITY PATCH v1.0.1:
- Add input sanitization for all user inputs
- Implement rate limiting per IP address  
- Add security event logging and monitoring
- Patch payment processor against XSS attacks
- Validate API keys with strict pattern matching
- Add security webhook integration for alerts

CRITICAL: Deploy immediately to production"

# Tag hotfix
git tag -a v1.0.1 -m "Hotfix v1.0.1 - Critical security patches"

# Merge hotfix to main (production)
git checkout main
git merge hotfix/security-patch-v1.0.1 --no-ff

# Emergency deploy to production
git push production main
git push production v1.0.1

# Merge hotfix to develop
git checkout develop
git merge hotfix/security-patch-v1.0.1 --no-ff
git push origin develop

# Cleanup
git branch -d hotfix/security-patch-v1.0.1

echo "🚨 HOTFIX DEPLOYED: Security patches applied to production"
echo "✅ Version v1.0.1 deployed successfully"
```

## 📊 Verifica e Validazione

### Checklist di Completamento

**Advanced Workflow Mastery:**
- [ ] Configurato repository multi-environment (dev/staging/prod)
- [ ] Implementato feature development con multiple contributors
- [ ] Gestito conflitti complessi tra feature branches
- [ ] Eseguito emergency rollback procedures
- [ ] Completato GitFlow con release management
- [ ] Gestito hotfix emergency deployment

**Remote Operations Excellence:**
- [ ] Configurato multiple remote repositories
- [ ] Utilizzato force push responsabilmente con backup
- [ ] Implementato branch tracking per tutti gli environment
- [ ] Sincronizzato modifiche tra development, staging e production
- [ ] Gestito tag versioning e release management

**Enterprise Security:**
- [ ] Implementato configurazione environment-based
- [ ] Applicato security patches con procedure di emergency
- [ ] Configurato monitoring e alerting system
- [ ] Documentato deployment e rollback procedures
- [ ] Testato fraud detection e validation systems

### Competenze Acquisite

Al completamento di questo esercizio avrai dimostrato:
- **🏢 Enterprise DevOps**: Gestione repository multi-ambiente
- **🔒 Security Operations**: Emergency patches e security procedures  
- **🚀 Advanced Git**: Complex merge scenarios e conflict resolution
- **📊 Operations**: Monitoring, alerting e incident response
- **🔄 Release Management**: GitFlow, versioning e deployment procedures

## 🎯 Challenge Bonus

### Challenge 1: Disaster Recovery Simulation
Simula un scenario dove la remote di produzione è compromessa e devi ricostruire tutto da backup locali.

### Challenge 2: Multi-Team Collaboration
Estendi l'esercizio simulando 5+ developer che lavorano contemporaneamente su feature diverse con complex dependencies.

### Challenge 3: Automated Pipeline Integration
Integra il workflow con GitHub Actions per automated testing, security scanning e deployment.

## 📚 Risorse per Approfondimento

### Documentation
- [Git Flow Workflow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow)
- [Advanced Git Tips](https://git-scm.com/book/en/v2/Git-Branching-Advanced-Merging)
- [Enterprise Git Strategies](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository)

### Security Resources
- [Git Security Best Practices](https://github.blog/2021-09-01-improving-git-protocol-security-github/)
- [PCI DSS Compliance](https://www.pcisecuritystandards.org/)

## 🔄 Navigazione

- [⬅️ Esercizio Precedente](02-collaboration-basics.md)
- [📚 Torna alla Sezione Esercizi](README.md)
- [🏠 Torna al Modulo Clone-Push-Pull](../README.md)
- [➡️ Prossimo Modulo: Collaborazione Base](../../18-Collaborazione-Base/README.md)

---

*Questo esercizio rappresenta il livello enterprise di competenza su Git workflow. Le skills acquisite sono direttamente applicabili in ambienti di produzione di livello aziendale.*
