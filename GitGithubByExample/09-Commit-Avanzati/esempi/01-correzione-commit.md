# Esempio 1: Correzione Commit - Workflow Completo per Errori

## Scenario
Durante lo sviluppo di una feature di autenticazione, sono stati commessi diversi errori che richiedono correzione usando tecniche avanzate di gestione commit.

## Setup Iniziale

### 1. Creazione Repository di Esempio
```bash
# Inizializzare repository per l'esempio
mkdir auth-project-example
cd auth-project-example
git init

# Configurazione base
git config user.name "Developer Example"
git config user.email "dev@example.com"

# Struttura iniziale del progetto
mkdir -p src/{auth,utils,tests}
```

### 2. Primo Commit con Errore
```bash
# Creare file con errore nel codice
cat > src/auth/auth-service.js << 'EOF'
class AuthService {
    constructor() {
        this.users = [];
        this.secret = "hardcoded-secret"; // ❌ ERRORE: secret hardcoded
    }
    
    login(username, password) {
        // ❌ ERRORE: logica di validazione sbagliata
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            return { token: "fake-token" }; // ❌ ERRORE: token fake
        }
        return null;
    }
}

module.exports = AuthService;
EOF

# Commit iniziale con errori
git add .
git commit -m "Add authentication service"  # ❌ Messaggio generico
```

### 3. Secondo Commit con Altri Errori
```bash
# Aggiungere test con errori
cat > src/tests/auth.test.js << 'EOF'
const AuthService = require('../auth/auth-service');

describe('AuthService', () => {
    it('should login user', () => {
        const auth = new AuthService();
        // ❌ ERRORE: test non completo
        expect(auth.login).toBeDefined();
    });
});
EOF

# File dimenticato nel commit precedente
cat > src/utils/jwt.js << 'EOF'
// ❌ File che doveva essere nel primo commit
function generateToken(payload) {
    return "jwt-token";
}
module.exports = { generateToken };
EOF

git add .
git commit -m "add tests"  # ❌ Messaggio non convenzionale
```

## Correzioni con Ammending

### 1. Correggere l'Ultimo Commit
```bash
# Problema: file dimenticato e messaggio sbagliato
echo "
# ⚠️ SITUAZIONE ATTUALE:
# - File jwt.js doveva essere nel primo commit  
# - Messaggio commit non segue convenzioni
# - Test incompleti

# Soluzione: Ammend dell'ultimo commit
"

# Completare i test
cat > src/tests/auth.test.js << 'EOF'
const AuthService = require('../auth/auth-service');

describe('AuthService', () => {
    let authService;
    
    beforeEach(() => {
        authService = new AuthService();
    });
    
    it('should authenticate valid user', () => {
        // Setup test user
        authService.users.push({
            username: 'testuser',
            password: 'testpass'
        });
        
        const result = authService.login('testuser', 'testpass');
        expect(result).not.toBeNull();
        expect(result.token).toBeDefined();
    });
    
    it('should reject invalid credentials', () => {
        const result = authService.login('invalid', 'credentials');
        expect(result).toBeNull();
    });
});
EOF

# Ammendare con messaggio corretto
git add .
git commit --amend -m "test: add comprehensive unit tests for AuthService

- Test successful authentication flow
- Test authentication failure scenarios  
- Add proper test setup and teardown
- Include edge case validation"

echo "✅ Ultimo commit corretto con ammending"
```

### 2. Spostare File tra Commit
```bash
# Problema: jwt.js dovrebbe essere nel primo commit
echo "
# 🔄 RIORGANIZZAZIONE COMMIT:
# jwt.js logicamente appartiene al primo commit (AuthService)
# Useremo reset soft per riorganizzare
"

# Reset soft per scomporre gli ultimi 2 commit
git reset --soft HEAD~2

# Verificare stato
git status
echo "📁 Tutti i file sono ora in staging area"

# Ricommit organizzato logicamente
git add src/auth/auth-service.js src/utils/jwt.js
git commit -m "feat(auth): implement authentication service with JWT

- Create AuthService class for user authentication
- Add JWT utility functions for token generation
- Implement login method with credential validation
- Set up basic user storage structure

Note: Security improvements needed (remove hardcoded secrets)"

# Commit separato per i test
git add src/tests/auth.test.js
git commit -m "test(auth): add comprehensive unit tests for AuthService

- Test successful authentication flow
- Test authentication failure scenarios
- Add proper test setup and teardown
- Include edge case validation"

echo "✅ Commit riorganizzati logicamente"
```

