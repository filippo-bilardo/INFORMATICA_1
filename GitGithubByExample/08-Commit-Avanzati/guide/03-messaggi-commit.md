# Messaggi di Commit: Best Practices per Comunicazione Efficace

## Introduzione
I messaggi di commit sono la documentazione vivente del progetto. Un buon messaggio spiega il "cosa" e il "perché" dei cambiamenti, facilitando maintenance, debugging e collaborazione.

## Anatomia di un Messaggio di Commit

### Struttura Base
```
<tipo>[scope opzionale]: <descrizione breve>

[corpo opzionale]

[footer opzionale]
```

### Esempio Completo
```
feat(auth): aggiungi autenticazione a due fattori

Implementa 2FA usando TOTP per migliorare la sicurezza:
- Genera QR code per setup iniziale
- Valida token temporali
- Gestisce backup codes
- Integra con provider esterni (Google, Authy)

Modifiche breaking: richiede migrazione database per campo 2fa_enabled

Closes #234
Refs #123, #456
Co-authored-by: Mario Rossi <mario@example.com>
```

## Tipi di Commit

### Tipi Standard (Conventional Commits)
```bash
# Nuove funzionalità
git commit -m "feat: aggiungi sistema di notifiche push"

# Bug fix
git commit -m "fix: risolvi memory leak nel parser JSON"

# Documentazione
git commit -m "docs: aggiorna README con nuove API"

# Stile/Formattazione
git commit -m "style: applica prettier a tutti i file JS"

# Refactoring
git commit -m "refactor: estrai logica validazione in classe separata"

# Test
git commit -m "test: aggiungi test unit per modulo autenticazione"

# Configurazione
git commit -m "chore: aggiorna dipendenze a versioni latest"
```

### Tipi Estesi
```bash
# Performance
git commit -m "perf: ottimizza query database con indici"

# Sicurezza
git commit -m "security: sanitizza input utente contro XSS"

# Build/CI
git commit -m "build: configura webpack per tree shaking"

# Revert
git commit -m "revert: annulla commit a1b2c3d per regressione"
```

## Scope (Ambito)

### Esempi per Moduli
```bash
# Frontend
git commit -m "feat(ui): aggiungi dark mode"
git commit -m "fix(navbar): correggi layout mobile"

# Backend
git commit -m "feat(api): endpoint per gestione utenti"
git commit -m "fix(database): risolvi deadlock su transazioni"

# Specifici Componenti
git commit -m "feat(auth): implementa SSO con SAML"
git commit -m "test(payment): aggiungi test integrazione Stripe"
```

## Linee Guida per la Descrizione

### 1. Lingua e Stile
```bash
# ✅ BUONO - Imperativo presente
git commit -m "fix: risolvi bug nella validazione email"

# ❌ CATTIVO - Passato
git commit -m "fix: risolto bug nella validazione email"

# ❌ CATTIVO - Gerundio
git commit -m "fix: risolvendo bug nella validazione email"
```

### 2. Lunghezza e Formato
```bash
# ✅ BUONO - Massimo 50 caratteri per subject
git commit -m "feat: aggiungi sistema cache Redis"

# ❌ CATTIVO - Troppo lungo
git commit -m "feat: aggiungi sistema di cache con Redis che migliora le performance del 40% usando pattern write-through"

# ✅ BUONO - Usare corpo per dettagli
git commit -m "feat: aggiungi sistema cache Redis

Implementa caching layer con:
- Write-through pattern
- TTL configurabile
- Invalidazione automatica
- Monitoring delle hit rates

Performance improvement: ~40% su endpoint API"
```

### 3. Capitalizzazione
```bash
# ✅ BUONO - Prima lettera minuscola dopo i due punti
git commit -m "feat: aggiungi funzionalità export"

# ❌ CATTIVO - Maiuscola
git commit -m "feat: Aggiungi funzionalità export"
```

## Corpo del Messaggio

