# Esercizio 3: Gestione Sicura della Navigazione Git

## Obiettivo
Sviluppare competenze professionali nella navigazione sicura di repository Git, implementando strategie di backup, recovery e automazione per prevenire perdite di dati e gestire efficacemente situazioni di emergenza.

## Prerequisiti
- Conoscenza avanzata dei comandi di navigazione Git
- Comprensione del detached HEAD e dei suoi rischi
- Familiarità con git reflog e tecniche di recovery
- Esperienza con scripting bash (base)

## Durata Stimata
⏱️ **100 minuti**

## Scenario
Sei il **Chief Technology Officer** di **SafeCode Solutions**, una software house che gestisce progetti critici per clienti enterprise. Il team ha subito diverse perdite di codice negli ultimi mesi a causa di navigazione Git non sicura. Il tuo compito è implementare un sistema completo di navigazione sicura che includa:

1. **Strategie di Backup Automatico** prima di operazioni rischiose
2. **Sistema di Checkpoint** per salvare stati di lavoro
3. **Procedure di Emergency Recovery** per situazioni critiche
4. **Automazione della Sicurezza** con script e hook personalizzati
5. **Training del Team** su best practices

## Setup dell'Ambiente Sicuro

### Creazione del Repository di Training

```bash
# Crea il repository per il training sulla sicurezza
mkdir safecode-navigation
cd safecode-navigation
git init

# Setup struttura progetto enterprise
mkdir -p {src/{frontend,backend,shared},tests,docs,scripts,backups}
touch README.md .gitignore

# Progetto iniziale: Sistema di gestione clienti
cat > README.md << 'EOF'
# SafeCode Client Management System

## Architecture
- Frontend: React/TypeScript
- Backend: Node.js/Express
- Database: PostgreSQL
- Testing: Jest/Cypress

## Critical Features
- Customer data management
- Payment processing
- Security compliance (GDPR)
- Real-time notifications

## Development Guidelines
- Never work directly on main
- Always create checkpoints before major changes
- Use safe navigation practices
- Backup before risky operations
EOF

cat > .gitignore << 'EOF'
node_modules/
dist/
.env
.DS_Store
*.log
coverage/
.nyc_output/
backups/local/
EOF

# Frontend base
cat > src/frontend/App.tsx << 'EOF'
import React, { useState, useEffect } from 'react';
import CustomerList from './components/CustomerList';
import PaymentProcessor from './components/PaymentProcessor';

interface Customer {
  id: string;
  name: string;
  email: string;
  status: 'active' | 'inactive';
  totalValue: number;
}

const App: React.FC = () => {
  const [customers, setCustomers] = useState<Customer[]>([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    fetchCustomers();
  }, []);

  const fetchCustomers = async () => {
    try {
      const response = await fetch('/api/customers');
      const data = await response.json();
      setCustomers(data);
    } catch (error) {
      console.error('Failed to fetch customers:', error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="app">
      <header>
        <h1>SafeCode Client Management</h1>
      </header>
      <main>
        {loading ? (
          <div>Loading customers...</div>
        ) : (
          <>
            <CustomerList customers={customers} />
            <PaymentProcessor />
          </>
        )}
      </main>
    </div>
  );
};

export default App;
EOF

# Backend base
cat > src/backend/server.js << 'EOF'
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const rateLimit = require('express-rate-limit');

const app = express();
const PORT = process.env.PORT || 3000;

// Security middleware
app.use(helmet());
app.use(cors());
app.use(express.json({ limit: '10mb' }));

// Rate limiting
const limiter = rateLimit({
  windowMs: 15 * 60 * 1000, // 15 minutes
  max: 100 // limit each IP to 100 requests per windowMs
});
app.use('/api/', limiter);

// Routes
app.get('/api/customers', async (req, res) => {
  try {
    // Simulated database call
    const customers = [
      { id: '1', name: 'Acme Corp', email: 'contact@acme.com', status: 'active', totalValue: 150000 },
      { id: '2', name: 'TechStart Inc', email: 'hello@techstart.com', status: 'active', totalValue: 75000 },
      { id: '3', name: 'Global Solutions', email: 'info@global.com', status: 'inactive', totalValue: 0 }
    ];
    res.json(customers);
  } catch (error) {
    console.error('Database error:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});

app.post('/api/customers', async (req, res) => {
  try {
    const { name, email } = req.body;
    
    if (!name || !email) {
      return res.status(400).json({ error: 'Name and email are required' });
    }

    // Simulated customer creation
    const newCustomer = {
      id: Date.now().toString(),
      name,
      email,
      status: 'active',
      totalValue: 0
    };

    res.status(201).json(newCustomer);
  } catch (error) {
    console.error('Creation error:', error);
    res.status(500).json({ error: 'Failed to create customer' });
  }
});

app.listen(PORT, () => {
  console.log(`SafeCode server running on port ${PORT}`);
});
EOF

# Shared utilities
cat > src/shared/utils.js << 'EOF'
/**
 * SafeCode Shared Utilities
 * Critical functions used across frontend and backend
 */

class DataValidator {
  static validateEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
  }

  static validateCustomerData(customer) {
    const errors = [];

    if (!customer.name || customer.name.length < 2) {
      errors.push('Customer name must be at least 2 characters');
    }

    if (!this.validateEmail(customer.email)) {
      errors.push('Invalid email format');
    }

    if (customer.totalValue < 0) {
      errors.push('Total value cannot be negative');
    }

    return {
      isValid: errors.length === 0,
      errors
    };
  }

  static sanitizeInput(input) {
    if (typeof input !== 'string') return input;
    
    return input
      .trim()
      .replace(/<script.*?>.*?<\/script>/gi, '')
      .replace(/<[^>]*>/g, '');
  }
}

class SecurityManager {
  static generateApiKey() {
    return 'sk_' + Math.random().toString(36).substr(2, 32);
  }

  static hashPassword(password) {
    // In production, use proper hashing library
    return 'hashed_' + Buffer.from(password).toString('base64');
  }

  static validatePermissions(user, action) {
    const permissions = {
      admin: ['read', 'write', 'delete', 'manage'],
      manager: ['read', 'write'],
      user: ['read']
    };

    return permissions[user.role]?.includes(action) || false;
  }
}

module.exports = {
  DataValidator,
  SecurityManager
};
EOF

git add .
git commit -m "Initial SafeCode client management system

- React/TypeScript frontend architecture
- Node.js/Express backend with security middleware
- Shared utilities for validation and security
- Enterprise-grade structure and documentation
- GDPR compliance foundation"

# Feature branch: Payment system
git checkout -b feature/payment-system

cat > src/frontend/components/PaymentProcessor.tsx << 'EOF'
import React, { useState } from 'react';

interface PaymentData {
  customerId: string;
  amount: number;
  currency: string;
  description: string;
}

const PaymentProcessor: React.FC = () => {
  const [paymentData, setPaymentData] = useState<PaymentData>({
    customerId: '',
    amount: 0,
    currency: 'USD',
    description: ''
  });
  const [processing, setProcessing] = useState(false);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setProcessing(true);

    try {
      const response = await fetch('/api/payments', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(paymentData)
      });

      if (!response.ok) {
        throw new Error('Payment processing failed');
      }

      const result = await response.json();
      alert(`Payment processed successfully: ${result.transactionId}`);
      
      // Reset form
      setPaymentData({
        customerId: '',
        amount: 0,
        currency: 'USD',
        description: ''
      });
    } catch (error) {
      console.error('Payment error:', error);
      alert('Payment processing failed. Please try again.');
    } finally {
      setProcessing(false);
    }
  };

  return (
    <div className="payment-processor">
      <h2>Process Payment</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Customer ID:</label>
          <input
            type="text"
            value={paymentData.customerId}
            onChange={(e) => setPaymentData({...paymentData, customerId: e.target.value})}
            required
          />
        </div>
        <div>
          <label>Amount:</label>
          <input
            type="number"
            step="0.01"
            value={paymentData.amount}
            onChange={(e) => setPaymentData({...paymentData, amount: parseFloat(e.target.value)})}
            required
          />
        </div>
        <div>
          <label>Currency:</label>
          <select
            value={paymentData.currency}
            onChange={(e) => setPaymentData({...paymentData, currency: e.target.value})}
          >
            <option value="USD">USD</option>
            <option value="EUR">EUR</option>
            <option value="GBP">GBP</option>
          </select>
        </div>
        <div>
          <label>Description:</label>
          <textarea
            value={paymentData.description}
            onChange={(e) => setPaymentData({...paymentData, description: e.target.value})}
            required
          />
        </div>
        <button type="submit" disabled={processing}>
          {processing ? 'Processing...' : 'Process Payment'}
        </button>
      </form>
    </div>
  );
};

export default PaymentProcessor;
EOF

git add .
git commit -m "Add payment processing component

- React form for payment data entry
- Integration with backend payment API
- Error handling and user feedback
- Currency selection support"

# Critical backend payment logic
cat > src/backend/payment.js << 'EOF'
const crypto = require('crypto');

class PaymentProcessor {
  constructor() {
    this.transactions = new Map();
    this.dailyLimits = new Map();
  }

  async processPayment(paymentData) {
    const { customerId, amount, currency, description } = paymentData;
    
    // Validate payment data
    const validation = this.validatePayment(paymentData);
    if (!validation.isValid) {
      throw new Error(`Validation failed: ${validation.errors.join(', ')}`);
    }

    // Check daily limits
    const today = new Date().toISOString().split('T')[0];
    const dailyKey = `${customerId}_${today}`;
    const currentDaily = this.dailyLimits.get(dailyKey) || 0;
    
    if (currentDaily + amount > 50000) { // $50k daily limit
      throw new Error('Daily transaction limit exceeded');
    }

    // Generate transaction ID
    const transactionId = crypto.randomUUID();
    
    // Simulate payment processing
    const transaction = {
      id: transactionId,
      customerId,
      amount,
      currency,
      description,
      status: 'completed',
      timestamp: new Date().toISOString(),
      confirmationCode: this.generateConfirmationCode()
    };

    // Store transaction
    this.transactions.set(transactionId, transaction);
    
    // Update daily limits
    this.dailyLimits.set(dailyKey, currentDaily + amount);

    return transaction;
  }

  validatePayment(paymentData) {
    const errors = [];
    
    if (!paymentData.customerId) {
      errors.push('Customer ID is required');
    }
    
    if (!paymentData.amount || paymentData.amount <= 0) {
      errors.push('Amount must be positive');
    }
    
    if (paymentData.amount > 100000) {
      errors.push('Amount exceeds maximum transaction limit');
    }
    
    if (!paymentData.description || paymentData.description.length < 5) {
      errors.push('Description must be at least 5 characters');
    }

    return {
      isValid: errors.length === 0,
      errors
    };
  }

  generateConfirmationCode() {
    return 'PAY_' + Math.random().toString(36).substr(2, 12).toUpperCase();
  }

  getTransaction(transactionId) {
    return this.transactions.get(transactionId);
  }

  getDailyTotal(customerId) {
    const today = new Date().toISOString().split('T')[0];
    const dailyKey = `${customerId}_${today}`;
    return this.dailyLimits.get(dailyKey) || 0;
  }
}

module.exports = PaymentProcessor;
EOF

git add .
git commit -m "Implement secure payment processing backend

- PaymentProcessor class with validation
- Daily transaction limits per customer
- Unique transaction ID generation
- Comprehensive error handling
- Transaction history tracking"

# Torna a main e merge
git checkout main
git merge feature/payment-system

# Nuova feature: Dashboard avanzata
git checkout -b feature/advanced-dashboard

cat > src/frontend/components/Dashboard.tsx << 'EOF'
import React, { useState, useEffect } from 'react';

interface DashboardData {
  totalCustomers: number;
  activeCustomers: number;
  totalRevenue: number;
  monthlyGrowth: number;
  recentTransactions: Transaction[];
}

interface Transaction {
  id: string;
  customerId: string;
  amount: number;
  currency: string;
  status: string;
  timestamp: string;
}

const Dashboard: React.FC = () => {
  const [data, setData] = useState<DashboardData | null>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    fetchDashboardData();
    const interval = setInterval(fetchDashboardData, 30000); // Refresh every 30 seconds
    return () => clearInterval(interval);
  }, []);

  const fetchDashboardData = async () => {
    try {
      const response = await fetch('/api/dashboard');
      if (!response.ok) {
        throw new Error('Failed to fetch dashboard data');
      }
      const dashboardData = await response.json();
      setData(dashboardData);
      setError(null);
    } catch (err) {
      setError(err instanceof Error ? err.message : 'Unknown error');
    } finally {
      setLoading(false);
    }
  };

  if (loading) return <div className="loading">Loading dashboard...</div>;
  if (error) return <div className="error">Error: {error}</div>;
  if (!data) return <div className="error">No data available</div>;

  return (
    <div className="dashboard">
      <h1>SafeCode Dashboard</h1>
      
      <div className="metrics-grid">
        <div className="metric-card">
          <h3>Total Customers</h3>
          <p className="metric-value">{data.totalCustomers}</p>
        </div>
        
        <div className="metric-card">
          <h3>Active Customers</h3>
          <p className="metric-value">{data.activeCustomers}</p>
          <p className="metric-subtitle">
            {((data.activeCustomers / data.totalCustomers) * 100).toFixed(1)}% active
          </p>
        </div>
        
        <div className="metric-card">
          <h3>Total Revenue</h3>
          <p className="metric-value">${data.totalRevenue.toLocaleString()}</p>
        </div>
        
        <div className="metric-card">
          <h3>Monthly Growth</h3>
          <p className={`metric-value ${data.monthlyGrowth >= 0 ? 'positive' : 'negative'}`}>
            {data.monthlyGrowth >= 0 ? '+' : ''}{data.monthlyGrowth.toFixed(1)}%
          </p>
        </div>
      </div>

      <div className="recent-transactions">
        <h2>Recent Transactions</h2>
        <table>
          <thead>
            <tr>
              <th>Transaction ID</th>
              <th>Customer</th>
              <th>Amount</th>
              <th>Status</th>
              <th>Date</th>
            </tr>
          </thead>
          <tbody>
            {data.recentTransactions.map(transaction => (
              <tr key={transaction.id}>
                <td>{transaction.id.substring(0, 8)}...</td>
                <td>{transaction.customerId}</td>
                <td>{transaction.currency} {transaction.amount}</td>
                <td className={`status-${transaction.status}`}>
                  {transaction.status}
                </td>
                <td>{new Date(transaction.timestamp).toLocaleDateString()}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );
};

export default Dashboard;
EOF

git add .
git commit -m "Add comprehensive dashboard component

- Real-time metrics display
- Customer and revenue analytics
- Recent transactions table
- Auto-refresh functionality
- Responsive grid layout"

# Ora introduciamo una situazione complessa che richiede navigazione sicura
git checkout main

# Crea script di sicurezza
mkdir scripts
cat > scripts/safe-navigation.sh << 'EOF'
#!/bin/bash

# SafeCode Navigation Safety Scripts
# Prevents data loss during Git operations

set -e  # Exit on any error

BACKUP_DIR="backups"
CHECKPOINT_DIR="$BACKUP_DIR/checkpoints"
EMERGENCY_DIR="$BACKUP_DIR/emergency"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Ensure backup directories exist
mkdir -p "$CHECKPOINT_DIR" "$EMERGENCY_DIR"

log_info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Create checkpoint before dangerous operations
create_checkpoint() {
    local checkpoint_name=${1:-"auto_$(date +%Y%m%d_%H%M%S)"}
    local current_branch=$(git rev-parse --abbrev-ref HEAD)
    local current_commit=$(git rev-parse HEAD)
    
    log_info "Creating checkpoint: $checkpoint_name"
    
    # Create checkpoint file
    cat > "$CHECKPOINT_DIR/$checkpoint_name.checkpoint" << EOL
CHECKPOINT_NAME=$checkpoint_name
CREATED_AT=$(date -Iseconds)
BRANCH=$current_branch
COMMIT=$current_commit
WORKING_DIR_STATUS=$(git status --porcelain | wc -l)
STASH_COUNT=$(git stash list | wc -l)
EOL

    # Backup current working directory if there are changes
    if [ -n "$(git status --porcelain)" ]; then
        log_warning "Working directory has changes, creating stash backup"
        git stash push -m "Checkpoint backup: $checkpoint_name"
        echo "STASH_CREATED=true" >> "$CHECKPOINT_DIR/$checkpoint_name.checkpoint"
    else
        echo "STASH_CREATED=false" >> "$CHECKPOINT_DIR/$checkpoint_name.checkpoint"
    fi
    
    # Create branch backup
    git branch "checkpoint_backup_$(date +%Y%m%d_%H%M%S)" > /dev/null 2>&1 || true
    
    log_info "Checkpoint '$checkpoint_name' created successfully"
    echo "$checkpoint_name"
}

# Safe checkout with automatic backup
safe_checkout() {
    local target=$1
    
    if [ -z "$target" ]; then
        log_error "Target branch/commit not specified"
        return 1
    fi
    
    log_info "Initiating safe checkout to: $target"
    
    # Check if target exists
    if ! git rev-parse --verify "$target" >/dev/null 2>&1; then
        log_error "Target '$target' does not exist"
        return 1
    fi
    
    # Create checkpoint
    local checkpoint=$(create_checkpoint "before_checkout_to_$target")
    
    # Perform checkout
    if git checkout "$target"; then
        log_info "Safe checkout completed successfully"
        log_info "Checkpoint available: $checkpoint"
    else
        log_error "Checkout failed, checkpoint available: $checkpoint"
        return 1
    fi
}

# Emergency backup of current state
emergency_backup() {
    local reason=${1:-"manual_emergency"}
    local timestamp=$(date +%Y%m%d_%H%M%S)
    local backup_name="emergency_${reason}_${timestamp}"
    
    log_warning "Creating emergency backup: $backup_name"
    
    # Create emergency directory for this backup
    local emergency_path="$EMERGENCY_DIR/$backup_name"
    mkdir -p "$emergency_path"
    
    # Backup all files (including untracked)
    rsync -av --exclude='.git' --exclude='node_modules' --exclude='backups' . "$emergency_path/"
    
    # Git information
    cat > "$emergency_path/git_state.info" << EOL
EMERGENCY_BACKUP_NAME=$backup_name
CREATED_AT=$(date -Iseconds)
REASON=$reason
CURRENT_BRANCH=$(git rev-parse --abbrev-ref HEAD)
CURRENT_COMMIT=$(git rev-parse HEAD)
WORKING_DIR_CHANGES=$(git status --porcelain)
RECENT_COMMITS=$(git log --oneline -10)
EOL
    
    # Create git bundle for complete history
    git bundle create "$emergency_path/repository.bundle" --all
    
    log_warning "Emergency backup completed: $emergency_path"
    echo "$backup_name"
}

# Restore from checkpoint
restore_checkpoint() {
    local checkpoint_name=$1
    
    if [ -z "$checkpoint_name" ]; then
        log_error "Checkpoint name not specified"
        list_checkpoints
        return 1
    fi
    
    local checkpoint_file="$CHECKPOINT_DIR/$checkpoint_name.checkpoint"
    
    if [ ! -f "$checkpoint_file" ]; then
        log_error "Checkpoint '$checkpoint_name' not found"
        list_checkpoints
        return 1
    fi
    
    log_warning "Restoring checkpoint: $checkpoint_name"
    
    # Source checkpoint data
    source "$checkpoint_file"
    
    # Create emergency backup before restore
    emergency_backup "before_restore_$checkpoint_name"
    
    # Restore to checkpoint state
    git checkout "$BRANCH"
    git reset --hard "$COMMIT"
    
    # Restore stash if created during checkpoint
    if [ "$STASH_CREATED" = "true" ]; then
        log_info "Restoring stashed changes from checkpoint"
        git stash pop || log_warning "Could not restore stashed changes automatically"
    fi
    
    log_info "Checkpoint '$checkpoint_name' restored successfully"
}

# List available checkpoints
list_checkpoints() {
    log_info "Available checkpoints:"
    
    if [ ! -d "$CHECKPOINT_DIR" ] || [ -z "$(ls -A $CHECKPOINT_DIR)" ]; then
        echo "No checkpoints found."
        return
    fi
    
    for checkpoint in "$CHECKPOINT_DIR"/*.checkpoint; do
        if [ -f "$checkpoint" ]; then
            source "$checkpoint"
            echo "  - $CHECKPOINT_NAME (Branch: $BRANCH, Created: $CREATED_AT)"
        fi
    done
}

# List emergency backups
list_emergency_backups() {
    log_info "Available emergency backups:"
    
    if [ ! -d "$EMERGENCY_DIR" ] || [ -z "$(ls -A $EMERGENCY_DIR)" ]; then
        echo "No emergency backups found."
        return
    fi
    
    for backup in "$EMERGENCY_DIR"/*/; do
        if [ -d "$backup" ]; then
            local info_file="$backup/git_state.info"
            if [ -f "$info_file" ]; then
                source "$info_file"
                echo "  - $EMERGENCY_BACKUP_NAME (Reason: $REASON, Created: $CREATED_AT)"
            fi
        fi
    done
}

# Safe git operations wrapper
safe_operation() {
    local operation=$1
    shift
    
    case $operation in
        "checkout")
            safe_checkout "$@"
            ;;
        "checkpoint")
            create_checkpoint "$@"
            ;;
        "emergency")
            emergency_backup "$@"
            ;;
        "restore")
            restore_checkpoint "$@"
            ;;
        "list-checkpoints")
            list_checkpoints
            ;;
        "list-emergency")
            list_emergency_backups
            ;;
        *)
            echo "Usage: $0 {checkout|checkpoint|emergency|restore|list-checkpoints|list-emergency}"
            echo ""
            echo "Commands:"
            echo "  checkout <target>     - Safe checkout with automatic backup"
            echo "  checkpoint [name]     - Create checkpoint of current state"
            echo "  emergency [reason]    - Create emergency backup"
            echo "  restore <checkpoint>  - Restore from checkpoint"
            echo "  list-checkpoints      - List available checkpoints"
            echo "  list-emergency        - List emergency backups"
            return 1
            ;;
    esac
}

# Run the requested operation
safe_operation "$@"
EOF

chmod +x scripts/safe-navigation.sh

git add scripts/
git commit -m "Add comprehensive safe navigation system

- Automated checkpoint creation before risky operations
- Emergency backup functionality with full state preservation
- Safe checkout wrapper with automatic recovery options
- Comprehensive restore capabilities
- Professional logging and error handling"

echo "SafeCode repository setup completato!"
echo ""
echo "🛡️  SISTEMA DI NAVIGAZIONE SICURA ATTIVO"
echo ""
echo "Comandi disponibili:"
echo "  ./scripts/safe-navigation.sh checkpoint [nome]"
echo "  ./scripts/safe-navigation.sh checkout <target>"
echo "  ./scripts/safe-navigation.sh emergency [reason]"
echo "  ./scripts/safe-navigation.sh restore <checkpoint>"
echo "  ./scripts/safe-navigation.sh list-checkpoints"
echo "  ./scripts/safe-navigation.sh list-emergency"
```

