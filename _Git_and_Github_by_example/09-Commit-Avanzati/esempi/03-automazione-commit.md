# Esempio 03: Automazione Commit

## Obiettivo
Dimostrare tecniche avanzate di automazione per i commit, inclusi hook, script personalizzati, conventional commits automatici e integrazione con CI/CD.

## Scenario: Automazione Completa del Workflow

Stai configurando un sistema di automazione per standardizzare i commit in un team di sviluppo, garantendo qualità e consistenza.

### 1. Setup Progetto con Automazione
```bash
mkdir ~/automated-commit-workflow
cd ~/automated-commit-workflow
git init

# Struttura progetto
mkdir -p .githooks
mkdir -p scripts
mkdir -p src/{components,utils,services}
mkdir -p tests/{unit,integration}
mkdir -p docs
```

### 2. Automazione Messaggi Commit con Inquirer

#### Script Interactive Commit
```bash
# Crea script per commit guidato
cat > scripts/commit.js << 'EOF'
#!/usr/bin/env node

const { execSync } = require('child_process');
const inquirer = require('inquirer');

const COMMIT_TYPES = [
  { value: 'feat', name: 'feat: A new feature' },
  { value: 'fix', name: 'fix: A bug fix' },
  { value: 'docs', name: 'docs: Documentation only changes' },
  { value: 'style', name: 'style: Code style changes (formatting, etc)' },
  { value: 'refactor', name: 'refactor: Code refactoring' },
  { value: 'test', name: 'test: Adding or updating tests' },
  { value: 'chore', name: 'chore: Build process or auxiliary tool changes' },
  { value: 'perf', name: 'perf: Performance improvements' },
  { value: 'ci', name: 'ci: CI/CD changes' },
  { value: 'build', name: 'build: Build system changes' },
  { value: 'revert', name: 'revert: Revert a previous commit' }
];

const SCOPES = [
  'auth',
  'user',
  'product',
  'cart',
  'payment',
  'api',
  'ui',
  'database',
  'config',
  'utils',
  'security',
  'performance'
];

async function getCommitInfo() {
  console.log('\n🚀 Guided Commit Creator\n');

  // Check if there are staged changes
  try {
    const stagedFiles = execSync('git diff --cached --name-only', { encoding: 'utf8' });
    if (!stagedFiles.trim()) {
      console.log('❌ No staged changes found. Please stage your changes first:');
      console.log('   git add <files>');
      process.exit(1);
    }
    console.log('📁 Staged files:');
    stagedFiles.trim().split('\n').forEach(file => console.log(`   ${file}`));
    console.log('');
  } catch (error) {
    console.log('❌ Error checking staged files');
    process.exit(1);
  }

  const answers = await inquirer.prompt([
    {
      type: 'list',
      name: 'type',
      message: 'Select the type of change:',
      choices: COMMIT_TYPES
    },
    {
      type: 'list',
      name: 'scope',
      message: 'Select the scope of change:',
      choices: [...SCOPES, 'other', 'none']
    },
    {
      type: 'input',
      name: 'customScope',
      message: 'Enter custom scope:',
      when: (answers) => answers.scope === 'other'
    },
    {
      type: 'input',
      name: 'subject',
      message: 'Enter a short description (max 50 chars):',
      validate: (input) => {
        if (input.length === 0) return 'Description is required';
        if (input.length > 50) return 'Description must be 50 characters or less';
        if (input.endsWith('.')) return 'Do not end with a period';
        return true;
      }
    },
    {
      type: 'input',
      name: 'body',
      message: 'Enter a longer description (optional):'
    },
    {
      type: 'confirm',
      name: 'isBreaking',
      message: 'Is this a breaking change?',
      default: false
    },
    {
      type: 'input',
      name: 'breakingDescription',
      message: 'Describe the breaking change:',
      when: (answers) => answers.isBreaking
    },
    {
      type: 'input',
      name: 'issues',
      message: 'Reference issues (e.g. "fixes #123, closes #456"):',
    }
  ]);

  return answers;
}

function formatCommitMessage(answers) {
  const { type, scope, customScope, subject, body, isBreaking, breakingDescription, issues } = answers;
  
  // Determine final scope
  let finalScope = '';
  if (scope && scope !== 'none') {
    finalScope = scope === 'other' ? customScope : scope;
  }

  // Build commit message
  let commitMessage = type;
  if (finalScope) {
    commitMessage += `(${finalScope})`;
  }
  if (isBreaking) {
    commitMessage += '!';
  }
  commitMessage += `: ${subject}`;

  // Add body if provided
  if (body) {
    commitMessage += `\n\n${body}`;
  }

  // Add breaking change footer
  if (isBreaking && breakingDescription) {
    commitMessage += `\n\nBREAKING CHANGE: ${breakingDescription}`;
  }

  // Add issue references
  if (issues) {
    commitMessage += `\n\n${issues}`;
  }

  return commitMessage;
}

async function main() {
  try {
    const answers = await getCommitInfo();
    const commitMessage = formatCommitMessage(answers);
    
    console.log('\n📝 Generated commit message:');
    console.log('─'.repeat(50));
    console.log(commitMessage);
    console.log('─'.repeat(50));

    const { confirm } = await inquirer.prompt([{
      type: 'confirm',
      name: 'confirm',
      message: 'Create commit with this message?',
      default: true
    }]);

    if (confirm) {
      execSync(`git commit -m "${commitMessage.replace(/"/g, '\\"')}"`, { stdio: 'inherit' });
      console.log('\n✅ Commit created successfully!');
    } else {
      console.log('\n❌ Commit cancelled');
    }
  } catch (error) {
    console.error('❌ Error:', error.message);
    process.exit(1);
  }
}

