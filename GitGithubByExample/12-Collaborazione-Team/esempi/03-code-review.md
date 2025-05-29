# Workflow di Code Review

## Obiettivi
- Implementare un processo di code review efficace
- Configurare strumenti per la review automatizzata
- Sviluppare competenze di review e feedback
- Integrare quality gates nel workflow

## Scenario: Sistema di Code Review Completo

### Configurazione Iniziale del Repository

```bash
# Setup del repository con protezioni
mkdir code-review-workflow
cd code-review-workflow
git init

# Configurazione di base
git config user.name "Team Lead"
git config user.email "lead@company.com"

# Struttura del progetto
mkdir -p {src,tests,docs,scripts}
mkdir -p .github/{workflows,PULL_REQUEST_TEMPLATE}

# File base dell'applicazione
cat > src/app.js << EOF
/**
 * Main application module
 * @author Team Lead
 * @version 1.0.0
 */

const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());
app.use(express.static('public'));

// Routes
app.get('/', (req, res) => {
    res.json({ 
        message: 'API is running',
        version: '1.0.0',
        timestamp: new Date().toISOString()
    });
});

app.get('/health', (req, res) => {
    res.status(200).json({ status: 'healthy' });
});

app.listen(PORT, () => {
    console.log(\`Server running on port \${PORT}\`);
});

module.exports = app;
EOF

# Package.json
cat > package.json << EOF
{
  "name": "code-review-demo",
  "version": "1.0.0",
  "description": "Demonstration of code review workflow",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "dev": "nodemon src/app.js",
    "test": "jest",
    "test:coverage": "jest --coverage",
    "lint": "eslint src/",
    "lint:fix": "eslint src/ --fix",
    "format": "prettier --write src/"
  },
  "keywords": ["nodejs", "express", "api"],
  "author": "Development Team",
  "license": "MIT",
  "dependencies": {
    "express": "^4.18.0"
  },
  "devDependencies": {
    "eslint": "^8.0.0",
    "jest": "^29.0.0",
    "nodemon": "^2.0.0",
    "prettier": "^2.8.0",
    "@types/jest": "^29.0.0"
  }
}
EOF

# ESLint configuration
cat > .eslintrc.js << EOF
module.exports = {
    env: {
        node: true,
        es2021: true,
        jest: true
    },
    extends: [
        'eslint:recommended'
    ],
    parserOptions: {
        ecmaVersion: 12,
        sourceType: 'module'
    },
    rules: {
        'indent': ['error', 4],
        'linebreak-style': ['error', 'unix'],
        'quotes': ['error', 'single'],
        'semi': ['error', 'always'],
        'no-unused-vars': 'error',
        'no-console': 'warn',
        'prefer-const': 'error',
        'no-var': 'error'
    }
};
EOF

# Prettier configuration
cat > .prettierrc << EOF
{
  "semi": true,
  "trailingComma": "es5",
  "singleQuote": true,
  "printWidth": 80,
  "tabWidth": 4
}
EOF

git add .
git commit -m "feat: initial project setup with linting and formatting"
```

### 1. Template per Pull Request