## Parte 1: Implementazione Sistema di Checkpoint (25 minuti)

### Compito 1.1: Test del Sistema di Sicurezza
Testa il sistema di navigazione sicura:

```bash
# Crea un checkpoint iniziale
./scripts/safe-navigation.sh checkpoint "initial_state"

# Verifica il checkpoint
./scripts/safe-navigation.sh list-checkpoints

# Fai alcune modifiche non committate
echo "// Test modification" >> src/backend/server.js
echo "console.log('Test change');" >> src/frontend/App.tsx

# Crea un checkpoint con modifiche
./scripts/safe-navigation.sh checkpoint "with_modifications"
```

**Attività:**
1. Analizza la struttura dei file di checkpoint creati
2. Verifica che le modifiche non committate vengano gestite correttamente
3. Testa il sistema di backup branch automatico

### Compito 1.2: Navigazione Sicura tra Branch
Usa il sistema sicuro per navigare tra i branch:

```bash
# Naviga al branch feature usando il sistema sicuro
./scripts/safe-navigation.sh checkout feature/payment-system

# Verifica lo stato
git status
git log --oneline -5

# Naviga a un commit specifico
./scripts/safe-navigation.sh checkout HEAD~2

# Analizza lo stato detached HEAD
git status
```

**Domande:**
1. Che differenza noti tra il checkout sicuro e quello normale?
2. Quali informazioni vengono salvate nel checkpoint?
3. Come gestisce il sistema il detached HEAD?

