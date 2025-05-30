# Security Guidelines: Proteggere Repository e Codice

## Obiettivi
- Implementare pratiche di sicurezza per repository Git
- Proteggere credenziali e dati sensibili
- Configurare controlli di sicurezza automatizzati
- Stabilire procedure di incident response

## Introduzione

La sicurezza nei repository Git è essenziale per:
- **Protezione dati**: Prevenire leak di informazioni sensibili
- **Controllo accessi**: Gestire permessi e autenticazione
- **Audit trail**: Tracciabilità delle modifiche
- **Compliance**: Rispettare standard di sicurezza

## 1. Gestione Credenziali e Secrets

### ❌ Errori Comuni da Evitare

```bash
# MAI committare credenziali
git add config/database.yml  # contiene password DB
git commit -m "add database config"

# MAI includere API keys nel codice
const API_KEY = "sk-1234567890abcdef";  # Hardcoded nel codice

# MAI committare file di environment
git add .env  # contiene secrets di produzione
```

### ✅ Gestione Corretta dei Secrets

```bash
# Usa .env.example come template
# .env.example
DATABASE_URL=postgres://user:password@localhost:5432/dbname
API_KEY=your_api_key_here
SECRET_KEY=your_secret_key_here

# .env (mai committato)
DATABASE_URL=postgres://realuser:realpass@prod.server:5432/proddb
API_KEY=sk-prod1234567890abcdef
SECRET_KEY=super-secret-production-key
```

### Environment Variables Best Practices

```javascript
// ✅ Usa variabili di ambiente
const config = {
  database: {
    url: process.env.DATABASE_URL,
    ssl: process.env.NODE_ENV === 'production'
  },
  api: {
    key: process.env.API_KEY,
    secret: process.env.API_SECRET
  },
  jwt: {
    secret: process.env.JWT_SECRET,
    expiresIn: process.env.JWT_EXPIRES_IN || '24h'
  }
};

// ✅ Validazione environment variables
function validateConfig() {
  const required = [
    'DATABASE_URL',
    'API_KEY',
    'JWT_SECRET'
  ];
  
  for (const key of required) {
    if (!process.env[key]) {
      throw new Error(`Missing required environment variable: ${key}`);
    }
  }
}

// ✅ Default values sicuri
const port = process.env.PORT || 3000;
const nodeEnv = process.env.NODE_ENV || 'development';
```

### .gitignore per Security

```gitignore
# ===== SECRETS E CREDENZIALI =====

# Environment files
.env
.env.local
.env.production
.env.staging
.env.*.local

# Configuration files con secrets
config/secrets.yml
config/database.yml
config/production.json

# SSH Keys
*.pem
*.key
*.p12
*.pfx
id_rsa
id_dsa
id_ed25519

# SSL Certificates
*.crt
*.cer
*.csr

# AWS Credentials
.aws/credentials
.aws/config

# Google Cloud
gcloud/
service-account.json
*.json  # Potenziali service account keys

# Database files
*.db
*.sqlite
*.sqlite3
database.db

# Logs che potrebbero contenere dati sensibili
*.log
logs/
npm-debug.log*
yarn-debug.log*

# Backup files
*.backup
*.bak
*.sql.gz
dump.sql

# IDE files che potrebbero contenere configurazioni
.vscode/settings.json
.idea/workspace.xml

# Temporary files
*.tmp
*.temp
.cache/

# ===== DIPENDENZE CON VULNERABILITÀ =====

# Node modules (ricompila sempre)
node_modules/

# Python
__pycache__/
*.pyc
.venv/
venv/

# Ruby
.bundle/
vendor/bundle/
```

## 2. Controlli di Sicurezza Automatizzati

### GitHub Security Features

