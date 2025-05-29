# Esempio 03: Pull e Sincronizzazione Avanzata

## 📋 Scenario
Lavori in team e devi costantemente sincronizzare il tuo lavoro con quello dei colleghi. Imparerai a gestire pull, fetch, merge conflicts e strategie di sincronizzazione per mantenere il repository sempre aggiornato.

## 🎯 Obiettivi
- Padroneggiare `git pull` vs `git fetch`
- Gestire sincronizzazione in scenari collaborativi
- Risolvere conflitti durante pull
- Implementare strategie di sync sicure

## 🚀 Implementazione Pratica

### Fase 1: Pull Base e Differenze con Fetch

```bash
# 1. Setup scenario collaborativo
mkdir team-collaboration
cd team-collaboration
git clone https://github.com/team/shared-project.git
cd shared-project

# 2. Verificare stato remoto
git remote -v
git branch -a
git log --oneline -5

# 3. Fetch vs Pull - capire la differenza
echo "🔍 FETCH: solo download, nessun merge"
git fetch origin

# Vedere cosa è stato scaricato
git log --oneline main..origin/main

# Vedere differenze specifiche
git diff main origin/main

echo -e "\n🔄 PULL: fetch + merge automatico"
git pull origin main
```

**Output fetch tipico:**
```
remote: Enumerating objects: 15, done.
remote: Counting objects: 100% (15/15), done.
remote: Total 8 (delta 2), reused 0 (delta 0)
Unpacking objects: 100% (8/8), done.
From https://github.com/team/shared-project
   abc1234..def5678  main       -> origin/main
```

### Fase 2: Simulazione Scenario Team Reale

