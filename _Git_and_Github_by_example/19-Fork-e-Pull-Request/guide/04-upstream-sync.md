# 04 - Upstream Sync: Mantenere il Fork Aggiornato

## 📖 Introduzione

Quando lavori con fork di repository esterni, è essenziale mantenere il tuo fork sincronizzato con il repository originale (upstream). Questa guida ti insegnerà tutte le strategie e tecniche per gestire efficacemente questa sincronizzazione.

## 🎯 Obiettivi di Apprendimento

Al termine di questa guida sarai in grado di:

- ✅ Comprendere la relazione fork-upstream
- ✅ Configurare remote upstream correttamente
- ✅ Sincronizzare fork con upstream regolarmente
- ✅ Gestire conflitti durante la sincronizzazione
- ✅ Automatizzare il processo di sync
- ✅ Mantenere branch di feature aggiornati
- ✅ Implementare strategie di sync per team

## 🔄 Concetti Fondamentali

### 1. **Repository Relationship**

#### Terminologia
```markdown
# Upstream (Original Repository)
https://github.com/original-owner/project.git
- Repository originale che hai forkato
- Source of truth per il progetto
- Riceve contribuzioni da multiple fork

# Origin (Your Fork)
https://github.com/your-username/project.git
- Tua copia personale del repository
- Dove sviluppi features e fixes
- Punto di partenza per Pull Requests

# Local (Your Clone)
~/projects/project/
- Clone locale del tuo fork
- Dove fai actual development work
- Connected to both origin e upstream
```

#### Visual Representation
```
[Upstream Repo] ←─── Pull Requests ←─── [Your Fork] ←─── [Local Clone]
    ↓                                        ↑              ↑
    └──── Direct Clone ──────────────────────┘              │
    ↓                                                       │
    └──── Fetch Updates ────────────────────────────────────┘
```

### 2. **Sync Strategies**

#### Frequency Patterns
```markdown
# Daily Sync (Active Projects)
- Sync main branch ogni mattina
- Check upstream changes before feature work
- Keep local development environment current

# Weekly Sync (Stable Projects)
- Scheduled sync ogni week start
- Batch updates for better planning
- Review changelog e breaking changes

# Release-Based Sync (Stable Dependencies)
- Sync only on upstream releases
- Major version updates planning
- Compatibility testing required
```

## 🛠️ Setup Upstream Remote

### 1. **Initial Configuration**

#### Adding Upstream Remote
```bash
# Check current remotes
git remote -v
# Output:
# origin    https://github.com/your-username/project.git (fetch)
# origin    https://github.com/your-username/project.git (push)

# Add upstream remote
git remote add upstream https://github.com/original-owner/project.git

# Verify remotes
git remote -v
# Output:
# origin      https://github.com/your-username/project.git (fetch)
# origin      https://github.com/your-username/project.git (push)
# upstream    https://github.com/original-owner/project.git (fetch)
# upstream    https://github.com/original-owner/project.git (push)

# Configure upstream for fetch only
git remote set-url --push upstream DISABLE
git remote -v
# Output:
# origin      https://github.com/your-username/project.git (fetch)
# origin      https://github.com/your-username/project.git (push)
# upstream    https://github.com/original-owner/project.git (fetch)
# upstream    DISABLE (push)
```

#### Fetch Upstream Changes
```bash
# Fetch all upstream branches
git fetch upstream

# List all branches (local + remotes)
git branch -a
# Output:
# * main
#   feature-branch
#   remotes/origin/main
#   remotes/origin/feature-branch
#   remotes/upstream/main
#   remotes/upstream/develop
#   remotes/upstream/release/v2.0

# Check upstream commit history
git log upstream/main --oneline -10
```

### 2. **Branch Mapping Strategy**

#### Main Branch Sync
```bash
# Switch to main branch
git checkout main

# Fetch latest from upstream
git fetch upstream

# Merge upstream changes
git merge upstream/main

# Push updated main to your fork
git push origin main
```

#### Alternative: Reset Strategy
```bash
# For clean main branch (no local changes)
git checkout main
git fetch upstream
git reset --hard upstream/main
git push --force-with-lease origin main
```

## 🔄 Sync Workflows

### 1. **Basic Sync Process**

