# Ricerca nella Cronologia

## 📖 Scenario Investigativo

Sei il lead developer di un team e devi investigare alcuni problemi emersi in produzione. Un bug critico è apparso nel sistema di pagamento, le prestazioni dell'autenticazione sono degradate, e il team segnala che alcune funzionalità sono state rotte. Devi usare Git per fare detective work e trovare quando e chi ha introdotto questi problemi.

## 🎯 Obiettivi dell'Esempio

- Utilizzare filtri temporali per localizzare problemi
- Cercare nei messaggi e nel codice per trovare modifiche specifiche
- Tracciare l'evoluzione di file critici
- Identificare pattern nei commit che potrebbero indicare problemi

## 🚀 Setup del Scenario Investigativo

### Estensione del Repository Precedente
```bash
# Continua dal repository creato nell'esempio precedente
cd ecommerce-project

# Aggiungiamo più cronologia realistica per l'investigazione
git config user.name "Marco Bianchi"
git config user.email "marco.bianchi@company.com"

# 1. Implementazione sistema pagamento
cat > src/payment/payment.js << 'EOF'
class PaymentProcessor {
    constructor(apiKey) {
        this.apiKey = apiKey;
        this.processingFee = 2.99;
    }

    async processPayment(amount, cardInfo) {
        try {
            // Simulate API call
            const response = await this.callPaymentAPI({
                amount: amount + this.processingFee,
                card: cardInfo
            });
            
            return {
                success: true,
                transactionId: response.id,
                amount: amount
            };
        } catch (error) {
            console.error('Payment failed:', error);
            return {
                success: false,
                error: error.message
            };
        }
    }

    async callPaymentAPI(data) {
        // Mock API call
        if (Math.random() > 0.1) {
            return { id: 'txn_' + Date.now() };
        } else {
            throw new Error('Payment gateway timeout');
        }
    }
}

module.exports = PaymentProcessor;
EOF

git add src/payment/payment.js
git commit -m "feat(payment): implement payment processing system

- Add PaymentProcessor class with API integration
- Include processing fee calculation
- Add error handling and retry logic
- Mock payment gateway integration for testing"

# 2. Qualche giorno dopo - aggiornamento configurazione
sleep 1
echo "API_TIMEOUT=5000" > .env
git add .env
git commit -m "config: add environment configuration

Added .env file with API timeout settings
for production deployment optimization"

# 3. Bug introdotto nel pagamento
git config user.name "Intern Developer"
git config user.email "intern@company.com"

sleep 1
sed -i 's/amount + this.processingFee/amount * this.processingFee/' src/payment/payment.js
git add src/payment/payment.js
git commit -m "refactor: improve payment calculation

Updated payment processing logic for better
accuracy in fee calculation"

# 4. Performance "miglioramento" nell'autenticazione
git config user.name "Performance Expert"
git config user.email "perf@company.com"

sleep 1
cat >> src/auth/login.js << 'EOF'

// Performance optimization: cache validation results
const validationCache = new Map();

function optimizedValidateUser(username, password) {
    const cacheKey = `${username}:${password}`;
    
    if (validationCache.has(cacheKey)) {
        return validationCache.get(cacheKey);
    }
    
    // Expensive validation logic
    for (let i = 0; i < 1000000; i++) {
        Math.random(); // Simulate heavy computation
    }
    
    const result = validateUser(username, password);
    validationCache.set(cacheKey, result);
    return result;
}

module.exports.optimizedValidateUser = optimizedValidateUser;
EOF

git add src/auth/login.js
git commit -m "perf(auth): optimize user validation with caching

Added caching layer to improve authentication performance.
Reduces database calls and improves response time for
frequently accessed user credentials.

Benchmark shows 90% performance improvement in repeated validations."

# 5. Hotfix per problema critico
git config user.name "Emergency Response"
git config user.email "emergency@company.com"

sleep 1
echo "EMERGENCY_BYPASS=true" >> .env
git add .env
git commit -m "hotfix: add emergency bypass for critical issue

URGENT: Production is down due to payment processing errors.
Added emergency bypass flag to allow manual order processing
while we investigate the root cause.

Incident #PROD-2024-001"

# 6. Tentativo di fix del pagamento
git config user.name "Senior Developer"
git config user.email "senior@company.com"

sleep 1
sed -i 's/amount \* this.processingFee/amount + this.processingFee/' src/payment/payment.js
git add src/payment/payment.js
git commit -m "fix(payment): correct fee calculation logic

Fixed multiplication error in payment processing.
Fee should be added, not multiplied by transaction amount.

Fixes issue where $100 transaction was charged $299 instead of $102.99
Resolves customer complaints about incorrect billing."

# 7. Rimozione "ottimizzazione" performance
sleep 1
git reset --hard HEAD~3  # Torna indietro di 3 commit
git config user.name "Tech Lead"
git config user.email "techlead@company.com"

# Ricrea fix payment senza la performance "optimization"
sed -i 's/amount \* this.processingFee/amount + this.processingFee/' src/payment/payment.js
git add src/payment/payment.js
git commit -m "fix(payment): correct payment calculation

Fixed critical bug where processing fee was being
multiplied instead of added to transaction amount.

Root cause: Incorrect operator in line 12 of payment.js
Impact: All payments since last deployment overcharged
Solution: Reverted to additive fee calculation

Tested on staging with positive results."

# 8. Aggiunta test per prevenire regressioni
mkdir -p tests
cat > tests/payment.test.js << 'EOF'
const PaymentProcessor = require('../src/payment/payment');

describe('PaymentProcessor', () => {
    test('should calculate correct fee', () => {
        const processor = new PaymentProcessor('test-key');
        const amount = 100;
        const expectedTotal = 102.99; // 100 + 2.99 fee
        
        // This test would have caught the multiplication bug
        expect(amount + processor.processingFee).toBe(expectedTotal);
    });
});
EOF

git add tests/
git commit -m "test(payment): add regression tests for fee calculation

Added comprehensive test suite for payment processing
to prevent future calculation errors.

Tests cover:
- Fee calculation accuracy
- Error handling scenarios  
- API timeout handling

These tests would have caught the recent production bug."

# 9. Documentazione dell'incidente
cat > INCIDENT_REPORT.md << 'EOF'
# Payment Processing Incident Report

## Incident ID: PROD-2024-001

### Timeline
- 14:30 - Bug introduced in payment calculation
- 15:45 - First customer complaints received
- 16:00 - Emergency bypass activated
- 16:30 - Root cause identified
- 17:00 - Fix deployed and verified

### Root Cause
Incorrect operator in payment fee calculation (multiplication instead of addition)

### Impact
- 23 customers overcharged
- $1,247 in incorrect fees collected
- 2.5 hours downtime for payment processing

### Resolution
- Reverted to correct fee calculation
- Added comprehensive test suite
- Implemented code review requirement for payment module
EOF

git add INCIDENT_REPORT.md
git commit -m "docs: add incident report for payment bug

Documented PROD-2024-001 incident for future reference
and team learning. Includes timeline, root cause analysis,
and preventive measures implemented."

# 10. Simuliamo qualche commit di feature normale
git config user.name "Feature Developer"
git config user.email "feature@company.com"

echo "console.log('User logged in successfully');" >> src/auth/login.js
git add src/auth/login.js
git commit -m "feat(auth): add success logging for user login

Added console logging for successful authentication
to improve debugging and monitoring capabilities."

# 11. Tag per release post-incident
git tag -a v1.1.0 -m "Release v1.1.0 - Payment Fix

Critical release to address payment processing bug.
Includes enhanced testing and monitoring.

Changes:
- Fixed payment calculation error
- Added comprehensive test suite  
- Improved error handling
- Enhanced logging"
```

