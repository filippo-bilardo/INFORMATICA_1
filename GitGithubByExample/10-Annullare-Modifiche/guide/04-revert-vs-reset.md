# Revert vs Reset: Quando Usare Cosa

## 📚 Obiettivi
- Comprendere le differenze fondamentali tra `git revert` e `git reset`
- Saper scegliere l'approccio corretto per ogni situazione
- Padroneggiare l'uso sicuro di entrambi i comandi
- Comprendere l'impatto su repository condivisi

## 🔄 Concetti Fondamentali

### Git Reset: "Riscrive la Storia"
- **Modifica** la cronologia dei commit
- **Rimuove** commit dalla storia
- **Pericoloso** su repository condivisi
- **Ideale** per correzioni locali

### Git Revert: "Aggiunge alla Storia"
- **Preserva** la cronologia dei commit
- **Crea** nuovi commit per annullare modifiche
- **Sicuro** su repository condivisi
- **Ideale** per collaborazione

## ⚖️ Matrice Decisionale

| Situazione | Reset | Revert | Motivazione |
|------------|-------|--------|-------------|
| Repository locale privato | ✅ | ✅ | Entrambi sicuri |
| Repository condiviso/pubblico | ❌ | ✅ | Reset rompe la storia |
| Commit non ancora pushati | ✅ | ✅ | Reset più semplice |
| Commit già pushati | ❌ | ✅ | Reset richiederebbe force push |
| Ultimo commit | ✅ | ✅ | Reset più veloce |
| Commit nel mezzo | ❌ | ✅ | Reset complica la storia |
| Correzione urgente | ❌ | ✅ | Revert più sicuro |

## 🔄 Git Reset - Riscrivere la Storia

### Sintassi Base
```bash
git reset [--soft|--mixed|--hard] <commit>
```

### Scenari di Uso

#### 1. Annullare Ultimo Commit (Locale)
```bash
# Mantieni modifiche nell'area di staging
git reset --soft HEAD~1

# Mantieni modifiche nella working directory
git reset --mixed HEAD~1  # default

# Rimuovi tutto completamente
git reset --hard HEAD~1
```

#### 2. Tornare a un Commit Specifico
```bash
# Vedere la storia
git log --oneline

# Tornare indietro (ATTENZIONE!)
git reset --hard abc123f
```

#### 3. Reset di File Specifici
```bash
# Reset di un file dal HEAD
git reset HEAD file.txt

# Reset di un file da commit specifico
git reset abc123f -- file.txt
```

### ⚠️ Problemi con Reset su Repository Condivisi

```bash
# ❌ PERICOLOSO - Non fare mai questo!
git reset --hard HEAD~3
git push --force-with-lease origin main
```

**Conseguenze:**
- Altri sviluppatori perdono commit
- Divergenza delle storie
- Conflitti complessi da risolvere

## ↩️ Git Revert - Aggiungere alla Storia

### Sintassi Base
```bash
git revert <commit>
git revert <commit1>..<commit2>
git revert --no-commit <commit>
```

### Scenari di Uso

#### 1. Revert di Singolo Commit
```bash
# Revert automatico con commit
git revert abc123f

# Revert senza commit automatico
git revert --no-commit abc123f
git commit -m "Revert feature X: causava bug Y"
```

#### 2. Revert di Range di Commit
```bash
# Revert multipli commit
git revert HEAD~3..HEAD

# Revert con merge commit
git revert -m 1 merge_commit_hash
```

#### 3. Revert Interattivo
```bash
# Revert con editing del messaggio
git revert --edit abc123f

# Revert senza aprire editor
git revert --no-edit abc123f
```

## 🛡️ Strategie Sicure

### Per Repository Privati
```bash
# Puoi usare reset liberamente
git reset --hard HEAD~2
git reset --soft origin/main
```

### Per Repository Condivisi
```bash
# Usa sempre revert
git revert HEAD
git revert abc123f
git push origin main
```

### Workflow Ibrido
```bash
# 1. Reset locale per "pulire"
git reset --soft HEAD~3
git commit -m "Refactor: consolidate changes"

# 2. Push del commit consolidato
git push origin feature-branch
```

## 🔧 Esempi Pratici

