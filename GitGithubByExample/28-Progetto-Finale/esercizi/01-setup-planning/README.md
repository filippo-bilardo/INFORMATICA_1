# Fase 1: Setup e Planning

## 🎯 Obiettivi

Al termine di questa fase sarai in grado di:
- ✅ Configurare un repository professionale con template completo
- ✅ Implementare branch protection e team policies
- ✅ Creare project board strutturato con milestone
- ✅ Documentare planning e requirements efficacemente

## ⏱️ Durata Stimata
**2-3 ore**

## 📋 Prerequisiti
- Account GitHub configurato
- Git installato e configurato
- Team format (opzionale ma consigliato)
- Access a repository template del corso

## 🚀 Tasks da Completare

### Task 1.1: Repository Setup (30 min)

#### 🎯 Obiettivo
Creare repository GitHub professionale per il Task Manager project

#### 📝 Steps
1. **Fork Template Repository**
   ```bash
   # Navigate to course template
   https://github.com/[course-org]/task-manager-template
   
   # Click "Use this template" > "Create a new repository"
   # Name: task-manager-[team-name]
   # Description: "Collaborative Task Manager - Git Course Final Project"
   # Public repository
   ```

2. **Clone Locally**
   ```bash
   git clone https://github.com/[your-username]/task-manager-[team-name].git
   cd task-manager-[team-name]
   
   # Verify template structure
   ls -la
   ```

3. **Initial Configuration**
   ```bash
   # Set up git config (if not done globally)
   git config user.name "Your Name"
   git config user.email "your.email@example.com"
   
   # Verify remote setup
   git remote -v
   ```

#### ✅ Deliverable
- Repository creato con template structure
- Local clone configurato
- Commit history clean

### Task 1.2: Team Setup e Permissions (20 min)

#### 🎯 Obiettivo
Configurare team collaboration e access permissions

#### 📝 Steps (Se lavori in team)
1. **Invite Team Members**
   - Go to Settings > Manage access
   - Click "Invite a collaborator"
   - Add team members con "Write" permissions
   - Send invitation links

2. **Define Team Roles**
   - **Project Manager**: Milestone e issue management
   - **Lead Developer**: Code review e merge decisions
   - **Developer(s)**: Feature implementation
   - **DevOps**: CI/CD e deployment setup

3. **Communication Setup**
   - Create team Slack/Discord channel
   - Share contact information
   - Agree on meeting schedule

#### ✅ Deliverable
- Team members added con appropriate permissions
- Roles assigned e documented
- Communication channels established

### Task 1.3: Branch Protection Setup (15 min)

#### 🎯 Obiettivo
Implementare branch protection rules per quality assurance

#### 📝 Steps
1. **Navigate to Branch Settings**
   - Repository > Settings > Branches
   - Click "Add rule" for main branch

2. **Configure Protection Rules**
   ```yaml
   Branch name pattern: main
   
   ✅ Require a pull request before merging
   ✅ Require approvals: 1 (team) o 0 (solo)
   ✅ Dismiss stale PR approvals when new commits are pushed
   ✅ Require status checks to pass before merging
   ✅ Require branches to be up to date before merging
   ✅ Include administrators
   ```

3. **Additional Settings**
   ```yaml
   ✅ Allow force pushes: NO
   ✅ Allow deletions: NO
   ```

#### ✅ Deliverable
- Branch protection rules configured
- Main branch protected from direct pushes
- PR workflow enforced

### Task 1.4: Project Board Creation (30 min)

#### 🎯 Obiettivo
Creare project board per tracking progress e milestone management

#### 📝 Steps
1. **Create New Project**
   - Go to Projects tab
   - Click "New project"
   - Name: "Task Manager Development"
   - Template: "Team backlog"

2. **Setup Columns**
   ```
   📋 Backlog           - New issues e features
   🏗️ Sprint Planning   - Items for current sprint
   🚧 In Progress       - Currently being worked
   👀 In Review         - Pull requests pending review
   ✅ Done             - Completed items
   ```

3. **Create Initial Issues**
   ```markdown
   # Epic: Core Task Management
   - [ ] User can create tasks
   - [ ] User can edit tasks
   - [ ] User can delete tasks
   - [ ] User can mark tasks complete
   
   # Epic: UI/UX
   - [ ] Responsive design implementation
   - [ ] Color theme system
   - [ ] Accessibility features
   
   # Epic: Testing & Quality
   - [ ] Unit test setup
   - [ ] E2E testing framework
   - [ ] Code coverage reporting
   
   # Epic: DevOps
   - [ ] CI/CD pipeline setup
   - [ ] GitHub Pages deployment
   - [ ] Performance monitoring
   ```