## Parte 2: Scenari di Emergency Recovery (30 minuti)

### Compito 2.1: Simulazione di Emergenza - Perdita di Codice
Simula una situazione di emergenza e testa il recovery:

```bash
# Crea modifiche importanti
cat >> src/shared/utils.js << 'EOF'

class EmergencyRecoveryTester {
  static criticalFunction() {
    // IMPORTANT: This code took 3 hours to write
    // Complex algorithm for customer risk assessment
    const riskFactors = ['payment_history', 'credit_score', 'business_volume'];
    
    return riskFactors.reduce((risk, factor) => {
      const weight = this.calculateWeight(factor);
      return risk + (weight * this.getFactorValue(factor));
    }, 0);
  }
  
  static calculateWeight(factor) {
    const weights = {
      'payment_history': 0.4,
      'credit_score': 0.35,
      'business_volume': 0.25
    };
    return weights[factor] || 0;
  }
}
EOF

# Crea checkpoint prima di operazione rischiosa
./scripts/safe-navigation.sh checkpoint "before_dangerous_operation"

# Simula operazione che va male (reset hard accidentale)
git add .
git commit -m "Add critical risk assessment algorithm"

# OOPS! Reset accidentale che elimina tutto
git reset --hard HEAD~5

# Verifica che il codice sia perso
cat src/shared/utils.js | grep -i "EmergencyRecoveryTester" || echo "CODICE PERSO!"
```

