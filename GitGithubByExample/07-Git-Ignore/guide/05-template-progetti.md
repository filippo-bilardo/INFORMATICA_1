# Template per Progetti Comuni

## 🎯 Template Preconfigurati

Ogni tipo di progetto ha pattern specifici di file da ignorare. Questa guida fornisce template completi e testati per i progetti più comuni.

## 🌐 Template Web Generale

### Frontend Base
```gitignore
# === DIPENDENZE ===
node_modules/
bower_components/
yarn.lock
package-lock.json

# === BUILD E DISTRIBUZIONE ===
build/
dist/
out/
.next/
.nuxt/
.vuepress/dist/

# === CACHE ===
.cache/
.parcel-cache/
.eslintcache
.stylelintcache

# === LOGS ===
*.log
logs/
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# === AMBIENTE ===
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# === COPERTURA TEST ===
coverage/
.nyc_output/
.coverage/

# === EDITOR E IDE ===
.vscode/settings.json
.idea/workspace.xml
*.swp
*.swo

# === OS ===
.DS_Store
Thumbs.db
```

## ⚛️ React / Next.js

### Template Completo React
```gitignore
# See https://help.github.com/articles/ignoring-files/ for more about ignoring files.

# === DIPENDENZE ===
node_modules/
/.pnp
.pnp.js

# === TESTING ===
/coverage

# === PRODUZIONE ===
/build

# === NEXT.JS ===
/.next/
/out/

# === NUXT.JS ===
.nuxt
dist

# === GATSBY ===
.cache/
public

# === VUEPRESS ===
.vuepress/dist

# === SERVERLESS ===
.serverless/

# === FUSEBOX ===
.fusebox/

# === DINAMODB LOCALE ===
.dynamodb/

# === TERNJS PORT FILE ===
.tern-port

# === STORES ===
.vscode/
.idea/

# === MISC ===
.DS_Store
.env.local
.env.development.local
.env.test.local
.env.production.local

npm-debug.log*
yarn-debug.log*
yarn-error.log*

# === STORYBOOK ===
.out
.storybook-out

# === JEST ===
# Coverage directory used by tools like istanbul
coverage/
*.lcov

# === ESLINT ===
.eslintcache

# === TYPESCRIPT ===
*.tsbuildinfo
next-env.d.ts
```

### Script Setup React
```bash
#!/bin/bash
# setup-react-gitignore.sh

echo "⚛️ Setup .gitignore per progetto React..."

# Verifica se è un progetto React
if [ ! -f "package.json" ] || ! grep -q "react" package.json; then
    echo "❌ Non sembra essere un progetto React"
    exit 1
fi

# Backup existing .gitignore
if [ -f ".gitignore" ]; then
    cp .gitignore .gitignore.backup
    echo "💾 Backup di .gitignore esistente creato"
fi

# Download template from GitHub
curl -sL https://raw.githubusercontent.com/github/gitignore/main/Node.gitignore > .gitignore

# Add React-specific rules
cat >> .gitignore << 'EOF'

# === REACT SPECIFIC ===
# Build outputs
build/
dist/

# Environment variables
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Testing
coverage/

# Production
/build
/out

# Storybook
.out
.storybook-out
storybook-static/

# ESLint cache
.eslintcache

# IDE
.vscode/settings.json
.idea/
EOF

echo "✅ .gitignore configurato per React!"
echo "📝 Aggiungi manualmente eventuali file specifici del tuo progetto"
```

## 🐍 Python

### Template Python Completo
```gitignore
# === BYTE-COMPILED / OPTIMIZED / DLL FILES ===
__pycache__/
*.py[cod]
*$py.class

# === C EXTENSIONS ===
*.so

# === DISTRIBUTION / PACKAGING ===
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
pip-wheel-metadata/
share/python-wheels/
*.egg-info/
.installed.cfg
*.egg
MANIFEST

# === PYINSTALLER ===
*.manifest
*.spec

# === INSTALLER LOGS ===
pip-log.txt
pip-delete-this-directory.txt

# === UNIT TEST / COVERAGE REPORTS ===
htmlcov/
.tox/
.nox/
.coverage
.coverage.*
.cache
nosetests.xml
coverage.xml
*.cover
*.py,cover
.hypothesis/
.pytest_cache/

# === TRANSLATIONS ===
*.mo
*.pot

# === DJANGO ===
*.log
local_settings.py
db.sqlite3
db.sqlite3-journal

# === FLASK ===
instance/
.webassets-cache

# === SCRAPY ===
.scrapy

# === SPHINX DOCUMENTATION ===
docs/_build/

# === PYBUILDER ===
target/

# === JUPYTER NOTEBOOK ===
.ipynb_checkpoints

# === IPYTHON ===
profile_default/
ipython_config.py

# === PYENV ===
.python-version

# === PIPENV ===
Pipfile.lock

# === POETRY ===
poetry.lock

# === CELERY ===
celerybeat-schedule
celerybeat.pid

# === SAGEMATH PARSED FILES ===
*.sage.py

# === ENVIRONMENTS ===
.env
.venv
env/
venv/
ENV/
env.bak/
venv.bak/

# === SPYDER PROJECT SETTINGS ===
.spyderproject
.spyproject

# === ROPE PROJECT SETTINGS ===
.ropeproject

# === MKDOCS DOCUMENTATION ===
/site

# === MYPY ===
.mypy_cache/
.dmypy.json
dmypy.json

# === PYRE TYPE CHECKER ===
.pyre/

# === FASTAPI ===
__pycache__/
.pytest_cache/

# === MACHINE LEARNING ===
# Datasets
data/
datasets/
*.csv
*.h5
*.pkl
*.joblib

# Models
models/
*.model
*.pth
*.ckpt

# Tensorboard logs
runs/
logs/
```