4. **Link Issues to Project**
   - Add labels: `feature`, `bug`, `documentation`, `testing`
   - Assign to project board
   - Set milestone dates

#### ✅ Deliverable
- Project board configured con workflow columns
- Initial issues created e categorized
- Labels e milestone setup completed

### Task 1.5: Documentation Foundation (45 min)

#### 🎯 Obiettivo
Creare documentation foundation professionale

#### 📝 Steps
1. **Update README.md**
   ```markdown
   # Task Manager - Team Collaboration Project
   
   ## 🎯 Project Overview
   [Brief description of the task manager application]
   
   ## 🚀 Features
   - [ ] Task creation and management
   - [ ] Priority and category system
   - [ ] User-friendly interface
   - [ ] Data persistence
   - [ ] Responsive design
   
   ## 🛠️ Technology Stack
   - Frontend: HTML5, CSS3, JavaScript (ES6+)
   - Testing: Jest, Cypress
   - CI/CD: GitHub Actions
   - Deployment: GitHub Pages
   
   ## 👥 Team Members
   - [Name 1] - Role
   - [Name 2] - Role
   
   ## 🏗️ Development Setup
   [Development environment setup instructions]
   
   ## 📋 Project Status
   [Link to project board]
   ```

2. **Create CONTRIBUTING.md**
   ```markdown
   # Contributing Guidelines
   
   ## 🔄 Workflow Process
   1. Pick issue from project board
   2. Create feature branch
   3. Implement changes
   4. Submit pull request
   5. Code review process
   6. Merge to main
   
   ## 📝 Commit Convention
   ```
   [Include conventional commit format]

3. **Setup Issue Templates**
   - Create `.github/ISSUE_TEMPLATE/`
   - Add `feature_request.md`
   - Add `bug_report.md`
   - Add `task.md`

#### ✅ Deliverable
- Professional README.md aggiornato
- Contributing guidelines create
- Issue templates configurati

### Task 1.6: Sprint Planning (30 min)

#### 🎯 Obiettivo
Pianificare primo sprint di development

#### 📝 Steps
1. **Sprint 1 Planning Meeting**
   - Review all created issues
   - Estimate effort (story points o hours)
   - Select issues for Sprint 1 (1 week)
   - Move selected issues to "Sprint Planning"

2. **Task Assignment**
   - Assign issues to team members
   - Set due dates
   - Identify dependencies

3. **Sprint Goal Definition**
   ```markdown
   ## Sprint 1 Goal
   "Implement basic task CRUD operations with responsive UI"
   
   ## Sprint Scope
   - Task creation functionality
   - Task list display
   - Basic styling and responsiveness
   - Test framework setup
   ```

4. **Definition of Done**
   ```markdown
   ## Definition of Done
   - [ ] Code written and tested
   - [ ] Pull request created
   - [ ] Code review completed
   - [ ] CI checks passing
   - [ ] Documentation updated
   - [ ] Issue linked and closed
   ```

#### ✅ Deliverable
- Sprint 1 plan documented
- Tasks assigned con due dates
- Definition of Done agreed upon

## 🎯 Phase 1 Completion Checklist

Verifica che tutti i deliverables siano completati:

### Repository Setup ✅
- [ ] Repository creato da template
- [ ] Team members invited (se applicabile)
- [ ] Branch protection configurato
- [ ] Local development environment setup

### Project Management ✅
- [ ] Project board creato con workflow columns
- [ ] Initial issues created e labeled
- [ ] Sprint 1 planned con task assignment
- [ ] Milestone dates impostati

### Documentation ✅
- [ ] README.md professionale aggiornato
- [ ] CONTRIBUTING.md created
- [ ] Issue templates configurati
- [ ] Team roles documented

### Quality Assurance ✅
- [ ] Branch protection rules active
- [ ] PR workflow enforced
- [ ] Definition of Done defined
- [ ] Code review process agreed

## 🚀 Next Steps

Dopo il completamento della Fase 1:

1. **Team Sync Meeting**
   - Review completata setup
   - Address any configuration issues
   - Confirm Sprint 1 planning
   - Set daily standup schedule (se team)

2. **Begin Development**
   - Procedi con [Fase 2: Development Sprint](../02-development-sprint/)
   - Start picking up assigned issues
   - Begin feature branch workflow

3. **Continuous Communication**
   - Daily progress updates
   - Blockers identification
   - Sprint adjustment se necessario

## 📞 Help & Support

Se incontri problemi durante questa fase:

- **Repository Issues**: Check GitHub help documentation
- **Team Coordination**: Use project board comments
- **Technical Problems**: Create issue con `help wanted` label
- **Process Questions**: Reach out durante office hours

**🎉 Ottimo lavoro! Repository e team setup completati. Ready per development!**
