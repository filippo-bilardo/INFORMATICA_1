# Hotfix di Emergenza: Gestione Incidente Critico

## Scenario: Vulnerabilità di Sicurezza Zero-Day

**Incidente**: SQL Injection critica nell'API di ricerca prodotti
**Scoperta**: 14:30 UTC, Venerdì
**Impatto**: Tutti gli utenti esposti, possibile data breach
**Severità**: P0 - Critical Security
**Tempo di risoluzione target**: 2 ore

## Timeline dell'Incidente

### 14:30 - Rilevamento Iniziale

```bash
# Security Alert ricevuto dal sistema di monitoring
echo "🚨 SECURITY ALERT - SQL Injection Detected"
echo "Time: $(date)"
echo "Endpoint: /api/products/search"
echo "Payload: '; DROP TABLE users; --"
echo "Source IP: 203.0.113.42"

# Immediate response team activation
curl -X POST $EMERGENCY_WEBHOOK -d '{
  "incident_type": "SECURITY_BREACH",
  "severity": "P0",
  "description": "SQL Injection in product search API",
  "affected_systems": ["API", "Database", "User Data"],
  "discovered_by": "Security Monitoring System"
}'
```

### 14:32 - Team Emergency Assembly

```bash
# Emergency team notification
echo "📞 EMERGENCY TEAM ASSEMBLY"
echo "=========================="

# Automatic page to on-call engineers
for engineer in "alice.security" "bob.backend" "carol.devops" "dave.manager"; do
  curl -X POST "https://pagerduty.com/api/incidents" \
    -H "Authorization: Token $PAGERDUTY_TOKEN" \
    -d "{
      \"incident\": {
        \"type\": \"incident\",
        \"title\": \"P0 Security: SQL Injection in Search API\",
        \"service\": {\"id\": \"$SERVICE_ID\", \"type\": \"service_reference\"},
        \"assigned_to_user\": {\"id\": \"$engineer\", \"type\": \"user_reference\"},
        \"urgency\": \"high\"
      }
    }"
done

# Start incident war room
echo "🎯 War Room: https://zoom.us/j/emergency123"
echo "📋 Incident Doc: https://docs.company.com/incidents/$(date +%Y%m%d-%H%M)"
```

### 14:35 - Immediate Damage Assessment

```bash
# Security Engineer: Alice
echo "🔍 DAMAGE ASSESSMENT"
echo "==================="

# Check for exploitation attempts
grep -E "(DROP|DELETE|INSERT|UPDATE|UNION|SELECT.*FROM)" /var/log/nginx/access.log | \
  grep "$(date +%d/%b/%Y)" | \
  tail -20

# Database integrity check
psql -h prod-db -U readonly -c "
  SELECT 
    schemaname, 
    tablename, 
    n_tup_ins as inserts_today,
    n_tup_upd as updates_today,
    n_tup_del as deletes_today
  FROM pg_stat_user_tables 
  WHERE schemaname = 'public'
  AND (n_tup_del > 0 OR n_tup_upd > 1000)
  ORDER BY n_tup_del DESC, n_tup_upd DESC;
"

# Check user data exposure
psql -h prod-db -U readonly -c "
  SELECT COUNT(*) as total_users,
         COUNT(CASE WHEN created_at::date = CURRENT_DATE THEN 1 END) as created_today,
         COUNT(CASE WHEN updated_at::date = CURRENT_DATE THEN 1 END) as modified_today
  FROM users;
"

echo "📊 Assessment Complete - No data loss detected"
echo "⚠️  Multiple injection attempts logged"
echo "🔒 Vulnerability still active - IMMEDIATE FIX REQUIRED"
```

### 14:40 - Immediate Containment

