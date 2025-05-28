# Esercizio 2: Detective Git - Investigazione Forense su Codice

## Obiettivo
Sviluppare competenze avanzate di debugging e investigazione utilizzando Git come strumento forense per identificare, isolare e risolvere bug complessi attraverso l'analisi della cronologia del codice.

## Prerequisiti
- Padronanza dei comandi di navigazione Git
- Conoscenza di git bisect e git blame
- Esperienza con git log e filtri di ricerca
- Comprensione dei concetti di regression testing

## Durata Stimata
⏱️ **120 minuti**

## Scenario
Sei il **Lead Developer** di **SecurePayments Inc.**, una fintech che gestisce transazioni finanziarie critiche. Il sistema di pagamento principale ha iniziato a mostrare comportamenti anomali in produzione:

1. **Bug Critico**: Le transazioni oltre €10.000 falliscono silenziosamente
2. **Performance Issue**: I tempi di risposta sono aumentati del 300%
3. **Data Corruption**: Alcuni record di transazione mostrano importi negativi

Il tuo compito è utilizzare le tecniche di Git forensics per identificare esattamente quando e come questi problemi sono stati introdotti nel sistema.

## Setup dell'Ambiente di Investigazione

### Creazione del Repository con Bug Nascosti

```bash
# Crea il repository del sistema di pagamento
mkdir securepay-forensics
cd securepay-forensics
git init

# Setup iniziale del sistema (6 mesi fa)
mkdir -p src/{core,payment,validation,utils} tests logs
touch README.md requirements.txt

# Sistema iniziale funzionante
cat > src/core/transaction.py << 'EOF'
"""Core transaction processing."""
import uuid
from datetime import datetime

class Transaction:
    def __init__(self, amount, currency="EUR", description=""):
        self.id = str(uuid.uuid4())
        self.amount = float(amount)
        self.currency = currency
        self.description = description
        self.timestamp = datetime.now()
        self.status = "pending"
        self.validated = False
    
    def validate(self):
        """Validate transaction parameters."""
        if self.amount <= 0:
            return False, "Amount must be positive"
        if len(self.description) < 3:
            return False, "Description too short"
        
        self.validated = True
        return True, "Valid transaction"
    
    def process(self):
        """Process the transaction."""
        if not self.validated:
            is_valid, message = self.validate()
            if not is_valid:
                self.status = "failed"
                return False, message
        
        self.status = "completed"
        return True, "Transaction processed successfully"
    
    def to_dict(self):
        """Convert transaction to dictionary."""
        return {
            "id": self.id,
            "amount": self.amount,
            "currency": self.currency,
            "description": self.description,
            "timestamp": self.timestamp.isoformat(),
            "status": self.status,
            "validated": self.validated
        }
EOF

cat > src/payment/processor.py << 'EOF'
"""Payment processing engine."""
from ..core.transaction import Transaction
import time

class PaymentProcessor:
    def __init__(self):
        self.transactions = {}
        self.daily_limit = 50000.0
        self.processed_today = 0.0
    
    def create_transaction(self, amount, currency="EUR", description=""):
        """Create a new transaction."""
        transaction = Transaction(amount, currency, description)
        self.transactions[transaction.id] = transaction
        return transaction
    
    def process_payment(self, transaction_id):
        """Process a payment transaction."""
        if transaction_id not in self.transactions:
            return False, "Transaction not found"
        
        transaction = self.transactions[transaction_id]
        
        # Check daily limit
        if self.processed_today + transaction.amount > self.daily_limit:
            return False, "Daily limit exceeded"
        
        # Process transaction
        success, message = transaction.process()
        if success:
            self.processed_today += transaction.amount
        
        return success, message
    
    def get_transaction_status(self, transaction_id):
        """Get transaction status."""
        if transaction_id in self.transactions:
            return self.transactions[transaction_id].status
        return "not_found"
    
    def get_daily_summary(self):
        """Get daily processing summary."""
        return {
            "processed_amount": self.processed_today,
            "remaining_limit": self.daily_limit - self.processed_today,
            "transaction_count": len(self.transactions)
        }
EOF

git add .
git commit -m "Initial payment system implementation

- Core Transaction class with validation
- PaymentProcessor with daily limits
- Basic transaction lifecycle management
- Comprehensive error handling"

# Sviluppo Fase 1: Validazione Avanzata (5 mesi fa)
cat > src/validation/validator.py << 'EOF'
"""Advanced transaction validation."""
import re

class TransactionValidator:
    def __init__(self):
        self.max_amount = 100000.0
        self.min_amount = 0.01
        self.blocked_patterns = ["test", "fake", "dummy"]
    
    def validate_amount(self, amount):
        """Validate transaction amount."""
        if amount < self.min_amount:
            return False, f"Amount below minimum: {self.min_amount}"
        if amount > self.max_amount:
            return False, f"Amount exceeds maximum: {self.max_amount}"
        return True, "Amount valid"
    
    def validate_description(self, description):
        """Validate transaction description."""
        if len(description) < 3:
            return False, "Description too short"
        
        for pattern in self.blocked_patterns:
            if pattern.lower() in description.lower():
                return False, f"Description contains blocked word: {pattern}"
        
        return True, "Description valid"
    
    def validate_currency(self, currency):
        """Validate currency code."""
        valid_currencies = ["EUR", "USD", "GBP", "JPY"]
        if currency not in valid_currencies:
            return False, f"Unsupported currency: {currency}"
        return True, "Currency valid"
    
    def comprehensive_validation(self, transaction):
        """Perform comprehensive transaction validation."""
        validations = [
            self.validate_amount(transaction.amount),
            self.validate_description(transaction.description),
            self.validate_currency(transaction.currency)
        ]
        
        for is_valid, message in validations:
            if not is_valid:
                return False, message
        
        return True, "All validations passed"
EOF

# Integra validator nel sistema
cat > src/core/transaction.py << 'EOF'
"""Core transaction processing."""
import uuid
from datetime import datetime

class Transaction:
    def __init__(self, amount, currency="EUR", description=""):
        self.id = str(uuid.uuid4())
        self.amount = float(amount)
        self.currency = currency
        self.description = description
        self.timestamp = datetime.now()
        self.status = "pending"
        self.validated = False
        self.validation_errors = []
    
    def validate(self, validator=None):
        """Validate transaction parameters."""
        if validator:
            is_valid, message = validator.comprehensive_validation(self)
            if not is_valid:
                self.validation_errors.append(message)
                return False, message
        else:
            # Basic validation
            if self.amount <= 0:
                return False, "Amount must be positive"
            if len(self.description) < 3:
                return False, "Description too short"
        
        self.validated = True
        return True, "Valid transaction"
    
    def process(self):
        """Process the transaction."""
        if not self.validated:
            is_valid, message = self.validate()
            if not is_valid:
                self.status = "failed"
                return False, message
        
        self.status = "completed"
        return True, "Transaction processed successfully"
    
    def to_dict(self):
        """Convert transaction to dictionary."""
        return {
            "id": self.id,
            "amount": self.amount,
            "currency": self.currency,
            "description": self.description,
            "timestamp": self.timestamp.isoformat(),
            "status": self.status,
            "validated": self.validated,
            "validation_errors": self.validation_errors
        }
EOF

git add .
git commit -m "Add comprehensive transaction validation

- Implemented TransactionValidator class
- Amount, description, and currency validation
- Blocked patterns for fraud prevention
- Enhanced Transaction class with validation errors
- Integrated validation into transaction lifecycle"

# Fase 2: Performance Optimization (4 mesi fa)
cat > src/utils/cache.py << 'EOF'
"""Caching utilities for performance optimization."""
import time
from functools import wraps

class TransactionCache:
    def __init__(self, ttl=300):  # 5 minutes TTL
        self.cache = {}
        self.ttl = ttl
    
    def get(self, key):
        """Get item from cache."""
        if key in self.cache:
            item, timestamp = self.cache[key]
            if time.time() - timestamp < self.ttl:
                return item
            else:
                del self.cache[key]
        return None
    
    def set(self, key, value):
        """Set item in cache."""
        self.cache[key] = (value, time.time())
    
    def clear(self):
        """Clear all cache."""
        self.cache.clear()
    
    def size(self):
        """Get cache size."""
        return len(self.cache)

def cache_result(cache_instance, key_func=None):
    """Decorator for caching function results."""
    def decorator(func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            # Generate cache key
            if key_func:
                cache_key = key_func(*args, **kwargs)
            else:
                cache_key = f"{func.__name__}_{hash(str(args) + str(kwargs))}"
            
            # Try to get from cache
            result = cache_instance.get(cache_key)
            if result is not None:
                return result
            
            # Execute function and cache result
            result = func(*args, **kwargs)
            cache_instance.set(cache_key, result)
            return result
        return wrapper
    return decorator
EOF

# Aggiorna processor per usare cache
cat > src/payment/processor.py << 'EOF'
"""Payment processing engine."""
from ..core.transaction import Transaction
from ..validation.validator import TransactionValidator
from ..utils.cache import TransactionCache, cache_result
import time

class PaymentProcessor:
    def __init__(self):
        self.transactions = {}
        self.daily_limit = 50000.0
        self.processed_today = 0.0
        self.validator = TransactionValidator()
        self.cache = TransactionCache(ttl=600)  # 10 minutes cache
    
    def create_transaction(self, amount, currency="EUR", description=""):
        """Create a new transaction."""
        transaction = Transaction(amount, currency, description)
        self.transactions[transaction.id] = transaction
        return transaction
    
    @cache_result(cache_instance=None)  # Will be set in __init__
    def validate_transaction(self, transaction):
        """Validate transaction with caching."""
        return self.validator.comprehensive_validation(transaction)
    
    def process_payment(self, transaction_id):
        """Process a payment transaction."""
        if transaction_id not in self.transactions:
            return False, "Transaction not found"
        
        transaction = self.transactions[transaction_id]
        
        # Cached validation
        is_valid, validation_message = self.validate_transaction(transaction)
        if not is_valid:
            transaction.status = "failed"
            return False, validation_message
        
        # Check daily limit
        if self.processed_today + transaction.amount > self.daily_limit:
            return False, "Daily limit exceeded"
        
        # Process transaction
        success, message = transaction.process()
        if success:
            self.processed_today += transaction.amount
        
        return success, message
    
    def get_transaction_status(self, transaction_id):
        """Get transaction status."""
        if transaction_id in self.transactions:
            return self.transactions[transaction_id].status
        return "not_found"
    
    def get_daily_summary(self):
        """Get daily processing summary."""
        return {
            "processed_amount": self.processed_today,
            "remaining_limit": self.daily_limit - self.processed_today,
            "transaction_count": len(self.transactions),
            "cache_size": self.cache.size()
        }
    
    def clear_cache(self):
        """Clear transaction cache."""
        self.cache.clear()
EOF

git add .
git commit -m "Implement caching system for performance

- Added TransactionCache class with TTL
- Cache decorator for function results
- Integrated caching into PaymentProcessor
- Validation result caching
- Performance monitoring in daily summary"

# BUG INTRODUCTION 1: Subtle amount handling bug (3 mesi fa)
cat > src/core/transaction.py << 'EOF'
"""Core transaction processing."""
import uuid
from datetime import datetime

class Transaction:
    def __init__(self, amount, currency="EUR", description=""):
        self.id = str(uuid.uuid4())
        # BUG: Integer division for amounts over 10000
        if float(amount) > 10000:
            self.amount = int(amount) // 1  # Truncates decimal places!
        else:
            self.amount = float(amount)
        self.currency = currency
        self.description = description
        self.timestamp = datetime.now()
        self.status = "pending"
        self.validated = False
        self.validation_errors = []
    
    def validate(self, validator=None):
        """Validate transaction parameters."""
        if validator:
            is_valid, message = validator.comprehensive_validation(self)
            if not is_valid:
                self.validation_errors.append(message)
                return False, message
        else:
            # Basic validation
            if self.amount <= 0:
                return False, "Amount must be positive"
            if len(self.description) < 3:
                return False, "Description too short"
        
        self.validated = True
        return True, "Valid transaction"
    
    def process(self):
        """Process the transaction."""
        if not self.validated:
            is_valid, message = self.validate()
            if not is_valid:
                self.status = "failed"
                return False, message
        
        self.status = "completed"
        return True, "Transaction processed successfully"
    
    def to_dict(self):
        """Convert transaction to dictionary."""
        return {
            "id": self.id,
            "amount": self.amount,
            "currency": self.currency,
            "description": self.description,
            "timestamp": self.timestamp.isoformat(),
            "status": self.status,
            "validated": self.validated,
            "validation_errors": self.validation_errors
        }
EOF

git add src/core/transaction.py
git commit -m "Optimize amount handling for large transactions

- Improved handling of amounts over 10,000
- Integer optimization for better performance
- Reduced memory footprint for large amounts"

# Fase 3: Logging System (10 settimane fa)
cat > src/utils/logger.py << 'EOF'
"""Logging utilities for transaction tracking."""
import logging
import json
from datetime import datetime

class TransactionLogger:
    def __init__(self, log_file="transactions.log"):
        self.logger = logging.getLogger("transaction_logger")
        self.logger.setLevel(logging.INFO)
        
        # File handler
        handler = logging.FileHandler(log_file)
        formatter = logging.Formatter(
            '%(asctime)s - %(levelname)s - %(message)s'
        )
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)
    
    def log_transaction(self, transaction, action):
        """Log transaction action."""
        log_data = {
            "action": action,
            "transaction_id": transaction.id,
            "amount": transaction.amount,
            "currency": transaction.currency,
            "status": transaction.status,
            "timestamp": datetime.now().isoformat()
        }
        self.logger.info(json.dumps(log_data))
    
    def log_error(self, transaction_id, error_message):
        """Log transaction error."""
        log_data = {
            "action": "error",
            "transaction_id": transaction_id,
            "error": error_message,
            "timestamp": datetime.now().isoformat()
        }
        self.logger.error(json.dumps(log_data))
    
    def log_performance(self, operation, duration):
        """Log performance metrics."""
        log_data = {
            "action": "performance",
            "operation": operation,
            "duration_ms": duration * 1000,
            "timestamp": datetime.now().isoformat()
        }
        self.logger.info(json.dumps(log_data))
EOF

git add src/utils/logger.py
git commit -m "Add comprehensive logging system

- TransactionLogger for audit trail
- JSON-formatted structured logging
- Performance metrics logging
- Error tracking and reporting"

# BUG INTRODUCTION 2: Performance degradation (8 settimane fa)
cat > src/payment/processor.py << 'EOF'
"""Payment processing engine."""
from ..core.transaction import Transaction
from ..validation.validator import TransactionValidator
from ..utils.cache import TransactionCache, cache_result
from ..utils.logger import TransactionLogger
import time

class PaymentProcessor:
    def __init__(self):
        self.transactions = {}
        self.daily_limit = 50000.0
        self.processed_today = 0.0
        self.validator = TransactionValidator()
        self.cache = TransactionCache(ttl=600)
        self.logger = TransactionLogger()
    
    def create_transaction(self, amount, currency="EUR", description=""):
        """Create a new transaction."""
        transaction = Transaction(amount, currency, description)
        self.transactions[transaction.id] = transaction
        self.logger.log_transaction(transaction, "created")
        return transaction
    
    def validate_transaction(self, transaction):
        """Validate transaction with logging."""
        start_time = time.time()
        
        # BUG: Unnecessary database-like operation simulation
        # This simulates a slow external API call that shouldn't be here
        time.sleep(0.1)  # 100ms delay per validation!
        
        result = self.validator.comprehensive_validation(transaction)
        
        duration = time.time() - start_time
        self.logger.log_performance("validation", duration)
        
        return result
    
    def process_payment(self, transaction_id):
        """Process a payment transaction."""
        start_time = time.time()
        
        if transaction_id not in self.transactions:
            return False, "Transaction not found"
        
        transaction = self.transactions[transaction_id]
        
        # Validation with performance bug
        is_valid, validation_message = self.validate_transaction(transaction)
        if not is_valid:
            transaction.status = "failed"
            self.logger.log_error(transaction_id, validation_message)
            return False, validation_message
        
        # Check daily limit
        if self.processed_today + transaction.amount > self.daily_limit:
            error_msg = "Daily limit exceeded"
            self.logger.log_error(transaction_id, error_msg)
            return False, error_msg
        
        # Process transaction
        success, message = transaction.process()
        if success:
            self.processed_today += transaction.amount
            self.logger.log_transaction(transaction, "processed")
        
        duration = time.time() - start_time
        self.logger.log_performance("process_payment", duration)
        
        return success, message
    
    def get_transaction_status(self, transaction_id):
        """Get transaction status."""
        if transaction_id in self.transactions:
            return self.transactions[transaction_id].status
        return "not_found"
    
    def get_daily_summary(self):
        """Get daily processing summary."""
        return {
            "processed_amount": self.processed_today,
            "remaining_limit": self.daily_limit - self.processed_today,
            "transaction_count": len(self.transactions),
            "cache_size": self.cache.size()
        }
    
    def clear_cache(self):
        """Clear transaction cache."""
        self.cache.clear()
EOF

git add src/payment/processor.py
git commit -m "Integrate comprehensive logging with processing

- Added logging to all transaction operations
- Performance monitoring for validation
- Error tracking with detailed messages
- Enhanced audit trail capabilities"

# BUG INTRODUCTION 3: Data corruption (6 settimane fa)
cat > src/validation/validator.py << 'EOF'
"""Advanced transaction validation."""
import re

class TransactionValidator:
    def __init__(self):
        self.max_amount = 100000.0
        self.min_amount = 0.01
        self.blocked_patterns = ["test", "fake", "dummy"]
    
    def validate_amount(self, amount):
        """Validate transaction amount."""
        # BUG: Negative amounts slip through due to absolute value check
        if abs(amount) < self.min_amount:  # Should be: amount < self.min_amount
            return False, f"Amount below minimum: {self.min_amount}"
        if amount > self.max_amount:
            return False, f"Amount exceeds maximum: {self.max_amount}"
        return True, "Amount valid"
    
    def validate_description(self, description):
        """Validate transaction description."""
        if len(description) < 3:
            return False, "Description too short"
        
        for pattern in self.blocked_patterns:
            if pattern.lower() in description.lower():
                return False, f"Description contains blocked word: {pattern}"
        
        return True, "Description valid"
    
    def validate_currency(self, currency):
        """Validate currency code."""
        valid_currencies = ["EUR", "USD", "GBP", "JPY"]
        if currency not in valid_currencies:
            return False, f"Unsupported currency: {currency}"
        return True, "Currency valid"
    
    def comprehensive_validation(self, transaction):
        """Perform comprehensive transaction validation."""
        validations = [
            self.validate_amount(transaction.amount),
            self.validate_description(transaction.description),
            self.validate_currency(transaction.currency)
        ]
        
        for is_valid, message in validations:
            if not is_valid:
                return False, message
        
        return True, "All validations passed"
EOF

git add src/validation/validator.py
git commit -m "Improve amount validation with edge case handling

- Enhanced validation for edge cases
- Better handling of small amounts
- Improved validation error messages
- Optimized validation performance"

# Fix uno dei bug (4 settimane fa)
cat > src/validation/validator.py << 'EOF'
"""Advanced transaction validation."""
import re

class TransactionValidator:
    def __init__(self):
        self.max_amount = 100000.0
        self.min_amount = 0.01
        self.blocked_patterns = ["test", "fake", "dummy"]
    
    def validate_amount(self, amount):
        """Validate transaction amount."""
        # FIXED: Proper negative amount checking
        if amount < self.min_amount:
            return False, f"Amount below minimum: {self.min_amount}"
        if amount > self.max_amount:
            return False, f"Amount exceeds maximum: {self.max_amount}"
        return True, "Amount valid"
    
    def validate_description(self, description):
        """Validate transaction description."""
        if len(description) < 3:
            return False, "Description too short"
        
        for pattern in self.blocked_patterns:
            if pattern.lower() in description.lower():
                return False, f"Description contains blocked word: {pattern}"
        
        return True, "Description valid"
    
    def validate_currency(self, currency):
        """Validate currency code."""
        valid_currencies = ["EUR", "USD", "GBP", "JPY"]
        if currency not in valid_currencies:
            return False, f"Unsupported currency: {currency}"
        return True, "Currency valid"
    
    def comprehensive_validation(self, transaction):
        """Perform comprehensive transaction validation."""
        validations = [
            self.validate_amount(transaction.amount),
            self.validate_description(transaction.description),
            self.validate_currency(transaction.currency)
        ]
        
        for is_valid, message in validations:
            if not is_valid:
                return False, message
        
        return True, "All validations passed"
EOF

git add src/validation/validator.py
git commit -m "HOTFIX: Fix negative amount validation bug

- Fixed validation allowing negative amounts
- Removed abs() function causing the bug
- Added proper boundary checking
- Enhanced test coverage for edge cases

Fixes critical security issue #CVE-2024-001"

# Aggiungi test per evidenziare i problemi
cat > tests/test_bugs.py << 'EOF'
"""Test suite to demonstrate the discovered bugs."""
import unittest
import time
from src.core.transaction import Transaction
from src.payment.processor import PaymentProcessor
from src.validation.validator import TransactionValidator

class TestBugDemonstration(unittest.TestCase):
    
    def setUp(self):
        self.processor = PaymentProcessor()
        self.validator = TransactionValidator()
    
    def test_large_amount_precision_bug(self):
        """Test that demonstrates the amount precision bug."""
        # This should fail for amounts over 10,000
        large_amount = 15000.99
        transaction = Transaction(large_amount, "EUR", "Large payment")
        
        # The bug causes loss of decimal precision
        self.assertNotEqual(transaction.amount, large_amount)
        self.assertEqual(transaction.amount, 15000)  # Lost the .99
    
    def test_performance_degradation(self):
        """Test that demonstrates the performance issue."""
        transaction = self.processor.create_transaction(1000.0, "EUR", "Test payment")
        
        start_time = time.time()
        self.processor.process_payment(transaction.id)
        duration = time.time() - start_time
        
        # This should be fast but the bug makes it slow
        self.assertGreater(duration, 0.1)  # Takes more than 100ms due to bug
    
    def test_negative_amount_bug_fixed(self):
        """Test that shows the negative amount bug was fixed."""
        # This test would fail before the hotfix
        negative_transaction = Transaction(-1000.0, "EUR", "Negative test")
        is_valid, _ = self.validator.validate_amount(negative_transaction.amount)
        
        # Should properly reject negative amounts now
        self.assertFalse(is_valid)

if __name__ == "__main__":
    unittest.main()
EOF

git add tests/test_bugs.py
git commit -m "Add test suite for bug demonstration

- Tests for amount precision bug
- Performance regression test
- Validation bug verification
- Comprehensive edge case coverage"

# Tag delle versioni per aiutare l'investigazione
git tag -a v1.0.0 HEAD~8 -m "Initial stable release"
git tag -a v1.1.0 HEAD~6 -m "Performance and caching improvements"
git tag -a v1.1.1 HEAD~4 -m "Enhanced logging system"
git tag -a v1.2.0 HEAD~2 -m "Security improvements"
git tag -a v1.2.1 HEAD -m "Hotfix for negative amounts"

echo "Bug repository setup completato!"
echo ""
echo "🔍 MISSIONE: Trova i seguenti bug nel codice:"
echo "1. 💰 Bug di precisione per importi > €10.000"
echo "2. 🐌 Degradazione delle performance (100ms+ per transazione)"
echo "3. ⚠️  Bug validazione importi negativi (ora risolto)"
echo ""
echo "Usa le tecniche di Git forensics per identificare:"
echo "- Quando sono stati introdotti"
echo "- Chi li ha introdotti"
echo "- Quale commit specifico ha causato il problema"
echo "- Come sono stati risolti (se applicabile)"
```

