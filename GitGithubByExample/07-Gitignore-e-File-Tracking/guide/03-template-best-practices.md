# Template e Best Practices .gitignore

## 📖 Template Pronti all'Uso

Invece di creare `.gitignore` da zero, è meglio partire da template testati e affidabili per il tuo stack tecnologico.

## 🌐 Generatori Online

### 1. **gitignore.io** - Il Più Completo
```bash
# Genera template per tecnologie multiple
$ curl -L https://www.toptal.com/developers/gitignore/api/node,react,vscode > .gitignore

# Via web: https://www.toptal.com/developers/gitignore
# Seleziona: Node, React, VS Code, macOS, Windows
```

### 2. **GitHub Template Repository**
```bash
# Clone dei template ufficiali GitHub
$ git clone https://github.com/github/gitignore.git
$ cp gitignore/Node.gitignore .gitignore
```

### 3. **VS Code Extension**
```bash
# Installa extension "gitignore"
# Comando: >Add gitignore
# Seleziona tecnologie dal menu
```

## 📚 Template per Linguaggi Comuni

### JavaScript/Node.js Completo
```gitignore
# === DEPENDENCIES ===
node_modules/
jspm_packages/

# === RUNTIME ===
npm-debug.log*
yarn-debug.log*
yarn-error.log*
lerna-debug.log*

# === BUILD OUTPUTS ===
dist/
build/
.next/
out/
.nuxt/
.vuepress/dist

# === CACHE ===
.npm
.eslintcache
.stylelintcache
.cache/
.parcel-cache/

# === ENVIRONMENT ===
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# === TESTING ===
coverage/
.nyc_output
.jest/

# === IDE/EDITORS ===
.vscode/
.idea/
*.swp
*.swo
*~

# === OS GENERATED ===
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db
```

### Python Completo
```gitignore
# === BYTE-COMPILED ===
__pycache__/
*.py[cod]
*$py.class

# === C EXTENSIONS ===
*.so

# === DISTRIBUTION ===
.Python
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
*.egg-info/
.installed.cfg
*.egg
MANIFEST

# === VIRTUAL ENVIRONMENTS ===
.env
.venv
env/
venv/
ENV/
env.bak/
venv.bak/

# === TESTING ===
.pytest_cache/
.coverage
htmlcov/
.tox/
.nox/
.cache
nosetests.xml
coverage.xml
*.cover
.hypothesis/

# === JUPYTER ===
.ipynb_checkpoints

# === DJANGO ===
*.log
local_settings.py
db.sqlite3
media

# === FLASK ===
instance/
.webassets-cache

# === IDE ===
.vscode/
.idea/
*.swp
*.swo
.spyderproject
.spyproject
```

### Java/Maven/Gradle
```gitignore
# === COMPILED ===
*.class
*.jar
*.war
*.ear
*.aar

# === MAVEN ===
target/
pom.xml.tag
pom.xml.releaseBackup
pom.xml.versionsBackup
pom.xml.next
release.properties
dependency-reduced-pom.xml
buildNumber.properties
.mvn/timing.properties
.mvn/wrapper/maven-wrapper.jar

# === GRADLE ===
.gradle
build/
!gradle/wrapper/gradle-wrapper.jar
!**/src/main/**/build/
!**/src/test/**/build/

# === IDE ===
.idea/
*.iws
*.iml
*.ipr
out/
.project
.classpath
.factorypath
.buildpath
.settings/

# === LOGS ===
*.log

# === OS ===
.DS_Store
Thumbs.db
```

### C# / .NET
```gitignore
# === BUILD RESULTS ===
[Dd]ebug/
[Dd]ebugPublic/
[Rr]elease/
[Rr]eleases/
x64/
x86/
[Aa][Rr][Mm]/
[Aa][Rr][Mm]64/
bld/
[Bb]in/
[Oo]bj/
[Ll]og/

# === VISUAL STUDIO ===
.vs/
*.user
*.userosscache
*.sln.docstates
*.userprefs

# === RESHARPER ===
_ReSharper*/
*.[Rr]e[Ss]harper
*.DotSettings.user

# === PACKAGES ===
packages/
!packages/build/
*.nupkg
*.snupkg

# === NuGet ===
project.lock.json
project.fragment.lock.json
artifacts/

# === ENTITY FRAMEWORK ===
*.edmx.diagram
*.edmx.sql
migrations/

# === AZURE ===
AppPackages/
BundleArtifacts/
Package.StoreAssociation.xml
_pkginfo.txt
*.appx
```