```bash
# DevOps Engineer: Carol
echo "🛡️  IMMEDIATE CONTAINMENT"
echo "========================"

# Rate limiting aggressive implementation
kubectl patch configmap nginx-config --type merge -p '{
  "data": {
    "rate-limit": "1r/s",
    "rate-limit-burst": "5"
  }
}'

# WAF rules deployment
cat > emergency-waf-rules.yaml <<'EOF'
apiVersion: v1
kind: ConfigMap
metadata:
  name: emergency-waf-rules
data:
  rules.conf: |
    # Emergency SQL Injection blocking
    SecRule ARGS "@detectSQLi" \
      "id:1001,\
       phase:2,\
       block,\
       msg:'SQL Injection Attack Detected',\
       logdata:'Matched Data: %{MATCHED_VAR} found within %{MATCHED_VAR_NAME}',\
       tag:'application-multi',\
       tag:'language-multi',\
       tag:'platform-multi',\
       tag:'attack-sqli'"
    
    # Block dangerous SQL keywords
    SecRule ARGS "@rx (?i:(\s*(;|'|\"|\\|\/\*|\*\/|--|#|\/\*\!|\/\*\s)))" \
      "id:1002,\
       phase:2,\
       block,\
       msg:'SQL Comment/Terminator Injection',\
       tag:'attack-sqli'"
EOF

kubectl apply -f emergency-waf-rules.yaml

# Restart affected services with WAF rules
kubectl rollout restart deployment/api-gateway
kubectl rollout restart deployment/search-api

echo "✅ Containment measures active"
echo "📈 Monitoring dashboards: https://monitoring.company.com/emergency"
```

### 14:45 - Emergency Hotfix Development