## 🔍 Investigazione: Il Caso del Payment Bug

### 1. Identificazione del Periodo Problematico
```bash
# Prima domanda: quando è iniziato il problema?
# Sappiamo che il bug è in produzione, quindi cerchiamo commit recenti
git log --oneline --since="1 day ago"

# Output mostra gli ultimi commit:
# a1b2c3d (HEAD -> main, tag: v1.1.0) feat(auth): add success logging
# b2c3d4e docs: add incident report for payment bug  
# c3d4e5f test(payment): add regression tests for fee calculation
# d4e5f6g fix(payment): correct payment calculation
# e5f6g7h hotfix: add emergency bypass for critical issue
# f6g7h8i perf(auth): optimize user validation with caching
# g7h8i9j refactor: improve payment calculation
```

**Osservazione**: Vediamo un pattern sospetto - hotfix emergency, poi fix payment, poi test. Chiaro segno di un problema serio.

### 2. Analisi dei Commit Sospetti
```bash
# Esaminiamo il commit "refactor: improve payment calculation"
git show g7h8i9j

# Output mostra la modifica problematica:
# -                amount: amount + this.processingFee,
# +                amount: amount * this.processingFee,
```

**Eureka!** Trovato il bug! Qualcuno ha cambiato `+` in `*` nel calcolo delle commissioni.

