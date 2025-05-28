# 01 - First Release

## 🎯 Obiettivo

Creare la prima release di un progetto, implementando tag semantici, release notes e distribuzione di assets.

## 📋 Scenario

Hai sviluppato una semplice applicazione CLI e vuoi pubblicare la prima versione stabile v1.0.0 su GitHub.

## 🚀 Implementazione Passo-Passo

### Fase 1: Preparazione del Progetto

```bash
# 1. Crea struttura del progetto
mkdir my-cli-app
cd my-cli-app

# 2. Inizializza Git e GitHub
git init
echo "# My CLI App" > README.md
echo "Una semplice applicazione CLI per gestire task." >> README.md

# 3. Crea struttura base
mkdir -p {src,docs,dist}

# 4. Crea file package.json
cat > package.json << 'EOF'
{
  "name": "my-cli-app",
  "version": "1.0.0",
  "description": "Simple CLI task manager",
  "main": "src/index.js",
  "bin": {
    "mycli": "./src/index.js"
  },
  "scripts": {
    "build": "node scripts/build.js",
    "test": "node test/test.js"
  },
  "keywords": ["cli", "task", "productivity"],
  "author": "Your Name",
  "license": "MIT"
}
EOF
```

### Fase 2: Sviluppo dell'Applicazione

```javascript
// src/index.js
#!/usr/bin/env node

const args = process.argv.slice(2);
const command = args[0];

const commands = {
  add: (task) => {
    console.log(`✅ Task aggiunto: ${task}`);
  },
  list: () => {
    console.log('📋 Lista task:');
    console.log('1. Esempio task 1');
    console.log('2. Esempio task 2');
  },
  help: () => {
    console.log(`
📝 My CLI App v1.0.0

Uso:
  mycli add "nome task"    Aggiunge un nuovo task
  mycli list              Mostra tutti i task
  mycli help              Mostra questo aiuto

Esempi:
  mycli add "Comprare il latte"
  mycli list
    `);
  }
};

if (!command || !commands[command]) {
  commands.help();
} else {
  commands[command](args.slice(1).join(' '));
}
```

```javascript
// scripts/build.js
const fs = require('fs');
const path = require('path');

console.log('🔨 Building My CLI App...');

// Crea directory dist se non esiste
if (!fs.existsSync('dist')) {
  fs.mkdirSync('dist');
}

// Copia file principale
fs.copyFileSync('src/index.js', 'dist/mycli');

// Rendi eseguibile (Unix)
if (process.platform !== 'win32') {
  fs.chmodSync('dist/mycli', '755');
}

console.log('✅ Build completato!');
console.log('📁 Output: dist/mycli');
```

```javascript
// test/test.js
console.log('🧪 Running tests...');

// Test semplice
const { execSync } = require('child_process');

try {
  // Test comando help
  const helpOutput = execSync('node src/index.js help', { encoding: 'utf8' });
  if (helpOutput.includes('My CLI App v1.0.0')) {
    console.log('✅ Help command test passed');
  } else {
    throw new Error('Help command test failed');
  }
  
  console.log('🎉 All tests passed!');
} catch (error) {
  console.error('❌ Tests failed:', error.message);
  process.exit(1);
}
```

### Fase 3: Documentazione Pre-Release

```markdown
<!-- docs/CHANGELOG.md -->
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.0.0] - 2024-01-15

### Added
- Initial release of My CLI App
- Basic task management commands (add, list)
- Command-line interface with help system
- Cross-platform compatibility

### Features
- `mycli add` - Add new tasks
- `mycli list` - List all tasks  
- `mycli help` - Show help information

### Technical
- Node.js based CLI application
- Simple file-based task storage
- Comprehensive help system
```