```bash
# Backend Engineer: Bob
echo "⚡ EMERGENCY HOTFIX DEVELOPMENT"
echo "=============================="

# Create emergency hotfix branch
git checkout main
git pull origin main
git flow hotfix start security-sql-injection-fix

# Identify vulnerable code
grep -r "query.*req\." src/api/ --include="*.js" --include="*.ts"

# Vulnerable code found in src/api/products/search.js
cat src/api/products/search.js
# Found: const query = `SELECT * FROM products WHERE name LIKE '%${req.query.q}%'`;

# IMMEDIATE FIX - Parameterized queries
cat > src/api/products/search.js <<'EOF'
const express = require('express');
const { Pool } = require('pg');
const validator = require('validator');
const rateLimit = require('express-rate-limit');

const pool = new Pool({
  connectionString: process.env.DATABASE_URL,
  ssl: { rejectUnauthorized: false }
});

// Emergency rate limiting
const searchLimiter = rateLimit({
  windowMs: 60 * 1000, // 1 minute
  max: 5, // 5 requests per minute
  message: 'Too many search requests, please try again later',
  standardHeaders: true,
  legacyHeaders: false,
});

// Input sanitization middleware
const sanitizeSearchInput = (req, res, next) => {
  const { q, category, sort, limit, offset } = req.query;
  
  // Sanitize search query
  if (q) {
    // Remove dangerous characters
    req.query.q = validator.escape(q.trim());
    
    // Validate length
    if (req.query.q.length > 100) {
      return res.status(400).json({ 
        error: 'Search query too long',
        code: 'SEARCH_QUERY_TOO_LONG'
      });
    }
    
    // Block SQL injection patterns
    const sqlPatterns = [
      /(\s*(;|'|"|\\|\/\*|\*\/|--|#))/gi,
      /\b(DROP|DELETE|INSERT|UPDATE|UNION|SELECT.*FROM|EXEC|EXECUTE)\b/gi
    ];
    
    for (const pattern of sqlPatterns) {
      if (pattern.test(req.query.q)) {
        // Log security incident
        console.error('SQL Injection attempt detected:', {
          query: req.query.q,
          ip: req.ip,
          userAgent: req.get('User-Agent'),
          timestamp: new Date().toISOString()
        });
        
        return res.status(400).json({ 
          error: 'Invalid search query',
          code: 'INVALID_SEARCH_QUERY'
        });
      }
    }
  }
  
  // Validate other parameters
  if (category && !validator.isAlphanumeric(category)) {
    req.query.category = 'all';
  }
  
  if (sort && !['name', 'price', 'date', 'relevance'].includes(sort)) {
    req.query.sort = 'relevance';
  }
  
  // Validate numeric parameters
  if (limit) {
    req.query.limit = Math.min(Math.max(parseInt(limit) || 20, 1), 100);
  }
  
  if (offset) {
    req.query.offset = Math.max(parseInt(offset) || 0, 0);
  }
  
  next();
};

// Secure search endpoint
const searchProducts = async (req, res) => {
  try {
    const { 
      q = '', 
      category = 'all', 
      sort = 'relevance', 
      limit = 20, 
      offset = 0 
    } = req.query;
    
    // Use parameterized query to prevent SQL injection
    let query = `
      SELECT 
        id, 
        name, 
        description, 
        price, 
        category,
        created_at,
        ts_rank(search_vector, plainto_tsquery($1)) as relevance
      FROM products 
      WHERE 1=1
    `;
    
    const params = [];
    let paramIndex = 1;
    
    // Add search filter with parameterized query
    if (q) {
      query += ` AND (
        search_vector @@ plainto_tsquery($${paramIndex}) OR
        name ILIKE $${paramIndex + 1} OR
        description ILIKE $${paramIndex + 1}
      )`;
      params.push(q, `%${q}%`);
      paramIndex += 2;
    }
    
    // Add category filter
    if (category !== 'all') {
      query += ` AND category = $${paramIndex}`;
      params.push(category);
      paramIndex++;
    }
    
    // Add sorting
    switch (sort) {
      case 'name':
        query += ' ORDER BY name ASC';
        break;
      case 'price':
        query += ' ORDER BY price ASC';
        break;
      case 'date':
        query += ' ORDER BY created_at DESC';
        break;
      default:
        query += ' ORDER BY relevance DESC, created_at DESC';
    }
    
    // Add pagination
    query += ` LIMIT $${paramIndex} OFFSET $${paramIndex + 1}`;
    params.push(limit, offset);
    
    const result = await pool.query(query, params);
    
    // Get total count for pagination
    const countQuery = `
      SELECT COUNT(*) as total 
      FROM products 
      WHERE 1=1
      ${q ? 'AND (search_vector @@ plainto_tsquery($1) OR name ILIKE $2 OR description ILIKE $2)' : ''}
      ${category !== 'all' ? `AND category = $${q ? '3' : '1'}` : ''}
    `;
    
    const countParams = [];
    if (q) countParams.push(q, `%${q}%`);
    if (category !== 'all') countParams.push(category);
    
    const countResult = await pool.query(countQuery, countParams);
    
    res.json({
      products: result.rows,
      pagination: {
        total: parseInt(countResult.rows[0].total),
        limit,
        offset,
        hasNext: offset + limit < parseInt(countResult.rows[0].total)
      }
    });
    
  } catch (error) {
    console.error('Search error:', error);
    res.status(500).json({ 
      error: 'Internal server error',
      code: 'SEARCH_ERROR'
    });
  }
};

module.exports = {
  searchProducts: [searchLimiter, sanitizeSearchInput, searchProducts]
};
EOF

# Add comprehensive security tests
cat > tests/security/sql-injection.test.js <<'EOF'
const request = require('supertest');
const app = require('../../src/app');

describe('SQL Injection Security Tests', () => {
  const maliciousPayloads = [
    "'; DROP TABLE products; --",
    "' OR '1'='1",
    "'; DELETE FROM users; --",
    "' UNION SELECT * FROM users --",
    "'; INSERT INTO admin (username) VALUES ('hacker'); --",
    "' OR 1=1 --",
    "'; EXEC xp_cmdshell('rm -rf /'); --"
  ];

  test.each(maliciousPayloads)('should block SQL injection: %s', async (payload) => {
    const response = await request(app)
      .get('/api/products/search')
      .query({ q: payload });
    
    expect(response.status).toBe(400);
    expect(response.body.code).toBe('INVALID_SEARCH_QUERY');
  });

  test('should accept safe search queries', async () => {
    const response = await request(app)
      .get('/api/products/search')
      .query({ q: 'laptop computer' });
    
    expect(response.status).toBe(200);
    expect(response.body).toHaveProperty('products');
  });

  test('should rate limit excessive requests', async () => {
    // Make 6 requests quickly (limit is 5 per minute)
    for (let i = 0; i < 6; i++) {
      const response = await request(app)
        .get('/api/products/search')
        .query({ q: 'test' });
      
      if (i < 5) {
        expect(response.status).toBe(200);
      } else {
        expect(response.status).toBe(429);
      }
    }
  });
});
EOF

# Commit the emergency fix
git add .
git commit -m "SECURITY: Fix critical SQL injection vulnerability in search API

EMERGENCY HOTFIX - P0 Security Issue

Vulnerability: SQL injection in product search endpoint
Impact: All users exposed to potential data breach
Fix: Implemented parameterized queries and input sanitization

Changes:
- Replace string concatenation with parameterized queries
- Add comprehensive input validation and sanitization  
- Implement emergency rate limiting (5 req/min)
- Block dangerous SQL patterns and keywords
- Add security incident logging
- Include comprehensive security test suite

Testing:
- All malicious payloads blocked
- Normal searches work correctly
- Rate limiting active
- Security tests passing

CVE: Pending assignment
Severity: Critical
Timeline: 2 hours from discovery to fix"

echo "🔐 Emergency fix implemented and committed"
```

### 14:55 - Rapid Testing e Validation

