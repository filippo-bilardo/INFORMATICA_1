 # Esempio 2: Setup .gitignore per Progetto Python

## Scenario
Configureremo un progetto Python Django completo con gestione di ambienti virtuali, database e file di configurazione.

## Setup Iniziale

### 1. Creazione Struttura Progetto
```bash
# Creiamo la struttura del progetto
mkdir python-blog
cd python-blog

# Inizializziamo Git
git init

# Creiamo la struttura base
mkdir -p {src,tests,docs,scripts,config}
mkdir -p src/{blog,users,core}
mkdir -p static/{css,js,images}
mkdir -p media/uploads
mkdir -p logs
```

### 2. File .gitignore Completo per Python
```bash
# Creiamo il .gitignore per Python/Django
cat > .gitignore << 'EOF'
# Byte-compiled / optimized / DLL files
__pycache__/
*.py[cod]
*$py.class

# C extensions
*.so

# Distribution / packaging
.Python
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
pip-wheel-metadata/
share/python-wheels/
*.egg-info/
.installed.cfg
*.egg
MANIFEST

# PyInstaller
*.manifest
*.spec

# Installer logs
pip-log.txt
pip-delete-this-directory.txt

# Unit test / coverage reports
htmlcov/
.tox/
.nox/
.coverage
.coverage.*
.cache
nosetests.xml
coverage.xml
*.cover
*.py,cover
.hypothesis/
.pytest_cache/

# Translations
*.mo
*.pot

# Django stuff:
*.log
local_settings.py
db.sqlite3
db.sqlite3-journal
media/

# Flask stuff:
instance/
.webassets-cache

# Scrapy stuff:
.scrapy

# Sphinx documentation
docs/_build/

# PyBuilder
target/

# Jupyter Notebook
.ipynb_checkpoints

# IPython
profile_default/
ipython_config.py

# pyenv
.python-version

# pipenv
Pipfile.lock

# PEP 582
__pypackages__/

# Celery stuff
celerybeat-schedule
celerybeat.pid

# SageMath parsed files
*.sage.py

# Environments
.env
.venv
env/
venv/
ENV/
env.bak/
venv.bak/

# Spyder project settings
.spyderproject
.spyproject

# Rope project settings
.ropeproject

# mkdocs documentation
/site

# mypy
.mypy_cache/
.dmypy.json
dmypy.json

# Pyre type checker
.pyre/

# Custom Django settings
# Manteniamo il template ma ignoriamo le configurazioni locali
config/local_settings.py
config/production_settings.py

# Log files
logs/*.log
*.log

# Database backups
*.sql
*.db

# IDE files
.vscode/
.idea/
*.swp
*.swo

# OS generated files
.DS_Store
.DS_Store?
._*
.Spotlight-V100
.Trashes
ehthumbs.db
Thumbs.db

# SSL certificates
*.pem
*.key
*.crt

# Media files (development)
media/uploads/*
!media/uploads/.gitkeep

# Static files compilati
staticfiles/
static/collected/
EOF
```

### 3. File di Configurazione Template
```bash
# Creiamo file di configurazione template
cat > config/settings_template.py << 'EOF'
"""
Template di configurazione Django
Copia questo file come local_settings.py e personalizza i valori
"""

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'your-secret-key-here'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True

ALLOWED_HOSTS = ['localhost', '127.0.0.1']

# Database
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql',
        'NAME': 'your_db_name',
        'USER': 'your_db_user',
        'PASSWORD': 'your_db_password',
        'HOST': 'localhost',
        'PORT': '5432',
    }
}

# Email settings
EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'
EMAIL_HOST = 'smtp.gmail.com'
EMAIL_PORT = 587
EMAIL_USE_TLS = True
EMAIL_HOST_USER = 'your-email@gmail.com'
EMAIL_HOST_PASSWORD = 'your-app-password'

# Media files
MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')

# Static files
STATIC_URL = '/static/'
STATIC_ROOT = os.path.join(BASE_DIR, 'staticfiles')
EOF

# Creiamo un file .env template
cat > .env.template << 'EOF'
# Django Settings
SECRET_KEY=your-secret-key-here
DEBUG=True
ALLOWED_HOSTS=localhost,127.0.0.1

# Database Configuration
DB_NAME=blog_db
DB_USER=blog_user
DB_PASSWORD=secure_password
DB_HOST=localhost
DB_PORT=5432

# Email Configuration
EMAIL_HOST=smtp.gmail.com
EMAIL_PORT=587
EMAIL_USE_TLS=True
EMAIL_HOST_USER=your-email@example.com
EMAIL_HOST_PASSWORD=your-app-password

# Redis (for caching)
REDIS_URL=redis://localhost:6379/0

# File Upload Settings
MAX_UPLOAD_SIZE=5242880  # 5MB
ALLOWED_IMAGE_TYPES=jpg,jpeg,png,gif

# API Keys (example)
GOOGLE_ANALYTICS_ID=UA-XXXXXXXX-X
STRIPE_PUBLIC_KEY=pk_test_...
STRIPE_SECRET_KEY=sk_test_...
EOF
```

