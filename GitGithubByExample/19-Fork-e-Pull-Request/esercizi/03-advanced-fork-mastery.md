# Esercizio 03 - Mastery: Fork e Pull Request Avanzato

## 🎯 Obiettivo

Padroneggiare **tecniche avanzate** di Fork e Pull Request attraverso scenari complessi che includono conflitti, sincronizzazione upstream, gestione di multiple PR e best practices per progetti enterprise.

## 📋 Requisiti Tecnici

- **Git installato** e configurato
- **Account GitHub** attivo
- **Esperienza con Fork & PR** di base
- **Conoscenza rebase** e conflict resolution
- **Editor di codice** preferito

## ⏱️ Durata Stimata

**180-240 minuti** (scenari complessi + best practices)

## 🎬 Scenario dell'Esercizio

Contribuirai a un **progetto open source enterprise** con policy rigide, dovrai gestire fork complessi, sincronizzazioni upstream frequenti, e navigare attraverso processi di review avanzati.

## 🏗️ Fase 1: Setup Progetto Enterprise (45 min)

### Step 1: Fork Progetto Target

```bash
# 1. Vai su GitHub e trova un repository con queste caratteristiche:
# - Progetto attivo con commit recenti
# - Branch protection abilitata
# - Workflow CI/CD configurati
# - Pull request template
# - Contributing guidelines

# Esempio di repository enterprise-ready (cercane uno simile):
# https://github.com/microsoft/vscode
# https://github.com/facebook/react
# https://github.com/kubernetes/kubernetes

# 2. Fai Fork del repository selezionato
```

### Step 2: Clone e Setup Development Environment

```bash
# 1. Clona il tuo fork
git clone https://github.com/YOUR_USERNAME/FORKED_REPO.git
cd FORKED_REPO

# 2. Aggiungi upstream remote
git remote add upstream https://github.com/ORIGINAL_OWNER/ORIGINAL_REPO.git

# 3. Verifica remotes
git remote -v
# origin    https://github.com/YOUR_USERNAME/FORKED_REPO.git (fetch)
# origin    https://github.com/YOUR_USERNAME/FORKED_REPO.git (push)
# upstream  https://github.com/ORIGINAL_OWNER/ORIGINAL_REPO.git (fetch)
# upstream  https://github.com/ORIGINAL_OWNER/ORIGINAL_REPO.git (push)

# 4. Sync con upstream
git fetch upstream
git checkout main
git merge upstream/main
git push origin main
```

### Step 3: Setup Development Tools

```bash
# 1. Installa dipendenze se necessario
npm install  # o yarn install, pip install -r requirements.txt, etc.

# 2. Esegui tests per verificare environment
npm test  # o python -m pytest, go test, etc.

# 3. Verifica linting
npm run lint  # o flake8, golangci-lint, etc.

# 4. Leggi CONTRIBUTING.md e documenti di policy
```

## 🔄 Fase 2: Workflow Avanzato Multi-Branch (60 min)

### Step 4: Sviluppo Feature Complessa

```bash
# 1. Crea feature branch
git checkout -b feature/advanced-search-api

# 2. Implementa cambiamenti in multiple files
# Simula una feature che tocca:
# - Backend API
# - Frontend UI
# - Tests
# - Documentation
# - Configuration

# Esempio: Advanced Search API
```

**File: `src/api/search.js`** (crea se non esiste)
```javascript
/**
 * Advanced Search API Implementation
 * Supports multiple filters and sorting options
 */
class AdvancedSearch {
    constructor(options = {}) {
        this.filters = options.filters || {};
        this.sortBy = options.sortBy || 'relevance';
        this.limit = options.limit || 50;
    }

    async search(query, options = {}) {
        const mergedOptions = { ...this.filters, ...options };
        
        try {
            const results = await this.executeSearch(query, mergedOptions);
            return this.formatResults(results);
        } catch (error) {
            console.error('Search failed:', error);
            throw new Error(`Search operation failed: ${error.message}`);
        }
    }

    async executeSearch(query, options) {
        // Implementation would connect to actual search service
        return {
            query,
            options,
            results: [],
            total: 0,
            timestamp: new Date().toISOString()
        };
    }

    formatResults(rawResults) {
        return {
            ...rawResults,
            formattedResults: rawResults.results.map(result => ({
                ...result,
                relevanceScore: this.calculateRelevance(result)
            }))
        };
    }

    calculateRelevance(result) {
        // Advanced relevance calculation
        return Math.random(); // Placeholder
    }
}

module.exports = AdvancedSearch;
```