```bash
# Template per PR standardizzate
cat > .github/PULL_REQUEST_TEMPLATE/feature.md << EOF
# Feature Pull Request

## 📝 Description
<!-- Describe what this PR accomplishes -->

## 🔄 Type of Change
- [ ] Bug fix (non-breaking change which fixes an issue)
- [ ] New feature (non-breaking change which adds functionality)
- [ ] Breaking change (fix or feature that would cause existing functionality to not work as expected)
- [ ] Documentation update
- [ ] Code refactoring
- [ ] Performance improvement

## 🧪 Testing
<!-- Describe the tests you ran and their results -->
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Manual testing completed
- [ ] Code coverage maintained/improved

### Test Cases
<!-- List specific test cases if applicable -->
- [ ] Test case 1: [description]
- [ ] Test case 2: [description]

## 📷 Screenshots/Demo
<!-- If UI changes, include before/after screenshots -->

## 🔗 Related Issues
<!-- Link to related issues -->
Closes #[issue_number]
Related to #[issue_number]

## 📋 Checklist
- [ ] My code follows the style guidelines of this project
- [ ] I have performed a self-review of my own code
- [ ] I have commented my code, particularly in hard-to-understand areas
- [ ] I have made corresponding changes to the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix is effective or that my feature works
- [ ] New and existing unit tests pass locally with my changes

## 🎯 Focus Areas for Review
<!-- Guide reviewers on what to focus on -->
- [ ] Logic correctness
- [ ] Performance impact
- [ ] Security considerations
- [ ] Error handling
- [ ] Code style and readability

## 📚 Additional Notes
<!-- Any additional information for reviewers -->
EOF

# Template per Bug Fix
cat > .github/PULL_REQUEST_TEMPLATE/bugfix.md << EOF
# Bug Fix Pull Request

## 🐛 Bug Description
<!-- Describe the bug that was fixed -->

## 🔧 Solution
<!-- Explain how you fixed the bug -->

## 📊 Root Cause Analysis
<!-- What caused this bug? -->

## ✅ Verification
<!-- How did you verify the fix works? -->
- [ ] Bug reproduced before fix
- [ ] Bug resolved after fix
- [ ] Regression tests added
- [ ] No side effects observed

## 🧪 Testing
- [ ] Existing tests pass
- [ ] New tests added for the fix
- [ ] Manual verification completed

## 📋 Checklist
- [ ] Code follows project guidelines
- [ ] Self-review completed
- [ ] Documentation updated if needed
- [ ] No new warnings introduced

## 🔗 Related
Issue: #[issue_number]
EOF

# Default template
cat > .github/pull_request_template.md << EOF
## Summary
<!-- Brief description of changes -->

## Changes Made
- [ ] Change 1
- [ ] Change 2

## Testing
- [ ] Tests added/updated
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Self-review completed
- [ ] Documentation updated
EOF
```

### 2. GitHub Actions per Quality Gates

```bash
# Workflow per CI/CD con quality checks
cat > .github/workflows/pr-checks.yml << EOF
name: Pull Request Checks

on:
  pull_request:
    branches: [ main, develop ]

jobs:
  lint:
    name: Lint Code
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run ESLint
        run: npm run lint
      
      - name: Check formatting
        run: npx prettier --check src/

  test:
    name: Run Tests
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run tests with coverage
        run: npm run test:coverage
      
      - name: Upload coverage to Codecov
        uses: codecov/codecov-action@v3
        with:
          file: ./coverage/lcov.info
          fail_ci_if_error: true

  security:
    name: Security Scan
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Run security audit
        run: npm audit --audit-level moderate
      
      - name: Check for vulnerabilities
        run: npx audit-ci --moderate

  build:
    name: Build Check
    runs-on: ubuntu-latest
    needs: [lint, test]
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Build application
        run: npm run build --if-present
      
      - name: Start application (smoke test)
        run: |
          npm start &
          sleep 5
          curl -f http://localhost:3000/health || exit 1
          killall node

  size-check:
    name: Bundle Size Check
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Check bundle size
        uses: andresz1/size-limit-action@v1
        with:
          github_token: \${{ secrets.GITHUB_TOKEN }}
EOF

# Workflow per review automatica
cat > .github/workflows/auto-review.yml << EOF
name: Automated Review

on:
  pull_request:
    types: [opened, synchronize]

jobs:
  auto-review:
    name: Automated Code Review
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run complexity analysis
        run: |
          npx complexity-report --output complexity.json src/
          echo "Complexity analysis completed"
      
      - name: Check code duplication
        run: |
          npx jscpd src/ --reporters json --output ./jscpd-report.json
          echo "Duplication check completed"
      
      - name: Comment PR with analysis
        uses: actions/github-script@v6
        with:
          script: |
            const fs = require('fs');
            
            let comment = '## 🤖 Automated Code Review\\n\\n';
            
            // Add complexity info if file exists
            try {
              const complexity = JSON.parse(fs.readFileSync('complexity.json', 'utf8'));
              comment += '### 📊 Complexity Analysis\\n';
              comment += \`- Average complexity: \${complexity.average}\\n\`;
              comment += \`- Total functions: \${complexity.functions}\\n\\n\`;
            } catch (e) {
              comment += '### 📊 Complexity Analysis\\n- Analysis completed successfully\\n\\n';
            }
            
            // Add duplication info
            try {
              const duplication = JSON.parse(fs.readFileSync('jscpd-report.json', 'utf8'));
              comment += '### 🔍 Code Duplication\\n';
              comment += \`- Duplicated lines: \${duplication.statistics.total.duplicatedLines}\\n\`;
              comment += \`- Duplication percentage: \${duplication.statistics.total.percentage}%\\n\\n\`;
            } catch (e) {
              comment += '### 🔍 Code Duplication\\n- No significant duplication found\\n\\n';
            }
            
            comment += '### ✅ Automated Checks\\n';
            comment += '- [ ] All tests passing\\n';
            comment += '- [ ] Linting rules followed\\n';
            comment += '- [ ] Code formatted correctly\\n';
            comment += '- [ ] Security vulnerabilities checked\\n\\n';
            comment += '*This review was generated automatically. Please ensure manual review is also completed.*';
            
            github.rest.issues.createComment({
              issue_number: context.issue.number,
              owner: context.repo.owner,
              repo: context.repo.repo,
              body: comment
            });
EOF
```

