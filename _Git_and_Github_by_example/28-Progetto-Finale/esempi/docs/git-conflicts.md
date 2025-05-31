# Git Conflicts Resolution Guide

## Understanding Merge Conflicts

### 1. Types of Conflicts

#### Text Conflicts
```bash
# Scenario: Due sviluppatori modificano la stessa linea
# File: utils.js

<<<<<<< HEAD (current branch)
function calculateTotal(price, tax) {
    return price * (1 + tax);
}
=======
function calculateTotal(price, taxRate) {
    return price + (price * taxRate);
}
>>>>>>> feature/tax-calculation (incoming branch)
```

#### Rename Conflicts
```bash
# Scenario: File rinominato in entrambi i branch
git status
# both modified: oldname.js -> newname1.js
# both modified: oldname.js -> newname2.js
```

#### Content vs Delete Conflicts
```bash
# Scenario: Un branch modifica file, altro lo cancella
git status
# deleted by us: deprecated-module.js
# modified by them: deprecated-module.js
```

### 2. Prevention Strategies

#### Frequent Integration
```bash
# Best Practice: Sincronizzazione frequente
git checkout feature/my-feature
git fetch origin
git rebase origin/develop  # Invece di merge

# Automated conflict detection
git merge-tree $(git merge-base HEAD origin/develop) HEAD origin/develop
```

#### Small, Focused Commits
```bash
# ❌ Large commits increase conflict probability
git add .
git commit -m "Massive refactor of authentication system"

# ✅ Atomic commits reduce conflicts
git add src/auth/login.js
git commit -m "feat: add email validation to login form"

git add src/auth/password.js  
git commit -m "feat: implement password strength checker"

git add tests/auth/login.test.js
git commit -m "test: add login form validation tests"
```

#### Code Ownership & Communication
```javascript
// .github/CODEOWNERS
# Global owners
* @team-leads

# Frontend components
src/components/ @frontend-team
src/styles/ @frontend-team

# Backend services  
src/api/ @backend-team
src/database/ @backend-team @db-admin

# Infrastructure
docker/ @devops-team
.github/ @devops-team

# Critical files require multiple approvals
package.json @team-leads @senior-devs
tsconfig.json @team-leads @senior-devs
```

### 3. Conflict Resolution Workflow

#### Step-by-Step Resolution
```bash
# 1. Identify conflict type
git status
git diff --check  # Show whitespace conflicts

# 2. Open merge tool
git mergetool
# Or use VS Code
code .

# 3. Manual resolution strategy
# a) Understand both changes
git log --oneline HEAD...MERGE_HEAD
git show HEAD  # Your changes
git show MERGE_HEAD  # Their changes

# b) Choose resolution approach
# - Keep yours: git checkout --ours conflicted-file.js
# - Keep theirs: git checkout --theirs conflicted-file.js  
# - Manual merge: Edit file directly
# - Combination: Merge both changes intelligently

# 4. Test resolution
npm test
npm run lint

# 5. Complete merge
git add resolved-file.js
git commit -m "resolve: merge conflict in authentication logic"
```

#### Advanced Resolution Techniques
```bash
# Three-way merge visualization
git show :1:filename  # Common ancestor
git show :2:filename  # Current branch (HEAD)
git show :3:filename  # Incoming branch (MERGE_HEAD)

# Interactive rebase for conflict resolution
git rebase -i HEAD~3
# Mark commits as 'edit' to resolve conflicts individually

# Rerere (reuse recorded resolution)
git config rerere.enabled true
# Git remembers conflict resolutions for future use
```

### 4. Complex Conflict Scenarios

#### Scenario 1: API Schema Changes
```javascript
// Branch A: Adds new field
const userSchema = {
    id: Number,
    name: String,
    email: String,
    avatar: String  // ← Added in branch A
};

// Branch B: Restructures schema
const userSchema = {
    id: Number,
    profile: {       // ← Restructured in branch B
        name: String,
        email: String
    }
};

// Resolution: Combine both changes
const userSchema = {
    id: Number,
    profile: {
        name: String,
        email: String,
        avatar: String  // Include new field in new structure
    }
};
```

#### Scenario 2: Database Migration Conflicts
```sql
-- Migration 001 (Branch A): Add column
ALTER TABLE users ADD COLUMN avatar_url VARCHAR(255);

-- Migration 001 (Branch B): Add different column  
ALTER TABLE users ADD COLUMN profile_picture TEXT;

-- Resolution: Create new migration combining both
-- 001_add_user_avatar_fields.sql
ALTER TABLE users ADD COLUMN avatar_url VARCHAR(255);
ALTER TABLE users ADD COLUMN profile_picture TEXT;
```

