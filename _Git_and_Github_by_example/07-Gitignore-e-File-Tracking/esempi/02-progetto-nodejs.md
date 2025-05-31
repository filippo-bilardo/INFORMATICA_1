# Esempio 02: Gitignore per Progetto Node.js

## Obiettivo
Configurare un file `.gitignore` completo per un progetto Node.js, includendo dipendenze, file temporanei e configurazioni locali.

## Struttura Progetto Iniziale
```
my-node-app/
├── package.json
├── package-lock.json
├── server.js
├── config/
│   ├── database.js
│   └── config.local.js
├── node_modules/
├── logs/
│   └── app.log
├── uploads/
│   └── temp-file.txt
└── .env
```

## Creazione Gitignore

### 1. Gitignore Base per Node.js
```bash
# Crea il file .gitignore
nano .gitignore
```

```gitignore
# Dipendenze
node_modules/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# File di ambiente
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Logs
logs/
*.log
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# Directory temporanee
tmp/
temp/
.tmp/

# File di configurazione locale
config/*.local.js
config/*.local.json

# File di upload utente
uploads/
!uploads/.gitkeep

# Cache
.npm
.eslintcache
.parcel-cache

# IDE
.vscode/
.idea/
*.swp
*.swo

# OS
.DS_Store
Thumbs.db
```

### 2. Verifica del Funzionamento
```bash
# Controlla lo status
git status

# Output atteso:
# On branch main
# Untracked files:
#   .gitignore
#   config/database.js
#   package.json
#   package-lock.json
#   server.js
```

### 3. Aggiungere File Necessari
```bash
# Aggiungi i file del progetto (non ignorati)
git add .gitignore package.json server.js config/database.js

# Commit iniziale
git commit -m "feat: setup initial Node.js project with gitignore"
```

## Pattern Avanzati per Node.js

### Build e Distribuzione
```gitignore
# Build output
build/
dist/
out/

# Coverage directory used by tools like istanbul
coverage/

# Dependency directories
node_modules/
jspm_packages/

# Optional npm cache directory
.npm

# Optional REPL history
.node_repl_history

# Output of 'npm pack'
*.tgz

# Yarn Integrity file
.yarn-integrity
```

### Strumenti di Sviluppo
```gitignore
# ESLint cache
.eslintcache

# Prettier cache
.prettiercache

# TypeScript cache
*.tsbuildinfo

# Jest cache
.jest/

# Cypress
cypress/videos
cypress/screenshots
```

## Best Practices

### 1. File .gitkeep per Directory Vuote
```bash
# Mantieni directory uploads ma vuota
touch uploads/.gitkeep
git add uploads/.gitkeep
```

### 2. Template Globale Node.js
```bash
# Usa template GitHub per Node.js
curl https://raw.githubusercontent.com/github/gitignore/main/Node.gitignore > .gitignore
```

### 3. Ignorare File già Tracciati
```bash
# Se hai già tracciato node_modules per errore
git rm -r --cached node_modules/
git commit -m "fix: remove node_modules from tracking"
```

## Risultato Finale

Dopo la configurazione, la struttura tracciata sarà:
```
my-node-app/
├── .gitignore
├── package.json
├── package-lock.json
├── server.js
├── config/
│   └── database.js
└── uploads/
    └── .gitkeep
```

File ignorati automaticamente:
- `node_modules/`
- `logs/`
- `.env`
- `config/config.local.js`
- File temporanei upload

## Verifica Finale
```bash
# Controlla cosa viene ignorato
git status --ignored

# Test che node_modules sia ignorato
npm install
git status  # Non dovrebbe mostrare node_modules
```

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Modulo Precedente](../06-Gestione-File-e-Directory/README.md)
- [➡️ Modulo Successivo](../08-Visualizzare-Storia-Commit/README.md)