main();
EOF

chmod +x scripts/commit.js

# Package.json per le dipendenze
cat > package.json << 'EOF'
{
  "name": "automated-commit-workflow",
  "version": "1.0.0",
  "description": "Automated commit workflow example",
  "scripts": {
    "commit": "node scripts/commit.js",
    "prepare": "node scripts/setup-hooks.js"
  },
  "devDependencies": {
    "inquirer": "^8.2.5"
  }
}
EOF
```

### 3. Hook di Pre-commit Avanzato

#### Hook per Validazione e Automazione
```bash
cat > .githooks/pre-commit << 'EOF'
#!/bin/bash

echo "🔍 Running pre-commit checks..."

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Track if any check fails
CHECKS_FAILED=0

# 1. Check for merge conflict markers
echo "   Checking for merge conflict markers..."
if git diff --cached --check; then
    echo -e "   ${GREEN}✓${NC} No merge conflict markers found"
else
    echo -e "   ${RED}✗${NC} Merge conflict markers found"
    CHECKS_FAILED=1
fi

# 2. Check for debugging statements
echo "   Checking for debugging statements..."
DEBUG_PATTERNS="console\.log|debugger|alert\(|print\(|var_dump|die\(|exit\("
if git diff --cached --name-only | xargs grep -l -E "$DEBUG_PATTERNS" 2>/dev/null; then
    echo -e "   ${YELLOW}⚠${NC} Warning: Debug statements found:"
    git diff --cached --name-only | xargs grep -n -E "$DEBUG_PATTERNS" 2>/dev/null || true
    
    # Ask user if they want to continue
    echo -n "   Continue anyway? (y/N): "
    read -r response
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        echo -e "   ${RED}✗${NC} Commit aborted due to debug statements"
        exit 1
    fi
else
    echo -e "   ${GREEN}✓${NC} No debug statements found"
fi

# 3. Check file sizes
echo "   Checking file sizes..."
MAX_SIZE=1048576  # 1MB
for file in $(git diff --cached --name-only); do
    if [ -f "$file" ]; then
        size=$(stat -c%s "$file" 2>/dev/null || stat -f%z "$file" 2>/dev/null)
        if [ "$size" -gt "$MAX_SIZE" ]; then
            echo -e "   ${RED}✗${NC} File too large: $file ($size bytes > $MAX_SIZE bytes)"
            CHECKS_FAILED=1
        fi
    fi
done

if [ $CHECKS_FAILED -eq 0 ]; then
    echo -e "   ${GREEN}✓${NC} All file sizes OK"
fi

# 4. Run tests if test files exist
if [ -d "tests" ] && [ "$(find tests -name "*.test.js" | wc -l)" -gt 0 ]; then
    echo "   Running tests..."
    if npm test; then
        echo -e "   ${GREEN}✓${NC} All tests passed"
    else
        echo -e "   ${RED}✗${NC} Tests failed"
        CHECKS_FAILED=1
    fi