### Compito 2.2: Procedura di Recovery
Usa il sistema per recuperare il codice perso:

```bash
# Lista dei checkpoint disponibili
./scripts/safe-navigation.sh list-checkpoints

# Ripristina il checkpoint
./scripts/safe-navigation.sh restore "before_dangerous_operation"

# Verifica il recupero
cat src/shared/utils.js | grep -i "EmergencyRecoveryTester"
git log --oneline -3
```

**Attività:**
1. Documenta i passaggi della procedura di recovery
2. Verifica che tutto il codice sia stato recuperato correttamente
3. Analizza i backup di emergenza creati durante il processo

### Compito 2.3: Gestione di Detached HEAD Complesso
Simula una situazione complessa di detached HEAD:

```bash
# Vai in detached HEAD
git checkout HEAD~3

# Fai modifiche significative
cat > src/frontend/components/EmergencyFeature.tsx << 'EOF'
import React from 'react';

// EMERGENCY FEATURE: Critical customer notification system
// This was developed under pressure during an outage

const EmergencyNotifications: React.FC = () => {
  const [notifications, setNotifications] = React.useState([]);
  
  const sendEmergencyAlert = async (customerId: string, message: string) => {
    try {
      const response = await fetch('/api/emergency-notifications', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ customerId, message, priority: 'HIGH' })
      });
      
      if (response.ok) {
        alert('Emergency notification sent successfully');
      }
    } catch (error) {
      console.error('Failed to send emergency notification:', error);
    }
  };

  return (
    <div className="emergency-notifications">
      <h2>Emergency Customer Notifications</h2>
      <button onClick={() => sendEmergencyAlert('all', 'System maintenance in progress')}>
        Send System Alert
      </button>
    </div>
  );
};

export default EmergencyNotifications;
EOF

# Commit in detached HEAD
git add .
git commit -m "EMERGENCY: Add critical customer notification system

This feature was developed during a production outage
to notify customers about system issues.
MUST NOT BE LOST!"

# Salva l'hash del commit
EMERGENCY_COMMIT=$(git rev-parse HEAD)
echo "Emergency commit: $EMERGENCY_COMMIT"

# Torna al main (simulando la perdita del commit)
git checkout main

# Il commit è ora "orfano"
git log --oneline | grep "EMERGENCY" || echo "COMMIT ORFANO!"
```