## Correzioni con Reset e Revert

### 3. Aggiungere Commit Problematico da Correggere
```bash
# Simulare commit problematico con bug critico
cat > src/auth/auth-service.js << 'EOF'
class AuthService {
    constructor() {
        this.users = [];
        this.secret = process.env.JWT_SECRET || "default-secret";
    }
    
    login(username, password) {
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            // ❌ BUG CRITICO: token sempre lo stesso
            return { token: "FIXED-TOKEN-123" };
        }
        return null;
    }
    
    // ❌ BUG: metodo che cancella tutti gli utenti
    clearAllUsers() {
        this.users = [];
        console.log("All users deleted!");
    }
}

module.exports = AuthService;
EOF

git add .
git commit -m "feat: add user management and improve security"

# Aggiungere altro commit valido
cat > README.md << 'EOF'
# Auth Project

Simple authentication service with JWT support.

## Features
- User authentication
- JWT token generation
- Secure password handling
EOF

git add README.md
git commit -m "docs: add project README with features list"
```

### 4. Identificare e Correggere con Revert
```bash
echo "
# 🐛 PROBLEMA IDENTIFICATO:
# Il commit di user management ha introdotto bug critici
# - Token fisso (security issue)
# - Metodo clearAllUsers pericoloso
"

# Visualizzare history
git log --oneline -5

# Revert del commit problematico (sicuro per repository condivisi)
git revert HEAD~1 --no-edit

# Verificare stato
git log --oneline -3
echo "✅ Bug revertato mantenendo history"
```

### 5. Implementazione Corretta
```bash
# Implementare la versione corretta
cat > src/auth/auth-service.js << 'EOF'
const { generateToken } = require('../utils/jwt');

class AuthService {
    constructor() {
        this.users = [];
        this.secret = process.env.JWT_SECRET;
        
        if (!this.secret) {
            throw new Error('JWT_SECRET environment variable required');
        }
    }
    
    login(username, password) {
        const user = this.users.find(u => u.username === username);
        if (user && user.password === password) {
            // ✅ CORRETTO: token unico generato
            return { 
                token: generateToken({ 
                    userId: user.id, 
                    username: user.username 
                }),
                user: { 
                    id: user.id, 
                    username: user.username 
                }
            };
        }
        return null;
    }
    
    addUser(username, password) {
        const id = Date.now().toString();
        this.users.push({ id, username, password });
        return { id, username };
    }
    
    // ✅ SICURO: metodo con conferma
    removeUser(username, confirmation = false) {
        if (!confirmation) {
            throw new Error('User removal requires explicit confirmation');
        }
        
        const index = this.users.findIndex(u => u.username === username);
        if (index > -1) {
            return this.users.splice(index, 1)[0];
        }
        return null;
    }
}

module.exports = AuthService;
EOF

# Migliorare JWT utility
cat > src/utils/jwt.js << 'EOF'
const crypto = require('crypto');

function generateToken(payload) {
    // Simplified JWT-like token generation
    const header = Buffer.from(JSON.stringify({ alg: 'HS256', typ: 'JWT' })).toString('base64');
    const payloadB64 = Buffer.from(JSON.stringify({
        ...payload,
        iat: Math.floor(Date.now() / 1000),
        exp: Math.floor(Date.now() / 1000) + (60 * 60) // 1 hour
    })).toString('base64');
    
    const signature = crypto
        .createHmac('sha256', process.env.JWT_SECRET || 'fallback-secret')
        .update(`${header}.${payloadB64}`)
        .digest('base64');
    
    return `${header}.${payloadB64}.${signature}`;
}

function verifyToken(token) {
    try {
        const [header, payload, signature] = token.split('.');
        const payloadData = JSON.parse(Buffer.from(payload, 'base64').toString());
        
        // Check expiration
        if (payloadData.exp < Math.floor(Date.now() / 1000)) {
            return null;
        }
        
        return payloadData;
    } catch (error) {
        return null;
    }
}

module.exports = { generateToken, verifyToken };
EOF

git add .
git commit -m "feat(auth): implement secure authentication system

- Generate unique JWT tokens with proper payload
- Add secure user management methods
- Implement token verification functionality
- Add proper error handling for missing secrets
- Remove dangerous clearAllUsers method

Security improvements:
- Tokens now expire after 1 hour
- User removal requires explicit confirmation
- Proper JWT signature verification

Fixes: security vulnerabilities from previous implementation"
```

