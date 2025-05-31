# 🏋️ Esercizi: Clone, Push, Pull

## 🎯 Obiettivi di Apprendimento
Al termine di questi esercizi sarai in grado di:
- Clonare repository remoti
- Gestire operazioni di push e pull
- Risolvere conflitti durante sincronizzazione
- Utilizzare diverse strategie di pull
- Implementare workflow collaborativi

---

## 📋 Prerequisiti
- Git installato e configurato
- Conoscenza base dei comandi Git
- Comprensione di branch e commit
- Account GitHub (per esercizi avanzati)

---

## 🏃‍♂️ Esercizio 1: Clone e Push Base
**Difficoltà: ⭐ Principiante**

### Obiettivo
Imparare le operazioni base di clone e push.

### Compiti
1. **Setup Repository Locale**
   ```bash
   # Crea directory di lavoro
   mkdir esercizio-clone-push
   cd esercizio-clone-push
   
   # Inizializza repository
   git init
   ```

2. **Crea Contenuto Iniziale**
   ```bash
   # Crea file README
   echo "# Mio Primo Repository" > README.md
   echo "Questo repository dimostra clone e push" >> README.md
   
   # Crea file di progetto
   cat > progetto.py << 'EOF'
   def saluta(nome):
       return f"Ciao, {nome}!"
   
   if __name__ == "__main__":
       print(saluta("Mondo"))
   EOF
   ```

3. **Primo Commit**
   ```bash
   git add .
   git commit -m "Initial commit: Add README and basic project"
   ```

4. **Simula Repository Remoto**
   ```bash
   # Torna alla directory padre
   cd ..
   
   # Crea repository "remoto" (bare)
   git init --bare repository-remoto.git
   
   # Torna al repository locale
   cd esercizio-clone-push
   
   # Aggiungi remote
   git remote add origin ../repository-remoto.git
   
   # Push iniziale
   git push -u origin main
   ```

5. **Test Clone**
   ```bash
   cd ..
   
   # Clona il repository
   git clone repository-remoto.git clone-test
   
   # Verifica contenuto
   cd clone-test
   ls -la
   cat README.md
   ```

### ✅ Criteri di Successo
- [ ] Repository clonato correttamente
- [ ] Tutti i file presenti nel clone
- [ ] Push funzionante
- [ ] Remote configurato correttamente

---

## 🔄 Esercizio 2: Pull e Sincronizzazione
**Difficoltà: ⭐⭐ Intermedio**

### Obiettivo
Gestire la sincronizzazione tra repository locali.

### Setup
```bash
# Continua dall'esercizio precedente o ricrea setup
mkdir sync-exercise
cd sync-exercise

# Crea repository remoto
git init --bare remote.git

# Crea due cloni (due sviluppatori)
git clone remote.git developer1
git clone remote.git developer2
```

### Compiti

#### Parte A: Setup Iniziale
1. **Developer 1 - Setup Progetto**
   ```bash
   cd developer1
   git config user.name "Alice"
   git config user.email "alice@example.com"
   
   # Crea struttura progetto
   mkdir src tests
   echo "# Calculator Project" > README.md
   
   cat > src/calculator.py << 'EOF'
   class Calculator:
       def add(self, a, b):
           return a + b
       
       def subtract(self, a, b):
           return a - b
   EOF
   
   git add .
   git commit -m "Initial project structure"
   git push origin main
   ```

#### Parte B: Sincronizzazione Base
2. **Developer 2 - Pull e Modifica**
   ```bash
   cd ../developer2
   git config user.name "Bob"
   git config user.email "bob@example.com"
   
   # Pull del progetto iniziale
   git pull origin main
   
   # Aggiungi test
   cat > tests/test_calculator.py << 'EOF'
   import sys
   sys.path.append('../src')
   from calculator import Calculator
   
   def test_add():
       calc = Calculator()
       assert calc.add(2, 3) == 5
       print("Test add: PASSED")
   
   def test_subtract():
       calc = Calculator()
       assert calc.subtract(5, 3) == 2
       print("Test subtract: PASSED")
   
   if __name__ == "__main__":
       test_add()
       test_subtract()
       print("All tests passed!")
   EOF
   
   git add tests/
   git commit -m "Add: Basic calculator tests"
   git push origin main
   ```

