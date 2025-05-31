# Esempio 02: Workflow Professionale di Commit

## Obiettivo
Dimostrare un workflow professionale di commit con conventional commits, atomic commits e gestione avanzata delle modifiche in un contesto di sviluppo reale.

## Scenario: Sviluppo E-commerce

Stai sviluppando un'applicazione e-commerce. Devi implementare funzionalità seguendo best practices professionali di commit.

### 1. Setup Progetto Professionale
```bash
mkdir ~/professional-commit-workflow
cd ~/professional-commit-workflow
git init

# Configurazione professionale
git config user.name "Developer Pro"
git config user.email "dev@company.com"

# Setup commit template
cat > .gitmessage << 'EOF'
# <type>(<scope>): <subject>
#
# <body>
#
# <footer>
#
# Types: feat, fix, docs, style, refactor, test, chore
# Scope: component, service, util, config, etc.
# Subject: imperative mood, no period, max 50 chars
# Body: what and why, wrap at 72 chars
# Footer: breaking changes, issue references
EOF

git config commit.template .gitmessage

# Struttura progetto
mkdir -p src/{components,services,utils,config}
mkdir -p tests/{unit,integration}
mkdir -p docs
```

### 2. Commit Template e Conventional Commits

#### Setup di Base (Atomic Commit)
```bash
# Primo commit: setup di base
cat > package.json << 'EOF'
{
  "name": "ecommerce-app",
  "version": "1.0.0",
  "description": "Professional e-commerce application",
  "main": "index.js",
  "scripts": {
    "start": "node src/index.js",
    "test": "jest",
    "lint": "eslint src/"
  },
  "keywords": ["ecommerce", "nodejs", "express"],
  "author": "Developer Team",
  "license": "MIT"
}
EOF

git add package.json
git commit -m "chore: initialize project with package.json

- Set up basic Node.js project structure
- Configure npm scripts for start, test, and lint
- Add project metadata and dependencies"
```

#### Configurazione Environment (Atomic Commit)
```bash
cat > src/config/database.js << 'EOF'
const config = {
  development: {
    host: process.env.DB_HOST || 'localhost',
    port: process.env.DB_PORT || 5432,
    database: process.env.DB_NAME || 'ecommerce_dev',
    username: process.env.DB_USER || 'postgres',
    password: process.env.DB_PASS || 'password'
  },
  test: {
    host: process.env.TEST_DB_HOST || 'localhost',
    port: process.env.TEST_DB_PORT || 5432,
    database: process.env.TEST_DB_NAME || 'ecommerce_test'
  },
  production: {
    host: process.env.PROD_DB_HOST,
    port: process.env.PROD_DB_PORT,
    database: process.env.PROD_DB_NAME,
    username: process.env.PROD_DB_USER,
    password: process.env.PROD_DB_PASS
  }
};

module.exports = config[process.env.NODE_ENV || 'development'];
EOF

cat > .env.example << 'EOF'
# Database Configuration
DB_HOST=localhost
DB_PORT=5432
DB_NAME=ecommerce_dev
DB_USER=postgres
DB_PASS=password

# API Configuration
API_PORT=3000
JWT_SECRET=your-secret-key
EOF

git add src/config/database.js .env.example
git commit -m "config: add database configuration for multiple environments

- Support for development, test, and production environments
- Environment variables for secure credential management
- Include .env.example template for team setup

Refs: #CONFIG-001"
```

### 3. Feature Development con Commits Atomici

#### User Service Implementation
```bash
# Step 1: Modello User (solo modello)
cat > src/models/User.js << 'EOF'
class User {
  constructor(id, email, username, passwordHash, createdAt = new Date()) {
    this.id = id;
    this.email = email;
    this.username = username;
    this.passwordHash = passwordHash;
    this.createdAt = createdAt;
    this.isActive = true;
  }

  static validate(userData) {
    const errors = [];
    
    if (!userData.email || !this.isValidEmail(userData.email)) {
      errors.push('Valid email is required');
    }
    
    if (!userData.username || userData.username.length < 3) {
      errors.push('Username must be at least 3 characters');
    }
    
    if (!userData.password || userData.password.length < 8) {
      errors.push('Password must be at least 8 characters');
    }
    
    return {
      isValid: errors.length === 0,
      errors
    };
  }

  static isValidEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
  }

  toJSON() {
    const { passwordHash, ...publicData } = this;
    return publicData;
  }
}

module.exports = User;
EOF

git add src/models/User.js
git commit -m "feat(user): implement User model with validation

- Add User class with basic properties and validation
- Include email format validation
- Implement secure JSON serialization (excludes password)
- Add static validation method for user data

Closes: #USER-001"
```

