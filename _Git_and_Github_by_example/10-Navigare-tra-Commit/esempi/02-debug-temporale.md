# 02 - Debug Temporale: Investigazione Detective con Git

## 📖 Scenario

Sei il **Senior Developer** di **FinTech Solutions**, e questa mattina è arrivata una segnalazione critica: il sistema di pagamenti ha iniziato a fallire per alcune transazioni. Il bug non c'era venerdì scorso, ma ora è presente. Devi usare la navigazione Git come una macchina del tempo per trovare esattamente quando e come si è introdotto il problema.

## 🎯 Obiettivi dell'Esempio

- ✅ Debugging usando navigazione temporale
- ✅ Identificazione del commit problematico
- ✅ Uso di git bisect per ricerca binaria
- ✅ Analisi di regressioni nel codice
- ✅ Workflow investigativo strutturato
- ✅ Documentazione del processo di debugging

## 📋 Prerequisiti

- Comprensione di git checkout e detached HEAD
- Familiarità con testing di base
- Conoscenza di git log e git show

## ⏱️ Durata Stimata

**45-60 minuti** (investigazione completa)

---

## 🚨 Setup del Caso Critico

### 1. Creazione del Repository "Problematico"

```bash
# Setup ambiente di test
cd ~/progetti
mkdir fintech-payment-debug
cd fintech-payment-debug
git init

echo "# FinTech Payment System" > README.md
git add .
git commit -m "initial: Setup repository"

# Sistema funzionante iniziale (versione 1.0)
mkdir src tests
cat > src/payment.js << 'EOF'
class PaymentProcessor {
    constructor(config) {
        this.config = config;
        this.validCurrencies = ['EUR', 'USD', 'GBP'];
    }
    
    validateAmount(amount) {
        return amount > 0 && amount <= 10000;
    }
    
    validateCurrency(currency) {
        return this.validCurrencies.includes(currency);
    }
    
    processPayment(amount, currency, cardToken) {
        if (!this.validateAmount(amount)) {
            throw new Error('Invalid amount');
        }
        
        if (!this.validateCurrency(currency)) {
            throw new Error('Invalid currency');
        }
        
        // Processo di pagamento
        return {
            success: true,
            transactionId: `tx_${Date.now()}`,
            amount: amount,
            currency: currency
        };
    }
}

module.exports = PaymentProcessor;
EOF

# Test funzionante
cat > tests/payment.test.js << 'EOF'
const PaymentProcessor = require('../src/payment');

const processor = new PaymentProcessor({apiKey: 'test'});

// Test base
try {
    const result = processor.processPayment(100, 'EUR', 'card_test');
    console.log('✅ Test base passed:', result.success);
} catch (error) {
    console.log('❌ Test base failed:', error.message);
}

// Test edge case
try {
    const result = processor.processPayment(9999, 'USD', 'card_test');
    console.log('✅ Test edge case passed:', result.success);
} catch (error) {
    console.log('❌ Test edge case failed:', error.message);
}
EOF

git add .
git commit -m "feat: Payment processor base implementazione"
git tag v1.0-working

# Miglioramento 1: Aggiunta logging
cat >> src/payment.js << 'EOF'

    log(message) {
        console.log(`[Payment] ${new Date().toISOString()}: ${message}`);
    }
EOF

git add .
git commit -m "feat: Aggiunto sistema di logging"

# Miglioramento 2: Validazione carta
sed -i 's/processPayment(amount, currency, cardToken) {/processPayment(amount, currency, cardToken) {\n        this.log(\`Processing payment: \${amount} \${currency}\`);/' src/payment.js

git add .
git commit -m "feat: Logging delle transazioni"

# INTRODUZIONE DEL BUG (commit problematico)
sed -i 's/amount > 0 && amount <= 10000/amount > 0 \&\& amount < 10000/' src/payment.js

git add .
git commit -m "refactor: Ottimizzazione validazione amount"

# Sviluppo continua (maschera il bug)
cat >> src/payment.js << 'EOF'

    getTransactionFee(amount) {
        return amount * 0.025; // 2.5% fee
    }
EOF

git add .
git commit -m "feat: Calcolo commissioni transazione"

# Altro commit innocuo
echo "// Version 1.1" >> src/payment.js
git add .
git commit -m "docs: Aggiornamento versione"

# Aggiungi più features per complicare l'investigazione
cat > src/security.js << 'EOF'
class SecurityValidator {
    static validateCard(token) {
        return token && token.startsWith('card_');
    }
}

module.exports = SecurityValidator;
EOF

git add .
git commit -m "feat: Validatore sicurezza carte"

echo "🚨 Setup completato! Il bug è nascosto nella cronologia..."
echo "💡 Suggerimento: il test con amount=10000 dovrebbe fallire ora"
```