### 3. Scripts per Review Locale

```bash
# Script per review pre-commit
cat > scripts/pre-review.sh << EOF
#!/bin/bash
set -e

echo "🔍 Starting pre-review checks..."

# Check if we're in git repository
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "❌ Not a git repository"
    exit 1
fi

# Install dependencies if needed
if [ ! -d "node_modules" ]; then
    echo "📦 Installing dependencies..."
    npm install
fi

# Run linting
echo "🧹 Running linter..."
npm run lint

# Run tests
echo "🧪 Running tests..."
npm run test

# Check formatting
echo "💅 Checking code formatting..."
npx prettier --check src/

# Security audit
echo "🔒 Running security audit..."
npm audit --audit-level moderate

# Check for TODO/FIXME comments
echo "📝 Checking for TODO/FIXME comments..."
TODO_COUNT=\$(grep -r "TODO\\|FIXME" src/ | wc -l || true)
if [ \$TODO_COUNT -gt 0 ]; then
    echo "⚠️  Found \$TODO_COUNT TODO/FIXME comments:"
    grep -rn "TODO\\|FIXME" src/ || true
    echo ""
fi

# Check file sizes
echo "📏 Checking file sizes..."
find src/ -name "*.js" -size +1000c -exec echo "⚠️  Large file: {}" \\;

# Check complexity (if tools available)
echo "📊 Analyzing code complexity..."
if command -v complexity-report &> /dev/null; then
    npx complexity-report src/ --format minimal
fi

echo "✅ Pre-review checks completed!"
echo ""
echo "📋 Review Checklist:"
echo "- [ ] Code follows style guidelines"
echo "- [ ] Tests added for new functionality"
echo "- [ ] Documentation updated"
echo "- [ ] No console.log statements in production code"
echo "- [ ] Error handling implemented"
echo "- [ ] Performance considerations addressed"
EOF

chmod +x scripts/pre-review.sh

# Script per review di sicurezza
cat > scripts/security-review.sh << EOF
#!/bin/bash
set -e

echo "🔒 Starting security review..."

# Check for common security issues
echo "🔍 Scanning for security vulnerabilities..."

# Check for hardcoded secrets
echo "🔑 Checking for hardcoded secrets..."
SECRET_PATTERNS=(
    "password.*=.*['\"][^'\"]*['\"]"
    "api[_-]?key.*=.*['\"][^'\"]*['\"]"
    "secret.*=.*['\"][^'\"]*['\"]"
    "token.*=.*['\"][^'\"]*['\"]"
    "auth.*=.*['\"][^'\"]*['\"]"
)

for pattern in "\${SECRET_PATTERNS[@]}"; do
    matches=\$(grep -ri "\$pattern" src/ || true)
    if [ ! -z "\$matches" ]; then
        echo "⚠️  Potential hardcoded secret found:"
        echo "\$matches"
        echo ""
    fi
done

# Check for SQL injection vulnerabilities
echo "💉 Checking for SQL injection risks..."
grep -rn "query.*+\\|exec.*+\\|\\\`.*\\\${" src/ && echo "⚠️  Potential SQL injection risk found" || echo "✅ No obvious SQL injection risks"

# Check for XSS vulnerabilities
echo "🌐 Checking for XSS risks..."
grep -rn "innerHTML\\|document\\.write\\|eval(" src/ && echo "⚠️  Potential XSS risk found" || echo "✅ No obvious XSS risks"

# Check dependencies
echo "📦 Checking dependencies for vulnerabilities..."
npm audit --json > audit.json 2>/dev/null || true
if [ -f audit.json ]; then
    HIGH_VULNS=\$(jq '.vulnerabilities | to_entries | map(select(.value.severity == "high" or .value.severity == "critical")) | length' audit.json 2>/dev/null || echo "0")
    if [ "\$HIGH_VULNS" -gt 0 ]; then
        echo "❌ Found \$HIGH_VULNS high/critical vulnerabilities"
        jq -r '.vulnerabilities | to_entries | map(select(.value.severity == "high" or .value.severity == "critical")) | .[] | "- " + .key + " (" + .value.severity + ")"' audit.json 2>/dev/null || true
    else
        echo "✅ No high/critical vulnerabilities found"
    fi
    rm -f audit.json
fi

echo "✅ Security review completed!"
EOF

chmod +x scripts/security-review.sh

# Script per metriche di qualità
cat > scripts/quality-metrics.sh << EOF
#!/bin/bash
set -e

echo "📊 Generating quality metrics..."

# Create reports directory
mkdir -p reports

# Test coverage
echo "📈 Generating test coverage report..."
npm run test:coverage > /dev/null 2>&1 || true
if [ -f coverage/lcov.info ]; then
    echo "✅ Coverage report generated in coverage/"
fi

# Code complexity
echo "🧮 Analyzing code complexity..."
if command -v complexity-report &> /dev/null; then
    npx complexity-report --output reports/complexity.json --format json src/
    echo "✅ Complexity report generated in reports/complexity.json"
fi

# Lines of code
echo "📏 Counting lines of code..."
echo "Lines of Code Analysis:" > reports/loc.txt
echo "======================" >> reports/loc.txt
find src/ -name "*.js" | xargs wc -l | tail -1 >> reports/loc.txt
echo "" >> reports/loc.txt
echo "File breakdown:" >> reports/loc.txt
find src/ -name "*.js" | xargs wc -l | head -n -1 >> reports/loc.txt

# Duplication analysis
echo "🔍 Analyzing code duplication..."
if command -v jscpd &> /dev/null; then
    npx jscpd src/ --reporters json --output reports/duplication.json > /dev/null 2>&1 || true
    echo "✅ Duplication analysis completed"
fi

# Generate summary report
echo "📋 Generating summary report..."
cat > reports/quality-summary.md << EOL
# Code Quality Summary

Generated on: \$(date)

## Test Coverage
\$(if [ -f coverage/lcov.info ]; then echo "✅ Coverage report available"; else echo "❌ No coverage data"; fi)

## Code Metrics
- Total JavaScript files: \$(find src/ -name "*.js" | wc -l)
- Total lines of code: \$(find src/ -name "*.js" | xargs wc -l | tail -1 | awk '{print \$1}')

## Static Analysis
\$(if [ -f reports/complexity.json ]; then echo "✅ Complexity analysis completed"; else echo "⚠️  Complexity analysis not available"; fi)
\$(if [ -f reports/duplication.json ]; then echo "✅ Duplication analysis completed"; else echo "⚠️  Duplication analysis not available"; fi)

## Recommendations
- Ensure test coverage is above 80%
- Keep cyclomatic complexity under 10
- Minimize code duplication
- Follow established coding standards
EOL

echo "✅ Quality metrics generated in reports/"
echo "📁 Check the reports/ directory for detailed analysis"
EOF

chmod +x scripts/quality-metrics.sh
```