```markdown
<!-- docs/INSTALLATION.md -->
# Installation Guide

## Download

Download the latest release from [GitHub Releases](https://github.com/username/my-cli-app/releases/latest).

### Available Downloads

- **Linux/macOS**: `mycli-v1.0.0-unix.tar.gz`
- **Windows**: `mycli-v1.0.0-windows.zip`
- **Source Code**: Available as zip or tar.gz

## Installation

### Linux/macOS

```bash
# Download and extract
wget https://github.com/username/my-cli-app/releases/download/v1.0.0/mycli-v1.0.0-unix.tar.gz
tar -xzf mycli-v1.0.0-unix.tar.gz

# Make executable and move to PATH
chmod +x mycli
sudo mv mycli /usr/local/bin/

# Verify installation
mycli help
```

### Windows

1. Download `mycli-v1.0.0-windows.zip`
2. Extract to a folder (e.g., `C:\mycli\`)
3. Add the folder to your PATH environment variable
4. Open new Command Prompt and run `mycli help`

### From Source

```bash
git clone https://github.com/username/my-cli-app.git
cd my-cli-app
npm install
npm run build
```

## Usage

```bash
# Add a task
mycli add "Buy groceries"

# List all tasks
mycli list

# Get help
mycli help
```
```

### Fase 4: Commit e Push Iniziale

```bash
# 1. Setup repository
git add .
git commit -m "feat: initial CLI application with basic task management

- Add command-line interface for task management
- Implement add, list, and help commands
- Include build system and basic tests
- Add comprehensive documentation"

# 2. Crea repository su GitHub (tramite web o CLI)
gh repo create my-cli-app --public
git remote add origin https://github.com/username/my-cli-app.git
git push -u origin main
```

### Fase 5: Preparazione Release

```bash
# 1. Final testing
npm test
npm run build

# 2. Crea assets per release
mkdir release-assets

# Linux/macOS package
tar -czf release-assets/mycli-v1.0.0-unix.tar.gz -C dist mycli

# Windows package (simulated)
cd dist && zip ../release-assets/mycli-v1.0.0-windows.zip mycli && cd ..

# Source code (Git archives)
git archive --format=zip --prefix=my-cli-app-1.0.0/ HEAD > release-assets/source-v1.0.0.zip
git archive --format=tar.gz --prefix=my-cli-app-1.0.0/ HEAD > release-assets/source-v1.0.0.tar.gz

# 3. Genera checksums
cd release-assets
sha256sum * > checksums.txt
cd ..
```

### Fase 6: Creazione Tag e Release

```bash
# 1. Crea tag annotato
git tag -a v1.0.0 -m "Release v1.0.0: Initial stable release

🚀 First stable release of My CLI App!

Features:
- Command-line task management
- Cross-platform compatibility  
- Simple and intuitive interface

This release includes:
- mycli add command for adding tasks
- mycli list command for viewing tasks
- mycli help command for assistance
- Complete documentation and installation guide

Assets:
- Binaries for Linux/macOS and Windows
- Source code archives
- Installation documentation"

# 2. Push tag
git push origin v1.0.0
```

### Fase 7: Creazione GitHub Release

#### Metodo 1: Via GitHub Web Interface

```bash
# 1. Naviga su GitHub
open https://github.com/username/my-cli-app/releases

# 2. Click "Create a new release"
# 3. Compila:
#    - Tag version: v1.0.0
#    - Release title: "🚀 My CLI App v1.0.0 - Initial Release"
#    - Description: (vedi template sotto)
#    - Upload assets da release-assets/
```

#### Metodo 2: Via GitHub CLI

```bash
# Crea release con GitHub CLI
gh release create v1.0.0 \
  --title "🚀 My CLI App v1.0.0 - Initial Release" \
  --notes "$(cat << 'EOF'
## 🎉 Welcome to My CLI App!

This is the first stable release of My CLI App, a simple and powerful command-line task manager.

### 🚀 Features

- **Task Management**: Add and list tasks with simple commands
- **Cross-Platform**: Works on Linux, macOS, and Windows
- **Easy to Use**: Intuitive command-line interface
- **Lightweight**: Minimal dependencies and fast execution

### 📦 Installation

Choose your platform:

| Platform | Download | Size |
|----------|----------|------|
| Linux/macOS | [mycli-v1.0.0-unix.tar.gz](./mycli-v1.0.0-unix.tar.gz) | ~2KB |
| Windows | [mycli-v1.0.0-windows.zip](./mycli-v1.0.0-windows.zip) | ~2KB |

### 🚀 Quick Start

```bash
# Add a task
mycli add "Your first task"