```bash
# Scenario: Team di 3 sviluppatori che lavorano su un'app web

# 1. Sviluppatore 1 (Alice) - Backend API
git checkout -b feature/user-api

# Creare API endpoint
mkdir -p api/routes
cat > api/routes/users.js << 'EOF'
const express = require('express');
const router = express.Router();

// Database simulation
let users = [
    { id: 1, name: 'Alice Smith', email: 'alice@example.com', role: 'admin' },
    { id: 2, name: 'Bob Johnson', email: 'bob@example.com', role: 'user' },
    { id: 3, name: 'Carol Davis', email: 'carol@example.com', role: 'user' }
];

// GET /api/users - Ottieni tutti gli utenti
router.get('/', (req, res) => {
    res.json({
        success: true,
        data: users,
        count: users.length
    });
});

// GET /api/users/:id - Ottieni utente specifico
router.get('/:id', (req, res) => {
    const id = parseInt(req.params.id);
    const user = users.find(u => u.id === id);
    
    if (!user) {
        return res.status(404).json({
            success: false,
            message: 'Utente non trovato'
        });
    }
    
    res.json({
        success: true,
        data: user
    });
});

// POST /api/users - Crea nuovo utente
router.post('/', (req, res) => {
    const { name, email, role } = req.body;
    
    if (!name || !email) {
        return res.status(400).json({
            success: false,
            message: 'Nome e email sono obbligatori'
        });
    }
    
    const newUser = {
        id: users.length + 1,
        name,
        email,
        role: role || 'user'
    };
    
    users.push(newUser);
    
    res.status(201).json({
        success: true,
        data: newUser,
        message: 'Utente creato con successo'
    });
});

module.exports = router;
EOF

cat > api/app.js << 'EOF'
const express = require('express');
const cors = require('cors');
const usersRouter = require('./routes/users');

const app = express();
const PORT = process.env.PORT || 3000;

// Middleware
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

// Routes
app.use('/api/users', usersRouter);

// Health check
app.get('/health', (req, res) => {
    res.json({ status: 'OK', timestamp: new Date().toISOString() });
});

// Error handling
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).json({
        success: false,
        message: 'Errore interno del server'
    });
});

app.listen(PORT, () => {
    console.log(`🚀 Server avviato su porta ${PORT}`);
});
EOF

# Commit API backend
git add api/
git commit -m "feat(api): implementata API REST per gestione utenti

- Endpoint GET /api/users con paginazione
- Endpoint GET /api/users/:id per singolo utente  
- Endpoint POST /api/users per creazione
- Validazione input e gestione errori
- Middleware CORS e JSON parsing
- Health check endpoint"

# 2. Mentre Alice lavora, simula aggiornamenti sul main
git checkout main

# Simula che Bob ha pushato frontend
mkdir -p public/js public/css
cat > public/index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Team App - Dashboard</title>
    <link rel="stylesheet" href="css/styles.css">
</head>
<body>
    <div class="container">
        <header class="header">
            <h1>🚀 Team Dashboard</h1>
            <div class="user-info">
                <span id="current-user">Caricamento...</span>
                <button id="logout-btn">Logout</button>
            </div>
        </header>
        
        <main class="main-content">
            <section class="stats-section">
                <div class="stat-card">
                    <h3>Utenti Totali</h3>
                    <span id="total-users" class="stat-number">-</span>
                </div>
                <div class="stat-card">
                    <h3>Utenti Attivi</h3>
                    <span id="active-users" class="stat-number">-</span>
                </div>
                <div class="stat-card">
                    <h3>Admin</h3>
                    <span id="admin-users" class="stat-number">-</span>
                </div>
            </section>
            
            <section class="users-section">
                <div class="section-header">
                    <h2>Gestione Utenti</h2>
                    <button id="add-user-btn" class="btn btn-primary">Aggiungi Utente</button>
                </div>
                <div id="users-table" class="users-table">
                    <div class="loading">Caricamento utenti...</div>
                </div>
            </section>
        </main>
    </div>
    
    <!-- Modal per aggiunta utente -->
    <div id="user-modal" class="modal hidden">
        <div class="modal-content">
            <h3>Aggiungi Nuovo Utente</h3>
            <form id="user-form">
                <input type="text" id="user-name" placeholder="Nome completo" required>
                <input type="email" id="user-email" placeholder="Email" required>
                <select id="user-role">
                    <option value="user">Utente</option>
                    <option value="admin">Admin</option>
                </select>
                <div class="modal-actions">
                    <button type="button" id="cancel-btn">Annulla</button>
                    <button type="submit">Salva</button>
                </div>
            </form>
        </div>
    </div>
    
    <script src="js/dashboard.js"></script>
</body>
</html>
EOF

cat > public/css/styles.css << 'EOF'
/* Reset e variabili */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

:root {
    --primary-color: #2563eb;
    --secondary-color: #64748b;
    --success-color: #10b981;
    --danger-color: #ef4444;
    --warning-color: #f59e0b;
    --bg-color: #f8fafc;
    --card-bg: #ffffff;
    --text-primary: #1e293b;
    --text-secondary: #64748b;
    --border-color: #e2e8f0;
}

body {
    font-family: 'Inter', -apple-system, BlinkMacSystemFont, sans-serif;
    background-color: var(--bg-color);
    color: var(--text-primary);
    line-height: 1.6;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
}

/* Header */
.header {
    background: var(--card-bg);
    border-bottom: 1px solid var(--border-color);
    padding: 1rem 0;
    margin-bottom: 2rem;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.header h1 {
    color: var(--primary-color);
    font-size: 1.5rem;
}

.user-info {
    display: flex;
    align-items: center;
    gap: 1rem;
}

/* Buttons */
.btn {
    padding: 0.5rem 1rem;
    border: none;
    border-radius: 0.375rem;
    font-size: 0.875rem;
    font-weight: 500;
    cursor: pointer;
    transition: all 0.2s;
}

.btn-primary {
    background: var(--primary-color);
    color: white;
}

.btn-primary:hover {
    background: #1d4ed8;
}

/* Stats Section */
.stats-section {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 1rem;
    margin-bottom: 2rem;
}

.stat-card {
    background: var(--card-bg);
    padding: 1.5rem;
    border-radius: 0.5rem;
    border: 1px solid var(--border-color);
    text-align: center;
}

.stat-card h3 {
    color: var(--text-secondary);
    font-size: 0.875rem;
    margin-bottom: 0.5rem;
}

.stat-number {
    font-size: 2rem;
    font-weight: bold;
    color: var(--primary-color);
}

/* Users Section */
.users-section {
    background: var(--card-bg);
    border-radius: 0.5rem;
    border: 1px solid var(--border-color);
    overflow: hidden;
}

.section-header {
    padding: 1.5rem;
    border-bottom: 1px solid var(--border-color);
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.users-table {
    padding: 1rem;
}

.loading {
    text-align: center;
    color: var(--text-secondary);
    padding: 2rem;
}

/* Modal */
.modal {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background: rgba(0, 0, 0, 0.5);
    display: flex;
    justify-content: center;
    align-items: center;
    z-index: 1000;
}

.modal.hidden {
    display: none;
}

.modal-content {
    background: var(--card-bg);
    padding: 2rem;
    border-radius: 0.5rem;
    width: 90%;
    max-width: 400px;
}

.modal-content h3 {
    margin-bottom: 1rem;
}

.modal-content input,
.modal-content select {
    width: 100%;
    padding: 0.5rem;
    margin-bottom: 1rem;
    border: 1px solid var(--border-color);
    border-radius: 0.375rem;
}

.modal-actions {
    display: flex;
    gap: 1rem;
    justify-content: flex-end;
}

/* Responsive */
@media (max-width: 768px) {
    .header {
        flex-direction: column;
        gap: 1rem;
        text-align: center;
    }
    
    .section-header {
        flex-direction: column;
        gap: 1rem;
    }
    
    .stats-section {
        grid-template-columns: 1fr;
    }
}
EOF

git add public/
git commit -m "feat(frontend): aggiunta dashboard utenti responsiva

- Layout responsive con CSS Grid e Flexbox
- Design system con variabili CSS custom
- Interfaccia per gestione utenti
- Modal per aggiunta nuovi utenti
- Sezione statistiche con cards
- Compatibilità mobile con media queries"

# 3. Alice deve sincronizzare prima di continuare
git checkout feature/user-api

echo "📥 Alice controlla aggiornamenti prima di continuare..."
git fetch origin

# Vedere cosa è cambiato
echo "🔍 Cosa è cambiato su main:"
git log --oneline main..origin/main

echo "📊 Statistiche modifiche:"
git diff --stat main origin/main

# Strategia 1: Merge main in feature branch
echo "🔄 Strategia 1: Merge main nel branch feature"
git merge origin/main
```

