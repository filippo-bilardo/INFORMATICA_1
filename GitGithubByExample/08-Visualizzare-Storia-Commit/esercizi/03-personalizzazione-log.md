# Esercizio 3: Personalizzazione Avanzata Git Log

## 📋 Obiettivi
- Creare alias personalizzati per ottimizzare il workflow
- Configurare formattazioni custom per diverse situazioni
- Sviluppare script automatici per analisi repository
- Implementare dashboard di monitoraggio Git

## 📚 Prerequisiti
- Completamento esercizi precedenti
- Conoscenza di git log e formattazione
- Familiarità con configurazione Git
- Nozioni di base scripting bash

## ⏱️ Durata Stimata
60-75 minuti

---

## 🎯 Scenario

Sei il **Git Administrator** di **TechStartup Inc.**, un'azienda con 15 sviluppatori che lavorano su 3 progetti principali:
- **WebApp** (Frontend React + Backend Django)
- **MobileApp** (React Native)
- **Analytics** (Python + Machine Learning)

Il team necessita di strumenti personalizzati per:
- Monitorare la produttività degli sviluppatori
- Generare report automatici per i manager
- Identificare rapidamente problemi di qualità
- Tracciare progress verso le milestone

---

## 🔧 Task 1: Configurazione Alias Produttività

### 1.1 Alias Base per Review Giornaliera

Crea questi alias nella configurazione Git globale:

```bash
# Alias per review giornaliera
git config --global alias.today "log --since='1 day ago' --author-date-order --pretty=format:'%C(yellow)%h %C(blue)%an %C(green)%ad %C(reset)%s' --date=format:'%H:%M'"

# Alias per review settimanale con statistiche
git config --global alias.week "log --since='1 week ago' --author-date-order --stat --pretty=format:'%C(cyan)=== %ad ===%C(reset)%n%C(yellow)%h %C(blue)%an%C(reset)%n%C(green)+%C(red)-%C(reset) %s%n' --date=format:'%A %d/%m/%Y'"

# Alias per autori più attivi
git config --global alias.contributors "shortlog -sn --all --since='1 month ago'"
```

### 1.2 Alias per Analisi Qualità

```bash
# Commit senza test (potenziali problemi)
git config --global alias.risky "log --grep='test' --invert-grep --oneline --since='2 weeks ago'"

# Commit di fix rapidi (possibili debiti tecnici)
git config --global alias.hotfix "log --grep='fix\\|Fix\\|FIX' --oneline --since='1 month ago'"

# Merge commit per review
git config --global alias.merges "log --merges --pretty=format:'%C(red)%h %C(blue)%an %C(green)%ad %C(reset)%s %C(yellow)%d' --date=short"
```

### 1.3 Test degli Alias

Testa ogni alias creato e documenta l'output:

```bash
git today
git week
git contributors
git risky
git hotfix
git merges
```

**Compito**: Crea uno screenshot dell'output di ogni comando e salva in `screenshots/alias-test/`.

---

## 🔧 Task 2: Formattazioni Custom per Reports

### 2.1 Formato per Manager Report

Crea un alias `manager-report` che generi output adatto ai non-tecnici:

```bash
git config --global alias.manager-report "log --since='1 week ago' --pretty=format:'📅 %ad%n👤 Sviluppatore: %an%n📝 Attività: %s%n⏱️  Ora: %cd%n➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖%n' --date=format:'%A %d %B %Y' --date-order"
```

### 2.2 Formato per Code Review

Crea un alias `review-format` per facilitare le review:

```bash
git config --global alias.review-format "log --pretty=format:'%C(bold red)Commit: %h%C(reset)%n%C(bold blue)Autore: %an <%ae>%C(reset)%n%C(bold green)Data: %ad%C(reset)%n%C(bold yellow)Messaggio:%C(reset) %s%n%C(bold cyan)File modificati:%C(reset)%n' --stat --date=format:'%d/%m/%Y alle %H:%M'"
```

### 2.3 Dashboard Sviluppatore

Crea un alias `my-dashboard` per dashboard personale:

