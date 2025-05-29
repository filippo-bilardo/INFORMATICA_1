# 04 - Utilizzo Avanzato Git Diff

## 📋 Scenario

Sei il lead developer di un team che sta sviluppando un'applicazione di social media. Devi revisionare pull request, fare debug di bug introdotti in commit recenti, e analizzare l'evoluzione del codice per ottimizzazioni. `git diff` è il tuo strumento principale per queste attività.

## 🎯 Obiettivo

Padroneggiare l'uso avanzato di `git diff` per:
- **Code review** efficaci e approfondite
- **Debug temporale** per individuare quando sono stati introdotti bug
- **Analisi di performance** e ottimizzazioni del codice
- **Confronti tra branch** per merge intelligenti
- **Workflow di team** con diff personalizzati

## 🛠️ Setup Progetto Social Media

```bash
# Crea progetto social media complesso
mkdir social-media-app
cd social-media-app
git init

# Configura sviluppatore
git config user.name "Elena TechLead"
git config user.email "elena@socialmedia.com"

# Struttura dell'applicazione
mkdir -p {frontend,backend,mobile}
mkdir -p frontend/src/{components,pages,utils,hooks}
mkdir -p backend/src/{models,controllers,services,middleware}

# File base per demo diff
cat > frontend/src/components/UserProfile.js << 'EOF'
import React, { useState, useEffect } from 'react';
import { getUserProfile, updateProfile } from '../services/api';

const UserProfile = ({ userId }) => {
  const [profile, setProfile] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    loadProfile();
  }, [userId]);

  const loadProfile = async () => {
    try {
      setLoading(true);
      const data = await getUserProfile(userId);
      setProfile(data);
    } catch (err) {
      setError('Failed to load profile');
    } finally {
      setLoading(false);
    }
  };

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div className="user-profile">
      <img src={profile.avatar} alt="Avatar" />
      <h2>{profile.name}</h2>
      <p>{profile.bio}</p>
      <div className="stats">
        <span>Posts: {profile.postCount}</span>
        <span>Followers: {profile.followers}</span>
      </div>
    </div>
  );
};

export default UserProfile;
EOF

# Commit iniziale
git add .
git commit -m "feat: initial social media app setup with user profile component"
```

## 🎯 Diff per Code Review