### 3. Investigazione dell'Autore
```bash
# Chi ha fatto questa modifica?
git log --author="Intern" --oneline

# Quando ha lavorato l'intern sul progetto?
git log --author="Intern" --pretty=format:"%ad - %s" --date=short

# Quali file ha modificato?
git log --author="Intern" --name-only --oneline
```

**Scoperta**: L'intern developer ha fatto il commit problematico, probabilmente senza comprendere l'impatto.

### 4. Ricerca per Parole Chiave
```bash
# Cerchiamo tutti i commit relativi a "payment"
git log --grep="payment" --oneline

# Cerchiamo commit che menzionano "fee"
git log --grep="fee" --oneline

# Cerchiamo commit con "hotfix" o "emergency"
git log --grep="hotfix\|emergency" --oneline --color=always
```

**Pattern**: I commit di emergency sono concentrati in un periodo specifico, confermando l'incident.

## 🔍 Investigazione: Il Caso della Performance Degradata

### 1. Ricerca nei Commit di Performance
```bash
# Cerchiamo modifiche di performance
git log --grep="perf\|performance\|optimize" --oneline

# Output:
# f6g7h8i perf(auth): optimize user validation with caching
```

### 2. Analisi delle Modifiche Performance
```bash
# Esaminiamo il commit di "ottimizzazione"
git show f6g7h8i --stat

# Vediamo cosa è stato aggiunto al file auth
git show f6g7h8i -- src/auth/login.js
```

**Problema Identificato**: L'"ottimizzazione" ha aggiunto un loop di 1.000.000 iterazioni! È una pessimizzazione, non un'ottimizzazione.

### 3. Verifica se il Codice è Ancora Presente
```bash
# Controlliamo se questo codice è ancora nel branch principale
git log --oneline --graph

# Verifichiamo il contenuto attuale del file
grep -n "1000000" src/auth/login.js
echo $?  # Se ritorna 1, il codice non c'è più
```

**Risultato**: Il codice della "performance optimization" non è più presente, probabilmente rimosso con il reset.

## 🔍 Investigazione: Tracking delle Modifiche ai File Critici

### 1. Storia Completa del File Payment
```bash
# Cronologia completa del file payment
git log --follow --patch -- src/payment/payment.js

# Versione più leggibile con solo metadati
git log --follow --oneline -- src/payment/payment.js

# Chi ha modificato il file payment più spesso?
git log --pretty=format:"%an" -- src/payment/payment.js | sort | uniq -c | sort -nr
```

### 2. Modifiche Specifiche per Linea
```bash
# Blame per vedere chi ha scritto ogni riga
git blame src/payment/payment.js

# Blame con più contesto
git blame -L 10,15 src/payment/payment.js

# Quando è stata aggiunta la riga problematica?
git log -L 12,12:src/payment/payment.js
```