```bash
git config --global alias.my-dashboard "!f() { \
    echo '🚀 La Mia Dashboard Git 🚀'; \
    echo '═══════════════════════════════'; \
    echo '📈 I miei commit oggi:'; \
    git log --author=\"$(git config user.name)\" --since='1 day ago' --oneline; \
    echo; \
    echo '📊 Statistiche ultime 2 settimane:'; \
    git log --author=\"$(git config user.name)\" --since='2 weeks ago' --stat | tail -n 1; \
    echo; \
    echo '🎯 Branch attuale:'; \
    git branch --show-current; \
    echo; \
    echo '⚠️  File modificati:'; \
    git status --porcelain; \
}; f"
```

---

## 🔧 Task 3: Script Automatici di Analisi

### 3.1 Script Produttività Team

Crea il file `git-team-stats.sh`:

```bash
#!/bin/bash

echo "📊 STATISTICHE TEAM - TechStartup Inc."
echo "======================================"
echo "Periodo: $(date -d '1 week ago' '+%d/%m/%Y') - $(date '+%d/%m/%Y')"
echo

# Top contributors
echo "🏆 TOP CONTRIBUTORS (ultima settimana):"
git shortlog -sn --since="1 week ago" | head -5

echo
echo "📈 COMMIT PER GIORNO:"
for i in {6..0}; do
    date_check=$(date -d "$i days ago" '+%Y-%m-%d')
    count=$(git log --since="$date_check 00:00" --until="$date_check 23:59" --oneline | wc -l)
    day_name=$(date -d "$i days ago" '+%A')
    printf "%-10s: %s\n" "$day_name" "$(printf '█%.0s' $(seq 1 $count))"
done

echo
echo "🚨 ANALISI QUALITÀ:"
hotfixes=$(git log --grep="fix\|Fix\|FIX" --since="1 week ago" --oneline | wc -l)
total=$(git log --since="1 week ago" --oneline | wc -l)
if [ $total -gt 0 ]; then
    percentage=$((hotfixes * 100 / total))
    echo "Hotfix ratio: $percentage% ($hotfixes/$total commit)"
else
    echo "Nessun commit questa settimana"
fi

echo
echo "📁 FILE PIÙ MODIFICATI:"
git log --since="1 week ago" --name-only --pretty=format: | sort | uniq -c | sort -rn | head -5
```

### 3.2 Script Report Automatico

Crea il file `daily-report.sh`:

```bash
#!/bin/bash

REPORT_DATE=$(date '+%Y-%m-%d')
REPORT_FILE="reports/daily-report-$REPORT_DATE.md"

mkdir -p reports

cat > $REPORT_FILE << EOF
# 📊 Daily Report - $REPORT_DATE

## 🎯 Commit del Giorno
$(git log --since="1 day ago" --pretty=format:"- **%an**: %s (%h)" --date=short)

## 📈 Statistiche
- **Totale commit**: $(git log --since="1 day ago" --oneline | wc -l)
- **Sviluppatori attivi**: $(git log --since="1 day ago" --format="%an" | sort -u | wc -l)
- **File modificati**: $(git log --since="1 day ago" --name-only --pretty=format: | sort -u | wc -l)

## 🔥 Hot Files (più modificati)
$(git log --since="1 day ago" --name-only --pretty=format: | sort | uniq -c | sort -rn | head -3 | awk '{print "- " $2 " (" $1 " modifiche)"}')

## ⚠️ Alert
$(if [ $(git log --grep="TODO\|FIXME\|HACK" --since="1 day ago" --oneline | wc -l) -gt 0 ]; then echo "⚠️ Commit con TODO/FIXME trovati:"; git log --grep="TODO\|FIXME\|HACK" --since="1 day ago" --oneline; else echo "✅ Nessun TODO/FIXME nei commit di oggi"; fi)

EOF

echo "Report generato: $REPORT_FILE"
```

### 3.3 Rendere Eseguibili gli Script

```bash
chmod +x git-team-stats.sh
chmod +x daily-report.sh
```