**File: `tests/search.test.js`** (crea se non esiste)
```javascript
const AdvancedSearch = require('../src/api/search');

describe('AdvancedSearch', () => {
    let searchEngine;

    beforeEach(() => {
        searchEngine = new AdvancedSearch({
            filters: { type: 'document' },
            limit: 25
        });
    });

    test('should initialize with default options', () => {
        const defaultSearch = new AdvancedSearch();
        expect(defaultSearch.limit).toBe(50);
        expect(defaultSearch.sortBy).toBe('relevance');
    });

    test('should perform search with query', async () => {
        const results = await searchEngine.search('test query');
        
        expect(results).toHaveProperty('query', 'test query');
        expect(results).toHaveProperty('total');
        expect(results).toHaveProperty('formattedResults');
    });

    test('should handle search errors gracefully', async () => {
        // Mock error scenario
        searchEngine.executeSearch = jest.fn().mockRejectedValue(new Error('Network error'));
        
        await expect(searchEngine.search('test')).rejects.toThrow('Search operation failed');
    });
});
```

**File: `docs/ADVANCED_SEARCH.md`** (crea se non esiste)
```markdown
# Advanced Search API

## Overview

The Advanced Search API provides sophisticated search capabilities with multiple filtering and sorting options.

## Features

- Multi-criteria filtering
- Relevance-based sorting
- Error handling and resilience
- Configurable result limits
- Real-time search suggestions

## Usage

```javascript
const AdvancedSearch = require('./src/api/search');

const searchEngine = new AdvancedSearch({
    filters: { category: 'tech' },
    sortBy: 'date',
    limit: 100
});

const results = await searchEngine.search('machine learning');
```

## API Reference

### Constructor Options

- `filters`: Object with default filter criteria
- `sortBy`: Default sorting method ('relevance', 'date', 'title')
- `limit`: Maximum number of results to return

### Methods

#### `search(query, options)`

Performs search with given query and optional filters.

**Parameters:**
- `query` (string): Search query
- `options` (object): Additional search options

**Returns:** Promise resolving to search results object

## Error Handling

The API provides comprehensive error handling for network issues, invalid queries, and service timeouts.
```

### Step 5: Commit Strategico

```bash
# 1. Stage changes
git add src/api/search.js
git commit -m "feat: implement advanced search API core functionality

- Add AdvancedSearch class with configurable options
- Implement search method with error handling
- Add relevance calculation algorithm
- Support for multiple filter types"

git add tests/search.test.js
git commit -m "test: add comprehensive test suite for advanced search

- Cover initialization scenarios
- Test search functionality
- Add error handling validation
- Ensure proper mock behavior"

git add docs/ADVANCED_SEARCH.md
git commit -m "docs: add advanced search API documentation

- Include usage examples
- Document configuration options
- Add API reference section
- Cover error handling guidelines"
```

## 🚀 Fase 3: Gestione Conflitti e Sincronizzazione (45 min)

### Step 6: Sync con Upstream Durante Sviluppo

```bash
# 1. Simula che upstream abbia ricevuto updates
git fetch upstream

# 2. Controlla differenze
git log HEAD..upstream/main --oneline

# 3. Rebase sulla versione più recente
git checkout main
git merge upstream/main
git push origin main

# 4. Rebase feature branch
git checkout feature/advanced-search-api
git rebase main

# Se ci sono conflitti, risolvili file per file:
# 1. Edita files conflittuali
# 2. git add file_risolto
# 3. git rebase --continue
```

