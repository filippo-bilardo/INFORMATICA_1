# 01 - Esercizio: Release Workflow Completo

Questo esercizio ti guida attraverso un workflow completo di release, dalla pianificazione al deployment, utilizzando un progetto JavaScript reale.

## 🎯 Obiettivi

- Implementare un workflow di release completo
- Creare tag e release seguendo le best practices
- Automatizzare il processo con GitHub Actions
- Gestire versioning con Semantic Versioning

## 📋 Prerequisiti

- Git installato e configurato
- Account GitHub
- Node.js e npm installati
- Conoscenza base di JavaScript

## 🚀 Scenario

Sviluppiamo una libreria JavaScript per manipolazione di stringhe e implementiamo un workflow di release professionale.

## Parte 1: Setup del Progetto

### 1.1 Creazione del Repository

```bash
# Crea directory del progetto
mkdir string-utils-lib
cd string-utils-lib

# Inizializza Git
git init
git branch -M main

# Crea repository su GitHub (sostituisci con il tuo username)
# Poi collega il repository locale
git remote add origin https://github.com/TUO-USERNAME/string-utils-lib.git
```

### 1.2 Struttura del Progetto

```bash
# Inizializza package.json
npm init -y

# Installa dipendenze di sviluppo
npm install --save-dev jest eslint prettier
```

**Aggiorna `package.json`**:
```json
{
  "name": "string-utils-lib",
  "version": "0.0.0",
  "description": "Utility library for string manipulation",
  "main": "src/index.js",
  "scripts": {
    "test": "jest",
    "lint": "eslint src/",
    "format": "prettier --write src/",
    "prepare": "npm run lint && npm run test"
  },
  "keywords": ["string", "utils", "javascript"],
  "author": "Your Name",
  "license": "MIT",
  "devDependencies": {
    "jest": "^29.0.0",
    "eslint": "^8.0.0",
    "prettier": "^2.0.0"
  }
}
```

### 1.3 Codice Base

**`src/index.js`**:
```javascript
/**
 * String Utils Library
 * A collection of utility functions for string manipulation
 */

/**
 * Capitalizes the first letter of a string
 * @param {string} str - The input string
 * @returns {string} The capitalized string
 */
function capitalize(str) {
  if (typeof str !== 'string' || str.length === 0) {
    return str;
  }
  return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
}

/**
 * Converts a string to camelCase
 * @param {string} str - The input string
 * @returns {string} The camelCase string
 */
function toCamelCase(str) {
  if (typeof str !== 'string') {
    return str;
  }
  return str
    .replace(/(?:^\w|[A-Z]|\b\w)/g, (word, index) => {
      return index === 0 ? word.toLowerCase() : word.toUpperCase();
    })
    .replace(/\s+/g, '');
}

/**
 * Truncates a string to a specified length
 * @param {string} str - The input string
 * @param {number} length - Maximum length
 * @param {string} suffix - Suffix to add when truncated
 * @returns {string} The truncated string
 */
function truncate(str, length, suffix = '...') {
  if (typeof str !== 'string' || str.length <= length) {
    return str;
  }
  return str.substring(0, length - suffix.length) + suffix;
}

module.exports = {
  capitalize,
  toCamelCase,
  truncate
};
```

**`tests/index.test.js`**:
```javascript
const { capitalize, toCamelCase, truncate } = require('../src/index');

describe('String Utils Library', () => {
  describe('capitalize', () => {
    test('should capitalize first letter', () => {
      expect(capitalize('hello')).toBe('Hello');
      expect(capitalize('WORLD')).toBe('World');
    });

    test('should handle edge cases', () => {
      expect(capitalize('')).toBe('');
      expect(capitalize(null)).toBe(null);
      expect(capitalize(undefined)).toBe(undefined);
    });
  });

  describe('toCamelCase', () => {
    test('should convert to camelCase', () => {
      expect(toCamelCase('hello world')).toBe('helloWorld');
      expect(toCamelCase('foo bar baz')).toBe('fooBarBaz');
    });

    test('should handle edge cases', () => {
      expect(toCamelCase('')).toBe('');
      expect(toCamelCase('single')).toBe('single');
    });
  });

  describe('truncate', () => {
    test('should truncate long strings', () => {
      expect(truncate('Hello World', 8)).toBe('Hello...');
      expect(truncate('Short', 10)).toBe('Short');
    });

    test('should use custom suffix', () => {
      expect(truncate('Hello World', 8, '!!!')).toBe('Hello!!!');
    });
  });
});
```

### 1.4 Configurazione Linting

**`.eslintrc.js`**:
```javascript
module.exports = {
  env: {
    node: true,
    es2021: true,
    jest: true
  },
  extends: ['eslint:recommended'],
  parserOptions: {
    ecmaVersion: 12,
    sourceType: 'module'
  },
  rules: {
    'no-console': 'warn',
    'no-unused-vars': 'error'
  }
};
```