### Fase 3: Pull con Conflitti Simulati

```bash
# 1. Creare conflitti intenzionali
git checkout main

# Modifica file che potrebbe confliggere
cat > public/js/dashboard.js << 'EOF'
// Dashboard Main Application
class UserDashboard {
    constructor() {
        this.apiBase = '/api';
        this.currentUser = null;
        this.users = [];
        this.init();
    }
    
    init() {
        this.loadCurrentUser();
        this.loadUsers();
        this.setupEventListeners();
    }
    
    async loadCurrentUser() {
        // Simula utente corrente (in app reale da JWT/session)
        this.currentUser = {
            name: 'Mario Rossi',
            role: 'admin',
            email: 'mario@example.com'
        };
        
        document.getElementById('current-user').textContent = this.currentUser.name;
    }
    
    async loadUsers() {
        try {
            const response = await fetch(`${this.apiBase}/users`);
            const result = await response.json();
            
            if (result.success) {
                this.users = result.data;
                this.renderUsers();
                this.updateStats();
            } else {
                this.showError('Errore nel caricamento utenti');
            }
        } catch (error) {
            console.error('Errore API:', error);
            this.showError('Errore di connessione');
        }
    }
    
    renderUsers() {
        const container = document.getElementById('users-table');
        
        if (this.users.length === 0) {
            container.innerHTML = '<div class="loading">Nessun utente trovato</div>';
            return;
        }
        
        const html = `
            <table class="table">
                <thead>
                    <tr>
                        <th>ID</th>
                        <th>Nome</th>
                        <th>Email</th>
                        <th>Ruolo</th>
                        <th>Azioni</th>
                    </tr>
                </thead>
                <tbody>
                    ${this.users.map(user => `
                        <tr>
                            <td>${user.id}</td>
                            <td>${user.name}</td>
                            <td>${user.email}</td>
                            <td>
                                <span class="badge badge-${user.role === 'admin' ? 'primary' : 'secondary'}">
                                    ${user.role}
                                </span>
                            </td>
                            <td>
                                <button onclick="dashboard.editUser(${user.id})" class="btn btn-sm">Modifica</button>
                                ${user.role !== 'admin' ? `<button onclick="dashboard.deleteUser(${user.id})" class="btn btn-sm btn-danger">Elimina</button>` : ''}
                            </td>
                        </tr>
                    `).join('')}
                </tbody>
            </table>
        `;
        
        container.innerHTML = html;
    }
    
    updateStats() {
        const totalUsers = this.users.length;
        const activeUsers = this.users.filter(u => u.role === 'user').length;
        const adminUsers = this.users.filter(u => u.role === 'admin').length;
        
        document.getElementById('total-users').textContent = totalUsers;
        document.getElementById('active-users').textContent = activeUsers;
        document.getElementById('admin-users').textContent = adminUsers;
    }
    
    setupEventListeners() {
        // Modal controls
        document.getElementById('add-user-btn').addEventListener('click', () => {
            this.openModal();
        });
        
        document.getElementById('cancel-btn').addEventListener('click', () => {
            this.closeModal();
        });
        
        document.getElementById('user-form').addEventListener('submit', (e) => {
            e.preventDefault();
            this.handleAddUser();
        });
        
        // Logout
        document.getElementById('logout-btn').addEventListener('click', () => {
            this.handleLogout();
        });
    }
    
    openModal() {
        document.getElementById('user-modal').classList.remove('hidden');
    }
    
    closeModal() {
        document.getElementById('user-modal').classList.add('hidden');
        document.getElementById('user-form').reset();
    }
    
    async handleAddUser() {
        const name = document.getElementById('user-name').value.trim();
        const email = document.getElementById('user-email').value.trim();
        const role = document.getElementById('user-role').value;
        
        if (!name || !email) {
            this.showError('Nome e email sono obbligatori');
            return;
        }
        
        try {
            const response = await fetch(`${this.apiBase}/users`, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({ name, email, role })
            });
            
            const result = await response.json();
            
            if (result.success) {
                this.users.push(result.data);
                this.renderUsers();
                this.updateStats();
                this.closeModal();
                this.showSuccess('Utente aggiunto con successo');
            } else {
                this.showError(result.message || 'Errore nell\'aggiunta utente');
            }
        } catch (error) {
            console.error('Errore:', error);
            this.showError('Errore di connessione');
        }
    }
    
    async deleteUser(userId) {
        if (!confirm('Sei sicuro di voler eliminare questo utente?')) {
            return;
        }
        
        // Simula eliminazione (in app reale chiamata DELETE API)
        this.users = this.users.filter(u => u.id !== userId);
        this.renderUsers();
        this.updateStats();
        this.showSuccess('Utente eliminato');
    }
    
    editUser(userId) {
        // TODO: Implementare modifica utente
        this.showInfo('Funzionalità di modifica in sviluppo');
    }
    
    handleLogout() {
        if (confirm('Sei sicuro di voler uscire?')) {
            // In app reale: invalidare token, redirect login
            alert('Logout simulato');
        }
    }
    
    showSuccess(message) {
        this.showToast(message, 'success');
    }
    
    showError(message) {
        this.showToast(message, 'error');
    }
    
    showInfo(message) {
        this.showToast(message, 'info');
    }
    
    showToast(message, type = 'info') {
        // Toast notification semplice
        const toast = document.createElement('div');
        toast.className = `toast toast-${type}`;
        toast.textContent = message;
        
        // Styling inline per semplicità
        Object.assign(toast.style, {
            position: 'fixed',
            top: '20px',
            right: '20px',
            padding: '12px 24px',
            borderRadius: '6px',
            color: 'white',
            fontSize: '14px',
            zIndex: '9999',
            backgroundColor: type === 'success' ? '#10b981' : 
                           type === 'error' ? '#ef4444' : '#3b82f6'
        });
        
        document.body.appendChild(toast);
        
        setTimeout(() => {
            toast.remove();
        }, 3000);
    }
}

// Inizializza dashboard quando DOM è pronto
let dashboard;
document.addEventListener('DOMContentLoaded', () => {
    dashboard = new UserDashboard();
});
EOF

git add public/js/dashboard.js
git commit -m "feat(frontend): implementata logica dashboard interattiva

- Classe UserDashboard per gestione stato
- Integrazione completa con API REST
- CRUD operations con feedback utente
- Sistema toast per notifiche
- Gestione errori e validazione
- Event listeners per interazioni UI"

# 2. Alice ora ha conflitti quando prova a fare merge
git checkout feature/user-api

echo "⚠️  Tentativo pull con potenziali conflitti..."
git pull origin main

# Se ci sono conflitti, li risolviamo
echo "🔧 Risoluzione conflitti manuale se necessario..."

# Verifica conflitti
if git status | grep -q "Unmerged paths"; then
    echo "❌ Conflitti rilevati! Risoluzione necessaria:"
    git status
    
    # Lista file in conflitto
    echo "📁 File in conflitto:"
    git diff --name-only --diff-filter=U
fi
```