### 1. Preparazione Feature Branch
```bash
# Crea feature branch per nuova funzionalità
git checkout -b feature/user-interactions

# Simula sviluppo: migliora UserProfile con interazioni
cat > frontend/src/components/UserProfile.js << 'EOF'
import React, { useState, useEffect } from 'react';
import { getUserProfile, updateProfile, followUser, unfollowUser } from '../services/api';
import { useAuth } from '../hooks/useAuth';
import Button from './Button';
import Modal from './Modal';

const UserProfile = ({ userId }) => {
  const [profile, setProfile] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [isEditing, setIsEditing] = useState(false);
  const [editForm, setEditForm] = useState({});
  const { user: currentUser } = useAuth();

  useEffect(() => {
    loadProfile();
  }, [userId]);

  const loadProfile = async () => {
    try {
      setLoading(true);
      const data = await getUserProfile(userId);
      setProfile(data);
      setEditForm({ name: data.name, bio: data.bio });
    } catch (err) {
      setError('Failed to load profile');
      console.error('Profile loading error:', err);
    } finally {
      setLoading(false);
    }
  };

  const handleFollow = async () => {
    try {
      if (profile.isFollowing) {
        await unfollowUser(userId);
        setProfile(prev => ({
          ...prev,
          isFollowing: false,
          followers: prev.followers - 1
        }));
      } else {
        await followUser(userId);
        setProfile(prev => ({
          ...prev,
          isFollowing: true,
          followers: prev.followers + 1
        }));
      }
    } catch (err) {
      console.error('Follow/unfollow error:', err);
    }
  };

  const handleSaveProfile = async () => {
    try {
      const updatedProfile = await updateProfile(userId, editForm);
      setProfile(updatedProfile);
      setIsEditing(false);
    } catch (err) {
      console.error('Profile update error:', err);
    }
  };

  if (loading) return <div className="loading-spinner">Loading...</div>;
  if (error) return <div className="error-message">Error: {error}</div>;

  const isOwnProfile = currentUser?.id === userId;

  return (
    <div className="user-profile">
      <div className="profile-header">
        <img 
          src={profile.avatar} 
          alt="Avatar" 
          className="avatar-large"
          onError={(e) => e.target.src = '/default-avatar.png'}
        />
        <div className="profile-info">
          <h2>{profile.name}</h2>
          <p className="bio">{profile.bio}</p>
          <div className="stats">
            <span className="stat">
              <strong>{profile.postCount}</strong> Posts
            </span>
            <span className="stat">
              <strong>{profile.followers}</strong> Followers
            </span>
            <span className="stat">
              <strong>{profile.following}</strong> Following
            </span>
          </div>
        </div>
      </div>
      
      <div className="profile-actions">
        {isOwnProfile ? (
          <Button onClick={() => setIsEditing(true)}>Edit Profile</Button>
        ) : (
          <Button 
            onClick={handleFollow}
            variant={profile.isFollowing ? 'secondary' : 'primary'}
          >
            {profile.isFollowing ? 'Unfollow' : 'Follow'}
          </Button>
        )}
      </div>

      {isEditing && (
        <Modal onClose={() => setIsEditing(false)}>
          <div className="edit-profile-form">
            <h3>Edit Profile</h3>
            <input
              type="text"
              placeholder="Name"
              value={editForm.name}
              onChange={(e) => setEditForm(prev => ({ ...prev, name: e.target.value }))}
            />
            <textarea
              placeholder="Bio"
              value={editForm.bio}
              onChange={(e) => setEditForm(prev => ({ ...prev, bio: e.target.value }))}
            />
            <div className="form-actions">
              <Button onClick={handleSaveProfile}>Save</Button>
              <Button variant="secondary" onClick={() => setIsEditing(false)}>Cancel</Button>
            </div>
          </div>
        </Modal>
      )}
    </div>
  );
};

export default UserProfile;
EOF

git add .
git commit -m "feat: add user interactions to profile component

Features added:
- Follow/unfollow functionality with real-time updates
- Profile editing for own profiles
- Enhanced error handling and loading states
- Modal-based edit form
- Improved UI with better stats display
- Avatar fallback for broken images

UI improvements:
- Better semantic HTML structure
- Enhanced accessibility with proper alt text
- Responsive design considerations"
```

### 2. Code Review con Git Diff
```bash
# Differenza tra main e feature branch (cosa cambierà il merge?)
echo "=== CODICE REVIEW: Analisi modifiche feature branch ==="

# Overview delle modifiche
git diff main...feature/user-interactions --stat
echo ""

# Modifiche dettagliate per revisione
echo "=== DIFF DETTAGLIATO PER CODE REVIEW ==="
git diff main...feature/user-interactions --word-diff=color

# Solo nomi file modificati
echo -e "\n=== FILE MODIFICATI ==="
git diff main...feature/user-interactions --name-only

# Differenze con contesto esteso per revisione approfondita
echo -e "\n=== DIFFERENZE CON CONTESTO ESTESO ==="
git diff main...feature/user-interactions -U10 -- frontend/src/components/UserProfile.js
```

