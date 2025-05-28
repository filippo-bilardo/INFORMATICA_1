# Introduzione ai Tag Git

## 📖 Cos'è un Tag Git

Un **tag** in Git è un riferimento immutabile a uno specifico commit che viene utilizzato per marcare punti importanti nella cronologia del progetto, tipicamente per identificare versioni rilasciate del software.

### Differenza tra Tag e Branch

| Aspetto | Tag | Branch |
|---------|-----|--------|
| **Mutabilità** | Immutabile | Mutabile |
| **Scopo** | Marcare versioni/milestone | Sviluppo parallelo |
| **Movimento** | Fisso su un commit | Si muove con nuovi commit |
| **Durata** | Permanente | Può essere eliminato |

## 🏷️ Tipi di Tag

### 1. Lightweight Tags
Tag semplici che puntano direttamente a un commit:

```bash
# Crea lightweight tag
git tag v1.0.0

# Tag su commit specifico
git tag v1.0.0 abc123
```

### 2. Annotated Tags
Tag completi con metadati aggiuntivi:

```bash
# Crea annotated tag
git tag -a v1.0.0 -m "Release version 1.0.0"

# Con editor per messaggio lungo
git tag -a v1.0.0

# Su commit specifico
git tag -a v1.0.0 abc123 -m "Release version 1.0.0"
```

### Differenze tra i Tipi

```bash
# Visualizza dettagli tag
git show v1.0.0

# Lightweight tag mostra: solo il commit
# Annotated tag mostra: tagger, data, messaggio, firma GPG
```

## 📋 Semantic Versioning

### Formato Standard: MAJOR.MINOR.PATCH

- **MAJOR**: Cambiamenti incompatibili all'API
- **MINOR**: Nuove funzionalità backward-compatible  
- **PATCH**: Bug fix backward-compatible

### Esempi Pratici

```bash
# Prima release
git tag -a v1.0.0 -m "Initial stable release"

# Bug fix
git tag -a v1.0.1 -m "Fix critical authentication bug"

# Nuova feature
git tag -a v1.1.0 -m "Add user profile management"

# Breaking change
git tag -a v2.0.0 -m "Redesigned API with new authentication system"
```

### Versioni Pre-release

```bash
# Alpha version
git tag -a v1.0.0-alpha.1 -m "First alpha release"

# Beta version
git tag -a v1.0.0-beta.2 -m "Second beta release"

# Release candidate
git tag -a v1.0.0-rc.1 -m "First release candidate"
```

## 🔍 Gestione Tag

### Visualizzazione Tag

```bash
# Lista tutti i tag
git tag

# Lista con pattern
git tag -l "v1.*"

# Mostra tag con dettagli
git tag -n

# Mostra commit di un tag
git show v1.0.0
```

### Navigazione con Tag

```bash
# Checkout su tag specifico
git checkout v1.0.0

# Crea branch da tag
git checkout -b hotfix/v1.0.1 v1.0.0

# Differenze tra tag
git diff v1.0.0 v1.1.0
```

### Modifica Tag

```bash
# Sposta tag (sconsigliato se pubblico)
git tag -f v1.0.0 new-commit-hash

# Elimina tag locale
git tag -d v1.0.0

# Elimina tag remoto
git push origin --delete v1.0.0
```

## 🌐 Tag Remoti

### Push Tag

```bash
# Push singolo tag
git push origin v1.0.0

# Push tutti i tag
git push origin --tags

# Push solo annotated tags
git push origin --follow-tags
```

### Fetch Tag

```bash
# Fetch automatico con pull
git pull

# Fetch esplicito tag
git fetch --tags

# Fetch tag specifico
git fetch origin refs/tags/v1.0.0:refs/tags/v1.0.0
```

## 🛠️ Workflow Tag Professionali

### 1. Release Workflow

```bash
# 1. Finalizza feature branch
git checkout develop
git merge --no-ff feature/new-feature

# 2. Crea release branch
git checkout -b release/v1.1.0

# 3. Update version in files
echo "1.1.0" > VERSION
git add VERSION
git commit -m "Bump version to 1.1.0"

# 4. Merge to main
git checkout main
git merge --no-ff release/v1.1.0

# 5. Crea tag
git tag -a v1.1.0 -m "Release version 1.1.0

Features:
- User authentication
- Profile management
- Settings panel

Bug fixes:
- Fixed login timeout
- Resolved CSS issues"

# 6. Push everything
git push origin main --tags
```

