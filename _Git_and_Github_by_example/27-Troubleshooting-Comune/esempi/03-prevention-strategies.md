# Strategie di Prevenzione Problemi Git

## Introduzione

Questo documento presenta strategie proattive per prevenire i problemi più comuni con Git. La prevenzione è sempre meglio della cura, specialmente quando si tratta di sistemi di controllo versione.

## Categoria 1: Prevenzione Problemi di Commit

### Strategia 1.1: Commit Guidelines e Automation

**Problema Prevenuto**: Commit inconsistenti, messaggi non chiari, file dimenticati.

**Implementazione**:

```bash
# 1. Setup commit template
cat > ~/.gitmessage << 'EOF'
# Title (50 chars max): If applied, this commit will...
# [type](scope): description

# Body (72 chars per line):
# - Why is this change needed?
# - How does it address the issue?
# - What are the side effects?

# Footer:
# - Closes #issue-number
# - BREAKING CHANGE: describe breaking changes
EOF

git config --global commit.template ~/.gitmessage

# 2. Setup pre-commit hooks
mkdir -p .git/hooks

cat > .git/hooks/pre-commit << 'EOF'
#!/bin/bash

# Prevent commits to main/master branch
branch="$(git rev-parse --abbrev-ref HEAD)"
if [[ "$branch" == "main" || "$branch" == "master" ]]; then
    echo "❌ Direct commits to $branch are not allowed"
    echo "💡 Create a feature branch: git checkout -b feature/your-feature"
    exit 1
fi

# Check for common mistakes
if git diff --cached --name-only | grep -E '\.(log|tmp|cache)$'; then
    echo "❌ Attempt to commit temporary files detected"
    echo "📁 Files found:"
    git diff --cached --name-only | grep -E '\.(log|tmp|cache)$'
    exit 1
fi

# Check for debugging code
if git diff --cached | grep -E '(console\.log|debugger|TODO|FIXME)'; then
    echo "⚠️  Debugging code or TODOs found in staged changes"
    echo "🔍 Review these before committing:"
    git diff --cached | grep -n -E '(console\.log|debugger|TODO|FIXME)'
    read -p "Continue anyway? (y/N): " choice
    case "$choice" in 
        y|Y ) echo "Proceeding with commit...";;
        * ) echo "Commit aborted"; exit 1;;
    esac
fi

# Check commit message format (if committing)
if [ -z "$GIT_EDITOR" ]; then
    echo "✅ Pre-commit checks passed"
fi
EOF

chmod +x .git/hooks/pre-commit

# 3. Setup commit message validation
cat > .git/hooks/commit-msg << 'EOF'
#!/bin/bash

commit_regex='^(feat|fix|docs|style|refactor|test|chore)(\(.+\))?: .{1,50}'

if ! grep -qE "$commit_regex" "$1"; then
    echo "❌ Invalid commit message format"
    echo "📝 Format: type(scope): description"
    echo "🏷️  Types: feat, fix, docs, style, refactor, test, chore"
    echo "📏 Description: 1-50 characters"
    echo ""
    echo "Examples:"
    echo "  feat(auth): add user login functionality"
    echo "  fix(api): resolve null pointer exception"
    echo "  docs(readme): update installation instructions"
    exit 1
fi
EOF

chmod +x .git/hooks/commit-msg
```

### Strategia 1.2: Automated Staging Best Practices

**Problema Prevenuto**: File sbagliati in staging, commit incompleti.

**Implementazione**:

```bash
# 1. Smart add aliases
git config --global alias.add-new '!git add $(git ls-files -o --exclude-standard)'
git config --global alias.add-modified '!git add $(git ls-files -m)'
git config --global alias.add-safe '!git add -A && git status'

# 2. Interactive staging helper script
cat > ~/bin/git-smart-add << 'EOF'
#!/bin/bash

echo "🔍 Scanning for changes..."
echo

# Show untracked files
untracked=$(git ls-files -o --exclude-standard)
if [ ! -z "$untracked" ]; then
    echo "📁 Untracked files:"
    echo "$untracked" | sed 's/^/  /'
    echo
    read -p "Add untracked files? (y/N): " add_untracked
    if [[ "$add_untracked" =~ ^[Yy]$ ]]; then
        echo "$untracked" | xargs git add
        echo "✅ Untracked files added"
    fi
fi

# Show modified files
modified=$(git ls-files -m)
if [ ! -z "$modified" ]; then
    echo "📝 Modified files:"
    echo "$modified" | sed 's/^/  /'
    echo
    read -p "Add modified files? (y/N): " add_modified
    if [[ "$add_modified" =~ ^[Yy]$ ]]; then
        echo "$modified" | xargs git add
        echo "✅ Modified files added"
    fi
fi

# Show final status
echo
echo "📊 Final staging status:"
git status --short
EOF

chmod +x ~/bin/git-smart-add
export PATH="$HOME/bin:$PATH"  # Add to .bashrc
```

