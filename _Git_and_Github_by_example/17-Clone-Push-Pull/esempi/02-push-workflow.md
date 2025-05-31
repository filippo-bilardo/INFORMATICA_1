# Esempio 02: Push Workflow Completo

## 📋 Scenario
Hai modificato i file nel tuo repository locale e devi condividere i cambiamenti con il team. Imparerai tutti gli aspetti del push: dai casi semplici ai workflow avanzati con branch multipli.

## 🎯 Obiettivi
- Padroneggiare `git push` in tutti gli scenari
- Gestire branch remoti correttamente
- Risolvere errori di push comuni
- Implementare workflow di push sicuri

## 🚀 Implementazione Pratica

### Fase 1: Push Base - Prima Volta

```bash
# 1. Setup repository locale
mkdir mio-progetto-web
cd mio-progetto-web
git init

# 2. Creare contenuto iniziale
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Il Mio Portfolio</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .container { max-width: 800px; margin: 0 auto; }
        .header { background: #333; color: white; padding: 20px; border-radius: 5px; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>Benvenuto nel Mio Portfolio</h1>
            <p>Sviluppatore Web Full Stack</p>
        </div>
        <section>
            <h2>Chi Sono</h2>
            <p>Sono uno sviluppatore appassionato di tecnologie moderne.</p>
        </section>
    </div>
</body>
</html>
EOF

# 3. Primo commit
git add index.html
git commit -m "feat: aggiunta pagina portfolio iniziale

- Layout responsive con CSS embedded
- Sezione header con stili personalizzati
- Struttura base per portfolio professionale"

# 4. Collegare a repository remoto GitHub
git remote add origin https://github.com/tuousername/mio-portfolio.git

# 5. Push iniziale (crea branch remoto)
git push -u origin main
```

**Output atteso:**
```
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Writing objects: 100% (3/3), 1.2 KiB | 1.2 MiB/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To https://github.com/tuousername/mio-portfolio.git
 * [new branch]      main -> main
Branch 'main' set up to track remote branch 'main' from 'origin'.
```

### Fase 2: Push con Feature Branch

```bash
# 1. Creare branch per nuova feature
git checkout -b feature/contact-form

# 2. Aggiungere form di contatto
cat >> index.html << 'EOF'
        <section>
            <h2>Contattami</h2>
            <form id="contact-form">
                <div style="margin-bottom: 15px;">
                    <label for="name">Nome:</label><br>
                    <input type="text" id="name" name="name" required 
                           style="width: 100%; padding: 8px; margin-top: 5px;">
                </div>
                <div style="margin-bottom: 15px;">
                    <label for="email">Email:</label><br>
                    <input type="email" id="email" name="email" required
                           style="width: 100%; padding: 8px; margin-top: 5px;">
                </div>
                <div style="margin-bottom: 15px;">
                    <label for="message">Messaggio:</label><br>
                    <textarea id="message" name="message" required
                              style="width: 100%; padding: 8px; margin-top: 5px; height: 100px;"></textarea>
                </div>
                <button type="submit" style="background: #333; color: white; padding: 10px 20px; border: none; border-radius: 5px;">
                    Invia Messaggio
                </button>
            </form>
        </section>
EOF

# 3. Aggiungere JavaScript per il form
cat > script.js << 'EOF'
document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('contact-form');
    
    form.addEventListener('submit', function(e) {
        e.preventDefault();
        
        // Validazione base
        const name = document.getElementById('name').value.trim();
        const email = document.getElementById('email').value.trim();
        const message = document.getElementById('message').value.trim();
        
        if (!name || !email || !message) {
            alert('Tutti i campi sono obbligatori!');
            return;
        }
        
        // Simulazione invio
        alert(`Grazie ${name}! Il tuo messaggio è stato inviato.`);
        form.reset();
    });
});
EOF

# 4. Collegare script a HTML
sed -i '/<\/head>/i\    <script src="script.js" defer></script>' index.html

# 5. Commit della feature
git add .
git commit -m "feat: aggiunto form di contatto interattivo

- Form HTML con validazione CSS integrata
- JavaScript per validazione client-side
- Gestione eventi submit con feedback utente
- Design coerente con resto del sito"

# 6. Push del branch feature
git push -u origin feature/contact-form
```