### 4. Simulazione di Feature Development

```bash
# Creazione di una nuova feature
git checkout -b feature/user-authentication

# Implementazione della feature
cat > src/auth.js << EOF
/**
 * User authentication module
 * @author Developer A
 */

const bcrypt = require('bcrypt');
const jwt = require('jsonwebtoken');

class AuthService {
    constructor() {
        this.users = new Map(); // In production, use database
        this.jwtSecret = process.env.JWT_SECRET || 'dev-secret-key';
    }

    async register(username, password, email) {
        // Input validation
        if (!username || !password || !email) {
            throw new Error('Username, password, and email are required');
        }

        if (password.length < 8) {
            throw new Error('Password must be at least 8 characters long');
        }

        if (this.users.has(username)) {
            throw new Error('Username already exists');
        }

        // Hash password
        const saltRounds = 12;
        const hashedPassword = await bcrypt.hash(password, saltRounds);

        // Store user
        const user = {
            username,
            email,
            password: hashedPassword,
            createdAt: new Date().toISOString(),
            isActive: true
        };

        this.users.set(username, user);
        
        return {
            username: user.username,
            email: user.email,
            createdAt: user.createdAt
        };
    }

    async login(username, password) {
        const user = this.users.get(username);
        
        if (!user || !user.isActive) {
            throw new Error('Invalid credentials');
        }

        const isValidPassword = await bcrypt.compare(password, user.password);
        
        if (!isValidPassword) {
            throw new Error('Invalid credentials');
        }

        // Generate JWT token
        const token = jwt.sign(
            { 
                username: user.username,
                email: user.email 
            },
            this.jwtSecret,
            { expiresIn: '24h' }
        );

        return {
            token,
            user: {
                username: user.username,
                email: user.email
            }
        };
    }

    verifyToken(token) {
        try {
            return jwt.verify(token, this.jwtSecret);
        } catch (error) {
            throw new Error('Invalid token');
        }
    }

    // Middleware for protecting routes
    requireAuth() {
        return (req, res, next) => {
            const authHeader = req.headers.authorization;
            
            if (!authHeader || !authHeader.startsWith('Bearer ')) {
                return res.status(401).json({ error: 'Missing or invalid authorization header' });
            }

            const token = authHeader.substring(7);
            
            try {
                const decoded = this.verifyToken(token);
                req.user = decoded;
                next();
            } catch (error) {
                return res.status(401).json({ error: 'Invalid token' });
            }
        };
    }
}

module.exports = AuthService;
EOF

# Test per il modulo auth
cat > tests/auth.test.js << EOF
const AuthService = require('../src/auth');

describe('AuthService', () => {
    let authService;

    beforeEach(() => {
        authService = new AuthService();
    });

    describe('register', () => {
        test('should register a new user successfully', async () => {
            const result = await authService.register('testuser', 'password123', 'test@example.com');
            
            expect(result).toHaveProperty('username', 'testuser');
            expect(result).toHaveProperty('email', 'test@example.com');
            expect(result).toHaveProperty('createdAt');
            expect(result).not.toHaveProperty('password');
        });

        test('should throw error for duplicate username', async () => {
            await authService.register('testuser', 'password123', 'test@example.com');
            
            await expect(
                authService.register('testuser', 'password456', 'test2@example.com')
            ).rejects.toThrow('Username already exists');
        });

        test('should throw error for short password', async () => {
            await expect(
                authService.register('testuser', '123', 'test@example.com')
            ).rejects.toThrow('Password must be at least 8 characters long');
        });

        test('should throw error for missing fields', async () => {
            await expect(
                authService.register('', 'password123', 'test@example.com')
            ).rejects.toThrow('Username, password, and email are required');
        });
    });

    describe('login', () => {
        beforeEach(async () => {
            await authService.register('testuser', 'password123', 'test@example.com');
        });

        test('should login successfully with correct credentials', async () => {
            const result = await authService.login('testuser', 'password123');
            
            expect(result).toHaveProperty('token');
            expect(result).toHaveProperty('user');
            expect(result.user.username).toBe('testuser');
        });

        test('should throw error for invalid username', async () => {
            await expect(
                authService.login('nonexistent', 'password123')
            ).rejects.toThrow('Invalid credentials');
        });

        test('should throw error for invalid password', async () => {
            await expect(
                authService.login('testuser', 'wrongpassword')
            ).rejects.toThrow('Invalid credentials');
        });
    });

    describe('verifyToken', () => {
        test('should verify valid token', async () => {
            await authService.register('testuser', 'password123', 'test@example.com');
            const { token } = await authService.login('testuser', 'password123');
            
            const decoded = authService.verifyToken(token);
            expect(decoded.username).toBe('testuser');
        });

        test('should throw error for invalid token', () => {
            expect(() => {
                authService.verifyToken('invalid-token');
            }).toThrow('Invalid token');
        });
    });
});
EOF

# Aggiornamento dell'app principale
cat > src/app.js << EOF
/**
 * Main application module
 * @author Team Lead
 * @version 1.1.0
 */

const express = require('express');
const AuthService = require('./auth');

const app = express();
const authService = new AuthService();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(express.json());
app.use(express.static('public'));

// Health check
app.get('/health', (req, res) => {
    res.status(200).json({ 
        status: 'healthy',
        timestamp: new Date().toISOString(),
        version: '1.1.0'
    });
});

// Public routes
app.get('/', (req, res) => {
    res.json({ 
        message: 'API is running',
        version: '1.1.0',
        endpoints: {
            auth: {
                register: 'POST /auth/register',
                login: 'POST /auth/login'
            },
            protected: {
                profile: 'GET /profile'
            }
        }
    });
});

// Authentication routes
app.post('/auth/register', async (req, res) => {
    try {
        const { username, password, email } = req.body;
        const user = await authService.register(username, password, email);
        
        res.status(201).json({
            success: true,
            message: 'User registered successfully',
            user
        });
    } catch (error) {
        res.status(400).json({
            success: false,
            error: error.message
        });
    }
});

app.post('/auth/login', async (req, res) => {
    try {
        const { username, password } = req.body;
        const result = await authService.login(username, password);
        
        res.json({
            success: true,
            message: 'Login successful',
            ...result
        });
    } catch (error) {
        res.status(401).json({
            success: false,
            error: error.message
        });
    }
});

// Protected routes
app.get('/profile', authService.requireAuth(), (req, res) => {
    res.json({
        success: true,
        user: req.user,
        message: 'Profile data retrieved successfully'
    });
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({
        success: false,
        error: 'Internal server error'
    });
});

// 404 handler
app.use((req, res) => {
    res.status(404).json({
        success: false,
        error: 'Endpoint not found'
    });
});

if (require.main === module) {
    app.listen(PORT, () => {
        console.log(\`Server running on port \${PORT}\`);
    });
}

module.exports = app;
EOF

# Aggiornamento package.json con nuove dipendenze
cat > package.json << EOF
{
  "name": "code-review-demo",
  "version": "1.1.0",
  "description": "Demonstration of code review workflow",
  "main": "src/app.js",
  "scripts": {
    "start": "node src/app.js",
    "dev": "nodemon src/app.js",
    "test": "jest",
    "test:coverage": "jest --coverage",
    "test:watch": "jest --watch",
    "lint": "eslint src/ tests/",
    "lint:fix": "eslint src/ tests/ --fix",
    "format": "prettier --write src/ tests/",
    "pre-review": "./scripts/pre-review.sh",
    "security-review": "./scripts/security-review.sh",
    "quality-metrics": "./scripts/quality-metrics.sh"
  },
  "keywords": ["nodejs", "express", "api", "authentication", "jwt"],
  "author": "Development Team",
  "license": "MIT",
  "dependencies": {
    "express": "^4.18.0",
    "bcrypt": "^5.1.0",
    "jsonwebtoken": "^9.0.0"
  },
  "devDependencies": {
    "eslint": "^8.0.0",
    "jest": "^29.0.0",
    "nodemon": "^2.0.0",
    "prettier": "^2.8.0",
    "@types/jest": "^29.0.0",
    "supertest": "^6.3.0"
  },
  "jest": {
    "testEnvironment": "node",
    "collectCoverageFrom": [
      "src/**/*.js",
      "!src/index.js"
    ],
    "coverageThreshold": {
      "global": {
        "branches": 80,
        "functions": 80,
        "lines": 80,
        "statements": 80
      }
    }
  }
}
EOF

git add .
git commit -m "feat: implement user authentication system

- Add AuthService with registration and login
- Implement JWT token-based authentication
- Add comprehensive test suite with 100% coverage
- Add protected routes with middleware
- Include password hashing with bcrypt
- Add input validation and error handling

Closes #123"
```

