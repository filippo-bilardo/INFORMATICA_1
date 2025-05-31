# 🏋️ Esercizi: Merge e Strategie

## 🎯 Obiettivi di Apprendimento
Al termine di questi esercizi sarai in grado di:
- Eseguire diversi tipi di merge (fast-forward, three-way, squash)
- Gestire e risolvere conflitti di merge
- Scegliere la strategia di merge appropriata per ogni situazione
- Utilizzare strumenti avanzati per la risoluzione di conflitti
- Prevenire conflitti attraverso best practices

---

## 📋 Prerequisiti
- Conoscenza base dei comandi Git
- Comprensione di branch e commit
- Familiarità con editor di testo/IDE
- Git configurato correttamente

---

## 🚀 Esercizio 1: Fast-Forward vs Three-Way Merge
**Difficoltà: ⭐ Principiante**

### Obiettivo
Comprendere la differenza tra fast-forward merge e three-way merge.

### Compiti

#### Parte A: Fast-Forward Merge
1. **Setup Repository**
   ```bash
   mkdir merge-basics
   cd merge-basics
   git init
   git config user.name "Your Name"
   git config user.email "your.email@example.com"
   ```

2. **Crea Contenuto Base**
   ```bash
   echo "# My Project" > README.md
   echo "This is a basic project to learn Git merge" >> README.md
   
   cat > main.py << 'EOF'
   def main():
       print("Hello, World!")

   if __name__ == "__main__":
       main()
   EOF
   
   git add .
   git commit -m "Initial commit: Basic project setup"
   ```

3. **Crea Branch Linear**
   ```bash
   git checkout -b feature/add-functions
   
   # Aggiungi funzioni
   cat >> main.py << 'EOF'

   def greet(name):
       return f"Hello, {name}!"

   def calculate_sum(a, b):
       return a + b
   EOF
   
   git add main.py
   git commit -m "Add: greet and calculate_sum functions"
   
   # Aggiungi documentazione
   cat >> README.md << 'EOF'

   ## Functions
   - `greet(name)`: Returns a greeting message
   - `calculate_sum(a, b)`: Returns the sum of two numbers
   EOF
   
   git add README.md
   git commit -m "Docs: Add function documentation"
   ```

4. **Esegui Fast-Forward Merge**
   ```bash
   git checkout main
   
   # Verifica stato prima del merge
   echo "=== BEFORE MERGE ==="
   git log --oneline --graph --all
   
   # Esegui merge
   git merge feature/add-functions
   
   # Verifica stato dopo il merge
   echo "=== AFTER MERGE ==="
   git log --oneline --graph --all
   ```

#### Parte B: Three-Way Merge
5. **Crea Modifiche Parallele**
   ```bash
   # Crea branch per nuova feature
   git checkout -b feature/add-tests
   
   # Sviluppa test
   cat > test_main.py << 'EOF'
   import main

   def test_greet():
       result = main.greet("Test")
       expected = "Hello, Test!"
       assert result == expected, f"Expected {expected}, got {result}"
       print("✅ test_greet passed")

   def test_calculate_sum():
       result = main.calculate_sum(5, 3)
       assert result == 8, f"Expected 8, got {result}"
       print("✅ test_calculate_sum passed")

   if __name__ == "__main__":
       test_greet()
       test_calculate_sum()
       print("All tests passed!")
   EOF
   
   git add test_main.py
   git commit -m "Add: Unit tests for main functions"
   ```

6. **Modifica Main Branch**
   ```bash
   git checkout main
   
   # Aggiungi configurazione
   cat > config.py << 'EOF'
   # Configuration settings
   DEBUG = True
   VERSION = "1.0.0"
   APP_NAME = "Merge Learning Project"
   EOF
   
   # Aggiorna main.py per usare config
   cat > main.py << 'EOF'
   import config

   def main():
       print(f"Welcome to {config.APP_NAME} v{config.VERSION}")
       if config.DEBUG:
           print("Debug mode is ON")

   def greet(name):
       return f"Hello, {name}!"

   def calculate_sum(a, b):
       return a + b

   if __name__ == "__main__":
       main()
   EOF
   
   git add .
   git commit -m "Add: Configuration system and update main"
   ```