## Parte 1: Setup dell'Investigazione (20 minuti)

### Compito 1.1: Analisi Iniziale
Inizia la tua investigazione con una panoramica del sistema:

```bash
# Panoramica del repository
git log --oneline --graph

# Analizza i tag delle versioni
git tag -l --sort=version:refname

# Identifica i file principali
find src -name "*.py" | head -10

# Cerca riferimenti ai bug nei commit
git log --grep="bug\|fix\|HOTFIX" --oneline
```

**Attività:**
1. Crea una mappa mentale dell'architettura del sistema
2. Identifica i periodi di sviluppo e le versioni
3. Nota i commit di bug fix già presenti

### Compito 1.2: Raccolta delle Prove Iniziali
Esegui i test per confermare la presenza dei bug:

```bash
# Esegui i test che dimostrano i bug
cd securepay-forensics
python3 -m pytest tests/test_bugs.py -v

# Verifica i file coinvolti
git ls-files | grep -E "(transaction|processor|validator)"
```

## Parte 2: Investigazione Bug #1 - Precisione Importi (30 minuti)

### Compito 2.1: Identificazione del Bug di Precisione
Usa git forensics per trovare quando è stato introdotto il bug degli importi:

```bash
# Cerca modifiche al file transaction.py
git log --follow -p src/core/transaction.py

# Cerca riferimenti a "amount" nelle modifiche
git log -S "amount" --source --all src/core/transaction.py

# Analizza i commit che modificano la gestione degli importi
git log --grep="amount\|Amount" --oneline
```