### 3. Analisi Specifica per Reviewer
```bash
# Crea script di code review automatizzato
cat > scripts/review-helper.sh << 'EOF'
#!/bin/bash
# Aiuto automatico per code review

BRANCH=${1:-HEAD}
BASE=${2:-main}

echo "🔍 CODE REVIEW ANALYSIS: $BRANCH vs $BASE"
echo "================================================"

echo -e "\n📊 STATISTICHE MODIFICHE:"
git diff $BASE...$BRANCH --stat | tail -1

echo -e "\n📁 FILE MODIFICATI:"
git diff $BASE...$BRANCH --name-status

echo -e "\n🔥 POTENZIALI PROBLEMI:"
# Cerca console.log
if git diff $BASE...$BRANCH | grep -q "console\.log"; then
    echo "⚠️  Console.log statements found"
    git diff $BASE...$BRANCH | grep "console\.log"
fi

# Cerca TODO/FIXME
if git diff $BASE...$BRANCH | grep -q -E "(TODO|FIXME|HACK)"; then
    echo "⚠️  TODO/FIXME comments found"
    git diff $BASE...$BRANCH | grep -E "(TODO|FIXME|HACK)"
fi

# Cerca hardcoded strings
if git diff $BASE...$BRANCH | grep -q -E "http://|https://"; then
    echo "⚠️  Hardcoded URLs found"
fi

echo -e "\n📈 COMPLESSITÀ AGGIUNTA:"
added_lines=$(git diff $BASE...$BRANCH --numstat | awk '{sum+=$1} END {print sum}')
removed_lines=$(git diff $BASE...$BRANCH --numstat | awk '{sum+=$2} END {print sum}')
echo "Lines added: $added_lines"
echo "Lines removed: $removed_lines"
echo "Net change: $((added_lines - removed_lines))"

echo -e "\n🧪 SUGGERIMENTI TEST:"
# Controlla se ci sono test
if git diff $BASE...$BRANCH --name-only | grep -q "\.test\."; then
    echo "✅ Test files detected"
else
    echo "⚠️  No test files found - consider adding tests"
fi
EOF

chmod +x scripts/review-helper.sh
git add scripts/
git commit -m "tools: add automated code review helper script"

# Esegui review helper
bash scripts/review-helper.sh feature/user-interactions main
```

## 🐛 Debug Temporale con Diff

### Scenario: Bug nel Sistema di Follow
```bash
# Simula un bug introdotto in un commit successivo
git checkout main
git merge feature/user-interactions --no-ff -m "merge: add user interactions feature"

# Simula bug fix commit
cat > frontend/src/services/api.js << 'EOF'
const API_BASE = process.env.REACT_APP_API_URL || 'http://localhost:3000/api';

export const getUserProfile = async (userId) => {
  const response = await fetch(`${API_BASE}/users/${userId}`);
  if (!response.ok) throw new Error('Failed to fetch profile');
  return response.json();
};

export const followUser = async (userId) => {
  const response = await fetch(`${API_BASE}/users/${userId}/follow`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ action: 'follow' })
  });
  if (!response.ok) throw new Error('Failed to follow user');
  return response.json();
};

// BUG: implementazione sbagliata di unfollow
export const unfollowUser = async (userId) => {
  // ERRORE: usando POST invece di DELETE
  const response = await fetch(`${API_BASE}/users/${userId}/follow`, {
    method: 'POST',  // Dovrebbe essere DELETE
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ action: 'unfollow' })
  });
  if (!response.ok) throw new Error('Failed to unfollow user');
  return response.json();
};

export const updateProfile = async (userId, profileData) => {
  const response = await fetch(`${API_BASE}/users/${userId}`, {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify(profileData)
  });
  if (!response.ok) throw new Error('Failed to update profile');
  return response.json();
};
EOF

git add .
git commit -m "fix: implement API service methods for user interactions

- Add getUserProfile API call
- Implement follow/unfollow functionality  
- Add profile update method
- Configure API base URL from environment"

# Commit che introduce un problema
sed -i 's/action: '\''unfollow'\''/action: '\''follow'\''/g' frontend/src/services/api.js
git add .
git commit -m "refactor: simplify API action handling"

# Ora hai un bug: unfollow invia 'follow' invece di 'unfollow'
```

### Debug: Quando è Stato Introdotto il Bug?
```bash
echo "🐛 DEBUG SESSIONE: Unfollow non funziona"

# 1. Analizza gli ultimi commit
echo -e "\n=== ULTIMI COMMIT ==="
git log --oneline -5

# 2. Diff dell'ultimo commit (sospetto)
echo -e "\n=== COSA È CAMBIATO NELL'ULTIMO COMMIT? ==="
git diff HEAD~1 HEAD

# 3. Confronta con versione funzionante
echo -e "\n=== DIFF CON VERSIONE PRECEDENTE ==="
git diff HEAD~2 HEAD -- frontend/src/services/api.js

# 4. Analizza solo le modifiche alla funzione unfollow
echo -e "\n=== FOCUS SU FUNZIONE UNFOLLOW ==="
git log -p --grep="unfollow" -- frontend/src/services/api.js

# 5. Vedi l'evoluzione della funzione unfollowUser
echo -e "\n=== EVOLUZIONE FUNZIONE UNFOLLOWUSER ==="
git log -L :unfollowUser:frontend/src/services/api.js
```

