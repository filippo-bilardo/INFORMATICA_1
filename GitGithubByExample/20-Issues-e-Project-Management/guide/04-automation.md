# Automation

## 📖 Introduzione

L'**automazione** è fondamentale per efficienza e consistenza nei progetti moderni. GitHub offre diversi strumenti per automatizzare workflow, dalla gestione di Issues alle deployment pipeline. Questa guida copre tutte le forme di automazione disponibili nell'ecosistema GitHub.

L'automazione può eliminare:
- **Lavoro ripetitivo**: Labeling, assignment, notifications
- **Errori umani**: Status updates, branch protection
- **Colli di bottiglia**: Review assignment, merge automation
- **Inconsistenze**: Formatting, naming conventions

## 🤖 Tipi di Automazione

### 1. GitHub Actions
Piattaforma CI/CD nativa per workflow complessi

### 2. Repository Rules
Automazione governance e compliance

### 3. Project Automation
Workflow management per Projects

### 4. Third-party Integrations
Bot e servizi esterni (Dependabot, CodeQL)

### 5. Webhooks e API
Integrazioni personalizzate

## ⚙️ GitHub Actions per Issue Management

### Auto-labeling

#### Basato su Contenuto Issue

```yaml
name: Auto Label Issues
on:
  issues:
    types: [opened]

jobs:
  auto-label:
    runs-on: ubuntu-latest
    steps:
    - name: Label bug reports
      if: contains(github.event.issue.title, '[BUG]') || contains(github.event.issue.body, 'bug')
      run: |
        gh issue edit ${{ github.event.issue.number }} \
          --add-label "Type: Bug" \
          --repo ${{ github.repository }}
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Label feature requests  
      if: contains(github.event.issue.title, '[FEATURE]') || contains(github.event.issue.body, 'feature')
      run: |
        gh issue edit ${{ github.event.issue.number }} \
          --add-label "Type: Feature" \
          --repo ${{ github.repository }}
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

#### Basato su Template Usato

```yaml
name: Template-based Labeling
on:
  issues:
    types: [opened]

jobs:
  template-label:
    runs-on: ubuntu-latest
    steps:
    - name: Extract template info
      id: template
      run: |
        # Extract template name from issue body
        template=$(echo '${{ github.event.issue.body }}' | grep -o 'name: [^}]*' | head -1 | cut -d' ' -f2-)
        echo "template=$template" >> $GITHUB_OUTPUT
    
    - name: Apply template labels
      run: |
        case "${{ steps.template.outputs.template }}" in
          "Bug Report")
            gh issue edit ${{ github.event.issue.number }} --add-label "Type: Bug,Priority: Triage"
            ;;
          "Feature Request")
            gh issue edit ${{ github.event.issue.number }} --add-label "Type: Feature,Status: Backlog"
            ;;
          "Documentation")
            gh issue edit ${{ github.event.issue.number }} --add-label "Type: Documentation,Priority: Low"
            ;;
        esac
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### Auto-assignment

#### Round-robin Assignment

```yaml
name: Auto Assign Issues
on:
  issues:
    types: [opened]

jobs:
  auto-assign:
    runs-on: ubuntu-latest
    steps:
    - name: Get team members
      id: team
      run: |
        # Define team members
        members=("alice" "bob" "charlie" "diana")
        
        # Get issue number for round-robin
        issue_num=${{ github.event.issue.number }}
        member_index=$((issue_num % ${#members[@]}))
        assignee=${members[$member_index]}
        
        echo "assignee=$assignee" >> $GITHUB_OUTPUT
    
    - name: Assign issue
      run: |
        gh issue edit ${{ github.event.issue.number }} \
          --assignee ${{ steps.team.outputs.assignee }} \
          --repo ${{ github.repository }}
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

#### Skill-based Assignment

```yaml
name: Skill-based Assignment
on:
  issues:
    types: [opened, labeled]

jobs:
  assign-by-skill:
    runs-on: ubuntu-latest
    steps:
    - name: Determine assignee by labels
      id: assignee
      run: |
        labels="${{ join(github.event.issue.labels.*.name, ',') }}"
        
        case "$labels" in
          *"Area: Frontend"*)
            echo "assignee=frontend-team" >> $GITHUB_OUTPUT
            ;;
          *"Area: Backend"*)
            echo "assignee=backend-team" >> $GITHUB_OUTPUT
            ;;
          *"Area: Database"*)
            echo "assignee=dba-team" >> $GITHUB_OUTPUT
            ;;
          *"Type: Security"*)
            echo "assignee=security-team" >> $GITHUB_OUTPUT
            ;;
          *)
            echo "assignee=triage-team" >> $GITHUB_OUTPUT
            ;;
        esac
    
    - name: Assign to team
      if: steps.assignee.outputs.assignee != ''
      run: |
        gh issue edit ${{ github.event.issue.number }} \
          --assignee ${{ steps.assignee.outputs.assignee }} \
          --repo ${{ github.repository }}
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### Stale Issue Management