### Setup Automatico Python
```bash
#!/bin/bash
# setup-python-project.sh

PROJECT_NAME=$1
if [ -z "$PROJECT_NAME" ]; then
    echo "Uso: $0 <nome-progetto>"
    exit 1
fi

echo "🐍 Creazione progetto Python: $PROJECT_NAME"

# Crea directory progetto
mkdir "$PROJECT_NAME"
cd "$PROJECT_NAME"

# Inizializza Git
git init

# Crea struttura base
mkdir -p {src,tests,docs,data,notebooks}

# Download gitignore Python da GitHub
curl -sL https://raw.githubusercontent.com/github/gitignore/main/Python.gitignore > .gitignore

# Aggiungi regole specifiche per ML/Data Science
cat >> .gitignore << 'EOF'

# === PROJECT SPECIFIC ===
# Data files
data/raw/
data/processed/
*.csv
*.h5
*.pkl

# Models
models/
*.model
*.pth

# Jupyter checkpoints
.ipynb_checkpoints/

# Environment
.env
config.ini
EOF

# Crea virtual environment
python -m venv venv
echo "✅ Virtual environment creato"

# Crea requirements.txt base
cat > requirements.txt << 'EOF'
# Core dependencies
requests>=2.28.0
python-dotenv>=0.19.0

# Development dependencies
pytest>=7.0.0
black>=22.0.0
flake8>=4.0.0
EOF

# Crea README base
cat > README.md << EOF
# $PROJECT_NAME

## Setup

1. Crea virtual environment:
   \`\`\`bash
   python -m venv venv
   source venv/bin/activate  # Linux/Mac
   # oppure
   venv\Scripts\activate     # Windows
   \`\`\`

2. Installa dipendenze:
   \`\`\`bash
   pip install -r requirements.txt
   \`\`\`

## Struttura Progetto

- \`src/\` - Codice sorgente
- \`tests/\` - Test unitari
- \`docs/\` - Documentazione
- \`data/\` - Dataset (non versionati)
- \`notebooks/\` - Jupyter notebooks
EOF

echo "✅ Progetto Python $PROJECT_NAME creato con successo!"
echo "📁 Struttura:"
tree . 2>/dev/null || ls -la
```

## ☕ Java

### Template Java/Maven
```gitignore
# === COMPILED CLASS FILES ===
*.class

# === LOG FILES ===
*.log

# === BLUEJ FILES ===
*.ctxt

# === MOBILE TOOLS FOR JAVA (J2ME) ===
.mtj.tmp/

# === PACKAGE FILES ===
*.jar
*.war
*.nar
*.ear
*.zip
*.tar.gz
*.rar

# === VIRTUAL MACHINE CRASH LOGS ===
hs_err_pid*

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
**/build/
!src/**/build/
gradle-app.setting
!gradle-wrapper.jar
!gradle-wrapper.properties
.gradletasknamecache

# === NETBEANS ===
/nbproject/private/
/nbbuild/
/dist/
/nbdist/
/.nb-gradle/
build/
!**/src/main/**/build/
!**/src/test/**/build/

# === INTELLIJ IDEA ===
.idea/
*.iws
*.iml
*.ipr
out/
!**/src/main/**/out/
!**/src/test/**/out/

# === ECLIPSE ===
.apt_generated
.classpath
.factorypath
.project
.settings
.springBeans
.sts4-cache
bin/
!**/src/main/**/bin/
!**/src/test/**/bin/

# === VSCODE ===
.vscode/

# === SPRING BOOT ===
*.pid
.spring-boot-devtools.properties

# === DATABASE ===
*.db
*.sqlite
*.sqlite3

# === JUNIT ===
.junit/

# === APPLICATION SPECIFIC ===
# Configuration files
application-local.properties
application-dev.properties
*.local.properties

# Logs
logs/
```