### Fase 4: Strategie Pull Avanzate

```bash
# 1. Pull con Rebase (mantiene cronologia lineare)
git checkout feature/clean-history
git pull --rebase origin main

# 2. Pull con strategie specifiche
git pull -X ours origin main       # In caso di conflitto, favorisce le nostre modifiche
git pull -X theirs origin main     # In caso di conflitto, favorisce le modifiche remote

# 3. Pull selettivo (solo fetch + merge manuale)
git fetch origin
git log --oneline origin/main ^main  # Vedere commit da mergere
git merge origin/main

# 4. Pull con verifica automatica
git pull --verify-signatures origin main  # Verifica firme GPG

# 5. Pull con depth limitato (per repository grandi)
git pull --depth=50 origin main
```

## 🔄 Workflow Avanzati di Sincronizzazione

### Script di Sincronizzazione Intelligente

```bash
#!/bin/bash
# smart-sync.sh - Sincronizzazione intelligente

echo "🔄 SINCRONIZZAZIONE INTELLIGENTE"
echo "================================="

current_branch=$(git branch --show-current)
echo "📍 Branch corrente: $current_branch"

# 1. Verifica stato working directory
if ! git diff-index --quiet HEAD --; then
    echo "⚠️  Working directory non pulito!"
    echo "Stash automatico delle modifiche..."
    git stash push -m "Auto-stash prima di sync $(date)"
    stashed=true
fi

# 2. Fetch aggiornamenti
echo "📥 Fetching aggiornamenti..."
git fetch origin

# 3. Verifica se ci sono aggiornamenti
if [ "$(git rev-parse HEAD)" = "$(git rev-parse @{u})" ]; then
    echo "✅ Repository già sincronizzato"
    exit 0
fi

echo "📊 Aggiornamenti disponibili:"
git log --oneline HEAD..@{u}

# 4. Strategia di merge basata su configurazione
merge_strategy=$(git config --get pull.rebase || echo "merge")

if [ "$merge_strategy" = "true" ]; then
    echo "🔄 Sincronizzazione con rebase..."
    git pull --rebase
else
    echo "🔄 Sincronizzazione con merge..."
    git pull
fi

# 5. Ripristina stash se necessario
if [ "$stashed" = true ]; then
    echo "📂 Ripristino modifiche stashed..."
    git stash pop
fi

echo "✅ Sincronizzazione completata!"
```