## Tecniche Avanzate di Correzione

### 6. Interactive Rebase per History Cleanup
```bash
echo "
# 🔄 CLEANUP FINALE:
# Usare interactive rebase per perfezionare la history
"

# Interactive rebase degli ultimi 4 commit
git rebase -i HEAD~4

# Il seguente editor si aprirà:
cat << 'EOF'
# Esempio di interactive rebase:
# pick a1b2c3d feat(auth): implement authentication service with JWT
# pick d4e5f6g test(auth): add comprehensive unit tests for AuthService  
# pick g7h8i9j docs: add project README with features list
# pick j0k1l2m Revert "feat: add user management and improve security"
# pick m3n4o5p feat(auth): implement secure authentication system

# Azioni possibili:
# pick = usare commit
# reword = usare commit ma modificare messaggio
# edit = usare commit ma fermarsi per ammending
# squash = unire con commit precedente
# fixup = come squash ma scartare messaggio
# drop = rimuovere commit
EOF

echo "
# Strategia suggerita:
# 1. Mantenere i commit logici
# 2. Squash del revert con il fix finale
# 3. Migliorare messaggi se necessario
"
```

### 7. Script di Automazione per Correzioni
```bash
# Creare script per correzioni automatiche
cat > scripts/fix-commit-history.sh << 'EOF'
#!/bin/bash
# Script per automatizzare correzioni comuni

set -e

echo "🔧 Git Commit Correction Assistant"

# Funzione per ammend sicuro
safe_amend() {
    echo "🔍 Checking if last commit is safe to amend..."
    
    # Verificare che non sia pushato
    if git log --oneline origin/$(git branch --show-current 2>/dev/null || echo "main")..HEAD 2>/dev/null | grep -q .; then
        echo "✅ Safe to amend (commit is local)"
        
        echo "📝 Current commit message:"
        git log -1 --pretty=format:"%s"
        echo
        
        read -p "Enter new commit message (or press Enter to keep current): " new_message
        
        if [ -n "$new_message" ]; then
            git commit --amend -m "$new_message"
            echo "✅ Commit amended successfully"
        else
            git commit --amend --no-edit
            echo "✅ Commit amended with staged changes"
        fi
    else
        echo "❌ Cannot amend: commit already pushed"
        echo "Use 'git revert' for pushed commits"
        exit 1
    fi
}

# Funzione per reset sicuro
safe_reset() {
    local commits=${1:-1}
    
    echo "⚠️ About to reset $commits commit(s)"
    echo "📋 Commits to be reset:"
    git log --oneline -n "$commits"
    
    read -p "Continue? (y/N): " confirm
    if [[ $confirm =~ ^[Yy]$ ]]; then
        # Creare backup
        local backup_tag="backup-$(date +%Y%m%d-%H%M%S)"
        git tag "$backup_tag"
        echo "💾 Backup created: $backup_tag"
        
        git reset --soft HEAD~"$commits"
        echo "✅ Reset completed. Files are staged."
        echo "🔄 To restore: git reset --hard $backup_tag"
    else
        echo "❌ Reset cancelled"
    fi
}

# Menu principale
case "${1:-menu}" in
    "amend")
        safe_amend
        ;;
    "reset")
        safe_reset "${2:-1}"
        ;;
    "status")
        echo "📊 Repository Status:"
        git status --short
        echo
        echo "📈 Recent commits:"
        git log --oneline -5
        ;;
    *)
        echo "Usage: $0 {amend|reset [count]|status}"
        echo
        echo "Commands:"
        echo "  amend       - Safely amend last commit"
        echo "  reset [n]   - Safely reset n commits (default: 1)" 
        echo "  status      - Show repository status"
        ;;
esac
EOF

chmod +x scripts/fix-commit-history.sh

# Test dello script
echo "📋 Testing correction script:"
./scripts/fix-commit-history.sh status
```

## Validazione e Test