#### Parte C: Workflow Collaborativo
3. **Developer 1 - Pull e Nuove Feature**
   ```bash
   cd ../developer1
   
   # Pull dei test
   git pull origin main
   
   # Aggiungi nuove funzioni
   cat >> src/calculator.py << 'EOF'
   
       def multiply(self, a, b):
           return a * b
       
       def divide(self, a, b):
           if b == 0:
               raise ValueError("Cannot divide by zero")
           return a / b
   EOF
   
   # Aggiorna README
   cat >> README.md << 'EOF'
   
   ## Features
   - Addition
   - Subtraction
   - Multiplication
   - Division
   EOF
   
   git add .
   git commit -m "Add: Multiply and divide functions"
   git push origin main
   ```

4. **Developer 2 - Sincronizza e Testa**
   ```bash
   cd ../developer2
   
   git pull origin main
   
   # Aggiungi test per nuove funzioni
   cat >> tests/test_calculator.py << 'EOF'
   
   def test_multiply():
       calc = Calculator()
       assert calc.multiply(4, 3) == 12
       print("Test multiply: PASSED")
   
   def test_divide():
       calc = Calculator()
       assert calc.divide(10, 2) == 5
       print("Test divide: PASSED")
   
   if __name__ == "__main__":
       test_add()
       test_subtract()
       test_multiply()
       test_divide()
       print("All tests passed!")
   EOF
   
   git add tests/
   git commit -m "Add: Tests for multiply and divide"
   git push origin main
   ```

### ✅ Criteri di Successo
- [ ] Entrambi i developer sincronizzati
- [ ] Pull funzionanti senza conflitti
- [ ] Codice e test funzionanti
- [ ] Storia Git pulita

---

## ⚔️ Esercizio 3: Gestione Conflitti
**Difficoltà: ⭐⭐⭐ Avanzato**

### Obiettivo
Imparare a gestire e risolvere conflitti durante pull.

### Setup
```bash
mkdir conflict-exercise
cd conflict-exercise
git init --bare remote.git
git clone remote.git dev1
git clone remote.git dev2
```

### Compiti

#### Parte A: Creazione Conflitto
1. **Setup Base**
   ```bash
   cd dev1
   git config user.name "Charlie"
   git config user.email "charlie@example.com"
   
   # File che causerà conflitto
   cat > config.py << 'EOF'
   # Configuration file
   APP_NAME = "MyApp"
   VERSION = "1.0.0"
   DEBUG = False
   
   # Database settings
   DB_HOST = "localhost"
   DB_PORT = 5432
   EOF
   
   git add config.py
   git commit -m "Initial configuration"
   git push origin main
   ```

2. **Developer 1 - Modifiche**
   ```bash
   # Modifica configurazione
   cat > config.py << 'EOF'
   # Configuration file
   APP_NAME = "MyAwesomeApp"
   VERSION = "1.1.0"
   DEBUG = True
   
   # Database settings
   DB_HOST = "localhost"
   DB_PORT = 5432
   
   # New feature settings
   CACHE_ENABLED = True
   LOG_LEVEL = "DEBUG"
   EOF
   
   git add config.py
   git commit -m "Update: App name, version and add caching"
   git push origin main
   ```

3. **Developer 2 - Modifiche Conflittuali**
   ```bash
   cd ../dev2
   git config user.name "Diana"
   git config user.email "diana@example.com"
   
   # Pull iniziale
   git pull origin main
   
   # Modifica STESSA sezione ma diversamente
   cat > config.py << 'EOF'
   # Configuration file - Production Ready
   APP_NAME = "ProductionApp"
   VERSION = "1.0.1"
   DEBUG = False
   
   # Database settings - Production
   DB_HOST = "prod-db.company.com"
   DB_PORT = 5432
   
   # Security settings
   SECRET_KEY = "change-me-in-production"
   SECURE_SSL = True
   EOF
   
   git add config.py
   git commit -m "Update: Production configuration and security"
   ```

#### Parte B: Risoluzione Conflitto
4. **Tentativo Push (fallirà)**
   ```bash
   # Questo fallirà
   git push origin main
   # Expected: ! [rejected] main -> main (fetch first)
   ```

5. **Pull con Conflitto**
   ```bash
   # Questo causerà conflitto
   git pull origin main
   ```

