# Esercizio 2: Gestione Avanzata del Team

## Obiettivo
Implementare un sistema completo di gestione del team per un progetto GitHub, includendo ruoli, permessi, workflow di collaborazione e metriche di performance del team.

## Scenario
Sei il Team Lead di "EcoCommerce", una startup che sviluppa una piattaforma e-commerce sostenibile. Il tuo team è cresciuto rapidamente e ora devi strutturare la collaborazione tra:
- 8 sviluppatori (4 senior, 4 junior)
- 3 QA engineers
- 2 DevOps engineers
- 1 Tech Lead
- 1 Product Manager
- 2 UI/UX designers

## Struttura del Team

### Organizzazione GitHub
```
EcoCommerce Organization
├── Core Team (Owners)
│   ├── tech-leads
│   └── product-managers
├── Development Teams
│   ├── frontend-team
│   ├── backend-team
│   └── fullstack-team
├── Quality Assurance
│   ├── qa-engineers
│   └── automation-testers
├── Operations
│   ├── devops-team
│   └── security-team
└── Design Team
    ├── ui-designers
    └── ux-researchers
```

## Fase 1: Configurazione Team e Ruoli

### 1. Creazione Team Structure

**Script di Setup Team**:
```bash
#!/bin/bash
# setup-teams.sh - Configurazione automatica team GitHub

# Definizione team structure
declare -A TEAMS=(
    ["tech-leads"]="admin"
    ["product-managers"]="admin"
    ["frontend-team"]="write"
    ["backend-team"]="write"
    ["fullstack-team"]="write"
    ["qa-engineers"]="triage"
    ["automation-testers"]="write"
    ["devops-team"]="admin"
    ["security-team"]="admin"
    ["ui-designers"]="read"
    ["ux-researchers"]="read"
)

# Membri per team
declare -A TEAM_MEMBERS=(
    ["tech-leads"]="alice.senior bob.lead"
    ["product-managers"]="sarah.pm"
    ["frontend-team"]="charlie.dev david.dev emma.junior frank.junior"
    ["backend-team"]="grace.senior henry.dev iris.junior jack.dev"
    ["fullstack-team"]="alice.senior bob.lead charlie.dev grace.senior"
    ["qa-engineers"]="kate.qa lisa.qa mike.qa"
    ["automation-testers"]="kate.qa lisa.qa"
    ["devops-team"]="noah.devops olivia.devops"
    ["security-team"]="noah.devops alice.senior"
    ["ui-designers"]="paul.design quinn.design"
    ["ux-researchers"]="quinn.design sarah.pm"
)

echo "🏗️  Configurazione Team EcoCommerce"
echo "=================================="

for team in "${!TEAMS[@]}"; do
    permission="${TEAMS[$team]}"
    members="${TEAM_MEMBERS[$team]}"
    
    echo "Creating team: $team with permission: $permission"
    # GitHub CLI commands (example)
    gh api orgs/ecocommerce/teams -f name="$team" -f permission="$permission"
    
    # Add members to team
    for member in $members; do
        echo "  Adding $member to $team"
        gh api orgs/ecocommerce/teams/$team/memberships/$member -f role="member"
    done
done
```

### 2. Matrice Responsabilità (RACI)

```markdown
| Attività                | Tech Lead | PM | Frontend | Backend | QA | DevOps | Design |
|-------------------------|-----------|----|---------|---------|----|--------|--------|
| Architecture Decisions | R         | C  | C       | C       | I  | C      | I      |
| Feature Planning        | C         | R  | C       | C       | C  | I      | C      |
| Code Review             | A         | I  | R       | R       | I  | C      | I      |
| Testing Strategy        | C         | I  | C       | C       | R  | C      | I      |
| Deployment              | C         | I  | I       | I       | C  | R      | I      |
| UI/UX Design            | I         | C  | C       | I       | I  | I      | R      |
| Performance Monitoring  | C         | I  | C       | C       | C  | R      | I      |

R = Responsible, A = Accountable, C = Consulted, I = Informed
```

## Fase 2: Workflow di Collaborazione

### 3. Branching Strategy per Team