## Categoria 2: Prevenzione Problemi di Branch

### Strategia 2.1: Branch Protection e Workflow Automation

**Problema Prevenuto**: Merge disastrosi, branch caotici, conflitti complessi.

**Implementazione**:

```bash
# 1. Automated branch naming
cat > ~/bin/git-smart-branch << 'EOF'
#!/bin/bash

BRANCH_TYPES=("feature" "bugfix" "hotfix" "release" "experiment")

echo "🌟 Smart Branch Creator"
echo "Select branch type:"
for i in "${!BRANCH_TYPES[@]}"; do
    echo "  $((i+1)). ${BRANCH_TYPES[$i]}"
done

read -p "Enter choice (1-${#BRANCH_TYPES[@]}): " choice
branch_type="${BRANCH_TYPES[$((choice-1))]}"

read -p "Enter branch description (lowercase, hyphens): " description
read -p "Enter ticket/issue number (optional): " ticket

# Construct branch name
if [ ! -z "$ticket" ]; then
    branch_name="${branch_type}/${ticket}-${description}"
else
    branch_name="${branch_type}/${description}"
fi

echo "Creating branch: $branch_name"

# Create and switch to branch
git checkout -b "$branch_name"

# Set up tracking (if remote exists)
if git remote | grep -q origin; then
    git push -u origin "$branch_name"
fi

echo "✅ Branch $branch_name created and set up"
EOF

chmod +x ~/bin/git-smart-branch

# 2. Branch cleanup automation
git config --global alias.cleanup-merged '!git branch --merged | grep -v "\*\|main\|master\|develop" | xargs -n 1 git branch -d'

# 3. Pre-merge validation
cat > .git/hooks/pre-merge-commit << 'EOF'
#!/bin/bash

echo "🔍 Pre-merge validation..."

# Check if all tests pass (if test command exists)
if command -v npm &> /dev/null && [ -f package.json ]; then
    echo "🧪 Running tests..."
    if ! npm test; then
        echo "❌ Tests failed, merge aborted"
        exit 1
    fi
fi

# Check for merge conflicts markers left in files
if git diff --cached | grep -E '^[<>=]{7}'; then
    echo "❌ Merge conflict markers found in staged files"
    exit 1
fi

echo "✅ Pre-merge validation passed"
EOF

chmod +x .git/hooks/pre-merge-commit
```

### Strategia 2.2: Conflict Prevention System

**Problema Prevenuto**: Conflitti di merge complessi, conflitti ricorrenti.

**Implementazione**:

```bash
# 1. Enable rerere (reuse recorded resolution)
git config rerere.enabled true
git config rerere.autoupdate true

# 2. Set up merge strategy preferences
git config merge.tool vimdiff  # or your preferred tool
git config merge.conflictstyle diff3

# 3. Automated conflict detection script
cat > ~/bin/git-conflict-check << 'EOF'
#!/bin/bash

TARGET_BRANCH="${1:-main}"
CURRENT_BRANCH="$(git rev-parse --abbrev-ref HEAD)"

echo "🔍 Checking for potential conflicts with $TARGET_BRANCH..."

# Fetch latest changes
git fetch origin

# Simulate merge without actually merging
git merge-tree $(git merge-base HEAD origin/$TARGET_BRANCH) HEAD origin/$TARGET_BRANCH > merge-preview.txt

if grep -q '<<<<<<<' merge-preview.txt; then
    echo "⚠️  Potential conflicts detected:"
    grep -A 5 -B 5 '<<<<<<<' merge-preview.txt
    echo
    echo "🛠️  Recommended actions:"
    echo "  1. Rebase your branch: git rebase origin/$TARGET_BRANCH"
    echo "  2. Resolve conflicts early"
    echo "  3. Test thoroughly before merging"
else
    echo "✅ No conflicts detected with $TARGET_BRANCH"
fi

rm merge-preview.txt
EOF

chmod +x ~/bin/git-conflict-check

# 4. Daily conflict monitoring (add to crontab)
cat > ~/bin/git-daily-conflict-check << 'EOF'
#!/bin/bash

# Check all local branches for potential conflicts
for branch in $(git for-each-ref --format='%(refname:short)' refs/heads/); do
    if [[ "$branch" != "main" && "$branch" != "master" ]]; then
        echo "Checking branch: $branch"
        git checkout "$branch" 2>/dev/null
        ~/bin/git-conflict-check
    fi
done
EOF

chmod +x ~/bin/git-daily-conflict-check
```