6. **Risoluzione Manuale**
   ```bash
   # Visualizza conflitto
   cat config.py
   
   # Risolvi manualmente creando versione combinata
   cat > config.py << 'EOF'
   # Configuration file - Configurable Environment
   APP_NAME = "MyAwesomeApp"
   VERSION = "1.1.0"
   DEBUG = False  # Can be overridden by environment
   
   # Database settings - Environment specific
   DB_HOST = "localhost"  # Override in production
   DB_PORT = 5432
   
   # Feature settings
   CACHE_ENABLED = True
   LOG_LEVEL = "INFO"
   
   # Security settings
   SECRET_KEY = "change-me-in-production"
   SECURE_SSL = True
   EOF
   
   # Segna come risolto
   git add config.py
   git commit -m "Merge: Resolve config conflicts - combine features and security"
   git push origin main
   ```

#### Parte C: Verifica Risoluzione
7. **Developer 1 - Sincronizza**
   ```bash
   cd ../dev1
   git pull origin main
   
   # Verifica risoluzione
   cat config.py
   git log --oneline --graph -5
   ```

### ✅ Criteri di Successo
- [ ] Conflitto creato e riconosciuto
- [ ] Conflitto risolto manualmente
- [ ] Merge commit creato
- [ ] Entrambi i developer sincronizzati
- [ ] Configurazione finale funzionante

---

## 📈 Esercizio 4: Strategie di Pull
**Difficoltà: ⭐⭐⭐ Avanzato**

### Obiettivo
Sperimentare diverse strategie di pull (merge, rebase, ff-only).

### Setup
```bash
mkdir pull-strategies
cd pull-strategies
git init --bare origin.git
git clone origin.git merge-dev
git clone origin.git rebase-dev
git clone origin.git ff-dev
```

### Compiti

#### Parte A: Setup Progetto Base
1. **Inizializzazione**
   ```bash
   cd merge-dev
   git config user.name "Merge Dev"
   git config user.email "merge@example.com"
   
   # Progetto base
   cat > app.js << 'EOF'
   // Simple Node.js app
   function greet(name) {
       return `Hello, ${name}!`;
   }
   
   function main() {
       console.log(greet("World"));
   }
   
   module.exports = { greet, main };
   
   if (require.main === module) {
       main();
   }
   EOF
   
   echo "node_modules/" > .gitignore
   cat > package.json << 'EOF'
   {
     "name": "pull-strategies-demo",
     "version": "1.0.0",
     "main": "app.js",
     "scripts": {
       "start": "node app.js",
       "test": "node test.js"
     }
   }
   EOF
   
   git add .
   git commit -m "Initial: Node.js app setup"
   git push origin main
   ```

#### Parte B: Test Merge Strategy
2. **Merge Dev - Modifiche Locali**
   ```bash
   # Configura per merge (default)
   git config pull.rebase false
   
   # Aggiungi test
   cat > test.js << 'EOF'
   const { greet } = require('./app');
   
   function testGreet() {
       const result = greet("Test");
       if (result === "Hello, Test!") {
           console.log("✅ Test greet: PASSED");
       } else {
           console.log("❌ Test greet: FAILED");
       }
   }
   
   testGreet();
   EOF
   
   git add test.js
   git commit -m "Add: Basic test suite"
   ```

3. **Simula Modifiche Remote**
   ```bash
   cd ../rebase-dev
   git config user.name "Remote Dev"
   git config user.email "remote@example.com"
   
   # Aggiungi feature remota
   cat >> app.js << 'EOF'

   function farewell(name) {
       return `Goodbye, ${name}!`;
   }

   module.exports = { greet, farewell, main };
   EOF
   
   git add app.js
   git commit -m "Add: farewell function"
   git push origin main
   ```

4. **Merge Dev - Pull con Merge**
   ```bash
   cd ../merge-dev
   
   echo "📊 Stato prima del pull:"
   git log --oneline --graph -3
   
   echo "🔀 Facendo pull con merge strategy:"
   git pull origin main
   
   echo "📊 Stato dopo pull merge:"
   git log --oneline --graph -5
   ```

#### Parte C: Test Rebase Strategy
5. **Rebase Dev - Setup**
   ```bash
   cd ../rebase-dev
   git config user.name "Rebase Dev"
   git config user.email "rebase@example.com"
   git config pull.rebase true
   
   # Pull ultimo stato
   git pull origin main
   
   # Modifiche locali
   cat > docs.md << 'EOF'
   # App Documentation
   
   ## Functions
   - `greet(name)`: Returns greeting message
   - `farewell(name)`: Returns farewell message
   
   ## Usage
   ```bash
   npm start
   npm test
   ```
   EOF
   
   git add docs.md
   git commit -m "Add: Documentation"
   ```