**Git Flow Adattato per Team**:
```bash
# Branch naming conventions
main                    # Production-ready code
develop                 # Integration branch
feature/team-name/feature-description
bugfix/team-name/bug-description
hotfix/hotfix-description
release/v1.2.3

# Examples:
feature/frontend-team/user-dashboard
feature/backend-team/payment-api
bugfix/qa-team/checkout-validation
hotfix/critical-security-patch
```

### 4. Pull Request Workflow

**PR Template per Team** (`.github/pull_request_template.md`):
```markdown
## 🔄 Pull Request Information

### Team & Assignment
- **Team**: <!-- frontend-team / backend-team / fullstack-team -->
- **Primary Reviewer**: <!-- @username -->
- **Secondary Reviewer**: <!-- @username -->
- **QA Assignee**: <!-- @qa-username -->

### Changes Description
**Type of Change**:
- [ ] 🐛 Bug fix
- [ ] ✨ New feature
- [ ] 💥 Breaking change
- [ ] 📝 Documentation update
- [ ] 🎨 UI/UX improvement
- [ ] ⚡ Performance improvement

**Summary**:
<!-- Brief description of changes -->

**Related Issue**: Closes #<!-- issue number -->

### Technical Details
**Architecture Impact**:
- [ ] No architectural changes
- [ ] Database schema changes
- [ ] API contract changes
- [ ] Configuration changes

**Testing Coverage**:
- [ ] Unit tests added/updated
- [ ] Integration tests added/updated
- [ ] E2E tests added/updated
- [ ] Manual testing completed

### Team Review Checklist

**Code Quality** (Dev Team):
- [ ] Code follows team standards
- [ ] No code smells detected
- [ ] Security best practices followed
- [ ] Performance considerations addressed

**QA Review** (QA Team):
- [ ] Test scenarios covered
- [ ] Edge cases considered
- [ ] Cross-browser compatibility checked
- [ ] Accessibility requirements met

**Design Review** (Design Team):
- [ ] UI matches design specifications
- [ ] UX patterns consistent
- [ ] Responsive design verified
- [ ] Brand guidelines followed

**DevOps Review** (DevOps Team):
- [ ] Deployment considerations reviewed
- [ ] Infrastructure requirements identified
- [ ] Monitoring/logging included
- [ ] Security scan passed

### Deployment Notes
**Environment Requirements**:
<!-- Any special deployment requirements -->

**Configuration Changes**:
<!-- Any configuration that needs to be updated -->

**Rollback Plan**:
<!-- Steps to rollback if issues occur -->

---

**Reviewer Assignment Rules**:
- Frontend changes: @frontend-team/reviewers
- Backend changes: @backend-team/reviewers
- Database changes: @backend-team/seniors + @devops-team
- UI changes: @frontend-team + @ui-designers
- Security changes: @security-team + @tech-leads
```

## Fase 3: Comunicazione e Coordinamento

### 5. Daily Standup Automation

**Standup Bot Configuration** (`.github/workflows/daily-standup.yml`):
```yaml
name: Daily Standup Reminder
on:
  schedule:
    # Monday to Friday at 9:00 AM UTC
    - cron: '0 9 * * 1-5'

jobs:
  standup_reminder:
    runs-on: ubuntu-latest
    steps:
      - name: Send Standup Reminder
        uses: actions/github-script@v6
        with:
          script: |
            const teams = {
              'frontend-team': ['charlie.dev', 'david.dev', 'emma.junior', 'frank.junior'],
              'backend-team': ['grace.senior', 'henry.dev', 'iris.junior', 'jack.dev'],
              'qa-engineers': ['kate.qa', 'lisa.qa', 'mike.qa'],
              'devops-team': ['noah.devops', 'olivia.devops']
            };
            
            for (const [team, members] of Object.entries(teams)) {
              const standupIssue = await github.rest.issues.create({
                owner: context.repo.owner,
                repo: `${team}-standup`,
                title: `Daily Standup - ${new Date().toLocaleDateString()}`,
                body: `## 🌅 Daily Standup - ${team}
                
**Team Members**: ${members.map(m => `@${m}`).join(', ')}

Please update with your daily standup information:

### Yesterday's Accomplishments
<!-- What did you complete yesterday? -->

