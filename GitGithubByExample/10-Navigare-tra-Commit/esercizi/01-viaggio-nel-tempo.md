# Esercizio 1: Viaggio nel Tempo con Git

## Obiettivo
Imparare a navigare efficacemente nella cronologia di un progetto utilizzando le tecniche di time travel di Git per esplorare l'evoluzione del codice e comprendere le decisioni di sviluppo.

## Prerequisiti
- Conoscenza base dei comandi Git
- Comprensione dei concetti di commit e branch
- Familiarità con git log e git show

## Durata Stimata
⏱️ **90 minuti**

## Scenario
Sei un nuovo sviluppatore che si è unito al team di **TimeMachine Analytics**, una startup che sviluppa software per l'analisi predittiva. Il progetto principale è una libreria Python chiamata `PredictorLib` che ha subito molte evoluzioni negli ultimi 6 mesi. Il tuo compito è esplorare la cronologia del progetto per comprendere l'architettura attuale e le decisioni prese dal team.

## Setup dell'Ambiente

### Creazione del Repository di Test

```bash
# Crea il repository di esempio
mkdir predictor-lib-history
cd predictor-lib-history
git init

# Crea la struttura iniziale
mkdir -p src/{core,utils,models} tests docs
touch README.md requirements.txt setup.py

# Commit iniziale
echo "# PredictorLib - Advanced Analytics Library" > README.md
echo "numpy>=1.20.0" > requirements.txt
git add .
git commit -m "Initial project structure

- Set up basic Python package structure
- Added initial dependencies
- Created core module directories"

# Sviluppo Fase 1: Core Engine (2 mesi fa)
cat > src/core/engine.py << 'EOF'
"""Core prediction engine."""

class PredictionEngine:
    def __init__(self):
        self.models = []
        self.data = None
    
    def load_data(self, data):
        """Load training data."""
        self.data = data
        print(f"Loaded {len(data)} records")
    
    def predict(self, input_data):
        """Basic prediction method."""
        return {"prediction": "default", "confidence": 0.5}
EOF

git add src/core/engine.py
git commit -m "Add basic prediction engine

- Implemented PredictionEngine class
- Added data loading functionality
- Basic prediction interface
- Foundation for future ML models"

# Fase 2: Utilities (6 settimane fa)
cat > src/utils/data_processor.py << 'EOF'
"""Data processing utilities."""
import json

class DataProcessor:
    @staticmethod
    def clean_data(raw_data):
        """Clean and normalize data."""
        cleaned = []
        for item in raw_data:
            if item and isinstance(item, dict):
                cleaned.append(item)
        return cleaned
    
    @staticmethod
    def export_json(data, filename):
        """Export data to JSON format."""
        with open(filename, 'w') as f:
            json.dump(data, f, indent=2)
EOF

git add src/utils/data_processor.py
git commit -m "Add data processing utilities

- Implemented DataProcessor class
- Data cleaning and validation
- JSON export functionality
- Improved data pipeline"

# Fase 3: Primo Modello ML (5 settimane fa)
cat > src/models/linear_model.py << 'EOF'
"""Linear regression model implementation."""

class LinearModel:
    def __init__(self):
        self.coefficients = []
        self.intercept = 0
        self.trained = False
    
    def train(self, X, y):
        """Train the linear model."""
        # Simplified training logic
        self.coefficients = [0.5] * len(X[0])
        self.intercept = 0.1
        self.trained = True
        return {"mse": 0.15, "r2": 0.85}
    
    def predict(self, X):
        """Make predictions."""
        if not self.trained:
            raise ValueError("Model not trained")
        
        predictions = []
        for x in X:
            pred = self.intercept + sum(c * v for c, v in zip(self.coefficients, x))
            predictions.append(pred)
        return predictions
EOF

# Aggiorna engine per usare i modelli
cat > src/core/engine.py << 'EOF'
"""Core prediction engine."""
from ..models.linear_model import LinearModel

class PredictionEngine:
    def __init__(self):
        self.models = {"linear": LinearModel()}
        self.data = None
        self.active_model = None
    
    def load_data(self, data):
        """Load training data."""
        self.data = data
        print(f"Loaded {len(data)} records")
    
    def train_model(self, model_type, X, y):
        """Train specified model."""
        if model_type in self.models:
            result = self.models[model_type].train(X, y)
            self.active_model = model_type
            return result
        raise ValueError(f"Unknown model type: {model_type}")
    
    def predict(self, input_data):
        """Make predictions using active model."""
        if not self.active_model:
            return {"prediction": "default", "confidence": 0.5}
        
        model = self.models[self.active_model]
        predictions = model.predict(input_data)
        return {"predictions": predictions, "model": self.active_model}
EOF

git add .
git commit -m "Integrate linear regression model

- Added LinearModel implementation
- Enhanced PredictionEngine with model management
- Training and prediction pipeline
- Model selection functionality"

# Fase 4: Bug Fix Critico (4 settimane fa)
cat > src/models/linear_model.py << 'EOF'
"""Linear regression model implementation."""

class LinearModel:
    def __init__(self):
        self.coefficients = []
        self.intercept = 0
        self.trained = False
    
    def train(self, X, y):
        """Train the linear model."""
        if not X or not y:
            raise ValueError("Training data cannot be empty")
        
        if len(X) != len(y):
            raise ValueError("X and y must have same length")
        
        # Simplified training logic
        self.coefficients = [0.5] * len(X[0]) if X else []
        self.intercept = 0.1
        self.trained = True
        return {"mse": 0.15, "r2": 0.85}
    
    def predict(self, X):
        """Make predictions."""
        if not self.trained:
            raise ValueError("Model not trained")
        
        if not X:
            return []
        
        predictions = []
        for x in X:
            if len(x) != len(self.coefficients):
                raise ValueError("Input dimension mismatch")
            pred = self.intercept + sum(c * v for c, v in zip(self.coefficients, x))
            predictions.append(pred)
        return predictions
EOF

git add src/models/linear_model.py
git commit -m "HOTFIX: Fix critical validation bugs

- Add input validation for training data
- Fix dimension mismatch errors
- Prevent crashes with empty data
- Improve error messages

Fixes #23 - Production crashes with malformed data"

# Fase 5: Feature Avanzate (3 settimane fa)
cat > src/models/neural_model.py << 'EOF'
"""Neural network model implementation."""

class NeuralModel:
    def __init__(self, layers=[10, 5, 1]):
        self.layers = layers
        self.weights = []
        self.trained = False
        self.epochs = 0
    
    def train(self, X, y, epochs=100):
        """Train the neural network."""
        if not X or not y:
            raise ValueError("Training data cannot be empty")
        
        # Initialize weights (simplified)
        self.weights = [[0.1] * self.layers[i] for i in range(len(self.layers))]
        
        # Simulated training
        for epoch in range(epochs):
            # Training logic here
            pass
        
        self.trained = True
        self.epochs = epochs
        return {"loss": 0.05, "accuracy": 0.92, "epochs": epochs}
    
    def predict(self, X):
        """Make predictions using neural network."""
        if not self.trained:
            raise ValueError("Model not trained")
        
        predictions = []
        for x in X:
            # Simplified neural network forward pass
            output = sum(x) * 0.1 + 0.2  # Dummy calculation
            predictions.append(output)
        return predictions
    
    def get_model_info(self):
        """Get model architecture information."""
        return {
            "type": "neural_network",
            "layers": self.layers,
            "trained": self.trained,
            "epochs": self.epochs
        }
EOF

# Aggiorna engine per supportare neural model
cat >> src/core/engine.py << 'EOF'

    def add_model(self, name, model):
        """Add a new model to the engine."""
        self.models[name] = model
        print(f"Added model: {name}")
    
    def list_models(self):
        """List all available models."""
        return list(self.models.keys())
    
    def get_model_info(self, model_type):
        """Get information about a specific model."""
        if model_type in self.models:
            model = self.models[model_type]
            if hasattr(model, 'get_model_info'):
                return model.get_model_info()
            return {"type": model_type, "trained": getattr(model, 'trained', False)}
        return None
EOF

git add .
git commit -m "Add neural network model support

- Implemented NeuralModel class
- Advanced training with epochs
- Model architecture configuration
- Enhanced engine with model management
- Model information and statistics"

# Fase 6: Performance Optimization (2 settimane fa)
cat > src/utils/performance.py << 'EOF'
"""Performance optimization utilities."""
import time
from functools import wraps

def timing_decorator(func):
    """Decorator to measure function execution time."""
    @wraps(func)
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        execution_time = end_time - start_time
        print(f"{func.__name__} executed in {execution_time:.4f} seconds")
        return result
    return wrapper

class PerformanceMonitor:
    def __init__(self):
        self.metrics = {}
    
    def start_timer(self, operation):
        """Start timing an operation."""
        self.metrics[operation] = {"start": time.time()}
    
    def end_timer(self, operation):
        """End timing and record duration."""
        if operation in self.metrics:
            end_time = time.time()
            duration = end_time - self.metrics[operation]["start"]
            self.metrics[operation]["duration"] = duration
            return duration
        return None
    
    def get_report(self):
        """Generate performance report."""
        report = {}
        for op, data in self.metrics.items():
            if "duration" in data:
                report[op] = data["duration"]
        return report
EOF

git add src/utils/performance.py
git commit -m "Add performance monitoring utilities

- Timing decorator for function profiling
- PerformanceMonitor class for operation tracking
- Execution time measurement
- Performance reporting system"

# Fase 7: Bug Fix e Refactoring (1 settimana fa)
cat > src/core/engine.py << 'EOF'
"""Core prediction engine."""
from ..models.linear_model import LinearModel
from ..utils.performance import timing_decorator, PerformanceMonitor

class PredictionEngine:
    def __init__(self):
        self.models = {"linear": LinearModel()}
        self.data = None
        self.active_model = None
        self.performance_monitor = PerformanceMonitor()
    
    def load_data(self, data):
        """Load training data."""
        self.data = data
        print(f"Loaded {len(data)} records")
    
    @timing_decorator
    def train_model(self, model_type, X, y, **kwargs):
        """Train specified model."""
        if model_type not in self.models:
            raise ValueError(f"Unknown model type: {model_type}")
        
        self.performance_monitor.start_timer(f"training_{model_type}")
        result = self.models[model_type].train(X, y, **kwargs)
        self.performance_monitor.end_timer(f"training_{model_type}")
        
        self.active_model = model_type
        return result
    
    @timing_decorator
    def predict(self, input_data):
        """Make predictions using active model."""
        if not self.active_model:
            return {"prediction": "default", "confidence": 0.5}
        
        model = self.models[self.active_model]
        predictions = model.predict(input_data)
        return {"predictions": predictions, "model": self.active_model}
    
    def add_model(self, name, model):
        """Add a new model to the engine."""
        self.models[name] = model
        print(f"Added model: {name}")
    
    def list_models(self):
        """List all available models."""
        return list(self.models.keys())
    
    def get_model_info(self, model_type):
        """Get information about a specific model."""
        if model_type in self.models:
            model = self.models[model_type]
            if hasattr(model, 'get_model_info'):
                return model.get_model_info()
            return {"type": model_type, "trained": getattr(model, 'trained', False)}
        return None
    
    def get_performance_report(self):
        """Get performance metrics report."""
        return self.performance_monitor.get_report()
EOF

git add src/core/engine.py
git commit -m "Refactor engine with performance monitoring

- Integrated PerformanceMonitor into engine
- Added timing decorators to critical methods
- Enhanced error handling
- Performance tracking for training and prediction"

# Fase 8: Documentazione e Test (Ieri)
cat > docs/api_reference.md << 'EOF'
# PredictorLib API Reference

## Core Classes

### PredictionEngine
Main engine for managing prediction models.

#### Methods
- `load_data(data)`: Load training data
- `train_model(model_type, X, y, **kwargs)`: Train a model
- `predict(input_data)`: Make predictions
- `add_model(name, model)`: Add custom model
- `get_performance_report()`: Get timing metrics

### Models

#### LinearModel
Basic linear regression implementation.

#### NeuralModel
Neural network with configurable architecture.

## Usage Examples

```python
from src.core.engine import PredictionEngine