### 1. Quando Includere il Corpo
```bash
# Commit semplice - solo subject
git commit -m "fix: typo in README"

# Commit complesso - con corpo
git commit -m "feat: implementa sistema di backup

Aggiunge backup automatico con:
- Schedulazione configurabile (cron)
- Compressione incrementale
- Verifica integrità con checksum
- Notifiche su successo/fallimento

Supporta storage locali e cloud (S3, GCS)
Compatibile con database MySQL e PostgreSQL"
```

### 2. Formattazione del Corpo
```bash
git commit -m "refactor: ristruttura modulo autenticazione

Motivazione:
Il codice esistente era difficile da mantenere e testare

Cambiamenti:
- Separazione concerns in classi dedicate
- Introduzione dependency injection
- Aggiunta interfaces per testabilità
- Migliorata gestione errori

Impatto:
- Ridotta complessità ciclomatica da 15 a 8
- Coverage test aumentata dal 60% al 95%
- Breaking change: metodo login() ora asincrono"
```

## Footer e Metadati

### 1. Riferimenti Issue
```bash
# Chiudere issue
git commit -m "fix: risolvi crash su iOS 15

Closes #123"

# Riferimenti multipli
git commit -m "feat: nuovo dashboard admin

Implements #456
Refs #789, #101
Part of #234"
```

### 2. Breaking Changes
```bash
git commit -m "feat!: migra API da v1 a v2

BREAKING CHANGE: endpoint /api/users ora richiede autenticazione
- Aggiungere header Authorization
- Usare formato JWT per token
- Endpoint legacy /api/v1/users deprecato (rimozione in v3.0)

Migration guide: docs/api-migration.md"
```

### 3. Co-authorship
```bash
git commit -m "feat: implementa algoritmo ML per raccomandazioni

Co-authored-by: Alice Smith <alice@example.com>
Co-authored-by: Bob Johnson <bob@example.com>"
```

## Template di Messaggi

### 1. Template Globale
```bash
# Configurare template
git config --global commit.template ~/.gitmessage

# Creare template
cat > ~/.gitmessage << 'EOF'
# <tipo>[scope]: <descrizione> (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento:
# - Cosa è stato modificato
# - Perché è stato necessario
# - Come influisce sul sistema
#
# Riferimenti:
# Closes #
# Refs #
#
# Breaking changes:
# BREAKING CHANGE: 
EOF
```

### 2. Template per Progetto
```bash
# Template specifico per progetto
cat > .gitmessage << 'EOF'
# [JIRA-XXX] <tipo>: <descrizione>
#
# Descrizione dettagliata:
# 
# Test eseguiti:
# - [ ] Unit tests
# - [ ] Integration tests  
# - [ ] Manual testing
#
# Checklist:
# - [ ] Documentazione aggiornata
# - [ ] Breaking changes documentati
# - [ ] Performance valutate
#
# Links:
# JIRA: https://company.atlassian.net/browse/XXX
# Closes #
EOF
```

### 3. Hook per Validazione
```bash
# .git/hooks/commit-msg
#!/bin/bash
commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! grep -qE "$commit_regex" "$1"; then
    echo "❌ Formato messaggio non valido!"
    echo "Formato richiesto: <tipo>[scope]: <descrizione>"
    echo "Tipi validi: feat, fix, docs, style, refactor, test, chore"
    exit 1
fi

# Verificare lunghezza subject line
subject=$(head -n1 "$1")
if [ ${#subject} -gt 50 ]; then
    echo "⚠️ Subject line troppo lungo (${#subject} caratteri, max 50)"
    exit 1
fi

echo "✅ Messaggio commit valido"
```

## Messaggi per Diversi Scenari

### 1. Bug Fix
```bash
# Bug semplice
git commit -m "fix: correggi null pointer in UserService.validate()"

# Bug complesso
git commit -m "fix: risolvi race condition nel sistema di pagamenti

Il problema si verificava quando due transazioni simultanee
modificavano lo stesso account utente, causando stati inconsistenti.

Soluzione:
- Aggiunto locking ottimistico con versioning
- Implementato retry pattern per conflitti
- Migliorata gestione timeout database

Fixes #567
Tested on: staging environment con 1000 concurrent users"
```