### Today's Goals
<!-- What will you work on today? -->

### Blockers & Dependencies
<!-- Any impediments or help needed? -->

### Sprint Progress
<!-- How are we tracking against sprint goals? -->

---
**Standup Time**: 9:30 AM  
**Meeting Room**: ${team}-room  
**Duration**: 15 minutes max`,
                assignees: members,
                labels: ['standup', 'team-coordination', `team/${team}`]
              });
              
              console.log(`Created standup issue for ${team}: #${standupIssue.data.number}`);
            }
```

### 6. Team Communication Matrix

**Slack Integration Setup**:
```yaml
# .github/workflows/team-notifications.yml
name: Team Notifications
on:
  issues:
    types: [opened, assigned, closed]
  pull_request:
    types: [opened, ready_for_review, review_requested]
  pull_request_review:
    types: [submitted]

jobs:
  notify_teams:
    runs-on: ubuntu-latest
    steps:
      - name: Determine notification channel
        id: channel
        run: |
          # Determine Slack channel based on labels/team
          if [[ "${{ contains(github.event.*.labels.*.name, 'team/frontend') }}" == "true" ]]; then
            echo "channel=#frontend-team" >> $GITHUB_OUTPUT
          elif [[ "${{ contains(github.event.*.labels.*.name, 'team/backend') }}" == "true" ]]; then
            echo "channel=#backend-team" >> $GITHUB_OUTPUT
          elif [[ "${{ contains(github.event.*.labels.*.name, 'team/qa') }}" == "true" ]]; then
            echo "channel=#qa-team" >> $GITHUB_OUTPUT
          else
            echo "channel=#general-dev" >> $GITHUB_OUTPUT
          fi
      
      - name: Send Slack notification
        uses: 8398a7/action-slack@v3
        with:
          status: custom
          channel: ${{ steps.channel.outputs.channel }}
          custom_payload: |
            {
              "text": "${{ github.event_name }} notification",
              "blocks": [
                {
                  "type": "section",
                  "text": {
                    "type": "mrkdwn",
                    "text": "*${{ github.event_name }}*: ${{ github.event.repository.name }}"
                  }
                },
                {
                  "type": "section",
                  "fields": [
                    {
                      "type": "mrkdwn",
                      "text": "*Author:*\n${{ github.event.sender.login }}"
                    },
                    {
                      "type": "mrkdwn",
                      "text": "*Assignee:*\n${{ github.event.assignee.login || 'Unassigned' }}"
                    }
                  ]
                },
                {
                  "type": "actions",
                  "elements": [
                    {
                      "type": "button",
                      "text": {
                        "type": "plain_text",
                        "text": "View on GitHub"
                      },
                      "url": "${{ github.event.html_url || github.event.pull_request.html_url }}"
                    }
                  ]
                }
              ]
            }
        env:
          SLACK_WEBHOOK_URL: ${{ secrets.SLACK_WEBHOOK_URL }}
```

## Fase 4: Metriche e Performance del Team

### 7. Team Performance Dashboard

**Metrics Collection Script** (`scripts/team-metrics.js`):
```javascript
#!/usr/bin/env node
// Team Performance Metrics Collection

const { Octokit } = require('@octokit/rest');
const fs = require('fs');

class TeamMetrics {
  constructor(token, org, repo) {
    this.octokit = new Octokit({ auth: token });
    this.org = org;
    this.repo = repo;
  }

  async getTeamMetrics(teamName, since = '2024-01-01') {
    const team = await this.octokit.rest.teams.getByName({
      org: this.org,
      team_slug: teamName
    });

    const members = await this.octokit.rest.teams.listMembersInOrg({
      org: this.org,
      team_slug: teamName
    });

    const metrics = {
      team: teamName,
      memberCount: members.data.length,
      members: members.data.map(m => m.login),
      performance: {}
    };

    // Collect metrics for each member
    for (const member of members.data) {
      metrics.performance[member.login] = await this.getMemberMetrics(member.login, since);
    }

    return metrics;
  }