#### Step-by-Step Workflow
```bash
#!/bin/bash
# sync-fork.sh - Basic fork synchronization

# Colors for output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}🔄 Starting fork synchronization...${NC}"

# 1. Fetch upstream changes
echo -e "${YELLOW}📥 Fetching upstream changes...${NC}"
git fetch upstream

# 2. Switch to main branch
echo -e "${YELLOW}🔀 Switching to main branch...${NC}"
git checkout main

# 3. Check for local changes
if ! git diff --quiet; then
    echo -e "${YELLOW}⚠️  Local changes detected. Stashing...${NC}"
    git stash push -m "Auto-stash before upstream sync $(date)"
fi

# 4. Merge upstream changes
echo -e "${YELLOW}🔀 Merging upstream/main...${NC}"
if git merge upstream/main; then
    echo -e "${GREEN}✅ Merge successful${NC}"
else
    echo -e "${RED}❌ Merge failed. Manual resolution required.${NC}"
    exit 1
fi

# 5. Push to origin
echo -e "${YELLOW}📤 Pushing to origin...${NC}"
git push origin main

# 6. Restore stashed changes if any
if git stash list | grep -q "Auto-stash before upstream sync"; then
    echo -e "${YELLOW}🔄 Restoring stashed changes...${NC}"
    git stash pop
fi

echo -e "${GREEN}🎉 Fork synchronization complete!${NC}"
```

#### Enhanced Sync with Verification
```bash
#!/bin/bash
# enhanced-sync.sh - Enhanced fork synchronization with verification

# Configuration
UPSTREAM_REMOTE="upstream"
ORIGIN_REMOTE="origin"
MAIN_BRANCH="main"

# Function: Check if we're in a git repository
check_git_repo() {
    if ! git rev-parse --git-dir > /dev/null 2>&1; then
        echo "❌ Not in a git repository"
        exit 1
    fi
}

# Function: Verify remotes exist
verify_remotes() {
    if ! git remote | grep -q "^${UPSTREAM_REMOTE}$"; then
        echo "❌ Upstream remote '${UPSTREAM_REMOTE}' not found"
        echo "Add it with: git remote add ${UPSTREAM_REMOTE} <upstream-url>"
        exit 1
    fi
    
    if ! git remote | grep -q "^${ORIGIN_REMOTE}$"; then
        echo "❌ Origin remote '${ORIGIN_REMOTE}' not found"
        exit 1
    fi
}

# Function: Get current branch
get_current_branch() {
    git branch --show-current
}

# Function: Check working directory status
check_working_directory() {
    if ! git diff --quiet || ! git diff --staged --quiet; then
        echo "⚠️  Working directory has uncommitted changes"
        echo "Options:"
        echo "1. Commit changes"
        echo "2. Stash changes" 
        echo "3. Reset changes"
        read -p "Enter choice (1-3): " choice
        
        case $choice in
            1) git add -A && git commit -m "Pre-sync commit: $(date)" ;;
            2) git stash push -m "Pre-sync stash: $(date)" ;;
            3) git reset --hard HEAD ;;
            *) echo "Invalid choice"; exit 1 ;;
        esac
    fi
}

# Function: Sync main branch
sync_main_branch() {
    local current_branch=$(get_current_branch)
    
    echo "🔀 Switching to ${MAIN_BRANCH} branch..."
    git checkout ${MAIN_BRANCH}
    
    echo "📥 Fetching upstream changes..."
    git fetch ${UPSTREAM_REMOTE}
    
    echo "🔀 Merging upstream/${MAIN_BRANCH}..."
    if git merge ${UPSTREAM_REMOTE}/${MAIN_BRANCH}; then
        echo "✅ Merge successful"
    else
        echo "❌ Merge conflicts detected"
        echo "Resolve conflicts and run: git commit"
        exit 1
    fi
    
    echo "📤 Pushing to origin/${MAIN_BRANCH}..."
    git push ${ORIGIN_REMOTE} ${MAIN_BRANCH}
    
    # Return to original branch if different
    if [ "$current_branch" != "${MAIN_BRANCH}" ]; then
        echo "🔄 Returning to ${current_branch} branch..."
        git checkout ${current_branch}
    fi
}

# Function: Update feature branches
update_feature_branches() {
    echo "🌿 Checking feature branches..."
    
    # Get all local branches except main
    local branches=$(git branch --format='%(refname:short)' | grep -v "^${MAIN_BRANCH}$")
    
    for branch in $branches; do
        echo "🔍 Checking branch: $branch"
        
        # Check if branch has upstream tracking
        if git config branch.${branch}.remote > /dev/null 2>&1; then
            echo "  ↪️ Updating $branch..."
            git checkout $branch
            git pull ${ORIGIN_REMOTE} $branch
            
            # Optionally rebase on updated main
            read -p "  Rebase $branch on updated main? (y/N): " rebase_choice
            if [[ $rebase_choice =~ ^[Yy]$ ]]; then
                git rebase ${MAIN_BRANCH}
            fi
        else
            echo "  ⚠️ $branch has no upstream tracking"
        fi
    done
    
    # Return to main
    git checkout ${MAIN_BRANCH}
}

# Main execution
main() {
    echo "🚀 Enhanced Fork Synchronization"
    echo "================================"
    
    check_git_repo
    verify_remotes
    check_working_directory
    sync_main_branch
    
    read -p "Update feature branches? (y/N): " update_features
    if [[ $update_features =~ ^[Yy]$ ]]; then
        update_feature_branches
    fi
    
    echo "🎉 Synchronization complete!"
}

# Execute main function
main "$@"
```