### Fix del Bug con Diff Verification
```bash
# Fix del bug
sed -i 's/action: '\''follow'\''/action: '\''unfollow'\''/g' frontend/src/services/api.js

# Verifica fix prima del commit
echo "🔧 VERIFICA FIX:"
git diff

# Confronta con versione originale funzionante
echo -e "\n=== CONFRONTO CON VERSIONE FUNZIONANTE ==="
git diff HEAD~2 -- frontend/src/services/api.js

git add .
git commit -m "fix: correct unfollow API action parameter

Bug: unfollowUser was sending 'follow' action instead of 'unfollow'
Root cause: Incorrect refactoring in previous commit  
Fix: Restore correct 'unfollow' action parameter

Tested: Verified unfollow functionality works correctly"
```

## 🎨 Diff Personalizzati e Configurazioni

### 1. Setup Tool Esterni per Diff
```bash
# Configura VS Code come diff tool
git config --global diff.tool vscode
git config --global difftool.vscode.cmd 'code --wait --diff $LOCAL $REMOTE'

# Per usare tool grafico
echo "Esempio uso difftool:"
echo "git difftool HEAD~1 HEAD -- frontend/src/services/api.js"

# Configura alias utili per diff
git config --global alias.dt "difftool"
git config --global alias.review "diff --stat --summary origin/main..."
git config --global alias.words "diff --word-diff=color"
```

### 2. Diff con Context Specifico
```bash
# Crea file di configurazione diff personalizzato
cat > .gitattributes << 'EOF'
# Configurazioni diff personalizzate per tipo file

# JavaScript: mostra nome funzione nel header
*.js diff=javascript
*.jsx diff=javascript

# CSS: pattern per selettori  
*.css diff=css

# JSON: formato speciale
*.json diff=json

# Markdown: headers come context
*.md diff=markdown
EOF

# Configura driver diff personalizzati
git config diff.javascript.xfuncname '^[[:space:]]*((export[[:space:]]+)?((async[[:space:]]+)?function|class)[[:space:]]+[A-Za-z_$][A-Za-z0-9_$]*|[A-Za-z_$][A-Za-z0-9_$]*[[:space:]]*:[[:space:]]*((async[[:space:]]+)?function))'

git add .gitattributes
git commit -m "config: add custom diff attributes for better code context"
```

### 3. Diff Statistiche e Reporting
```bash
# Script per report diff avanzato
cat > scripts/diff-report.sh << 'EOF'
#!/bin/bash
# Report avanzato delle differenze tra branch

FROM=${1:-main}
TO=${2:-HEAD}

echo "📊 DIFF REPORT: $FROM → $TO"
echo "==============================="

echo -e "\n📈 STATISTICHE GENERALI:"
git diff $FROM..$TO --stat

echo -e "\n🎯 MODIFICHE PER LINGUAGGIO:"
echo "JavaScript files:"
git diff $FROM..$TO --name-only | grep -E '\.(js|jsx)$' | wc -l
echo "CSS files:"  
git diff $FROM..$TO --name-only | grep -E '\.(css|scss)$' | wc -l
echo "Test files:"
git diff $FROM..$TO --name-only | grep -E '\.test\.(js|jsx)$' | wc -l

echo -e "\n🔍 TOP 5 FILE PIÙ MODIFICATI:"
git diff $FROM..$TO --numstat | sort -nr | head -5

echo -e "\n📝 AUTORI DELLE MODIFICHE:"
git log $FROM..$TO --pretty=format:'%an' | sort | uniq -c | sort -nr

echo -e "\n⏰ TIMELINE MODIFICHE:"
git log $FROM..$TO --pretty=format:'%h %ad %s' --date=short | head -10

echo -e "\n🎨 COMPLESSITÀ AGGIUNTA:"
ADDED=$(git diff $FROM..$TO --numstat | awk '{sum+=$1} END {print sum}')
REMOVED=$(git diff $FROM..$TO --numstat | awk '{sum+=$2} END {print sum}') 
echo "Linee aggiunte: $ADDED"
echo "Linee rimosse: $REMOVED"
echo "Modifica netta: $((ADDED - REMOVED))"
EOF

chmod +x scripts/diff-report.sh
git add scripts/
git commit -m "tools: add comprehensive diff reporting script"

# Esegui report
bash scripts/diff-report.sh HEAD~5 HEAD
```