### 2. Nuove Funzionalità
```bash
# Feature semplice
git commit -m "feat: aggiungi pulsante share per articoli"

# Feature complessa
git commit -m "feat: sistema di chat real-time

Implementa chat WebSocket-based con:
- Room pubbliche e private
- Messaggi persistenti (30 giorni)
- Supporto file upload (max 10MB)
- Moderazione automatica anti-spam
- Notifiche push mobile
- Crittografia end-to-end per chat private

Stack tecnologico:
- WebSocket server: Socket.io
- Database: Redis per cache + PostgreSQL per persistenza
- File storage: AWS S3 con CDN CloudFront

Performance:
- Supporta 10k utenti simultanei
- Latenza media: <100ms
- Uptime target: 99.9%

Implements #234, #567
Refs architecture decision: docs/adr/001-realtime-chat.md"
```

### 3. Refactoring
```bash
git commit -m "refactor: estrai business logic da controller

Motivazione: i controller erano diventati troppo pesanti (>500 LOC)
violando il principio Single Responsibility

Cambiamenti:
- Creati service layer per ogni dominio business
- Spostata validazione in classi dedicate  
- Implementato dependency injection pattern
- Aggiunta astrazione per database access

Benefici:
- Migliorata testabilità (ora 95% coverage)
- Ridotta complessità (da 25 a 8 cyclomatic complexity)
- Facilitata manutenibilità futura
- Preparato terreno per microservices migration

No breaking changes - API pubblica invariata"
```

## Tools e Automazione

### 1. Commitizen
```bash
# Installazione
npm install -g commitizen cz-conventional-changelog

# Configurazione
echo '{ "path": "cz-conventional-changelog" }' > ~/.czrc

# Uso
git cz  # invece di git commit
```

### 2. Commitlint
```bash
# Installazione
npm install --save-dev @commitlint/cli @commitlint/config-conventional

# Configurazione
cat > .commitlintrc.js << 'EOF'
module.exports = {
  extends: ['@commitlint/config-conventional'],
  rules: {
    'subject-case': [2, 'always', 'lower-case'],
    'subject-max-length': [2, 'always', 50],
    'body-max-line-length': [2, 'always', 72]
  }
}
EOF

# Hook setup
npx husky add .husky/commit-msg 'npx commitlint --edit $1'
```

### 3. Conventional Changelog
```bash
# Generazione CHANGELOG automatico
npm install --save-dev conventional-changelog-cli

# Package.json script
{
  "scripts": {
    "changelog": "conventional-changelog -p angular -i CHANGELOG.md -s"
  }
}

# Uso
npm run changelog
```

## Metriche e Analisi

### 1. Analisi Qualità Messaggi
```bash
#!/bin/bash
# analyze-commits.sh
echo "📊 Analisi qualità messaggi commit (ultimi 100)"

# Lunghezza media subject
git log --pretty=format:"%s" -100 | awk '{print length}' | \
  awk '{sum+=$1; count++} END {print "📏 Lunghezza media subject:", sum/count, "caratteri"}'

# Distribuzione tipi commit
echo -e "\n📋 Tipi di commit:"
git log --pretty=format:"%s" -100 | \
  grep -oE '^[a-z]+(\([^)]+\))?' | \
  sort | uniq -c | sort -nr

# Subject troppo lunghi
echo -e "\n⚠️ Subject > 50 caratteri:"
git log --pretty=format:"%h %s" -100 | \
  awk 'length($0) > 57 {print "- " substr($0,1,80) "..."}'
```

## Conclusioni
Messaggi di commit ben scritti sono un investimento nel futuro del progetto. Seguire convenzioni condivise facilita la manutenzione, il debugging e la collaborazione in team.
