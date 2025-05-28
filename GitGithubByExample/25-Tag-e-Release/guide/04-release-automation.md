# 04 - Release Automation

## 📋 Indice
- [Introduzione](#introduzione)
- [GitHub Actions per Release](#github-actions-per-release)
- [Conventional Commits](#conventional-commits)
- [Automated Versioning](#automated-versioning)
- [Multi-Platform Builds](#multi-platform-builds)
- [Release Pipeline](#release-pipeline)
- [Monitoring e Rollback](#monitoring-e-rollback)
- [Best Practices](#best-practices)

## Introduzione

**Release Automation** elimina il lavoro manuale e riduce gli errori nel processo di rilascio, garantendo consistenza e affidabilità.

### Vantaggi dell'Automazione

```
Manual Release Process:
Developer → Build → Test → Tag → Upload → Notes → Publish
(20-30 minuti, propenso ad errori)

Automated Release Process:  
Push → CI/CD → Auto Release
(2-5 minuti, processo ripetibile)
```

### Componenti Chiave
- **Trigger automatici** (tag, push, schedule)
- **Build multi-piattaforma** 
- **Test automatici**
- **Generazione release notes**
- **Deployment automatico**
- **Notifiche e monitoring**

## GitHub Actions per Release

### 1. Basic Release Workflow

```yaml
# .github/workflows/release.yml
name: Release

on:
  push:
    tags:
      - 'v*.*.*'

jobs:
  release:
    runs-on: ubuntu-latest
    
    steps:
      - name: Checkout
        uses: actions/checkout@v4
        with:
          fetch-depth: 0  # Necessario per changelog

      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'

      - name: Install dependencies
        run: npm ci

      - name: Run tests
        run: npm test

      - name: Build
        run: npm run build

      - name: Create Release
        uses: softprops/action-gh-release@v1
        with:
          files: |
            dist/**/*
          generate_release_notes: true
          draft: false
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 2. Advanced Release with Multiple Jobs

```yaml
# .github/workflows/advanced-release.yml
name: Advanced Release

on:
  push:
    tags: ['v*']
  workflow_dispatch:
    inputs:
      version:
        description: 'Version to release'
        required: true
        type: string

env:
  VERSION: ${{ github.event.inputs.version || github.ref_name }}

jobs:
  # Job 1: Validazione
  validate:
    runs-on: ubuntu-latest
    outputs:
      version: ${{ steps.version.outputs.version }}
      is_prerelease: ${{ steps.version.outputs.is_prerelease }}
    steps:
      - name: Validate version
        id: version
        run: |
          VERSION="${{ env.VERSION }}"
          if [[ ! $VERSION =~ ^v[0-9]+\.[0-9]+\.[0-9]+.*$ ]]; then
            echo "❌ Invalid version format: $VERSION"
            exit 1
          fi
          
          echo "version=$VERSION" >> $GITHUB_OUTPUT
          
          if [[ $VERSION =~ (alpha|beta|rc) ]]; then
            echo "is_prerelease=true" >> $GITHUB_OUTPUT
          else
            echo "is_prerelease=false" >> $GITHUB_OUTPUT
          fi

  # Job 2: Test completi
  test:
    needs: validate
    runs-on: ubuntu-latest
    strategy:
      matrix:
        node-version: [16, 18, 20]
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-node@v3
        with:
          node-version: ${{ matrix.node-version }}
      - run: npm ci
      - run: npm test
      - run: npm run lint
      - run: npm run type-check

  # Job 3: Build multi-piattaforma
  build:
    needs: [validate, test]
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        include:
          - os: ubuntu-latest
            platform: linux
            extension: ''
          - os: windows-latest
            platform: windows
            extension: '.exe'
          - os: macos-latest
            platform: macos
            extension: ''
    runs-on: ${{ matrix.os }}
    
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          
      - name: Install dependencies
        run: npm ci
        
      - name: Build for ${{ matrix.platform }}
        run: npm run build:${{ matrix.platform }}
        
      - name: Package binary
        run: |
          mkdir -p dist/
          cp build/app${{ matrix.extension }} dist/app-${{ needs.validate.outputs.version }}-${{ matrix.platform }}${{ matrix.extension }}
          
      - name: Upload artifacts
        uses: actions/upload-artifact@v3
        with:
          name: build-${{ matrix.platform }}
          path: dist/*

  # Job 4: Release finale
  release:
    needs: [validate, test, build]
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          
      - name: Download all artifacts
        uses: actions/download-artifact@v3
        with:
          path: artifacts/
          
      - name: Prepare release assets
        run: |
          mkdir -p release-assets/
          find artifacts/ -name "*" -type f -exec cp {} release-assets/ \;
          
      - name: Generate checksums
        run: |
          cd release-assets/
          sha256sum * > checksums.txt
          
      - name: Generate release notes
        id: release_notes
        run: |
          echo "RELEASE_NOTES<<EOF" >> $GITHUB_OUTPUT
          echo "## What's Changed" >> $GITHUB_OUTPUT
          git log --pretty=format:"- %s" $(git describe --tags --abbrev=0 HEAD^)..HEAD >> $GITHUB_OUTPUT
          echo "" >> $GITHUB_OUTPUT
          echo "## Assets" >> $GITHUB_OUTPUT
          ls -la release-assets/ | grep -v "^total" | awk '{print "- " $9 " (" $5 " bytes)"}' >> $GITHUB_OUTPUT
          echo "EOF" >> $GITHUB_OUTPUT
          
      - name: Create GitHub Release
        uses: softprops/action-gh-release@v1
        with:
          tag_name: ${{ needs.validate.outputs.version }}
          name: Release ${{ needs.validate.outputs.version }}
          body: ${{ steps.release_notes.outputs.RELEASE_NOTES }}
          files: release-assets/*
          prerelease: ${{ needs.validate.outputs.is_prerelease }}
          draft: false
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
          
      - name: Notify team
        if: success()
        run: |
          echo "🎉 Release ${{ needs.validate.outputs.version }} created successfully!"
          echo "URL: https://github.com/${{ github.repository }}/releases/tag/${{ needs.validate.outputs.version }}"
```

## Conventional Commits

### 1. Setup Conventional Commits

```bash
# Installa commitizen per commit standardizzati
npm install -g commitizen cz-conventional-changelog

# Configura commitizen
echo '{ "path": "cz-conventional-changelog" }' > ~/.czrc

# Ora usa 'git cz' invece di 'git commit'
git cz
```

### 2. Commit Message Format

```bash
# Formato: <type>(<scope>): <description>

# Esempi:
feat: aggiunta funzione di ricerca
fix: risolto bug nel login
docs: aggiornata documentazione API
style: formattazione codice
refactor: refactoring modulo utenti
test: aggiunti test per auth
chore: aggiornate dipendenze

# Con scope:
feat(auth): aggiunta autenticazione OAuth
fix(api): risolto timeout su requests lunghe

# Breaking changes:
feat!: cambiata struttura API response
feat(api)!: rimossa endpoint deprecated
```

### 3. Automated Versioning da Commits

```yaml
# .github/workflows/auto-version.yml
name: Auto Version

on:
  push:
    branches: [main]

jobs:
  version:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          token: ${{ secrets.GITHUB_TOKEN }}
          
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
          
      - name: Install standard-version
        run: npm install -g standard-version
        
      - name: Configure git
        run: |
          git config user.name "Release Bot"
          git config user.email "release-bot@company.com"
          
      - name: Generate version and changelog
        run: |
          # Analizza commit messages e genera nuova versione
          standard-version --skip.commit --skip.tag
          
          # Leggi la nuova versione
          NEW_VERSION=$(node -p "require('./package.json').version")
          echo "NEW_VERSION=v$NEW_VERSION" >> $GITHUB_ENV
          
      - name: Commit version bump
        run: |
          git add .
          git commit -m "chore(release): ${{ env.NEW_VERSION }}"
          git tag ${{ env.NEW_VERSION }}
          
      - name: Push changes
        run: |
          git push origin main
          git push origin ${{ env.NEW_VERSION }}
```

## Automated Versioning

### 1. Semantic Release Setup

```javascript
// .releaserc.js
module.exports = {
  branches: ['main'],
  plugins: [
    '@semantic-release/commit-analyzer',
    '@semantic-release/release-notes-generator',
    [
      '@semantic-release/changelog',
      {
        changelogFile: 'CHANGELOG.md',
      },
    ],
    '@semantic-release/npm',
    [
      '@semantic-release/git',
      {
        assets: ['CHANGELOG.md', 'package.json'],
        message:
          'chore(release): ${nextRelease.version} [skip ci]\n\n${nextRelease.notes}',
      },
    ],
    '@semantic-release/github',
  ],
};
```

### 2. Release Please Configuration

```yaml
# .github/workflows/release-please.yml
name: Release Please

on:
  push:
    branches: [main]

jobs:
  release-please:
    runs-on: ubuntu-latest
    outputs:
      release_created: ${{ steps.release.outputs.release_created }}
      tag_name: ${{ steps.release.outputs.tag_name }}
    steps:
      - uses: google-github-actions/release-please-action@v3
        id: release
        with:
          release-type: node
          package-name: my-app
          changelog-types: |
            [
              {"type": "feat", "section": "🚀 Features", "hidden": false},
              {"type": "fix", "section": "🐛 Bug Fixes", "hidden": false},
              {"type": "perf", "section": "⚡ Performance", "hidden": false},
              {"type": "docs", "section": "📖 Documentation", "hidden": false},
              {"type": "style", "section": "💎 Styles", "hidden": true},
              {"type": "refactor", "section": "♻️ Refactoring", "hidden": true},
              {"type": "test", "section": "🧪 Tests", "hidden": true},
              {"type": "chore", "section": "🔧 Miscellaneous", "hidden": true}
            ]

  # Build e deploy solo se release è stata creata
  build-and-deploy:
    needs: release-please
    if: ${{ needs.release-please.outputs.release_created }}
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Build and upload assets
        run: |
          npm run build
          gh release upload ${{ needs.release-please.outputs.tag_name }} dist/*
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 3. Custom Version Calculation

```javascript
// scripts/calculate-version.js
const { execSync } = require('child_process');
const semver = require('semver');

function getLastTag() {
  try {
    return execSync('git describe --tags --abbrev=0', { encoding: 'utf8' }).trim();
  } catch {
    return 'v0.0.0';
  }
}

function getCommitsSinceTag(tag) {
  const command = `git log ${tag}..HEAD --oneline`;
  try {
    return execSync(command, { encoding: 'utf8' })
      .split('\n')
      .filter(line => line.trim())
      .map(line => line.split(' ').slice(1).join(' '));
  } catch {
    return [];
  }
}

function calculateNextVersion() {
  const currentTag = getLastTag();
  const currentVersion = currentTag.replace('v', '');
  const commits = getCommitsSinceTag(currentTag);
  
  let bump = 'patch'; // Default
  
  for (const commit of commits) {
    if (commit.includes('BREAKING CHANGE') || commit.includes('!:')) {
      bump = 'major';
      break;
    } else if (commit.startsWith('feat')) {
      bump = 'minor';
    }
  }
  
  const nextVersion = semver.inc(currentVersion, bump);
  return `v${nextVersion}`;
}

console.log(calculateNextVersion());
```

## Multi-Platform Builds

### 1. Cross-Platform Build Matrix

```yaml
# .github/workflows/cross-platform.yml
name: Cross Platform Build

on:
  workflow_call:
    inputs:
      version:
        required: true
        type: string

jobs:
  build:
    strategy:
      matrix:
        include:
          # Linux builds
          - os: ubuntu-latest
            target: x86_64-unknown-linux-gnu
            platform: linux-x64
            
          - os: ubuntu-latest
            target: aarch64-unknown-linux-gnu
            platform: linux-arm64
            
          # Windows builds
          - os: windows-latest
            target: x86_64-pc-windows-msvc
            platform: windows-x64
            
          # macOS builds
          - os: macos-latest
            target: x86_64-apple-darwin
            platform: macos-x64
            
          - os: macos-latest
            target: aarch64-apple-darwin
            platform: macos-arm64

    runs-on: ${{ matrix.os }}
    
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup build environment
        run: |
          # Setup specifico per piattaforma
          case "${{ matrix.os }}" in
            ubuntu-latest)
              sudo apt-get update
              sudo apt-get install -y build-essential
              ;;
            windows-latest)
              # Windows setup
              ;;
            macos-latest)
              # macOS setup
              ;;
          esac
          
      - name: Build for ${{ matrix.platform }}
        run: |
          npm run build:${{ matrix.target }}
          
      - name: Package binary
        run: |
          mkdir -p dist/
          # Package specifico per piattaforma
          case "${{ matrix.platform }}" in
            linux-*)
              tar -czf dist/app-${{ inputs.version }}-${{ matrix.platform }}.tar.gz -C build/ .
              ;;
            windows-*)
              cd build && zip -r ../dist/app-${{ inputs.version }}-${{ matrix.platform }}.zip . && cd ..
              ;;
            macos-*)
              cd build && zip -r ../dist/app-${{ inputs.version }}-${{ matrix.platform }}.zip . && cd ..
              ;;
          esac
          
      - name: Upload build artifact
        uses: actions/upload-artifact@v3
        with:
          name: build-${{ matrix.platform }}
          path: dist/
```

### 2. Docker-based Builds

```yaml
# .github/workflows/docker-builds.yml
name: Docker Multi-Arch Build

on:
  workflow_call:
    inputs:
      version:
        required: true
        type: string

jobs:
  docker-build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v2
        
      - name: Build multi-arch images
        run: |
          # Build per multiple architetture
          docker buildx build \
            --platform linux/amd64,linux/arm64,linux/arm/v7 \
            --tag myapp:${{ inputs.version }} \
            --output type=local,dest=./dist \
            .
            
      - name: Extract binaries
        run: |
          # Estrai binari dalle immagini Docker
          mkdir -p release/
          
          # AMD64
          docker run --rm -v $(pwd)/release:/output \
            myapp:${{ inputs.version }}-amd64 \
            cp /app/binary /output/app-${{ inputs.version }}-linux-amd64
            
          # ARM64
          docker run --rm -v $(pwd)/release:/output \
            myapp:${{ inputs.version }}-arm64 \
            cp /app/binary /output/app-${{ inputs.version }}-linux-arm64
```

## Release Pipeline

### 1. Complete Release Pipeline

```yaml
# .github/workflows/release-pipeline.yml
name: Complete Release Pipeline

on:
  push:
    tags: ['v*']

jobs:
  # Stage 1: Preparation
  prepare:
    runs-on: ubuntu-latest
    outputs:
      version: ${{ steps.version.outputs.version }}
      is_prerelease: ${{ steps.version.outputs.is_prerelease }}
      changelog: ${{ steps.changelog.outputs.changelog }}
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          
      - name: Extract version info
        id: version
        run: |
          VERSION=${GITHUB_REF#refs/tags/}
          echo "version=$VERSION" >> $GITHUB_OUTPUT
          
          if [[ $VERSION =~ (alpha|beta|rc) ]]; then
            echo "is_prerelease=true" >> $GITHUB_OUTPUT
          else
            echo "is_prerelease=false" >> $GITHUB_OUTPUT
          fi
          
      - name: Generate changelog
        id: changelog
        run: |
          PREVIOUS_TAG=$(git describe --tags --abbrev=0 HEAD^ 2>/dev/null || echo "")
          if [ -n "$PREVIOUS_TAG" ]; then
            CHANGELOG=$(git log --pretty=format:"- %s" $PREVIOUS_TAG..HEAD)
          else
            CHANGELOG="Initial release"
          fi
          echo "changelog<<EOF" >> $GITHUB_OUTPUT
          echo "$CHANGELOG" >> $GITHUB_OUTPUT
          echo "EOF" >> $GITHUB_OUTPUT

  # Stage 2: Quality Assurance
  quality:
    needs: prepare
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Run quality checks
        run: |
          npm ci
          npm run lint
          npm run test:coverage
          npm run security-audit
          
  # Stage 3: Build
  build:
    needs: [prepare, quality]
    uses: ./.github/workflows/cross-platform.yml
    with:
      version: ${{ needs.prepare.outputs.version }}
      
  # Stage 4: Security Scan
  security:
    needs: build
    runs-on: ubuntu-latest
    steps:
      - name: Download artifacts
        uses: actions/download-artifact@v3
        
      - name: Security scan
        run: |
          # Scan dei binari per vulnerabilità
          for file in build-*/*; do
            echo "Scanning $file..."
            # Tool di security scanning
          done
          
  # Stage 5: Release
  release:
    needs: [prepare, quality, build, security]
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        
      - name: Download all artifacts
        uses: actions/download-artifact@v3
        with:
          path: release-assets/
          
      - name: Create release
        uses: softprops/action-gh-release@v1
        with:
          tag_name: ${{ needs.prepare.outputs.version }}
          name: Release ${{ needs.prepare.outputs.version }}
          body: |
            ## Changes
            ${{ needs.prepare.outputs.changelog }}
            
            ## Downloads
            - Linux x64: `app-${{ needs.prepare.outputs.version }}-linux-x64.tar.gz`
            - Windows x64: `app-${{ needs.prepare.outputs.version }}-windows-x64.zip`
            - macOS x64: `app-${{ needs.prepare.outputs.version }}-macos-x64.zip`
          files: release-assets/**/*
          prerelease: ${{ needs.prepare.outputs.is_prerelease }}
          
  # Stage 6: Post-Release
  post-release:
    needs: [prepare, release]
    runs-on: ubuntu-latest
    if: always()
    steps:
      - name: Update documentation
        run: |
          # Aggiorna siti di documentazione
          curl -X POST https://docs.example.com/webhook/update \
            -H "Authorization: Bearer ${{ secrets.DOCS_TOKEN }}" \
            -d '{"version": "${{ needs.prepare.outputs.version }}"}'
            
      - name: Notify stakeholders
        run: |
          # Notifica stakeholder via Slack/Teams/Email
          echo "Release ${{ needs.prepare.outputs.version }} completed!"
          
      - name: Update monitoring
        run: |
          # Configura monitoring per nuova versione
          echo "Setting up monitoring for ${{ needs.prepare.outputs.version }}"
```

## Monitoring e Rollback

### 1. Release Health Monitoring

```yaml
# .github/workflows/release-monitor.yml
name: Release Health Monitor

on:
  release:
    types: [published]

jobs:
  monitor:
    runs-on: ubuntu-latest
    steps:
      - name: Setup monitoring
        run: |
          VERSION=${{ github.event.release.tag_name }}
          
          # Configura alerting per nuova versione
          curl -X POST "${{ secrets.MONITORING_WEBHOOK }}" \
            -H "Content-Type: application/json" \
            -d '{
              "version": "'$VERSION'",
              "action": "monitor_start",
              "thresholds": {
                "error_rate": 0.01,
                "response_time": 500
              }
            }'
            
      - name: Wait and check metrics
        run: |
          echo "Waiting 10 minutes for metrics..."
          sleep 600
          
          # Controlla metriche
          METRICS=$(curl -s "${{ secrets.METRICS_API }}/health/$VERSION")
          ERROR_RATE=$(echo $METRICS | jq -r '.error_rate')
          
          if (( $(echo "$ERROR_RATE > 0.01" | bc -l) )); then
            echo "❌ High error rate detected: $ERROR_RATE"
            # Trigger rollback
            curl -X POST "${{ secrets.ROLLBACK_WEBHOOK }}" \
              -d '{"version": "'$VERSION'", "action": "rollback"}'
          else
            echo "✅ Release health OK"
          fi
```

### 2. Automated Rollback

```yaml
# .github/workflows/rollback.yml
name: Emergency Rollback

on:
  workflow_dispatch:
    inputs:
      target_version:
        description: 'Version to rollback to'
        required: true
      reason:
        description: 'Rollback reason'
        required: true

jobs:
  rollback:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
        with:
          fetch-depth: 0
          
      - name: Validate target version
        run: |
          if ! git tag | grep -q "^${{ github.event.inputs.target_version }}$"; then
            echo "❌ Target version not found"
            exit 1
          fi
          
      - name: Create rollback release
        run: |
          CURRENT_VERSION=$(git describe --tags --abbrev=0)
          TARGET_VERSION=${{ github.event.inputs.target_version }}
          ROLLBACK_VERSION="${CURRENT_VERSION}-rollback-$(date +%Y%m%d%H%M%S)"
          
          # Checkout target version
          git checkout $TARGET_VERSION
          
          # Create rollback tag
          git tag -a $ROLLBACK_VERSION -m "Emergency rollback from $CURRENT_VERSION to $TARGET_VERSION
          
          Reason: ${{ github.event.inputs.reason }}"
          
          git push origin $ROLLBACK_VERSION
          
      - name: Notify team
        run: |
          echo "🚨 Emergency rollback executed!"
          echo "From: $CURRENT_VERSION"
          echo "To: ${{ github.event.inputs.target_version }}"
          echo "Reason: ${{ github.event.inputs.reason }}"
```

## Best Practices

### 1. Release Strategy

```bash
# Branching strategy per releases
main                    # Production releases
├── develop            # Development integration
├── release/v1.2.0     # Release preparation
├── hotfix/critical    # Emergency fixes
└── feature/new-auth   # Feature development

# Release flow:
# 1. develop → release/v1.2.0 (stabilization)
# 2. release/v1.2.0 → main (release)
# 3. main → develop (merge back)
```

### 2. Environment Strategy

```yaml
# Deployment environments
environments:
  development:
    trigger: push to develop
    auto_deploy: true
    
  staging:
    trigger: release branch creation
    auto_deploy: true
    requires_approval: false
    
  production:
    trigger: tag creation
    auto_deploy: false
    requires_approval: true
    approvers: ['release-team']
```

### 3. Release Checklist Automation

```yaml
# Release checklist enforcement
name: Release Checklist

on:
  pull_request:
    branches: [main]
    types: [opened, synchronize]

jobs:
  checklist:
    runs-on: ubuntu-latest
    steps:
      - name: Verify changelog
        run: |
          if ! grep -q "## \[.*\]" CHANGELOG.md; then
            echo "❌ CHANGELOG.md not updated"
            exit 1
          fi
          
      - name: Verify version bump
        run: |
          # Check che la versione sia stata incrementata
          CURRENT_VERSION=$(git show HEAD:package.json | jq -r .version)
          PREVIOUS_VERSION=$(git show HEAD^:package.json | jq -r .version)
          
          if [ "$CURRENT_VERSION" = "$PREVIOUS_VERSION" ]; then
            echo "❌ Version not bumped"
            exit 1
          fi
          
      - name: Verify tests
        run: |
          if ! npm test; then
            echo "❌ Tests failing"
            exit 1
          fi
```

---

## 🔗 Link Utili

- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [Semantic Release](https://semantic-release.gitbook.io/)
- [Release Please](https://github.com/googleapis/release-please)
- [Conventional Commits](https://conventionalcommits.org/)
- [Standard Version](https://github.com/conventional-changelog/standard-version)

## 🔄 Navigazione

- [⬅️ 03 - GitHub Releases](./03-github-releases.md)
- [🏠 Torna al Modulo](../README.md)
