# Fase 2: Development Sprint

## 🎯 Obiettivi

Al termine di questa fase sarai in grado di:
- ✅ Implementare features usando Git Flow workflow
- ✅ Gestire Pull Request process con code review efficaci
- ✅ Risolvere merge conflicts in team environment
- ✅ Mantenere code quality con automated testing
- ✅ Coordinare development in parallel branches

## ⏱️ Durata Stimata
**4-6 ore** (distribuito in 1 settimana)

## 📋 Prerequisiti
- Fase 1 completata con repository setup
- Team coordination stabilita
- Sprint 1 planning completed
- Development environment ready

## 🚀 Tasks da Completare

### Task 2.1: Feature Branch Workflow (60 min)

#### 🎯 Obiettivo
Implementare first feature usando proper Git Flow workflow

#### 📝 Steps
1. **Pick Sprint Issue**
   ```bash
   # From project board, select assigned issue
   # Example: "User can create tasks" (#3)
   ```

2. **Create Feature Branch**
   ```bash
   # Update main branch
   git checkout main
   git pull origin main
   
   # Create feature branch
   git checkout -b feature/task-creation-#3
   
   # Verify branch
   git branch
   ```

3. **Implement Feature**
   ```javascript
   // Example: Basic task creation functionality
   // File: js/taskManager.js
   class TaskManager {
       constructor() {
           this.tasks = [];
           this.nextId = 1;
       }
   
       createTask(title, description = '') {
           const task = {
               id: this.nextId++,
               title: title,
               description: description,
               completed: false,
               createdAt: new Date().toISOString()
           };
           this.tasks.push(task);
           return task;
       }
   }
   ```

4. **Atomic Commits**
   ```bash
   # Stage changes
   git add js/taskManager.js
   
   # Commit with conventional format
   git commit -m "feat: add basic task creation functionality
   
   - Implement TaskManager class
   - Add createTask method with validation
   - Include timestamp and unique ID generation
   
   Closes #3"
   
   # Continue development with more commits
   git add css/styles.css
   git commit -m "style: add task creation form styling"
   
   git add index.html
   git commit -m "feat: add task creation UI form"
   ```

5. **Push Feature Branch**
   ```bash
   # Push to remote
   git push -u origin feature/task-creation-#3
   ```

#### ✅ Deliverable
- Feature branch created con descriptive naming
- Multiple atomic commits con clear messages
- Working feature implementation
- Branch pushed to remote repository

### Task 2.2: Pull Request Creation (30 min)

#### 🎯 Obiettivo
Creare comprehensive Pull Request con proper documentation

#### 📝 Steps
1. **Create Pull Request**
   - Navigate to GitHub repository
   - Click "Compare & pull request"
   - Base: `main` ← Compare: `feature/task-creation-#3`

2. **PR Title e Description**
   ```markdown
   ## 🎯 Feature: Task Creation Implementation
   
   ### 📋 Description
   Implements basic task creation functionality allowing users to create new tasks with title and description.
   
   ### 🔄 Changes Made
   - ✅ TaskManager class implementation
   - ✅ Task creation form UI
   - ✅ Form validation and error handling
   - ✅ CSS styling for new components
   
   ### 🧪 Testing
   - [ ] Manual testing completed
   - [ ] Form validation tested
   - [ ] Error cases handled
   - [ ] Cross-browser compatibility checked
   
   ### 📸 Screenshots
   [Include before/after screenshots]
   
   ### 🔗 Related Issues
   Closes #3
   
   ### 👀 Review Checklist
   - [ ] Code follows project conventions
   - [ ] No console errors
   - [ ] Responsive design maintained
   - [ ] Comments added where needed
   ```

3. **Add Reviewers**
   - Assign team members as reviewers
   - Add appropriate labels (`feature`, `ready-for-review`)
   - Link to project board

4. **Self-Review**
   - Review own changes line by line
   - Add inline comments dove necessario
   - Verify all files included

#### ✅ Deliverable
- Comprehensive PR created con detailed description
- Reviewers assigned e labels added
- Self-review completed con comments

### Task 2.3: Code Review Process (45 min)

#### 🎯 Obiettivo
Eseguire e ricevere constructive code review

#### 📝 Steps (As Reviewer)
1. **Review Code Changes**
   ```markdown
   # Example Review Comments
   
   ## Positive Feedback
   > Great implementation of the TaskManager class! 
   > The atomic commit structure makes it easy to follow your changes.
   
   ## Suggestions
   > Consider adding input validation for empty titles:
   > ```javascript
   > if (!title || title.trim() === '') {
   >     throw new Error('Task title is required');
   > }
   > ```
   
   ## Questions
   > Should we add a maximum length for task descriptions?
   > What happens if localStorage is not available?
   ```

