# Esempio 01: Correzione Errori con Commit Avanzati

## Obiettivo
Dimostrare come correggere errori comuni utilizzando tecniche avanzate di commit come `--amend`, `reset` e `revert` in scenari realistici.

## Scenario: Sviluppo Feature Login

Stai sviluppando una feature di login e commetti diversi errori tipici che dovrai correggere.

### 1. Setup Progetto
```bash
mkdir ~/commit-correction-demo
cd ~/commit-correction-demo
git init

# Struttura iniziale
mkdir -p src/{components,utils,api}
mkdir -p tests
```

### 2. Primo Commit con Errore nel Messaggio
```bash
# Crea file iniziale
cat > src/components/LoginForm.js << 'EOF'
import React, { useState } from 'react';

const LoginForm = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');

  return (
    <div>
      <h2>Login</h2>
      <form>
        <input 
          type="email" 
          value={email}
          onChange={(e) => setEmail(e.target.value)}
          placeholder="Email"
        />
        <input 
          type="password" 
          value={password}
          onChange={(e) => setPassword(e.target.value)}
          placeholder="Password"
        />
        <button type="submit">Login</button>
      </form>
    </div>
  );
};

export default LoginForm;
EOF

# Commit con messaggio errato
git add src/components/LoginForm.js
git commit -m "add login form"  # Messaggio non convenzionale
```

### 3. Correzione Messaggio con --amend
```bash
# Correzione del messaggio dell'ultimo commit
git commit --amend -m "feat: implement basic login form component

- Add LoginForm React component with email/password fields
- Include basic form structure without validation
- Prepare foundation for authentication logic"

# Verifica correzione
git log --oneline -1
```

### 4. Commit con File Dimenticato
```bash
# Aggiungi validazione ma dimentica di includere utils
cat > src/utils/validation.js << 'EOF'
export const validateEmail = (email) => {
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  return emailRegex.test(email);
};

export const validatePassword = (password) => {
  return password.length >= 8;
};

export const validateForm = (email, password) => {
  return {
    isValid: validateEmail(email) && validatePassword(password),
    errors: {
      email: !validateEmail(email) ? 'Invalid email format' : '',
      password: !validatePassword(password) ? 'Password must be at least 8 characters' : ''
    }
  };
};
EOF

# Aggiorna LoginForm per usare validation
cat > src/components/LoginForm.js << 'EOF'
import React, { useState } from 'react';
import { validateForm } from '../utils/validation';

const LoginForm = () => {
  const [email, setEmail] = useState('');
  const [password, setPassword] = useState('');
  const [errors, setErrors] = useState({});

  const handleSubmit = (e) => {
    e.preventDefault();
    const validation = validateForm(email, password);
    
    if (validation.isValid) {
      console.log('Form is valid, proceeding with login...');
    } else {
      setErrors(validation.errors);
    }
  };

  return (
    <div>
      <h2>Login</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <input 
            type="email" 
            value={email}
            onChange={(e) => setEmail(e.target.value)}
            placeholder="Email"
          />
          {errors.email && <span style={{color: 'red'}}>{errors.email}</span>}
        </div>
        <div>
          <input 
            type="password" 
            value={password}
            onChange={(e) => setPassword(e.target.value)}
            placeholder="Password"
          />
          {errors.password && <span style={{color: 'red'}}>{errors.password}</span>}
        </div>
        <button type="submit">Login</button>
      </form>
    </div>
  );
};

export default LoginForm;
EOF

# Commit dimenticando il file validation.js
git add src/components/LoginForm.js
git commit -m "feat: add form validation to login component"
```

### 5. Correzione con --amend (File Mancante)
```bash
# Aggiungi il file dimenticato al commit precedente
git add src/utils/validation.js
git commit --amend --no-edit  # Mantiene il messaggio esistente

# Verifica che entrambi i file siano nel commit
git show --name-only
```

### 6. Commit con Errore nel Codice
```bash
# Aggiungi API call con bug
cat > src/api/auth.js << 'EOF'
const API_BASE = 'https://api.example.com';

export const loginUser = async (email, password) => {
  try {
    const response = await fetch(`${API_BASE}/auth/login`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        email: email,
        password: password,
        // BUG: campo extra che causa errore
        extraField: 'shouldNotBeHere'
      }),
    });

    if (!response.ok) {
      throw new Error('Login failed');
    }

    const data = await response.json();
    // BUG: non gestisce il token correttamente
    return data.user;  // Dovrebbe restituire data.token
  } catch (error) {
    console.error('Login error:', error);
    throw error;
  }
};
EOF

git add src/api/auth.js
git commit -m "feat: implement login API integration"
```