```yaml
# .github/workflows/security.yml
name: Security Checks

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  security-scan:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
    
    - name: Run Trivy vulnerability scanner
      uses: aquasecurity/trivy-action@master
      with:
        scan-type: 'fs'
        scan-ref: '.'
        format: 'sarif'
        output: 'trivy-results.sarif'
    
    - name: Upload Trivy scan results
      uses: github/codeql-action/upload-sarif@v2
      with:
        sarif_file: 'trivy-results.sarif'
    
    - name: Run CodeQL Analysis
      uses: github/codeql-action/analyze@v2
      with:
        languages: javascript
    
    - name: Dependency Review
      uses: actions/dependency-review-action@v3
      if: github.event_name == 'pull_request'

  secret-scan:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
      with:
        fetch-depth: 0
    
    - name: Run gitleaks scan
      uses: zricethezav/gitleaks-action@v2.0.0
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Run TruffleHog OSS
      uses: trufflesecurity/trufflehog@main
      with:
        path: ./
        base: main
        head: HEAD

  dependency-check:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Run npm audit
      run: npm audit --audit-level moderate
    
    - name: Run Snyk security scan
      uses: snyk/actions/node@master
      env:
        SNYK_TOKEN: ${{ secrets.SNYK_TOKEN }}
      with:
        args: --severity-threshold=medium
```

### Pre-commit Security Hooks

```bash
#!/bin/bash
# .git/hooks/pre-commit

echo "🔒 Running security checks..."

# Check for secrets in staged files
echo "🔍 Scanning for secrets..."
if command -v gitleaks >/dev/null 2>&1; then
    gitleaks protect --staged --verbose
    if [ $? -ne 0 ]; then
        echo "❌ Secrets detected! Please remove sensitive data."
        exit 1
    fi
fi

# Check for hardcoded IPs and URLs
echo "🌐 Checking for hardcoded endpoints..."
staged_files=$(git diff --cached --name-only --diff-filter=ACM)
if echo "$staged_files" | xargs grep -l "http://\|https://\|[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}" >/dev/null 2>&1; then
    echo "⚠️  Warning: Hardcoded URLs/IPs found in staged files:"
    echo "$staged_files" | xargs grep -n "http://\|https://\|[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}\.[0-9]\{1,3\}"
    read -p "Continue anyway? (y/N): " confirm
    if [ "$confirm" != "y" ] && [ "$confirm" != "Y" ]; then
        exit 1
    fi
fi

# Check for TODO comments with security implications
echo "📝 Checking for security TODOs..."
if echo "$staged_files" | xargs grep -i "TODO.*security\|FIXME.*security\|TODO.*auth\|FIXME.*auth" >/dev/null 2>&1; then
    echo "⚠️  Security-related TODOs found:"
    echo "$staged_files" | xargs grep -n -i "TODO.*security\|FIXME.*security\|TODO.*auth\|FIXME.*auth"
fi

# Check file permissions
echo "🔐 Checking file permissions..."
for file in $staged_files; do
    if [ -f "$file" ]; then
        perms=$(stat -c "%a" "$file" 2>/dev/null || stat -f "%A" "$file" 2>/dev/null)
        if [ "$perms" = "777" ] || [ "$perms" = "666" ]; then
            echo "❌ Dangerous file permissions ($perms) on $file"
            exit 1
        fi
    fi
done

echo "✅ Security checks passed!"
```

### Security Configuration

```javascript
// config/security.js
module.exports = {
  // Content Security Policy
  csp: {
    directives: {
      defaultSrc: ["'self'"],
      styleSrc: ["'self'", "'unsafe-inline'"],
      scriptSrc: ["'self'"],
      imgSrc: ["'self'", "data:", "https:"],
      connectSrc: ["'self'"],
      fontSrc: ["'self'"],
      objectSrc: ["'none'"],
      mediaSrc: ["'self'"],
      frameSrc: ["'none'"],
    },
  },
  
  // HTTPS Enforcement
  hsts: {
    maxAge: 31536000, // 1 year
    includeSubDomains: true,
    preload: true
  },
  
  // Rate Limiting
  rateLimit: {
    windowMs: 15 * 60 * 1000, // 15 minutes
    max: 100, // limit each IP to 100 requests per windowMs
    message: "Too many requests from this IP",
    standardHeaders: true,
    legacyHeaders: false,
  },
  
  // Input Validation
  validation: {
    // Maximum request size
    maxRequestSize: '10mb',
    
    // File upload restrictions
    fileUpload: {
      maxFileSize: 5 * 1024 * 1024, // 5MB
      allowedMimeTypes: [
        'image/jpeg',
        'image/png',
        'image/gif',
        'application/pdf'
      ],
      sanitizeFilename: true
    }
  },
  
  // Session Security
  session: {
    name: 'sessionId', // Don't use default session name
    secret: process.env.SESSION_SECRET,
    resave: false,
    saveUninitialized: false,
    cookie: {
      secure: process.env.NODE_ENV === 'production',
      httpOnly: true,
      maxAge: 24 * 60 * 60 * 1000, // 24 hours
      sameSite: 'strict'
    }
  },
  
  // JWT Security
  jwt: {
    secret: process.env.JWT_SECRET,
    expiresIn: '15m',
    algorithm: 'HS256',
    issuer: 'your-app-name',
    audience: 'your-app-users'
  }
};
```