**`.prettierrc`**:
```json
{
  "semi": true,
  "trailingComma": "es5",
  "singleQuote": true,
  "printWidth": 80,
  "tabWidth": 2
}
```

### 1.5 First Commit

```bash
# Aggiungi tutti i file
git add .

# Commit iniziale
git commit -m "feat: initial library implementation

- Add capitalize function
- Add toCamelCase function  
- Add truncate function
- Add comprehensive test suite
- Add ESLint and Prettier configuration"

# Push su GitHub
git push -u origin main
```

## Parte 2: Development Workflow

### 2.1 Feature Development

```bash
# Crea branch per nuova feature
git checkout -b feature/reverse-string

# Implementa la nuova funzione
```

**Aggiungi a `src/index.js`**:
```javascript
/**
 * Reverses a string
 * @param {string} str - The input string
 * @returns {string} The reversed string
 */
function reverse(str) {
  if (typeof str !== 'string') {
    return str;
  }
  return str.split('').reverse().join('');
}

// Aggiungi al module.exports
module.exports = {
  capitalize,
  toCamelCase,
  truncate,
  reverse
};
```

**Aggiungi test in `tests/index.test.js`**:
```javascript
describe('reverse', () => {
  test('should reverse string', () => {
    expect(reverse('hello')).toBe('olleh');
    expect(reverse('12345')).toBe('54321');
  });

  test('should handle edge cases', () => {
    expect(reverse('')).toBe('');
    expect(reverse('a')).toBe('a');
  });
});
```

```bash
# Testa la nuova feature
npm test

# Commit della feature
git add .
git commit -m "feat: add reverse string function

- Add reverse() function to reverse strings
- Add comprehensive tests for reverse function
- Update module exports"

# Push del branch
git push origin feature/reverse-string
```

### 2.2 Pull Request e Merge

1. **Crea Pull Request su GitHub**
2. **Merge nella main branch**

```bash
# Torna su main e aggiorna
git checkout main
git pull origin main

# Elimina il branch feature (opzionale)
git branch -d feature/reverse-string
```

## Parte 3: Preparazione per la Release

### 3.1 Conventional Commits Setup

**`.gitmessage`**:
```
# <type>[optional scope]: <description>
#
# [optional body]
#
# [optional footer(s)]
#
# Types:
# feat:     A new feature
# fix:      A bug fix
# docs:     Documentation only changes
# style:    Changes that do not affect the meaning of the code
# refactor: A code change that neither fixes a bug nor adds a feature
# perf:     A code change that improves performance
# test:     Adding missing tests or correcting existing tests
# build:    Changes that affect the build system or external dependencies
# ci:       Changes to our CI configuration files and scripts
# chore:    Other changes that don't modify src or test files
```

```bash
# Configura il template di commit
git config commit.template .gitmessage
```

### 3.2 Changelog Setup

**`CHANGELOG.md`**:
```markdown
# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial library implementation
- capitalize() function
- toCamelCase() function
- truncate() function
- reverse() function

### Changed

### Deprecated

### Removed

### Fixed

### Security
```

## Parte 4: First Release (v1.0.0)

### 4.1 Pre-Release Checklist

```bash
# Verifica che tutto funzioni
npm test
npm run lint

# Aggiorna la documentazione
```

**`README.md`**:
```markdown
# String Utils Library

A lightweight JavaScript library for common string manipulation tasks.

## Installation

```bash
npm install string-utils-lib
```

## Usage

```javascript
const { capitalize, toCamelCase, truncate, reverse } = require('string-utils-lib');

// Capitalize first letter
console.log(capitalize('hello world')); // "Hello world"

// Convert to camelCase
console.log(toCamelCase('hello world')); // "helloWorld"

// Truncate string
console.log(truncate('Hello World', 8)); // "Hello..."

// Reverse string
console.log(reverse('hello')); // "olleh"
```

## API Reference

### capitalize(str)
Capitalizes the first letter of a string.

### toCamelCase(str) 
Converts a string to camelCase.

### truncate(str, length, suffix = '...')
Truncates a string to a specified length.

### reverse(str)
Reverses a string.

## License

MIT
```

### 4.2 Update Version e Changelog

```bash
# Aggiorna package.json version
npm version major --no-git-tag-version
```

**Aggiorna `CHANGELOG.md`**:
```markdown
# Changelog

## [1.0.0] - 2025-01-XX

### Added
- Initial library implementation
- capitalize() function for capitalizing first letter
- toCamelCase() function for converting to camelCase  
- truncate() function for truncating strings
- reverse() function for reversing strings
- Comprehensive test suite with Jest
- ESLint and Prettier configuration
- Documentation and examples

## [Unreleased]

### Added

### Changed

### Deprecated

### Removed

### Fixed

### Security
```