## Categoria 3: Prevenzione Problemi di Performance

### Strategia 3.1: Repository Size Management

**Problema Prevenuto**: Repository lenti, file giganti nella cronologia.

**Implementazione**:

```bash
# 1. Large file detection pre-commit hook
cat > .git/hooks/pre-commit-size-check << 'EOF'
#!/bin/bash

MAX_FILE_SIZE=10485760  # 10MB in bytes

echo "📏 Checking file sizes..."

# Check staged files
git diff --cached --name-only | while read file; do
    if [ -f "$file" ]; then
        size=$(stat -f%z "$file" 2>/dev/null || stat -c%s "$file" 2>/dev/null)
        if [ "$size" -gt "$MAX_FILE_SIZE" ]; then
            echo "❌ Large file detected: $file ($(numfmt --to=iec $size))"
            echo "💡 Consider using Git LFS for large files"
            echo "🔗 Setup: git lfs track \"*.$extension\""
            exit 1
        fi
    fi
done

echo "✅ File size check passed"
EOF

chmod +x .git/hooks/pre-commit-size-check

# 2. Automated Git LFS setup for common large file types
cat > setup-git-lfs.sh << 'EOF'
#!/bin/bash

echo "🗂️  Setting up Git LFS for common file types..."

# Initialize Git LFS
git lfs install

# Track common large file types
git lfs track "*.zip"
git lfs track "*.tar.gz"
git lfs track "*.exe"
git lfs track "*.dmg"
git lfs track "*.iso"
git lfs track "*.pdf"
git lfs track "*.mp4"
git lfs track "*.mov"
git lfs track "*.avi"
git lfs track "*.mp3"
git lfs track "*.wav"
git lfs track "*.psd"
git lfs track "*.ai"
git lfs track "*.sketch"

# Commit .gitattributes
git add .gitattributes
git commit -m "setup: configure Git LFS for large file types"

echo "✅ Git LFS configured"
echo "📝 Tracked file types:"
cat .gitattributes
EOF

chmod +x setup-git-lfs.sh

# 3. Repository health monitoring
cat > ~/bin/git-health-monitor << 'EOF'
#!/bin/bash

REPO_PATH="${1:-.}"
cd "$REPO_PATH"

echo "🏥 Git Repository Health Monitor"
echo "Repository: $(pwd)"
echo "Date: $(date)"
echo

# Size analysis
echo "📊 Repository Size Analysis:"
TOTAL_SIZE=$(du -sh .git | cut -f1)
OBJECTS_SIZE=$(du -sh .git/objects | cut -f1)
echo "  Total .git size: $TOTAL_SIZE"
echo "  Objects size: $OBJECTS_SIZE"

# Object count
echo
echo "📦 Object Statistics:"
git count-objects -v

# Largest files in history
echo
echo "🐘 Largest files in repository history:"
git rev-list --objects --all | \
git cat-file --batch-check='%(objecttype) %(objectname) %(objectsize) %(rest)' | \
sed -n 's/^blob //p' | \
sort --numeric-sort --key=2 --reverse | \
head -10 | \
while read objectname size path; do
    echo "  $(numfmt --to=iec $size) $path"
done

# Recent large commits
echo
echo "📈 Recent commits by size:"
git log --oneline -10 --pretty=format:"%h %s" | while read commit message; do
    size=$(git cat-file -s $commit 2>/dev/null || echo "0")
    echo "  $commit $(numfmt --to=iec $size) $message"
done

# Recommendations
echo
echo "💡 Recommendations:"
REPO_SIZE_BYTES=$(du -s .git | cut -f1)
if [ "$REPO_SIZE_BYTES" -gt 100000 ]; then  # >100MB
    echo "  ⚠️  Repository is large. Consider:"
    echo "    - Git LFS for large files"
    echo "    - Repository splitting"
    echo "    - History cleanup"
fi

if git rev-list --objects --all | git cat-file --batch-check='%(objecttype) %(objectsize) %(rest)' | awk '/^blob/ {if($2>10485760) print}' | head -1 > /dev/null; then
    echo "  🐘 Large files detected. Consider Git LFS"
fi
EOF

chmod +x ~/bin/git-health-monitor
```