**Domande di Investigazione:**
1. In quale commit specifico è stato introdotto il bug?
2. Qual era la motivazione dichiarata per la modifica?
3. Quale linea di codice specifica causa il problema?

### Compito 2.2: Analisi Dettagliata del Bug
Esamina il commit problematico:

```bash
# Trova il commit esatto
git log --oneline -S "int(amount) // 1"

# Esamina le modifiche in dettaglio
git show <commit-hash>

# Confronta con la versione precedente
git show <commit-hash>~1:src/core/transaction.py > transaction_before.py
git show <commit-hash>:src/core/transaction.py > transaction_after.py
diff transaction_before.py transaction_after.py
```

### Compito 2.3: Impatto Assessment
Determina l'impatto del bug:

```bash
# Controlla se il bug è presente nelle diverse versioni
git checkout v1.0.0
cat src/core/transaction.py | grep -A 5 -B 5 "amount"

git checkout v1.1.0
cat src/core/transaction.py | grep -A 5 -B 5 "amount"

# Torna al commit corrente
git checkout main
```

## Parte 3: Investigazione Bug #2 - Performance (30 minuti)

### Compito 3.1: Caccia al Bug di Performance
Identifica quando è stata introdotta la degradazione delle performance:

```bash
# Cerca modifiche al PaymentProcessor
git log --follow -p src/payment/processor.py

# Cerca introduzione di sleep o delay
git log -S "sleep" --source --all

# Analizza i commit relativi alle performance
git log --grep="performance\|Performance" --oneline
```