```bash
# QA Engineer: Emergency validation
echo "🧪 EMERGENCY TESTING"
echo "==================="

# Run security test suite
npm test tests/security/sql-injection.test.js

# Manual penetration testing
echo "Manual security validation..."

# Test known attack vectors
attack_vectors=(
  "'; DROP TABLE users; --"
  "' OR '1'='1"
  "'; DELETE FROM products; --"
  "' UNION SELECT password FROM users --"
)

for vector in "${attack_vectors[@]}"; do
  echo "Testing: $vector"
  response=$(curl -s -w "%{http_code}" \
    "http://staging-api.company.com/api/products/search?q=$(echo "$vector" | jq -sRr @uri)")
  
  if [[ "$response" == *"400"* ]]; then
    echo "✅ Attack blocked"
  else
    echo "❌ Attack NOT blocked - STATUS: $response"
    exit 1
  fi
done

# Verify normal functionality
echo "Testing normal search functionality..."
normal_response=$(curl -s "http://staging-api.company.com/api/products/search?q=laptop")
if echo "$normal_response" | jq -e '.products' > /dev/null; then
  echo "✅ Normal search working"
else
  echo "❌ Normal search broken"
  exit 1
fi

echo "🎉 All security tests passed"
```

### 15:00 - Emergency Deployment

```bash
# DevOps: Emergency deployment
echo "🚀 EMERGENCY DEPLOYMENT"
echo "======================"

# Finish hotfix branch
git flow hotfix finish security-sql-injection-fix

# Tag emergency release
git tag -a v2.1.2-emergency -m "EMERGENCY: SQL Injection Security Fix

Critical security vulnerability fixed:
- SQL injection in product search API
- Parameterized queries implemented
- Input validation added
- Rate limiting enforced

Deployment: Emergency P0 procedure
Testing: Security test suite passed
Approval: Emergency security team override"

# Push to production immediately
git push origin main develop --tags

# Deploy to production with emergency override
kubectl set image deployment/search-api \
  search-api=company/search-api:v2.1.2-emergency \
  --record

# Wait for rollout
kubectl rollout status deployment/search-api --timeout=300s

# Remove emergency WAF rules after fix is deployed
sleep 60
kubectl delete configmap emergency-waf-rules

# Immediate production validation
echo "Validating production fix..."
prod_test=$(curl -s -w "%{http_code}" \
  "https://api.company.com/api/products/search?q='; DROP TABLE users; --")

if [[ "$prod_test" == *"400"* ]]; then
  echo "✅ Production fix validated"
else
  echo "❌ Production fix FAILED - IMMEDIATE ROLLBACK REQUIRED"
  kubectl rollout undo deployment/search-api
  exit 1
fi

echo "🎉 Emergency deployment successful"
```

### 15:15 - Immediate Post-Incident Actions

```bash
# Security Team: Immediate actions
echo "🔒 POST-INCIDENT IMMEDIATE ACTIONS"
echo "================================="

# Password reset for potentially exposed accounts
psql -h prod-db -U admin -c "
  UPDATE users 
  SET password_reset_required = true,
      password_reset_token = encode(gen_random_bytes(32), 'hex'),
      password_reset_expires = NOW() + INTERVAL '24 hours'
  WHERE last_login > NOW() - INTERVAL '7 days';
"

# Invalidate all active sessions
redis-cli FLUSHDB

# Enable enhanced monitoring
cat > monitoring/enhanced-security.yaml <<'EOF'
apiVersion: v1
kind: ConfigMap
metadata:
  name: enhanced-security-monitoring
data:
  rules.yaml: |
    groups:
    - name: security.rules
      rules:
      - alert: SQLInjectionAttempt
        expr: increase(nginx_http_requests_total{status="400",uri=~".*search.*"}[5m]) > 10
        for: 0m
        labels:
          severity: critical
        annotations:
          summary: "Multiple SQL injection attempts detected"
          
      - alert: UnusualSearchPatterns
        expr: rate(api_search_requests_total[5m]) > 100
        for: 2m
        labels:
          severity: warning
        annotations:
          summary: "Unusual search request rate detected"
EOF

kubectl apply -f monitoring/enhanced-security.yaml

# Customer communication
cat > customer-notification.md <<'EOF'
# Security Incident Notification

Dear ProductFlow Customers,

We are writing to inform you of a security vulnerability that was discovered and immediately fixed in our product search system.

## What Happened
On [DATE] at 14:30 UTC, our security monitoring detected a potential SQL injection vulnerability in our product search API. We immediately implemented emergency containment measures and deployed a fix within 45 minutes.

## What We Did
- Immediately blocked malicious requests
- Deployed emergency rate limiting
- Fixed the vulnerability with parameterized queries
- Enhanced input validation and sanitization
- Implemented additional security monitoring

## Impact
- No customer data was compromised
- No unauthorized access occurred  
- All systems remained operational
- Fix was deployed with zero downtime

## What We're Doing Next
- Comprehensive security audit of all APIs
- Enhanced automated security testing
- Additional security training for development team
- Improved vulnerability detection systems

## What You Should Do
As a precautionary measure, we recommend:
- Changing your password (forced reset implemented)
- Reviewing your recent account activity
- Enabling two-factor authentication if not already active

We sincerely apologize for any concern this may cause and appreciate your continued trust in ProductFlow.

Security Team
ProductFlow Inc.
EOF

echo "📧 Customer notification prepared"
echo "🔍 Enhanced monitoring active"
echo "🔐 Security measures implemented"
```