## 📱 Mobile Development

### Android
```gitignore
# === BUILT APPLICATION FILES ===
*.apk
*.aar
*.ap_
*.aab

# === FILES FOR THE ART/DALVIK VM ===
*.dex

# === JAVA CLASS FILES ===
*.class

# === GENERATED FILES ===
bin/
gen/
out/
#  Uncomment the following line to ignore the release folder
#release/

# === GRADLE FILES ===
.gradle/
build/

# === LOCAL CONFIGURATION FILE ===
local.properties

# === PROGUARD FOLDER GENERATED BY ECLIPSE ===
proguard/

# === LOG FILES ===
*.log

# === ANDROID STUDIO NAVIGATION FILES ===
.navigation/

# === ANDROID STUDIO CAPTURES FOLDER ===
captures/

# === INTELLIJ ===
*.iml
.idea/workspace.xml
.idea/tasks.xml
.idea/gradle.xml
.idea/assetWizardSettings.xml
.idea/dictionaries
.idea/libraries
.idea/jarRepositories.xml
.idea/compiler.xml
.idea/modules.xml
.idea/.name
.idea/artifacts
.idea/caches
.idea/libraries
.idea/modules.xml
.idea/workspace.xml
.idea/navEditor.xml
.idea/assetWizardSettings.xml
.idea/deploymentTargetDropDown.xml

# === KEYSTORE FILES ===
*.jks
*.keystore

# === EXTERNAL NATIVE BUILD FOLDER ===
.externalNativeBuild
.cxx/

# === GOOGLE SERVICES (e.g. APIs or Firebase) ===
google-services.json

# === FREELINE ===
freeline.py
freeline/
freeline_project_description.json

# === FASTLANE ===
fastlane/report.xml
fastlane/Preview.html
fastlane/screenshots
fastlane/test_output
fastlane/readme.md

# === VERSION CONTROL ===
vcs.xml

# === LINT ===
lint/intermediates/
lint/generated/
lint/outputs/
lint/tmp/
lint-results*.xml
```

### iOS/Swift
```gitignore
# === XCODE ===
#
# gitignore contributors: remember to update Global/Xcode.gitignore, Objective-C.gitignore & Swift.gitignore

## USER SETTINGS
xcuserdata/

## COMPATIBILITY WITH XCODE 8 AND EARLIER
*.xcscmblueprint
*.xccheckout

## COMPATIBILITY WITH XCODE 9
*.xcuserstate

## XCODE PATCH
*.xcodeproj/*
!*.xcodeproj/project.pbxproj
!*.xcodeproj/xcshareddata/
!*.xcodeproj/project.xcworkspace/
*.xcworkspace/*
!*.xcworkspace/contents.xcworkspacedata
!*.xcworkspace/xcshareddata/

# === SWIFT SPECIFIC ===
.build/

# === COCOAPODS ===
Pods/
*.podspec

# === CARTHAGE ===
Carthage/Checkouts
Carthage/Build/

# === ACCIO DEPENDENCY MANAGEMENT ===
Dependencies/
.accio/

# === FASTLANE ===
fastlane/report.xml
fastlane/Preview.html
fastlane/screenshots/**/*.png
fastlane/test_output

# === CODE INJECTION ===
iOSInjectionProject/
```

## 🛠️ DevOps e Infrastructure

### Docker
```gitignore
# === DOCKER ===
# Ignore Docker build context
.dockerignore

# Compose override files
docker-compose.override.yml
docker-compose.override.yaml

# Environment variables
.env
.env.local
.env.*.local

# Logs
logs/
*.log

# Runtime data
pids/
*.pid
*.seed
```

### Terraform
```gitignore
# === TERRAFORM ===
# Local .terraform directories
**/.terraform/*

# .tfstate files
*.tfstate
*.tfstate.*

# Crash log files
crash.log
crash.*.log

# Exclude all .tfvars files
*.tfvars
*.tfvars.json

# Ignore override files
override.tf
override.tf.json
*_override.tf
*_override.tf.json

# CLI configuration files
.terraformrc
terraform.rc

# Variables
terraform.tfvars
terraform.tfvars.json
*.auto.tfvars
*.auto.tfvars.json
```

## 🎮 Unity/Game Development