fi

# 5. Check for TODO/FIXME comments in staged files
echo "   Checking for TODO/FIXME comments..."
TODO_COUNT=$(git diff --cached | grep -c "TODO\|FIXME" || echo "0")
if [ "$TODO_COUNT" -gt 0 ]; then
    echo -e "   ${YELLOW}⚠${NC} Found $TODO_COUNT TODO/FIXME comments in staged changes"
    git diff --cached | grep -n "TODO\|FIXME" || true
fi

# 6. Auto-format staged files (example with prettier)
echo "   Auto-formatting staged files..."
STAGED_FILES=$(git diff --cached --name-only --diff-filter=ACM | grep -E '\.(js|jsx|ts|tsx|json|css|md)$' || echo "")
if [ -n "$STAGED_FILES" ]; then
    # This would run prettier if available
    # npx prettier --write $STAGED_FILES
    # git add $STAGED_FILES
    echo -e "   ${GREEN}✓${NC} Formatting complete (skipped - prettier not configured)"
else
    echo -e "   ${GREEN}✓${NC} No files to format"
fi

# Final result
if [ $CHECKS_FAILED -eq 1 ]; then
    echo -e "\n${RED}❌ Pre-commit checks failed. Commit aborted.${NC}"
    exit 1
else
    echo -e "\n${GREEN}✅ All pre-commit checks passed!${NC}"
    exit 0
fi
EOF

chmod +x .githooks/pre-commit
```

### 4. Hook di Commit-msg per Validazione

#### Validazione Automatica Messaggi
```bash
cat > .githooks/commit-msg << 'EOF'
#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

COMMIT_MSG_FILE=$1
COMMIT_MSG=$(cat "$COMMIT_MSG_FILE")

echo "🔍 Validating commit message..."

# Check if message is empty
if [ -z "$(echo "$COMMIT_MSG" | tr -d '\n\r\t ')" ]; then
    echo -e "${RED}❌ Commit message cannot be empty${NC}"
    exit 1
fi

# Conventional commit pattern
PATTERN="^(feat|fix|docs|style|refactor|test|chore|perf|ci|build|revert)(\(.+\))?(!)?: .{1,50}(\n\n.*)?$"

