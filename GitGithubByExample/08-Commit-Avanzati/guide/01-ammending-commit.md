# Ammending Commit: Modificare l'Ultimo Commit

## Introduzione
Il comando `git commit --amend` permette di modificare l'ultimo commit effettuato, sia per correggere il messaggio che per aggiungere modifiche dimenticate.

## Quando Usare Ammending

### Scenari Comuni
- **Errori nel messaggio**: Correggere typo o migliorare la descrizione
- **File dimenticati**: Aggiungere file che dovevano essere inclusi
- **Piccole correzioni**: Fix minori che logicamente appartengono al commit precedente
- **Informazioni mancanti**: Aggiungere dettagli importanti al messaggio

## Sintassi e Opzioni

### Modificare Solo il Messaggio
```bash
git commit --amend -m "Nuovo messaggio corretto"
```

### Modificare Messaggio Interattivamente
```bash
git commit --amend
# Si apre l'editor per modificare il messaggio
```

### Aggiungere File al Commit
```bash
git add file-dimenticato.txt
git commit --amend --no-edit
# --no-edit mantiene il messaggio originale
```

### Modificare File e Messaggio
```bash
git add correzioni.txt
git commit --amend -m "Fix: Correzioni complete al modulo utenti"
```

## Best Practices

### 1. Solo per Commit Non Pushati
```bash
# ✅ SICURO - commit locale
git log --oneline -3
# a1b2c3d Fix: correzione minore
# d4e5f6g Add: nuova funzionalità
# g7h8i9j Update: documentazione

git commit --amend -m "Fix: correzione minore con test aggiuntivi"
```

### 2. Verificare lo Stato Prima
```bash
# Controllare cosa c'è nello staging area
git status

# Vedere le differenze
git diff --staged

# Procedere con ammending
git commit --amend
```

### 3. Ammending con Autore Diverso
```bash
git commit --amend --author="Nome Cognome <email@example.com>"
```

## Workflow Completo

### Scenario: Correzione Post-Commit
```bash
# 1. Effettuare commit iniziale
git add feature.js
git commit -m "Add: nuova funzionalità login"

# 2. Scoprire errore o dimenticanza
echo "console.log('Debug removed');" >> feature.js
git add test-feature.js  # file di test dimenticato

# 3. Ammendare il commit
git add feature.js test-feature.js
git commit --amend -m "Add: nuova funzionalità login con test"

# 4. Verificare il risultato
git show --stat
```

### Scenario: Messaggio Commit Migliorato
```bash
# Commit con messaggio generico
git commit -m "fix"

# Migliorare il messaggio
git commit --amend -m "Fix: risolto bug nella validazione email

- Corretta regex per domini internazionali
- Aggiunto supporto per caratteri speciali
- Test unitari aggiornati

Closes #123"
```

## Ammending Avanzato

### 1. Modificare Data del Commit
```bash
# Usare data corrente
git commit --amend --date="$(date)"

# Usare data specifica
git commit --amend --date="2024-01-15 10:30:00"
```

### 2. Ammending con Hook
```bash
# Impostare un hook per validazione automatica
cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash
# Validare formato messaggio prima dell'ammending
if git diff --cached --name-only | grep -q "\.js$"; then
    npm test
fi
EOF

chmod +x .git/hooks/pre-commit
```

### 3. Template per Messaggi
```bash
# Configurare template globale
git config --global commit.template ~/.gitmessage

# Creare template
cat > ~/.gitmessage << 'EOF'
# Tipo: Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento (max 72 caratteri per riga)
#
# - Bullet point per cambiamenti specifici
# - Un altro punto importante
#
# Riferimenti: Closes #123, Refs #456
EOF
```

## Limitazioni e Avvertenze

### 1. Non Ammendare Commit Pubblici
```bash
# ❌ PERICOLOSO - commit già pushato
git log --oneline origin/main..HEAD
# Nessun output = tutto è stato pushato

git commit --amend  # Cambierà l'hash del commit!
git push  # ERRORE: non-fast-forward
```

### 2. Perdita di Dati
```bash
# Salvare il commit originale prima di ammendare
git tag backup-commit HEAD
git commit --amend -m "Nuovo messaggio"

# Se necessario, recuperare
git reset --hard backup-commit
```

### 3. Collaborazione in Team
```bash
# Comunicare cambiamenti al team
git push --force-with-lease origin feature-branch
# Più sicuro di --force, verifica che nessun altro abbia pushato
```

## Script di Automazione

### Script per Ammending Sicuro
```bash
#!/bin/bash
# safe-amend.sh - Ammending con controlli di sicurezza

# Verificare che non ci siano commit pushati
if git log --oneline origin/$(git branch --show-current)..HEAD | grep -q .; then
    echo "✅ Commit locale trovato, sicuro procedere"
else
    echo "❌ Nessun commit locale da ammendare"
    exit 1
fi

# Verificare staging area
if ! git diff --staged --quiet; then
    echo "📝 File in staging area trovati"
    git status --porcelain --staged
    read -p "Procedere con ammending? (y/N): " confirm
    [[ $confirm =~ ^[Yy]$ ]] || exit 1
fi

# Procedere con ammending
git commit --amend
echo "✅ Commit ammendato con successo"
```

## Risoluzione Problemi

### 1. Ammending Fallito
```bash
# Se l'editor si chiude senza salvare
git commit --amend --reuse-message=HEAD
```

### 2. Recupero dopo Ammending Errato
```bash
# Usare reflog per recuperare
git reflog
git reset --hard HEAD@{1}  # Tornare al commit precedente
```

### 3. Conflitti durante Ammending
```bash
# Se ci sono conflitti con file staged
git reset --mixed HEAD~1
# Risolvere conflitti manualmente
git add .
git commit -m "Messaggio corretto"
```

## Conclusioni
Il comando `git commit --amend` è uno strumento potente per perfezionare i commit, ma richiede attenzione quando si lavora in team. Usarlo solo per commit locali e sempre con controlli di sicurezza.