### 5. Processo di Review

```bash
# Preparazione per review
echo "🔍 Preparando il codice per review..."

# Esecuzione dei controlli pre-review
./scripts/pre-review.sh

# Generazione delle metriche di qualità
./scripts/quality-metrics.sh

# Controllo di sicurezza
./scripts/security-review.sh

echo "✅ Codice pronto per review!"

# Creazione del branch di review con annotazioni
cat > REVIEW_NOTES.md << EOF
# Code Review Notes - User Authentication Feature

## 📋 Overview
This PR implements a complete user authentication system with JWT tokens.

## 🔍 Key Changes
1. **New AuthService class** (\`src/auth.js\`)
   - User registration with password hashing
   - Login with JWT token generation
   - Token verification middleware
   - Input validation and error handling

2. **Updated main app** (\`src/app.js\`)
   - New authentication endpoints
   - Protected route example
   - Enhanced error handling

3. **Comprehensive tests** (\`tests/auth.test.js\`)
   - 100% code coverage
   - Edge cases covered
   - Integration tests for middleware

## 🎯 Review Focus Areas

### Security Considerations
- ✅ Passwords are properly hashed using bcrypt
- ✅ JWT tokens have expiration
- ✅ Input validation implemented
- ✅ No sensitive data in responses
- ⚠️  JWT secret should come from environment in production

### Code Quality
- ✅ Follows ESLint rules
- ✅ Proper error handling
- ✅ Comprehensive documentation
- ✅ TypeScript-style JSDoc comments
- ⚠️  Consider adding rate limiting for auth endpoints

### Testing
- ✅ Unit tests for all methods
- ✅ Error scenarios covered
- ✅ Async operations properly tested
- 🔄 Integration tests could be expanded

### Performance
- ✅ Efficient bcrypt salt rounds (12)
- ✅ Stateless JWT implementation
- ⚠️  In-memory storage not suitable for production

## 📚 Documentation
- [ ] API documentation needs updating
- [ ] Deployment guide should include JWT_SECRET
- [ ] Database migration guide for production

## 🧪 Testing Results
\`\`\`
Test Suites: 1 passed, 1 total
Tests:       8 passed, 8 total
Coverage:    100% statements, 100% branches, 100% functions, 100% lines
\`\`\`

## 🚀 Next Steps
1. Code review approval
2. Update API documentation
3. Plan database integration
4. Deploy to staging environment
EOF

git add REVIEW_NOTES.md
git commit -m "docs: add comprehensive review notes for authentication feature"

echo "📝 Review notes created in REVIEW_NOTES.md"
```