### Compito 2.4: Recovery di Commit Orfani
Recupera il commit orfano usando tecniche avanzate:

```bash
# Usa reflog per trovare il commit perso
git reflog | grep "EMERGENCY"

# Crea un emergency backup prima del recovery
./scripts/safe-navigation.sh emergency "orphaned_commit_recovery"

# Recupera il commit orfano creando un branch
git branch recover-emergency-feature $EMERGENCY_COMMIT

# Verifica il recupero
git checkout recover-emergency-feature
cat src/frontend/components/EmergencyFeature.tsx

# Merge il codice recuperato nel main
git checkout main
git merge recover-emergency-feature
```

## Parte 3: Automazione della Sicurezza (25 minuti)

### Compito 3.1: Hook di Sicurezza Automatici
Crea hook Git per automazione della sicurezza:

```bash
# Crea pre-checkout hook
cat > .git/hooks/pre-checkout << 'EOF'
#!/bin/bash
# Automatic safety checkpoint before checkout

# Ottieni informazioni sul checkout
while read oldrev newrev refname; do
    # Crea checkpoint automatico se ci sono modifiche non committate
    if [ -n "$(git status --porcelain)" ]; then
        echo "🛡️  Creating automatic safety checkpoint..."
        ./scripts/safe-navigation.sh checkpoint "auto_pre_checkout_$(date +%H%M%S)"
    fi
done
EOF

chmod +x .git/hooks/pre-checkout

# Crea post-checkout hook per logging
cat > .git/hooks/post-checkout << 'EOF'
#!/bin/bash
# Log checkout operations for audit trail

PREV_HEAD=$1
NEW_HEAD=$2
BRANCH_SWITCH=$3

LOG_FILE="backups/checkout_audit.log"

echo "$(date -Iseconds) - Checkout: $PREV_HEAD -> $NEW_HEAD (Branch switch: $BRANCH_SWITCH)" >> $LOG_FILE

# Verifica se siamo in detached HEAD
if git symbolic-ref HEAD > /dev/null 2>&1; then
    echo "✅ On branch: $(git branch --show-current)"
else
    echo "⚠️  WARNING: You are in detached HEAD state!"
    echo "Current commit: $(git rev-parse HEAD)"
    echo "Use 'git checkout -b <new-branch-name>' to create a branch"
fi
EOF

chmod +x .git/hooks/post-checkout
```