6. **Crea Nuove Modifiche Remote**
   ```bash
   cd ../ff-dev
   git config user.name "FF Dev"
   git config user.email "ff@example.com"
   
   git pull origin main
   
   # Aggiungi configurazione
   cat > config.json << 'EOF'
   {
     "app": {
       "name": "Pull Strategies Demo",
       "version": "1.0.0"
     },
     "environment": "development"
   }
   EOF
   
   git add config.json
   git commit -m "Add: Application configuration"
   git push origin main
   ```

7. **Rebase Dev - Pull con Rebase**
   ```bash
   cd ../rebase-dev
   
   echo "📊 Stato prima del pull rebase:"
   git log --oneline --graph -3
   
   echo "📈 Facendo pull con rebase strategy:"
   git pull origin main
   
   echo "📊 Stato dopo pull rebase:"
   git log --oneline --graph -5
   ```

#### Parte D: Test Fast-Forward Only
8. **FF Dev - Setup Fast-Forward Only**
   ```bash
   cd ../ff-dev
   git config pull.ff only
   
   # Crea modifiche locali
   echo "console.log('App started');" >> app.js
   git add app.js
   git commit -m "Add: Startup message"
   ```

9. **Crea Divergenza**
   ```bash
   cd ../merge-dev
   git pull origin main
   
   # Aggiungi utility
   cat > utils.js << 'EOF'
   function getCurrentTime() {
       return new Date().toISOString();
   }
   
   function log(message) {
       console.log(`[${getCurrentTime()}] ${message}`);
   }
   
   module.exports = { getCurrentTime, log };
   EOF
   
   git add utils.js
   git commit -m "Add: Utility functions"
   git push origin main
   ```

10. **FF Dev - Test Fast-Forward Only**
    ```bash
    cd ../ff-dev
    
    echo "⏩ Tentativo pull --ff-only (fallirà):"
    if ! git pull --ff-only origin main; then
        echo "❌ Fast-forward impossibile - divergenza rilevata"
        echo "💡 Opzioni disponibili:"
        echo "  1. git pull (merge)"
        echo "  2. git pull --rebase"
        echo "  3. git reset --hard origin/main (perde modifiche locali)"
        
        echo "🔄 Usando pull normale:"
        git config pull.ff false
        git pull origin main
    fi
    ```

#### Parte E: Confronto Risultati
11. **Analisi Finale**
    ```bash
    echo "📊 CONFRONTO STRATEGIE:"
    echo "======================"
    
    cd ../merge-dev
    echo "🔀 MERGE STRATEGY:"
    git log --oneline --graph -8
    
    cd ../rebase-dev
    echo -e "\n📈 REBASE STRATEGY:"
    git log --oneline --graph -8
    
    cd ../ff-dev
    echo -e "\n⏩ FAST-FORWARD STRATEGY:"
    git log --oneline --graph -8
    ```

### ✅ Criteri di Successo
- [ ] Tutte e tre le strategie testate
- [ ] Differenze tra strategie comprese
- [ ] Storia Git analizzata per ogni strategia
- [ ] Configurazioni pull impostate correttamente

---

## 🚀 Esercizio 5: Workflow GitHub
**Difficoltà: ⭐⭐⭐⭐ Esperto**

### Obiettivo
Implementare un workflow completo con GitHub.

### Prerequisiti
- Account GitHub
- Git configurato con SSH o token

### Compiti

#### Parte A: Setup Repository GitHub
1. **Crea Repository su GitHub**
   - Nome: `git-workflow-exercise`
   - Pubblico o privato
   - Con README, .gitignore (Node), licenza MIT

2. **Clone Locale**
   ```bash
   git clone https://github.com/TUO_USERNAME/git-workflow-exercise.git
   cd git-workflow-exercise
   ```

#### Parte B: Sviluppo Feature
3. **Setup Progetto**
   ```bash
   # Inizializza progetto Node.js
   npm init -y
   
   # Installa dipendenze
   npm install express
   npm install --save-dev jest
   
   # Crea struttura
   mkdir src tests
   ```

