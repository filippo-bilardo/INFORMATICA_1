# 02 - Semantic Versioning

## 📋 Indice
- [Introduzione](#introduzione)
- [Schema di Versioning](#schema-di-versioning)
- [Regole di Incremento](#regole-di-incremento)
- [Pre-release e Metadata](#pre-release-e-metadata)
- [Esempi Pratici](#esempi-pratici)
- [Best Practices](#best-practices)
- [Strumenti di Automazione](#strumenti-di-automazione)

## Introduzione

**Semantic Versioning** (SemVer) è uno standard per assegnare numeri di versione ai software in modo significativo e prevedibile.

### Vantaggi del Semantic Versioning

```bash
# Schema base: MAJOR.MINOR.PATCH
1.0.0   # Prima release stabile
1.0.1   # Bug fix
1.1.0   # Nuova feature
2.0.0   # Breaking change
```

### Benefici
- **Predicibilità**: Gli utenti sanno cosa aspettarsi
- **Automazione**: Tool possono gestire dipendenze automaticamente  
- **Comunicazione**: Cambio di versione comunica tipo di modifica
- **Compatibilità**: Gestione chiara della retrocompatibilità

## Schema di Versioning

### Formato Base

```
MAJOR.MINOR.PATCH
```

- **MAJOR**: Incrementato per breaking changes
- **MINOR**: Incrementato per nuove feature retrocompatibili
- **PATCH**: Incrementato per bug fix retrocompatibili

### Esempi di Incremento

```bash
# Da 1.2.3 a:
1.2.4   # Bug fix (PATCH)
1.3.0   # Nuova feature (MINOR)
2.0.0   # Breaking change (MAJOR)
```

## Regole di Incremento

### MAJOR Version (X.y.z)

Incrementa quando introduci **breaking changes**:

```javascript
// Versione 1.x.x
function getUserData(userId) {
    return { id: userId, name: "User" };
}

// Versione 2.0.0 - Breaking change
function getUserData(userId, options = {}) {
    // Cambiato il formato di ritorno
    return {
        user: { id: userId, name: "User" },
        metadata: options
    };
}
```

### MINOR Version (x.Y.z)

Incrementa quando aggiungi **funzionalità retrocompatibili**:

```javascript
// Versione 1.1.0 - Aggiunta nuova funzione
function getUserData(userId) {
    return { id: userId, name: "User" };
}

// Nuova funzione aggiunta
function getUserSettings(userId) {
    return { theme: "dark", language: "it" };
}
```

### PATCH Version (x.y.Z)

Incrementa quando fissi **bug retrocompatibili**:

```javascript
// Versione 1.1.0 - Bug
function calculateTotal(items) {
    return items.reduce((sum, item) => sum + item.price, 0);
    // Bug: non gestisce items null/undefined
}

// Versione 1.1.1 - Bug fix
function calculateTotal(items) {
    if (!items || !Array.isArray(items)) return 0;
    return items.reduce((sum, item) => sum + item.price, 0);
}
```

## Pre-release e Metadata

### Pre-release Versions

```bash
1.0.0-alpha.1      # Versione alpha
1.0.0-beta.2       # Versione beta
1.0.0-rc.1         # Release candidate
```

### Build Metadata

```bash
1.0.0+20230524.1   # Con timestamp
1.0.0+commit.abc123 # Con commit hash
```

### Esempi Completi

```bash
# Sviluppo di una nuova major version
2.0.0-alpha.1      # Prima alpha
2.0.0-alpha.2      # Seconda alpha
2.0.0-beta.1       # Prima beta
2.0.0-rc.1         # Release candidate
2.0.0              # Release finale

# Con metadata
2.0.0-rc.1+build.123
```

## Esempi Pratici

### Workflow di Rilascio

```bash
# 1. Sviluppo feature
git checkout -b feature/new-api
# ... sviluppo ...
git tag v1.1.0-alpha.1

# 2. Testing
git tag v1.1.0-beta.1

# 3. Release candidate
git tag v1.1.0-rc.1

# 4. Release finale
git tag v1.1.0
```

### Gestione Bug Fix

```bash
# Release corrente: 2.1.5
# Bug critico scoperto

# 1. Hotfix
git checkout -b hotfix/critical-bug
# ... fix ...

# 2. Release patch
git tag v2.1.6

# 3. Merge in develop
git checkout develop
git merge hotfix/critical-bug
```

### Gestione Breaking Changes

```bash
# Pianificazione major release
echo "# Breaking Changes in 3.0.0

## API Changes
- `getUserData()` now returns Promise
- Removed deprecated `oldFunction()`

## Migration Guide
- Replace `getUserData()` calls with await
- Use `newFunction()` instead of `oldFunction()`
" > BREAKING_CHANGES.md

git tag v3.0.0
```

## Best Practices

### 1. Versione Iniziale

```bash
# Prima release pubblica
git tag v1.0.0

# Sviluppo pre-1.0
git tag v0.1.0  # Early development
git tag v0.9.0  # Near stable
```

### 2. Documentazione Cambiamenti

```markdown
# CHANGELOG.md

## [2.1.0] - 2024-01-15

### Added
- Nuova API per gestione utenti
- Supporto per autenticazione OAuth

### Changed
- Migliorata performance della ricerca

### Fixed
- Risolto bug nella validazione email

### Deprecated
- `oldApiFunction()` sarà rimossa in v3.0.0
```

### 3. Automazione con Scripts

```json
// package.json
{
  "scripts": {
    "version:patch": "npm version patch",
    "version:minor": "npm version minor", 
    "version:major": "npm version major",
    "version:prerelease": "npm version prerelease --preid=alpha"
  }
}
```

### 4. Validazione Versioni

```bash
# Script di validazione
#!/bin/bash
validate_version() {
    local version=$1
    if [[ ! $version =~ ^[0-9]+\.[0-9]+\.[0-9]+$ ]]; then
        echo "Errore: Versione non valida: $version"
        exit 1
    fi
}

validate_version "1.2.3"  # ✅ Valida
validate_version "1.2"    # ❌ Non valida
```

## Strumenti di Automazione

### 1. Conventional Commits

```bash
# Commit messages strutturati
feat: aggiunta nuova API utenti       # → MINOR
fix: risolto bug validazione         # → PATCH
feat!: cambiata struttura risposta   # → MAJOR

# Generazione automatica versione
npm install -g standard-version
standard-version  # Analizza commits e incrementa versione
```

### 2. Release Please (GitHub)

```yaml
# .github/workflows/release-please.yml
name: Release Please
on:
  push:
    branches: [main]

jobs:
  release-please:
    runs-on: ubuntu-latest
    steps:
      - uses: google-github-actions/release-please-action@v3
        with:
          release-type: node
          package-name: my-package
```

### 3. Semantic Release

```javascript
// .releaserc.js
module.exports = {
  branches: ['main'],
  plugins: [
    '@semantic-release/commit-analyzer',
    '@semantic-release/release-notes-generator',
    '@semantic-release/changelog',
    '@semantic-release/npm',
    '@semantic-release/github'
  ]
};
```

### 4. Version Management Script

```bash
#!/bin/bash
# release.sh

set -e

# Ottieni versione corrente
CURRENT_VERSION=$(git describe --tags --abbrev=0 2>/dev/null || echo "v0.0.0")
echo "Versione corrente: $CURRENT_VERSION"

# Menu per tipo di release
echo "Tipo di release:"
echo "1) patch (bug fix)"
echo "2) minor (nuova feature)"  
echo "3) major (breaking change)"
read -p "Seleziona (1-3): " choice

case $choice in
    1) NEW_VERSION=$(semver -i patch $CURRENT_VERSION) ;;
    2) NEW_VERSION=$(semver -i minor $CURRENT_VERSION) ;;
    3) NEW_VERSION=$(semver -i major $CURRENT_VERSION) ;;
    *) echo "Scelta non valida"; exit 1 ;;
esac

echo "Nuova versione: $NEW_VERSION"
read -p "Confermi? (y/N): " confirm

if [[ $confirm == "y" ]]; then
    git tag -a "$NEW_VERSION" -m "Release $NEW_VERSION"
    git push origin "$NEW_VERSION"
    echo "✅ Release $NEW_VERSION creata!"
fi
```

## Quiz di Autovalutazione

### Domande

1. **Quale numero incrementi per un bug fix?**
   - a) MAJOR
   - b) MINOR  
   - c) PATCH ✅

2. **Cosa indica la versione `2.1.0-beta.3`?**
   - a) Terza beta della versione 2.1.0 ✅
   - b) Build numero 3
   - c) Patch 3 della beta

3. **Quando incrementi il numero MAJOR?**
   - a) Nuove feature
   - b) Bug fix
   - c) Breaking changes ✅

### Esercizio Pratico

Dato questo changelog, determina le versioni corrette:

```
Versione corrente: 1.2.5

Cambiamenti:
- Aggiunta funzione di ricerca avanzata
- Risolto bug nel salvataggio dati  
- Rimossa API deprecated (breaking)
- Aggiunto supporto per nuovi filtri
```

**Risposta**: La presenza di breaking changes richiede `2.0.0`

---

## 🔗 Link Utili

- [Semantic Versioning Specification](https://semver.org/)
- [Conventional Commits](https://conventionalcommits.org/)
- [Standard Version](https://github.com/conventional-changelog/standard-version)
- [Release Please](https://github.com/googleapis/release-please)

## 🔄 Navigazione

- [⬅️ 01 - Git Tags](./01-git-tags.md)
- [➡️ 03 - GitHub Releases](./03-github-releases.md)
- [🏠 Torna al Modulo](../README.md)