### Compito 3.2: Script di Monitoraggio Continuo
Crea un sistema di monitoraggio per la sicurezza:

```bash
# Script di monitoraggio dello stato Git
cat > scripts/git-health-monitor.sh << 'EOF'
#!/bin/bash

# Git Health Monitor - Continuous safety monitoring

HEALTH_LOG="backups/git_health.log"

check_git_health() {
    local timestamp=$(date -Iseconds)
    local current_branch=$(git branch --show-current)
    local uncommitted_changes=$(git status --porcelain | wc -l)
    local untracked_files=$(git ls-files --others --exclude-standard | wc -l)
    local stash_count=$(git stash list | wc -l)
    local unpushed_commits=$(git log @{u}.. --oneline 2>/dev/null | wc -l || echo "0")
    
    # Controlla stato detached HEAD
    local detached_head="false"
    if ! git symbolic-ref HEAD > /dev/null 2>&1; then
        detached_head="true"
    fi
    
    # Controlla commit recenti senza backup
    local recent_commits_no_backup=$(git log --since="1 hour ago" --oneline | wc -l)
    
    # Genera report
    cat << EOL >> $HEALTH_LOG
{
  "timestamp": "$timestamp",
  "current_branch": "$current_branch",
  "uncommitted_changes": $uncommitted_changes,
  "untracked_files": $untracked_files,
  "stash_count": $stash_count,
  "unpushed_commits": $unpushed_commits,
  "detached_head": $detached_head,
  "recent_commits_no_backup": $recent_commits_no_backup
}
EOL

    # Avvisi di sicurezza
    if [ "$detached_head" = "true" ]; then
        echo "🚨 WARNING: Repository in detached HEAD state!"
    fi
    
    if [ $uncommitted_changes -gt 10 ]; then
        echo "⚠️  Many uncommitted changes ($uncommitted_changes) - consider creating checkpoint"
    fi
    
    if [ $recent_commits_no_backup -gt 5 ]; then
        echo "📋 Consider creating backup - $recent_commits_no_backup recent commits"
    fi
}

# Esegui controllo
check_git_health

# Modalità continua (se richiesta)
if [ "$1" = "--continuous" ]; then
    echo "Starting continuous Git health monitoring..."
    while true; do
        sleep 300  # Ogni 5 minuti
        check_git_health
    done
fi
EOF

chmod +x scripts/git-health-monitor.sh

# Testa il monitoraggio
./scripts/git-health-monitor.sh
```

### Compito 3.3: Dashboard di Sicurezza
Crea un dashboard per visualizzare lo stato della sicurezza:

```bash
# Script per dashboard sicurezza
cat > scripts/safety-dashboard.sh << 'EOF'
#!/bin/bash

# SafeCode Git Safety Dashboard

clear
echo "🛡️  SAFECODE GIT SAFETY DASHBOARD"
echo "=================================="
echo ""

# Stato corrente
echo "📊 CURRENT STATUS"
echo "-----------------"
if git symbolic-ref HEAD > /dev/null 2>&1; then
    echo "✅ Branch: $(git branch --show-current)"
else
    echo "🚨 DETACHED HEAD: $(git rev-parse --short HEAD)"
fi

echo "📝 Uncommitted changes: $(git status --porcelain | wc -l)"
echo "📁 Untracked files: $(git ls-files --others --exclude-standard | wc -l)"
echo "📚 Stash entries: $(git stash list | wc -l)"
echo ""

# Checkpoint status
echo "💾 CHECKPOINT STATUS"
echo "--------------------"
if [ -d "backups/checkpoints" ]; then
    local checkpoint_count=$(ls backups/checkpoints/*.checkpoint 2>/dev/null | wc -l)
    echo "Available checkpoints: $checkpoint_count"
    
    if [ $checkpoint_count -gt 0 ]; then
        echo "Latest checkpoint:"
        ls -t backups/checkpoints/*.checkpoint | head -1 | xargs basename | sed 's/.checkpoint$//'
    fi
else
    echo "No checkpoints found"
fi
echo ""

# Emergency backups
echo "🚨 EMERGENCY BACKUPS"
echo "--------------------"
if [ -d "backups/emergency" ]; then
    local emergency_count=$(ls backups/emergency/ 2>/dev/null | wc -l)
    echo "Emergency backups: $emergency_count"
    
    if [ $emergency_count -gt 0 ]; then
        echo "Latest emergency backup:"
        ls -t backups/emergency/ | head -1
    fi
else
    echo "No emergency backups found"
fi
echo ""

# Sicurezza recente
echo "🔍 RECENT ACTIVITY"
echo "------------------"
echo "Recent commits:"
git log --oneline -5
echo ""

# Raccomandazioni
echo "💡 RECOMMENDATIONS"
echo "------------------"
local recommendations=0

if [ -n "$(git status --porcelain)" ]; then
    echo "• Consider creating checkpoint (uncommitted changes detected)"
    recommendations=$((recommendations + 1))
fi

if ! git symbolic-ref HEAD > /dev/null 2>&1; then
    echo "• WARNING: Create branch from detached HEAD state"
    recommendations=$((recommendations + 1))
fi

local recent_commits=$(git log --since="2 hours ago" --oneline | wc -l)
if [ $recent_commits -gt 3 ]; then
    echo "• Consider creating backup ($recent_commits recent commits)"
    recommendations=$((recommendations + 1))
fi

if [ $recommendations -eq 0 ]; then
    echo "✅ All good! Repository state is safe."
fi

echo ""
echo "Commands: checkpoint | emergency | restore | list-checkpoints"
EOF

chmod +x scripts/safety-dashboard.sh

# Testa il dashboard
./scripts/safety-dashboard.sh
```

## Parte 4: Training del Team e Best Practices (20 minuti)

### Compito 4.1: Simulazione di Training Scenario
Crea scenari di training per il team:

```bash
# Scenario 1: Sviluppatore junior fa errori comuni
echo "=== TRAINING SCENARIO 1: Junior Developer Mistakes ==="

# Simula errori comuni
git checkout feature/advanced-dashboard
echo "// Buggy code that will cause issues" >> src/frontend/components/Dashboard.tsx

# Invece di creare checkpoint, va direttamente in detached HEAD
git checkout HEAD~2

# Fa modifiche senza sapere che è in detached HEAD
echo "console.log('Important debugging code');" >> src/backend/server.js

# Si accorge del problema troppo tardi
git status

# Usa il sistema di sicurezza per risolvere
echo "📚 LESSON: Always check git status and use safe-navigation"
```