# View all tasks
mycli list

# Get help
mycli help
```

### 📖 Documentation

- [Installation Guide](./docs/INSTALLATION.md)
- [User Manual](./docs/USER_GUIDE.md)
- [Changelog](./docs/CHANGELOG.md)

### 🔒 Security

All release assets include SHA256 checksums in `checksums.txt` for verification.

### 🐛 Bug Reports

Found a bug? Please [create an issue](https://github.com/username/my-cli-app/issues/new).

### 🙏 Acknowledgments

Thank you to everyone who provided feedback during development!

---

**Full Changelog**: https://github.com/username/my-cli-app/commits/v1.0.0
EOF
)" \
  release-assets/mycli-v1.0.0-unix.tar.gz \
  release-assets/mycli-v1.0.0-windows.zip \
  release-assets/source-v1.0.0.zip \
  release-assets/source-v1.0.0.tar.gz \
  release-assets/checksums.txt
```

### Fase 8: Verifica e Post-Release

```bash
# 1. Verifica release su GitHub
gh release view v1.0.0

# 2. Test download e installazione
wget https://github.com/username/my-cli-app/releases/download/v1.0.0/mycli-v1.0.0-unix.tar.gz
tar -xzf mycli-v1.0.0-unix.tar.gz
./mycli help

# 3. Aggiorna README con badge release
echo "[![Latest Release](https://img.shields.io/github/v/release/username/my-cli-app)](https://github.com/username/my-cli-app/releases/latest)" >> README.md

# 4. Commit aggiornamenti post-release
git add README.md
git commit -m "docs: add release badge to README"
git push
```

## 📊 Risultato Finale

### Release Creata con Successo

```
✅ Tag v1.0.0 creato
✅ Release notes complete
✅ Assets multipli caricati
✅ Checksums inclusi
✅ Documentazione aggiornata
✅ Badge release aggiunto
```

### Assets Disponibili

```
📦 mycli-v1.0.0-unix.tar.gz (2.1 KB)
📦 mycli-v1.0.0-windows.zip (2.3 KB) 
📦 source-v1.0.0.zip (15.2 KB)
📦 source-v1.0.0.tar.gz (12.8 KB)
🔐 checksums.txt (256 bytes)
```

### Metriehe di Successo

- **Download Tracking**: Monitoraggio via GitHub Analytics
- **User Feedback**: Issues e discussions attivate
- **Documentation**: Guide complete per installazione e uso
- **Security**: Checksums per verifica integrità

## 🔍 Punti Chiave Appresi

1. **Tag Semantici**: Uso di v1.0.0 per prima release stabile
2. **Release Notes Strutturate**: Formato chiaro e informativo
3. **Assets Multipli**: Supporto per diverse piattaforme
4. **Verifica Sicurezza**: Checksums per integrità file
5. **Documentazione**: Guide complete per utenti

## 🔄 Prossimi Passi

1. **Monitoring**: Tracciare download e feedback
2. **Bug Fixes**: Preparare patch releases (v1.0.1)
3. **Feature Updates**: Pianificare minor releases (v1.1.0)
4. **Automazione**: Implementare CI/CD per future release

---

## 🔗 Link Utili

- [GitHub Releases Documentation](https://docs.github.com/en/repositories/releasing-projects-on-github)
- [Semantic Versioning](https://semver.org/)
- [Keep a Changelog](https://keepachangelog.com/)

## 🔄 Navigazione

- [⬅️ README Esempi](./README.md)
- [➡️ 02 - Automated Releases](./02-automated-releases.md)
- [🏠 Torna al Modulo](../README.md)