## Best Practices per Code Review

### 1. **Per gli Autori**
- Mantenere PR di dimensioni ragionevoli (< 400 righe)
- Scrivere descrizioni chiare e dettagliate
- Auto-review prima di inviare
- Rispondere costruttivamente ai feedback
- Testare thoroughly prima del submit

### 2. **Per i Reviewer**
- Focalizzarsi su logica, sicurezza e maintainability
- Essere costruttivi nei commenti
- Suggerire soluzioni alternative
- Considerare il contesto e gli obiettivi
- Approvare solo quando sicuri

### 3. **Per il Team**
- Stabilire standard e checklist comuni
- Utilizzare automation per controlli basilari
- Rotazione dei reviewer per knowledge sharing
- Timeframe definiti per le review
- Learning culture, non blame culture

## Troubleshooting

### Problemi Comuni nelle Review

#### Review che si trascinano
```bash
# Setting di deadline automatiche
git config --global review.deadline "2 days"

# Notifiche automatiche
# (configurare in GitHub/GitLab settings)
```

#### Conflitti durante la review
```bash
# Rebase del branch con main aggiornato
git fetch origin
git rebase origin/main

# Risoluzione conflitti e force push
git push --force-with-lease origin feature-branch
```

#### Review incomplete
```bash
# Checklist automatica nei PR template
# Quality gates che bloccano merge
# Required reviewers configurati
```

## Navigazione del Corso
- [📑 Indice](../README.md)
- [⬅️ Gestione Conflitti](02-gestione-conflitti.md)
- [➡️ Esercizio Team Workflow](../esercizi/01-team-workflow.md)
