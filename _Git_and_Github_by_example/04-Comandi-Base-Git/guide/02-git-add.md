# 02 - Git Add e Area di Staging

## 📖 Spiegazione Concettuale

`git add` è il comando che sposta i file dalla **working directory** all'**area di staging** (o index). È il primo passo per creare un commit e ti permette di controllare precisamente quali modifiche includere.

### Concetti Chiave

L'area di staging è come una "zona di preparazione" dove organizzi le modifiche prima di confermarle definitivamente con un commit.

```
Working Directory → [git add] → Staging Area → [git commit] → Repository
```

### Perché Usare l'Area di Staging?

- **Controllo granulare**: Puoi scegliere esattamente quali file includere
- **Commit atomici**: Raggruppa modifiche logicamente correlate
- **Revisione**: Puoi ispezionare cosa stai per committare
- **Flessibilità**: Puoi modificare cosa includere prima del commit

## 🔧 Sintassi e Parametri

### Comando Base
```bash
git add <file>
```

### Varianti Principali

#### 1. Aggiungere File Specifici
```bash
# Singolo file
git add index.html

# Multipli file
git add index.html style.css script.js

# Con percorsi
git add src/main.js docs/README.md
```

#### 2. Aggiungere per Pattern
```bash
# Tutti i file .js
git add *.js

# Tutti i file in una directory
git add src/

# Tutti i file modificati
git add .

# Tutti i file (inclusi quelli eliminati)
git add -A
```

#### 3. Opzioni Avanzate
```bash
# Modalità interattiva
git add -i

# Aggiungere parti di file (patch mode)
git add -p

# Aggiungere tutto (modificati + nuovi + eliminati)
git add -A

# Solo file tracciati modificati
git add -u
```

## 🎯 Esempi Pratici

### Scenario 1: Primo Aggiunta File
```bash
# Stato iniziale
$ git status
On branch main
Untracked files:
  index.html
  style.css

# Aggiungere un file
$ git add index.html

# Verificare risultato
$ git status
On branch main
Changes to be committed:
  new file:   index.html

Untracked files:
  style.css
```

### Scenario 2: Staging Selettivo
```bash
# Hai modificato più file ma vuoi committare solo alcuni
$ git status
On branch main
Changes not staged for commit:
  modified:   header.js
  modified:   footer.js
  modified:   sidebar.js

# Aggiungere solo le modifiche correlate
$ git add header.js footer.js

$ git status
On branch main
Changes to be committed:
  modified:   header.js
  modified:   footer.js

Changes not staged for commit:
  modified:   sidebar.js
```

### Scenario 3: Patch Mode
```bash
# Aggiungere solo parti di un file
$ git add -p utils.js

# Git ti mostrerà ogni "hunk" (blocco di modifiche)
@@ -10,3 +10,7 @@ function calculateTotal(items) {
   return total;
 }
 
+function formatCurrency(amount) {
+  return '$' + amount.toFixed(2);
+}

Stage this hunk [y,n,q,a,d,s,e,?]?
```

## 🎨 Modalità Interattiva

La modalità interattiva (`git add -i`) offre un menu per operazioni avanzate:

```bash
$ git add -i

*** Commands ***
  1: status       2: update       3: revert       4: add untracked
  5: patch        6: diff         7: quit         8: help
What now>
```

### Opzioni del Menu
- **status**: Mostra stato file
- **update**: Aggiorna file tracciati
- **revert**: Rimuove file dal staging
- **add untracked**: Aggiunge file non tracciati
- **patch**: Modalità patch per file specifici
- **diff**: Mostra differenze

## 💡 Best Practices

### 1. Verifica Prima di Aggiungere
```bash
# Sempre controllare cosa stai aggiungendo
git status
git diff
git add <files>
git status
```

### 2. Staging Logico
```bash
# ❌ Non fare questo
git add .  # Aggiunge tutto senza discriminazione

# ✅ Fai questo
git add src/auth.js src/login.js  # Modifiche correlate all'autenticazione
git commit -m "feat: implement user authentication"

git add docs/api.md docs/README.md  # Aggiornamenti documentazione
git commit -m "docs: update API documentation"
```

### 3. Usare .gitignore
```bash
# Prima di git add ., assicurati di avere un .gitignore appropriato
echo "node_modules/" >> .gitignore
echo "*.log" >> .gitignore
echo ".env" >> .gitignore
```

## 🚨 Errori Comuni

### 1. Aggiungere File Sensibili
```bash
# ❌ Problema
git add .env config/secrets.json

# ✅ Soluzione
# Aggiungere al .gitignore PRIMA
echo ".env" >> .gitignore
echo "config/secrets.json" >> .gitignore
```

### 2. Staging di File Temporanei
```bash
# ❌ Evitare
git add *.tmp *.log backup.*

# ✅ Meglio
# Configurare .gitignore appropriato
echo "*.tmp" >> .gitignore
echo "*.log" >> .gitignore
echo "backup.*" >> .gitignore
```

### 3. Non Verificare Prima del Commit
```bash
# ❌ Workflow frettoloso
git add .
git commit -m "fixes"

# ✅ Workflow controllato
git status
git diff
git add <specific-files>
git status
git diff --staged
git commit -m "fix: resolve navigation bug in mobile menu"
```

## 🔄 Annullare git add

Se hai aggiunto file per errore:

```bash
# Rimuovere file specifico dal staging
git reset HEAD file.txt

# Rimuovere tutto dal staging
git reset HEAD

# Con Git 2.23+
git restore --staged file.txt
git restore --staged .
```

## 🎓 Quiz di Verifica

1. **Qual è la differenza tra `git add .` e `git add -A`?**
2. **Come aggiungi solo parte delle modifiche di un file?**
3. **Come rimuovi un file dal staging senza perdere le modifiche?**

### Risposte
1. `git add .` aggiunge file nuovi e modificati, `git add -A` include anche file eliminati
2. Con `git add -p` per la modalità patch
3. Con `git reset HEAD <file>` o `git restore --staged <file>`

## 🔗 Comandi Correlati

- `git status` - Vedere stato dei file
- `git diff` - Vedere modifiche non staged
- `git diff --staged` - Vedere modifiche staged
- `git reset` - Rimuovere dal staging
- `git commit` - Committare file staged

## 📚 Risorse Aggiuntive

- [Git Add Documentation](https://git-scm.com/docs/git-add)
- [Interactive Staging Guide](https://git-scm.com/book/en/v2/Git-Tools-Interactive-Staging)
- [Staging Best Practices](https://www.atlassian.com/git/tutorials/saving-changes)

---

**Prossimo**: [03 - Git Commit e Messaggi](./03-git-commit.md) - Impara a creare commit efficaci
