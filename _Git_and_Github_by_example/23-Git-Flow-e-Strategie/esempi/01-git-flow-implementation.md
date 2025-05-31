# Implementazione Completa di Git Flow

## Scenario di Progetto

**Progetto**: E-commerce Platform "ShopFlow"
**Team**: 12 sviluppatori
**Release Cycle**: Bimensile
**Ambiente**: Production, Staging, Development

## Setup Iniziale Git Flow

### 1. Inizializzazione Repository

```bash
# Clone del repository
git clone https://github.com/company/shopflow.git
cd shopflow

# Inizializzazione Git Flow
git flow init

# Configurazione interactive
Which branch should be used for bringing forth production releases?
   - main
Branch name for production releases: [main] 

Which branch should be used for integration of the "next release"?
   - develop
Branch name for "next release" development: [develop] 

How to name your supporting branch prefixes?
Feature branches? [feature/] 
Bugfix branches? [bugfix/] 
Release branches? [release/] 
Hotfix branches? [hotfix/] 
Support branches? [support/] 
Version tag prefix? [] v

# Verifica configurazione
git branch -a
```

### 2. Configurazione Team

```bash
# Script per setup sviluppatori
#!/bin/bash
# setup-developer.sh

echo "🔧 Setup Git Flow per ShopFlow"
echo "==============================="

# Verifica git-flow installato
if ! command -v git-flow &> /dev/null; then
    echo "Installando git-flow..."
    brew install git-flow  # macOS
    # apt-get install git-flow  # Ubuntu
fi

# Clone e configurazione
git clone https://github.com/company/shopflow.git
cd shopflow

# Configurazione Git Flow con settings predefiniti
cat > .gitflow <<EOF
[gitflow "branch"]
	master = main
	develop = develop
[gitflow "prefix"]
	feature = feature/
	bugfix = bugfix/
	release = release/
	hotfix = hotfix/
	support = support/
	versiontag = v
EOF

# Inizializzazione automatica
git flow init -d

echo "✅ Setup completato!"
echo "📚 Leggi la documentazione: docs/git-flow-guide.md"
```

## Workflow Sviluppo Features

### 3. Feature Development Cycle

#### Feature 1: Shopping Cart Enhancement

```bash
# Developer: Alice
echo "🛒 Sviluppo: Enhanced Shopping Cart"

# Avvia nuova feature
git flow feature start shopping-cart-enhancement

# Verifica branch corrente
git branch
# * feature/shopping-cart-enhancement
#   develop
#   main

# Sviluppo della feature
mkdir -p src/components/cart
touch src/components/cart/EnhancedCart.js
touch src/components/cart/CartSummary.js
touch tests/cart/cart.test.js

cat > src/components/cart/EnhancedCart.js <<'EOF'
import React, { useState, useEffect } from 'react';
import { CartSummary } from './CartSummary';

export const EnhancedCart = () => {
  const [items, setItems] = useState([]);
  const [loading, setLoading] = useState(false);

  const updateQuantity = async (itemId, quantity) => {
    setLoading(true);
    try {
      // API call to update quantity
      const response = await fetch(`/api/cart/items/${itemId}`, {
        method: 'PATCH',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ quantity })
      });
      
      const updatedItem = await response.json();
      setItems(prev => prev.map(item => 
        item.id === itemId ? updatedItem : item
      ));
    } catch (error) {
      console.error('Error updating cart:', error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="enhanced-cart">
      <h2>Shopping Cart</h2>
      {loading && <div className="loading">Updating...</div>}
      <div className="cart-items">
        {items.map(item => (
          <div key={item.id} className="cart-item">
            <span>{item.name}</span>
            <input 
              type="number" 
              value={item.quantity}
              onChange={(e) => updateQuantity(item.id, e.target.value)}
            />
            <span>${item.price * item.quantity}</span>
          </div>
        ))}
      </div>
      <CartSummary items={items} />
    </div>
  );
};
EOF

# Test della feature
cat > tests/cart/cart.test.js <<'EOF'
import { render, screen, fireEvent, waitFor } from '@testing-library/react';
import { EnhancedCart } from '../../src/components/cart/EnhancedCart';

describe('EnhancedCart', () => {
  test('updates item quantity', async () => {
    render(<EnhancedCart />);
    
    const quantityInput = screen.getByDisplayValue('2');
    fireEvent.change(quantityInput, { target: { value: '3' } });
    
    await waitFor(() => {
      expect(screen.getByDisplayValue('3')).toBeInTheDocument();
    });
  });

  test('shows loading state during update', async () => {
    render(<EnhancedCart />);
    
    const quantityInput = screen.getByDisplayValue('2');
    fireEvent.change(quantityInput, { target: { value: '3' } });
    
    expect(screen.getByText('Updating...')).toBeInTheDocument();
  });
});
EOF

# Commit progressivi durante sviluppo
git add src/components/cart/EnhancedCart.js
git commit -m "feat(cart): add enhanced cart component with async updates"

git add src/components/cart/CartSummary.js  
git commit -m "feat(cart): add cart summary component"

git add tests/cart/cart.test.js
git commit -m "test(cart): add enhanced cart tests"

# Aggiornamento con develop (se necessario)
git flow feature rebase shopping-cart-enhancement

# Finalizzazione feature
git flow feature finish shopping-cart-enhancement
```