#### Step 2: User Service (solo logica business)
```bash
cat > src/services/UserService.js << 'EOF'
const User = require('../models/User');
const bcrypt = require('bcryptjs');

class UserService {
  constructor(dbConnection) {
    this.db = dbConnection;
  }

  async createUser(userData) {
    // Validate input
    const validation = User.validate(userData);
    if (!validation.isValid) {
      throw new Error(`Validation failed: ${validation.errors.join(', ')}`);
    }

    // Check if user already exists
    const existingUser = await this.findByEmail(userData.email);
    if (existingUser) {
      throw new Error('User with this email already exists');
    }

    // Hash password
    const saltRounds = 12;
    const passwordHash = await bcrypt.hash(userData.password, saltRounds);

    // Create user
    const user = new User(
      null, // ID will be assigned by database
      userData.email,
      userData.username,
      passwordHash
    );

    // Save to database (mock implementation)
    const savedUser = await this.save(user);
    return savedUser;
  }

  async findByEmail(email) {
    // Mock database query
    // In real implementation: SELECT * FROM users WHERE email = ?
    return null;
  }

  async findById(id) {
    // Mock database query
    return null;
  }

  async save(user) {
    // Mock database save
    // In real implementation: INSERT INTO users...
    user.id = Math.random().toString(36).substr(2, 9);
    return user;
  }

  async authenticateUser(email, password) {
    const user = await this.findByEmail(email);
    if (!user) {
      throw new Error('Invalid credentials');
    }

    const isValidPassword = await bcrypt.compare(password, user.passwordHash);
    if (!isValidPassword) {
      throw new Error('Invalid credentials');
    }

    return user;
  }
}

module.exports = UserService;
EOF

git add src/services/UserService.js
git commit -m "feat(user): implement UserService with authentication

- Add user creation with password hashing
- Implement secure authentication with bcrypt
- Include duplicate email validation
- Add database interaction methods (mocked)

Refs: #USER-002"
```

#### Step 3: Tests (commit separato per i test)
```bash
cat > tests/unit/UserService.test.js << 'EOF'
const UserService = require('../../src/services/UserService');
const User = require('../../src/models/User');

describe('UserService', () => {
  let userService;

  beforeEach(() => {
    userService = new UserService(null); // Mock DB connection
  });

  describe('createUser', () => {
    test('should create user with valid data', async () => {
      const userData = {
        email: 'test@example.com',
        username: 'testuser',
        password: 'password123'
      };

      const result = await userService.createUser(userData);
      
      expect(result).toBeDefined();
      expect(result.email).toBe(userData.email);
      expect(result.username).toBe(userData.username);
      expect(result.passwordHash).toBeDefined();
      expect(result.passwordHash).not.toBe(userData.password);
    });

    test('should throw error for invalid email', async () => {
      const userData = {
        email: 'invalid-email',
        username: 'testuser',
        password: 'password123'
      };

      await expect(userService.createUser(userData))
        .rejects.toThrow('Validation failed');
    });

    test('should throw error for short password', async () => {
      const userData = {
        email: 'test@example.com',
        username: 'testuser',
        password: '123'
      };

      await expect(userService.createUser(userData))
        .rejects.toThrow('Password must be at least 8 characters');
    });
  });
});
EOF

git add tests/unit/UserService.test.js
git commit -m "test(user): add comprehensive UserService unit tests

- Test user creation with valid data
- Test validation error handling
- Test password security requirements
- Achieve 100% coverage for UserService

Refs: #TEST-001"
```

### 4. Commit di Refactoring

#### Refactoring per migliorare l'architettura
```bash
# Extract validation logic
mkdir -p src/validators
cat > src/validators/UserValidator.js << 'EOF'
class UserValidator {
  static validate(userData) {
    const errors = [];
    
    // Email validation
    if (!userData.email) {
      errors.push('Email is required');
    } else if (!this.isValidEmail(userData.email)) {
      errors.push('Invalid email format');
    }
    
    // Username validation
    if (!userData.username) {
      errors.push('Username is required');
    } else if (userData.username.length < 3) {
      errors.push('Username must be at least 3 characters');
    } else if (userData.username.length > 30) {
      errors.push('Username must not exceed 30 characters');
    } else if (!/^[a-zA-Z0-9_]+$/.test(userData.username)) {
      errors.push('Username can only contain letters, numbers, and underscores');
    }
    
    // Password validation
    if (!userData.password) {
      errors.push('Password is required');
    } else {
      const passwordErrors = this.validatePassword(userData.password);
      errors.push(...passwordErrors);
    }
    
    return {
      isValid: errors.length === 0,
      errors
    };
  }

  static validatePassword(password) {
    const errors = [];
    
    if (password.length < 8) {
      errors.push('Password must be at least 8 characters');
    }
    
    if (!/[A-Z]/.test(password)) {
      errors.push('Password must contain at least one uppercase letter');
    }
    
    if (!/[a-z]/.test(password)) {
      errors.push('Password must contain at least one lowercase letter');
    }
    
    if (!/\d/.test(password)) {
      errors.push('Password must contain at least one number');
    }
    
    return errors;
  }

  static isValidEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
  }
}

module.exports = UserValidator;
EOF

# Update User model to use validator
cat > src/models/User.js << 'EOF'
const UserValidator = require('../validators/UserValidator');

class User {
  constructor(id, email, username, passwordHash, createdAt = new Date()) {
    this.id = id;
    this.email = email;
    this.username = username;
    this.passwordHash = passwordHash;
    this.createdAt = createdAt;
    this.isActive = true;
  }

  static validate(userData) {
    return UserValidator.validate(userData);
  }

  toJSON() {
    const { passwordHash, ...publicData } = this;
    return publicData;
  }
}

module.exports = User;
EOF

git add src/validators/UserValidator.js src/models/User.js
git commit -m "refactor(user): extract validation logic to dedicated validator

- Move validation logic from User model to UserValidator
- Implement stronger password requirements
- Add username format validation
- Improve separation of concerns

Breaking Change: Password requirements are now stricter
Refs: #REFACTOR-001"
```