### Compito 4.2: Procedure di Emergenza Documentate
Crea documentazione per le procedure di emergenza:

```bash
cat > docs/EMERGENCY_PROCEDURES.md << 'EOF'
# SafeCode Git Emergency Procedures

## 🚨 Emergency Response Guide

### Immediate Actions for Git Emergencies

#### 1. **STOP AND ASSESS**
- Don't panic or make additional changes
- Run: `git status` to understand current state
- Run: `./scripts/safety-dashboard.sh` for overview

#### 2. **Create Emergency Backup**
```bash
./scripts/safe-navigation.sh emergency "immediate_response"
```

#### 3. **Identify the Problem**
- **Lost commits**: Check `git reflog`
- **Detached HEAD**: Look for uncommitted changes
- **Wrong branch**: Verify with `git branch -v`
- **Merge conflicts**: Use `git status` for details

### Common Emergency Scenarios

#### Scenario A: Accidental Hard Reset
```bash
# 1. Create emergency backup
./scripts/safe-navigation.sh emergency "after_hard_reset"

# 2. Find lost commits in reflog
git reflog

# 3. Restore lost commit
git cherry-pick <lost-commit-hash>
```

#### Scenario B: Stuck in Detached HEAD with Important Changes
```bash
# 1. DO NOT checkout another branch yet
# 2. Create emergency backup
./scripts/safe-navigation.sh emergency "detached_head_rescue"

# 3. Create branch from current position
git checkout -b rescue-branch-$(date +%Y%m%d-%H%M)

# 4. Commit changes
git add .
git commit -m "RESCUE: Important changes from detached HEAD"
```

#### Scenario C: Corrupted Working Directory
```bash
# 1. Emergency backup
./scripts/safe-navigation.sh emergency "corruption_detected"

# 2. Check repository integrity
git fsck

# 3. If needed, restore from recent checkpoint
./scripts/safe-navigation.sh list-checkpoints
./scripts/safe-navigation.sh restore <checkpoint-name>
```

### Prevention Checklist

#### Before Risky Operations:
- [ ] Create checkpoint: `./scripts/safe-navigation.sh checkpoint`
- [ ] Verify clean working directory: `git status`
- [ ] Confirm target exists: `git branch -a | grep target`
- [ ] Use safe navigation: `./scripts/safe-navigation.sh checkout <target>`

#### Daily Safety Habits:
- [ ] Check dashboard: `./scripts/safety-dashboard.sh`
- [ ] Create backup before major changes
- [ ] Never work directly on main branch
- [ ] Regular commits with descriptive messages

### Team Communication Protocol

#### When Emergency Occurs:
1. **Immediately notify team lead**
2. **Do not attempt fixes without consultation**
3. **Document all actions taken**
4. **Share emergency backup location**

#### Emergency Contact List:
- Team Lead: [contact-info]
- Senior Developer: [contact-info]
- DevOps Engineer: [contact-info]

### Recovery Success Verification

After any emergency recovery:
- [ ] All expected files present
- [ ] Code compiles without errors
- [ ] Tests pass
- [ ] Recent commits visible in history
- [ ] Team notified of resolution
EOF

git add docs/
git commit -m "Add comprehensive emergency procedures documentation

- Immediate response protocols
- Common scenario handling
- Prevention checklists
- Team communication procedures
- Recovery verification steps"
```

### Compito 4.3: Test di Competenza del Team
Crea un test pratico per verificare le competenze del team:

```bash
cat > scripts/team-competency-test.sh << 'EOF'
#!/bin/bash

# SafeCode Team Git Safety Competency Test

echo "🎓 SAFECODE GIT SAFETY COMPETENCY TEST"
echo "====================================="
echo ""

SCORE=0
TOTAL_QUESTIONS=0

ask_question() {
    local question="$1"
    local correct_answer="$2"
    local explanation="$3"
    
    TOTAL_QUESTIONS=$((TOTAL_QUESTIONS + 1))
    
    echo "Question $TOTAL_QUESTIONS: $question"
    read -p "Your answer: " user_answer
    
    if [ "$user_answer" = "$correct_answer" ]; then
        echo "✅ Correct!"
        SCORE=$((SCORE + 1))
    else
        echo "❌ Incorrect. Correct answer: $correct_answer"
        echo "💡 Explanation: $explanation"
    fi
    echo ""
}

practical_test() {
    local test_name="$1"
    local instructions="$2"
    
    echo "🔧 PRACTICAL TEST: $test_name"
    echo "Instructions: $instructions"
    echo "Press Enter when completed..."
    read
}

echo "This test covers Git safety procedures and best practices."
echo "You will be asked both theoretical and practical questions."
echo ""

# Theoretical Questions
ask_question \
    "What should you do FIRST when you realize you're in detached HEAD?" \
    "stop" \
    "Always stop and assess the situation before making any changes."

ask_question \
    "Which command creates a safety checkpoint?" \
    "./scripts/safe-navigation.sh checkpoint" \
    "Our safety system requires using the safe-navigation script."

ask_question \
    "What Git command shows lost commits?" \
    "git reflog" \
    "Reflog maintains a record of all HEAD movements."

ask_question \
    "Should you work directly on the main branch?" \
    "no" \
    "Always work on feature branches to protect main."

# Practical Tests
practical_test \
    "Create Safety Checkpoint" \
    "Create a checkpoint named 'competency-test' using our safety system."

practical_test \
    "Emergency Backup" \
    "Create an emergency backup with reason 'training-exercise'."

practical_test \
    "Safe Navigation" \
    "Use safe navigation to checkout the feature/payment-system branch."

# Results
echo "🏆 TEST RESULTS"
echo "==============="
echo "Score: $SCORE / $TOTAL_QUESTIONS"

PERCENTAGE=$((SCORE * 100 / TOTAL_QUESTIONS))

if [ $PERCENTAGE -ge 80 ]; then
    echo "🎉 EXCELLENT! You are qualified to work independently with Git."
elif [ $PERCENTAGE -ge 60 ]; then
    echo "👍 GOOD! You understand the basics but review emergency procedures."
else
    echo "📚 NEEDS IMPROVEMENT! Please review documentation and retake test."
fi

echo ""
echo "📋 Recommendations based on your score:"
if [ $PERCENTAGE -lt 80 ]; then
    echo "• Review emergency procedures documentation"
    echo "• Practice with safe-navigation scripts daily"
    echo "• Work with a senior developer on risky operations"
fi

echo "• Always use checkpoints before major changes"
echo "• Run safety dashboard at least once daily"
echo "• Never skip safety procedures under pressure"
EOF

chmod +x scripts/team-competency-test.sh

# Esegui il test
echo "Test creato! Esegui con: ./scripts/team-competency-test.sh"
```