### Compito 3.2: Analisi con Git Bisect
Usa git bisect per identificare esattamente quando è stato introdotto il problema:

```bash
# Inizia bisect tra una versione buona e una cattiva
git bisect start HEAD v1.0.0

# Per ogni commit testato, simula il test di performance
# git bisect good/bad basato sul risultato del test
```

**Simulazione Test di Performance:**
```bash
# Script di test per ogni commit durante bisect
#!/bin/bash
echo "Testing commit: $(git rev-parse HEAD)"
grep -q "time.sleep" src/payment/processor.py
if [ $? -eq 0 ]; then
    echo "Performance bug found!"
    exit 1  # git bisect bad
else
    echo "Performance OK"
    exit 0  # git bisect good
fi
```

### Compito 3.3: Root Cause Analysis
Analizza la causa del problema di performance:

```bash
# Esamina il commit che introduce il problema
git show <performance-bug-commit>

# Analizza il contesto della modifica
git show --stat <performance-bug-commit>

# Verifica se ci sono alternative migliori
git log --grep="logging\|Logger" --oneline
```

## Parte 4: Investigazione Bug #3 - Validazione (20 minuti)

### Compito 4.1: Analisi del Bug Risolto
Investiga il bug di validazione che è già stato risolto:

```bash
# Trova il commit di fix
git log --grep="negative\|HOTFIX" --oneline

# Esamina il fix
git show <hotfix-commit>

# Trova quando è stato introdotto il bug originale
git log -S "abs(amount)" --source --all
```