2. **Test Changes Locally**
   ```bash
   # Fetch PR branch
   git fetch origin
   git checkout feature/task-creation-#3
   
   # Test functionality
   npm install  # if packages needed
   # Open index.html and test manually
   
   # Run any automated tests
   npm test
   ```

3. **Provide Constructive Feedback**
   - **Approval**: Clear approval con positive comments
   - **Request Changes**: Specific actionable feedback
   - **Comments**: Questions o suggestions senza blocking

#### 📝 Steps (As Author)
1. **Respond to Feedback**
   ```bash
   # Address review comments
   git checkout feature/task-creation-#3
   
   # Make requested changes
   # Edit files based on feedback
   
   # Commit updates
   git add .
   git commit -m "refactor: add input validation per review feedback"
   
   # Push updates
   git push origin feature/task-creation-#3
   ```

2. **Re-request Review**
   - Respond to comments explaining changes
   - Re-request review from team members
   - Mark conversations as resolved

#### ✅ Deliverable
- Constructive code review provided/received
- Review feedback addressed con additional commits
- All conversations resolved

### Task 2.4: Merge e Cleanup (15 min)

#### 🎯 Obiettivo
Complete PR merge process e cleanup branches

#### 📝 Steps
1. **Final Review Check**
   ```markdown
   ✅ All review comments addressed
   ✅ CI checks passing (if configured)
   ✅ Branch up to date with main
   ✅ No merge conflicts
   ✅ Issue linked properly
   ```

2. **Merge Pull Request**
   - Use "Squash and merge" per clean history
   - Ensure commit message is clear
   - Verify issue closes automatically

3. **Local Cleanup**
   ```bash
   # Switch to main
   git checkout main
   
   # Pull latest changes
   git pull origin main
   
   # Delete local feature branch
   git branch -d feature/task-creation-#3
   
   # Delete remote branch (if not auto-deleted)
   git push origin --delete feature/task-creation-#3
   ```

4. **Update Project Board**
   - Verify issue moved to "Done"
   - Update Sprint progress
   - Pick next issue

#### ✅ Deliverable
- PR successfully merged con clean commit message
- Feature branch cleaned up locally e remotely
- Project board updated
- Ready per next feature

### Task 2.5: Parallel Development (90 min)

#### 🎯 Obiettivo
Simulare parallel development con multiple feature branches

#### 📝 Steps
1. **Multiple Team Members Start Features**
   ```bash
   # Member 1: Task editing feature
   git checkout main
   git pull origin main
   git checkout -b feature/task-editing-#4
   
   # Member 2: Task deletion feature  
   git checkout main
   git pull origin main
   git checkout -b feature/task-deletion-#5
   
   # Member 3: Task filtering
   git checkout main
   git pull origin main
   git checkout -b feature/task-filtering-#6
   ```

2. **Implement Features Independently**
   - Each member works on separate functionality
   - Regular commits con descriptive messages
   - Test functionality independently

3. **Handle Merge Conflicts**
   ```bash
   # When PRs conflict, resolve systematically
   git checkout feature/task-editing-#4
   git rebase main  # or git merge main
   
   # Resolve conflicts in files
   # Edit conflicted files manually
   git add resolved-file.js
   git rebase --continue
   
   # Push resolved branch
   git push --force-with-lease origin feature/task-editing-#4
   ```

4. **Coordinate Integration**
   - Stagger PR merges to avoid conflicts
   - Communicate changes that might affect others
   - Update documentation as features merge

#### ✅ Deliverable
- Multiple features developed in parallel
- Merge conflicts resolved successfully
- Team coordination maintained
- All features integrated cleanly

### Task 2.6: CI/CD Pipeline Setup (60 min)

#### 🎯 Obiettivo
Implementare automated testing e quality checks

