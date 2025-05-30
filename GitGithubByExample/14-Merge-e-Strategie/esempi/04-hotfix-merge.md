# Esempio: Hotfix Merge

## Scenario
Un bug critico è stato scoperto in produzione che blocca il login degli utenti. Devi implementare un hotfix immediato seguendo le best practices.

## Obiettivo
Imparare a gestire situazioni di emergenza con hotfix rapidi e sicuri.

## Situazione Iniziale

```
main (v2.1.0) ← PRODUZIONE
├── develop (v2.2.0-dev)
├── feature/dashboard-redesign
└── hotfix/login-fix (da creare)
```

## Problema Identificato

```bash
# Bug report: utenti non riescono a fare login
# Errore: "Invalid token validation"
# File coinvolto: src/auth/validator.js
# Urgenza: CRITICA
```

## Processo Hotfix

### 1. Creazione Branch Hotfix

```bash
# SEMPRE partire da main per hotfix
git checkout main
git pull origin main

# Crea branch hotfix
git checkout -b hotfix/login-fix

# Verifica che siamo sulla versione corretta
git log --oneline -1
```

### 2. Analisi e Fix del Bug

```bash
# Esamina il file problematico
git show HEAD:src/auth/validator.js

# Identifica il problema
# Nel nostro caso: regex di validazione token errata
```

**File: src/auth/validator.js**
```javascript
// PRIMA (problematico)
const tokenRegex = /^[a-zA-Z0-9]{32}$/;

// DOPO (corretto)
const tokenRegex = /^[a-zA-Z0-9-_]{32,}$/;

function validateToken(token) {
    if (!token) {
        return false;
    }
    
    // Fix: gestione corretta di token con caratteri speciali
    return tokenRegex.test(token) && token.length >= 32;
}
```

### 3. Implementazione Fix

```bash
# Modifica il file
nano src/auth/validator.js

# Testa localmente
npm test -- --grep "token validation"
npm run test:integration

# Aggiungi fix
git add src/auth/validator.js
git commit -m "fix(auth): correct token validation regex

- Fixed regex to allow hyphens and underscores
- Added minimum length validation
- Resolves critical login issue in production

Fixes: #TICKET-123"
```

### 4. Testing Accelerato

```bash
# Test specifici per il fix
npm run test:auth
npm run test:login-flow

# Test di regressione rapido
npm run test:critical-path

# Verifica manuale
npm run dev
# Testa login con vari tipi di token
```

### 5. Deploy Hotfix

```bash
# Merge in main (produzione)
git checkout main
git merge --no-ff hotfix/login-fix -m "hotfix: fix critical login validation bug"

# Tag della patch version
git tag -a v2.1.1 -m "Hotfix v2.1.1 - Login validation fix"

# Push immediato
git push origin main
git push origin v2.1.1
```

### 6. Aggiornamento Develop

```bash
# IMPORTANTE: porta il fix anche in develop
git checkout develop
git merge main -m "merge: hotfix v2.1.1 into develop"

# Risolvi eventuali conflitti
git push origin develop
```

### 7. Cleanup

```bash
# Elimina branch hotfix
git branch -d hotfix/login-fix
git push origin --delete hotfix/login-fix
```

## Script di Emergenza

```bash
#!/bin/bash
# emergency-hotfix.sh

HOTFIX_NAME=$1
if [ -z "$HOTFIX_NAME" ]; then
    echo "Usage: ./emergency-hotfix.sh <hotfix-name>"
    exit 1
fi

echo "🚨 Emergency Hotfix: $HOTFIX_NAME"

# Verifica stato clean
if [ -n "$(git status --porcelain)" ]; then
    echo "❌ Working directory not clean!"
    exit 1
fi

# Crea hotfix branch
git checkout main
git pull origin main
git checkout -b "hotfix/$HOTFIX_NAME"

echo "✅ Hotfix branch created: hotfix/$HOTFIX_NAME"
echo "🔧 Ready for emergency fix implementation"
echo "📝 Next steps:"
echo "  1. Implement the fix"
echo "  2. Test thoroughly"
echo "  3. Run: git add . && git commit"
echo "  4. Run: ./deploy-hotfix.sh $HOTFIX_NAME"
```