### 2. Verifica del Problema

```bash
# Test attuale (dovrebbe fallire)
echo "=== TEST DEL PROBLEMA ATTUALE ==="
node tests/payment.test.js

# Output atteso:
# ✅ Test base passed: true
# ❌ Test edge case failed: Invalid amount

echo "🔍 Il problema è confermato! Iniziamo l'investigazione..."
```

---

## 🕵️ Investigazione Detective

### Fase 1: Analisi Iniziale

```bash
echo "=== FASE 1: ANALISI INIZIALE ==="

# Checkpoint di sicurezza
git tag debug-start
git stash push -m "Debug session backup"

# Analizza cronologia recente
echo "📅 Commit recenti:"
git log --oneline -10

echo ""
echo "📊 Statistiche modifiche:"
git log --stat -5

echo ""
echo "🔍 File modificati di recente:"
git log --name-only -5 | grep -v "^$" | sort | uniq
```

### Fase 2: Test di Regressione

```bash
echo "=== FASE 2: TEST DI REGRESSIONE ==="

# Funzione di test automatico
test_payment_system() {
    echo "🧪 Testing payment system al commit: $(git log --oneline -1)"
    
    # Test critico
    node -e "
        const PaymentProcessor = require('./src/payment');
        const processor = new PaymentProcessor({apiKey: 'test'});
        try {
            const result = processor.processPayment(10000, 'EUR', 'card_test');
            console.log('✅ PASS: amount=10000 accettato');
            process.exit(0);
        } catch (error) {
            console.log('❌ FAIL: amount=10000 rifiutato -', error.message);
            process.exit(1);
        }
    " 2>/dev/null
    
    return $?
}

# Test al commit attuale
echo "Test commit attuale:"
test_payment_system
CURRENT_STATUS=$?

# Test al tag funzionante
echo "Test versione funzionante (v1.0):"
git checkout v1.0-working
test_payment_system
WORKING_STATUS=$?

echo ""
if [ $WORKING_STATUS -eq 0 ] && [ $CURRENT_STATUS -eq 1 ]; then
    echo "✅ Confermato: regressione introdotta dopo v1.0-working"
else
    echo "❓ Risultati inconsistenti, serve analisi più profonda"
fi

# Torna al presente
git switch -
```

### Fase 3: Ricerca Binaria con Git Bisect

```bash
echo "=== FASE 3: RICERCA BINARIA CON GIT BISECT ==="

# Inizia bisect
git bisect start

# Marca il commit attuale come bad
git bisect bad HEAD

# Marca la versione funzionante come good
git bisect good v1.0-working

echo "🎯 Git bisect avviato! Seguirò il processo guidato..."

# Funzione per test automatico durante bisect
test_current_commit() {
    echo "📍 Testing commit: $(git log --oneline -1)"
    
    # Verifica che il file esista
    if [ ! -f "src/payment.js" ]; then
        echo "⚠️  File payment.js non esiste in questo commit"
        return 1
    fi
    
    # Test specifico per il bug
    node -e "
        try {
            const PaymentProcessor = require('./src/payment');
            const processor = new PaymentProcessor({apiKey: 'test'});
            const result = processor.processPayment(10000, 'EUR', 'card_test');
            console.log('✅ Test passed: 10000 EUR accettato');
            process.exit(0);
        } catch (error) {
            console.log('❌ Test failed: 10000 EUR rifiutato');
            process.exit(1);
        }
    " 2>/dev/null
}

# Processo manuale guidato (simula interazione)
echo "🔄 Iniziando processo bisect manuale..."

while git bisect log >/dev/null 2>&1; do
    echo ""
    echo "📍 Commit corrente: $(git log --oneline -1)"
    
    test_current_commit
    result=$?
    
    if [ $result -eq 0 ]; then
        echo "✅ Questo commit è GOOD"
        git bisect good
    else
        echo "❌ Questo commit è BAD"
        git bisect bad
    fi
    
    # Controlla se bisect è finito
    if git bisect log | grep -q "first bad commit"; then
        break
    fi
done

echo ""
echo "🎯 BISECT COMPLETATO!"
git bisect log | tail -10
```