### 4. Creazione File di Sviluppo
```bash
# Creiamo alcuni file Python di esempio
cat > src/blog/models.py << 'EOF'
from django.db import models
from django.contrib.auth.models import User

class Post(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    author = models.ForeignKey(User, on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)
    
    def __str__(self):
        return self.title
EOF

# Creiamo un file di test
cat > tests/test_models.py << 'EOF'
import pytest
from django.test import TestCase
from django.contrib.auth.models import User
from src.blog.models import Post

class PostModelTest(TestCase):
    def setUp(self):
        self.user = User.objects.create_user(
            username='testuser',
            password='testpass123'
        )
    
    def test_post_creation(self):
        post = Post.objects.create(
            title='Test Post',
            content='This is a test post content',
            author=self.user
        )
        self.assertEqual(post.title, 'Test Post')
        self.assertEqual(post.author, self.user)
EOF

# Creiamo file requirements
cat > requirements.txt << 'EOF'
Django==4.2.7
psycopg2-binary==2.9.9
python-decouple==3.8
Pillow==10.1.0
django-crispy-forms==2.1
celery==5.3.4
redis==5.0.1
EOF

cat > requirements-dev.txt << 'EOF'
-r requirements.txt
pytest==7.4.3
pytest-django==4.7.0
coverage==7.3.2
black==23.11.0
flake8==6.1.0
pre-commit==3.5.0
django-debug-toolbar==4.2.0
EOF
```

### 5. Simulazione File da Ignorare
```bash
# Creiamo file che dovrebbero essere ignorati
echo "SECRET_KEY=real-secret-key-123" > config/local_settings.py

# File cache Python
mkdir -p src/blog/__pycache__
echo "fake cache" > src/blog/__pycache__/models.cpython-311.pyc

# File di log
mkdir -p logs
echo "2024-01-15 10:30:00 ERROR: Test error" > logs/django.log
echo "2024-01-15 10:35:00 INFO: User login" > logs/application.log

# Database locale
touch db.sqlite3

# Media files
mkdir -p media/uploads/images
echo "fake image" > media/uploads/images/test.jpg

# Ambiente virtuale (simulato)
mkdir -p venv/lib/python3.11
echo "virtual env file" > venv/lib/python3.11/site-packages

# File IDE
mkdir -p .vscode
echo '{"python.defaultInterpreter": "./venv/bin/python"}' > .vscode/settings.json

# File di ambiente reale
cat > .env << 'EOF'
SECRET_KEY=django-insecure-real-secret-key-12345
DEBUG=True
DB_PASSWORD=real_db_password_123
EMAIL_HOST_PASSWORD=real_email_password
EOF
```

## Verifica del .gitignore

### 1. Controllo Status
```bash
# Aggiungiamo tutto e vediamo cosa viene tracciato
git add .
git status

# Output atteso: solo i file che vogliamo tracciare
# Should see:
# - .gitignore
# - src/blog/models.py
# - tests/test_models.py
# - requirements.txt
# - requirements-dev.txt
# - config/settings_template.py
# - .env.template
```

### 2. Verifica File Ignorati
```bash
# Verifichiamo che i file sensibili siano ignorati
git status --ignored

# Dovremmo vedere nella sezione "Ignored files":
# - config/local_settings.py
# - .env
# - src/blog/__pycache__/
# - logs/
# - db.sqlite3
# - media/uploads/
# - venv/
# - .vscode/
```