### Fase 3: Push dopo Merge

```bash
# 1. Tornare a main e fare merge
git checkout main
git merge feature/contact-form

# 2. Push del merge
git push origin main

# 3. Opzionale: eliminare branch feature remoto
git push origin --delete feature/contact-form

# 4. Pulizia locale
git branch -d feature/contact-form
```

### Fase 4: Push Workflow Avanzato

```bash
# 1. Creare multiple features in parallelo
git checkout -b feature/responsive-design
git checkout -b feature/seo-optimization

# 2. Lavorare su responsive design
git checkout feature/responsive-design

cat > styles.css << 'EOF'
/* Reset e base styles */
* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    line-height: 1.6;
    color: #333;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0 20px;
}

/* Header responsivo */
.header {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 60px 0;
    text-align: center;
}

.header h1 {
    font-size: 3rem;
    margin-bottom: 10px;
}

.header p {
    font-size: 1.2rem;
    opacity: 0.9;
}

/* Sezioni */
section {
    padding: 40px 0;
    margin-bottom: 20px;
}

section h2 {
    font-size: 2rem;
    margin-bottom: 20px;
    color: #333;
}

/* Form responsivo */
.contact-form {
    max-width: 600px;
    margin: 0 auto;
}

.form-group {
    margin-bottom: 20px;
}

.form-group label {
    display: block;
    margin-bottom: 5px;
    font-weight: bold;
}

.form-group input,
.form-group textarea {
    width: 100%;
    padding: 12px;
    border: 2px solid #ddd;
    border-radius: 5px;
    font-size: 16px;
    transition: border-color 0.3s;
}

.form-group input:focus,
.form-group textarea:focus {
    outline: none;
    border-color: #667eea;
}

.btn-submit {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 12px 30px;
    border: none;
    border-radius: 5px;
    font-size: 16px;
    cursor: pointer;
    transition: transform 0.2s;
}

.btn-submit:hover {
    transform: translateY(-2px);
}

/* Media queries */
@media (max-width: 768px) {
    .header h1 {
        font-size: 2rem;
    }
    
    .header p {
        font-size: 1rem;
    }
    
    .container {
        padding: 0 15px;
    }
    
    section {
        padding: 30px 0;
    }
}

@media (max-width: 480px) {
    .header {
        padding: 40px 0;
    }
    
    .header h1 {
        font-size: 1.8rem;
    }
    
    section h2 {
        font-size: 1.5rem;
    }
}
EOF

# 3. Aggiornare HTML per usare CSS esterno
cat > index.html << 'EOF'
<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Portfolio Professionale - Mario Rossi</title>
    <meta name="description" content="Portfolio di Mario Rossi, sviluppatore web full stack specializzato in tecnologie moderne">
    <link rel="stylesheet" href="styles.css">
    <script src="script.js" defer></script>
</head>
<body>
    <div class="container">
        <header class="header">
            <h1>Mario Rossi</h1>
            <p>Sviluppatore Web Full Stack</p>
        </header>
        
        <main>
            <section>
                <h2>Chi Sono</h2>
                <p>Sono uno sviluppatore appassionato di tecnologie moderne con oltre 5 anni di esperienza nello sviluppo di applicazioni web responsive e performanti.</p>
                <p>Le mie competenze includono JavaScript, React, Node.js, Python e molto altro.</p>
            </section>
            
            <section>
                <h2>Progetti</h2>
                <div class="projects-grid">
                    <div class="project-card">
                        <h3>E-commerce Platform</h3>
                        <p>Piattaforma completa con React e Node.js</p>
                    </div>
                    <div class="project-card">
                        <h3>Task Management App</h3>
                        <p>App per gestione progetti con Vue.js</p>
                    </div>
                </div>
            </section>
            
            <section>
                <h2>Contattami</h2>
                <form id="contact-form" class="contact-form">
                    <div class="form-group">
                        <label for="name">Nome:</label>
                        <input type="text" id="name" name="name" required>
                    </div>
                    <div class="form-group">
                        <label for="email">Email:</label>
                        <input type="email" id="email" name="email" required>
                    </div>
                    <div class="form-group">
                        <label for="message">Messaggio:</label>
                        <textarea id="message" name="message" required rows="5"></textarea>
                    </div>
                    <button type="submit" class="btn-submit">Invia Messaggio</button>
                </form>
            </section>
        </main>
    </div>
</body>
</html>
EOF

# 4. Commit responsive design
git add .
git commit -m "feat: implementato design responsive completo

- CSS esterno con mobile-first approach
- Media queries per tablet e mobile
- Gradients e animazioni moderne
- Grid layout per progetti
- Form styling migliorato
- Ottimizzazione per accessibilità"

# 5. Push branch responsive
git push -u origin feature/responsive-design
```