### Compito 4.2: Timeline della Vulnerabilità
Costruisci la timeline del bug di sicurezza:

```bash
# Commit che introduce il bug
git log --oneline -S "abs(amount)"

# Periodo di vulnerabilità
git log --oneline <bug-commit>..<fix-commit>

# Analizza i commit nel periodo vulnerabile
git log --pretty=format:"%h %ad %s" --date=short <bug-commit>..<fix-commit>
```

## Parte 5: Investigazione Forense Avanzata (20 minuti)

### Compito 5.1: Analisi dell'Autore e Blame
Identifica chi ha introdotto i bug:

```bash
# Analizza blame per i file problematici
git blame src/core/transaction.py

# Cerca pattern nei commit dell'autore
git log --author="<author-name>" --oneline

# Analizza le modifiche per periodo
git log --since="3 months ago" --until="2 months ago" --oneline
```

### Compito 5.2: Analisi dei Pattern
Identifica pattern nei bug introdotti:

```bash
# Analizza i giorni della settimana dei commit problematici
git log --pretty=format:"%h %ad %s" --date=format:"%a %Y-%m-%d" <bug-commits>

# Cerca correlazioni temporali
git log --since="3 months ago" --oneline --stat

# Analizza la frequenza dei commit
git log --pretty=format:"%ad" --date=short | sort | uniq -c
```