## 3. Access Control e Permessi

### Branch Protection Rules

```yaml
# .github/branch-protection.yml
main:
  protection:
    required_status_checks:
      strict: true
      contexts:
        - "security-scan"
        - "dependency-check"
        - "tests"
    
    enforce_admins: false
    
    required_pull_request_reviews:
      required_approving_review_count: 2
      dismiss_stale_reviews: true
      require_code_owner_reviews: true
      restrict_dismissals: true
      dismissal_restrictions:
        users: []
        teams: ["security-team"]
    
    restrictions:
      users: []
      teams: ["core-developers"]
    
    allow_force_pushes: false
    allow_deletions: false

develop:
  protection:
    required_status_checks:
      strict: true
      contexts:
        - "security-scan"
        - "tests"
    
    required_pull_request_reviews:
      required_approving_review_count: 1
      dismiss_stale_reviews: true
```

### CODEOWNERS per Security Review

```bash
# .github/CODEOWNERS

# Global rules
* @core-team

# Security-sensitive files require security team review
/.github/workflows/ @security-team @devops-team
/config/security.* @security-team
/.env.example @security-team
/docker/ @security-team @devops-team

# Authentication and authorization
/src/auth/ @security-team @backend-team
/src/middleware/auth.js @security-team
/src/services/auth/ @security-team

# Database and sensitive data
/migrations/ @database-team @security-team
/src/models/ @backend-team @security-team

# Infrastructure and deployment
/infrastructure/ @devops-team @security-team
/deploy/ @devops-team @security-team
/Dockerfile @devops-team

# Package dependencies
package.json @security-team @core-team
package-lock.json @security-team @core-team
requirements.txt @security-team @backend-team
```

### Role-Based Access Control

```javascript
// middleware/rbac.js
const permissions = {
  admin: ['read', 'write', 'delete', 'manage_users'],
  developer: ['read', 'write'],
  reviewer: ['read', 'review'],
  viewer: ['read']
};

function hasPermission(userRole, requiredPermission) {
  return permissions[userRole]?.includes(requiredPermission) || false;
}

function requirePermission(permission) {
  return (req, res, next) => {
    const userRole = req.user?.role;
    
    if (!userRole) {
      return res.status(401).json({ error: 'Authentication required' });
    }
    
    if (!hasPermission(userRole, permission)) {
      return res.status(403).json({ 
        error: 'Insufficient permissions',
        required: permission,
        userRole: userRole
      });
    }
    
    next();
  };
}

// Audit logging
function auditLog(action, resource, user, metadata = {}) {
  console.log({
    timestamp: new Date().toISOString(),
    action,
    resource,
    user: {
      id: user.id,
      email: user.email,
      role: user.role
    },
    ip: metadata.ip,
    userAgent: metadata.userAgent,
    success: metadata.success || true
  });
}

module.exports = {
  hasPermission,
  requirePermission,
  auditLog
};
```

## 4. Incident Response

### Security Incident Procedure

```markdown
# Security Incident Response Plan

## 🚨 Immediate Response (0-1 hour)

### 1. Assess and Contain
- [ ] Identify the scope of the incident
- [ ] Contain the threat (block IPs, revoke tokens, etc.)
- [ ] Preserve evidence
- [ ] Document everything

### 2. Notify Team
- [ ] Alert security team immediately
- [ ] Notify development lead
- [ ] Inform stakeholders if customer data affected

### 3. Initial Actions
```bash
# Revoke compromised tokens immediately
git log --grep="token\|key\|password" --all
git filter-branch --force --index-filter \
  'git rm --cached --ignore-unmatch config/secrets.yml' \
  --prune-empty --tag-name-filter cat -- --all

# Force push to rewrite history (EMERGENCY ONLY)
git push origin --force --all
git push origin --force --tags
```

## 📋 Investigation (1-24 hours)

### 1. Evidence Collection
```bash
# Git forensics
git log --oneline --since="2023-01-01" --author="suspicious@email.com"
git show --stat commit-hash
git diff commit-hash^ commit-hash