## 🎯 Diff per Performance Analysis

### Analisi Prestazioni nel Tempo
```bash
# Simula ottimizzazione performance
cat > frontend/src/hooks/useAuth.js << 'EOF'
import { useState, useEffect, useMemo } from 'react';

export const useAuth = () => {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    // Simula caricamento auth
    const token = localStorage.getItem('auth_token');
    if (token) {
      // Versione ottimizzata: cache del parsing JWT
      const cachedUser = sessionStorage.getItem('cached_user');
      if (cachedUser) {
        setUser(JSON.parse(cachedUser));
        setLoading(false);
        return;
      }
      
      // Solo se non in cache, fai parsing completo
      parseTokenAndSetUser(token);
    } else {
      setLoading(false);
    }
  }, []);

  const parseTokenAndSetUser = async (token) => {
    try {
      // Simulazione parsing JWT ottimizzato
      const userData = await parseJWT(token);
      setUser(userData);
      sessionStorage.setItem('cached_user', JSON.stringify(userData));
    } catch (error) {
      console.error('Auth parsing error:', error);
      localStorage.removeItem('auth_token');
    } finally {
      setLoading(false);
    }
  };

  // Memoized helpers per performance
  const isAuthenticated = useMemo(() => user !== null, [user]);
  const userRole = useMemo(() => user?.role || 'guest', [user]);

  return { user, loading, isAuthenticated, userRole };
};

const parseJWT = async (token) => {
  // Simulazione parsing JWT
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({
        id: '123',
        name: 'Test User',
        email: 'test@example.com',
        role: 'user'
      });
    }, 100);
  });
};
EOF

git add .
git commit -m "perf: optimize authentication hook with caching

Performance improvements:
- Add session storage cache for user data
- Avoid re-parsing JWT on every mount
- Memoize computed auth properties
- Reduce auth check time from ~200ms to ~5ms

Impact:
- Faster app startup time
- Reduced localStorage reads
- Better user experience on route changes"

# Analizza diff per performance
echo "🚀 ANALISI PERFORMANCE DIFF:"
git diff HEAD~1 HEAD --word-diff | grep -E "(cache|memo|performance|optimize)"
```

## 🎓 Workflow Team con Diff

### 1. Pull Request Review Process
```bash
# Simula processo review PR
cat > scripts/pr-review-checklist.sh << 'EOF'
#!/bin/bash
# Checklist automatica per review PR

BRANCH=${1:-HEAD}
BASE=${2:-main}

echo "✅ PR REVIEW CHECKLIST: $BRANCH"
echo "================================"

# 1. Dimensione del PR
LINES_CHANGED=$(git diff $BASE...$BRANCH --numstat | awk '{sum+=$1+$2} END {print sum}')
echo "📏 Linee modificate: $LINES_CHANGED"
if [ $LINES_CHANGED -gt 500 ]; then
    echo "⚠️  PR molto grande (>500 linee) - considera di dividere"
fi

# 2. File modificati
FILES_COUNT=$(git diff $BASE...$BRANCH --name-only | wc -l)
echo "📁 File modificati: $FILES_COUNT"

# 3. Test coverage
if git diff $BASE...$BRANCH --name-only | grep -q "\.test\."; then
    echo "✅ Test files presenti"
else
    echo "❌ Nessun test trovato"
fi

# 4. Breaking changes
if git log $BASE..$BRANCH --grep="BREAKING" | grep -q "BREAKING"; then
    echo "🚨 BREAKING CHANGES rilevati"
fi

# 5. Security check
if git diff $BASE...$BRANCH | grep -q -E "(password|secret|api.?key|token)"; then
    echo "🔒 Possibili informazioni sensibili nel diff"
fi

# 6. Performance considerations
if git diff $BASE...$BRANCH | grep -q -E "(useEffect|useMemo|useCallback)"; then
    echo "⚡ Hook React performance-related modificati"
fi

echo -e "\n📋 PUNTI DI ATTENZIONE:"
git diff $BASE...$BRANCH | grep -E "(TODO|FIXME|console\.log|debugger)" || echo "✅ Nessun debug statement"
EOF

chmod +x scripts/pr-review-checklist.sh
bash scripts/pr-review-checklist.sh
```