#### Feature 2: User Authentication (Parallela)

```bash
# Developer: Bob
echo "🔐 Sviluppo: User Authentication"

# Avvia feature parallela
git flow feature start user-authentication

# Sviluppo moduli auth
mkdir -p src/auth
touch src/auth/AuthProvider.js
touch src/auth/LoginForm.js
touch src/auth/ProtectedRoute.js

cat > src/auth/AuthProvider.js <<'EOF'
import React, { createContext, useContext, useState, useEffect } from 'react';

const AuthContext = createContext();

export const useAuth = () => {
  const context = useContext(AuthContext);
  if (!context) {
    throw new Error('useAuth must be used within AuthProvider');
  }
  return context;
};

export const AuthProvider = ({ children }) => {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    // Check for existing session
    const token = localStorage.getItem('authToken');
    if (token) {
      validateToken(token);
    } else {
      setLoading(false);
    }
  }, []);

  const login = async (email, password) => {
    setLoading(true);
    try {
      const response = await fetch('/api/auth/login', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password })
      });

      if (response.ok) {
        const { user, token } = await response.json();
        localStorage.setItem('authToken', token);
        setUser(user);
        return { success: true };
      } else {
        const error = await response.json();
        return { success: false, error: error.message };
      }
    } catch (error) {
      return { success: false, error: 'Network error' };
    } finally {
      setLoading(false);
    }
  };

  const logout = () => {
    localStorage.removeItem('authToken');
    setUser(null);
  };

  const validateToken = async (token) => {
    try {
      const response = await fetch('/api/auth/validate', {
        headers: { Authorization: `Bearer ${token}` }
      });

      if (response.ok) {
        const user = await response.json();
        setUser(user);
      } else {
        localStorage.removeItem('authToken');
      }
    } catch (error) {
      console.error('Token validation failed:', error);
      localStorage.removeItem('authToken');
    } finally {
      setLoading(false);
    }
  };

  const value = {
    user,
    login,
    logout,
    loading
  };

  return (
    <AuthContext.Provider value={value}>
      {children}
    </AuthContext.Provider>
  );
};
EOF

# Commit incrementali
git add src/auth/
git commit -m "feat(auth): add authentication provider with context"

# Continua sviluppo e finalizza
# ... (altri file)

git flow feature finish user-authentication
```

## Release Cycle Implementation

### 4. Preparazione Release 2.1.0