7. **Esegui Three-Way Merge**
   ```bash
   # Verifica divergenza
   echo "=== BEFORE THREE-WAY MERGE ==="
   git log --oneline --graph --all
   
   # Esegui merge
   git merge feature/add-tests -m "Merge: Add testing infrastructure

   This merge combines:
   - Configuration system from main
   - Unit testing from feature branch"
   
   # Verifica risultato
   echo "=== AFTER THREE-WAY MERGE ==="
   git log --oneline --graph --all
   ```

### ✅ Criteri di Successo
- [ ] Fast-forward merge eseguito correttamente
- [ ] Three-way merge con merge commit creato
- [ ] Differenze tra i due tipi comprese
- [ ] Storia Git pulita in entrambi i casi

---

## ⚔️ Esercizio 2: Risoluzione Conflitti Base
**Difficoltà: ⭐⭐ Intermedio**

### Obiettivo
Imparare a riconoscere, analizzare e risolvere conflitti di merge.

### Setup
```bash
mkdir conflict-resolution
cd conflict-resolution
git init
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

### Compiti

#### Parte A: Creazione Conflitto Intenzionale
1. **Progetto Base**
   ```bash
   cat > website.html << 'EOF'
   <!DOCTYPE html>
   <html>
   <head>
       <title>My Website</title>
       <style>
           body { font-family: Arial, sans-serif; }
           .header { background-color: blue; color: white; padding: 20px; }
       </style>
   </head>
   <body>
       <div class="header">
           <h1>Welcome to My Website</h1>
       </div>
       <main>
           <p>This is the main content area.</p>
       </main>
   </body>
   </html>
   EOF
   
   git add website.html
   git commit -m "Initial: Basic website structure"
   ```

2. **Branch A - Design Changes**
   ```bash
   git checkout -b design/modern-theme
   
   # Modifica il design
   cat > website.html << 'EOF'
   <!DOCTYPE html>
   <html>
   <head>
       <title>Modern Website Platform</title>
       <style>
           body { 
               font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
               margin: 0; 
               background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
           }
           .header { 
               background: rgba(255,255,255,0.95); 
               color: #333; 
               padding: 30px; 
               text-align: center;
               box-shadow: 0 2px 10px rgba(0,0,0,0.1);
           }
           .content {
               padding: 40px;
               max-width: 800px;
               margin: 0 auto;
               background: white;
               margin-top: 20px;
               border-radius: 10px;
           }
       </style>
   </head>
   <body>
       <div class="header">
           <h1>Modern Website Platform</h1>
           <p>Experience the future of web design</p>
       </div>
       <main class="content">
           <p>Welcome to our modern, responsive platform designed for the future.</p>
           <button onclick="alert('Welcome!')">Get Started</button>
       </main>
   </body>
   </html>
   EOF
   
   git add website.html
   git commit -m "Design: Modern theme with gradients and shadows"
   ```

3. **Branch B - Content Changes**
   ```bash
   git checkout main
   git checkout -b content/business-focus
   
   # Modifica il contenuto
   cat > website.html << 'EOF'
   <!DOCTYPE html>
   <html>
   <head>
       <title>Business Solutions Hub</title>
       <style>
           body { font-family: Arial, sans-serif; margin: 0; }
           .header { 
               background-color: #2c3e50; 
               color: white; 
               padding: 25px;
               border-bottom: 4px solid #3498db;
           }
           .content {
               padding: 30px;
               line-height: 1.6;
           }
           .services {
               display: flex;
               gap: 20px;
               margin-top: 30px;
           }
           .service-card {
               border: 1px solid #ddd;
               padding: 20px;
               flex: 1;
               border-radius: 5px;
           }
       </style>
   </head>
   <body>
       <div class="header">
           <h1>Business Solutions Hub</h1>
           <p>Professional services for your business needs</p>
       </div>
       <main class="content">
           <h2>Our Services</h2>
           <p>We provide comprehensive business solutions to help your company grow.</p>
           <div class="services">
               <div class="service-card">
                   <h3>Consulting</h3>
                   <p>Expert business advice</p>
               </div>
               <div class="service-card">
                   <h3>Development</h3>
                   <p>Custom software solutions</p>
               </div>
           </div>
       </main>
   </body>
   </html>
   EOF
   
   git add website.html
   git commit -m "Content: Business-focused content and services"
   ```

#### Parte B: Merge e Risoluzione Conflitto
4. **Primo Merge (senza conflitto)**
   ```bash
   git checkout main
   git merge design/modern-theme -m "Merge: Modern design theme"
   ```

5. **Secondo Merge (con conflitto)**
   ```bash
   git merge content/business-focus
   # Questo causerà un conflitto!
   ```

6. **Analisi del Conflitto**
   ```bash
   # Verifica stato
   git status
   
   # Analizza il conflitto
   echo "=== CONFLICT ANALYSIS ==="
   git diff --name-only --diff-filter=U
   
   # Visualizza il conflitto
   cat website.html
   ```

7. **Risoluzione Manuale**
   ```bash
   # Apri website.html nel tuo editor preferito
   # Risolvi il conflitto combinando le migliori caratteristiche
   
   cat > website.html << 'EOF'
   <!DOCTYPE html>
   <html>
   <head>
       <title>Modern Business Solutions</title>
       <style>
           body { 
               font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
               margin: 0; 
               background: linear-gradient(135deg, #2c3e50 0%, #3498db 100%);
           }
           .header { 
               background: rgba(255,255,255,0.95); 
               color: #2c3e50; 
               padding: 30px; 
               text-align: center;
               box-shadow: 0 2px 10px rgba(0,0,0,0.1);
           }
           .content {
               padding: 40px;
               max-width: 1000px;
               margin: 20px auto;
               background: white;
               border-radius: 10px;
               line-height: 1.6;
           }
           .services {
               display: flex;
               gap: 20px;
               margin-top: 30px;
               flex-wrap: wrap;
           }
           .service-card {
               border: 1px solid #ddd;
               padding: 25px;
               flex: 1;
               border-radius: 10px;
               min-width: 250px;
               box-shadow: 0 2px 5px rgba(0,0,0,0.1);
               transition: transform 0.3s ease;
           }
           .service-card:hover {
               transform: translateY(-5px);
           }
           .cta-button {
               background: #3498db;
               color: white;
               border: none;
               padding: 15px 30px;
               border-radius: 25px;
               cursor: pointer;
               font-size: 1.1em;
               margin-top: 20px;
           }
       </style>
   </head>
   <body>
       <div class="header">
           <h1>Modern Business Solutions</h1>
           <p>Professional services with cutting-edge design</p>
       </div>
       <main class="content">
           <h2>Our Services</h2>
           <p>We combine modern technology with professional business expertise to deliver exceptional results.</p>
           <div class="services">
               <div class="service-card">
                   <h3>Consulting</h3>
                   <p>Expert business advice with modern methodologies</p>
               </div>
               <div class="service-card">
                   <h3>Development</h3>
                   <p>Custom software solutions using latest technologies</p>
               </div>
               <div class="service-card">
                   <h3>Design</h3>
                   <p>Modern, responsive design that converts</p>
               </div>
           </div>
           <button class="cta-button" onclick="alert('Contact us for a consultation!')">Get Started</button>
       </main>
   </body>
   </html>
   EOF
   
   # Completa il merge
   git add website.html
   git commit -m "Merge: Resolve conflict combining modern design with business content

   Resolution strategy:
   - Combined modern design aesthetics with business content
   - Merged color schemes harmoniously  
   - Enhanced service cards with hover effects
   - Added professional CTA button
   - Maintained responsive design principles"
   ```

8. **Verifica Risultato**
   ```bash
   # Visualizza storia
   git log --oneline --graph --all
   
   # Testa il risultato
   echo "Open website.html in a browser to verify the merged result"
   ```

### ✅ Criteri di Successo
- [ ] Conflitto riconosciuto e analizzato
- [ ] Risoluzione manuale completata
- [ ] File funzionante dopo merge
- [ ] Commit di merge con messaggio chiaro
- [ ] Storia Git pulita

---

## 🗜️ Esercizio 3: Merge Squash e No-FF
**Difficoltà: ⭐⭐ Intermedio**

### Obiettivo
Padroneggiare le strategie di merge avanzate: squash e no-fast-forward.

### Setup
```bash
mkdir advanced-merge-strategies
cd advanced-merge-strategies
git init
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

### Compiti

#### Parte A: Merge Squash
1. **Progetto API Base**
   ```bash
   cat > api.py << 'EOF'
   from flask import Flask, jsonify

   app = Flask(__name__)

   @app.route('/')
   def home():
       return jsonify({"message": "Welcome to our API", "version": "1.0.0"})

   if __name__ == '__main__':
       app.run(debug=True)
   EOF
   
   cat > requirements.txt << 'EOF'
   Flask==2.3.3
   EOF
   
   git add .
   git commit -m "Initial: Basic Flask API setup"
   ```

2. **Feature Branch con Multiple Commit**
   ```bash
   git checkout -b feature/user-management
   
   # Commit 1: User model
   cat >> api.py << 'EOF'

   # User data (in-memory for demo)
   users = [
       {"id": 1, "name": "Alice", "email": "alice@example.com"},
       {"id": 2, "name": "Bob", "email": "bob@example.com"}
   ]

   @app.route('/users')
   def get_users():
       return jsonify(users)
   EOF
   
   git add api.py
   git commit -m "Add: User model and get users endpoint"
   
   # Commit 2: Get single user
   cat >> api.py << 'EOF'

   @app.route('/users/<int:user_id>')
   def get_user(user_id):
       user = next((u for u in users if u['id'] == user_id), None)
       if user:
           return jsonify(user)
       return jsonify({"error": "User not found"}), 404
   EOF
   
   git add api.py
   git commit -m "Add: Get single user endpoint"
   
   # Commit 3: Create user
   cat >> api.py << 'EOF'

   from flask import request

   @app.route('/users', methods=['POST'])
   def create_user():
       data = request.get_json()
       if not data or 'name' not in data or 'email' not in data:
           return jsonify({"error": "Name and email required"}), 400
       
       new_id = max(u['id'] for u in users) + 1
       new_user = {
           "id": new_id,
           "name": data['name'],
           "email": data['email']
       }
       users.append(new_user)
       return jsonify(new_user), 201
   EOF
   
   git add api.py
   git commit -m "Add: Create user endpoint with validation"
   
   # Commit 4: Error handling
   cat >> api.py << 'EOF'

   @app.errorhandler(404)
   def not_found(error):
       return jsonify({"error": "Resource not found"}), 404

   @app.errorhandler(400)
   def bad_request(error):
       return jsonify({"error": "Bad request"}), 400
   EOF
   
   git add api.py
   git commit -m "Add: Global error handlers"
   
   # Commit 5: Documentation
   cat > README.md << 'EOF'
   # API Documentation

   ## Endpoints

   ### Users
   - `GET /users` - Get all users
   - `GET /users/<id>` - Get user by ID
   - `POST /users` - Create new user

   ### Example Usage
   ```bash
   # Get all users
   curl http://localhost:5000/users

   # Create user
   curl -X POST http://localhost:5000/users \
        -H "Content-Type: application/json" \
        -d '{"name": "Charlie", "email": "charlie@example.com"}'
   ```
   EOF
   
   git add README.md
   git commit -m "Docs: API documentation and usage examples"
   ```

3. **Squash Merge**
   ```bash
   git checkout main
   
   # Visualizza storia del feature branch
   echo "=== FEATURE BRANCH HISTORY ==="
   git log --oneline feature/user-management
   
   # Esegui squash merge
   git merge --squash feature/user-management
   
   # Verifica stato (modifiche staged ma non committate)
   git status
   
   # Crea commit squashed
   git commit -m "Add: Complete user management system

   Features implemented:
   - User model with in-memory storage
   - GET /users endpoint for all users
   - GET /users/<id> endpoint for single user
   - POST /users endpoint for creating users
   - Input validation and error handling
   - Global error handlers for 404/400
   - Complete API documentation

   This squash combines 5 development commits into a single clean feature commit."
   
   # Visualizza risultato
   echo "=== AFTER SQUASH MERGE ==="
   git log --oneline --graph --all
   ```

#### Parte B: No Fast-Forward Merge
4. **Feature Semplice (che normalmente farebbe FF)**
   ```bash
   git checkout -b feature/health-check
   
   # Aggiungi endpoint semplice
   cat >> api.py << 'EOF'

   @app.route('/health')
   def health_check():
       return jsonify({
           "status": "healthy",
           "timestamp": "2024-01-01T00:00:00Z",
           "version": "1.0.0"
       })
   EOF
   
   git add api.py
   git commit -m "Add: Health check endpoint for monitoring"
   ```

5. **No-FF Merge**
   ```bash
   git checkout main
   
   # Verifica che sarebbe fast-forward
   echo "=== WOULD BE FAST-FORWARD ==="
   git log --oneline --graph --all
   
   # Forza merge commit con --no-ff
   git merge --no-ff feature/health-check -m "Merge: Add health check endpoint

   This feature adds monitoring capabilities:
   - /health endpoint for service status
   - Returns timestamp and version info
   - Essential for production monitoring

   Using --no-ff to explicitly track this feature in history."
   
   # Visualizza risultato
   echo "=== AFTER NO-FF MERGE ==="
   git log --oneline --graph --all
   ```

#### Parte C: Confronto Strategie
6. **Analisi Finale**
   ```bash
   echo "=== FINAL PROJECT STRUCTURE ==="
   ls -la
   
   echo "=== COMPLETE GIT HISTORY ==="
   git log --oneline --graph --all
   
   echo "=== STRATEGY COMPARISON ==="
   echo "Squash Merge: 5 commits → 1 clean commit"
   echo "No-FF Merge: 1 commit → explicit merge commit"
   echo "Both preserve feature integration in history"
   ```

### ✅ Criteri di Successo
- [ ] Squash merge eseguito correttamente
- [ ] No-FF merge creato anche per fast-forward
- [ ] Differenze tra strategie comprese
- [ ] API funzionante dopo tutti i merge

---

## 🔥 Esercizio 4: Conflitti Multipli e Avanzati
**Difficoltà: ⭐⭐⭐ Avanzato**

### Obiettivo
Gestire scenari complessi con conflitti multipli e strategie di risoluzione avanzate.

### Setup
```bash
mkdir complex-conflicts
cd complex-conflicts
git init
git config user.name "Your Name"
git config user.email "your.email@example.com"
```

### Compiti

#### Parte A: Progetto Multi-File
1. **Struttura Iniziale**
   ```bash
   mkdir -p src/{models,views,controllers} tests config
   
   # Model base
   cat > src/models/user.py << 'EOF'
   class User:
       def __init__(self, user_id, name, email):
           self.id = user_id
           self.name = name
           self.email = email
       
       def to_dict(self):
           return {
               'id': self.id,
               'name': self.name,
               'email': self.email
           }
   EOF
   
   # Controller base
   cat > src/controllers/user_controller.py << 'EOF'
   from src.models.user import User

   class UserController:
       def __init__(self):
           self.users = []
       
       def get_all_users(self):
           return [user.to_dict() for user in self.users]
   EOF
   
   # Config base
   cat > config/settings.py << 'EOF'
   # Application settings
   DEBUG = True
   HOST = 'localhost'
   PORT = 5000
   DATABASE_URL = 'sqlite:///app.db'
   EOF
   
   git add .
   git commit -m "Initial: Basic MVC structure"
   ```

#### Parte B: Team Development Simulation
2. **Developer 1 - Database Integration**
   ```bash
   git checkout -b dev1/database-integration
   
   # Modifica User model per database
   cat > src/models/user.py << 'EOF'
   from sqlalchemy import Column, Integer, String, create_engine
   from sqlalchemy.ext.declarative import declarative_base
   from sqlalchemy.orm import sessionmaker

   Base = declarative_base()

   class User(Base):
       __tablename__ = 'users'
       
       id = Column(Integer, primary_key=True)
       name = Column(String(100), nullable=False)
       email = Column(String(100), unique=True, nullable=False)
       created_at = Column(String(50))
       
       def to_dict(self):
           return {
               'id': self.id,
               'name': self.name,
               'email': self.email,
               'created_at': self.created_at
           }
   EOF
   
   # Aggiorna controller
   cat > src/controllers/user_controller.py << 'EOF'
   from src.models.user import User, Base
   from sqlalchemy import create_engine
   from sqlalchemy.orm import sessionmaker
   from datetime import datetime

   class UserController:
       def __init__(self, database_url):
           self.engine = create_engine(database_url)
           Base.metadata.create_all(self.engine)
           Session = sessionmaker(bind=self.engine)
           self.session = Session()
       
       def get_all_users(self):
           users = self.session.query(User).all()
           return [user.to_dict() for user in users]
       
       def create_user(self, name, email):
           user = User(name=name, email=email, created_at=datetime.now().isoformat())
           self.session.add(user)
           self.session.commit()
           return user.to_dict()
   EOF
   
   # Aggiorna config
   cat >> config/settings.py << 'EOF'

   # Database settings
   SQLALCHEMY_DATABASE_URI = DATABASE_URL
   SQLALCHEMY_TRACK_MODIFICATIONS = False

   # Security settings
   SECRET_KEY = 'dev-secret-key'
   EOF
   
   git add .
   git commit -m "Add: SQLAlchemy database integration"
   ```

3. **Developer 2 - API Integration**
   ```bash
   git checkout main
   git checkout -b dev2/api-integration
   
   # Modifica User model per API serialization
   cat > src/models/user.py << 'EOF'
   import json
   from datetime import datetime

   class User:
       def __init__(self, user_id, name, email, role='user'):
           self.id = user_id
           self.name = name
           self.email = email
           self.role = role
           self.last_login = None
           self.is_active = True
       
       def to_dict(self):
           return {
               'id': self.id,
               'name': self.name,
               'email': self.email,
               'role': self.role,
               'last_login': self.last_login,
               'is_active': self.is_active
           }
       
       def to_json(self):
           return json.dumps(self.to_dict())
       
       def update_last_login(self):
           self.last_login = datetime.now().isoformat()
   EOF
   
   # Modifica controller per API
   cat > src/controllers/user_controller.py << 'EOF'
   from src.models.user import User
   import json

   class UserController:
       def __init__(self):
           self.users = []
           self.next_id = 1
       
       def get_all_users(self):
           return [user.to_dict() for user in self.users]
       
       def get_user_by_id(self, user_id):
           for user in self.users:
               if user.id == user_id:
                   return user.to_dict()
           return None
       
       def create_user(self, name, email, role='user'):
           user = User(self.next_id, name, email, role)
           self.users.append(user)
           self.next_id += 1
           return user.to_dict()
       
       def authenticate_user(self, user_id):
           for user in self.users:
               if user.id == user_id:
                   user.update_last_login()
                   return True
           return False
   EOF
   
   # Modifica config per API
   cat >> config/settings.py << 'EOF'

   # API settings
   API_VERSION = 'v1'
   CORS_ENABLED = True
   RATE_LIMIT = 100  # requests per minute

   # Authentication
   JWT_SECRET_KEY = 'jwt-secret'
   TOKEN_EXPIRATION = 3600  # seconds
   EOF
   
   git add .
   git commit -m "Add: API integration with authentication"
   ```

4. **Developer 3 - Testing Framework**
   ```bash
   git checkout main
   git checkout -b dev3/testing-framework
   
   # Modifica config per testing
   cat > config/settings.py << 'EOF'
   import os

   # Application settings
   DEBUG = os.getenv('DEBUG', 'True').lower() == 'true'
   HOST = os.getenv('HOST', 'localhost')
   PORT = int(os.getenv('PORT', 5000))
   DATABASE_URL = os.getenv('DATABASE_URL', 'sqlite:///app.db')

   # Testing settings
   TESTING = os.getenv('TESTING', 'False').lower() == 'true'
   TEST_DATABASE_URL = 'sqlite:///:memory:'

   # Logging
   LOG_LEVEL = os.getenv('LOG_LEVEL', 'INFO')
   LOG_FILE = 'app.log'
   EOF
   
   # Aggiungi test per User
   cat > tests/test_user.py << 'EOF'
   import unittest
   from src.models.user import User

   class TestUser(unittest.TestCase):
       def setUp(self):
           self.user = User(1, "Test User", "test@example.com")
       
       def test_user_creation(self):
           self.assertEqual(self.user.id, 1)
           self.assertEqual(self.user.name, "Test User")
           self.assertEqual(self.user.email, "test@example.com")
       
       def test_to_dict(self):
           user_dict = self.user.to_dict()
           self.assertIn('id', user_dict)
           self.assertIn('name', user_dict)
           self.assertIn('email', user_dict)

   if __name__ == '__main__':
       unittest.main()
   EOF
   
   # Test per controller
   cat > tests/test_controller.py << 'EOF'
   import unittest
   from src.controllers.user_controller import UserController

   class TestUserController(unittest.TestCase):
       def setUp(self):
           self.controller = UserController()
       
       def test_get_all_users_empty(self):
           users = self.controller.get_all_users()
           self.assertEqual(len(users), 0)

   if __name__ == '__main__':
       unittest.main()
   EOF
   
   git add .
   git commit -m "Add: Testing framework and initial tests"
   ```

#### Parte C: Merge Complex Conflicts
5. **First Merge (Database)**
   ```bash
   git checkout main
   git merge dev1/database-integration -m "Merge: Database integration"
   ```

6. **Second Merge (API) - Conflicts Expected**
   ```bash
   if git merge dev2/api-integration; then
       echo "No conflicts (unexpected)"
   else
       echo "=== CONFLICTS IN API MERGE ==="
       git status
       
       # Risolvi conflitti in User model
       cat > src/models/user.py << 'EOF'
   from sqlalchemy import Column, Integer, String, DateTime, Boolean, create_engine
   from sqlalchemy.ext.declarative import declarative_base
   from sqlalchemy.orm import sessionmaker
   from datetime import datetime
   import json

   Base = declarative_base()

   class User(Base):
       __tablename__ = 'users'
       
       id = Column(Integer, primary_key=True)
       name = Column(String(100), nullable=False)
       email = Column(String(100), unique=True, nullable=False)
       role = Column(String(50), default='user')
       created_at = Column(DateTime, default=datetime.utcnow)
       last_login = Column(DateTime)
       is_active = Column(Boolean, default=True)
       
       def to_dict(self):
           return {
               'id': self.id,
               'name': self.name,
               'email': self.email,
               'role': self.role,
               'created_at': self.created_at.isoformat() if self.created_at else None,
               'last_login': self.last_login.isoformat() if self.last_login else None,
               'is_active': self.is_active
           }
       
       def to_json(self):
           return json.dumps(self.to_dict())
       
       def update_last_login(self):
           self.last_login = datetime.utcnow()
   EOF
       
       # Risolvi conflitti in Controller
       cat > src/controllers/user_controller.py << 'EOF'
   from src.models.user import User, Base
   from sqlalchemy import create_engine
   from sqlalchemy.orm import sessionmaker
   from datetime import datetime

   class UserController:
       def __init__(self, database_url):
           self.engine = create_engine(database_url)
           Base.metadata.create_all(self.engine)
           Session = sessionmaker(bind=self.engine)
           self.session = Session()
       
       def get_all_users(self):
           users = self.session.query(User).all()
           return [user.to_dict() for user in users]
       
       def get_user_by_id(self, user_id):
           user = self.session.query(User).filter(User.id == user_id).first()
           return user.to_dict() if user else None
       
       def create_user(self, name, email, role='user'):
           user = User(name=name, email=email, role=role)
           self.session.add(user)
           self.session.commit()
           return user.to_dict()
       
       def authenticate_user(self, user_id):
           user = self.session.query(User).filter(User.id == user_id).first()
           if user:
               user.update_last_login()
               self.session.commit()
               return True
           return False
   EOF
       
       git add .
       git commit -m "Merge: Resolve conflicts combining database and API features

       Resolution strategy:
       - Combined SQLAlchemy ORM with API serialization
       - Merged authentication features with database persistence
       - Preserved both role-based access and database timestamps
       - Maintained backward compatibility for both systems"
   fi
   ```

7. **Third Merge (Testing) - More Conflicts**
   ```bash
   if git merge dev3/testing-framework; then
       echo "Testing merge successful"
   else
       echo "=== CONFLICTS IN TESTING MERGE ==="
       
       # Risolvi config conflicts
       cat > config/settings.py << 'EOF'
   import os

   # Application settings
   DEBUG = os.getenv('DEBUG', 'True').lower() == 'true'
   HOST = os.getenv('HOST', 'localhost')
   PORT = int(os.getenv('PORT', 5000))
   DATABASE_URL = os.getenv('DATABASE_URL', 'sqlite:///app.db')

   # Database settings
   SQLALCHEMY_DATABASE_URI = DATABASE_URL
   SQLALCHEMY_TRACK_MODIFICATIONS = False

   # Security settings
   SECRET_KEY = os.getenv('SECRET_KEY', 'dev-secret-key')

   # API settings
   API_VERSION = 'v1'
   CORS_ENABLED = True
   RATE_LIMIT = 100  # requests per minute

   # Authentication
   JWT_SECRET_KEY = os.getenv('JWT_SECRET_KEY', 'jwt-secret')
   TOKEN_EXPIRATION = 3600  # seconds

   # Testing settings
   TESTING = os.getenv('TESTING', 'False').lower() == 'true'
   TEST_DATABASE_URL = 'sqlite:///:memory:'

   # Logging
   LOG_LEVEL = os.getenv('LOG_LEVEL', 'INFO')
   LOG_FILE = 'app.log'
   EOF
       
       # Aggiorna test per nuova struttura
       cat > tests/test_user.py << 'EOF'
   import unittest
   from src.models.user import User, Base
   from sqlalchemy import create_engine
   from sqlalchemy.orm import sessionmaker

   class TestUser(unittest.TestCase):
       def setUp(self):
           # Setup in-memory database for testing
           self.engine = create_engine('sqlite:///:memory:')
           Base.metadata.create_all(self.engine)
           Session = sessionmaker(bind=self.engine)
           self.session = Session()
       
       def test_user_creation(self):
           user = User(name="Test User", email="test@example.com")
           self.session.add(user)
           self.session.commit()
           
           self.assertEqual(user.name, "Test User")
           self.assertEqual(user.email, "test@example.com")
           self.assertEqual(user.role, "user")  # default role
       
       def test_to_dict(self):
           user = User(name="Test User", email="test@example.com")
           user_dict = user.to_dict()
           self.assertIn('id', user_dict)
           self.assertIn('name', user_dict)
           self.assertIn('email', user_dict)
           self.assertIn('role', user_dict)

   if __name__ == '__main__':
       unittest.main()
   EOF
       
       cat > tests/test_controller.py << 'EOF'
   import unittest
   from src.controllers.user_controller import UserController

   class TestUserController(unittest.TestCase):
       def setUp(self):
           self.controller = UserController('sqlite:///:memory:')
       
       def test_create_and_get_user(self):
           # Create user
           user_data = self.controller.create_user("Test User", "test@example.com")
           self.assertIsNotNone(user_data['id'])
           
           # Get user
           retrieved = self.controller.get_user_by_id(user_data['id'])
           self.assertEqual(retrieved['name'], "Test User")

   if __name__ == '__main__':
       unittest.main()
   EOF
       
       git add .
       git commit -m "Merge: Resolve testing conflicts with integrated system

       Resolution:
       - Unified configuration system with environment variables
       - Updated tests to work with SQLAlchemy models
       - Maintained testing isolation with in-memory database
       - Preserved all API, database, and testing functionality"
   fi
   ```

#### Parte D: Verification and Cleanup
8. **Final Verification**
   ```bash
   echo "=== FINAL PROJECT STRUCTURE ==="
   find . -type f -name "*.py" | head -10
   
   echo "=== COMPLETE MERGE HISTORY ==="
   git log --oneline --graph --all
   
   echo "=== CONFLICT RESOLUTION SUMMARY ==="
   echo "✅ Database + API integration resolved"
   echo "✅ Configuration conflicts unified"
   echo "✅ Testing framework integrated"
   echo "✅ All systems working together"
   ```

### ✅ Criteri di Successo
- [ ] Conflitti multipli risolti sistematicamente
- [ ] Architettura integrata funzionante
- [ ] Test compatibili con sistema integrato
- [ ] Storia Git che mostra evoluzione complessa
- [ ] Configurazione unificata per tutti i sistemi

---

## 🎯 Progetto Finale: Sistema di Merge Avanzato
**Difficoltà: ⭐⭐⭐⭐⭐ Master**

### Obiettivo
Implementare un workflow completo di merge in un progetto reale con team simulato.

### Scenario
Stai lavorando su un e-commerce con un team di 4 sviluppatori. Ogni dev lavora su feature diverse che si intersecano.

### Team Roles
- **Frontend Dev**: UI/UX e React components
- **Backend Dev**: API e business logic
- **DevOps**: CI/CD e infrastructure
- **QA**: Testing e quality assurance

### Compiti
1. **Setup progetto e-commerce base**
2. **Sviluppo parallelo di 4 feature che si intersecano**
3. **Gestione conflitti realistici**
4. **Integration testing**
5. **Release preparation**

### Deliverable
- Repository con storia complessa ma pulita
- Tutti i conflitti risolti correttamente
- Sistema funzionante end-to-end
- Documentazione del processo di merge

---

## 📚 Risorse Aggiuntive

### Strumenti di Merge
```bash
# Configurazione merge tools
git config --global merge.tool vscode
git config --global merge.tool meld
git config --global merge.tool kdiff3

# Per usare merge tool
git mergetool
```

### Best Practices per Merge
1. **Prima del Merge**
   - Pull dell'ultimo stato
   - Review delle modifiche
   - Test locali

2. **Durante Conflitti**
   - Analizza prima di risolvere
   - Testa dopo ogni risoluzione
   - Documenta decisioni complesse

3. **Dopo il Merge**
   - Verifica funzionalità
   - Run test suite
   - Update documentazione

### Debugging Merge Issues
```bash
# Visualizza conflitti
git diff --name-only --diff-filter=U

# Storia del merge
git log --merge

# Annulla merge in corso
git merge --abort

# Reset dopo merge sbagliato
git reset --hard HEAD~1
```

---

*🏆 Completa tutti gli esercizi per diventare un esperto di merge Git!*