### 2. Diff per Documentazione Automatica
```bash
# Script per generare changelog da diff
cat > scripts/generate-changelog.sh << 'EOF'
#!/bin/bash
# Genera changelog automatico da diff

FROM_TAG=${1:-$(git describe --tags --abbrev=0)}
TO_TAG=${2:-HEAD}

echo "# Changelog: $FROM_TAG → $TO_TAG"
echo "================================="

echo -e "\n## 🚀 Nuove Funzionalità"
git log $FROM_TAG..$TO_TAG --grep="feat:" --pretty=format:"- %s (%h)" | sed 's/feat: //'

echo -e "\n## 🐛 Bug Fix"  
git log $FROM_TAG..$TO_TAG --grep="fix:" --pretty=format:"- %s (%h)" | sed 's/fix: //'

echo -e "\n## 📚 Documentazione"
git log $FROM_TAG..$TO_TAG --grep="docs:" --pretty=format:"- %s (%h)" | sed 's/docs: //'

echo -e "\n## 🎨 Miglioramenti"
git log $FROM_TAG..$TO_TAG --grep="refactor:" --pretty=format:"- %s (%h)" | sed 's/refactor: //'

echo -e "\n## ⚡ Performance"
git log $FROM_TAG..$TO_TAG --grep="perf:" --pretty=format:"- %s (%h)" | sed 's/perf: //'

echo -e "\n## 📊 Statistiche"
echo "- File modificati: $(git diff $FROM_TAG..$TO_TAG --name-only | wc -l)"
echo "- Linee aggiunte: $(git diff $FROM_TAG..$TO_TAG --numstat | awk '{sum+=$1} END {print sum}')"
echo "- Linee rimosse: $(git diff $FROM_TAG..$TO_TAG --numstat | awk '{sum+=$2} END {print sum}')"
echo "- Contributor: $(git log $FROM_TAG..$TO_TAG --pretty=format:'%an' | sort | uniq | wc -l)"
EOF

chmod +x scripts/generate-changelog.sh
git add scripts/
git commit -m "tools: add automatic changelog generation from diff"

# Genera changelog di esempio
bash scripts/generate-changelog.sh HEAD~10 HEAD
```

## 🎓 Quiz di Verifica

1. **Qual è la differenza tra `git diff branch1..branch2` e `git diff branch1...branch2`?**
2. **Come usi git diff per trovare quando è stata introdotta una specifica funzione?**
3. **Come configuri un tool esterno per visualizzare diff graficamente?**

### Risposte
1. **`..` mostra diff tra tip di branch, `...` mostra diff dal common ancestor**
2. **`git log -L :functionName:file.js` o `git log -p -S "function content"`**
3. **`git config diff.tool toolname` e `git config difftool.toolname.cmd 'command'`**

## 🔗 Comandi Correlati

- `git log -p` - Log con diff completo
- `git show` - Diff di commit specifico  
- `git blame` - Chi ha modificato ogni riga
- `git bisect` - Debug binario con diff
- `git difftool` - Diff con tool grafici

## 📚 Risorse Aggiuntive

- [Git Diff Documentation](https://git-scm.com/docs/git-diff)
- [Advanced Diffing](https://git-scm.com/book/en/v2/Git-Tools-Advanced-Merging)
- [Diff Tool Configuration](https://git-scm.com/docs/git-difftool)
- [Git Attributes for Diff](https://git-scm.com/book/en/v2/Customizing-Git-Git-Attributes)

---

**Completato**: Hai completato gli esempi pratici dei comandi base Git!

**Prossimo**: [Esercizi di Consolidamento](../esercizi/) - Metti alla prova le tue competenze