### Step 7: Gestione Conflitti Complessi

Simula un conflitto modificando lo stesso file da direzioni diverse:

```bash
# 1. Crea cambiamento conflittuale nel main
git checkout main
echo "// Main branch change" >> src/api/search.js
git add -A
git commit -m "main: add main branch modification"

# 2. Torna al feature branch
git checkout feature/advanced-search-api
echo "// Feature branch change" >> src/api/search.js
git add -A
git commit -m "feat: add feature branch modification"

# 3. Tenta rebase (causerà conflitto)
git rebase main

# 4. Risolvi conflitto manualmente
# Modifica src/api/search.js per unire entrambi i cambiamenti

# 5. Continua rebase
git add src/api/search.js
git rebase --continue
```

## 📝 Fase 4: Pull Request Enterprise (60 min)

### Step 8: Preparazione PR Professionale

```bash
# 1. Push feature branch
git push origin feature/advanced-search-api

# 2. Va su GitHub e crea Pull Request con:
```

**Titolo PR:**
```
feat: Implement Advanced Search API with Multi-Criteria Filtering
```

**Descrizione PR:**
```markdown
## 🎯 Overview

This PR introduces a comprehensive Advanced Search API that provides sophisticated search capabilities with configurable filtering, sorting, and error handling.

## 🚀 Changes

### New Features
- ✅ `AdvancedSearch` class with configurable options
- ✅ Multi-criteria filtering system
- ✅ Relevance-based sorting algorithm
- ✅ Configurable result limits
- ✅ Comprehensive error handling

### Files Added/Modified
- `src/api/search.js` - Core API implementation
- `tests/search.test.js` - Comprehensive test suite
- `docs/ADVANCED_SEARCH.md` - API documentation

## 🧪 Testing

- [ ] Unit tests passing
- [ ] Integration tests verified
- [ ] Performance benchmarks completed
- [ ] Error scenarios validated

## 📚 Documentation

- [ ] API documentation updated
- [ ] Usage examples provided
- [ ] Error handling documented
- [ ] Configuration options explained

## 🔄 Breaking Changes

None. This is a new feature that doesn't affect existing functionality.

## 🎯 Migration Guide

No migration required. New API is optional and doesn't replace existing functionality.

## 📋 Checklist

- [x] Code follows project style guidelines
- [x] Self-review completed
- [x] Tests added for new functionality
- [x] Documentation updated
- [ ] Reviewed by team lead
- [ ] Security review completed (if applicable)

## 🔗 Related Issues

Closes #123 (if applicable)
Related to #456 (if applicable)

## 📱 Screenshots/Demo

(Include screenshots or demo GIFs if UI changes)

## 🚨 Notes for Reviewers

Please pay special attention to:
1. Error handling in `executeSearch` method
2. Performance implications of relevance calculation
3. Test coverage for edge cases
```

### Step 9: Gestione Review Cycle

```bash
# 1. Simula feedback del reviewer
# Aggiungi un file di risposta alle review

# 2. Crea nuovo commit per addressing feedback
echo "// Added input validation as requested in review" >> src/api/search.js
git add -A
git commit -m "refactor: add input validation based on code review feedback

- Add query string validation
- Implement options parameter sanitization
- Improve error messages clarity"

# 3. Push aggiornamenti
git push origin feature/advanced-search-api

# 4. Squash commits per clean history (se richiesto dal progetto)
git rebase -i HEAD~4  # Interactive rebase per combinare commits
```

## 🔄 Fase 5: Workflow Avanzato Post-Merge (30 min)

### Step 10: Cleanup Post-Merge

```bash
# 1. Simula merge della PR (dopo approval)
git checkout main
git pull upstream main  # Ora include la tua feature

# 2. Cleanup locale
git branch -d feature/advanced-search-api
git push origin --delete feature/advanced-search-api

# 3. Update fork
git push origin main
```

