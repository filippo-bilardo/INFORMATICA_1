# Sprint Planning Guide

## Metodologia Agile per il Progetto

### 1. Sprint Structure
```
Sprint Duration: 2 settimane (10 giorni lavorativi)
Sprint Planning: 2 ore
Daily Standup: 15 minuti
Sprint Review: 1 ora
Sprint Retrospective: 1 ora
```

### 2. Sprint Planning Process

#### Fase 1: Sprint Goal Definition (30 min)
```markdown
**Sprint Goal Template:**
"In questo sprint, consegneremo [funzionalità principale] che permetterà agli utenti di [valore business] migliorando [metrica specifica] del [X%]."

**Esempio:**
"In questo sprint, consegneremo il sistema di autenticazione che permetterà agli utenti di accedere in modo sicuro migliorando la security del 100% e riducendo i support tickets del 80%."
```

#### Fase 2: Backlog Refinement (60 min)
```javascript
// User Story Template
const userStory = {
    id: "US-001",
    title: "Login utente",
    description: "Come utente, voglio poter accedere al sistema con email e password, così da accedere alle funzionalità personalizzate",
    acceptanceCriteria: [
        "Dato che sono un utente registrato",
        "Quando inserisco email e password corrette",
        "Allora vengo reindirizzato alla dashboard",
        "E vedo il messaggio di benvenuto personalizzato"
    ],
    storyPoints: 5,
    priority: "High",
    dependencies: ["US-000 - Registrazione utente"],
    definition_of_done: [
        "Codice sviluppato e testato",
        "Unit test coverage > 80%",
        "Code review completato",
        "Documentazione aggiornata",
        "Deploy in staging completato"
    ]
};
```

#### Fase 3: Task Breakdown (30 min)
```markdown
**US-001: Login utente**
- [ ] Setup database schema per utenti (2h)
- [ ] Implementare API login endpoint (4h)
- [ ] Creare form di login frontend (3h)
- [ ] Implementare validazione client-side (2h)
- [ ] Aggiungere gestione errori (2h)
- [ ] Scrivere unit tests (3h)
- [ ] Scrivere integration tests (2h)
- [ ] Code review e refactoring (2h)
- [ ] Documentazione API (1h)
- [ ] Deploy e testing in staging (1h)

**Totale stimato: 22 ore**
```

## Sprint Backlog Management

### 1. Story Points Estimation
```javascript
// Fibonacci sequence per story points
const fibonacciScale = [1, 2, 3, 5, 8, 13, 21];

// Guida estimation
const estimationGuide = {
    1: "Molto semplice - poche ore",
    2: "Semplice - mezza giornata",
    3: "Medio-semplice - 1 giornata",
    5: "Medio - 2-3 giorni",
    8: "Complesso - 1 settimana",
    13: "Molto complesso - > 1 settimana",
    21: "Epico - da scomporre"
};

// Planning Poker
function planningPoker(team, story) {
    const votes = team.map(member => member.estimate(story));
    
    if (Math.max(...votes) - Math.min(...votes) <= 2) {
        return Math.round(votes.reduce((a, b) => a + b) / votes.length);
    } else {
        // Discussion needed
        return discussAndRevote(team, story, votes);
    }
}
```

### 2. Capacity Planning
```javascript
// Team capacity calculation
function calculateSprintCapacity(team, sprintDays = 10) {
    return team.reduce((total, member) => {
        const availability = member.availability; // 0.8 = 80% available
        const dailyCapacity = member.dailyHours; // 6 hours productive per day
        const vacationDays = member.vacationDays || 0;
        
        const memberCapacity = (sprintDays - vacationDays) * dailyCapacity * availability;
        return total + memberCapacity;
    }, 0);
}

// Esempio team
const team = [
    { name: "Alice", dailyHours: 6, availability: 0.8, vacationDays: 0 },
    { name: "Bob", dailyHours: 6, availability: 0.9, vacationDays: 1 },
    { name: "Charlie", dailyHours: 5, availability: 0.7, vacationDays: 0 }
];

const totalCapacity = calculateSprintCapacity(team);
// Alice: 10 * 6 * 0.8 = 48h
// Bob: 9 * 6 * 0.9 = 48.6h  
// Charlie: 10 * 5 * 0.7 = 35h
// Total: ~132 hours
```

## Daily Standup Framework

### 1. Three Questions Format
```markdown
**Standup Template per ogni membro:**

1. **Cosa ho fatto ieri?**
   - Completato task X (US-001)
   - Risolto bug Y
   - Partecipato a code review Z

2. **Cosa farò oggi?**
   - Continuerò task A (US-002)
   - Inizierò implementazione B
   - Code review per task C

3. **Ci sono impedimenti?**
   - Bloccato su API integration (need help from backend team)
   - Waiting for design approval
   - Environment issues on staging
```

