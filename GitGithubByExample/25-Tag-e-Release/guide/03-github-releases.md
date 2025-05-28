# 03 - GitHub Releases

## 📋 Indice
- [Introduzione](#introduzione)
- [Anatomia di una Release](#anatomia-di-una-release)
- [Creazione Release Manuale](#creazione-release-manuale)
- [Release Notes Automatiche](#release-notes-automatiche)
- [Asset e Artifacts](#asset-e-artifacts)
- [Pre-release e Draft](#pre-release-e-draft)
- [Release via API](#release-via-api)
- [Best Practices](#best-practices)

## Introduzione

**GitHub Releases** trasforma i tag Git in release formali con documentazione, artifacts e distribuzione centralizzata.

### Cosa Sono le GitHub Releases

```
Tag Git + Release Notes + Assets = GitHub Release
```

### Vantaggi delle Release
- **Documentazione**: Release notes dettagliate
- **Distribuzione**: Download centralizzato di assets
- **Notifiche**: Alert automatici ai follower
- **Integrazione**: API per automazione
- **Versioning**: Collegamento diretto ai tag

## Anatomia di una Release

### Componenti di una Release

```
GitHub Release
├── Tag Version (v1.2.0)
├── Release Title ("New Features & Bug Fixes")
├── Release Notes (markdown formatted)
├── Assets (binari, archivi, documenti)
├── Metadata (data, autore, commit)
└── Settings (pre-release, draft)
```

### Esempio Release Completa

```markdown
# v2.1.0 - "Enhanced User Experience"

## 🚀 New Features
- **User Dashboard**: Nuovo pannello di controllo utente
- **Dark Mode**: Supporto per tema scuro
- **Export Data**: Esportazione dati in CSV/JSON

## 🐛 Bug Fixes  
- Risolto crash durante il login con email lunghe
- Fixato problema con upload file > 10MB
- Corretta visualizzazione data su Safari

## 🔧 Improvements
- Performance migliorata del 40% sui database query
- UI più responsiva su dispositivi mobili
- Ridotto bundle size del 15%

## 📁 Assets
- `app-v2.1.0-windows.exe` (Windows installer)
- `app-v2.1.0-macos.dmg` (macOS package)
- `app-v2.1.0-linux.tar.gz` (Linux archive)
- `source-code.zip` (Source code)

## 🔄 Migration Guide
Per aggiornare dalla v2.0.x alla v2.1.0:
1. Backup del database esistente
2. Aggiorna config file (vedi CHANGELOG.md)
3. Esegui script di migrazione: `npm run migrate`

## ⚠️ Breaking Changes
Nessun breaking change in questa release.

---
**Full Changelog**: https://github.com/user/repo/compare/v2.0.5...v2.1.0
```

## Creazione Release Manuale

### 1. Via GitHub Web Interface

```bash
# 1. Naviga su GitHub repository
https://github.com/USERNAME/REPOSITORY

# 2. Vai alla sezione Releases
Click su "Releases" → "Create a new release"

# 3. Compila i campi:
# - Tag version: v1.2.0
# - Release title: Enhanced Features  
# - Description: [Release notes in markdown]
# - Assets: [Upload files se necessario]
```

### 2. Preparazione Tag

```bash
# Assicurati di avere un tag
git tag v1.2.0
git push origin v1.2.0

# Oppure crea tag durante la release
# GitHub può creare il tag automaticamente
```

### 3. Template Release Notes

```markdown
<!-- Template base per release notes -->

## What's Changed

### 🚀 New Features
- Feature 1 description
- Feature 2 description

### 🐛 Bug Fixes
- Bug fix 1
- Bug fix 2

### 🔧 Improvements
- Performance improvement 1
- UX improvement 2

### 📖 Documentation
- Updated API docs
- Added tutorial for new feature

### 🔒 Security
- Fixed security vulnerability in auth module

## Assets
- `binary-v1.2.0.zip` - Main application
- `docs-v1.2.0.pdf` - Documentation

## Upgrade Notes
Instructions for upgrading from previous version.

**Full Changelog**: https://github.com/user/repo/compare/v1.1.0...v1.2.0
```

## Release Notes Automatiche

### 1. GitHub Auto-generated Notes

```yaml
# .github/release.yml
changelog:
  exclude:
    labels:
      - ignore-for-release
  categories:
    - title: 🚀 New Features
      labels:
        - enhancement
        - feature
    - title: 🐛 Bug Fixes
      labels:
        - bug
        - bugfix
    - title: 📖 Documentation
      labels:
        - documentation
    - title: Other Changes
      labels:
        - "*"
```

### 2. Conventional Commits Integration

```bash
# Install standard-version
npm install -g standard-version

# Genera CHANGELOG e release notes
standard-version

# Output automatico:
# - Analizza commit messages
# - Genera CHANGELOG.md  
# - Crea tag con versione incrementata
# - Prepara release notes
```

### 3. Automated Release Workflow

```yaml
# .github/workflows/release.yml
name: Create Release

on:
  push:
    tags:
      - 'v*'

jobs:
  release:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0

      - name: Generate Release Notes
        id: release_notes
        run: |
          # Script per generare release notes
          echo "RELEASE_NOTES<<EOF" >> $GITHUB_OUTPUT
          git log --pretty=format:"- %s" $(git describe --tags --abbrev=0 HEAD^)..HEAD >> $GITHUB_OUTPUT
          echo "EOF" >> $GITHUB_OUTPUT

      - name: Create Release
        uses: actions/create-release@v1
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        with:
          tag_name: ${{ github.ref_name }}
          release_name: Release ${{ github.ref_name }}
          body: ${{ steps.release_notes.outputs.RELEASE_NOTES }}
          draft: false
          prerelease: false
```

## Asset e Artifacts

### 1. Tipi di Assets Comuni

```bash
# Binari compilati
app-v1.2.0-windows.exe      # Windows executable
app-v1.2.0-macos.app        # macOS application  
app-v1.2.0-linux            # Linux binary

# Archivi sorgente
source-v1.2.0.tar.gz        # Source tarball
source-v1.2.0.zip           # Source zip

# Documentazione
docs-v1.2.0.pdf             # Documentation PDF
api-reference-v1.2.0.html   # API reference

# Configurazioni
config-template-v1.2.0.yml  # Configuration template
migration-script-v1.2.0.sql # Database migration
```

### 2. Build e Upload Assets

```yaml
# Build workflow per multiple platform
name: Build and Release

on:
  push:
    tags: ['v*']

jobs:
  build:
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
    runs-on: ${{ matrix.os }}
    
    steps:
      - uses: actions/checkout@v3
      
      - name: Build
        run: |
          # Build specifico per OS
          npm run build:${{ matrix.os }}
          
      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: build-${{ matrix.os }}
          path: dist/

  release:
    needs: build
    runs-on: ubuntu-latest
    steps:
      - name: Download artifacts
        uses: actions/download-artifact@v3
        
      - name: Create Release
        uses: softprops/action-gh-release@v1
        with:
          files: |
            build-ubuntu-latest/*
            build-windows-latest/*
            build-macos-latest/*
```

### 3. Asset Management Script

```bash
#!/bin/bash
# release-assets.sh

VERSION=$1
if [ -z "$VERSION" ]; then
    echo "Usage: $0 <version>"
    exit 1
fi

echo "📦 Preparando assets per release $VERSION..."

# 1. Build per multiple piattaforme
echo "🔨 Building applications..."
npm run build:all

# 2. Crea archivi
echo "📁 Creando archivi..."
cd dist/
tar -czf "../app-$VERSION-linux.tar.gz" linux/
zip -r "../app-$VERSION-windows.zip" windows/
zip -r "../app-$VERSION-macos.zip" macos/
cd ..

# 3. Genera checksums
echo "🔐 Generando checksums..."
sha256sum app-$VERSION-* > checksums-$VERSION.txt

# 4. Lista assets creati
echo "✅ Assets creati:"
ls -la app-$VERSION-*
echo ""
echo "📋 Per uploadare su GitHub:"
echo "gh release create $VERSION app-$VERSION-* checksums-$VERSION.txt"
```

## Pre-release e Draft

### 1. Draft Releases

```bash
# Crea draft release via CLI
gh release create v1.2.0-beta.1 \
  --title "v1.2.0 Beta 1" \
  --notes "Beta release for testing" \
  --draft

# Lista draft releases  
gh release list --limit 10
```

### 2. Pre-release Management

```yaml
# Workflow per pre-release automatiche
name: Pre-release

on:
  push:
    branches: [develop]

jobs:
  pre-release:
    if: contains(github.event.head_commit.message, '[pre-release]')
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Create pre-release
        run: |
          VERSION="v$(date +%Y%m%d)-$(git rev-parse --short HEAD)"
          gh release create $VERSION \
            --title "Development Build $VERSION" \
            --notes "Automated pre-release from develop branch" \
            --prerelease
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 3. Beta Testing Workflow

```bash
# Workflow per beta releases
# 1. Crea branch per beta
git checkout -b release/v1.2.0-beta
git push origin release/v1.2.0-beta

# 2. Trigger beta release
git tag v1.2.0-beta.1
git push origin v1.2.0-beta.1

# 3. Testa e itera
# ... testing ...
git tag v1.2.0-beta.2
git push origin v1.2.0-beta.2

# 4. Release finale
git checkout main
git merge release/v1.2.0-beta
git tag v1.2.0
git push origin v1.2.0
```

## Release via API

### 1. GitHub REST API

```bash
# Crea release via API
curl -X POST \
  -H "Authorization: token $GITHUB_TOKEN" \
  -H "Accept: application/vnd.github.v3+json" \
  https://api.github.com/repos/OWNER/REPO/releases \
  -d '{
    "tag_name": "v1.2.0",
    "target_commitish": "main",
    "name": "v1.2.0",
    "body": "Release notes here",
    "draft": false,
    "prerelease": false
  }'
```

### 2. Script di Automazione

```javascript
// release-script.js
const { Octokit } = require("@octokit/rest");
const fs = require("fs");

const octokit = new Octokit({
  auth: process.env.GITHUB_TOKEN,
});

async function createRelease(version, notes, assets = []) {
  try {
    // 1. Crea release
    const release = await octokit.rest.repos.createRelease({
      owner: "USERNAME",
      repo: "REPOSITORY", 
      tag_name: version,
      name: version,
      body: notes,
      draft: false,
      prerelease: version.includes("beta") || version.includes("alpha")
    });

    console.log(`✅ Release ${version} creata!`);

    // 2. Upload assets
    for (const asset of assets) {
      await octokit.rest.repos.uploadReleaseAsset({
        owner: "USERNAME",
        repo: "REPOSITORY",
        release_id: release.data.id,
        name: asset.name,
        data: fs.readFileSync(asset.path),
      });
      console.log(`📎 Asset ${asset.name} caricato`);
    }

  } catch (error) {
    console.error("❌ Errore:", error.message);
  }
}

// Uso
const releaseNotes = fs.readFileSync("RELEASE_NOTES.md", "utf8");
const assets = [
  { name: "app-linux.tar.gz", path: "./dist/app-linux.tar.gz" },
  { name: "app-windows.zip", path: "./dist/app-windows.zip" }
];

createRelease("v1.2.0", releaseNotes, assets);
```

### 3. GitHub CLI Integration

```bash
#!/bin/bash
# release-cli.sh

VERSION=$1
NOTES_FILE=$2

if [ -z "$VERSION" ] || [ -z "$NOTES_FILE" ]; then
    echo "Usage: $0 <version> <notes-file>"
    exit 1
fi

# 1. Verifica tag esiste
if ! git tag | grep -q "^$VERSION$"; then
    echo "❌ Tag $VERSION non esiste"
    exit 1
fi

# 2. Crea release con assets
gh release create "$VERSION" \
  --title "$VERSION" \
  --notes-file "$NOTES_FILE" \
  dist/*.{zip,tar.gz,exe} \
  checksums.txt

echo "✅ Release $VERSION pubblicata!"

# 3. Notifica team
echo "🔔 Notificando il team..."
gh api repos/:owner/:repo/releases/latest \
  --jq '.html_url' | \
  xargs -I {} echo "Nuova release disponibile: {}"
```

## Best Practices

### 1. Nomenclatura Release

```bash
# ✅ Buone pratiche
v1.2.0              # Semantic versioning
v2.0.0-beta.1       # Pre-release chiara
v1.2.0-hotfix       # Hotfix identificabile

# ❌ Da evitare  
release-final       # Non specifico
v1.2               # Incompleto
latest              # Ambiguo
```

### 2. Struttura Release Notes

```markdown
<!-- Template strutturato -->

## 🎯 Highlights
Brief overview of major changes

## 📈 Statistics  
- X new features
- Y bug fixes
- Z% performance improvement

## 🚀 New Features
### Major Features
- Feature 1 with detailed description
- Feature 2 with use cases

### Minor Features  
- Small improvement 1
- Small improvement 2

## 🐛 Bug Fixes
### Critical Fixes
- Critical bug 1 (Security impact)
- Critical bug 2 (Data loss prevention)

### Minor Fixes
- UI bug 1
- Edge case fix 2

## 🔧 Improvements
- Performance optimization details
- UX improvements

## 🔄 Migration Guide
Step-by-step upgrade instructions

## 💔 Breaking Changes
- Change 1 with migration path
- Change 2 with alternatives

## 📁 Downloads
| Platform | File | Size | Checksum |
|----------|------|------|----------|
| Windows  | app.exe | 50MB | sha256... |
| macOS    | app.dmg | 45MB | sha256... |
| Linux    | app.tar.gz | 40MB | sha256... |

## 🙏 Contributors
Thanks to all contributors who made this release possible!

---
**Full Changelog**: [v1.1.0...v1.2.0](link)
```

### 3. Checklist Pre-Release

```markdown
## Release Checklist

### Pre-Release
- [ ] Tutti i test passano
- [ ] Documentazione aggiornata
- [ ] CHANGELOG.md aggiornato
- [ ] Version bump completato
- [ ] Tag creato e pushato
- [ ] Build assets preparati
- [ ] Checksums generati

### Release Creation
- [ ] Release notes complete
- [ ] Assets caricati
- [ ] Links verificati
- [ ] Migration guide presente (se breaking changes)

### Post-Release
- [ ] Release annunciata al team
- [ ] Documentazione sito aggiornata
- [ ] Package repositories aggiornati (npm, etc.)
- [ ] Monitoring attivato per nuova versione
- [ ] Feedback canali aperti
```

### 4. Automation Best Practices

```yaml
# Release automation completa
name: Complete Release Process

on:
  workflow_dispatch:
    inputs:
      version:
        description: 'Release version (e.g., v1.2.0)'
        required: true
      pre_release:
        description: 'Mark as pre-release'
        type: boolean
        default: false

jobs:
  validate:
    runs-on: ubuntu-latest
    steps:
      - name: Validate version format
        run: |
          if [[ ! "${{ github.event.inputs.version }}" =~ ^v[0-9]+\.[0-9]+\.[0-9]+.*$ ]]; then
            echo "❌ Invalid version format"
            exit 1
          fi

  test:
    needs: validate
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run tests
        run: npm test

  build:
    needs: test
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
    runs-on: ${{ matrix.os }}
    steps:
      - name: Build and package
        run: npm run build:${{ matrix.os }}

  release:
    needs: [validate, test, build]
    runs-on: ubuntu-latest
    steps:
      - name: Create GitHub Release
        uses: softprops/action-gh-release@v1
        with:
          tag_name: ${{ github.event.inputs.version }}
          prerelease: ${{ github.event.inputs.pre_release }}
          generate_release_notes: true
          files: |
            dist/**/*
```

---

## 🔗 Link Utili

- [GitHub Releases Documentation](https://docs.github.com/en/repositories/releasing-projects-on-github)
- [GitHub CLI Releases](https://cli.github.com/manual/gh_release)
- [Octokit.js (GitHub API)](https://octokit.github.io/rest.js/)
- [Release Automation Tools](https://github.com/semantic-release/semantic-release)

## 🔄 Navigazione

- [⬅️ 02 - Semantic Versioning](./02-semantic-versioning.md)
- [➡️ 04 - Release Automation](./04-release-automation.md)
- [🏠 Torna al Modulo](../README.md)