# Access log analysis
grep "suspicious-pattern" /var/log/nginx/access.log
grep "error\|warning" /var/log/app/application.log
```

### 2. Impact Assessment
- [ ] Identify affected systems
- [ ] Determine data exposure
- [ ] Assess business impact
- [ ] Check compliance implications

### 3. Root Cause Analysis
- [ ] How did the incident occur?
- [ ] What controls failed?
- [ ] Could it have been prevented?

## 🔧 Recovery (24-72 hours)

### 1. Remediation
- [ ] Apply security patches
- [ ] Update compromised credentials
- [ ] Implement additional controls
- [ ] Test remediation

### 2. Communication
- [ ] Update stakeholders
- [ ] Prepare customer communication
- [ ] Document lessons learned

## 📊 Post-Incident (1 week)

### 1. Review and Improve
- [ ] Conduct post-incident review
- [ ] Update security procedures
- [ ] Implement preventive measures
- [ ] Train team on lessons learned
```

### Emergency Response Scripts

```bash
#!/bin/bash
# scripts/emergency-response.sh

echo "🚨 EMERGENCY SECURITY RESPONSE"
echo "=============================="

# Check for recent suspicious activity
echo "🔍 Recent suspicious commits:"
git log --oneline --since="24 hours ago" | grep -i "password\|secret\|key\|token"

# Check for large files that might contain dumps
echo "📦 Large files in recent commits:"
git log --since="24 hours ago" --name-only --diff-filter=A | xargs ls -la 2>/dev/null | awk '$5 > 1000000'

# Check current branch protections
echo "🛡️  Current branch protections:"
gh api repos/:owner/:repo/branches/main/protection --jq '.required_status_checks, .required_pull_request_reviews'

# Scan for secrets in current state
echo "🔒 Scanning for secrets in current state:"
if command -v gitleaks >/dev/null 2>&1; then
    gitleaks detect --verbose
fi

# Check recent access patterns
echo "👥 Recent contributors:"
git shortlog --since="7 days ago" -sn

# Generate incident report template
cat > incident-report-$(date +%Y%m%d-%H%M%S).md << EOF
# Security Incident Report

**Date**: $(date)
**Reporter**: [Your Name]
**Severity**: [Low/Medium/High/Critical]

## Incident Summary
[Brief description of what happened]

## Timeline
- **$(date)**: Incident discovered
- **$(date)**: [Additional timeline events]

## Impact Assessment
- **Systems Affected**: [List affected systems]
- **Data Exposure**: [Yes/No - describe if yes]
- **Service Availability**: [Any downtime or degradation]

## Root Cause
[What caused this incident]

## Immediate Actions Taken
- [ ] [Action 1]
- [ ] [Action 2]

## Long-term Remediation
- [ ] [Action 1]
- [ ] [Action 2]

## Lessons Learned
[What we learned and how to prevent future incidents]
EOF

echo "📝 Incident report template created: incident-report-$(date +%Y%m%d-%H%M%S).md"
```

## 5. Security Monitoring

### Security Metrics Dashboard