### Strategia 3.2: Performance Optimization Automation

**Problema Prevenuto**: Operazioni Git lente, repository inefficienti.

**Implementazione**:

```bash
# 1. Automated maintenance schedule
cat > ~/bin/git-maintenance << 'EOF'
#!/bin/bash

REPO_PATH="${1:-.}"
cd "$REPO_PATH"

echo "🔧 Running Git maintenance..."

# Garbage collection
echo "🗑️  Running garbage collection..."
git gc --aggressive --prune=now

# Repack objects
echo "📦 Repacking objects..."
git repack -Ad

# Update server info (for dumb HTTP servers)
echo "ℹ️  Updating server info..."
git update-server-info

# Cleanup reflog
echo "📜 Cleaning reflog..."
git reflog expire --expire-unreachable=30.days.ago --all

# Prune unreachable objects
echo "✂️  Pruning unreachable objects..."
git prune --expire=30.days.ago

# Performance optimization
echo "⚡ Applying performance optimizations..."
git config gc.auto 256
git config gc.autopacklimit 50
git config pack.deltacachesize 2g
git config pack.packsizelimit 2g
git config pack.windowmemory 2g
git config core.preloadindex true
git config core.fscache true

echo "✅ Maintenance completed"

# Show results
echo
echo "📊 Post-maintenance statistics:"
git count-objects -v
EOF

chmod +x ~/bin/git-maintenance

# 2. Cron job for weekly maintenance (add to crontab)
echo "0 2 * * 0 cd /path/to/your/repo && ~/bin/git-maintenance" | crontab -
```

## Categoria 4: Prevenzione Problemi di Sicurezza

### Strategia 4.1: Sensitive Data Protection

**Problema Prevenuto**: Commit accidentali di password, chiavi API, dati sensibili.

**Implementazione**:

```bash
# 1. Sensitive data detection pre-commit hook
cat > .git/hooks/pre-commit-secrets << 'EOF'
#!/bin/bash

echo "🔒 Checking for sensitive data..."

# Patterns to detect
SECRET_PATTERNS=(
    "password\s*=\s*['\"][^'\"]{3,}['\"]"
    "api[_-]?key\s*=\s*['\"][^'\"]{10,}['\"]"
    "secret\s*=\s*['\"][^'\"]{10,}['\"]"
    "token\s*=\s*['\"][^'\"]{10,}['\"]"
    "-----BEGIN [A-Z]+ KEY-----"
    "sk_live_[a-zA-Z0-9]+"
    "pk_live_[a-zA-Z0-9]+"
)

# Check staged files
git diff --cached --name-only | while read file; do
    if [ -f "$file" ]; then
        for pattern in "${SECRET_PATTERNS[@]}"; do
            if grep -iE "$pattern" "$file" >/dev/null; then
                echo "❌ Potential secret detected in $file"
                echo "🔍 Pattern: $pattern"
                grep -inE "$pattern" "$file" | head -3
                echo "💡 Move secrets to environment variables or config files"
                exit 1
            fi
        done
    fi
done

echo "✅ No secrets detected"
EOF

chmod +x .git/hooks/pre-commit-secrets

# 2. Automated .gitignore for common sensitive files
cat > setup-security-gitignore.sh << 'EOF'
#!/bin/bash

echo "🛡️  Setting up security-focused .gitignore..."

cat >> .gitignore << 'GITIGNORE_EOF'

# Security - Sensitive Files
*.key
*.pem
*.p12
*.pfx
.env
.env.local
.env.production
config/secrets.yml
config/database.yml
secrets/
.secrets/

# OS and Editor Files
.DS_Store
Thumbs.db
*.swp
*.swo
*~
.vscode/settings.json
.idea/

# Logs and Temporary Files
*.log
logs/
*.tmp
*.temp
tmp/
temp/

# Dependencies
node_modules/
vendor/
.bundle/

# Build Outputs
dist/
build/
*.min.js
*.min.css

GITIGNORE_EOF

echo "✅ Security .gitignore patterns added"
EOF

chmod +x setup-security-gitignore.sh
```