## Incident Resolution e Learning

### 15:30 - Incident Closure

```bash
# Incident Commander: Final actions
echo "✅ INCIDENT RESOLUTION"
echo "====================

# Final status update
curl -X POST $SLACK_WEBHOOK -d '{
  "text": "🎉 INCIDENT RESOLVED - SQL Injection Vulnerability Fixed",
  "attachments": [{
    "color": "good",
    "fields": [
      {"title": "Duration", "value": "60 minutes", "short": true},
      {"title": "Impact", "value": "Zero data loss", "short": true},
      {"title": "Fix", "value": "Parameterized queries + validation", "short": true},
      {"title": "Status", "value": "Production stable", "short": true}
    ]
  }]
}'

# Update incident tracking
curl -X PATCH "https://api.pagerduty.com/incidents/$INCIDENT_ID" \
  -H "Authorization: Token $PAGERDUTY_TOKEN" \
  -d '{
    "incident": {
      "type": "incident",
      "status": "resolved"
    }
  }'

echo "📊 Incident metrics:"
echo "  Discovery to fix: 25 minutes"
echo "  Fix to deployment: 20 minutes" 
echo "  Total resolution: 45 minutes"
echo "  Downtime: 0 minutes"
echo "  Data compromised: 0 records"
```

### Post-Incident Report (Immediate)

```markdown
# Emergency Incident Report - SQL Injection

## Incident Summary
- **ID**: INC-2024-05-30-001
- **Type**: Security Vulnerability (SQL Injection)
- **Severity**: P0 - Critical
- **Duration**: 45 minutes (14:30 - 15:15 UTC)
- **Impact**: Zero downtime, zero data loss

## Timeline
- **14:30** - Vulnerability detected by monitoring
- **14:32** - Emergency team assembled
- **14:35** - Damage assessment completed
- **14:40** - Containment measures deployed
- **14:45** - Hotfix development started
- **14:55** - Security testing completed
- **15:00** - Emergency deployment executed
- **15:15** - Incident resolved and verified

## Root Cause
SQL injection vulnerability in product search API caused by:
- String concatenation instead of parameterized queries
- Insufficient input validation
- Missing security testing in CI/CD pipeline

## Impact Assessment
- **Systems Affected**: Product Search API
- **Users Affected**: 0 (vulnerability detected before exploitation)
- **Data Compromised**: None
- **Revenue Impact**: None
- **Downtime**: 0 minutes

## Resolution
- Implemented parameterized queries
- Added comprehensive input validation
- Deployed emergency rate limiting
- Enhanced security monitoring

## Immediate Actions Taken
- ✅ Vulnerability patched and deployed
- ✅ Enhanced monitoring implemented
- ✅ User sessions invalidated as precaution
- ✅ Customer notification sent
- ✅ Security team briefed

## Lessons Learned
### What Worked Well
- Fast detection (security monitoring)
- Rapid team response (2 minutes)
- Effective emergency procedures
- Zero-downtime deployment

### What Could Be Improved
- Earlier detection in development
- Automated security testing in CI/CD
- Better input validation standards
- More comprehensive code review process

## Action Items
- [ ] Implement automated security testing in CI/CD
- [ ] Conduct security audit of all APIs
- [ ] Enhanced developer security training
- [ ] Update secure coding standards
- [ ] Improve vulnerability detection tools
```

Questo esempio mostra come gestire un hotfix di emergenza per un incidente critico di sicurezza, dalla scoperta alla risoluzione completa, includendo tutti gli aspetti operativi, tecnici e comunicativi necessari per una risposta efficace.