```yaml
name: Stale Issue Management
on:
  schedule:
    - cron: '0 0 * * *'  # Daily at midnight

jobs:
  stale:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/stale@v8
      with:
        # Issues
        stale-issue-message: |
          This issue has been automatically marked as stale because it has not had 
          recent activity. It will be closed if no further activity occurs within 7 days.
          
          If you believe this issue is still relevant, please comment to keep it open.
        close-issue-message: |
          This issue has been automatically closed due to inactivity. 
          If you need to reopen this issue, please create a new issue and reference this one.
        
        # Pull Requests  
        stale-pr-message: |
          This pull request has been automatically marked as stale because it has not had
          recent activity. It will be closed if no further activity occurs within 7 days.
        close-pr-message: |
          This pull request has been automatically closed due to inactivity.
        
        # Timing
        days-before-stale: 30
        days-before-close: 7
        
        # Labels
        stale-issue-label: 'Status: Stale'
        stale-pr-label: 'Status: Stale'
        close-issue-label: 'Status: Closed'
        close-pr-label: 'Status: Closed'
        
        # Exemptions
        exempt-issue-labels: 'Status: Pinned,Priority: High'
        exempt-pr-labels: 'Status: Pinned,Priority: High'
        
        # Enable operations
        remove-stale-when-updated: true
        ascending: true
```

## 🔀 Pull Request Automation

### Auto-merge per Dependency Updates

```yaml
name: Auto-merge Dependabot PRs
on:
  pull_request:
    types: [opened, synchronize]

jobs:
  auto-merge:
    runs-on: ubuntu-latest
    if: github.actor == 'dependabot[bot]'
    steps:
    - name: Check if PR is ready
      id: check
      run: |
        # Check if all checks pass
        checks_status=$(gh pr view ${{ github.event.pull_request.number }} --json statusCheckRollup -q '.statusCheckRollup[].state' | grep -v SUCCESS | wc -l)
        
        if [ $checks_status -eq 0 ]; then
          echo "ready=true" >> $GITHUB_OUTPUT
        else
          echo "ready=false" >> $GITHUB_OUTPUT
        fi
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
    
    - name: Auto-approve minor updates
      if: steps.check.outputs.ready == 'true' && contains(github.event.pull_request.title, 'patch') || contains(github.event.pull_request.title, 'minor')
      run: |
        gh pr review ${{ github.event.pull_request.number }} --approve --body "Auto-approved by GitHub Actions"
        gh pr merge ${{ github.event.pull_request.number }} --squash --delete-branch
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### Auto-labeling PRs

```yaml
name: PR Auto Labeling
on:
  pull_request:
    types: [opened, synchronize]