## 🔧 Push Workflow Avanzati

### Push con Force (Attenzione!)

```bash
# ⚠️ SOLO per branch personali, MAI su main condiviso!

# 1. Scenario: hai fatto rebase e devi aggiornare remote
git checkout feature/my-branch
git rebase main
git push --force-with-lease origin feature/my-branch

# 2. Force più sicuro (verifica che nessuno abbia pushato)
git push --force-with-lease origin feature/my-branch

# 3. Force "nuklear" (PERICOLOSO - usa solo se sicuro)
git push --force origin feature/my-branch
```

### Push Tags e Release

```bash
# 1. Creare e pushare tag
git tag -a v1.0.0 -m "Prima release stabile

- Portfolio completo responsive
- Form di contatto funzionante
- Design moderno e accessibile"

git push origin v1.0.0

# 2. Push di tutti i tag
git push origin --tags

# 3. Push branch e tag insieme
git push origin main --tags
```

### Push Multiple Remote

```bash
# 1. Setup multiple remote (GitHub + GitLab)
git remote add github https://github.com/user/repo.git
git remote add gitlab https://gitlab.com/user/repo.git

# 2. Push su tutti i remote
git push github main
git push gitlab main

# 3. Script per push multiplo
#!/bin/bash
# push-all.sh
for remote in $(git remote); do
    echo "📤 Push su $remote..."
    git push "$remote" main
done
```

## ⚠️ Gestione Errori Comuni

### Errore: Push Rejected

```bash
# Problema: "Updates were rejected because the tip of your current branch is behind"

# Soluzione 1: Pull + Push
git pull origin main
git push origin main

# Soluzione 2: Pull con rebase
git pull --rebase origin main
git push origin main

# Soluzione 3: Fetch + merge manuale
git fetch origin
git merge origin/main
git push origin main
```

### Errore: Permission Denied

```bash
# Verifica autenticazione
git config --list | grep user
ssh -T git@github.com

# Fix credenziali HTTPS
git config --global credential.helper cache
git config --global credential.helper 'cache --timeout=3600'

# Switch da HTTPS a SSH
git remote set-url origin git@github.com:user/repo.git
```

### Errore: Large File

```bash
# Errore: file troppo grande per GitHub (>100MB)

# Soluzione: Git LFS
git lfs install
git lfs track "*.zip"
git lfs track "*.mp4"
git add .gitattributes
git add large-file.zip
git commit -m "feat: aggiunto file con Git LFS"
git push origin main
```

## 📊 Monitoring e Verifica Push

### Script di Verifica Push