### 3. Confronto tra Versioni
```bash
# Confronto tra version prima e dopo il bug
git diff HEAD~5:src/payment/payment.js HEAD:src/payment/payment.js

# Vedere solo le linee che contengono "processingFee"
git log -S"processingFee" --oneline -- src/payment/payment.js
```

## 📊 Analisi dei Pattern e Trend

### 1. Analisi Temporale dei Problemi
```bash
# Commit per giorno per vedere i picchi di attività
git log --pretty=format:"%ad" --date=short | sort | uniq -c

# Commit di fix negli ultimi giorni
git log --grep="fix\|hotfix" --since="3 days ago" --oneline

# Rapporto fix/feature
echo "Fix commits:"
git log --grep="fix" --oneline | wc -l
echo "Feature commits:"  
git log --grep="feat" --oneline | wc -l
```

### 2. Analisi degli Autori Problematici
```bash
# Rapporto commit per autore negli ultimi giorni critici
git log --since="3 days ago" --pretty=format:"%an" | sort | uniq -c | sort -nr

# Autori che hanno fatto commit di fix
git log --grep="fix" --pretty=format:"%an - %s" --since="1 week ago"

# Correlazione tra autori e tipi di commit
for author in $(git log --pretty=format:"%an" | sort | uniq); do
    echo "=== $author ==="
    echo "Features: $(git log --author="$author" --grep="feat" --oneline | wc -l)"
    echo "Fixes: $(git log --author="$author" --grep="fix" --oneline | wc -l)"
    echo
done
```

## 🔍 Ricerca Avanzata nel Contenuto

### 1. Ricerca di Modifiche Specifiche
```bash
# Trovare quando "processingFee" è stato modificato
git log -S"processingFee" --oneline --all

# Trovare commit che hanno aggiunto/rimosso "Math.random"
git log -S"Math.random" --oneline

# Ricerca regex per pattern problematici
git log -G"amount.*\*.*processingFee" --oneline
```

### 2. Ricerca di Introduzione di Vulnerabilità
```bash
# Cercare aggiunta di codice sospetto
git log -S"emergency" --oneline
git log -S"bypass" --oneline

# Cercare commit che menzionano password
git log --grep="password" --oneline

# Cercare modifiche ai file di configurazione
git log --oneline -- "*.env" "*.config.*"
```

### 3. Analisi delle Revert e Rollback
```bash
# Trovare tutti i revert
git log --grep="revert\|rollback" --oneline

# Vedere se ci sono stati reset hard
git reflog | grep "reset"

# Commit che sono stati "undone" da commit successivi
git log --grep="undo\|correct\|fix.*error" --oneline
```

## 📈 Report dell'Investigazione

### Script di Analisi Automatizzata
```bash
#!/bin/bash
# incident-analysis.sh

echo "=== GIT INCIDENT ANALYSIS REPORT ==="
echo "Generated on: $(date)"
echo

echo "=== RECENT HOTFIXES AND EMERGENCY COMMITS ==="
git log --grep="hotfix\|emergency\|urgent\|critical" --since="1 week ago" --pretty=format:"[%ad] %an: %s" --date=short
echo

echo "=== PAYMENT MODULE CHANGE HISTORY ==="
git log --oneline -- src/payment/ | head -10
echo

echo "=== SUSPICIOUS PATTERN DETECTION ==="
echo "Commits by intern developers:"
git log --author="intern\|Intern" --oneline | wc -l

echo "Commits with '*' in payment files:"
git log -S"*" --oneline -- src/payment/ | wc -l

echo "Performance-related commits:"
git log --grep="perf\|performance" --oneline | wc -l
echo

echo "=== BLAME ANALYSIS FOR CRITICAL FILES ==="
echo "Last 5 changes to payment.js:"
git log --oneline -5 -- src/payment/payment.js

echo "=== RECOMMENDATIONS ==="
echo "1. Implement mandatory code review for payment module"
echo "2. Add integration tests for fee calculations"  
echo "3. Restrict intern access to critical payment code"
echo "4. Add performance benchmarks to CI/CD pipeline"
```

