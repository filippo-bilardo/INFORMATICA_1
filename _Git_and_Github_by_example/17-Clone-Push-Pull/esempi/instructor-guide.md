# Guida per l'Istruttore - Esempi Submodules e Subtree

## Overview
Questa guida fornisce istruzioni per utilizzare gli esempi pratici di Git Submodules e Subtree nelle lezioni.

## Struttura degli Esempi

### 📁 File Presenti
- `05-submodules-example.md` - Esempio completo per submoduli
- `06-subtree-example.md` - Esempio completo per subtree  
- `setup-examples.sh` - Script di automazione per setup rapido
- `instructor-guide.md` - Questa guida

## Utilizzo Rapido

### Setup Automatico (Raccomandato)
```bash
# Eseguire lo script interattivo
./setup-examples.sh

# Opzioni disponibili:
# 1. Setup solo esempio submoduli
# 2. Setup solo esempio subtree
# 3. Setup entrambi gli esempi
# 4. Eseguire dimostrazioni
# 5. Pulizia file di esempio
```

### Setup Manuale
Se preferite seguire passo-passo:
```bash
# Per submoduli
bash -c "$(sed -n '/setup_submodules_example()/,/^}/p' setup-examples.sh | tail -n +2 | head -n -1)"

# Per subtree
bash -c "$(sed -n '/setup_subtree_example()/,/^}/p' setup-examples.sh | tail -n +2 | head -n -1)"
```

## Tempi di Esecuzione

### Submodules Example (45-60 minuti)
- **Setup iniziale**: 10 minuti
- **Workflow base**: 15 minuti
- **Aggiornamenti coordinati**: 15 minuti
- **Automazione e best practices**: 15 minuti

### Subtree Example (45-60 minuti)
- **Setup iniziale**: 10 minuti
- **Integrazione e utilizzo**: 15 minuti
- **Contribuzioni upstream**: 15 minuti
- **Workflow di team**: 15 minuti

## Punti Chiave da Sottolineare

### Per Submoduli
1. **Concetto di puntatore**: I submoduli sono riferimenti a commit specifici
2. **Sincronizzazione**: Importanza di `git submodule update`
3. **Workflow coordinato**: Come team diversi lavorano insieme
4. **Vantaggi**: Versioning preciso, separazione dei repository
5. **Svantaggi**: Complessità operativa, curve di apprendimento

### Per Subtree  
1. **Integrazione diretta**: I file sono effettivamente copiati
2. **Storia unificata**: Come i commit vengono integrati
3. **Contribuzioni upstream**: Workflow per push verso progetti esterni
4. **Vantaggi**: Semplicità per sviluppatori, storia lineare
5. **Svantaggi**: Dimensione repository, complessità merge

## Differenze da Evidenziare

| Aspetto | Submoduli | Subtree |
|---------|-----------|---------|
| **Complessità** | Alta per utenti | Bassa per utenti |
| **Dimensione repo** | Piccola | Più grande |
| **Storia** | Separata | Integrata |
| **Clone** | Richiede `--recursive` | Automatico |
| **Contribuzioni** | Dirette | Via subtree push |

## Errori Comuni e Soluzioni

### Submoduli
```bash
# Errore: Submodulo vuoto dopo clone
git submodule update --init --recursive

# Errore: Modifiche non tracciate nel submodulo
cd submodule_dir
git add . && git commit -m "Changes"
cd .. && git add submodule_dir

# Errore: Submodulo in stato "detached HEAD"
cd submodule_dir && git checkout main
```

### Subtree
```bash
# Errore: Conflitti durante subtree pull
git subtree pull --prefix=utils origin main --strategy=subtree -X subtree

# Errore: Push upstream fallito
git subtree push --prefix=utils origin branch-name --squash

# Errore: Storia troppo complessa
# Usare sempre --squash per operazioni subtree
```

## Esercizi Aggiuntivi

### Per Submoduli
1. **Multi-submodule**: Aggiungere un secondo submodulo per i test
2. **Branch tracking**: Configurare submoduli per tracciare branch diversi
3. **Nested submodules**: Creare submoduli che contengono altri submoduli

### Per Subtree
1. **Multiple subtrees**: Gestire più subtree nello stesso progetto
2. **Selective pull**: Aggiornare solo parti specifiche
3. **Conflict resolution**: Simulare e risolvere conflitti complessi

## Script di Verifica

### Test Rapido Submoduli
```bash
cd submodules-example/webapp-main
echo "🔍 Checking submodule status..."
git submodule status
echo "🧪 Testing integration..."
node -e "console.log('✅ Submodules working')" 2>/dev/null || echo "⚠️ Node.js test skipped"
```

### Test Rapido Subtree
```bash  
cd subtree-example/main-project
echo "🔍 Checking subtree integration..."
ls utils/ | head -5
echo "🧪 Testing functionality..."
node tests/integration-test.js
```

## Troubleshooting

### Problemi di Permessi
```bash
# Se lo script non è eseguibile
chmod +x setup-examples.sh

# Se ci sono problemi con git init
git config --global init.defaultBranch main
```

### Problemi di Node.js
```bash
# Verificare versione Node.js
node --version  # Dovrebbe essere >= 14

# Se mancano moduli ES6
export NODE_OPTIONS="--experimental-modules"
```

### Reset Completo
```bash
# Rimuovere tutto e ricominciare
rm -rf submodules-example subtree-example
./setup-examples.sh
```

## Adattamenti per Aula

### Versione Breve (30 minuti)
- Usare solo lo script automatico
- Concentrarsi sui concetti principali
- Saltare gli script di automazione avanzati

### Versione Estesa (90 minuti)
- Seguire tutti i passaggi manuali
- Aggiungere esercizi personalizzati
- Includere troubleshooting in tempo reale

### Modalità Collaborativa
- Dividere la classe in gruppi
- Un gruppo lavora sui submoduli, l'altro sui subtree
- Scambio di esperienze alla fine

## Risorse Aggiuntive

### Comandi di Riferimento Rapido
```bash
# Submoduli
git submodule add <url> <path>
git submodule update --init --recursive
git submodule foreach 'git pull origin main'

# Subtree  
git subtree add --prefix=<dir> <repo> <branch> --squash
git subtree pull --prefix=<dir> <repo> <branch> --squash
git subtree push --prefix=<dir> <repo> <branch>
```

### Link Utili per Approfondimenti
- Git Submodules: https://git-scm.com/book/en/v2/Git-Tools-Submodules
- Git Subtree: https://github.com/git/git/blob/master/contrib/subtree/git-subtree.txt
- Best Practices: Da condividere durante la lezione

## Note Finali

Gli esempi sono progettati per essere:
- **Realistici**: Scenari che si incontrano realmente
- **Progressivi**: Dalla base agli scenari avanzati  
- **Interattivi**: Gli studenti possono sperimentare
- **Completi**: Coprono tutti i casi d'uso principali

Ricordate di enfatizzare quando usare uno strumento rispetto all'altro:
- **Submoduli**: Quando serve controllo preciso delle versioni
- **Subtree**: Quando serve semplicità operativa e storia unificata