```bash
#!/bin/bash
# verify-push.sh

echo "🔍 VERIFICA STATO PUSH"
echo "======================"

# Stato repository
echo "📍 Repository status:"
git status --porcelain

# Branch tracking
echo -e "\n🌿 Branch tracking:"
git branch -vv

# Confronto con remote
echo -e "\n📊 Differenze con remote:"
git log --oneline origin/main..HEAD

# Verifica ultimo push
echo -e "\n⏰ Ultimo push:"
git log --oneline -1 origin/main

# Check se push necessario
if [ "$(git rev-parse HEAD)" != "$(git rev-parse origin/main)" ]; then
    echo -e "\n⚠️  PUSH NECESSARIO!"
    echo "Commit locali non pushati: $(git rev-list --count origin/main..HEAD)"
else
    echo -e "\n✅ Repository sincronizzato"
fi
```

### Pre-push Hook

```bash
#!/bin/bash
# .git/hooks/pre-push

echo "🔍 Pre-push validation..."

# Eseguire test
if ! npm test; then
    echo "❌ Test falliti! Push abortito."
    exit 1
fi

# Controllare linting
if ! npm run lint; then
    echo "❌ Linting fallito! Push abortito."
    exit 1
fi

# Controllare dimensione commit
large_files=$(git diff --cached --name-only --diff-filter=A | xargs -I{} find {} -size +50M 2>/dev/null)
if [ ! -z "$large_files" ]; then
    echo "❌ File troppo grandi trovati: $large_files"
    echo "Usa Git LFS per file >50MB"
    exit 1
fi

echo "✅ Pre-push validation passata"
```

## 🎯 Best Practices Push

### 1. **Commit Atomici**
```bash
# Male: commit tutto insieme
git add .
git commit -m "fix stuff"

# Bene: commit logici separati
git add styles.css
git commit -m "style: migliorata responsività mobile"

git add script.js
git commit -m "feat: aggiunta validazione form avanzata"

git push origin main
```

### 2. **Branch Naming**
```bash
# Convezioni team
feature/user-authentication
bugfix/login-validation-error
hotfix/security-patch-2024
release/v2.1.0
```

### 3. **Push Safety**
```bash
# Sempre controllare prima di push
git log --oneline -5
git diff origin/main..HEAD --stat

# Push graduale
git push origin feature/my-branch  # Prima il branch
# Test e verifica
git push origin main              # Poi main
```

## 💡 Tips Produttività

### Alias Utili

```bash
# Setup alias per push comuni
git config --global alias.pushup 'push -u origin'
git config --global alias.pushf 'push --force-with-lease'
git config --global alias.pusht 'push --tags'

# Uso degli alias
git pushup feature/new-feature
git pushf feature/rebased-branch
git pusht
```

### Scripts Automatizzati

```bash
#!/bin/bash
# smart-push.sh - Push intelligente

branch=$(git branch --show-current)
echo "📤 Push intelligente per branch: $branch"

# Controlli pre-push
if [ "$branch" = "main" ] || [ "$branch" = "master" ]; then
    echo "⚠️  Push su branch principale. Confermi? (y/N)"
    read -r confirm
    if [ "$confirm" != "y" ]; then
        echo "❌ Push annullato"
        exit 1
    fi
fi

# Verifica se branch esiste su remote
if git show-ref --verify --quiet "refs/remotes/origin/$branch"; then
    echo "🔄 Aggiornamento branch esistente..."
    git push origin "$branch"
else
    echo "🆕 Creazione nuovo branch remoto..."
    git push -u origin "$branch"
fi

echo "✅ Push completato con successo!"
```

## 🔄 Prossimi Passi

Dopo aver masterizzato il push workflow:

1. **[03-Pull-Sync](./03-pull-sync.md)** - Sincronizzazione avanzata
2. **[04-Remote-Management](./04-remote-management.md)** - Gestione remote complessa
3. **[../18-Collaborazione-Base](../18-Collaborazione-Base/README.md)** - Workflow collaborativi

## 📚 Risorse Aggiuntive

- [Git Push Documentation](https://git-scm.com/docs/git-push)
- [GitHub Push Best Practices](https://docs.github.com/en/repositories)
- [Git LFS Guide](https://git-lfs.github.io/)