### Fase 4: Analisi del Commit Problematico

```bash
echo "=== FASE 4: ANALISI DEL COMMIT PROBLEMATICO ==="

# Ottieni l'hash del commit problematico
BAD_COMMIT=$(git bisect log | grep "first bad commit" | awk '{print $1}' || git rev-parse HEAD)

echo "🔍 Commit problematico identificato: $BAD_COMMIT"

# Analisi dettagliata
echo ""
echo "📝 Dettagli del commit:"
git show --stat $BAD_COMMIT

echo ""
echo "🔬 Modifiche specifiche:"
git show $BAD_COMMIT

echo ""
echo "📋 File modificati:"
git show --name-only $BAD_COMMIT

echo ""
echo "👤 Autore e data:"
git show --format="Autore: %an <%ae>%nData: %ad%nMessaggio: %s" --no-patch $BAD_COMMIT

# Fine bisect
git bisect reset
```

### Fase 5: Analisi dell'Impatto

```bash
echo "=== FASE 5: ANALISI DELL'IMPATTO ==="

# Confronta prima e dopo il bug
GOOD_COMMIT=$(git log --oneline | grep "feat: Logging delle transazioni" | cut -d' ' -f1)
echo "Commit buono (prima): $GOOD_COMMIT"
echo "Commit cattivo (dopo): $BAD_COMMIT"

echo ""
echo "🔄 Differenze tra versione buona e cattiva:"
git diff $GOOD_COMMIT..$BAD_COMMIT -- src/payment.js

echo ""
echo "📊 Statistiche cambiamenti:"
git diff --stat $GOOD_COMMIT..$BAD_COMMIT

echo ""
echo "🎯 Linee specifiche modificate:"
git diff $GOOD_COMMIT..$BAD_COMMIT -- src/payment.js | grep -E "^[+-]" | grep -v "^+++" | grep -v "^---"
```

---

## 🔬 Analisi Forensica Dettagliata

### Estrazione Automatica del Bug

```bash
echo "=== ANALISI FORENSICA AUTOMATICA ==="

# Script di analisi automatica
cat > debug_analysis.sh << 'EOF'
#!/bin/bash

echo "🔍 ANALISI FORENSICA DEL BUG"
echo "=============================="

# Trova il commit esatto che ha introdotto il bug
echo "1. Identificazione commit problematico:"
git log --oneline --grep="Ottimizzazione validazione" | head -1

echo ""
echo "2. Estrazione della modifica problematica:"
BAD_COMMIT=$(git log --oneline --grep="Ottimizzazione validazione" | head -1 | cut -d' ' -f1)
git show $BAD_COMMIT | grep -A5 -B5 "amount.*10000"

echo ""
echo "3. Impatto del bug:"
echo "   - Prima: amount <= 10000 (inclusivo)"
echo "   - Dopo:  amount < 10000 (esclusivo)"
echo "   - Risultato: transazioni da exactly €10,000 rifiutate"

echo ""
echo "4. Severità:"
echo "   🔴 CRITICA: Rifiuta transazioni legittime di €10,000"
echo "   💰 Impatto business: Perdita di transazioni ad alto valore"

echo ""
echo "5. Root cause:"
echo "   📝 Messaggio commit fuorviante: 'Ottimizzazione'"
echo "   🐛 Cambio logica: <= diventa <"
echo "   ❌ Testing insufficiente per edge cases"
EOF

chmod +x debug_analysis.sh
./debug_analysis.sh
```

### Timeline dell'Introduzione del Bug

```bash
echo "=== TIMELINE DETTAGLIATA ==="

# Crea timeline dell'evoluzione
git log --oneline --reverse | nl | while read num hash message; do
    git checkout $hash 2>/dev/null
    
    if [ -f "src/payment.js" ]; then
        # Test veloce
        test_result="❓"
        if grep -q "amount <= 10000" src/payment.js 2>/dev/null; then
            test_result="✅"
        elif grep -q "amount < 10000" src/payment.js 2>/dev/null; then
            test_result="❌"
        fi
        
        echo "$num. $test_result $hash $message"
    fi
done

git switch -
```

### Impatto Analysis Report