### 5. Bug Fix Workflow

#### Simulate bug discovery
```bash
# Create bug scenario
echo "🐛 BUG DISCOVERED: Users can create account with same username"

# Fix the bug
cat > src/services/UserService.js << 'EOF'
const User = require('../models/User');
const bcrypt = require('bcryptjs');

class UserService {
  constructor(dbConnection) {
    this.db = dbConnection;
  }

  async createUser(userData) {
    // Validate input
    const validation = User.validate(userData);
    if (!validation.isValid) {
      throw new Error(`Validation failed: ${validation.errors.join(', ')}`);
    }

    // Check if user already exists by email
    const existingUserByEmail = await this.findByEmail(userData.email);
    if (existingUserByEmail) {
      throw new Error('User with this email already exists');
    }

    // BUG FIX: Check if username already exists
    const existingUserByUsername = await this.findByUsername(userData.username);
    if (existingUserByUsername) {
      throw new Error('User with this username already exists');
    }

    // Hash password
    const saltRounds = 12;
    const passwordHash = await bcrypt.hash(userData.password, saltRounds);

    // Create user
    const user = new User(
      null,
      userData.email,
      userData.username,
      passwordHash
    );

    const savedUser = await this.save(user);
    return savedUser;
  }

  async findByEmail(email) {
    // Mock database query
    return null;
  }

  async findByUsername(username) {
    // Mock database query - NEW METHOD
    return null;
  }

  async findById(id) {
    return null;
  }

  async save(user) {
    user.id = Math.random().toString(36).substr(2, 9);
    return user;
  }

  async authenticateUser(email, password) {
    const user = await this.findByEmail(email);
    if (!user) {
      throw new Error('Invalid credentials');
    }

    const isValidPassword = await bcrypt.compare(password, user.passwordHash);
    if (!isValidPassword) {
      throw new Error('Invalid credentials');
    }

    return user;
  }
}

module.exports = UserService;
EOF

# Add regression test
cat > tests/unit/UserService.test.js << 'EOF'
const UserService = require('../../src/services/UserService');
const User = require('../../src/models/User');

describe('UserService', () => {
  let userService;

  beforeEach(() => {
    userService = new UserService(null);
  });

  describe('createUser', () => {
    test('should create user with valid data', async () => {
      const userData = {
        email: 'test@example.com',
        username: 'testuser',
        password: 'Password123'
      };

      const result = await userService.createUser(userData);
      
      expect(result).toBeDefined();
      expect(result.email).toBe(userData.email);
      expect(result.username).toBe(userData.username);
    });

    test('should throw error for invalid email', async () => {
      const userData = {
        email: 'invalid-email',
        username: 'testuser',
        password: 'Password123'
      };

      await expect(userService.createUser(userData))
        .rejects.toThrow('Validation failed');
    });

    test('should throw error for weak password', async () => {
      const userData = {
        email: 'test@example.com',
        username: 'testuser',
        password: 'weak'
      };

      await expect(userService.createUser(userData))
        .rejects.toThrow('Password must');
    });

    // BUG FIX TEST
    test('should prevent duplicate usernames', async () => {
      // Mock findByUsername to return existing user
      userService.findByUsername = jest.fn().mockResolvedValue({
        id: '123',
        username: 'existinguser'
      });

      const userData = {
        email: 'new@example.com',
        username: 'existinguser',
        password: 'Password123'
      };

      await expect(userService.createUser(userData))
        .rejects.toThrow('User with this username already exists');
    });
  });
});
EOF

git add src/services/UserService.js tests/unit/UserService.test.js
git commit -m "fix(user): prevent duplicate username registration

- Add username uniqueness validation in UserService
- Implement findByUsername method for duplicate check
- Add regression test for duplicate username prevention

Fixes: #BUG-042
Reported-by: QA Team
Tested-by: Unit Tests"
```