### Strategia 4.2: Access Control e Audit Trail

**Problema Prevenuto**: Accessi non autorizzati, perdita di audit trail.

**Implementazione**:

```bash
# 1. Git access logging
cat > ~/bin/git-access-logger << 'EOF'
#!/bin/bash

LOG_FILE="$HOME/.git-access.log"
REPO_PATH="$(pwd)"
USER="$(whoami)"
COMMAND="$@"
TIMESTAMP="$(date '+%Y-%m-%d %H:%M:%S')"

echo "[$TIMESTAMP] $USER in $REPO_PATH: git $COMMAND" >> "$LOG_FILE"

# Execute the original git command
git "$@"
EOF

chmod +x ~/bin/git-access-logger

# 2. SSH key monitoring for GitHub
cat > ~/bin/check-github-keys << 'EOF'
#!/bin/bash

echo "🔑 Checking GitHub SSH keys..."

# Get current SSH keys from GitHub
GITHUB_USER="${1:-$(git config github.user)}"
if [ -z "$GITHUB_USER" ]; then
    echo "❌ GitHub username not found"
    echo "💡 Set with: git config --global github.user YOUR_USERNAME"
    exit 1
fi

echo "Checking keys for user: $GITHUB_USER"
curl -s "https://api.github.com/users/$GITHUB_USER/keys" | \
jq -r '.[].key' > /tmp/github-keys.txt

# Compare with local keys
echo "Local SSH keys:"
find ~/.ssh -name "*.pub" -exec echo "📄 {}" \; -exec cat {} \;

echo
echo "GitHub keys:"
cat /tmp/github-keys.txt

# Check if local keys are on GitHub
echo
echo "🔍 Key status:"
find ~/.ssh -name "*.pub" | while read keyfile; do
    key_content=$(ssh-keygen -f "$keyfile" -e -m RFC4716 | grep -v "Comment:" | tr -d '\n' | sed 's/---- BEGIN SSH2 PUBLIC KEY ----//' | sed 's/---- END SSH2 PUBLIC KEY ----//')
    if grep -q "$key_content" /tmp/github-keys.txt; then
        echo "✅ $keyfile is registered on GitHub"
    else
        echo "⚠️  $keyfile is NOT registered on GitHub"
    fi
done

rm /tmp/github-keys.txt
EOF

chmod +x ~/bin/check-github-keys
```

## Categoria 5: Disaster Recovery Preparation

### Strategia 5.1: Automated Backup System

**Problema Prevenuto**: Perdita completa del repository, corruzione dati.

**Implementazione**:

```bash
# 1. Comprehensive backup script
cat > ~/bin/git-backup-complete << 'EOF'
#!/bin/bash

REPO_PATH="${1:-.}"
BACKUP_BASE="$HOME/git-backups"
REPO_NAME="$(basename $(cd "$REPO_PATH" && pwd))"
TIMESTAMP="$(date +%Y%m%d_%H%M%S)"
BACKUP_DIR="$BACKUP_BASE/$REPO_NAME/$TIMESTAMP"

echo "💾 Creating comprehensive backup..."
echo "Repository: $REPO_PATH"
echo "Backup location: $BACKUP_DIR"

mkdir -p "$BACKUP_DIR"
cd "$REPO_PATH"

# 1. Full repository backup
echo "📦 Backing up full repository..."
tar -czf "$BACKUP_DIR/repo-full.tar.gz" .git

# 2. Bundle backup (portable)
echo "🎁 Creating bundle backup..."
git bundle create "$BACKUP_DIR/repo-bundle.bundle" --all

# 3. Configuration backup
echo "⚙️  Backing up configuration..."
git config --list > "$BACKUP_DIR/config.txt"
git remote -v > "$BACKUP_DIR/remotes.txt"

# 4. Branch information
echo "🌿 Backing up branch info..."
git branch -a > "$BACKUP_DIR/branches.txt"
git tag > "$BACKUP_DIR/tags.txt"

# 5. Recent history backup
echo "📜 Backing up recent history..."
git log --oneline -100 > "$BACKUP_DIR/recent-history.txt"
git reflog > "$BACKUP_DIR/reflog.txt"

# 6. Current state backup
echo "📸 Backing up current state..."
git status > "$BACKUP_DIR/status.txt"
git diff > "$BACKUP_DIR/uncommitted-changes.patch"
git stash list > "$BACKUP_DIR/stashes.txt"

# 7. Cleanup old backups (keep last 10)
echo "🧹 Cleaning old backups..."
cd "$BACKUP_BASE/$REPO_NAME"
ls -t | tail -n +11 | xargs rm -rf

echo "✅ Backup completed: $BACKUP_DIR"
echo "📊 Backup size: $(du -sh "$BACKUP_DIR" | cut -f1)"

# 8. Verify backup integrity
echo "🔍 Verifying backup integrity..."
cd /tmp
git clone "$BACKUP_DIR/repo-bundle.bundle" verify-backup-$$
if [ $? -eq 0 ]; then
    echo "✅ Backup integrity verified"
    rm -rf verify-backup-$$
else
    echo "❌ Backup integrity check failed"
fi
EOF

chmod +x ~/bin/git-backup-complete

# 2. Restore script
cat > ~/bin/git-restore-backup << 'EOF'
#!/bin/bash

BACKUP_DIR="$1"
RESTORE_PATH="${2:-./restored-repo}"

if [ -z "$BACKUP_DIR" ]; then
    echo "Usage: git-restore-backup <backup-directory> [restore-path]"
    exit 1
fi

echo "🔄 Restoring repository from backup..."
echo "Backup: $BACKUP_DIR"
echo "Restore to: $RESTORE_PATH"

mkdir -p "$RESTORE_PATH"
cd "$RESTORE_PATH"

# Method 1: Try bundle restore (fastest)
if [ -f "$BACKUP_DIR/repo-bundle.bundle" ]; then
    echo "📦 Restoring from bundle..."
    git clone "$BACKUP_DIR/repo-bundle.bundle" .
    
    # Restore remotes
    if [ -f "$BACKUP_DIR/remotes.txt" ]; then
        echo "🔗 Restoring remotes..."
        grep "origin" "$BACKUP_DIR/remotes.txt" | head -1 | awk '{print $2}' | while read url; do
            git remote add origin "$url"
        done
    fi
    
    echo "✅ Bundle restore completed"
    
# Method 2: Full tar restore
elif [ -f "$BACKUP_DIR/repo-full.tar.gz" ]; then
    echo "📁 Restoring from full backup..."
    tar -xzf "$BACKUP_DIR/repo-full.tar.gz"
    git reset --hard HEAD
    echo "✅ Full backup restore completed"
    
else
    echo "❌ No valid backup found in $BACKUP_DIR"
    exit 1
fi

# Show restore status
echo
echo "📊 Restore summary:"
git log --oneline -5
git status
EOF

chmod +x ~/bin/git-restore-backup
```

### Strategia 5.2: Multi-Location Backup Strategy

**Problema Prevenuto**: Perdita di backup, single point of failure.

**Implementazione**:

```bash
# 1. Multi-destination backup
cat > ~/bin/git-backup-multi << 'EOF'
#!/bin/bash

REPO_PATH="${1:-.}"
REPO_NAME="$(basename $(cd "$REPO_PATH" && pwd))"

# Backup destinations
DESTINATIONS=(
    "$HOME/git-backups/local"
    "/mnt/usb-backup/git-backups"  # USB drive
    "$HOME/Dropbox/git-backups"   # Cloud storage
    "user@backup-server:/backups/git"  # Remote server
)

cd "$REPO_PATH"

echo "🌐 Multi-location backup for $REPO_NAME"

for dest in "${DESTINATIONS[@]}"; do
    echo "📤 Backing up to: $dest"
    
    if [[ "$dest" == *"@"* ]]; then
        # Remote destination
        git bundle create - --all | ssh "${dest%:*}" "mkdir -p ${dest#*:}/$REPO_NAME && cat > ${dest#*:}/$REPO_NAME/backup-$(date +%Y%m%d).bundle"
    else
        # Local destination
        mkdir -p "$dest/$REPO_NAME"
        git bundle create "$dest/$REPO_NAME/backup-$(date +%Y%m%d).bundle" --all
        
        # Cleanup old backups
        find "$dest/$REPO_NAME" -name "backup-*.bundle" -mtime +30 -delete
    fi
    
    if [ $? -eq 0 ]; then
        echo "  ✅ Success"
    else
        echo "  ❌ Failed"
    fi
done
EOF

chmod +x ~/bin/git-backup-multi
```