```javascript
// scripts/security-metrics.js
const { exec } = require('child_process');
const fs = require('fs');

class SecurityMetrics {
  async generateReport() {
    const metrics = {
      timestamp: new Date().toISOString(),
      repository: await this.getRepoInfo(),
      secrets: await this.scanSecrets(),
      dependencies: await this.checkDependencies(),
      commits: await this.analyzeCommits(),
      branches: await this.checkBranches()
    };
    
    return metrics;
  }
  
  async scanSecrets() {
    return new Promise((resolve) => {
      exec('gitleaks detect --report-format json', (error, stdout) => {
        if (error) {
          resolve({ status: 'error', message: error.message });
        } else {
          const results = JSON.parse(stdout || '[]');
          resolve({
            status: 'success',
            secretsFound: results.length,
            secrets: results
          });
        }
      });
    });
  }
  
  async checkDependencies() {
    return new Promise((resolve) => {
      exec('npm audit --json', (error, stdout) => {
        const audit = JSON.parse(stdout || '{}');
        resolve({
          vulnerabilities: audit.metadata?.vulnerabilities || 0,
          totalDependencies: audit.metadata?.totalDependencies || 0,
          auditReport: audit
        });
      });
    });
  }
  
  async analyzeCommits() {
    return new Promise((resolve) => {
      const since = new Date(Date.now() - 7 * 24 * 60 * 60 * 1000).toISOString();
      exec(`git log --since="${since}" --oneline`, (error, stdout) => {
        const commits = stdout.trim().split('\n').filter(Boolean);
        const suspiciousPatterns = /password|secret|key|token|credential/i;
        const suspiciousCommits = commits.filter(commit => 
          suspiciousPatterns.test(commit)
        );
        
        resolve({
          totalCommits: commits.length,
          suspiciousCommits: suspiciousCommits.length,
          suspicious: suspiciousCommits
        });
      });
    });
  }
  
  async checkBranches() {
    return new Promise((resolve) => {
      exec('git branch -r', (error, stdout) => {
        const branches = stdout.trim().split('\n').filter(Boolean);
        resolve({
          totalBranches: branches.length,
          branches: branches.map(b => b.trim())
        });
      });
    });
  }
  
  async getRepoInfo() {
    return new Promise((resolve) => {
      exec('git remote get-url origin', (error, stdout) => {
        resolve({
          url: stdout.trim(),
          branch: process.env.GITHUB_REF || 'unknown'
        });
      });
    });
  }
}

// Generate and save report
async function main() {
  const metrics = new SecurityMetrics();
  const report = await metrics.generateReport();
  
  const filename = `security-report-${new Date().toISOString().split('T')[0]}.json`;
  fs.writeFileSync(filename, JSON.stringify(report, null, 2));
  
  console.log('📊 Security Report Generated:', filename);
  console.log('🔒 Secrets Found:', report.secrets.secretsFound);
  console.log('🔍 Vulnerabilities:', report.dependencies.vulnerabilities);
  console.log('⚠️  Suspicious Commits:', report.commits.suspiciousCommits);
}

if (require.main === module) {
  main().catch(console.error);
}

module.exports = SecurityMetrics;
```

### Automated Security Reporting

```yaml
# .github/workflows/security-report.yml
name: Weekly Security Report

on:
  schedule:
    - cron: '0 9 * * 1'  # Every Monday at 9 AM
  workflow_dispatch:

jobs:
  security-report:
    runs-on: ubuntu-latest
    
    steps:
    - name: Checkout code
      uses: actions/checkout@v3
      with:
        fetch-depth: 0
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
    
    - name: Install gitleaks
      run: |
        wget https://github.com/zricethezav/gitleaks/releases/download/v8.15.0/gitleaks_8.15.0_linux_x64.tar.gz
        tar xzf gitleaks_8.15.0_linux_x64.tar.gz
        sudo mv gitleaks /usr/local/bin/
    
    - name: Generate security report
      run: node scripts/security-metrics.js
    
    - name: Upload security report
      uses: actions/upload-artifact@v3
      with:
        name: security-report
        path: security-report-*.json
    
    - name: Send notification
      if: failure()
      uses: 8398a7/action-slack@v3
      with:
        status: failure
        text: '🚨 Security scan failed! Please check the results.'
      env:
        SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK }}
```

## Best Practices Riassunto

### ✅ Security Essentials

1. **Never commit secrets** - Use environment variables
2. **Enable branch protection** - Require reviews and checks
3. **Automate security scans** - Integrate in CI/CD pipeline
4. **Regular dependency updates** - Monitor for vulnerabilities
5. **Access control** - Implement role-based permissions
6. **Audit logging** - Track all security-relevant actions
7. **Incident response plan** - Be prepared for security events

### ❌ Security Anti-Patterns

1. **Hardcoded credentials** in source code
2. **Overly permissive access** to sensitive branches
3. **Ignoring security warnings** from tools
4. **No incident response plan** or procedures
5. **Outdated dependencies** with known vulnerabilities
6. **Weak authentication** or authorization mechanisms
7. **No security training** for development team

### 🔒 Security Checklist

- [ ] All secrets in environment variables
- [ ] .gitignore properly configured
- [ ] Automated security scanning enabled
- [ ] Branch protection rules active
- [ ] Code owners assigned for sensitive files
- [ ] Regular dependency audits
- [ ] Incident response procedures documented
- [ ] Team trained on security practices
- [ ] Security metrics monitored
- [ ] Regular security reviews conducted

---

*La sicurezza è un processo continuo, non un evento singolo. Mantieni sempre aggiornate le tue pratiche di sicurezza.*