---

## 🔧 Task 4: Dashboard Interattivo

### 4.1 Script Dashboard Completo

Crea il file `git-dashboard.sh`:

```bash
#!/bin/bash

# Colori
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

clear
echo -e "${CYAN}╔══════════════════════════════════════╗${NC}"
echo -e "${CYAN}║        🚀 GIT DASHBOARD 🚀           ║${NC}"
echo -e "${CYAN}║         TechStartup Inc.             ║${NC}"
echo -e "${CYAN}╚══════════════════════════════════════╝${NC}"
echo

while true; do
    echo -e "${YELLOW}Seleziona un'opzione:${NC}"
    echo "1. 📊 Statistiche Team"
    echo "2. 🏆 Top Contributors"
    echo "3. 📈 Activity Graph"
    echo "4. 🔍 Cerca commit"
    echo "5. 📋 Report giornaliero"
    echo "6. ⚙️  Configurazione"
    echo "0. ❌ Esci"
    echo
    read -p "Scelta: " choice

    case $choice in
        1)
            echo -e "\n${GREEN}📊 STATISTICHE TEAM${NC}"
            echo "===================="
            ./git-team-stats.sh
            ;;
        2)
            echo -e "\n${GREEN}🏆 TOP CONTRIBUTORS${NC}"
            echo "==================="
            git shortlog -sn --all | head -10
            ;;
        3)
            echo -e "\n${GREEN}📈 ACTIVITY GRAPH (ultima settimana)${NC}"
            echo "====================================="
            for i in {6..0}; do
                date_check=$(date -d "$i days ago" '+%Y-%m-%d')
                count=$(git log --since="$date_check 00:00" --until="$date_check 23:59" --oneline | wc -l)
                day_name=$(date -d "$i days ago" '+%a %d/%m')
                printf "%-10s: " "$day_name"
                for j in $(seq 1 $count); do printf "█"; done
                printf " (%d)\n" $count
            done
            ;;
        4)
            read -p "Inserisci termine di ricerca: " search_term
            echo -e "\n${GREEN}🔍 RISULTATI RICERCA: '$search_term'${NC}"
            git log --grep="$search_term" --oneline -10
            ;;
        5)
            ./daily-report.sh
            echo -e "${GREEN}✅ Report generato!${NC}"
            ;;
        6)
            echo -e "\n${GREEN}⚙️  CONFIGURAZIONE ATTUALE${NC}"
            echo "=========================="
            echo "User: $(git config user.name) <$(git config user.email)>"
            echo "Repository: $(basename $(git rev-parse --show-toplevel))"
            echo "Branch: $(git branch --show-current)"
            ;;
        0)
            echo -e "${GREEN}👋 Arrivederci!${NC}"
            exit 0
            ;;
        *)
            echo -e "${RED}❌ Opzione non valida${NC}"
            ;;
    esac
    
    echo
    read -p "Premi INVIO per continuare..."
    clear
    echo -e "${CYAN}╔══════════════════════════════════════╗${NC}"
    echo -e "${CYAN}║        🚀 GIT DASHBOARD 🚀           ║${NC}"
    echo -e "${CYAN}║         TechStartup Inc.             ║${NC}"
    echo -e "${CYAN}╚══════════════════════════════════════╝${NC}"
    echo
done
```

### 4.2 Test del Dashboard

```bash
chmod +x git-dashboard.sh
./git-dashboard.sh
```

---

## 🔧 Task 5: Configurazione Avanzata

### 5.1 Template Commit Message

Crea il file `.gitmessage`:

```
# Tipo: Breve descrizione (max 50 caratteri)
#
# Spiegazione dettagliata del cambiamento (max 72 caratteri per riga)
#
# Tipo può essere:
# feat: nuova funzionalità
# fix: correzione bug  
# docs: documentazione
# style: formattazione
# refactor: refactoring
# test: aggiunta test
# chore: task di mantenimento
#
# Issue correlate: #123
```

Configuralo:
```bash
git config --global commit.template ~/.gitmessage
```