### Unity
```gitignore
# === UNITY ===
[Ll]ibrary/
[Tt]emp/
[Oo]bj/
[Bb]uild/
[Bb]uilds/
[Ll]ogs/
[Mm]emoryCaptures/

# Asset meta data should only be ignored when the corresponding asset is also ignored
!/[Aa]ssets/**/*.meta

# Uncomment this line if you wish to ignore the asset store tools plugin
# /[Aa]ssets/AssetStoreTools*

# Autogenerated Jetbrains Rider plugin
[Aa]ssets/Plugins/Editor/JetBrains*

# Visual Studio cache/options directory
.vs/

# Gradle cache directory
.gradle/

# Autogenerated VS/MD/Consulo solution and project files
ExportedObj/
.consulo/
*.csproj
*.unityproj
*.sln
*.suo
*.tmp
*.user
*.userprefs
*.pidb
*.booproj
*.svd
*.pdb
*.mdb
*.opendb
*.VC.db

# Unity3D generated meta files
*.pidb.meta
*.pdb.meta
*.mdb.meta

# Unity3D generated file on crash reports
sysinfo.txt

# Builds
*.apk
*.unitypackage

# Crashlytics generated file
crashlytics-build.properties

# Packed Addressables
/[Aa]ssets/[Aa]ddressable[Aa]ssets[Dd]ata/*/*.bin*

# Temporary auto-generated Android Assets
/[Aa]ssets/[Ss]treamingAssets/aa.meta
/[Aa]ssets/[Ss]treamingAssets/aa/*
```

## 🎯 Script di Selezione Template

### Template Selector
```bash
#!/bin/bash
# select-gitignore-template.sh

echo "🎯 Selettore Template .gitignore"
echo "==============================="

templates=(
    "Web/Frontend"
    "React/Next.js"
    "Python"
    "Java/Maven"
    "Android"
    "iOS/Swift"
    "Docker"
    "Terraform"
    "Unity"
    "Personalizzato"
)

echo "📋 Template disponibili:"
for i in "${!templates[@]}"; do
    echo "   $((i+1)). ${templates[$i]}"
done

echo ""
read -p "Seleziona template (1-${#templates[@]}): " choice

case $choice in
    1) template_url="https://raw.githubusercontent.com/github/gitignore/main/Node.gitignore" ;;
    2) template_url="https://raw.githubusercontent.com/github/gitignore/main/Node.gitignore" ;;
    3) template_url="https://raw.githubusercontent.com/github/gitignore/main/Python.gitignore" ;;
    4) template_url="https://raw.githubusercontent.com/github/gitignore/main/Java.gitignore" ;;
    5) template_url="https://raw.githubusercontent.com/github/gitignore/main/Android.gitignore" ;;
    6) template_url="https://raw.githubusercontent.com/github/gitignore/main/Swift.gitignore" ;;
    7) echo "# Docker\n.env\nlogs/\n*.log" > .gitignore; echo "✅ Template Docker creato!"; exit 0 ;;
    8) echo "# Terraform\n*.tfstate\n*.tfvars\n.terraform/" > .gitignore; echo "✅ Template Terraform creato!"; exit 0 ;;
    9) template_url="https://raw.githubusercontent.com/github/gitignore/main/Unity.gitignore" ;;
    10) echo "📝 Creazione template personalizzato..."; nano .gitignore; exit 0 ;;
    *) echo "❌ Scelta non valida"; exit 1 ;;
esac

echo "📥 Download template..."
curl -sL "$template_url" > .gitignore

echo "✅ Template ${templates[$((choice-1))]} installato!"
echo "📝 Modifica .gitignore per personalizzarlo ulteriormente"
```

## 🧪 Test Template

### Script di Verifica
```bash
#!/bin/bash
# test-gitignore-template.sh

echo "🧪 Test Template .gitignore"
echo "============================"

if [ ! -f .gitignore ]; then
    echo "❌ .gitignore non trovato!"
    exit 1
fi

echo "📊 Statistiche template:"
echo "   Righe totali: $(wc -l < .gitignore)"
echo "   Regole attive: $(grep -v '^#' .gitignore | grep -v '^$' | wc -l)"
echo "   Commenti: $(grep '^#' .gitignore | wc -l)"

echo ""
echo "🔍 Verifica pattern comuni:"

# Test patterns comuni
common_patterns=(
    "node_modules/"
    "*.log"
    ".env"
    "build/"
    ".DS_Store"
)

for pattern in "${common_patterns[@]}"; do
    if grep -q "$pattern" .gitignore; then
        echo "   ✅ $pattern"
    else
        echo "   ❌ $pattern (considerare l'aggiunta)"
    fi
done

echo ""
echo "📁 File nel progetto che potrebbero essere ignorati:"
find . -name "node_modules" -o -name "*.log" -o -name ".env" -o -name "build" -o -name ".DS_Store" 2>/dev/null | head -5
```

## 🔗 Prossimi Passi

- [← Gestione File Già Tracciati](./04-file-tracciati.md)
- [Esempi Pratici →](../esempi/01-setup-nodejs.md)
- [Torna alla Panoramica ←](../README.md)

---

> 💡 **Suggerimento**: Usa sempre un template appropriato come base e personalizzalo per le specifiche esigenze del tuo progetto!