### 2. **Conflict Resolution During Sync**

#### Common Conflict Scenarios
```bash
# Scenario 1: Conflicting changes in same file
# During: git merge upstream/main
# Result: CONFLICT (content): Merge conflict in file.txt

# Resolution steps:
# 1. Check conflict status
git status

# 2. View conflicted files
git diff --name-only --diff-filter=U

# 3. Resolve conflicts manually
nano file.txt  # Edit and resolve <<<< ==== >>>> markers

# 4. Stage resolved files
git add file.txt

# 5. Complete merge
git commit -m "Merge upstream/main with conflict resolution"
```

#### Automated Conflict Resolution
```bash
# For simple conflicts, use merge strategies
git merge upstream/main -X ours      # Favor our changes
git merge upstream/main -X theirs    # Favor upstream changes

# For specific file types
git merge upstream/main -X ours --no-commit
git checkout upstream/main -- package-lock.json  # Always use upstream version
git add package-lock.json
git commit -m "Merge upstream with package-lock update"
```

### 3. **Feature Branch Sync Strategies**

#### Rebase Strategy
```bash
# Keep feature branch updated with main
git checkout feature-branch
git fetch upstream
git rebase upstream/main

# Handle rebase conflicts
# (edit conflicted files, then)
git add .
git rebase --continue

# Force push updated branch (if already pushed)
git push --force-with-lease origin feature-branch
```

#### Merge Strategy
```bash
# Alternative to rebase for shared branches
git checkout feature-branch
git fetch upstream
git merge upstream/main

# Push updated branch
git push origin feature-branch
```

#### Interactive Rebase for Clean History
```bash
# Clean up feature branch before sync
git checkout feature-branch
git rebase -i HEAD~5  # Interactive rebase last 5 commits

# Sync with upstream
git fetch upstream
git rebase upstream/main

# Alternative: squash merge preparation
git checkout main
git merge --squash feature-branch
git commit -m "Feature: Complete implementation"
```

## 🤖 Automation Strategies

### 1. **GitHub Actions Automation**

#### Automated Fork Sync Workflow
```yaml
# .github/workflows/sync-upstream.yml
name: Sync Upstream
on:
  schedule:
    # Run daily at 2 AM UTC
    - cron: '0 2 * * *'
  workflow_dispatch:  # Allow manual trigger

jobs:
  sync:
    runs-on: ubuntu-latest
    if: github.repository != github.repository_owner  # Only run on forks
    
    steps:
      - name: Checkout
        uses: actions/checkout@v3
        with:
          token: ${{ secrets.GITHUB_TOKEN }}
          fetch-depth: 0
      
      - name: Configure Git
        run: |
          git config user.name "github-actions[bot]"
          git config user.email "github-actions[bot]@users.noreply.github.com"
      
      - name: Add upstream remote
        run: |
          git remote add upstream ${{ github.event.repository.parent.clone_url }}
          git fetch upstream
      
      - name: Sync main branch
        run: |
          git checkout main
          git merge upstream/main --no-edit
          git push origin main
      
      - name: Sync other branches
        run: |
          for branch in $(git branch -r --format='%(refname:short)' | grep '^upstream/' | grep -v 'upstream/main'); do
            branch_name=${branch#upstream/}
            if git show-ref --verify --quiet refs/heads/$branch_name; then
              echo "Syncing existing branch: $branch_name"
              git checkout $branch_name
              git merge $branch --no-edit
              git push origin $branch_name
            else
              echo "Creating new branch: $branch_name"
              git checkout -b $branch_name $branch
              git push origin $branch_name
            fi
          done
      
      - name: Create sync summary
        run: |
          echo "## Sync Summary" >> $GITHUB_STEP_SUMMARY
          echo "- ✅ Main branch synced" >> $GITHUB_STEP_SUMMARY
          echo "- 📊 $(git rev-list --count HEAD ^upstream/main) commits behind upstream" >> $GITHUB_STEP_SUMMARY
          echo "- 🕐 Last sync: $(date)" >> $GITHUB_STEP_SUMMARY
```