4. **Implementa Feature**
   ```bash
   cat > src/server.js << 'EOF'
   const express = require('express');
   const app = express();
   const PORT = process.env.PORT || 3000;
   
   app.use(express.json());
   
   // Routes
   app.get('/', (req, res) => {
       res.json({ message: 'Hello, World!', timestamp: new Date() });
   });
   
   app.get('/health', (req, res) => {
       res.json({ status: 'OK', uptime: process.uptime() });
   });
   
   const server = app.listen(PORT, () => {
       console.log(`Server running on port ${PORT}`);
   });
   
   module.exports = { app, server };
   EOF
   
   # Test
   cat > tests/server.test.js << 'EOF'
   const request = require('supertest');
   const { app } = require('../src/server');
   
   describe('Server Endpoints', () => {
       test('GET / should return hello message', async () => {
           const response = await request(app).get('/');
           expect(response.status).toBe(200);
           expect(response.body.message).toBe('Hello, World!');
       });
       
       test('GET /health should return OK', async () => {
           const response = await request(app).get('/health');
           expect(response.status).toBe(200);
           expect(response.body.status).toBe('OK');
       });
   });
   EOF
   
   # Package.json scripts
   npm pkg set scripts.start="node src/server.js"
   npm pkg set scripts.test="jest"
   npm pkg set scripts.dev="nodemon src/server.js"
   
   # Installa dipendenze aggiuntive
   npm install --save-dev supertest nodemon
   ```

#### Parte C: Commit e Push
5. **Primo Push**
   ```bash
   git add .
   git commit -m "feat: Initial Express server with health endpoint
   
   - Add Express server setup
   - Implement hello world endpoint
   - Add health check endpoint
   - Include Jest test suite
   - Configure npm scripts"
   
   git push origin main
   ```

#### Parte D: Feature Branch Workflow
6. **Crea Feature Branch**
   ```bash
   git checkout -b feature/user-api
   ```

7. **Implementa User API**
   ```bash
   # Crea user controller
   mkdir src/controllers
   cat > src/controllers/userController.js << 'EOF'
   let users = [
       { id: 1, name: 'Alice', email: 'alice@example.com' },
       { id: 2, name: 'Bob', email: 'bob@example.com' }
   ];
   
   const getAllUsers = (req, res) => {
       res.json(users);
   };
   
   const getUserById = (req, res) => {
       const user = users.find(u => u.id === parseInt(req.params.id));
       if (!user) {
           return res.status(404).json({ error: 'User not found' });
       }
       res.json(user);
   };
   
   const createUser = (req, res) => {
       const { name, email } = req.body;
       if (!name || !email) {
           return res.status(400).json({ error: 'Name and email required' });
       }
       
       const newUser = {
           id: users.length + 1,
           name,
           email
       };
       users.push(newUser);
       res.status(201).json(newUser);
   };
   
   module.exports = { getAllUsers, getUserById, createUser };
   EOF
   
   # Aggiorna server.js
   cat > src/server.js << 'EOF'
   const express = require('express');
   const { getAllUsers, getUserById, createUser } = require('./controllers/userController');
   
   const app = express();
   const PORT = process.env.PORT || 3000;
   
   app.use(express.json());
   
   // Basic routes
   app.get('/', (req, res) => {
       res.json({ message: 'Hello, World!', timestamp: new Date() });
   });
   
   app.get('/health', (req, res) => {
       res.json({ status: 'OK', uptime: process.uptime() });
   });
   
   // User routes
   app.get('/api/users', getAllUsers);
   app.get('/api/users/:id', getUserById);
   app.post('/api/users', createUser);
   
   const server = app.listen(PORT, () => {
       console.log(`Server running on port ${PORT}`);
   });
   
   module.exports = { app, server };
   EOF
   
   # Test per user API
   cat > tests/users.test.js << 'EOF'
   const request = require('supertest');
   const { app } = require('../src/server');
   
   describe('User API', () => {
       test('GET /api/users should return all users', async () => {
           const response = await request(app).get('/api/users');
           expect(response.status).toBe(200);
           expect(Array.isArray(response.body)).toBe(true);
           expect(response.body.length).toBeGreaterThan(0);
       });
       
       test('GET /api/users/:id should return specific user', async () => {
           const response = await request(app).get('/api/users/1');
           expect(response.status).toBe(200);
           expect(response.body.id).toBe(1);
           expect(response.body.name).toBeDefined();
       });
       
       test('POST /api/users should create new user', async () => {
           const newUser = { name: 'Charlie', email: 'charlie@example.com' };
           const response = await request(app).post('/api/users').send(newUser);
           expect(response.status).toBe(201);
           expect(response.body.name).toBe('Charlie');
           expect(response.body.id).toBeDefined();
       });
   });
   EOF
   ```