### Monitoring Continuo Repository

```bash
#!/bin/bash
# repo-monitor.sh - Monitora cambiamenti remoti

watch_interval=30  # secondi

echo "👁️  MONITORING REPOSITORY"
echo "Controllo ogni $watch_interval secondi..."
echo "Premi Ctrl+C per fermare"

last_commit=""

while true; do
    # Fetch silenzioso
    git fetch origin 2>/dev/null
    
    # Ottieni ultimo commit remoto
    current_commit=$(git rev-parse origin/main)
    
    if [ "$last_commit" != "" ] && [ "$last_commit" != "$current_commit" ]; then
        echo "🔔 NUOVI AGGIORNAMENTI RILEVATI!"
        echo "Timestamp: $(date)"
        echo "Nuovo commit: $current_commit"
        
        # Mostra dettagli nuovo commit
        git log --oneline -1 $current_commit
        
        # Notifica desktop (Linux)
        if command -v notify-send >/dev/null; then
            notify-send "Git Update" "Nuovi commit disponibili nel repository"
        fi
        
        # Opzionale: pull automatico
        # echo "Pull automatico..."
        # git pull origin main
    fi
    
    last_commit=$current_commit
    sleep $watch_interval
done
```

## 🔧 Risoluzione Problemi Pull

### Errori Comuni e Soluzioni