## Consegna

### Report di Investigazione Forense
Crea un documento `forensic_investigation_report.md` con:

#### 1. Executive Summary
- Riassunto dei bug identificati
- Impatto sul business
- Timeline degli eventi
- Raccomandazioni per la prevenzione

#### 2. Analisi Dettagliata per Ogni Bug

**Bug #1: Precisione Importi**
- Commit di introduzione: `<hash>`
- Data di introduzione: `<data>`
- Autore: `<nome>`
- Descrizione tecnica del problema
- Impatto stimato (transazioni affette)
- Proposta di fix

**Bug #2: Degradazione Performance**
- Commit di introduzione: `<hash>`
- Root cause: `<causa>`
- Impatto misurato: `<tempo-di-risposta>`
- Soluzione proposta

**Bug #3: Validazione Importi Negativi**
- Timeline completa: introduzione → fix
- Periodo di vulnerabilità
- Impatto sulla sicurezza
- Efficacia del fix

#### 3. Comandi Git Utilizzati
```bash
# Lista completa dei comandi utilizzati per l'investigazione
git log --grep="pattern"
git bisect start/good/bad
git blame filename
git show commit-hash
# etc.
```

#### 4. Raccomandazioni per la Prevenzione
- Processi di code review migliorati
- Test automatizzati per regressioni
- Monitoring delle performance in CI/CD
- Security checks automatici

