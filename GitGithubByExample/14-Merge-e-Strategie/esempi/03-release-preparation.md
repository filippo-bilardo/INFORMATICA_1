# Esempio: Preparazione di una Release

## Scenario
Sei il lead developer di un progetto e devi preparare la release v2.1.0 che include diverse feature completate nel corso dell'ultimo sprint.

## Obiettivo
Imparare il processo di preparazione di una release attraverso merge strategici e testing.

## Setup Iniziale

```bash
# Clona il repository di esempio
git clone https://github.com/example/project-release.git
cd project-release

# Verifica i branch disponibili
git branch -a
```

## Struttura Branch

```
main (v2.0.0)
├── develop
├── feature/user-authentication
├── feature/payment-gateway
├── feature/notification-system
└── release/v2.1.0 (da creare)
```

## Processo di Release

### 1. Creazione Branch di Release

```bash
# Crea branch di release da develop
git checkout develop
git pull origin develop
git checkout -b release/v2.1.0

# Push del branch di release
git push -u origin release/v2.1.0
```

### 2. Merge delle Feature

```bash
# Merge feature completate
git merge feature/user-authentication
git merge feature/payment-gateway
git merge feature/notification-system
```

### 3. Testing e Stabilizzazione

```bash
# Esegui test completi
npm test
npm run e2e-test

# Fix eventuali bug minori
git add .
git commit -m "fix: minor bugs found during release testing"
```

### 4. Aggiornamento Versione

```bash
# Aggiorna package.json
echo '{"version": "2.1.0"}' > version.json
git add version.json
git commit -m "bump: version to 2.1.0"
```

### 5. Merge in Main

```bash
# Torna a main e merge
git checkout main
git pull origin main
git merge --no-ff release/v2.1.0 -m "release: version 2.1.0"

# Tag della release
git tag -a v2.1.0 -m "Release version 2.1.0

Features:
- User authentication system
- Payment gateway integration
- Notification system

Bug fixes:
- Fixed login validation
- Improved error handling"

# Push changes e tag
git push origin main
git push origin v2.1.0
```

### 6. Backmerge in Develop

```bash
# Aggiorna develop con le modifiche di release
git checkout develop
git merge main
git push origin develop
```

### 7. Cleanup

```bash
# Elimina branch di release locale e remoto
git branch -d release/v2.1.0
git push origin --delete release/v2.1.0
```

## Checklist Release

- [ ] Tutte le feature sono state testate
- [ ] Documentazione aggiornata
- [ ] Changelog creato
- [ ] Versione aggiornata
- [ ] Test di regressione passati
- [ ] Build di produzione funzionante
- [ ] Tag creato con messaggio descrittivo
- [ ] Branch di release pulito

## Best Practices

### Preparazione
- Congela le feature 1-2 giorni prima
- Pianifica tempo per testing approfondito
- Documenta breaking changes

### Testing
- Esegui test automatizzati
- Test manuali su staging
- Performance testing
- Security scanning

### Comunicazione
- Notifica il team della release
- Aggiorna stakeholder
- Prepara note di release

## Script di Automazione

```bash
#!/bin/bash
# release-prep.sh

VERSION=$1
if [ -z "$VERSION" ]; then
    echo "Usage: ./release-prep.sh <version>"
    exit 1
fi

echo "🚀 Preparing release $VERSION"

# Crea branch di release
git checkout develop
git pull origin develop
git checkout -b "release/$VERSION"

# Aggiorna versione
echo "{\"version\": \"$VERSION\"}" > version.json
git add version.json
git commit -m "bump: version to $VERSION"

# Push branch
git push -u origin "release/$VERSION"

echo "✅ Release branch created: release/$VERSION"
echo "📝 Next steps:"
echo "  1. Run tests: npm test"
echo "  2. Fix any issues"
echo "  3. Merge to main when ready"
```

## Troubleshooting

### Conflitti durante il Merge
```bash
# Se ci sono conflitti
git status
# Risolvi manualmente i conflitti
git add .
git commit -m "resolve: merge conflicts in release preparation"
```

### Rollback di Release
```bash
# Se necessario annullare
git reset --hard HEAD~1
git push --force-with-lease origin release/v2.1.0
```

## Risorse Aggiuntive

- [Semantic Versioning](https://semver.org/)
- [Git Flow Release Process](https://git-flow.readthedocs.io/)
- [Conventional Commits](https://conventionalcommits.org/)

## Prossimi Passi

1. Pratica con [Esercizio Merge Workflow](../esercizi/01-merge-workflow.md)
2. Studia [Strategy Selection](../esercizi/02-strategy-selection.md)
3. Approfondisci [Complex Integration](../esercizi/03-complex-integration.md)