```bash
# Release Manager: Carol
echo "📦 Preparazione Release 2.1.0"

# Verifica stato develop
git checkout develop
git pull origin develop

# Visualizza feature incluse
git log --oneline --graph develop ^main

# Avvia release branch
git flow release start 2.1.0

# Branch: release/2.1.0 è stato creato da develop

# Update version numbers
echo "2.1.0" > VERSION
npm version 2.1.0 --no-git-tag-version

# Update changelog
cat > CHANGELOG.md <<'EOF'
# Changelog

## [2.1.0] - 2024-01-15

### Added
- Enhanced shopping cart with real-time updates
- User authentication system with JWT tokens
- Password reset functionality
- Email verification for new accounts

### Fixed
- Cart total calculation bug
- Session timeout handling
- Memory leak in product search

### Changed
- Improved mobile responsive design
- Updated API error messages
- Optimized database queries

### Security
- Added rate limiting to login attempts
- Implemented CSRF protection
- Updated dependencies for security patches
EOF

# Documentation updates
cat > docs/RELEASE_NOTES_2.1.0.md <<'EOF'
# Release Notes v2.1.0

## Overview
This release focuses on user experience improvements and security enhancements.

## New Features

### Enhanced Shopping Cart
- Real-time quantity updates
- Improved loading states
- Better error handling

### User Authentication
- Secure JWT-based authentication
- Password reset via email
- Email verification for new accounts

## Migration Guide

### Database Changes
```sql
-- New user authentication tables
CREATE TABLE user_sessions (
  id UUID PRIMARY KEY,
  user_id UUID REFERENCES users(id),
  token_hash VARCHAR(255),
  expires_at TIMESTAMP
);

-- Add email verification column
ALTER TABLE users ADD COLUMN email_verified BOOLEAN DEFAULT FALSE;
```

### Configuration Updates
```env
# Add to .env
JWT_SECRET=your-secret-key
EMAIL_SERVICE_API_KEY=your-email-api-key
```

## Breaking Changes
- Login API endpoint changed from `/login` to `/api/auth/login`
- Cart API now requires authentication

## Upgrade Instructions
1. Run database migrations: `npm run migrate`
2. Update environment variables
3. Clear user sessions: `npm run clear-sessions`
4. Restart application

EOF

# Bug fixes durante release preparation
git add .
git commit -m "chore(release): update version to 2.1.0"

# Testing della release
npm test
npm run test:integration
npm run test:e2e

# Fix di bug critici trovati in testing
echo "Fixing critical bug found in testing..."
# ... fix implementations ...
git add .
git commit -m "fix(cart): resolve total calculation error in edge cases"

# Finalizza release
git flow release finish 2.1.0

# Questo merge in main e develop, crea tag v2.1.0
```

### 5. Deploy e Post-Release

```bash
# Auto-deploy script triggered by tag
#!/bin/bash
# .github/workflows/deploy.yml equivalent

echo "🚀 Deploying v2.1.0 to production"

# Build production
npm run build:prod

# Run final tests
npm run test:smoke

# Database migrations
npm run migrate:prod

# Deploy to production
kubectl apply -f k8s/production/

# Health checks
sleep 30
curl -f https://shopflow.com/health || exit 1

# Notify team
curl -X POST $SLACK_WEBHOOK -d '{
  "text": "🎉 ShopFlow v2.1.0 deployed successfully!",
  "attachments": [{
    "color": "good",
    "fields": [
      {"title": "Version", "value": "2.1.0", "short": true},
      {"title": "Environment", "value": "Production", "short": true}
    ]
  }]
}'

echo "✅ Deployment completed"
```

## Hotfix Emergency Workflow

### 6. Critical Security Hotfix