## 🎯 Template per Progetti Specifici

### React Frontend
```gitignore
# === DEPENDENCIES ===
node_modules/

# === PRODUCTION BUILD ===
/build
/dist

# === DEVELOPMENT ===
.env.local
.env.development.local
.env.test.local
.env.production.local

# === CACHE ===
.cache/
.parcel-cache/

# === TESTING ===
coverage/

# === STORYBOOK ===
.out
.storybook-out
storybook-static/

# === MISC ===
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# === IDE ===
.vscode/
.idea/

# === OS ===
.DS_Store
Thumbs.db
```

### Backend API (Node.js)
```gitignore
# === DEPENDENCIES ===
node_modules/

# === ENVIRONMENT ===
.env
.env.local
.env.development
.env.staging
.env.production

# === LOGS ===
logs/
*.log
npm-debug.log*

# === DATABASE ===
*.sqlite
*.sqlite3
*.db

# === UPLOADS ===
uploads/
public/uploads/

# === SSL/CERTIFICATES ===
*.pem
*.key
*.crt

# === PROCESS FILES ===
*.pid
*.seed
*.pid.lock

# === COVERAGE ===
coverage/
.nyc_output

# === CACHE ===
.cache/
.npm

# === IDE ===
.vscode/
.idea/
```

### Monorepo (Nx/Lerna)
```gitignore
# === DEPENDENCIES ===
node_modules/
**/node_modules/

# === BUILD OUTPUTS ===
dist/
**/dist/
build/
**/build/
.next/
**/.next/

# === CACHE ===
.cache/
**/.cache/
.nx/cache
.nx/workspace-data

# === ENVIRONMENT ===
.env
.env.local
**/.env.local

# === TESTING ===
coverage/
**/coverage/

# === LOGS ===
*.log
**/*.log

# === IDE ===
.vscode/
.idea/

# === OS ===
.DS_Store
**/. DS_Store
```

## 🏗️ Template Personalizzabili

### Template Base Universale
```gitignore
# ========================================
# TEMPLATE BASE - PERSONALIZZA PER IL TUO PROGETTO
# ========================================

# === DEPENDENCIES (Aggiungi il tuo package manager) ===
node_modules/           # Node.js
vendor/                # PHP Composer
venv/                  # Python Virtual Env
.bundle/               # Ruby Bundle

# === BUILD OUTPUTS (Aggiungi le tue directory di build) ===
dist/
build/
out/
target/                # Java Maven
bin/                   # C#/.NET

# === ENVIRONMENT & SECRETS (CRITICAL!) ===
.env
.env.*
!.env.example          # Eccezione per file di esempio
config/secrets.*
*.key
*.pem

# === IDE & EDITOR CONFIG ===
.vscode/
.idea/
*.swp
*.swo
*~

# === OS GENERATED FILES ===
.DS_Store              # macOS
._*                    # macOS
.Spotlight-V100        # macOS
.Trashes              # macOS
ehthumbs.db           # Windows
Thumbs.db             # Windows
Desktop.ini           # Windows

# === LOGS & CACHE ===
*.log
logs/
.cache/
tmp/
temp/

# === TESTING & COVERAGE ===
coverage/
.nyc_output
test-results/

# ========================================
# PERSONALIZZAZIONI SPECIFICHE
# Aggiungi qui le regole specifiche per il tuo progetto
# ========================================

# Esempio: ignorare file di configurazione specifici
# config/database.yml
# assets/uploads/

# Esempio: ignorare directory di terze parti
# third-party/
# libraries/
```

## ✅ Best Practices Template

### 1. **Organizzazione Logica**
```gitignore
# === SECTION HEADERS ===
# Usa intestazioni per organizzare

# === DEPENDENCIES ===
node_modules/

# === BUILD & COMPILE ===
dist/
build/

# === ENVIRONMENT & SECRETS ===
.env
*.key

# === DEVELOPMENT TOOLS ===
.vscode/
.cache/

# === SYSTEM FILES ===
.DS_Store
```

### 2. **Commenti Esplicativi**
```gitignore
# Database files - contengono dati sensibili
*.sqlite
*.db

# SSL certificates - mai committare chiavi private!
*.pem
*.key

# Upload directory - file caricati dagli utenti
uploads/
public/uploads/

# IDE settings - preferenze personali
.vscode/settings.json
```