# Initialize engine
engine = PredictionEngine()

# Load and train
engine.load_data(training_data)
result = engine.train_model("linear", X, y)

# Make predictions
predictions = engine.predict(test_data)
```
EOF

cat > tests/test_engine.py << 'EOF'
"""Tests for PredictionEngine."""
import unittest
from src.core.engine import PredictionEngine

class TestPredictionEngine(unittest.TestCase):
    def setUp(self):
        self.engine = PredictionEngine()
    
    def test_model_list(self):
        models = self.engine.list_models()
        self.assertIn("linear", models)
    
    def test_load_data(self):
        test_data = [{"x": 1, "y": 2}]
        self.engine.load_data(test_data)
        self.assertEqual(self.engine.data, test_data)
    
    def test_invalid_model(self):
        with self.assertRaises(ValueError):
            self.engine.train_model("invalid", [], [])

if __name__ == "__main__":
    unittest.main()
EOF

git add docs/ tests/
git commit -m "Add comprehensive documentation and tests

- API reference documentation
- Usage examples and best practices
- Unit tests for core functionality
- Test coverage for error cases"

# Tag delle versioni
git tag -a v0.1.0 HEAD~7 -m "Initial release with basic engine"
git tag -a v0.2.0 HEAD~5 -m "Added neural network support"
git tag -a v0.3.0 HEAD~2 -m "Performance optimization release"
git tag -a v1.0.0 HEAD -m "First stable release"

echo "Repository setup completato! Ora puoi iniziare l'esercizio."
```