### 2. Impediment Tracking
```javascript
// Impediment tracking system
const impediments = [
    {
        id: "IMP-001",
        description: "API documentation incomplete",
        reporter: "Alice",
        dateReported: "2024-01-15",
        status: "Open",
        owner: "Bob",
        impact: "High",
        resolution: null
    }
];

// Impediment categories
const impedimentTypes = {
    TECHNICAL: "Technical debt, bugs, infrastructure",
    DEPENDENCIES: "Waiting for other teams, external services", 
    RESOURCES: "Missing tools, access, information",
    PROCESS: "Unclear requirements, approval delays"
};
```

## Sprint Metrics & Tracking

### 1. Burndown Chart
```javascript
// Sprint burndown data
function generateBurndownData(sprint) {
    const idealBurndown = [];
    const actualBurndown = [];
    
    const totalStoryPoints = sprint.stories.reduce((sum, story) => sum + story.points, 0);
    const sprintDays = sprint.duration;
    
    // Ideal burndown (linear)
    for (let day = 0; day <= sprintDays; day++) {
        const remaining = totalStoryPoints - (totalStoryPoints * day / sprintDays);
        idealBurndown.push({ day, remaining });
    }
    
    // Actual burndown (basato su completion)
    let remainingPoints = totalStoryPoints;
    for (let day = 0; day <= sprintDays; day++) {
        const completedToday = getCompletedStoryPoints(sprint, day);
        remainingPoints -= completedToday;
        actualBurndown.push({ day, remaining: remainingPoints });
    }
    
    return { ideal: idealBurndown, actual: actualBurndown };
}
```

### 2. Velocity Tracking
```javascript
// Velocity calculation
function calculateVelocity(completedSprints) {
    const velocities = completedSprints.map(sprint => 
        sprint.stories
            .filter(story => story.status === 'Done')
            .reduce((sum, story) => sum + story.points, 0)
    );
    
    return {
        current: velocities[velocities.length - 1],
        average: velocities.reduce((a, b) => a + b) / velocities.length,
        trend: calculateTrend(velocities)
    };
}
```

## Sprint Events Templates

### 1. Sprint Review Agenda
```markdown
**Sprint Review - Sprint X**
*Durata: 1 ora*

**Agenda:**
1. Sprint Goal Recap (5 min)
2. Demo delle funzionalità completate (30 min)
   - US-001: Login system
   - US-002: User dashboard
   - US-003: Profile management
3. Metriche sprint (10 min)
   - Velocity: X story points
   - Completion rate: Y%
   - Bug count: Z
4. Feedback stakeholders (10 min)
5. Next sprint preview (5 min)

**Partecipanti:**
- Development Team
- Product Owner
- Scrum Master
- Key Stakeholders
```

### 2. Sprint Retrospective Format
```markdown
**Sprint Retrospective - Sprint X**
*Durata: 1 ora*

**Formato: Mad, Sad, Glad**

**Mad (Cosa ci ha frustrato):**
- [ ] Deploy process troppo lento
- [ ] Requirements poco chiari
- [ ] Interruzioni frequenti

**Sad (Cosa non è andato bene):**
- [ ] Non abbiamo raggiunto il sprint goal
- [ ] Bug quality più alta del previsto
- [ ] Communication gaps

**Glad (Cosa è andato bene):**
- [ ] Buona collaborazione team
- [ ] Code quality migliorata
- [ ] User feedback positivo

**Action Items:**
1. Automatizzare deploy process (Owner: Bob, Due: Next sprint)
2. Weekly requirements review (Owner: Alice, Due: Ongoing)
3. Focus time blocks daily (Owner: Team, Due: Tomorrow)
```

## Tools per Sprint Management

### 1. Jira Configuration
```javascript
// Jira board configuration
const sprintBoardConfig = {
    columns: [
        { name: "To Do", status: ["Open", "Reopened"] },
        { name: "In Progress", status: ["In Progress"] },
        { name: "Code Review", status: ["In Review"] },
        { name: "Testing", status: ["Testing", "QA"] },
        { name: "Done", status: ["Resolved", "Closed"] }
    ],
    swimlanes: "Stories",
    quickFilters: [
        "Current Sprint",
        "My Issues", 
        "Bugs",
        "Blocked"
    ]
};
```

### 2. GitHub Integration
```yaml
# .github/workflows/sprint-automation.yml
name: Sprint Automation
on:
  issues:
    types: [opened, closed]
  pull_request:
    types: [opened, merged]

jobs:
  update-sprint:
    runs-on: ubuntu-latest
    steps:
      - name: Update Sprint Board
        uses: actions/github-script@v6
        with:
          script: |
            // Automatically move cards based on PR status
            if (context.eventName === 'pull_request' && context.payload.action === 'opened') {
              // Move to "In Review"
            }
            if (context.eventName === 'pull_request' && context.payload.action === 'merged') {
              // Move to "Done"
            }
```

Questa guida fornisce un framework completo per la gestione degli sprint nel progetto finale, dalla pianificazione alla retrospettiva.