### Script di Investigazione Automatica
Crea uno script `forensic_analysis.sh`:

```bash
#!/bin/bash
# Automated forensic analysis script

echo "=== SECUREPAY FORENSIC ANALYSIS ==="

echo "1. Bug #1 - Amount Precision:"
echo "Commit introducing bug:"
git log --oneline -S "int(amount) // 1" | head -1

echo -e "\n2. Bug #2 - Performance:"
echo "Commit introducing performance issue:"
git log --oneline -S "time.sleep" | head -1

echo -e "\n3. Bug #3 - Negative Amount Validation:"
echo "Bug introduction:"
git log --oneline -S "abs(amount)" | head -1
echo "Bug fix:"
git log --oneline --grep="HOTFIX.*negative" | head -1

echo -e "\n4. Overall Timeline:"
git log --oneline --grep="bug\|fix\|HOTFIX" --reverse

echo -e "\n5. Files Most Affected:"
git log --name-only --pretty=format: | sort | uniq -c | sort -rn | head -10

echo "Analysis complete!"
```

### Criteri di Valutazione
- **Accuratezza** (35%): Identificazione corretta dei bug e commit
- **Metodologia** (25%): Uso appropriato degli strumenti Git forensics
- **Analisi** (20%): Profondità dell'analisi root cause
- **Documentazione** (20%): Chiarezza e completezza del report