#### Scenario 3: Dependency Conflicts
```json
// package.json conflicts
{
  "dependencies": {
<<<<<<< HEAD
    "react": "^18.2.0",
    "axios": "^1.3.0"
=======
    "react": "^18.1.0", 
    "lodash": "^4.17.21"
>>>>>>> feature/utilities
  }
}

// Resolution strategy
{
  "dependencies": {
    "react": "^18.2.0",    // Keep newer version
    "axios": "^1.3.0",     // Keep from both branches
    "lodash": "^4.17.21"   // Keep from both branches
  }
}
```

### 5. Tools for Conflict Resolution

#### VS Code Integration
```json
// .vscode/settings.json
{
    "merge-conflict.autoNavigateNextConflict.enabled": true,
    "merge-conflict.decorators.enabled": true,
    "git.mergeEditor": true,
    "diffEditor.renderSideBySide": true
}
```

#### Command Line Tools
```bash
# Git built-in merge tools
git config merge.tool vimdiff
git config merge.tool code  # VS Code
git config merge.tool meld   # Meld (Linux)

# External diff tools
git config diff.tool beyond-compare
git config difftool.bc.cmd 'bcomp "$LOCAL" "$REMOTE"'

# Custom merge driver for specific files
# .gitattributes
*.json merge=json-merge

# .git/config
[merge "json-merge"]
    driver = jq -s '.[0] * .[1]' %O %A %B > %A
```

#### Automated Conflict Resolution
```javascript
// Git hooks for conflict prevention
// .git/hooks/pre-commit
#!/bin/sh
# Check for potential conflicts before commit

# Run tests
npm test || exit 1

# Check for merge conflict markers
git diff --cached --check || exit 1

# Validate JSON files
for file in $(git diff --cached --name-only | grep '\.json$'); do
    jq . "$file" >/dev/null || exit 1
done
```

### 6. Post-Resolution Best Practices

#### Verification Checklist
```markdown
**After Resolving Conflicts:**
- [ ] All conflict markers removed (<<<, ===, >>>)
- [ ] Code compiles without errors
- [ ] All tests pass
- [ ] Functionality works as expected
- [ ] No accidental code deletion
- [ ] Commit message describes resolution
- [ ] Team notified of complex resolutions
```

#### Communication Protocol
```javascript
// Slack notification for complex conflicts
const conflictNotification = {
    channel: '#dev-team',
    message: `
🔀 **Complex Merge Conflict Resolved**

**Branches**: feature/auth-refactor ← develop
**Files affected**: 
- src/auth/login.js (logic changes)
- package.json (dependency updates)
- database/migrations/ (schema conflicts)

**Resolution**: Combined new validation logic with existing error handling
**Testing**: All auth tests passing ✅
**Review needed**: @team-lead please verify auth flow

**Commit**: abc123f
    `
};
```

#### Learning from Conflicts
```javascript
// Conflict analysis script
function analyzeConflicts() {
    const conflictLog = execSync('git log --grep="resolve:" --oneline').toString();
    const patterns = {
        fileTypes: extractFileTypes(conflictLog),
        frequency: calculateConflictFrequency(),
        hotspots: identifyConflictHotspots(),
        resolution_time: measureResolutionTime()
    };
    
    return {
        summary: `${patterns.frequency.total} conflicts resolved this sprint`,
        improvements: [
            'Consider refactoring high-conflict areas',
            'Improve communication for concurrent work',
            'Add more atomic commits for easier resolution'
        ]
    };
}
```

### 7. Conflict Resolution Strategies

#### By File Type
```bash
# JavaScript/TypeScript
# Strategy: Combine functionality, maintain types
git checkout --theirs src/types.ts  # Keep type definitions
# Manually merge implementation files

# CSS/SCSS  
# Strategy: Combine selectors, avoid duplicate rules
git merge-file styles.css styles.css.orig styles.css.theirs

# Configuration files
# Strategy: Merge conservatively, test thoroughly
# package.json, tsconfig.json, webpack.config.js

# Documentation
# Strategy: Combine information, maintain consistency
# README.md, API docs, comments
```

#### By Conflict Complexity
```javascript
const resolutionStrategies = {
    simple: {
        description: "Non-overlapping changes in same file",
        approach: "Accept both changes",
        time: "< 5 minutes"
    },
    
    moderate: {
        description: "Overlapping logic changes",
        approach: "Understand intent, combine functionality",
        time: "15-30 minutes"  
    },
    
    complex: {
        description: "Architectural changes or refactoring",
        approach: "Team discussion, possibly rewrite section",
        time: "1+ hours"
    },
    
    impossible: {
        description: "Fundamental approach conflicts",
        approach: "Escalate to architecture review",
        time: "Meeting required"
    }
};
```

Questa guida fornisce strumenti e strategie complete per gestire e risolvere conflitti Git in modo efficace nel progetto finale.