  async getMemberMetrics(username, since) {
    const [commits, prs, reviews, issues] = await Promise.all([
      this.getCommitActivity(username, since),
      this.getPullRequestActivity(username, since),
      this.getReviewActivity(username, since),
      this.getIssueActivity(username, since)
    ]);

    return {
      commits: commits.length,
      pullRequests: {
        opened: prs.opened.length,
        merged: prs.merged.length,
        avgReviewTime: this.calculateAvgReviewTime(prs.opened)
      },
      codeReviews: {
        given: reviews.given.length,
        received: reviews.received.length,
        avgResponseTime: this.calculateAvgResponseTime(reviews.given)
      },
      issues: {
        created: issues.created.length,
        resolved: issues.resolved.length,
        avgResolutionTime: this.calculateAvgResolutionTime(issues.resolved)
      },
      productivity: this.calculateProductivityScore({
        commits: commits.length,
        prs: prs.merged.length,
        reviews: reviews.given.length
      })
    };
  }

  async getCommitActivity(username, since) {
    const commits = await this.octokit.rest.repos.listCommits({
      owner: this.org,
      repo: this.repo,
      author: username,
      since: since
    });
    return commits.data;
  }

  async getPullRequestActivity(username, since) {
    const prs = await this.octokit.rest.pulls.list({
      owner: this.org,
      repo: this.repo,
      state: 'all',
      sort: 'created',
      direction: 'desc'
    });

    const userPrs = prs.data.filter(pr => pr.user.login === username);
    const opened = userPrs.filter(pr => new Date(pr.created_at) >= new Date(since));
    const merged = opened.filter(pr => pr.merged_at);

    return { opened, merged };
  }

  async getReviewActivity(username, since) {
    // Get reviews given by user
    const reviewsGiven = await this.octokit.rest.pulls.listReviews({
      owner: this.org,
      repo: this.repo,
      pull_number: 1 // This would need to iterate through all PRs
    });

    // Get reviews received on user's PRs
    const reviewsReceived = []; // Similar logic

    return { given: reviewsGiven.data, received: reviewsReceived };
  }

  async getIssueActivity(username, since) {
    const issues = await this.octokit.rest.issues.listForRepo({
      owner: this.org,
      repo: this.repo,
      state: 'all',
      since: since
    });

    const created = issues.data.filter(issue => issue.user.login === username);
    const resolved = created.filter(issue => issue.state === 'closed');

    return { created, resolved };
  }

  calculateProductivityScore(metrics) {
    // Weighted scoring system
    const weights = {
      commits: 1,
      prs: 3,
      reviews: 2
    };

    return (
      metrics.commits * weights.commits +
      metrics.prs * weights.prs +
      metrics.reviews * weights.reviews
    );
  }

  calculateAvgReviewTime(prs) {
    if (!prs.length) return 0;
    
    const times = prs
      .filter(pr => pr.merged_at)
      .map(pr => {
        const created = new Date(pr.created_at);
        const merged = new Date(pr.merged_at);
        return (merged - created) / (1000 * 60 * 60); // hours
      });

    return times.reduce((sum, time) => sum + time, 0) / times.length;
  }

  calculateAvgResponseTime(reviews) {
    // Similar calculation for review response time
    return 0; // Placeholder
  }

  calculateAvgResolutionTime(issues) {
    // Similar calculation for issue resolution time
    return 0; // Placeholder
  }

  async generateTeamReport() {
    const teams = ['frontend-team', 'backend-team', 'qa-engineers', 'devops-team'];
    const report = {
      generatedAt: new Date().toISOString(),
      teams: {}
    };

    for (const team of teams) {
      report.teams[team] = await this.getTeamMetrics(team);
    }

    // Generate HTML report
    const html = this.generateHTMLReport(report);
    fs.writeFileSync('team-performance-report.html', html);

    console.log('📊 Team performance report generated: team-performance-report.html');
    return report;
  }