```bash
# 1. "Your local changes would be overwritten by merge"
# Soluzione: Stash o commit le modifiche
git stash
git pull origin main
git stash pop

# 2. "There is no tracking information for the current branch"
# Soluzione: Impostare upstream
git branch --set-upstream-to=origin/main main
git pull

# 3. "Cannot pull with rebase: You have unstaged changes"
# Soluzione: Pulire working directory
git add .
git commit -m "WIP: work in progress"
git pull --rebase origin main

# 4. "CONFLICT (content): Merge conflict in file.txt"
# Soluzione: Risoluzione manuale
git status
# Modificare file con conflitti
git add file.txt
git commit

# 5. "refusing to merge unrelated histories"
# Soluzione: Forzare merge di historie separate
git pull origin main --allow-unrelated-histories
```

### Script di Recovery Automatico

```bash
#!/bin/bash
# pull-recovery.sh - Recovery automatico da errori pull

echo "🚑 RECOVERY AUTOMATICO PULL"

# Verifica se siamo in mezzo a un merge
if [ -f .git/MERGE_HEAD ]; then
    echo "⚠️  Merge in corso rilevato"
    
    # Controlla conflitti
    if git status | grep -q "Unmerged paths"; then
        echo "❌ Conflitti rilevati. Risoluzione manuale necessaria:"
        git status --porcelain | grep "^UU"
        echo "Dopo aver risolto i conflitti, esegui:"
        echo "  git add <file>"
        echo "  git commit"
        exit 1
    else
        echo "✅ Nessun conflitto, completamento merge..."
        git commit --no-edit
    fi
fi

# Verifica se siamo in mezzo a un rebase
if [ -d .git/rebase-merge ] || [ -d .git/rebase-apply ]; then
    echo "⚠️  Rebase in corso rilevato"
    echo "Opzioni:"
    echo "  git rebase --continue  (dopo aver risolto conflitti)"
    echo "  git rebase --abort     (per annullare)"
    echo "  git rebase --skip      (per saltare commit problematico)"
    exit 1
fi

# Verifica working directory pulito
if ! git diff-index --quiet HEAD --; then
    echo "⚠️  Working directory non pulito, auto-stash..."
    git stash push -m "Auto-recovery stash $(date)"
fi

# Tentativo pull con fallback
echo "🔄 Tentativo pull automatico..."

if git pull origin "$(git branch --show-current)"; then
    echo "✅ Pull completato con successo"
    
    # Ripristina stash se presente
    if git stash list | grep -q "Auto-recovery stash"; then
        echo "📂 Ripristino stash automatico..."
        git stash pop
    fi
else
    echo "❌ Pull fallito, tentativo con rebase..."
    
    if git pull --rebase origin "$(git branch --show-current)"; then
        echo "✅ Pull con rebase completato"
    else
        echo "❌ Tutti i tentativi falliti"
        echo "Intervento manuale necessario"
        git status
    fi
fi
```