## Parte 1: Esplorazione della Timeline (30 minuti)

### Compito 1.1: Panoramica Generale
Esplora la cronologia del progetto e rispondi alle seguenti domande:

```bash
# Visualizza la cronologia completa
git log --oneline --graph --all

# Analizza i tag
git tag -l

# Conta i commit per autore (se ci sono più autori)
git shortlog -sn
```

**Domande:**
1. Quanti commit totali ci sono nel progetto?
2. Quali sono le versioni taggate e quando sono state create?
3. Qual è stata l'evoluzione principale dell'architettura?

### Compito 1.2: Analisi delle Fasi di Sviluppo
Identifica le diverse fasi di sviluppo del progetto:

```bash
# Visualizza commit con date
git log --pretty=format:"%h %ad %s" --date=relative

# Cerca commit che introducono nuove funzionalità
git log --grep="Add" --oneline

# Trova i bug fix
git log --grep="fix\|Fix\|HOTFIX" --oneline --all
```

**Attività:**
1. Crea una timeline delle funzionalità principali
2. Identifica i periodi di maggiore attività
3. Trova i commit di bug fix e analizza cosa hanno risolto

## Parte 2: Viaggio nel Tempo Guidato (45 minuti)

### Compito 2.1: Esplorare le Versioni
Naviga attraverso le diverse versioni del progetto:

```bash
# Vai alla versione 0.1.0
git checkout v0.1.0

# Esplora la struttura
find . -name "*.py" | head -10
cat src/core/engine.py

# Vai alla versione 0.2.0
git checkout v0.2.0

# Confronta le differenze
git diff v0.1.0..v0.2.0 --stat
```

**Attività:**
1. Documenta le differenze principali tra le versioni
2. Identifica quando è stato aggiunto il supporto per i neural network
3. Analizza l'evoluzione della classe `PredictionEngine`

### Compito 2.2: Investigazione di Bug Fix
Analizza il bug fix critico:

```bash
# Trova il commit del bug fix
git log --grep="HOTFIX" --oneline

# Esamina le modifiche
git show <commit-hash-hotfix>

# Vai al commit prima del fix
git checkout <commit-hash-hotfix>~1

# Esamina il codice problematico
cat src/models/linear_model.py

# Vai al commit del fix
git checkout <commit-hash-hotfix>

# Confronta le modifiche
git diff HEAD~1 src/models/linear_model.py
```

**Domande:**
1. Quali erano i problemi nel codice originale?
2. Come sono stati risolti?
3. Che tipo di errori avrebbero causato?

### Compito 2.3: Analisi dell'Evoluzione del Codice
Traccia l'evoluzione di un file specifico:

```bash
# Storia completa di engine.py
git log --follow -p src/core/engine.py

# Versioni specifiche del file
git show v0.1.0:src/core/engine.py > engine_v0.1.py
git show v1.0.0:src/core/engine.py > engine_v1.0.py

# Confronta le versioni
diff engine_v0.1.py engine_v1.0.py
```

**Attività:**
1. Conta le linee di codice aggiunte nel tempo
2. Identifica le funzionalità principali aggiunte
3. Analizza come è cambiata la complessità

## Parte 3: Simulazione di Debugging (15 minuti)

### Compito 3.1: Caccia al Bug con Bisect
Simula la ricerca di un bug introdotto durante lo sviluppo:

```bash
# Torna all'ultimo commit
git checkout main

# Supponiamo di aver trovato un bug e di dover trovare quando è stato introdotto
# Inizia bisect tra v0.1.0 e HEAD
git bisect start HEAD v0.1.0

# Il processo di bisect (simulato)
# git bisect bad/good per ogni commit testato
```