  generateHTMLReport(data) {
    return `
<!DOCTYPE html>
<html>
<head>
    <title>Team Performance Report</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        .team { margin-bottom: 30px; border: 1px solid #ddd; padding: 20px; }
        .metrics { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; }
        .metric { background: #f5f5f5; padding: 15px; border-radius: 5px; }
        .score { font-size: 24px; font-weight: bold; color: #2ea44f; }
    </style>
</head>
<body>
    <h1>🏆 Team Performance Report</h1>
    <p>Generated: ${data.generatedAt}</p>
    
    ${Object.entries(data.teams).map(([teamName, teamData]) => `
        <div class="team">
            <h2>${teamName} (${teamData.memberCount} members)</h2>
            <div class="metrics">
                ${Object.entries(teamData.performance).map(([member, metrics]) => `
                    <div class="metric">
                        <h3>${member}</h3>
                        <div class="score">${metrics.productivity}</div>
                        <p>Productivity Score</p>
                        <ul>
                            <li>Commits: ${metrics.commits}</li>
                            <li>PRs Merged: ${metrics.pullRequests.merged}</li>
                            <li>Reviews Given: ${metrics.codeReviews.given}</li>
                        </ul>
                    </div>
                `).join('')}
            </div>
        </div>
    `).join('')}
</body>
</html>`;
  }
}

// Usage
if (require.main === module) {
  const metrics = new TeamMetrics(
    process.env.GITHUB_TOKEN,
    'ecocommerce',
    'main-app'
  );
  
  metrics.generateTeamReport().catch(console.error);
}

module.exports = TeamMetrics;
```

### 8. Automated Performance Reviews

**Monthly Team Review** (`.github/workflows/monthly-review.yml`):
```yaml
name: Monthly Team Performance Review
on:
  schedule:
    # First day of each month at 9 AM
    - cron: '0 9 1 * *'
  workflow_dispatch: # Manual trigger

jobs:
  generate_performance_report:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      
      - name: Setup Node.js
        uses: actions/setup-node@v3
        with:
          node-version: '18'
      
      - name: Install dependencies
        run: npm install @octokit/rest
      
      - name: Generate team metrics
        run: node scripts/team-metrics.js
        env:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
      
      - name: Create performance review issue
        uses: actions/github-script@v6
        with:
          script: |
            const fs = require('fs');
            const report = JSON.parse(fs.readFileSync('team-performance-report.json', 'utf8'));
            
            const issueBody = `
# 📊 Monthly Team Performance Review
**Period**: ${new Date().toLocaleDateString()}

## Team Summary
${Object.entries(report.teams).map(([team, data]) => `
### ${team}
- **Members**: ${data.memberCount}
- **Total Commits**: ${Object.values(data.performance).reduce((sum, m) => sum + m.commits, 0)}
- **Total PRs**: ${Object.values(data.performance).reduce((sum, m) => sum + m.pullRequests.merged, 0)}
- **Avg Productivity**: ${(Object.values(data.performance).reduce((sum, m) => sum + m.productivity, 0) / data.memberCount).toFixed(1)}
`).join('')}

## Action Items
- [ ] Schedule 1:1s with low-performing team members
- [ ] Recognize top performers
- [ ] Identify training needs
- [ ] Adjust workload distribution

## Next Review
Next automated review: ${new Date(Date.now() + 30*24*60*60*1000).toLocaleDateString()}
            `;
            
            await github.rest.issues.create({
              owner: context.repo.owner,
              repo: context.repo.repo,
              title: `Monthly Team Performance Review - ${new Date().toLocaleDateString()}`,
              body: issueBody,
              assignees: ['tech-lead', 'product-manager'],
              labels: ['team-management', 'monthly-review', 'performance']
            });
```

## Fase 5: Onboarding e Training

### 9. New Team Member Onboarding

**Onboarding Checklist Template**:
```markdown
# 🎯 New Team Member Onboarding Checklist

**New Member**: @username
**Team**: <!-- team-name -->
**Start Date**: <!-- date -->
**Buddy**: @buddy-username
**Manager**: @manager-username

## Week 1: Setup & Orientation

### Administrative Setup
- [ ] GitHub account added to organization
- [ ] Added to appropriate teams and repositories
- [ ] Slack workspace access granted
- [ ] Development environment setup completed
- [ ] VPN and security access configured

### Team Introduction
- [ ] Team introduction meeting completed
- [ ] 1:1 with direct manager scheduled
- [ ] Buddy system introduction
- [ ] Team communication channels joined
- [ ] Project overview presentation attended