#### Smart Conflict Detection
```yaml
# .github/workflows/sync-check.yml
name: Sync Conflict Check
on:
  schedule:
    - cron: '0 8 * * *'  # Daily at 8 AM
  workflow_dispatch:

jobs:
  check-sync:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
        with:
          fetch-depth: 0
      
      - name: Check for sync conflicts
        id: conflict-check
        run: |
          git remote add upstream ${{ github.event.repository.parent.clone_url }}
          git fetch upstream
          
          # Test merge without committing
          git merge upstream/main --no-commit --no-ff || {
            echo "conflicts=true" >> $GITHUB_OUTPUT
            git merge --abort
          }
      
      - name: Create issue on conflicts
        if: steps.conflict-check.outputs.conflicts == 'true'
        uses: actions/github-script@v6
        with:
          script: |
            github.rest.issues.create({
              owner: context.repo.owner,
              repo: context.repo.repo,
              title: '🚨 Upstream Sync Conflicts Detected',
              body: `
              ## Sync Conflict Alert
              
              Automated sync check detected conflicts when attempting to merge upstream changes.
              
              ### Action Required
              - [ ] Review conflicting files
              - [ ] Manually resolve conflicts
              - [ ] Test resolution
              - [ ] Merge upstream changes
              
              ### Commands to Resolve
              \`\`\`bash
              git fetch upstream
              git merge upstream/main
              # Resolve conflicts in editor
              git add .
              git commit
              git push origin main
              \`\`\`
              
              **Detected:** ${new Date().toISOString()}
              `,
              labels: ['sync-conflict', 'urgent']
            });
```

### 2. **Local Automation Scripts**

#### Cron Job Setup
```bash
# Add to crontab (crontab -e)
# Daily sync at 9 AM
0 9 * * * cd /path/to/project && ./scripts/sync-fork.sh >> /var/log/fork-sync.log 2>&1

# Weekly sync on Monday at 9 AM
0 9 * * 1 cd /path/to/project && ./scripts/enhanced-sync.sh >> /var/log/fork-sync.log 2>&1
```

#### Git Hook Automation
```bash
# .git/hooks/post-merge
#!/bin/bash
# Auto-push to origin after successful upstream merge

# Check if this is an upstream merge
if git log -1 --pretty=%B | grep -q "Merge.*upstream"; then
    echo "Upstream merge detected, pushing to origin..."
    git push origin $(git branch --show-current)
fi
```

#### Makefile Integration
```makefile
# Makefile
.PHONY: sync-upstream sync-check

sync-upstream:
	@echo "🔄 Syncing with upstream..."
	@git fetch upstream
	@git checkout main
	@git merge upstream/main
	@git push origin main
	@echo "✅ Sync complete"

sync-check:
	@echo "🔍 Checking sync status..."
	@git fetch upstream >/dev/null 2>&1
	@commits_behind=$$(git rev-list --count HEAD..upstream/main); \
	if [ $$commits_behind -gt 0 ]; then \
		echo "⚠️  Fork is $$commits_behind commits behind upstream"; \
		echo "Run 'make sync-upstream' to update"; \
	else \
		echo "✅ Fork is up to date"; \
	fi

sync-conflicts:
	@echo "🔍 Testing for merge conflicts..."
	@git fetch upstream >/dev/null 2>&1
	@if git merge-tree $$(git merge-base HEAD upstream/main) HEAD upstream/main | grep -q "<<<<<<< "; then \
		echo "⚠️  Conflicts detected with upstream"; \
		echo "Manual resolution required"; \
	else \
		echo "✅ No conflicts detected"; \
	fi
```

## 📊 Monitoring e Tracking

### 1. **Sync Status Tracking**

#### Dashboard Script
```bash
#!/bin/bash
# sync-dashboard.sh - Fork synchronization dashboard

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Function: Get commits behind upstream
get_commits_behind() {
    git fetch upstream >/dev/null 2>&1
    git rev-list --count HEAD..upstream/main 2>/dev/null || echo "unknown"
}