```bash
# Security incident detected
echo "🚨 CRITICAL: SQL Injection vulnerability in search"

# Security team lead: Dave
git checkout main
git pull origin main

# Start emergency hotfix
git flow hotfix start security-patch-2.1.1

# Implement critical fix
cat > src/utils/sanitize.js <<'EOF'
import validator from 'validator';

export const sanitizeSearchQuery = (query) => {
  if (!query || typeof query !== 'string') {
    return '';
  }

  // Remove SQL injection patterns
  const cleaned = query
    .replace(/['";\\]/g, '') // Remove quotes and backslashes
    .replace(/\b(DROP|DELETE|INSERT|UPDATE|SELECT|UNION|EXEC)\b/gi, '') // Remove SQL keywords
    .trim();

  // Validate length
  if (cleaned.length > 100) {
    throw new Error('Search query too long');
  }

  return validator.escape(cleaned);
};

export const validateSearchParams = (params) => {
  const { query, category, sort } = params;

  return {
    query: sanitizeSearchQuery(query),
    category: validator.isAlphanumeric(category) ? category : 'all',
    sort: ['price', 'name', 'date'].includes(sort) ? sort : 'relevance'
  };
};
EOF

# Update search endpoint
sed -i 's/const { query } = req.query;/const { query } = validateSearchParams(req.query);/' src/api/search.js

# Add security tests
cat > tests/security/injection.test.js <<'EOF'
import { sanitizeSearchQuery, validateSearchParams } from '../../src/utils/sanitize';

describe('SQL Injection Protection', () => {
  test('removes dangerous SQL keywords', () => {
    const malicious = "'; DROP TABLE users; --";
    const cleaned = sanitizeSearchQuery(malicious);
    expect(cleaned).not.toContain('DROP');
    expect(cleaned).not.toContain(';');
  });

  test('validates search parameters', () => {
    const params = {
      query: "'; DELETE FROM products; --",
      category: "../../etc/passwd",
      sort: "'; DROP TABLE orders; --"
    };
    
    const validated = validateSearchParams(params);
    expect(validated.query).not.toContain('DELETE');
    expect(validated.category).toBe('all');
    expect(validated.sort).toBe('relevance');
  });
});
EOF

# Immediate testing
npm test tests/security/
npm run test:security-scan

# Commit fix
git add .
git commit -m "security: fix SQL injection vulnerability in search endpoint

- Add input sanitization for search queries  
- Remove dangerous SQL keywords
- Add parameter validation
- Include security tests

CVE: Pending
Severity: Critical
Affected: All search functionality"

# Finish hotfix (merges to main and develop, creates tag)
git flow hotfix finish security-patch-2.1.1

# Emergency deploy
git push origin main develop --tags

# Trigger immediate deployment
curl -X POST "$DEPLOY_WEBHOOK" -d '{
  "version": "2.1.1",
  "urgent": true,
  "reason": "Critical security patch"
}'
```

## Advanced Git Flow Customization

### 7. Custom Hook Implementation

```bash
# .git/hooks/post-flow-feature-start
#!/bin/bash
# Automatically executed after git flow feature start

FEATURE_NAME="$1"

echo "🎯 Setting up feature: $FEATURE_NAME"

# Create feature-specific directories if needed
if [[ "$FEATURE_NAME" == *"auth"* ]]; then
    mkdir -p src/auth tests/auth docs/auth
    echo "Created auth directories"
fi

if [[ "$FEATURE_NAME" == *"cart"* ]]; then
    mkdir -p src/cart tests/cart
    echo "Created cart directories" 
fi

# Create feature tracking issue
if command -v gh &> /dev/null; then
    gh issue create \
        --title "Feature: $FEATURE_NAME" \
        --body "Tracking issue for feature branch: feature/$FEATURE_NAME" \
        --label "feature,in-progress"
fi

# Add feature branch to project board
# (GitHub CLI or API call)

echo "✅ Feature $FEATURE_NAME setup completed"
```

### 8. Automated Quality Gates

```bash
# .git/hooks/pre-flow-release-start
#!/bin/bash
# Quality gates before release

echo "🔍 Running pre-release quality checks..."

# Code coverage check
COVERAGE=$(npm test -- --coverage --silent | grep "All files" | awk '{print $10}' | sed 's/%//')
if (( $(echo "$COVERAGE < 80" | bc -l) )); then
    echo "❌ Code coverage too low: $COVERAGE%"
    echo "Required: 80%"
    exit 1
fi

# Security audit
if ! npm audit --audit-level moderate; then
    echo "❌ Security vulnerabilities found"
    exit 1
fi

# Linting
if ! npm run lint; then
    echo "❌ Linting errors found"
    exit 1
fi

# Integration tests
if ! npm run test:integration; then
    echo "❌ Integration tests failed"
    exit 1
fi

echo "✅ All quality checks passed"
```

## Metrics and Monitoring

### 9. Git Flow Analytics