### 3. **Pattern Progressivi**
```gitignore
# Inizia ampio
*.log

# Poi specifica eccezioni se necessarie
!important.log

# Affina ulteriormente
logs/*
!logs/README.md
!logs/.gitkeep
```

### 4. **Versionamento Template**
```gitignore
# === GITIGNORE TEMPLATE v2.1 ===
# Created: 2024-01-15
# Updated: 2024-01-20
# Stack: Node.js + React + MongoDB
# Author: Team Dev
# 
# CHANGELOG:
# v2.1 - Added Storybook ignores
# v2.0 - Added MongoDB ignores
# v1.0 - Initial template

# === DEPENDENCIES ===
node_modules/
```

## 🔧 Strumenti per Template

### 1. **Generatore CLI Personalizzato**
```bash
#!/bin/bash
# Script: generate-gitignore.sh

echo "Seleziona stack tecnologico:"
echo "1) Node.js + React"
echo "2) Python + Django"
echo "3) Java + Spring"
read -p "Scelta: " choice

case $choice in
    1) curl -L https://www.toptal.com/developers/gitignore/api/node,react > .gitignore ;;
    2) curl -L https://www.toptal.com/developers/gitignore/api/python,django > .gitignore ;;
    3) curl -L https://www.toptal.com/developers/gitignore/api/java,maven,intellij > .gitignore ;;
    *) echo "Scelta non valida" ;;
esac
```

### 2. **Template Repository Aziendale**
```bash
# Crea template per la tua azienda
company-templates/
├── web-frontend.gitignore
├── api-backend.gitignore
├── mobile-app.gitignore
├── data-science.gitignore
└── README.md

# Uso:
$ cp company-templates/web-frontend.gitignore .gitignore
```

### 3. **VS Code Snippet**
```json
{
  "Basic GitIgnore": {
    "prefix": "gitignore-basic",
    "body": [
      "# === DEPENDENCIES ===",
      "node_modules/",
      "",
      "# === ENVIRONMENT ===", 
      ".env",
      ".env.local",
      "",
      "# === BUILD ===",
      "dist/",
      "build/",
      "",
      "# === IDE ===",
      ".vscode/",
      ".idea/",
      "",
      "# === OS ===",
      ".DS_Store",
      "Thumbs.db"
    ],
    "description": "Basic .gitignore template"
  }
}
```

## 🧪 Esercizio Template

### Scenario
Devi creare un template `.gitignore` per un progetto che usa:
- Frontend: React + TypeScript
- Backend: Node.js + Express
- Database: MongoDB
- Testing: Jest
- Build: Webpack
- IDE: VS Code

<details>
<summary>💡 Soluzione Template</summary>

```gitignore
# === PROJECT: Full-Stack MERN App ===
# Stack: MongoDB + Express + React + Node.js
# Updated: $(date)

# === DEPENDENCIES ===
node_modules/
jspm_packages/

# === FRONTEND BUILD ===
/client/build/
/client/dist/
.next/

# === BACKEND ===
/server/dist/
/server/uploads/

# === ENVIRONMENT & SECRETS ===
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# === DATABASE ===
*.sqlite
*.sqlite3
/data/

# === TESTING ===
coverage/
.jest/
test-results/

# === CACHE & TEMP ===
.cache/
.parcel-cache/
.eslintcache
.stylelintcache
*.tmp

# === LOGS ===
*.log
logs/
npm-debug.log*
yarn-debug.log*

# === IDE & EDITORS ===
.vscode/
.idea/
*.swp
*.swo

# === OS FILES ===
.DS_Store
Thumbs.db
._*

# === TYPESCRIPT ===
*.tsbuildinfo

# === WEBPACK ===
.webpack/
```
</details>

## 📋 Checklist Template

- [ ] ✅ **Dependencies** - node_modules, vendor, etc.
- [ ] ✅ **Build outputs** - dist, build, target
- [ ] ✅ **Environment files** - .env, secrets
- [ ] ✅ **IDE settings** - .vscode, .idea
- [ ] ✅ **OS files** - .DS_Store, Thumbs.db
- [ ] ✅ **Logs** - *.log, logs/
- [ ] ✅ **Cache** - .cache, tmp/
- [ ] ✅ **Testing** - coverage, test-results
- [ ] ✅ **Comments** - Sezioni chiare
- [ ] ✅ **Eccezioni** - File da non ignorare (!pattern)

---

**Prossimo:** [Gestione File Tracciati](./04-gestione-file-tracciati.md) per rimuovere file già in tracking!