### 3. Test con git check-ignore
```bash
# Testiamo specifici file
echo "Testing file ignore patterns:"

git check-ignore config/local_settings.py && echo "✓ Local settings ignored"
git check-ignore .env && echo "✓ Environment file ignored"
git check-ignore src/blog/__pycache__/models.cpython-311.pyc && echo "✓ Python cache ignored"
git check-ignore logs/django.log && echo "✓ Log files ignored"
git check-ignore db.sqlite3 && echo "✓ Database file ignored"
git check-ignore media/uploads/images/test.jpg && echo "✓ Media files ignored"
git check-ignore venv/lib/python3.11/site-packages && echo "✓ Virtual env ignored"
```

## Pattern Avanzati Utilizzati

### 1. Pattern per Cache Python
```gitignore
__pycache__/          # Directory cache
*.py[cod]            # File compilati (.pyc, .pyo, .pyd)
*$py.class           # Jython class files
```

### 2. Pattern per File di Configurazione
```gitignore
# Template incluso, configurazioni locali escluse
config/settings_template.py     # Incluso
config/local_settings.py        # Escluso
config/production_settings.py   # Escluso

# Pattern per ambienti
.env                   # File reale escluso
.env.template         # Template incluso
```

### 3. Pattern per Media Files
```gitignore
# Ignora tutti i file media ma mantieni la struttura
media/uploads/*
!media/uploads/.gitkeep
```

## Script di Automazione

### 1. Script di Setup Ambiente
```bash
cat > scripts/setup_dev.sh << 'EOF'
#!/bin/bash

echo "🚀 Setting up development environment..."

# Crea ambiente virtuale se non esiste
if [ ! -d "venv" ]; then
    echo "📦 Creating virtual environment..."
    python3 -m venv venv
fi

# Attiva ambiente virtuale
source venv/bin/activate

# Installa dipendenze
echo "📚 Installing dependencies..."
pip install -r requirements-dev.txt

# Crea file di configurazione locale se non esiste
if [ ! -f "config/local_settings.py" ]; then
    echo "⚙️ Creating local settings..."
    cp config/settings_template.py config/local_settings.py
    echo "Please edit config/local_settings.py with your local configuration"
fi

# Crea file .env se non esiste
if [ ! -f ".env" ]; then
    echo "🔐 Creating environment file..."
    cp .env.template .env
    echo "Please edit .env with your environment variables"
fi

# Crea directory per media se non esistono
mkdir -p media/uploads
touch media/uploads/.gitkeep

# Crea directory per log se non esistono
mkdir -p logs
touch logs/.gitkeep

echo "✅ Development environment setup complete!"
echo "Don't forget to:"
echo "1. Edit config/local_settings.py"
echo "2. Edit .env file"
echo "3. Run migrations: python manage.py migrate"
EOF

chmod +x scripts/setup_dev.sh
```

### 2. Script di Pulizia
```bash
cat > scripts/clean.sh << 'EOF'
#!/bin/bash

echo "🧹 Cleaning development files..."

# Rimuovi cache Python
find . -type d -name "__pycache__" -exec rm -rf {} + 2>/dev/null
find . -name "*.pyc" -delete
find . -name "*.pyo" -delete
find . -name "*.pyd" -delete

# Rimuovi file di log
rm -f logs/*.log

# Rimuovi database di sviluppo
rm -f db.sqlite3

# Rimuovi file di coverage
rm -f .coverage
rm -rf htmlcov/

echo "✅ Cleanup complete!"
EOF

chmod +x scripts/clean.sh
```

## Commit Finale

```bash
# Aggiungiamo tutto
git add .

# Verifichiamo cosa stiamo committando
git status

# Commit
git commit -m "feat: setup Python Django project with comprehensive .gitignore

- Add complete .gitignore for Python/Django projects
- Include configuration templates for local settings
- Add development and production requirements
- Create setup and cleanup scripts
- Implement media file handling with .gitkeep
- Add comprehensive test coverage for ignore patterns"
```

## Punti Chiave Appresi

1. **Pattern Python Specifici**: Cache, bytecode, ambienti virtuali
2. **Gestione Configurazioni**: Template vs file reali
3. **Media Files**: Struttura directory con .gitkeep
4. **Automazione**: Script per setup e pulizia
5. **Security**: File sensibili mai committati
6. **Testing**: Verifica dei pattern con git check-ignore

Questo esempio mostra una configurazione professionale per progetti Python/Django con attenzione alla sicurezza e alla collaborazione in team.
