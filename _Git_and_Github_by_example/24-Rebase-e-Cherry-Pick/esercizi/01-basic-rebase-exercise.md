# Esercizio 1: Rebase di Base

## 🎯 Obiettivo
Imparare a eseguire un rebase semplice per sincronizzare un branch feature con il branch main aggiornato.

## 📋 Scenario
Stai lavorando su una nuova feature per un'applicazione web. Nel frattempo, altri sviluppatori hanno fatto commit sul branch `main`. Devi fare rebase del tuo branch per incorporare le modifiche più recenti.

## 🏗️ Setup Iniziale

Esegui questi comandi per creare l'ambiente di esercizio:

```bash
#!/bin/bash
# Creazione repository di esercizio
mkdir rebase-exercise-1 && cd rebase-exercise-1
git init
git config user.name "Student"
git config user.email "student@example.com"

# Setup iniziale
echo "# Web App Project" > README.md
mkdir src
echo "function main() { console.log('Hello World'); }" > src/main.js
git add .
git commit -m "Initial project setup"

# Simulazione sviluppo parallelo
git checkout -b feature/user-login

# Lavoro sul branch feature
echo "function login(user, pass) { return authenticate(user, pass); }" > src/auth.js
git add src/auth.js
git commit -m "Add basic login function"

echo "function authenticate(user, pass) { /* TODO */ return false; }" >> src/auth.js
git add src/auth.js
git commit -m "Add authenticate function skeleton"

# Tornare a main e simulare aggiornamenti da altri dev
git checkout main
echo "function utils() { return 'utility functions'; }" > src/utils.js
git add src/utils.js
git commit -m "Add utility functions"

echo "# Installation Guide" >> README.md
echo "npm install" >> README.md
git add README.md
git commit -m "Update README with installation guide"

echo "Ambiente setup completato!"
git log --oneline --all --graph
```

## 📝 Compiti da Svolgere

### Parte 1: Analisi Situazione Iniziale

1. **Controlla lo stato dei branch:**
   ```bash
   git branch -v
   git log --oneline --all --graph
   ```

2. **Identifica i commit su main che non sono nel branch feature**

3. **Verifica quale branch è ahead/behind:**
   ```bash
   git status
   git checkout feature/user-login
   git status
   ```

### Parte 2: Esecuzione Rebase

4. **Esegui il rebase del branch feature su main:**
   ```bash
   git checkout feature/user-login
   git rebase main
   ```

5. **Verifica il risultato:**
   ```bash
   git log --oneline --graph
   ```

### Parte 3: Verifica e Cleanup

6. **Controlla che tutti i file siano presenti:**
   ```bash
   ls src/
   cat src/main.js
   cat src/utils.js
   cat src/auth.js
   ```

7. **Verifica che la cronologia sia lineare:**
   ```bash
   git log --oneline --graph --all
   ```

## ✅ Risultati Attesi

Dopo il rebase, dovresti vedere:

1. Una cronologia lineare
2. I commit del branch feature applicati dopo quelli di main
3. Tutti i file presenti (main.js, utils.js, auth.js)
4. Nessun merge commit

### Cronologia Finale Attesa:
```
* commit-hash Add authenticate function skeleton
* commit-hash Add basic login function  
* commit-hash Update README with installation guide
* commit-hash Add utility functions
* commit-hash Initial project setup
```

## 🤔 Domande di Riflessione

1. Qual è la differenza tra il risultato del rebase e quello che avresti ottenuto con un merge?
2. Quando useresti rebase invece di merge?
3. Cosa succede ai commit SHA del branch feature dopo il rebase?

## 🔍 Troubleshooting

**Problema: Conflitti durante il rebase**
```bash
# Se ci sono conflitti, risolvi manualmente e poi:
git add .
git rebase --continue
```

**Problema: Vuoi annullare il rebase**
```bash
git rebase --abort
```

**Problema: Hai fatto rebase ma vuoi tornare indietro**
```bash
git reflog
git reset --hard HEAD@{n}  # dove n è la posizione prima del rebase
```

## 🎉 Bonus Challenge

Una volta completato l'esercizio base, prova a:

1. Aggiungere più commit su entrambi i branch
2. Creare una situazione con conflitti e risolverli
3. Utilizzare `git rebase -i` per modificare i messaggi di commit durante il rebase

## 📚 Riferimenti

- [Guida al Rebase Fundamentals](../guide/01-rebase-fundamentals.md)
- [Esempio Pratico Simple Rebase](../esempi/01-simple-rebase.md)