### 2. Hotfix Workflow

```bash
# 1. Crea hotfix da ultimo tag
git checkout -b hotfix/v1.0.1 v1.0.0

# 2. Fix the bug
git add .
git commit -m "Fix critical security vulnerability"

# 3. Merge to main
git checkout main
git merge --no-ff hotfix/v1.0.1

# 4. Crea tag patch
git tag -a v1.0.1 -m "Hotfix v1.0.1 - Security vulnerability fix"

# 5. Merge back to develop
git checkout develop
git merge --no-ff hotfix/v1.0.1

# 6. Push
git push origin main develop --tags
```

## 🔒 Tag Signing

### Setup GPG per Firma

```bash
# Genera chiave GPG
gpg --generate-key

# Configura Git per usare GPG
git config --global user.signingkey YOUR_KEY_ID
git config --global tag.gpgSign true

# Crea tag firmato
git tag -s v1.0.0 -m "Signed release v1.0.0"

# Verifica firma
git tag -v v1.0.0
```

## 📊 Best Practices

### ✅ Cosa Fare

1. **Usa semantic versioning** - Standard riconosciuto universalmente
2. **Annota sempre i tag** - Metadati utili per tracciabilità
3. **Messaggi descrittivi** - Include changelog nel messaggio tag
4. **Tag su main/master** - Evita tag su branch di sviluppo
5. **Testa prima del tag** - CI/CD deve passare
6. **Firma tag di release** - Sicurezza e integrità

### ❌ Cosa Evitare

1. **Non spostare tag pubblici** - Confonde altri sviluppatori
2. **Non tag su commit instabili** - Solo su versioni testate
3. **Non tag troppo frequenti** - Noise nel versioning
4. **Non tag senza documentazione** - Sempre include release notes
5. **Non eliminare tag di produzione** - Storico importante

## 🎯 Quiz di Autovalutazione

1. **Qual è la differenza principale tra lightweight e annotated tag?**
   - a) Lightweight tag sono più veloci
   - b) Annotated tag contengono metadati aggiuntivi
   - c) Lightweight tag sono più sicuri
   - d) Non c'è differenza

2. **In semantic versioning, quando incrementi la versione MAJOR?**
   - a) Per ogni nuovo commit
   - b) Per bug fix
   - c) Per nuove funzionalità
   - d) Per breaking changes

3. **Quale comando elimina un tag remoto?**
   - a) `git tag -d v1.0.0`
   - b) `git push origin --delete v1.0.0`
   - c) `git remote delete v1.0.0`
   - d) `git tag --remove v1.0.0`

**Risposte: 1-b, 2-d, 3-b**

## 🎯 Esercizi Pratici

### Esercizio 1: Tag di Base
1. Crea un repository di test
2. Fai alcuni commit
3. Crea un lightweight tag `v0.1.0`
4. Crea un annotated tag `v0.2.0` con messaggio
5. Visualizza entrambi i tag con `git show`

### Esercizio 2: Semantic Versioning
1. Simula 3 bug fix (tag v1.0.1, v1.0.2, v1.0.3)
2. Aggiungi nuova feature (tag v1.1.0)
3. Implementa breaking change (tag v2.0.0)
4. Crea pre-release alpha (tag v2.1.0-alpha.1)

### Esercizio 3: Workflow Release
1. Implementa il workflow completo di release
2. Crea release branch
3. Merge su main con tag
4. Simula hotfix con nuovo tag patch

---

## 📖 Letture Approfondimento

- [Git Tagging Documentation](https://git-scm.com/book/en/v2/Git-Basics-Tagging)
- [Semantic Versioning Specification](https://semver.org/)
- [GPG Signing Tags](https://git-scm.com/book/en/v2/Git-Tools-Signing-Your-Work)

## Navigazione del Corso

- [📑 Indice](../README.md)
- [⬅️ Git Flow e Strategie](../../23-Git-Flow-e-Strategie/README.md)
- [➡️ Tag Release GitHub](./02-github-releases.md)