8. **Commit Feature**
   ```bash
   git add .
   git commit -m "feat: Add user API endpoints
   
   - Implement user controller with CRUD operations
   - Add GET /api/users endpoint
   - Add GET /api/users/:id endpoint  
   - Add POST /api/users endpoint
   - Include comprehensive test suite
   - Add input validation and error handling"
   
   git push origin feature/user-api
   ```

#### Parte E: Pull Request Workflow
9. **Crea Pull Request su GitHub**
   - Vai su GitHub
   - Crea Pull Request da `feature/user-api` a `main`
   - Titolo: "feat: Add user API endpoints"
   - Descrizione dettagliata della feature

10. **Simulazione Review**
    ```bash
    # Crea branch per review
    git checkout main
    git pull origin main
    git checkout -b review/user-api-improvements
    
    # Aggiungi miglioramenti
    cat > src/middleware/validation.js << 'EOF'
    const validateUser = (req, res, next) => {
        const { name, email } = req.body;
        
        if (!name || typeof name !== 'string' || name.trim().length < 2) {
            return res.status(400).json({ 
                error: 'Name must be a string with at least 2 characters' 
            });
        }
        
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!email || !emailRegex.test(email)) {
            return res.status(400).json({ 
                error: 'Valid email address is required' 
            });
        }
        
        next();
    };
    
    module.exports = { validateUser };
    EOF
    
    # Aggiorna controller per usare validation
    git add .
    git commit -m "improve: Add input validation middleware
    
    - Create validation middleware for user data
    - Add email format validation
    - Add name length validation
    - Improve error messages"
    
    git push origin review/user-api-improvements
    ```

#### Parte F: Merge e Cleanup
11. **Merge Pull Request**
    - Merge su GitHub (o localmente)
    - Cancella branch feature

12. **Sync Locale**
    ```bash
    git checkout main
    git pull origin main
    git branch -d feature/user-api
    git branch -d review/user-api-improvements
    
    # Cleanup remote branches
    git remote prune origin
    ```

### ✅ Criteri di Successo
- [ ] Repository GitHub creato
- [ ] Feature implementata su branch separato
- [ ] Pull Request creato e gestito
- [ ] Codice testato e funzionante
- [ ] Workflow collaborativo completato
- [ ] Branch cleanup eseguito

---

## 🎯 Progetto Finale: Team Collaboration
**Difficoltà: ⭐⭐⭐⭐⭐ Master**

### Obiettivo
Simulare un progetto di team completo con multiple feature.

### Setup
Se possibile, lavora con 2-3 persone. Altrimenti simula con branch diversi.

### Compiti
1. **Project Manager**: Setup repository e project board
2. **Frontend Dev**: Implementa interfaccia utente
3. **Backend Dev**: API e business logic  
4. **DevOps**: CI/CD e deployment scripts

### Deliverable
- Repository con storia Git pulita
- README completo con documentazione
- Test suite completa
- Workflow CI/CD funzionante

---

## 📚 Risorse Aggiuntive

### Comandi Utili
```bash
# Verifica configurazioni pull
git config --list | grep pull

# Visualizza storia con grafico
git log --oneline --graph --all

# Verifica stato remoti
git remote -v
git branch -vv

# Cleanup repository
git gc --prune=now
git remote prune origin
```

### Best Practices
1. **Sempre fare pull prima di push**
2. **Usare branch per feature**
3. **Scrivere commit message chiari**
4. **Testare prima di push**
5. **Configurare pull strategy appropriata**

### Troubleshooting
- **Push respinto**: `git pull` prima di push
- **Conflitti**: Risolvi manualmente, poi `git add` e `git commit`
- **Storia confusa**: Usa `git log --graph` per visualizzare
- **Branch obsoleti**: `git remote prune origin`

---

*🎓 Completa tutti gli esercizi per padroneggiare le operazioni remote di Git!*