# Function: Get last sync date
get_last_sync() {
    git log --grep="Merge.*upstream" --format="%ar" -1 2>/dev/null || echo "never"
}

# Function: Check for local changes
check_local_changes() {
    if ! git diff --quiet || ! git diff --staged --quiet; then
        echo "yes"
    else
        echo "no"
    fi
}

# Function: Get diverged commits
get_diverged_commits() {
    git fetch upstream >/dev/null 2>&1
    local ahead=$(git rev-list --count upstream/main..HEAD 2>/dev/null || echo "0")
    local behind=$(git rev-list --count HEAD..upstream/main 2>/dev/null || echo "0")
    echo "$ahead,$behind"
}

# Main dashboard
echo -e "${BLUE}🔄 Fork Sync Dashboard${NC}"
echo "======================="

# Repository info
echo -e "${YELLOW}📁 Repository:${NC} $(basename $(git rev-parse --show-toplevel))"
echo -e "${YELLOW}🌿 Current Branch:${NC} $(git branch --show-current)"

# Remote info
echo -e "${YELLOW}📡 Origin:${NC} $(git remote get-url origin 2>/dev/null || echo 'not configured')"
echo -e "${YELLOW}⬆️  Upstream:${NC} $(git remote get-url upstream 2>/dev/null || echo 'not configured')"

# Sync status
commits_behind=$(get_commits_behind)
last_sync=$(get_last_sync)
local_changes=$(check_local_changes)
diverged=$(get_diverged_commits)
ahead=$(echo $diverged | cut -d, -f1)
behind=$(echo $diverged | cut -d, -f2)

echo ""
echo -e "${BLUE}📊 Sync Status${NC}"
echo "==============="

if [ "$commits_behind" = "0" ]; then
    echo -e "${GREEN}✅ Up to date${NC}"
elif [ "$commits_behind" = "unknown" ]; then
    echo -e "${RED}❌ Cannot determine status${NC}"
else
    echo -e "${YELLOW}⚠️  $commits_behind commits behind upstream${NC}"
fi

echo -e "${YELLOW}📅 Last Sync:${NC} $last_sync"
echo -e "${YELLOW}🔧 Local Changes:${NC} $local_changes"
echo -e "${YELLOW}📈 Divergence:${NC} $ahead ahead, $behind behind"

# Recent upstream activity
echo ""
echo -e "${BLUE}📈 Recent Upstream Activity${NC}"
echo "============================"
git fetch upstream >/dev/null 2>&1
git log upstream/main --oneline -5 --format="%C(yellow)%h%C(reset) %s %C(green)(%ar)%C(reset)"

# Recommendations
echo ""
echo -e "${BLUE}💡 Recommendations${NC}"
echo "=================="

if [ "$commits_behind" != "0" ] && [ "$commits_behind" != "unknown" ]; then
    echo -e "${YELLOW}🔄 Run sync to get latest changes${NC}"
fi

if [ "$local_changes" = "yes" ]; then
    echo -e "${YELLOW}💾 Commit or stash local changes before sync${NC}"
fi

if [ "$ahead" != "0" ]; then
    echo -e "${YELLOW}📤 Consider pushing local commits to origin${NC}"
fi
```

### 2. **Integration with Development Tools**

#### VS Code Extension Configuration
```json
// .vscode/settings.json
{
    "git.fetchOnPull": true,
    "git.pruneOnFetch": true,
    "gitlens.remotes": [
        {
            "name": "upstream",
            "urls": {
                "base": "https://github.com/original-owner/repo"
            }
        }
    ],
    "gitlens.views.remotes.pullRequests.enabled": true
}
```

#### GitHub CLI Integration
```bash
# Check PR status across forks
gh pr list --repo original-owner/repo --author @me

# Create PR from fork
gh pr create --repo original-owner/repo \
  --title "Feature: New functionality" \
  --body "Detailed description"

# Sync fork using GitHub CLI
gh repo sync your-username/repo --source original-owner/repo
```

## 🎯 Best Practices

### 1. **Sync Frequency Guidelines**

#### Project Type Recommendations
```markdown
# Active Open Source Projects
- Daily sync for main contributors
- Before starting new features
- After major upstream releases

# Stable Dependencies
- Weekly or bi-weekly sync
- Version-based sync (tags/releases)
- Security update immediate sync