## Consegna

### 1. Sistema di Sicurezza Implementato
Documenta il sistema completo che hai implementato:

#### A. Componenti del Sistema
- **Script di navigazione sicura** con tutte le funzionalità
- **Sistema di checkpoint** automatico e manuale
- **Emergency backup** con preservazione completa dello stato
- **Hook Git** per automazione della sicurezza
- **Dashboard di monitoraggio** per visibilità continua

#### B. Documentazione delle Procedure
- **Guida alle procedure di emergenza** completa
- **Checklist di prevenzione** per operazioni quotidiane
- **Protocolli di comunicazione** per situazioni critiche
- **Test di competenza** per validazione delle skills del team

### 2. Report di Testing
Crea un documento `safe_navigation_testing_report.md`:

#### A. Test Eseguiti
- **Test di checkpoint** con e senza modifiche
- **Simulazione di emergenze** e procedure di recovery
- **Validazione degli hook** automatici
- **Test del dashboard** e monitoraggio

#### B. Scenari di Recovery Testati
- **Hard reset accidentale** e recupero tramite reflog
- **Detached HEAD con modifiche critiche** e rescue
- **Commit orfani** e tecniche di recupero
- **Corruzione del working directory** e restore

#### C. Metriche di Sicurezza
- **Tempo di recovery** per diversi tipi di emergenza
- **Percentuale di successo** nel recupero dei dati
- **Facilità d'uso** del sistema di sicurezza
- **Efficacia della prevenzione** tramite automazione

### 3. Script di Automazione Finale
Crea uno script master `setup-safe-environment.sh`:

```bash
#!/bin/bash
# Master setup script for SafeCode navigation safety

echo "🛡️  Setting up SafeCode Safe Navigation Environment"

# Crea tutte le directory necessarie
mkdir -p backups/{checkpoints,emergency}

# Installa gli hook
cp scripts/hooks/* .git/hooks/ 2>/dev/null || echo "No hooks to install"

# Configura alias Git utili
git config alias.safe-checkout "!./scripts/safe-navigation.sh checkout"
git config alias.checkpoint "!./scripts/safe-navigation.sh checkpoint"
git config alias.emergency "!./scripts/safe-navigation.sh emergency"
git config alias.dashboard "!./scripts/safety-dashboard.sh"

# Crea cron job per monitoraggio (opzionale)
echo "0 */6 * * * cd $(pwd) && ./scripts/git-health-monitor.sh" | crontab -

echo "✅ Safe navigation environment setup complete!"
echo ""
echo "Available commands:"
echo "  git checkpoint [name]"
echo "  git safe-checkout <target>"
echo "  git emergency [reason]"
echo "  git dashboard"
```

### 4. Criteri di Valutazione

#### A. Funzionalità (40%)
- **Completezza del sistema** di sicurezza implementato
- **Robustezza** delle procedure di backup e recovery
- **Efficacia** dell'automazione e dei controlli

#### B. Sicurezza (30%)
- **Prevenzione** efficace della perdita di dati
- **Recovery capabilities** per diversi scenari di emergenza
- **Validation** dell'integrità dei backup

#### C. Usabilità (20%)
- **Facilità d'uso** del sistema per il team
- **Chiarezza** della documentazione e procedure
- **Integrazione** fluida nel workflow esistente

#### D. Professionalità (10%)
- **Qualità** del codice e degli script
- **Documentazione** completa e professionale
- **Best practices** seguiti nell'implementazione

## Risorse Aggiuntive

### Pattern di Sicurezza Git Avanzati
```bash
# Pattern 1: Checkpoint automatico basato su tempo
git config alias.auto-checkpoint "!if [ $(($(date +%s) - $(stat -c %Y .git/refs/heads/$(git branch --show-current) 2>/dev/null || echo 0))) -gt 3600 ]; then ./scripts/safe-navigation.sh checkpoint auto_hourly_$(date +%H%M); fi"

# Pattern 2: Backup condizionale
git config alias.smart-checkout "!f() { if [ -n \"$(git status --porcelain)\" ]; then ./scripts/safe-navigation.sh checkpoint before_checkout_$1; fi; git checkout $1; }; f"

# Pattern 3: Emergency alias
git config alias.panic "!./scripts/safe-navigation.sh emergency panic_$(date +%Y%m%d_%H%M%S)"
```

### Integrazione con IDE e Tools
- **VS Code extensions** per integrazione Git safety
- **Git hooks** per IDE-triggered checkpoints
- **CI/CD integration** per automated safety checks

---

## Note per l'Istruttore

### Obiettivi Pedagogici
- **Mastery** delle tecniche di sicurezza Git avanzate
- **Prevenzione** proattiva delle perdite di dati
- **Recovery skills** per situazioni di emergenza critiche
- **Team leadership** nella gestione della sicurezza del codice

### Varianti dell'Esercizio
- **Enterprise Version**: Integrazione con sistemi di backup aziendali
- **Team Simulation**: Scenari multi-developer con conflitti
- **CI/CD Integration**: Automazione della sicurezza nella pipeline

### Estensioni Avanzate
- **Distributed backup** con repository remoti multipli
- **Blockchain-based** integrity verification
- **AI-powered** risk assessment per operazioni Git

---

*[⬅️ Esercizio Precedente](02-detective-bug.md) | [🏠 Home Modulo](../README.md) | [➡️ Modulo Successivo](../../10-Branch-e-Merge/README.md)*