## Dashboard di Monitoraggio Completo

### Strategia 6.1: Repository Health Dashboard

```bash
# Comprehensive monitoring dashboard
cat > ~/bin/git-dashboard << 'EOF'
#!/bin/bash

clear
echo "🎛️  GIT REPOSITORY DASHBOARD"
echo "============================"
echo "Repository: $(pwd)"
echo "Date: $(date)"
echo

# Section 1: Basic Status
echo "📊 REPOSITORY STATUS"
echo "-------------------"
git status --porcelain | head -10
if [ $(git status --porcelain | wc -l) -gt 10 ]; then
    echo "... and $(($(git status --porcelain | wc -l) - 10)) more files"
fi
echo

# Section 2: Branch Information
echo "🌿 BRANCH INFORMATION"
echo "--------------------"
echo "Current branch: $(git rev-parse --abbrev-ref HEAD)"
echo "Branches:"
git branch -vv | head -5
echo

# Section 3: Recent Activity
echo "⏰ RECENT ACTIVITY"
echo "-----------------"
git log --oneline --graph -5
echo

# Section 4: Repository Health
echo "🏥 REPOSITORY HEALTH"
echo "-------------------"
REPO_SIZE=$(du -sh .git | cut -f1)
OBJECT_COUNT=$(git count-objects | awk '{sum += $1} END {print sum}')
echo "Repository size: $REPO_SIZE"
echo "Object count: $OBJECT_COUNT"

# Check for issues
if git fsck --quiet 2>/dev/null; then
    echo "Integrity: ✅ OK"
else
    echo "Integrity: ❌ Issues detected"
fi

# Section 5: Remotes
echo
echo "🔗 REMOTE STATUS"
echo "---------------"
git remote -v
echo

# Section 6: Performance Metrics
echo "⚡ PERFORMANCE METRICS"
echo "---------------------"
TIME_STATUS=$(time git status >/dev/null 2>&1)
echo "Git status time: Fast"  # Simplified for demo

# Section 7: Security Check
echo
echo "🔒 SECURITY STATUS"
echo "-----------------"
if [ -f .gitignore ]; then
    if grep -q "\.env" .gitignore; then
        echo "Environment files: ✅ Protected"
    else
        echo "Environment files: ⚠️  Not protected"
    fi
else
    echo "Gitignore: ❌ Missing"
fi

echo
echo "Dashboard updated: $(date)"
EOF

chmod +x ~/bin/git-dashboard

# Auto-refresh dashboard
cat > ~/bin/git-dashboard-watch << 'EOF'
#!/bin/bash

while true; do
    ~/bin/git-dashboard
    echo
    echo "Press Ctrl+C to exit, refreshing in 30 seconds..."
    sleep 30
done
EOF

chmod +x ~/bin/git-dashboard-watch
```

---

## Summary: Prevention Checklist

### Daily Prevention Habits
- [ ] Use `git status` before any operation
- [ ] Write descriptive commit messages
- [ ] Review changes before committing (`git diff --staged`)
- [ ] Pull before pushing (`git pull --rebase`)
- [ ] Work in feature branches, not main
- [ ] Use `git stash` before switching branches

### Weekly Prevention Tasks
- [ ] Run repository health check
- [ ] Clean up merged branches
- [ ] Review .gitignore effectiveness
- [ ] Check backup integrity
- [ ] Update team on branch strategy

### Monthly Prevention Tasks
- [ ] Full repository backup
- [ ] Performance optimization (`git gc`)
- [ ] Security audit (check for exposed secrets)
- [ ] Team workflow review
- [ ] Update Git tools and hooks

### Project Setup Prevention
- [ ] Configure pre-commit hooks
- [ ] Set up Git LFS for large files
- [ ] Create comprehensive .gitignore
- [ ] Establish branch protection rules
- [ ] Document team Git workflow
- [ ] Set up automated backups

---

**🎯 Remember**: The goal of prevention is to make mistakes impossible, not just difficult. Automate as much as possible and create safe defaults for your team.