### 4.3 Release Commit e Tag

```bash
# Commit della release
git add .
git commit -m "chore(release): prepare v1.0.0

- Update package.json to version 1.0.0
- Update CHANGELOG.md with release notes
- Add comprehensive README documentation"

# Crea tag annotato
git tag -a v1.0.0 -m "Release version 1.0.0

First stable release of String Utils Library

Features:
- capitalize() - Capitalize first letter
- toCamelCase() - Convert to camelCase  
- truncate() - Truncate strings
- reverse() - Reverse strings

This release includes comprehensive tests and documentation."

# Push commit e tag
git push origin main
git push origin v1.0.0
```

### 4.4 GitHub Release

1. **Vai su GitHub → Releases → Create a new release**
2. **Seleziona tag**: v1.0.0
3. **Release title**: String Utils Library v1.0.0
4. **Description**:
```markdown
# 🎉 First Stable Release

This is the first stable release of String Utils Library, a lightweight JavaScript library for common string manipulation tasks.

## ✨ Features

- **capitalize()** - Capitalize the first letter of a string
- **toCamelCase()** - Convert strings to camelCase format
- **truncate()** - Truncate strings with customizable suffix
- **reverse()** - Reverse string characters

## 📦 Installation

```bash
npm install string-utils-lib
```

## 🚀 Quick Start

```javascript
const { capitalize, toCamelCase, truncate, reverse } = require('string-utils-lib');

console.log(capitalize('hello'));      // "Hello"
console.log(toCamelCase('hello world')); // "helloWorld"
console.log(truncate('Long text', 5));   // "Lo..."
console.log(reverse('hello'));           // "olleh"
```

## 📋 What's Changed

- Initial library implementation with core string utilities
- Comprehensive test coverage with Jest
- TypeScript definitions (coming in v1.1.0)
- Complete documentation and examples

## 🔗 Links

- [Documentation](https://github.com/USERNAME/string-utils-lib#readme)
- [Changelog](https://github.com/USERNAME/string-utils-lib/blob/main/CHANGELOG.md)
- [Issues](https://github.com/USERNAME/string-utils-lib/issues)

**Full Changelog**: https://github.com/USERNAME/string-utils-lib/commits/v1.0.0
```

5. **Pubblica la release**

## Parte 5: Bug Fix Release (v1.0.1)

### 5.1 Simula e Risolvi un Bug

```bash
# Crea branch per bug fix
git checkout -b fix/capitalize-numbers

# Modifica src/index.js per gestire meglio i casi edge
```

**Aggiorna la funzione `capitalize`**:
```javascript
function capitalize(str) {
  if (typeof str !== 'string' || str.length === 0) {
    return str;
  }
  // Fix: gestisci meglio stringhe che iniziano con numeri
  const firstChar = str.charAt(0);
  if (/\d/.test(firstChar)) {
    return str; // Non modificare stringhe che iniziano con numeri
  }
  return firstChar.toUpperCase() + str.slice(1).toLowerCase();
}
```

**Aggiungi test**:
```javascript
test('should handle strings starting with numbers', () => {
  expect(capitalize('123abc')).toBe('123abc');
  expect(capitalize('9test')).toBe('9test');
});
```

```bash
# Test del fix
npm test

# Commit del fix
git add .
git commit -m "fix(capitalize): handle strings starting with numbers

The capitalize function now correctly handles strings that start 
with numbers by leaving them unchanged instead of attempting to 
capitalize numeric characters.

Fixes #1"

# Push e merge
git push origin fix/capitalize-numbers
```

### 5.2 Patch Release

```bash
# Merge in main
git checkout main
git merge fix/capitalize-numbers

# Aggiorna versione
npm version patch --no-git-tag-version

# Aggiorna changelog
```

**CHANGELOG.md**:
```markdown
## [1.0.1] - 2025-01-XX

### Fixed
- capitalize() now correctly handles strings starting with numbers

## [1.0.0] - 2025-01-XX
...
```

```bash
# Release commit
git add .
git commit -m "chore(release): v1.0.1

- Fix capitalize function for strings starting with numbers
- Update changelog and version"

# Tag e push
git tag -a v1.0.1 -m "Release v1.0.1 - Bug fix for capitalize function"
git push origin main v1.0.1
```

## Parte 6: Feature Release (v1.1.0)

### 6.1 Nuova Feature

```bash
# Branch per nuova feature
git checkout -b feature/slug-function

# Implementa funzione slug
```