```bash
# Genera report completo
cat > bug_report.md << 'EOF'
# 🐛 Bug Report: Payment Amount Validation

## 📊 Summary
- **Bug Type**: Logic Error in Amount Validation
- **Severity**: CRITICAL
- **Impact**: High-value transactions (€10,000) rejected
- **Introduction**: Commit with misleading message "refactor: Ottimizzazione validazione amount"

## 🔍 Technical Details

### Code Change
```diff
- amount > 0 && amount <= 10000
+ amount > 0 && amount < 10000
```

### Impact
- **Before**: Maximum amount €10,000 (inclusive)
- **After**: Maximum amount €9,999.99 (exclusive)
- **Lost Business**: All exactly €10,000 transactions

## 🎯 Root Cause Analysis

1. **Misleading Commit Message**: "Ottimizzazione" suggests improvement, not logic change
2. **Insufficient Testing**: No test case for boundary value €10,000
3. **Code Review Gap**: Logic change not properly reviewed

## 🛠️ Recommended Fixes

### Immediate Fix
```javascript
// Restore original logic
amount > 0 && amount <= 10000
```

### Long-term Improvements
1. Add boundary value tests
2. Improve commit message standards
3. Enhanced code review for logic changes
4. Automated regression testing

## 📈 Prevention Strategies

- [ ] Test boundary values (0, 10000, 10001)
- [ ] Commit message guidelines
- [ ] Pre-commit hooks for validation logic
- [ ] Business logic review checklist

---
Generated by: Git Detective Analysis
Date: $(date)
EOF

echo "📄 Report generato: bug_report.md"
cat bug_report.md
```

---

## 🛠️ Strategie di Fix e Prevenzione

### Fix Immediato

```bash
echo "=== FIX IMMEDIATO ==="

# Identifica la linea problematica
echo "🔍 Linea da fixare:"
grep -n "amount < 10000" src/payment.js

# Applica fix
sed -i 's/amount < 10000/amount <= 10000/' src/payment.js

echo "✅ Fix applicato!"

# Verifica fix
echo "🧪 Test del fix:"
node tests/payment.test.js

# Commit del fix
git add src/payment.js
git commit -m "fix: Ripristina validazione amount <= 10000

- Corregge regressione introdotta nel commit precedente
- Ripristina accettazione di transazioni da €10,000
- Aggiunge test per edge case
- Fixes #1001: Transazioni €10K rifiutate"

echo "🎯 Fix committato e testato!"
```

### Test di Prevenzione

```bash
# Aggiungi test comprehensivi
cat > tests/comprehensive.test.js << 'EOF'
const PaymentProcessor = require('../src/payment');

const processor = new PaymentProcessor({apiKey: 'test'});

console.log('🧪 COMPREHENSIVE PAYMENT TESTS');
console.log('================================');

// Test cases boundary
const testCases = [
    { amount: 0, expected: false, desc: 'Zero amount' },
    { amount: 0.01, expected: true, desc: 'Minimum valid amount' },
    { amount: 9999.99, expected: true, desc: 'Just under 10K' },
    { amount: 10000, expected: true, desc: 'Exactly 10K (critical edge case)' },
    { amount: 10000.01, expected: false, desc: 'Just over 10K' },
    { amount: 50000, expected: false, desc: 'Way over limit' }
];

testCases.forEach(test => {
    try {
        const result = processor.processPayment(test.amount, 'EUR', 'card_test');
        const passed = test.expected === true;
        console.log(`${passed ? '✅' : '❌'} ${test.desc}: €${test.amount} ${passed ? 'accepted' : 'unexpected success'}`);
    } catch (error) {
        const passed = test.expected === false;
        console.log(`${passed ? '✅' : '❌'} ${test.desc}: €${test.amount} ${passed ? 'correctly rejected' : 'unexpected failure'}`);
    }
});

console.log('\n🎯 All boundary tests completed!');
EOF

echo "🧪 Eseguendo test comprehensivi:"
node tests/comprehensive.test.js

git add tests/comprehensive.test.js
git commit -m "test: Aggiunge test comprehensivi per edge cases

- Test boundary values per amount validation
- Previene regressioni future
- Copre caso critico €10,000"
```

### Automazione Prevenzione