```bash
#!/bin/bash
# deploy-hotfix.sh

HOTFIX_NAME=$1
CURRENT_BRANCH=$(git branch --show-current)

if [ "$CURRENT_BRANCH" != "hotfix/$HOTFIX_NAME" ]; then
    echo "❌ Not on hotfix branch!"
    exit 1
fi

echo "🚀 Deploying hotfix: $HOTFIX_NAME"

# Verifica che ci sia almeno un commit
if [ -z "$(git log --oneline HEAD ^main)" ]; then
    echo "❌ No commits in hotfix branch!"
    exit 1
fi

# Merge in main
git checkout main
git merge --no-ff "hotfix/$HOTFIX_NAME"

# Determina nuova versione patch
CURRENT_VERSION=$(git describe --tags --abbrev=0)
NEW_VERSION=$(echo $CURRENT_VERSION | awk -F. '{$NF = $NF + 1;} 1' | sed 's/ /./g')

# Crea tag
git tag -a "$NEW_VERSION" -m "Hotfix $NEW_VERSION - $HOTFIX_NAME"

# Deploy
git push origin main
git push origin "$NEW_VERSION"

# Aggiorna develop
git checkout develop
git merge main
git push origin develop

# Cleanup
git branch -d "hotfix/$HOTFIX_NAME"
git push origin --delete "hotfix/$HOTFIX_NAME"

echo "✅ Hotfix $NEW_VERSION deployed successfully!"
```

## Checklist Hotfix

### Pre-Implementation
- [ ] Bug confermato in produzione
- [ ] Gravità valutata (critica/alta)
- [ ] Working directory pulita
- [ ] Branch da main aggiornato

### Implementation
- [ ] Fix implementato minimalmente
- [ ] Test specifici passati
- [ ] Test di regressione rapido
- [ ] Commit message descrittivo

### Deploy
- [ ] Merge in main
- [ ] Tag versione patch
- [ ] Push in produzione
- [ ] Monitoring attivato

### Post-Deploy
- [ ] Fix backportato in develop
- [ ] Branch hotfix eliminato
- [ ] Incident documentation
- [ ] Root cause analysis

## Best Practices Hotfix

### Speed vs Safety
```bash
# ✅ GIUSTO: Fix minimo e sicuro
git commit -m "fix: single line regex correction"

# ❌ SBAGLIATO: Refactoring durante hotfix
git commit -m "refactor: complete auth system rewrite"
```

### Testing Strategy
```bash
# Test mirati e rapidi
npm test -- --grep "critical"
npm run test:regression:fast

# Evita test suite completa
# npm test  # ❌ Troppo lento per emergenza
```

### Communication
- Notifica team immediatamente
- Update stakeholder su progress
- Documenta nel ticket/issue
- Post-mortem dopo risoluzione

## Casi Comuni

### Multiple Environment
```bash
# Hotfix per staging prima di produzione
git checkout main
git merge hotfix/fix-name
git push origin main

# Test in staging
curl -X POST staging.example.com/test

# Poi produzione
git push production main
```

### Rollback Rapido
```bash
# Se il fix causa altri problemi
git checkout main
git reset --hard v2.1.0  # Versione precedente
git push --force-with-lease origin main
```

## Monitoraggio Post-Deploy

```bash
# Check immediate
tail -f /var/log/app.log | grep ERROR

# Metrics dashboard
open https://monitoring.example.com/dashboard

# User feedback monitoring
grep "login" /var/log/user-feedback.log
```

## Prossimi Passi

1. Pratica con [Strategy Selection](../esercizi/02-strategy-selection.md)
2. Studia [Complex Integration](../esercizi/03-complex-integration.md)
3. Approfondisci [Risoluzione Conflitti](../15-Risoluzione-Conflitti/README.md)