### 5.2 Hook Pre-commit per Qualità

Crea `.git/hooks/pre-commit`:

```bash
#!/bin/bash

echo "🔍 Controllo pre-commit in corso..."

# Controlla se ci sono TODO/FIXME
if git diff --cached | grep -E "(TODO|FIXME|HACK)"; then
    echo "⚠️  ATTENZIONE: Trovati TODO/FIXME nel commit"
    read -p "Continuare comunque? (y/N): " confirm
    if [[ $confirm != "y" && $confirm != "Y" ]]; then
        echo "❌ Commit annullato"
        exit 1
    fi
fi

# Controlla dimensione commit
files_changed=$(git diff --cached --name-only | wc -l)
if [ $files_changed -gt 10 ]; then
    echo "⚠️  ATTENZIONE: Commit molto grande ($files_changed file)"
    read -p "Continuare comunque? (y/N): " confirm
    if [[ $confirm != "y" && $confirm != "Y" ]]; then
        echo "❌ Commit annullato - considera di dividere in commit più piccoli"
        exit 1
    fi
fi

echo "✅ Controlli superati!"
```

```bash
chmod +x .git/hooks/pre-commit
```

---

## 📝 Consegna

### File da Creare:
1. **Screenshots**:
   - `screenshots/alias-test/` con output di tutti gli alias
   - `screenshots/dashboard/` con il dashboard in azione

2. **Script**:
   - `git-team-stats.sh`
   - `daily-report.sh` 
   - `git-dashboard.sh`

3. **Configurazione**:
   - `.gitmessage`
   - File con lista alias configurati

4. **Report**:
   - Cartella `reports/` con almeno un daily report generato

### Test di Verifica:
1. Tutti gli alias funzionano correttamente
2. Scripts sono eseguibili e producono output
3. Dashboard interattivo risponde a tutti i comandi
4. Template commit è configurato
5. Hook pre-commit funziona

---

## 🎯 Criteri di Valutazione

| Criterio | Eccellente (9-10) | Buono (7-8) | Sufficiente (6) | Insufficiente (<6) |
|----------|-------------------|-------------|-----------------|-------------------|
| **Alias** | Tutti funzionanti + personalizzazioni | Tutti funzionanti | La maggior parte funziona | Molti non funzionano |
| **Script** | Completi + miglioramenti | Completi e funzionanti | Funzionanti con errori minori | Non funzionanti |
| **Dashboard** | Interattivo + features extra | Completamente funzionale | Funzionale di base | Non funzionale |
| **Configurazione** | Template + hook + extra | Template e hook configurati | Solo template configurato | Configurazione mancante |
| **Documentazione** | Screenshots + spiegazioni | Screenshots complete | Screenshots di base | Screenshots mancanti |

---

## 💡 Bonus Challenge

### Challenge 1: GitLab/GitHub Integration
Estendi il dashboard per mostrare:
- Issue aperte
- Pull/Merge request pending
- CI/CD status

### Challenge 2: Notifiche Automatiche
Crea script che invii notifiche quando:
- Troppi hotfix in un giorno
- Commit senza test
- Repository non aggiornato da giorni

### Challenge 3: Metriche Avanzate
Aggiungi al dashboard:
- Code churn analysis
- Commit size trends  
- Developer velocity metrics

---

## 🔗 Link Utili

### Documentazione
- [Git Aliases Documentation](https://git-scm.com/book/en/v2/Git-Basics-Git-Aliases)
- [Git Hooks Guide](https://git-scm.com/book/en/v2/Customizing-Git-Git-Hooks)
- [Pretty Formats](https://git-scm.com/docs/pretty-formats)

### Navigazione Corso
- [← Torna al Modulo](../README.md)
- [← Esercizio Precedente](02-detective-git.md)
- [Prossimo Modulo →](../../09-Branching-Concetti-Base/README.md)

---

*📚 Questo esercizio conclude il Modulo 08. Hai acquisito competenze avanzate nella personalizzazione di Git per ambienti di sviluppo professionali!*