### Esecuzione dell'Analisi
```bash
# Rendi eseguibile e lancia lo script
chmod +x incident-analysis.sh
./incident-analysis.sh
```

## 🎯 Tecniche di Ricerca Specifiche

### 1. Ricerca Combinata Multi-Criterio
```bash
# Commit di un autore specifico che menzionano "payment" negli ultimi 7 giorni
git log --author="Intern" --grep="payment" --since="1 week ago" --oneline

# Modifiche ai file JavaScript che contengono "fee" nel messaggio
git log --grep="fee" --oneline -- "*.js"

# Commit che NON sono merge e contengono "fix"
git log --grep="fix" --no-merges --oneline
```

### 2. Ricerca per Impatto sul Codice
```bash
# Commit che hanno aggiunto più di 10 righe
git log --shortstat | grep -B1 "insertion" | grep -E "[0-9]{2,} insertion"

# Commit che hanno modificato più di 5 file
git log --name-only --pretty=format:"COMMIT:%h %s" | awk '/^COMMIT:/ {if(count>5) print prev; prev=$0; count=0; next} /^$/ {next} {count++} END {if(count>5) print prev}'
```

### 3. Ricerca di Anti-Pattern
```bash
# Commit con messaggi vaghi
git log --grep="fix\|update\|change" --pretty=format:"%h - %s" | grep -E "^[a-f0-9]+ - (fix|update|change)$"

# Commit fatti di venerdì sera (possibili errori)
git log --pretty=format:"%ad %h %s" --date=format:"%A %H" | grep "Friday [1-2][0-9]"

# Commit con hash che iniziano con numeri (spesso problematici)
git log --oneline | grep "^[0-9]"
```

## 🧪 Esercizi di Detective Work

### Esercizio 1: Timeline Investigation
```bash
# Crea una timeline degli eventi critici
# Trova tutti i commit tra il bug e il fix
git log --oneline g7h8i9j..d4e5f6g

# Calcola quanto tempo è passato tra introduzione bug e fix
git log --pretty=format:"%ad" --date=iso g7h8i9j d4e5f6g
```

### Esercizio 2: Author Analysis
```bash
# Analizza il comportamento degli autori
# Chi fa più commit di fix?
git log --grep="fix" --pretty=format:"%an" | sort | uniq -c | sort -nr

# Chi introduce più bug (poi fixati)?
# Hint: confronta autori di commit seguiti da fix
```

### Esercizio 3: Pattern Recognition
```bash
# Identifica pattern di commit sospetti
# Cerca commit che modificano la stessa riga più volte
git log --follow -p -- src/payment/payment.js | grep "processingFee"
```

## 🔄 Conclusioni e Lezioni Apprese

### Tecniche Più Efficaci
1. **Combinazione di filtri**: Autore + tempo + contenuto per ricerche precise
2. **Ricerca nel codice**: `-S` e `-G` per trovare modifiche specifiche
3. **Analisi temporale**: `--since`/`--until` per localizzare problemi
4. **Follow dei file**: `--follow` per tracciare rinominazioni

### Red Flags Identificati
- Commit di "performance" che aggiungono loop inutili
- Intern che modifica codice critico senza supervisione
- Cambi di operatori matematici in calcoli finanziari
- Commit di emergency seguiti da fix multipli

### Raccomandazioni Preventive
- Code review obbligatorio per moduli critici
- Test automatizzati per calcoli finanziari
- Monitoring delle performance in real-time
- Restrizioni di accesso per sviluppatori junior

---

**Continua con**: [03-Analisi-Modifiche](./03-analisi-modifiche.md) - Analisi approfondita delle modifiche con git show