## Risorse Aggiuntive

### Comandi Git Forensics Avanzati
```bash
# Ricerca avanzata nei commit
git log -S "keyword" --pickaxe-all
git log -G "regex-pattern"
git log --follow --patch -- filename

# Analisi blame avanzata
git blame -L 10,20 filename
git blame -C -C filename  # Rileva movimenti di codice

# Analisi temporale
git log --since="2 weeks ago" --author="name"
git log --before="2024-01-01" --grep="bug"

# Ricerca in tutti i branch
git log --all --source --grep="pattern"
git log --all -S "code" --source
```

### Pattern di Investigazione
1. **Identificazione**: `git log`, `git grep`, `git blame`
2. **Isolamento**: `git bisect`, `git show`
3. **Analisi**: `git diff`, `git log -p`
4. **Verifica**: checkout di commit specifici
5. **Documentazione**: raccolta di evidenze

---

## Note per l'Istruttore

### Obiettivi Pedagogici
- Padronanza delle tecniche di Git forensics
- Sviluppo di competenze di debugging sistematico
- Comprensione dell'importanza della cronologia del codice
- Esperienza pratica con scenari reali di bug hunting

### Varianti dell'Esercizio
- **Versione Semplificata**: Un solo bug da trovare
- **Versione Avanzata**: Aggiungere merge conflicts e branch complessi
- **Versione Team**: Simulare investigazione collaborativa

### Metriche di Successo
- Identificazione corretta dei commit problematici
- Uso efficace di git bisect
- Analisi accurata della root cause
- Qualità del report finale

---

*[⬅️ Esercizio Precedente](01-viaggio-nel-tempo.md) | [🏠 Home Modulo](../README.md) | [➡️ Prossimo Esercizio](03-gestione-sicura.md)*