### 6. Documentation Commit
```bash
cat > docs/API.md << 'EOF'
# User Service API Documentation

## UserService Class

### Methods

#### createUser(userData)
Creates a new user account with validation and security measures.

**Parameters:**
- `userData` (Object): User registration data
  - `email` (string): Valid email address
  - `username` (string): Unique username (3-30 chars, alphanumeric + underscore)
  - `password` (string): Strong password (min 8 chars, uppercase, lowercase, number)

**Returns:** Promise<User> - Created user object (without password hash)

**Throws:**
- Validation error if data is invalid
- Error if email or username already exists

**Example:**
```javascript
const user = await userService.createUser({
  email: 'john@example.com',
  username: 'john_doe',
  password: 'SecurePass123'
});
```

#### authenticateUser(email, password)
Authenticates user with email and password.

**Parameters:**
- `email` (string): User's email
- `password` (string): User's password

**Returns:** Promise<User> - Authenticated user object

**Throws:** Error if credentials are invalid

### Security Features
- Password hashing with bcrypt (12 salt rounds)
- Email and username uniqueness validation
- Strong password requirements
- Secure JSON serialization (excludes password hash)
EOF

git add docs/API.md
git commit -m "docs(user): add comprehensive API documentation

- Document UserService public methods
- Include parameter types and validation rules
- Add usage examples and error handling
- Document security features and best practices

Refs: #DOC-001"
```

### 7. Performance Optimization
```bash
# Add caching utility
cat > src/utils/cache.js << 'EOF'
class SimpleCache {
  constructor(ttlMs = 300000) { // 5 minutes default
    this.cache = new Map();
    this.ttl = ttlMs;
  }

  set(key, value) {
    const expiresAt = Date.now() + this.ttl;
    this.cache.set(key, { value, expiresAt });
  }

  get(key) {
    const item = this.cache.get(key);
    if (!item) return null;
    
    if (Date.now() > item.expiresAt) {
      this.cache.delete(key);
      return null;
    }
    
    return item.value;
  }

  clear() {
    this.cache.clear();
  }
}

module.exports = SimpleCache;
EOF

git add src/utils/cache.js
git commit -m "perf(utils): implement simple TTL cache for performance optimization

- Add SimpleCache class with TTL support
- Automatic expiration of cached items
- Memory-efficient with Map-based storage
- Configurable TTL per cache instance

This will be used to cache user lookups and reduce database queries.

Refs: #PERF-001"
```

## Workflow Summary

### Commits Created
1. **chore**: Project initialization
2. **config**: Environment configuration  
3. **feat(user)**: User model implementation
4. **feat(user)**: User service implementation
5. **test(user)**: Comprehensive testing
6. **refactor(user)**: Validation extraction
7. **fix(user)**: Duplicate username bug
8. **docs(user)**: API documentation
9. **perf(utils)**: Performance optimization

### Best Practices Demonstrated

#### ✅ Atomic Commits
- Each commit represents one logical change
- Single responsibility per commit
- Easy to review and revert

#### ✅ Conventional Commits
- Structured commit messages
- Clear type and scope
- Detailed body when needed

#### ✅ Professional Workflow
- Separate commits for features, tests, docs
- Bug fixes with regression tests
- Performance improvements documented

### Git Log Example
```bash
git log --oneline
# perf(utils): implement simple TTL cache for performance optimization
# docs(user): add comprehensive API documentation  
# fix(user): prevent duplicate username registration
# refactor(user): extract validation logic to dedicated validator
# test(user): add comprehensive UserService unit tests
# feat(user): implement UserService with authentication
# feat(user): implement User model with validation
# config: add database configuration for multiple environments
# chore: initialize project with package.json
```

## Tools e Configurazioni

### Commit Template
Il template `.gitmessage` aiuta a mantenere consistenza:
```bash
git config commit.template .gitmessage
```

### Git Aliases Utili
```bash
git config alias.cz "commit --verbose"
git config alias.amend "commit --amend --no-edit"
git config alias.fixup "commit --fixup"
```

### Validation Hooks
```bash
# Pre-commit hook per validare messaggi
cat > .git/hooks/commit-msg << 'EOF'
#!/bin/bash
commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'
if ! grep -qE "$commit_regex" "$1"; then
    echo "Invalid commit message format!"
    echo "Use: type(scope): description"
    exit 1
fi
EOF
chmod +x .git/hooks/commit-msg
```

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Modulo Precedente](../08-Visualizzare-Storia-Commit/README.md)
- [➡️ Modulo Successivo](../10-Navigare-tra-Commit/README.md)