### Step 11: Preparazione Prossimo Contributo

```bash
# 1. Identifica issue successivo
# Cerca un "good first issue" o "help wanted"

# 2. Crea nuovo branch per prossima feature
git checkout -b feature/search-autocomplete

# 3. Mantieni sincronizzazione costante
git fetch upstream
git rebase upstream/main
```

## 🏆 Fase 6: Best Practices Avanzate (20 min)

### Step 12: Documentazione Best Practices

Crea un file con le best practices apprese:

**File: `FORK_BEST_PRACTICES.md`**
```markdown
# Fork & Pull Request Best Practices

## Pre-Development
1. Always sync with upstream before starting new work
2. Read CONTRIBUTING.md and project guidelines
3. Check existing issues and PRs to avoid duplicates
4. Set up proper development environment

## During Development
1. Use descriptive branch names: feature/issue-123-advanced-search
2. Make atomic commits with clear messages
3. Follow conventional commit format
4. Keep commits focused and single-purpose
5. Regularly sync with upstream to avoid conflicts

## Pull Request Preparation
1. Squash commits if project requires clean history
2. Write comprehensive PR description
3. Include tests and documentation
4. Self-review all changes before submitting
5. Ensure CI/CD passes locally

## Code Review Process
1. Respond promptly to review feedback
2. Ask questions if feedback is unclear
3. Make requested changes in separate commits
4. Re-request review after addressing feedback
5. Be respectful and professional in discussions

## Post-Merge Cleanup
1. Delete feature branches after merge
2. Update local main branch
3. Sync fork with upstream
4. Plan next contribution

## Common Pitfalls to Avoid
- Don't develop directly on main branch
- Don't force push to shared branches
- Don't ignore CI/CD failures
- Don't submit massive PRs without discussion
- Don't take review feedback personally
```

## ✅ Verifica Completamento

### Checklist Finale

- [ ] **Fork Setup**: Repository forkato e remotes configurati
- [ ] **Development Environment**: Tools installati e funzionanti
- [ ] **Feature Development**: Feature complessa implementata con test
- [ ] **Conflict Resolution**: Conflitti risolti durante rebase
- [ ] **Professional PR**: PR con descrizione completa e professionale
- [ ] **Review Cycle**: Feedback processato e cambiamenti implementati
- [ ] **Post-Merge Cleanup**: Branch puliti e fork sincronizzato
- [ ] **Best Practices**: Documentate lezioni apprese

### Domande di Auto-Valutazione

1. **Workflow Management**: Come gestisci la sincronizzazione con upstream durante sviluppo lungo?
2. **Conflict Resolution**: Quali strategie usi per minimizzare conflitti di merge?
3. **PR Quality**: Come assicuri che le tue PR siano di qualità enterprise?
4. **Code Review**: Come respondi costruttivamente al feedback dei reviewer?
5. **Open Source Contribution**: Quali best practices segui per contributi open source?

## 🎯 Obiettivi Raggiunti

Completando questo esercizio hai sviluppato:

- **Mastery di Fork Workflow** per progetti enterprise
- **Gestione avanzata di conflitti** e sincronizzazione
- **Preparazione di PR professionali** con documentazione completa
- **Navigazione del processo di review** in progetti complessi
- **Best practices per contributi open source** sostenibili

## 🚀 Prossimi Passi

- Applica queste tecniche a progetti open source reali
- Diventa maintainer di un tuo progetto open source
- Contribuisci regolarmente a progetti della community
- Mentorizza altri sviluppatori nel workflow Fork & PR

## 📚 Risorse Aggiuntive

- [GitHub Flow Guide](https://guides.github.com/introduction/flow/)
- [Open Source Contribution Guide](https://opensource.guide/how-to-contribute/)
- [Code Review Best Practices](https://google.github.io/eng-practices/review/)
- [Conventional Commits](https://www.conventionalcommits.org/)