jobs:
  label-pr:
    runs-on: ubuntu-latest
    steps:
    - name: Checkout code
      uses: actions/checkout@v4
      with:
        fetch-depth: 0
    
    - name: Get changed files
      id: changes
      run: |
        # Get list of changed files
        changed_files=$(git diff --name-only ${{ github.event.pull_request.base.sha }} ${{ github.event.pull_request.head.sha }})
        echo "files=$changed_files" >> $GITHUB_OUTPUT
    
    - name: Label based on files
      run: |
        files="${{ steps.changes.outputs.files }}"
        labels=()
        
        # Check for frontend changes
        if echo "$files" | grep -E "\.(js|jsx|ts|tsx|css|scss|html)$"; then
          labels+=("Area: Frontend")
        fi
        
        # Check for backend changes
        if echo "$files" | grep -E "\.(py|java|go|rs|php)$"; then
          labels+=("Area: Backend")
        fi
        
        # Check for documentation changes
        if echo "$files" | grep -E "\.(md|txt|rst)$"; then
          labels+=("Type: Documentation")
        fi
        
        # Check for test changes
        if echo "$files" | grep -E "test|spec"; then
          labels+=("Type: Test")
        fi
        
        # Add labels if any found
        if [ ${#labels[@]} -gt 0 ]; then
          label_string=$(IFS=','; echo "${labels[*]}")
          gh pr edit ${{ github.event.pull_request.number }} --add-label "$label_string"
        fi
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

## 📊 Project Automation

### Auto-add Items to Projects

```yaml
name: Add to Project
on:
  issues:
    types: [opened]
  pull_request:
    types: [opened]

jobs:
  add-to-project:
    runs-on: ubuntu-latest
    steps:
    - name: Add item to project
      uses: actions/add-to-project@v0.5.0
      with:
        project-url: https://github.com/users/USERNAME/projects/PROJECT_NUMBER
        github-token: ${{ secrets.PROJECT_TOKEN }}
```

### Smart Project Field Updates

```yaml
name: Update Project Fields
on:
  issues:
    types: [opened, closed, labeled]
  pull_request:
    types: [opened, closed, merged, ready_for_review]

jobs:
  update-project:
    runs-on: ubuntu-latest
    steps:
    - name: Update project item
      uses: actions/github-script@v6
      with:
        github-token: ${{ secrets.PROJECT_TOKEN }}
        script: |
          const query = `
            query($repo: String!, $owner: String!, $number: Int!) {
              repository(name: $repo, owner: $owner) {
                issue(number: $number) {
                  projectItems(first: 10) {
                    nodes {
                      id
                      project {
                        id
                        title
                      }
                    }
                  }
                }
              }
            }
          `;
          
          const variables = {
            repo: context.repo.repo,
            owner: context.repo.owner,
            number: context.payload.issue?.number || context.payload.pull_request?.number
          };
          
          const result = await github.graphql(query, variables);
          
          // Update project fields based on event
          const eventType = context.eventName;
          const action = context.payload.action;
          
          for (const item of result.repository.issue.projectItems.nodes) {
            let statusUpdate = null;
            
            if (eventType === 'issues') {
              if (action === 'opened') statusUpdate = 'Todo';
              if (action === 'closed') statusUpdate = 'Done';
            } else if (eventType === 'pull_request') {
              if (action === 'opened') statusUpdate = 'In Progress';
              if (action === 'ready_for_review') statusUpdate = 'Review';
              if (action === 'merged') statusUpdate = 'Done';
            }
            
            if (statusUpdate) {
              // Update project item status (implementation depends on your project fields)
              console.log(`Updating item ${item.id} to ${statusUpdate}`);
            }
          }
```

## 🔒 Repository Rules Automation

### Branch Protection

```yaml
# .github/workflows/branch-protection.yml
name: Enforce Branch Protection
on:
  repository_dispatch:
    types: [protect-branches]

jobs:
  protect-branches:
    runs-on: ubuntu-latest
    steps:
    - name: Protect main branch
      run: |
        gh api repos/${{ github.repository }}/branches/main/protection \
          --method PUT \
          --field required_status_checks='{"strict":true,"contexts":["ci","test"]}' \
          --field enforce_admins=true \
          --field required_pull_request_reviews='{"required_approving_review_count":2,"dismiss_stale_reviews":true}' \
          --field restrictions=null
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### Auto-delete Merged Branches

```yaml
name: Auto-delete Merged Branches
on:
  pull_request:
    types: [closed]

jobs:
  delete-branch:
    runs-on: ubuntu-latest
    if: github.event.pull_request.merged == true && github.event.pull_request.head.ref != 'main'
    steps:
    - name: Delete merged branch
      run: |
        gh api repos/${{ github.repository }}/git/refs/heads/${{ github.event.pull_request.head.ref }} \
          --method DELETE
      env:
        GH_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

## 🕷️ Webhooks e API Integration

### Custom Webhook Handler

```javascript
// webhook-handler.js
const express = require('express');
const crypto = require('crypto');
const { Octokit } = require('@octokit/rest');

const app = express();
const octokit = new Octokit({ auth: process.env.GITHUB_TOKEN });

app.use(express.json());

// Webhook signature verification
function verifySignature(payload, signature) {
  const computedSignature = crypto
    .createHmac('sha256', process.env.WEBHOOK_SECRET)
    .update(payload)
    .digest('hex');
  return `sha256=${computedSignature}` === signature;
}

app.post('/webhook', async (req, res) => {
  const signature = req.headers['x-hub-signature-256'];
  
  if (!verifySignature(JSON.stringify(req.body), signature)) {
    return res.status(401).send('Unauthorized');
  }
  
  const { action, issue, repository } = req.body;
  
  // Auto-assign based on custom logic
  if (action === 'opened' && issue) {
    const assignee = await determineAssignee(issue);
    
    if (assignee) {
      await octokit.issues.addAssignees({
        owner: repository.owner.login,
        repo: repository.name,
        issue_number: issue.number,
        assignees: [assignee]
      });
    }
  }
  
  res.status(200).send('OK');
});

async function determineAssignee(issue) {
  // Custom logic for assignee determination
  const keywords = {
    'database': 'db-expert',
    'frontend': 'ui-expert', 
    'security': 'security-expert'
  };
  
  const content = (issue.title + ' ' + issue.body).toLowerCase();
  
  for (const [keyword, assignee] of Object.entries(keywords)) {
    if (content.includes(keyword)) {
      return assignee;
    }
  }
  
  return null;
}

app.listen(3000, () => {
  console.log('Webhook handler listening on port 3000');
});
```

## 🤖 Third-party Bot Integration

### Dependabot Configuration

```yaml
# .github/dependabot.yml
version: 2
updates:
  # Enable version updates for npm
  - package-ecosystem: "npm"
    directory: "/"
    schedule:
      interval: "weekly"
      day: "monday"
      time: "09:00"
    labels:
      - "Type: Dependencies"
      - "Priority: Low"
    reviewers:
      - "maintenance-team"
    commit-message:
      prefix: "deps"
      include: "scope"
    
  # Enable version updates for pip
  - package-ecosystem: "pip"
    directory: "/backend"
    schedule:
      interval: "monthly"
    labels:
      - "Type: Dependencies"
      - "Area: Backend"
```

### CodeQL Analysis

```yaml
# .github/workflows/codeql-analysis.yml
name: CodeQL Analysis
on:
  push:
    branches: [main, develop]
  pull_request:
    branches: [main]
  schedule:
    - cron: '0 0 * * 1'  # Weekly on Monday

jobs:
  analyze:
    runs-on: ubuntu-latest
    permissions:
      actions: read
      contents: read
      security-events: write
    
    strategy:
      fail-fast: false
      matrix:
        language: ['javascript', 'python']
    
    steps:
    - name: Checkout repository
      uses: actions/checkout@v4
    
    - name: Initialize CodeQL
      uses: github/codeql-action/init@v2
      with:
        languages: ${{ matrix.language }}
        queries: security-and-quality
    
    - name: Autobuild
      uses: github/codeql-action/autobuild@v2
    
    - name: Perform CodeQL Analysis
      uses: github/codeql-action/analyze@v2
      with:
        category: "/language:${{matrix.language}}"
```

## 📊 Monitoring e Metrics

### Workflow Success Tracking

```yaml
name: Workflow Metrics
on:
  workflow_run:
    workflows: ["CI", "Deploy", "Test"]
    types: [completed]

jobs:
  track-metrics:
    runs-on: ubuntu-latest
    steps:
    - name: Send metrics
      run: |
        # Send to monitoring system
        curl -X POST ${{ secrets.METRICS_ENDPOINT }} \
          -H "Content-Type: application/json" \
          -d '{
            "workflow": "${{ github.event.workflow_run.name }}",
            "status": "${{ github.event.workflow_run.conclusion }}",
            "duration": "${{ github.event.workflow_run.run_duration_ms }}",
            "repository": "${{ github.repository }}",
            "timestamp": "${{ github.event.workflow_run.updated_at }}"
          }'
```

### Issue Resolution Time

```yaml
name: Issue Metrics
on:
  issues:
    types: [closed]

jobs:
  calculate-metrics:
    runs-on: ubuntu-latest
    steps:
    - name: Calculate resolution time
      run: |
        created_at="${{ github.event.issue.created_at }}"
        closed_at="${{ github.event.issue.closed_at }}"
        
        created_timestamp=$(date -d "$created_at" +%s)
        closed_timestamp=$(date -d "$closed_at" +%s)
        
        resolution_time=$((closed_timestamp - created_timestamp))
        resolution_hours=$((resolution_time / 3600))
        
        echo "Issue #${{ github.event.issue.number }} resolved in $resolution_hours hours"
        
        # Send to analytics system
        curl -X POST ${{ secrets.ANALYTICS_ENDPOINT }} \
          -H "Content-Type: application/json" \
          -d '{
            "issue_number": ${{ github.event.issue.number }},
            "resolution_time_hours": '$resolution_hours',
            "labels": ${{ toJson(github.event.issue.labels) }},
            "repository": "${{ github.repository }}"
          }'
```

## 🚨 Problemi Comuni e Soluzioni

### Rate Limiting

**Problema**: GitHub API rate limits con automation intensive

**Soluzione**:
```yaml
- name: Handle rate limiting
  run: |
    # Check rate limit before operations
    rate_limit=$(gh api rate_limit --jq '.rate.remaining')
    
    if [ $rate_limit -lt 100 ]; then
      echo "Rate limit low ($rate_limit), waiting..."
      sleep 300  # Wait 5 minutes
    fi
    
    # Batch operations when possible
    # Use GitHub Apps for higher limits
```

### Token Permissions

**Problema**: Insufficient permissions per automation

**Soluzione**:
```yaml
# Use fine-grained personal access tokens
permissions:
  issues: write
  pull-requests: write
  contents: read
  metadata: read

# Or GitHub App with specific permissions
```

### Conflicting Automations

**Problema**: Multiple workflows che si interferiscono

**Soluzione**:
```yaml
# Use concurrency groups
concurrency:
  group: issue-automation-${{ github.event.issue.number }}
  cancel-in-progress: false

# Coordinate with conditional logic
if: github.actor != 'github-actions[bot]'
```

## 📋 Best Practices

### 1. Start Simple

```yaml
# Begin with basic automation
- Auto-labeling
- Stale issue management
- Basic PR checks

# Gradually add complexity
- Custom assignment logic
- Advanced project automation
- External integrations
```

### 2. Testing Automation

```yaml
# Test workflows in development
- Use repository dispatch for manual triggers
- Test with draft PRs
- Monitor workflow logs

# Version control your automation
- .github/workflows/ in version control
- Document automation behavior
- Review automation changes
```

### 3. Monitoring e Maintenance

```yaml
# Monitor automation effectiveness
- Track automation success rates
- Measure time savings
- Collect team feedback

# Regular maintenance
- Update action versions
- Review and prune unused workflows
- Optimize performance
```

## 🧪 Quiz di Verifica

### Domanda 1
**Come implementeresti un sistema di assignment automatico basato su expertise del team?**

<details>
<summary>Risposta</summary>

```yaml
1. Creare mapping skills → team members in file config
2. Analizzare labels/content di issues per identificare skill richieste
3. Query GitHub API per controllare workload corrente
4. Assegnare a membro con skill appropriata e minor carico
5. Fallback a round-robin se nessuna skill match
```

Con custom fields in Projects per tracciare expertise e availability.

</details>

### Domanda 2
**Quale approccio useresti per evitare automation loops?**

<details>
<summary>Risposta</summary>

```yaml
# Conditional logic
if: github.actor != 'github-actions[bot]'

# Token tagging
if: !contains(github.event.issue.body, '[automated]')

# Concurrency groups
concurrency:
  group: automation-${{ github.event.issue.number }}
  cancel-in-progress: false

# State tracking con labels
if: !contains(github.event.issue.labels.*.name, 'automated-processed')
```

</details>

### Domanda 3
**Come implementeresti escalation automatica per issues critiche?**

<details>
<summary>Risposta</summary>

```yaml
# Schedule check for critical issues
on:
  schedule:
    - cron: '0 */2 * * *'  # Every 2 hours

# Logic:
1. Query issues con label "Priority: Critical"
2. Check tempo dalla creazione/ultimo update
3. Se > threshold, escalate:
   - Ping team lead
   - Add label "Escalated"
   - Create Slack notification
   - Assign to senior team member
```

</details>

## 🛠️ Esercizio Pratico

### Obiettivo
Implementare sistema di automazione completo per progetto team.

### Passi

1. **Issue Automation**:
   ```yaml
   # Auto-labeling basato su template
   # Assignment basato su area/skill
   # Stale issue management
   ```

2. **PR Automation**:
   ```yaml
   # Auto-labeling basato su file changes
   # Auto-assignment di reviewers
   # Auto-merge per dependency updates
   ```

3. **Project Integration**:
   ```yaml
   # Auto-add items to project
   # Status updates based on events
   # Sprint planning automation
   ```

4. **Monitoring**:
   ```yaml
   # Metrics collection
   # Performance tracking
   # Error alerting
   ```

5. **Documentation**:
   ```markdown
   # Team automation guide
   # Troubleshooting runbook
   # Maintenance checklist
   ```

### Verifica Risultati

Il completamento dell'esercizio dimostra:
- ✅ Automation riduce lavoro manuale significativamente
- ✅ Team workflow è più consistente e predictable
- ✅ Metrics mostrano miglioramento in efficiency
- ✅ Sistema è maintainable e well-documented

## 🔗 Link Correlati

- [01 - GitHub Issues](./01-github-issues.md) - Fondamentali degli Issues
- [02 - Labels e Organization](./02-labels-organization.md) - Organizzazione sistemica
- [03 - GitHub Projects](./03-github-projects.md) - Project management

---

### 🧭 Navigazione

- **⬅️ Precedente**: [03 - GitHub Projects](./03-github-projects.md)
- **🏠 Home Modulo**: [README.md](../README.md)
- **➡️ Successivo**: [Esempi Pratici](../esempi/01-issue-management.md)