# Personal Projects/Learning
- Sync before major development sessions
- Monthly maintenance sync
- Before contributing back to upstream
```

### 2. **Branch Management Strategy**

#### Clean Branch Workflow
```bash
# 1. Always start features from updated main
git checkout main
git pull upstream main
git checkout -b feature/new-functionality

# 2. Regularly sync feature branch
git fetch upstream
git rebase upstream/main  # Keep linear history

# 3. Final sync before PR
git fetch upstream
git rebase upstream/main
git push --force-with-lease origin feature/new-functionality
```

### 3. **Team Coordination**

#### Communication Protocols
```markdown
# Team Sync Coordination
📢 Announce major upstream syncs in team chat
🕐 Schedule sync windows for minimal disruption
📋 Document breaking changes from upstream
🔄 Coordinate feature branch rebases
```

## 🚨 Common Issues e Solutions

### 1. **Sync Failures**

#### Large Divergence Problem
```bash
# When fork has diverged significantly
git fetch upstream
git log --oneline --graph main upstream/main

# Option 1: Rebase (for clean history)
git rebase upstream/main
# Handle conflicts, then:
git push --force-with-lease origin main

# Option 2: Merge (preserves history)
git merge upstream/main
git push origin main

# Option 3: Reset (when local changes are not needed)
git reset --hard upstream/main
git push --force origin main
```

#### Broken Upstream Remote
```bash
# Update upstream URL if repository moved
git remote set-url upstream https://github.com/new-owner/project.git

# Re-add upstream if accidentally removed
git remote remove upstream
git remote add upstream https://github.com/original-owner/project.git
git fetch upstream
```

### 2. **Performance Optimization**

#### Large Repository Handling
```bash
# Shallow clone for large repositories
git clone --depth 1 https://github.com/your-username/large-project.git
cd large-project
git remote add upstream https://github.com/original-owner/large-project.git

# Partial clone (Git 2.19+)
git clone --filter=blob:none https://github.com/your-username/large-project.git

# Sync with depth control
git fetch upstream --depth=50
```

## 🏁 Conclusioni

La sincronizzazione upstream è un aspetto critico della collaborazione open source. Una strategia ben definita garantisce:

- **Code Quality**: Accesso alle latest fixes e improvements
- **Security**: Aggiornamenti di sicurezza tempestivi
- **Compatibility**: Riduzione conflicts nei Pull Requests
- **Team Efficiency**: Workflows automatizzati e coordinati

### Key Takeaways

1. **Setup Correct**: Configure upstream remote properly
2. **Regular Sync**: Establish consistent sync frequency
3. **Conflict Prevention**: Test merges before actual sync
4. **Automation**: Use tools to reduce manual overhead
5. **Team Coordination**: Communicate sync activities

### Prossimi Passi

- Implementa automated sync workflow per i tuoi progetti
- Stabilisci sync schedule based on project activity
- Configura monitoring per detect sync conflicts early
- Documenta sync procedures per il team

## 🔗 Risorse Aggiuntive

### Documentazione
- [GitHub Fork Syncing](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/working-with-forks/syncing-a-fork)
- [Git Remote Documentation](https://git-scm.com/docs/git-remote)

### Tools
- [GitHub CLI Sync](https://cli.github.com/manual/gh_repo_sync)
- [Fork Sync Action](https://github.com/marketplace/actions/fork-sync)

### Monitoring
- [GitKraken Fork Assistant](https://www.gitkraken.com/)
- [Sourcetree Fork Management](https://www.sourcetreeapp.com/)

## 📝 Esercizi Pratici

### Esercizio 1: Setup Upstream Sync
1. Fork un repository pubblico
2. Configure upstream remote
3. Implementa basic sync script
4. Test conflict resolution

### Esercizio 2: Automated Workflow
1. Setup GitHub Actions sync workflow
2. Configure conflict detection
3. Test automation with simulated changes
4. Document process per team

### Esercizio 3: Advanced Sync Management
1. Implement multi-branch sync strategy
2. Setup monitoring dashboard
3. Create team coordination procedures
4. Optimize per large repository

---

## 🧭 Navigazione

- [📖 Guide Teoriche](../README.md#guide-teoriche)
- [⬅️ Code Review](./03-code-review.md)
- [➡️ Esempi Pratici](../esempi/01-first-fork.md)
- [🏠 Home Modulo](../README.md)