```python
# scripts/gitflow_analytics.py
import git
import json
from datetime import datetime, timedelta
from collections import defaultdict

def analyze_gitflow_metrics():
    """Analyze Git Flow workflow efficiency."""
    
    repo = git.Repo('.')
    
    # Analyze feature branches
    feature_metrics = analyze_feature_branches(repo)
    
    # Analyze release cycles
    release_metrics = analyze_releases(repo)
    
    # Analyze hotfixes
    hotfix_metrics = analyze_hotfixes(repo)
    
    return {
        'features': feature_metrics,
        'releases': release_metrics,
        'hotfixes': hotfix_metrics,
        'overall_health': calculate_health_score(feature_metrics, release_metrics, hotfix_metrics)
    }

def analyze_feature_branches(repo):
    """Analyze feature branch patterns."""
    
    features = []
    
    # Get all feature branches (including deleted ones from reflog)
    for ref in repo.heads:
        if ref.name.startswith('feature/'):
            feature_data = {
                'name': ref.name,
                'start_date': list(repo.iter_commits(ref))[-1].committed_date,
                'end_date': ref.commit.committed_date,
                'commits': len(list(repo.iter_commits(ref))),
                'files_changed': len(ref.commit.stats.files),
                'lines_added': ref.commit.stats.total['insertions'],
                'lines_deleted': ref.commit.stats.total['deletions']
            }
            
            # Calculate duration
            start = datetime.fromtimestamp(feature_data['start_date'])
            end = datetime.fromtimestamp(feature_data['end_date'])
            feature_data['duration_days'] = (end - start).days
            
            features.append(feature_data)
    
    # Calculate averages
    if features:
        avg_duration = sum(f['duration_days'] for f in features) / len(features)
        avg_commits = sum(f['commits'] for f in features) / len(features)
        avg_files = sum(f['files_changed'] for f in features) / len(features)
    else:
        avg_duration = avg_commits = avg_files = 0
    
    return {
        'total_features': len(features),
        'avg_duration_days': avg_duration,
        'avg_commits_per_feature': avg_commits,
        'avg_files_per_feature': avg_files,
        'features': features
    }

def generate_flow_report():
    """Generate comprehensive Git Flow report."""
    
    metrics = analyze_gitflow_metrics()
    
    report = f"""
# Git Flow Analytics Report
Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}

## Feature Development
- Total features: {metrics['features']['total_features']}
- Average duration: {metrics['features']['avg_duration_days']:.1f} days
- Average commits per feature: {metrics['features']['avg_commits_per_feature']:.1f}

## Release Cycle
- Total releases: {metrics['releases']['total_releases']}
- Average time between releases: {metrics['releases']['avg_cycle_days']:.1f} days
- Average features per release: {metrics['releases']['avg_features_per_release']:.1f}

## Hotfixes
- Total hotfixes: {metrics['hotfixes']['total_hotfixes']}
- Hotfix frequency: {metrics['hotfixes']['frequency_per_month']:.1f} per month

## Workflow Health Score: {metrics['overall_health']}/100

### Recommendations
"""
    
    if metrics['features']['avg_duration_days'] > 7:
        report += "- ⚠️ Feature branches too long-lived. Consider smaller features.\n"
    
    if metrics['hotfixes']['frequency_per_month'] > 2:
        report += "- ⚠️ High hotfix frequency. Review quality processes.\n"
    
    if metrics['overall_health'] < 70:
        report += "- 🔴 Workflow needs improvement. Review processes.\n"
    
    return report

# Run analytics
if __name__ == "__main__":
    print(generate_flow_report())
```

## Conclusione dell'Implementazione

Questo esempio completo di Git Flow mostra:

1. **Setup strutturato** del workflow per team enterprise
2. **Sviluppo parallelo** di features con isolamento
3. **Release management** con controlli qualità
4. **Hotfix emergency** per problemi critici
5. **Automazione** tramite hooks e script
6. **Monitoring** delle metriche workflow

Il workflow Git Flow, se implementato correttamente, fornisce:
- Stabilità della produzione
- Controllo qualità robusto
- Gestione release prevedibile
- Procedure emergency chiare
- Tracciabilità completa delle modifiche

Questo approccio è ideale per progetti enterprise con team grandi e release cycle strutturati.