**Scenario:** Il team ha scoperto che il metodo `get_performance_report()` non esisteva nelle prime versioni ma è stato aggiunto in seguito. Usa git bisect per trovare esattamente quando è stato introdotto.

### Compito 3.2: Recupero di Codice Perso
Simula il recupero di codice da versioni precedenti:

```bash
# Supponiamo di voler recuperare una versione specifica di un file
git show v0.2.0:src/models/linear_model.py > linear_model_backup.py

# O di voler vedere tutte le versioni di un file
git log --oneline src/models/neural_model.py
```

## Consegna

### Risultati Attesi
Crea un documento `viaggio_nel_tempo_report.md` con:

1. **Timeline del Progetto:**
   - Date e descrizioni delle milestone principali
   - Evoluzione dell'architettura
   - Identificazione dei periodi di sviluppo

2. **Analisi delle Versioni:**
   - Confronto tra v0.1.0, v0.2.0, v0.3.0 e v1.0.0
   - Funzionalità introdotte in ogni versione
   - Metriche di crescita del codice

3. **Investigazione Bug Fix:**
   - Descrizione del problema risolto
   - Analisi del codice prima e dopo il fix
   - Valutazione dell'impatto del bug

4. **Comando Git Utilizzati:**
   - Lista completa dei comandi utilizzati
   - Spiegazione di quando e perché usare ciascuno
   - Alias utili creati durante l'esercizio

### Script di Automazione
Crea uno script `explore_history.sh` che automatizzi l'esplorazione:

```bash
#!/bin/bash
# Script per esplorare automaticamente la cronologia del progetto

echo "=== PREDICTOR LIB HISTORY EXPLORER ==="

echo "1. Panoramica generale:"
git log --oneline --graph | head -20

echo -e "\n2. Versioni rilasciate:"
git tag -l --sort=version:refname

echo -e "\n3. Statistiche sviluppo:"
git log --pretty=format:"%ad" --date=short | sort | uniq -c

echo -e "\n4. Analisi file principali:"
for file in src/core/engine.py src/models/linear_model.py; do
    echo "Storia di $file:"
    git log --oneline --follow $file | head -5
    echo ""
done

echo "Esplorazione completata!"
```

### Criteri di Valutazione
- **Completezza** (30%): Tutti i compiti completati correttamente
- **Analisi** (25%): Qualità dell'analisi della cronologia
- **Comprensione** (25%): Dimostrazione della comprensione dei concetti
- **Documentazione** (20%): Chiarezza e completezza del report

## Risorse Aggiuntive

### Comandi Git Avanzati per Time Travel
```bash
# Visualizzazione cronologia avanzata
git log --graph --pretty=format:'%C(yellow)%h%Creset %C(blue)%ad%Creset %C(green)%s%Creset %C(red)%d%Creset' --date=short

# Ricerca di modifiche specifiche
git log -S "PredictionEngine" --source --all

# Analisi delle modifiche per periodo
git log --since="2 weeks ago" --until="1 week ago" --oneline

# Confronto tra branch o tag
git diff v0.1.0..v1.0.0 --stat
git diff v0.1.0..v1.0.0 --name-only
```

### Pattern di Analisi Cronologia
1. **Panoramica generale**: `git log --oneline --graph`
2. **Dettagli temporali**: `git log --since --until`
3. **Ricerca contenuti**: `git log -S "text" -p`
4. **Analisi file**: `git log --follow file`
5. **Confronti**: `git diff commit1..commit2`

---

## Note per l'Istruttore

### Obiettivi Pedagogici
- Consolidare la comprensione della cronologia Git
- Sviluppare competenze di analisi del codice nel tempo
- Imparare tecniche di debugging temporale
- Praticare la navigazione sicura tra commit

### Varianti dell'Esercizio
- **Versione Semplificata**: Solo timeline e analisi versioni
- **Versione Avanzata**: Aggiungere merge conflict resolution
- **Versione Team**: Simulare contributi di più sviluppatori

### Estensioni Possibili
- Integrazione con strumenti di visualizzazione (gitk, tig)
- Analisi delle performance del codice nel tempo
- Creazione di dashboard automatici per la cronologia

---

*[⬅️ Torna agli Esempi](../esempi/README.md) | [🏠 Home Modulo](../README.md) | [➡️ Prossimo Esercizio](02-detective-bug.md)*