## 📊 Analytics e Monitoraggio

### Script Statistiche Sync

```bash
#!/bin/bash
# sync-stats.sh - Statistiche sincronizzazione

echo "📊 STATISTICHE SINCRONIZZAZIONE"
echo "================================"

# Ultimo pull
last_pull=$(git reflog | grep "pull" | head -1 | cut -d' ' -f4-)
echo "🕐 Ultimo pull: $last_pull"

# Commit non pushati
unpushed=$(git rev-list --count @{u}..HEAD 2>/dev/null || echo "0")
echo "📤 Commit da pushare: $unpushed"

# Commit non pullati
unpulled=$(git rev-list --count HEAD..@{u} 2>/dev/null || echo "0")
echo "📥 Commit da pullare: $unpulled"

# Branch tracking info
echo -e "\n🌿 Tracking status:"
git for-each-ref --format='%(refname:short) -> %(upstream:short)' refs/heads

# Dimensione repository
echo -e "\n💾 Dimensione repository:"
du -sh .git/

# Ultimi 5 fetch
echo -e "\n📡 Ultimi fetch:"
git reflog | grep "fetch" | head -5

# Conflitti risolti recentemente
echo -e "\n⚔️  Merge commit recenti (possibili conflitti risolti):"
git log --merges --oneline -5
```

## 💡 Tips Produttività

### Alias Utili per Pull

```bash
# Setup alias per operazioni pull comuni
git config --global alias.up 'pull --rebase'
git config --global alias.sync '!f() { git stash; git pull; git stash pop; }; f'
git config --global alias.catchup 'log --oneline HEAD..@{u}'

# Utilizzo
git up              # pull con rebase
git sync            # pull con auto-stash
git catchup         # vedere cosa c'è da pullare
```

### Configurazioni Ottimali

```bash
# Configurazioni consigliate per team
git config --global pull.rebase true          # Usa sempre rebase
git config --global rebase.autoStash true     # Auto-stash durante rebase
git config --global fetch.prune true          # Pulisci reference obsoleti
git config --global merge.conflictStyle diff3 # Mostra ancestor nei conflitti
```

## 🔄 Prossimi Passi

Dopo aver masterizzato pull e sincronizzazione:

1. **[04-Remote-Management](./04-remote-management.md)** - Gestione remote complessa
2. **[../18-Collaborazione-Base](../18-Collaborazione-Base/README.md)** - Workflow collaborativi avanzati
3. **[../15-Risoluzione-Conflitti](../15-Risoluzione-Conflitti/README.md)** - Gestione conflitti avanzata

## 📚 Risorse Aggiuntive

- [Git Pull Documentation](https://git-scm.com/docs/git-pull)
- [Git Fetch vs Pull](https://www.atlassian.com/git/tutorials/syncing/git-fetch)
- [Merge vs Rebase](https://www.atlassian.com/git/tutorials/merging-vs-rebasing)