### Technical Setup
- [ ] Development environment configured
- [ ] Local repository cloned and building
- [ ] IDE/Editor setup with team standards
- [ ] Git configuration completed
- [ ] First test commit/PR submitted

## Week 2: Learning & First Contributions

### Code Familiarization
- [ ] Codebase walkthrough with team member
- [ ] Architecture documentation reviewed
- [ ] Development workflow understood
- [ ] Code review process learned
- [ ] Testing practices explained

### First Tasks
- [ ] First bug fix assigned and completed
- [ ] Code review participation (as reviewer)
- [ ] Team standup participation
- [ ] Documentation contribution
- [ ] Tool familiarity assessment

## Week 3-4: Integration

### Project Contribution
- [ ] Feature development task assigned
- [ ] Cross-team collaboration initiated
- [ ] Process improvement suggestion made
- [ ] Knowledge sharing session attended
- [ ] Peer feedback session completed

### Milestone Completion
- [ ] 30-day review with manager
- [ ] Team integration feedback collected
- [ ] Learning plan for next quarter defined
- [ ] Long-term goals discussed
- [ ] Onboarding feedback provided

## Resources

### Documentation
- [Team Handbook](./team-handbook.md)
- [Development Guidelines](./dev-guidelines.md)
- [Code Review Standards](./code-review.md)
- [Architecture Overview](./architecture.md)

### Contacts
- **Buddy**: @buddy-username
- **Team Lead**: @team-lead-username
- **HR**: @hr-contact
- **IT Support**: @it-support

### Training Materials
- [ ] Git/GitHub Advanced Workshop
- [ ] Team Development Stack Training
- [ ] Security Best Practices Course
- [ ] Agile Methodology Overview
```

## Deliverable dell'Esercizio

### Checklist di Completamento

**Team Structure** ✅
- [ ] Organization teams created (11 teams)
- [ ] Member assignments completed
- [ ] Permission matrix implemented
- [ ] RACI matrix documented

**Workflow Implementation** ✅
- [ ] Branching strategy documented
- [ ] PR template customized for teams
- [ ] Review assignment automation
- [ ] Quality gates configured

**Communication Systems** ✅
- [ ] Daily standup automation
- [ ] Slack integration configured
- [ ] Notification routing implemented
- [ ] Escalation procedures defined

**Performance Monitoring** ✅
- [ ] Metrics collection system
- [ ] Performance dashboard
- [ ] Monthly review automation
- [ ] Individual KPI tracking

**Team Development** ✅
- [ ] Onboarding process documented
- [ ] Training curriculum defined
- [ ] Mentorship program established
- [ ] Career development paths

### Metriche di Successo

**Team Efficiency**:
```
📈 PR Review Time: <24 hours
📈 Code Quality Score: >8/10
📈 Sprint Completion Rate: >90%
📈 Team Satisfaction: >4.5/5
```

**Collaboration Metrics**:
```
🤝 Cross-team PRs: >20% of total
🤝 Knowledge Sharing Sessions: 2/month
🤝 Pair Programming Hours: >10% of dev time
🤝 Mentorship Engagement: 100% participation
```

**Performance Indicators**:
```
⚡ Deployment Frequency: Daily
⚡ Lead Time: <3 days
⚡ Mean Time to Recovery: <2 hours
⚡ Change Failure Rate: <5%
```

## Troubleshooting

### Common Team Issues

**1. Communication Gaps**
```bash
# Solution: Implement communication matrix
# Regular sync meetings between teams
# Clear escalation paths
```

**2. Code Review Bottlenecks**
```bash
# Solution: Distribute review load
# Implement time-based assignment
# Cross-train team members
```

**3. Knowledge Silos**
```bash
# Solution: Documentation culture
# Regular knowledge sharing
# Code walkthrough sessions
```

## Advanced Team Management

### AI-Powered Insights
```python
# Predictive analytics for team performance
# Automated workload balancing
# Skill gap analysis
```

### Continuous Improvement
```yaml
# Regular retrospectives
# Process optimization metrics
# Team health monitoring
```

---

**Tempo stimato**: 6-8 ore  
**Difficoltà**: Avanzato  
**Prerequisiti**: GitHub Teams, Project Management, Leadership Skills