### 7. Scoperta dell'Errore e Reset
```bash
# Simula testing che rivela il bug
echo "❌ Test failed: Login API returns wrong data"
echo "❌ Extra field causes server error"

# Decidi di rifare completamente il commit
git reset --soft HEAD~1  # Mantiene i file in staging

# Correggi il codice
cat > src/api/auth.js << 'EOF'
const API_BASE = 'https://api.example.com';

export const loginUser = async (email, password) => {
  try {
    const response = await fetch(`${API_BASE}/auth/login`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        email,
        password
      }),
    });

    if (!response.ok) {
      throw new Error(`Login failed: ${response.status}`);
    }

    const data = await response.json();
    // Gestisce correttamente token e user data
    return {
      token: data.token,
      user: data.user
    };
  } catch (error) {
    console.error('Login error:', error);
    throw error;
  }
};

export const logoutUser = () => {
  localStorage.removeItem('authToken');
  localStorage.removeItem('userData');
};
EOF

# Commit corretto
git add src/api/auth.js
git commit -m "feat: implement secure login API integration

- Add proper login endpoint integration
- Return both token and user data
- Include logout functionality
- Add comprehensive error handling"
```

### 8. Commit Pubblico con Errore (Usa Revert)
```bash
# Simula che il commit sia già stato pushato
echo "⚠️  Commit è stato già pushato al repository remoto"

# Aggiungi feature problematica
cat > src/components/SecurityHole.js << 'EOF'
// QUESTO È UN ESEMPIO DI CODICE PROBLEMATICO
export const unsafeFunction = (userInput) => {
  // VULNERABILITÀ: eval di input utente
  return eval(userInput);
};

export const exposeSecrets = () => {
  // VULNERABILITÀ: espone informazioni sensibili
  return {
    apiKey: 'sk_live_12345',
    dbPassword: 'password123'
  };
};
EOF

git add src/components/SecurityHole.js
git commit -m "feat: add utility functions for dynamic operations"

# Simulare push
echo "git push origin main  # (simulato - commit ora è pubblico)"
```

### 9. Correzione con Revert
```bash
# Scoperta della vulnerabilità dopo il push
echo "🚨 SECURITY ALERT: Vulnerabilità critiche trovate nel commit $(git rev-parse HEAD)"

# Usa revert per annullare pubblicamente
git revert HEAD --no-edit

# Verifica che il file problematico sia stato rimosso
ls src/components/SecurityHole.js 2>/dev/null || echo "✅ File vulnerabile rimosso"

# Guarda la cronologia
git log --oneline -4
```

### 10. Reset vs Revert - Dimostrazione Differenze
```bash
# Crea scenario per mostrare differenze
echo 'console.log("temporary feature");' > temp-feature.js
git add temp-feature.js
git commit -m "temp: add temporary feature"

echo "=== RESET (cambia storia) ==="
echo "Prima del reset:"
git log --oneline -2

# Reset rimuove dalla storia
git reset --hard HEAD~1

echo "Dopo il reset:"
git log --oneline -2
echo "Il commit temporaneo è sparito dalla storia"

# Ricrea per mostrare revert
git add temp-feature.js
git commit -m "temp: add temporary feature"

echo -e "\n=== REVERT (mantiene storia) ==="
echo "Prima del revert:"
git log --oneline -2

# Revert crea nuovo commit
git revert HEAD --no-edit

echo "Dopo il revert:"
git log --oneline -3
echo "Il commit temporaneo è ancora nella storia, ma annullato"
```

## Riepilogo Tecniche

### 1. git commit --amend
**Quando usare:** Ultimo commit non ancora pushato
```bash
# Correggere messaggio
git commit --amend -m "nuovo messaggio"

# Aggiungere file dimenticato
git add file-dimenticato
git commit --amend --no-edit

# Modificare file nell'ultimo commit
git add file-modificato
git commit --amend
```

### 2. git reset
**Quando usare:** Commit locali da rifare completamente
```bash
# Mantieni modifiche in staging
git reset --soft HEAD~1

# Mantieni modifiche nel working directory
git reset --mixed HEAD~1  # (default)

# Elimina tutto (PERICOLOSO)
git reset --hard HEAD~1
```

### 3. git revert
**Quando usare:** Commit già pushati/pubblici
```bash
# Revert singolo commit
git revert <commit-hash>

# Revert ultimo commit
git revert HEAD

# Revert range di commit
git revert HEAD~3..HEAD
```

## Best Practices

### ✅ Cosa Fare
- Usa `--amend` per correzioni immediate pre-push
- Usa `revert` per commit già condivisi
- Sempre backup prima di operazioni distruttive
- Scrivi messaggi commit chiari fin dall'inizio

### ❌ Cosa NON Fare
- Non usare `reset --hard` su commit pushati
- Non ammendare commit già pushati (se collabori con altri)
- Non resettare la storia pubblica
- Non nascondere errori - documenta le correzioni

## Troubleshooting Comuni

### Amend Fallito
```bash
# Se amend non funziona, verifica:
git status
git log --oneline -1

# Potrebbe essere necessario unstage:
git reset HEAD~1
git add file-corretto
git commit -m "messaggio corretto"
```

### Revert con Conflitti
```bash
# Se revert crea conflitti:
git revert <commit> --no-commit
# Risolvi conflitti manualmente
git add .
git commit -m "revert: remove problematic feature"
```

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Modulo Precedente](../08-Visualizzare-Storia-Commit/README.md)
- [➡️ Modulo Successivo](../10-Navigare-tra-Commit/README.md)