#### 📝 Steps
1. **Create GitHub Actions Workflow**
   ```yaml
   # .github/workflows/ci.yml
   name: CI Pipeline
   
   on:
     push:
       branches: [ main ]
     pull_request:
       branches: [ main ]
   
   jobs:
     test:
       runs-on: ubuntu-latest
       
       steps:
       - uses: actions/checkout@v3
       
       - name: Setup Node.js
         uses: actions/setup-node@v3
         with:
           node-version: '16'
           cache: 'npm'
       
       - name: Install dependencies
         run: npm ci
       
       - name: Run tests
         run: npm test
       
       - name: Run linting
         run: npm run lint
       
       - name: Check code coverage
         run: npm run coverage
   
     build:
       runs-on: ubuntu-latest
       needs: test
       
       steps:
       - uses: actions/checkout@v3
       
       - name: Build application
         run: |
           npm ci
           npm run build
       
       - name: Upload build artifacts
         uses: actions/upload-artifact@v3
         with:
           name: build-files
           path: dist/
   ```

2. **Setup Testing Framework**
   ```javascript
   // tests/taskManager.test.js
   const TaskManager = require('../js/taskManager');
   
   describe('TaskManager', () => {
       let taskManager;
       
       beforeEach(() => {
           taskManager = new TaskManager();
       });
       
       test('should create a new task', () => {
           const task = taskManager.createTask('Test Task', 'Description');
           
           expect(task.title).toBe('Test Task');
           expect(task.description).toBe('Description');
           expect(task.completed).toBe(false);
           expect(task.id).toBe(1);
       });
       
       test('should increment task IDs', () => {
           const task1 = taskManager.createTask('Task 1');
           const task2 = taskManager.createTask('Task 2');
           
           expect(task2.id).toBe(task1.id + 1);
       });
   });
   ```

3. **Configure Package.json Scripts**
   ```json
   {
     "scripts": {
       "test": "jest",
       "test:watch": "jest --watch",
       "coverage": "jest --coverage",
       "lint": "eslint js/ tests/",
       "lint:fix": "eslint js/ tests/ --fix",
       "build": "webpack --mode production"
     }
   }
   ```

4. **Test CI Pipeline**
   ```bash
   # Commit CI configuration
   git add .github/workflows/ci.yml
   git add package.json
   git add tests/
   git commit -m "ci: add automated testing pipeline"
   
   # Push and verify actions run
   git push origin main
   ```

#### ✅ Deliverable
- GitHub Actions workflow configured
- Automated tests running on PR/push
- Code quality checks enforced
- Build process automated

## 🎯 Phase 2 Completion Checklist

Verifica che tutti i deliverables siano completati:

### Git Workflow Mastery ✅
- [ ] Multiple feature branches created e merged
- [ ] Atomic commits con conventional messages
- [ ] Clean commit history maintained
- [ ] Branch cleanup performed consistently

### Pull Request Excellence ✅
- [ ] Comprehensive PR descriptions written
- [ ] Code review process executed effectively
- [ ] Review feedback addressed promptly
- [ ] Merge conflicts resolved successfully

### Team Collaboration ✅
- [ ] Parallel development coordinated
- [ ] Communication maintained throughout
- [ ] Issues linked e tracked properly
- [ ] Project board kept updated

### Quality Assurance ✅
- [ ] CI/CD pipeline configured e working
- [ ] Automated tests written e passing
- [ ] Code quality standards maintained
- [ ] Documentation updated with changes

### Sprint Delivery ✅
- [ ] Sprint 1 features completed
- [ ] Sprint goal achieved
- [ ] Definition of Done met per feature
- [ ] Ready per Sprint 2 planning

## 🚀 Next Steps

Dopo il completamento della Fase 2:

1. **Sprint Review Meeting**
   - Demo completed features to stakeholders
   - Collect feedback on implementations
   - Document lessons learned

2. **Sprint Retrospective**
   - What went well in the development process?
   - What could be improved for next sprint?
   - Action items per process improvement

3. **Sprint 2 Planning**
   - Plan next set of features
   - Apply lessons learned from Sprint 1
   - Adjust timeline se necessario

4. **Continue Development**
   - Procedi con additional features
   - Maintain quality standards established
   - Prepare per final release

**Ready per [Fase 3: Release e Deployment](../03-release-deployment/)**

## 📊 Sprint Metrics

Track your progress con questi metrics:

### Development Velocity
- **Stories Completed**: ___/___
- **Story Points Delivered**: ___/___
- **Average Cycle Time**: ___ days per feature

### Code Quality
- **Test Coverage**: ___%
- **PR Review Time**: ___ hours average
- **Merge Conflicts**: ___ resolved successfully

### Team Collaboration
- **PR Conversations**: ___ constructive exchanges
- **Issues Created/Closed**: ___/___
- **Team Communication**: Daily standups maintained

**🎉 Excellent development sprint! Team workflow established successfully!**