### Scenario 1: Correzione Bug Urgente
```bash
# Situazione: bug in produzione da commit recente
git log --oneline
# a1b2c3d Fix login validation
# e4f5g6h Add new feature
# h7i8j9k Update dependencies

# ✅ Soluzione sicura con revert
git revert a1b2c3d
git push origin main

# Risultato: nuovo commit che annulla a1b2c3d
```

### Scenario 2: Rimozione Feature Completa
```bash
# Feature implementata in 3 commit
git log --oneline
# a1b2c3d Feature: final touches
# e4f5g6h Feature: main logic
# h7i8j9k Feature: initial setup

# ✅ Revert dell'intera feature
git revert a1b2c3d e4f5g6h h7i8j9k
# O usando range
git revert HEAD~2..HEAD
```

### Scenario 3: Reset Locale Prima del Push
```bash
# Commit locali non ancora pushati
git log --oneline
# a1b2c3d WIP: debugging
# e4f5g6h WIP: temp changes
# h7i8j9k Last good commit

# ✅ Reset sicuro (locale)
git reset --hard h7i8j9k
# Ricomincia da commit pulito
```

## 🆘 Recovery e Troubleshooting

### Recupero da Reset Accidentale
```bash
# Vedere il reflog
git reflog

# Tornare al commit precedente
git reset --hard HEAD@{1}
```

### Gestione Conflitti in Revert
```bash
# Se revert ha conflitti
git revert abc123f
# CONFLICT: Risolvi manualmente

# Dopo risoluzione
git add .
git revert --continue
```

### Reset vs Revert: Cleanup
```bash
# Reset: pulizia locale completa
git reset --hard origin/main
git clean -fd

# Revert: mantenere storia
git revert --no-commit HEAD~3..HEAD
git commit -m "Revert multiple problematic changes"
```

## 📋 Checklist Decisionale

Prima di scegliere tra reset e revert, chiediti:

- [ ] I commit sono già stati pushati?
- [ ] Altri sviluppatori hanno basato lavoro su questi commit?
- [ ] È un repository pubblico/condiviso?
- [ ] È necessario mantenere audit trail?
- [ ] È una correzione urgente?
- [ ] Ci sono dipendenze downstream?

## 🎯 Best Practices

### Reset Guidelines
- ✅ Usa su repository locali privati
- ✅ Prima del primo push
- ✅ Per consolidare commit WIP
- ❌ Mai su repository condivisi
- ❌ Mai con `--force` senza `--force-with-lease`

### Revert Guidelines
- ✅ Sempre per repository condivisi
- ✅ Per correzioni urgenti
- ✅ Quando serve audit trail
- ✅ Per annullare merge problematici
- ⚠️ Attenzione a conflitti complessi

## 🧪 Esercizio Pratico

1. **Crea scenario di test:**
   ```bash
   git init test-revert-reset
   cd test-revert-reset
   
   # Crea alcuni commit
   echo "Initial" > file.txt && git add . && git commit -m "Initial"
   echo "Feature A" >> file.txt && git add . && git commit -m "Add feature A"
   echo "Feature B" >> file.txt && git add . && git commit -m "Add feature B"
   echo "Bug fix" >> file.txt && git add . && git commit -m "Fix bug"
   ```

2. **Sperimenta con reset:**
   ```bash
   # Salva stato attuale
   git tag before-reset
   
   # Prova reset
   git reset --hard HEAD~2
   git log --oneline
   
   # Recupera
   git reset --hard before-reset
   ```

3. **Sperimenta con revert:**
   ```bash
   # Revert del fix bug
   git revert HEAD
   git log --oneline
   
   # Nota: storia preservata
   ```

## 📊 Riepilogo Visivo

```
RESET (Riscrive Storia):
A---B---C---D (HEAD)
        ↓ reset --hard B
A---B (HEAD)
# C e D spariscono dalla storia

REVERT (Aggiunge Storia):
A---B---C---D (HEAD)
        ↓ revert C
A---B---C---D---E (HEAD)
# E annulla le modifiche di C
```

La scelta tra reset e revert è fondamentale per la collaborazione sicura. Quando in dubbio, **scegli sempre revert** per repository condivisi!