```bash
# Script di pre-commit hook
mkdir -p .git/hooks
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash

echo "🔍 Pre-commit checks..."

# Test automatici
if [ -f "tests/comprehensive.test.js" ]; then
    echo "🧪 Running comprehensive tests..."
    node tests/comprehensive.test.js
    if [ $? -ne 0 ]; then
        echo "❌ Tests failed! Commit blocked."
        exit 1
    fi
fi

# Controlla modifiche a validazione
if git diff --cached | grep -q "amount.*10000"; then
    echo "⚠️  ATTENZIONE: Modifica alla validazione amount rilevata!"
    echo "   Verificare attentamente la logica di boundary"
    echo "   Continuare? (y/N)"
    read answer
    [ "$answer" != "y" ] && exit 1
fi

echo "✅ Pre-commit checks passed!"
EOF

chmod +x .git/hooks/pre-commit
echo "🛡️ Pre-commit hook installato per prevenire future regressioni"
```

---

## 📊 Report Finale dell'Investigazione

### Investigazione Summary

```bash
#!/bin/bash
cat << 'EOF'
# 🕵️ INVESTIGAZIONE COMPLETATA

## 📋 Caso: Payment System Bug
**Data investigazione**: $(date)
**Investigatore**: Senior Developer

## 🎯 Risultati Chiave

### ✅ Bug Identificato
- **Commit**: Refactor "Ottimizzazione validazione amount"
- **Linea**: `amount <= 10000` → `amount < 10000`
- **Impatto**: Transazioni €10,000 rifiutate

### 🔧 Tools Utilizzati
1. **git bisect**: Ricerca binaria del commit problematico
2. **git show**: Analisi dettagliata delle modifiche
3. **Automated testing**: Verifica regressioni
4. **Timeline analysis**: Comprensione evoluzione

### 📈 Metriche Investigazione
- **Tempo totale**: ~45 minuti
- **Commit analizzati**: 8
- **Commit bisect steps**: 3
- **Accuratezza**: 100% (bug trovato precisamente)

## 🛠️ Azioni Correttive
- [x] Bug fixato e testato
- [x] Test comprehensivi aggiunti
- [x] Pre-commit hook installato
- [x] Documentazione processo debug

## 💡 Lezioni Apprese
1. **Git bisect è potentissimo** per bug regression
2. **Test boundary values sono critici**
3. **Commit messages fuorvianti sono pericolosi**
4. **Automazione previene ricorrenze**

## 🎓 Skills Developed
- Debug forensics con Git
- Investigazione systematica
- Test-driven debugging
- Prevention automation

EOF
```

### Cleanup Finale

```bash
echo "=== CLEANUP INVESTIGAZIONE ==="

# Rimuovi file temporanei
rm -f debug_analysis.sh

# Verifica stato finale
git status

echo ""
echo "📊 STATISTICHE FINALI:"
echo "- Commit totali: $(git rev-list --count HEAD)"
echo "- Bug risolto: ✅"
echo "- Test aggiunti: ✅" 
echo "- Prevenzione attiva: ✅"

echo ""
echo "🎯 INVESTIGAZIONE COMPLETATA CON SUCCESSO!"
echo "   💻 Repository più robusto e sicuro"
echo "   🛡️ Sistemi di prevenzione attivi"
echo "   📚 Processo documentato per future investigazioni"
```

---

## 💡 Takeaways e Best Practices

### Workflow Detective Confermato

1. **Analisi Iniziale** → Identifica area problema
2. **Test Regressione** → Conferma quando funzionava
3. **Git Bisect** → Trova commit esatto problematico
4. **Analisi Forensica** → Comprende root cause
5. **Fix + Prevenzione** → Risolve e previene ricorrenza

### Tools Git per Debugging

```bash
# Comando consolidati utilizzati
git bisect start/good/bad    # Ricerca binaria bug
git show <commit>            # Analisi dettagliata commit
git diff commit1..commit2    # Confronto versioni
git log --grep="pattern"     # Ricerca commit specifici
git reflog                   # Cronologia navigazione
```

### Pattern Debugging Temporale

- **Checkpoint sempre** prima dell'investigazione
- **Test automatici** per verifica rapida
- **Documentazione processo** per casi futuri
- **Fix + Test + Prevenzione** come workflow completo

---

## 🔄 Navigazione

- [⬅️ 01 - Esplorazione Base](./01-esplorazione-base.md)
- [🏠 Modulo 09](../README.md)
- [➡️ 03 - Testing Versioni](./03-testing-versioni.md)
- [📑 Indice Corso](../../README.md)

---

**Prossimo esempio**: [03 - Testing Versioni](./03-testing-versioni.md) - Utilizzo della navigazione per testing di diverse versioni del software