# Check conventional commit format
if echo "$COMMIT_MSG" | grep -qE "^(feat|fix|docs|style|refactor|test|chore|perf|ci|build|revert)(\(.+\))?(!)?: .+"; then
    echo -e "${GREEN}✓ Conventional commit format detected${NC}"
    
    # Extract subject line
    SUBJECT=$(echo "$COMMIT_MSG" | head -n 1)
    
    # Check subject length
    if [ ${#SUBJECT} -gt 72 ]; then
        echo -e "${RED}❌ Subject line too long: ${#SUBJECT} characters (max 72)${NC}"
        exit 1
    fi
    
    # Check if subject ends with period
    if [[ "$SUBJECT" =~ \.$  ]]; then
        echo -e "${RED}❌ Subject line should not end with a period${NC}"
        exit 1
    fi
    
    # Check for proper case
    if [[ ! "$SUBJECT" =~ ^[a-z] ]]; then
        echo -e "${YELLOW}⚠ Warning: Subject should start with lowercase${NC}"
    fi
    
    echo -e "${GREEN}✅ Commit message validation passed${NC}"
    
else
    echo -e "${YELLOW}⚠ Warning: Not using conventional commit format${NC}"
    echo "Expected format: type(scope): description"
    echo "Types: feat, fix, docs, style, refactor, test, chore, perf, ci, build, revert"
    
    # Ask if user wants to continue
    echo -n "Continue with non-conventional format? (y/N): "
    read -r response < /dev/tty
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        echo -e "${RED}❌ Commit aborted${NC}"
        exit 1
    fi
fi

# Check for common typos
TYPOS="teh|hte|recieve|recieved|occured|seperate|defalut|lenght"
if echo "$COMMIT_MSG" | grep -iE "$TYPOS"; then
    echo -e "${YELLOW}⚠ Warning: Possible typos detected in commit message${NC}"
    echo -n "Continue anyway? (y/N): "
    read -r response < /dev/tty
    if [[ ! "$response" =~ ^[Yy]$ ]]; then
        echo -e "${RED}❌ Commit aborted${NC}"
        exit 1
    fi
fi

exit 0
EOF

chmod +x .githooks/commit-msg
```

### 5. Script di Setup Automatico

#### Installazione Hook e Configurazione
```bash
cat > scripts/setup-hooks.js << 'EOF'
#!/usr/bin/env node

const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

console.log('🚀 Setting up automated commit workflow...\n');

function copyHooks() {
    const hooksDir = path.join('.git', 'hooks');
    const customHooksDir = '.githooks';
    
    if (!fs.existsSync(customHooksDir)) {
        console.log('❌ .githooks directory not found');
        return false;
    }

    const hooks = fs.readdirSync(customHooksDir);
    
    hooks.forEach(hook => {
        const src = path.join(customHooksDir, hook);
        const dest = path.join(hooksDir, hook);
        
        fs.copyFileSync(src, dest);
        fs.chmodSync(dest, '755');
        console.log(`✅ Installed ${hook} hook`);
    });
    
    return true;
}

function setupGitAliases() {
    const aliases = [
        ['cz', '!node scripts/commit.js'],
        ['amend', 'commit --amend --no-edit'],
        ['uncommit', 'reset --soft HEAD~1'],
        ['unstage', 'reset HEAD --'],
        ['graph', 'log --graph --oneline --decorate --all']
    ];
    
    console.log('\n📝 Setting up Git aliases...');
    
    aliases.forEach(([alias, command]) => {
        try {
            execSync(`git config alias.${alias} "${command}"`, { stdio: 'pipe' });
            console.log(`✅ Added alias: git ${alias}`);
        } catch (error) {
            console.log(`❌ Failed to add alias: git ${alias}`);
        }
    });
}

function createTemplates() {
    console.log('\n📄 Creating commit templates...');
    
    const template = `# <type>(<scope>): <subject>
#
# <body>
#
# <footer>
#
# Types:
# feat: new feature
# fix: bug fix  
# docs: documentation
# style: formatting
# refactor: code restructure
# test: add/update tests
# chore: maintenance
#
# Remember:
# - Use imperative mood in subject
# - No period at end of subject
# - Max 50 chars for subject
# - Wrap body at 72 chars
# - Reference issues in footer
`;

    fs.writeFileSync('.gitmessage', template);
    execSync('git config commit.template .gitmessage');
    console.log('✅ Created commit message template');
}

function setupPreCommitDependencies() {
    console.log('\n📦 Installing dependencies...');
    
    // Check if package.json exists and install inquirer
    if (fs.existsSync('package.json')) {
        try {
            execSync('npm install', { stdio: 'inherit' });
            console.log('✅ Dependencies installed');
        } catch (error) {
            console.log('❌ Failed to install dependencies');
        }
    }
}

function showUsageInstructions() {
    console.log('\n🎉 Setup complete! Here\'s how to use the automated workflow:\n');
    
    console.log('📝 Committing changes:');
    console.log('   git add <files>');
    console.log('   npm run commit  # or git cz');
    console.log('');
    
    console.log('🔧 Available aliases:');
    console.log('   git cz        # Interactive commit');
    console.log('   git amend     # Amend last commit');
    console.log('   git uncommit  # Undo last commit (keep changes)');
    console.log('   git unstage   # Unstage files');
    console.log('   git graph     # Pretty git log');
    console.log('');
    
    console.log('🛡️ Automatic checks:');
    console.log('   ✓ Conventional commit format validation');
    console.log('   ✓ File size limits');
    console.log('   ✓ Debug statement detection');
    console.log('   ✓ Merge conflict markers');
    console.log('   ✓ Test execution (if available)');
    console.log('');
    
    console.log('⚙️ Configuration files created:');
    console.log('   .gitmessage - Commit template');
    console.log('   .git/hooks/pre-commit - Pre-commit validation');
    console.log('   .git/hooks/commit-msg - Message validation');
}

// Main execution
function main() {
    try {
        if (!fs.existsSync('.git')) {
            console.log('❌ Not a git repository');
            process.exit(1);
        }
        
        copyHooks();
        setupGitAliases();
        createTemplates();
        setupPreCommitDependencies();
        showUsageInstructions();
        
    } catch (error) {
        console.error('❌ Setup failed:', error.message);
        process.exit(1);
    }
}

main();
EOF

chmod +x scripts/setup-hooks.js
```

### 6. CI/CD Integration Script

#### GitHub Actions Workflow Generator
```bash
mkdir -p .github/workflows

cat > scripts/generate-ci.js << 'EOF'
#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

const workflow = `name: Automated Commit Validation

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  validate-commits:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
      with:
        fetch-depth: 0
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Validate commit messages
      run: |
        # Check all commits in PR
        commits=$(git rev-list --no-merges ${{ github.event.before }}..${{ github.sha }})
        for commit in $commits; do
          message=$(git log --format=%s -n 1 $commit)
          echo "Validating commit: $message"
          
          if ! echo "$message" | grep -qE "^(feat|fix|docs|style|refactor|test|chore|perf|ci|build|revert)(\\(.+\\))?(!)?: .+"; then
            echo "❌ Invalid commit message format: $message"
            echo "Expected: type(scope): description"
            exit 1
          fi
          
          if [ \${#message} -gt 72 ]; then
            echo "❌ Commit message too long: $message"
            exit 1
          fi
        done
        echo "✅ All commit messages are valid"
    
    - name: Run tests
      run: npm test || echo "No tests found"
    
    - name: Check for large files
      run: |
        find . -type f -size +1M -not -path "./.git/*" -not -path "./node_modules/*" | while read file; do
          echo "❌ Large file detected: $file"
          exit 1
        done || echo "✅ No large files found"
    
    - name: Security audit
      run: npm audit --audit-level moderate || true

  build-test:
    runs-on: ubuntu-latest
    needs: validate-commits
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Node.js
      uses: actions/setup-node@v3
      with:
        node-version: '18'
        cache: 'npm'
    
    - name: Install dependencies
      run: npm ci
    
    - name: Build project
      run: npm run build || echo "No build script found"
    
    - name: Run linting
      run: npm run lint || echo "No lint script found"
`;

fs.writeFileSync('.github/workflows/commit-validation.yml', workflow);
console.log('✅ Created GitHub Actions workflow for commit validation');
EOF

chmod +x scripts/generate-ci.js
```

### 7. Demo Setup e Test

#### Testare l'Automazione Completa
```bash
# Setup iniziale
git add package.json scripts/ .githooks/
git commit -m "chore: setup automated commit workflow infrastructure

- Add interactive commit script with conventional commits
- Implement comprehensive pre-commit hooks
- Add commit message validation
- Include CI/CD workflow generation
- Setup git aliases and templates"

# Setup dell'automazione
npm install inquirer@8.2.5
node scripts/setup-hooks.js

# Test del workflow
echo 'console.log("test");' > src/components/test.js
git add src/components/test.js

# Test commit interattivo (simulate input)
echo "Ora puoi testare con: npm run commit"
```

### 8. Automation Summary

#### Features Implementate

1. **Interactive Commit Creator**
   - Guided prompts for commit type, scope, description
   - Validation of input length and format
   - Automatic conventional commit formatting

2. **Pre-commit Hooks**
   - Conflict marker detection
   - Debug statement warnings
   - File size validation
   - Automated testing
   - Code formatting

3. **Commit Message Validation**
   - Conventional commit format enforcement
   - Length limits
   - Typo detection
   - Case sensitivity checks

4. **CI/CD Integration**
   - GitHub Actions workflow
   - Automated commit validation
   - Security auditing
   - Build and test automation

5. **Developer Experience**
   - Git aliases for common operations
   - Commit message templates
   - Easy setup script
   - Comprehensive documentation

#### Usage Examples
```bash
# Interactive commit
npm run commit

# Quick aliases
git cz          # Same as npm run commit
git amend       # Amend last commit
git uncommit    # Undo last commit
git unstage     # Unstage files
git graph       # Pretty log

# Generate CI workflow
node scripts/generate-ci.js
```

## Navigazione
- [📑 Indice](../README.md)
- [⬅️ Modulo Precedente](../08-Visualizzare-Storia-Commit/README.md)
- [➡️ Modulo Successivo](../10-Navigare-tra-Commit/README.md)