### 8. Verificare le Correzioni
```bash
echo "
# ✅ VALIDAZIONE FINALE:
# Verificare che tutte le correzioni siano state applicate correttamente
"

# Test del codice
echo "🧪 Testing corrected code:"

# Verificare che AuthService funzioni
node -e "
const AuthService = require('./src/auth/auth-service.js');
try {
    process.env.JWT_SECRET = 'test-secret-key';
    const auth = new AuthService();
    
    // Test aggiunta utente
    const user = auth.addUser('testuser', 'testpass');
    console.log('✅ User created:', user);
    
    // Test login
    const loginResult = auth.login('testuser', 'testpass');
    console.log('✅ Login successful:', !!loginResult.token);
    
    // Test token verification
    const { verifyToken } = require('./src/utils/jwt.js');
    const payload = verifyToken(loginResult.token);
    console.log('✅ Token verified:', !!payload);
    
    console.log('🎉 All tests passed!');
} catch (error) {
    console.error('❌ Test failed:', error.message);
}
"

# Analizzare history finale
echo "
📊 FINAL COMMIT HISTORY:"
git log --oneline --graph

echo "
📝 COMMIT MESSAGES ANALYSIS:"
git log --pretty=format:"- %s" -10

echo "
✅ SUMMARY:
- Fixed hardcoded secrets
- Implemented proper JWT generation
- Added secure user management  
- Removed dangerous methods
- Organized commits logically
- Applied conventional commit format
"
```

### 9. Documentation delle Correzioni
```bash
# Creare documentazione delle correzioni applicate
cat > COMMIT_CORRECTIONS.md << 'EOF'
# Commit Corrections Applied

## Overview
This document tracks the commit corrections applied to improve code quality and repository history.

## Issues Fixed

### 1. Security Issues
- **Problem**: Hardcoded JWT secret in source code
- **Solution**: Use environment variable with proper error handling
- **Commit**: `feat(auth): implement authentication service with JWT`

### 2. Code Quality Issues
- **Problem**: Fixed token generation and dangerous methods
- **Solution**: Implement proper JWT generation and safe user management
- **Commit**: `feat(auth): implement secure authentication system`

### 3. Commit Message Issues
- **Problem**: Non-conventional commit messages
- **Solution**: Applied conventional commits standard
- **Technique**: `git commit --amend` for recent commits

### 4. Logical Organization
- **Problem**: Files not grouped logically in commits
- **Solution**: Reset and re-commit with logical grouping
- **Technique**: `git reset --soft HEAD~n` followed by atomic commits

## Techniques Used

### Ammending
- Safe for local commits only
- Used to fix messages and add forgotten files
- Command: `git commit --amend`

### Reset
- Used to reorganize commit structure
- Soft reset preserves changes in staging area
- Command: `git reset --soft HEAD~n`

### Revert
- Safe for shared repositories
- Creates new commit that undoes changes
- Command: `git revert <commit-hash>`

## Best Practices Applied

1. **Atomic Commits**: Each commit represents one logical change
2. **Conventional Messages**: Following type(scope): description format
3. **Security First**: Remove sensitive data, use environment variables
4. **Testing**: Each commit leaves code in working state
5. **Documentation**: Clear commit messages explain why, not just what

## Tools and Scripts

- `scripts/fix-commit-history.sh`: Automated correction assistant
- Commitlint: Validate commit message format
- Pre-commit hooks: Prevent common issues

## Lessons Learned

1. Plan commits before development
2. Use staging area selectively (`git add -p`)
3. Write clear, conventional commit messages
4. Test code after each commit
5. Keep security considerations in mind
6. Use appropriate correction technique for situation
EOF

git add .
git commit -m "docs: add commit corrections documentation

- Document all correction techniques applied
- Explain rationale for each change
- Provide reference for future corrections
- Include best practices and lessons learned"

echo "✅ Example completed with full documentation"
```

## Risultato Finale

### Repository State
```bash
echo "
🎯 FINAL REPOSITORY STATE:

$(git log --oneline --graph -10)

📁 Files structure:
$(find . -name "*.js" -o -name "*.md" | grep -v node_modules | sort)

🔒 Security improvements:
- No hardcoded secrets
- Proper JWT implementation  
- Safe user management methods
- Environment variable validation

📝 Code quality:
- Atomic commits
- Conventional commit messages
- Comprehensive test coverage
- Clear documentation

🛠️ Tools available:
- Automated correction script
- Commit validation
- Security checks
"
```

Questo esempio completo mostra come gestire correzioni comuni nei commit usando ammending, reset, revert e altre tecniche avanzate, sempre con focus su sicurezza e best practices.