**Aggiungi a `src/index.js`**:
```javascript
/**
 * Converts a string to URL-friendly slug
 * @param {string} str - The input string
 * @returns {string} The slug string
 */
function toSlug(str) {
  if (typeof str !== 'string') {
    return str;
  }
  return str
    .toLowerCase()
    .trim()
    .replace(/[^\w\s-]/g, '') // Remove special characters
    .replace(/[\s_-]+/g, '-') // Replace spaces and underscores with hyphens
    .replace(/^-+|-+$/g, ''); // Remove leading/trailing hyphens
}

// Aggiungi all'export
module.exports = {
  capitalize,
  toCamelCase,
  truncate,
  reverse,
  toSlug
};
```

**Test per `toSlug`**:
```javascript
describe('toSlug', () => {
  test('should convert to URL-friendly slug', () => {
    expect(toSlug('Hello World!')).toBe('hello-world');
    expect(toSlug('Test & Example')).toBe('test-example');
    expect(toSlug('  Multiple   Spaces  ')).toBe('multiple-spaces');
  });

  test('should handle edge cases', () => {
    expect(toSlug('')).toBe('');
    expect(toSlug('---test---')).toBe('test');
  });
});
```

```bash
# Test e commit
npm test
git add .
git commit -m "feat: add toSlug function for URL-friendly strings

- Add toSlug() function to convert strings to URL slugs
- Handle special characters, spaces, and edge cases
- Add comprehensive tests for slug functionality"

git push origin feature/slug-function
```

### 6.2 Minor Release

```bash
# Merge in main
git checkout main
git merge feature/slug-function

# Minor version bump
npm version minor --no-git-tag-version

# Aggiorna documentazione e changelog
```

**Aggiorna README.md con nuova funzione**:
```markdown
### toSlug(str)
Converts a string to a URL-friendly slug.

```javascript
console.log(toSlug('Hello World!')); // "hello-world"
```
```

```bash
# Release commit
git add .
git commit -m "chore(release): v1.1.0

- Add toSlug function for URL-friendly string conversion
- Update documentation with new function
- Update changelog"

# Tag e push
git tag -a v1.1.0 -m "Release v1.1.0 - Add toSlug function"
git push origin main v1.1.0
```

## Parte 7: Automation Setup

### 7.1 GitHub Actions per Release

**`.github/workflows/release.yml`**:
```yaml
name: Release

on:
  push:
    tags:
      - 'v*'

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run tests
        run: npm test
      
      - name: Run linting
        run: npm run lint

  publish:
    needs: test
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      
      - name: Setup Node.js
        uses: actions/setup-node@v4
        with:
          node-version: '18'
          registry-url: 'https://registry.npmjs.org'
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Publish to npm
        run: npm publish
        env:
          NODE_AUTH_TOKEN: ${{ secrets.NPM_TOKEN }}
      
      - name: Create GitHub Release
        uses: actions/create-release@v1
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
        with:
          tag_name: ${{ github.ref }}
          release_name: Release ${{ github.ref }}
          body: |
            Release notes for ${{ github.ref }}
            
            See [CHANGELOG.md](https://github.com/${{ github.repository }}/blob/main/CHANGELOG.md) for details.
          draft: false
          prerelease: false
```

### 7.2 Automated Testing

**`.github/workflows/test.yml`**:
```yaml
name: Test

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main, develop ]

jobs:
  test:
    runs-on: ubuntu-latest
    
    strategy:
      matrix:
        node-version: [16, 18, 20]
    
    steps:
      - uses: actions/checkout@v4
      
      - name: Use Node.js ${{ matrix.node-version }}
        uses: actions/setup-node@v4
        with:
          node-version: ${{ matrix.node-version }}
          cache: 'npm'
      
      - name: Install dependencies
        run: npm ci
      
      - name: Run linting
        run: npm run lint
      
      - name: Run tests
        run: npm test
      
      - name: Upload coverage
        uses: codecov/codecov-action@v3
        if: matrix.node-version == '18'
```

## 📝 Verifica e Riflessione

### ✅ Checklist Completamento

- [ ] Progetto inizializzato con package.json
- [ ] Codice base implementato con test
- [ ] Conventional commits utilizzati
- [ ] Changelog mantenuto aggiornato
- [ ] Tag Git creati correttamente
- [ ] Release GitHub create
- [ ] Workflow automatizzato configurato
- [ ] Versioning semantico applicato

### 🤔 Domande di Riflessione

1. **Quando creeresti una release MAJOR vs MINOR vs PATCH?**
2. **Come gestiresti un bug critico in produzione?**
3. **Quali informazioni includeresti sempre nelle release notes?**
4. **Come organizzeresti i branch per supportare più versioni?**

### 📈 Prossimi Passi

1. **Implementa pre-release** (alpha, beta, rc)
2. **Aggiungi TypeScript definitions**
3. **Setup deployment automatizzato**
4. **Implementa feature flags**
5. **Aggiungi metriche di utilizzo**

Questo esercizio ti ha guidato attraverso un workflow completo di release professionale. Hai imparato a gestire versioning, tag, documentazione e automazione - competenze essenziali per qualsiasi progetto software serio.
