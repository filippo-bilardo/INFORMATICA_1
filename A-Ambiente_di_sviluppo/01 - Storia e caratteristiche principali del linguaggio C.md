### **1.1 Storia e caratteristiche principali del linguaggio C**

#### **Origini del linguaggio C**
Il linguaggio di programmazione **C** ha una lunga e affascinante storia che ha profondamente influenzato lo sviluppo del software moderno. Nato nei primi anni '70, il C è stato sviluppato da **Dennis Ritchie** presso i Bell Labs, negli Stati Uniti, come parte del progetto per lo sviluppo del sistema operativo Unix. Ritchie ha preso ispirazione da linguaggi precedenti come **B** e **BCPL**, ma ha creato un linguaggio che fosse più potente e flessibile per la gestione diretta dell'hardware e per lo sviluppo di sistemi operativi.

C ha avuto un successo rapido e diffuso, grazie alla sua efficienza e portabilità. Essendo strettamente legato all'hardware, permetteva di scrivere codice di basso livello che poteva essere facilmente trasportato su diverse piattaforme, rendendolo ideale per lo sviluppo di sistemi operativi, compilatori e applicazioni di sistema. Unix stesso è stato riscritto in C, e questo ha contribuito enormemente alla sua diffusione. Nel 1978, Brian Kernighan e Dennis Ritchie pubblicarono il libro "The C Programming Language", che divenne il testo di riferimento per il linguaggio e consolidò il suo utilizzo nel mondo accademico e industriale.

Negli anni '80, il linguaggio C è stato standardizzato dall'ANSI, dando vita allo standard **ANSI C** (C89 o C90), che ha definito una versione ufficiale del linguaggio. Questa standardizzazione ha assicurato che il C rimanesse compatibile tra diverse implementazioni e piattaforme, consolidandone il ruolo fondamentale nello sviluppo di software di sistema.

Parallelamente allo sviluppo del C, a partire dalla fine degli anni '70, un altro importante passo evolutivo nel mondo della programmazione stava prendendo forma con **C++**. Nato dall'ingegno di **Bjarne Stroustrup**, C++ inizialmente si chiamava "C with Classes" e si proponeva di estendere C con nuove funzionalità orientate agli oggetti. Stroustrup voleva mantenere la potenza e l'efficienza del C, aggiungendo però meccanismi per l'astrazione e la gestione più strutturata e modulare del codice, come l'incapsulamento, l'ereditarietà e il polimorfismo.

C++ è diventato rapidamente popolare negli anni '80 e '90, poiché ha permesso agli sviluppatori di scrivere codice complesso mantenendo le prestazioni elevate tipiche del C, ma con una maggiore capacità di riutilizzo e manutenzione. Una delle caratteristiche più apprezzate era la possibilità di combinare programmazione procedurale e programmazione orientata agli oggetti nello stesso linguaggio. Nel 1998, il C++ è stato standardizzato dall'ISO, definendo ufficialmente le caratteristiche del linguaggio in quello che è noto come **C++98**.

Da quel momento in poi, sia C che C++ hanno continuato a evolversi. Per quanto riguarda C, lo standard **C99**, pubblicato nel 1999, ha introdotto diverse funzionalità moderne, come l'inizializzazione designata, i tipi di dati complessi e le funzioni inline, mantenendo però l'essenza del linguaggio come uno strumento potente per la programmazione di basso livello. C ha continuato ad essere utilizzato principalmente in ambiti come sistemi embedded, driver di dispositivo, sistemi operativi e altre applicazioni dove le risorse sono limitate e l'efficienza è cruciale.

Nel frattempo, C++ ha continuato ad aggiungere caratteristiche che ne hanno esteso le capacità e lo hanno mantenuto rilevante nel panorama della programmazione. **C++11**, pubblicato nel 2011, è stato una delle revisioni più significative del linguaggio, introducendo funzionalità come le lambda expressions, il tipo `auto`, i thread, e una gestione migliorata della memoria grazie al **move semantics**. Questo aggiornamento ha reso C++ molto più adatto allo sviluppo di applicazioni moderne e ha semplificato alcuni aspetti del linguaggio che erano considerati complessi o macchinosi.

Negli anni successivi, altre revisioni come **C++14**, **C++17** e **C++20** hanno continuato ad arricchire il linguaggio, introducendo nuovi paradigmi e migliorando la sicurezza e la leggibilità del codice. C++20, in particolare, ha introdotto concetti avanzati come i **concetti generici** e le **coroutine**, che permettono una programmazione asincrona più efficiente e modulare.

Oggi, C e C++ sono entrambi considerati linguaggi chiave per lo sviluppo di software critico e ad alte prestazioni. C rimane un pilastro per lo sviluppo di sistemi embedded e applicazioni dove il controllo dell'hardware è essenziale, mentre C++ è spesso utilizzato per grandi progetti software che richiedono un'alta efficienza ma anche la capacità di gestire una complessità elevata, come motori di gioco, simulazioni scientifiche e applicazioni finanziarie. Entrambi i linguaggi continuano a essere aggiornati e migliorati, rimanendo fondamentali nel mondo dello sviluppo software.

#### **Caratteristiche principali del linguaggio C**
Il linguaggio C è noto per le sue caratteristiche che lo hanno reso uno dei linguaggi di programmazione più influenti e utilizzati.

---

### **1. Strutturato e modulare**
- **C supporta la programmazione strutturata**, che incoraggia l'uso di funzioni per suddividere i programmi in moduli più piccoli e leggibili.
- Questo paradigma facilita la **manutenzione**, il **debug** e il **riutilizzo del codice**.

**Esempio**:
```c
#include <stdio.h>

void saluta() {
    printf("Ciao, Mondo!\n");
}

int main() {
    saluta();
    return 0;
}
```

---

### **2. Portabilità**
- Uno degli obiettivi principali di C era creare codice che potesse essere facilmente compilato su sistemi diversi.
- Grazie alla standardizzazione, i programmi scritti in C possono essere eseguiti su una vasta gamma di architetture hardware con modifiche minime.

---

### **3. Controllo di basso livello**
- Il C fornisce un controllo diretto sull'hardware del computer, permettendo operazioni a livello di bit e l'uso di puntatori.
- Questa capacità lo rende ideale per applicazioni di **sistema operativo**, **driver di dispositivo** e altri software che necessitano di interagire direttamente con l'hardware.

**Esempio: Accesso alla memoria con puntatori**
```c
#include <stdio.h>

int main() {
    int x = 10;
    int *ptr = &x;

    printf("Valore: %d, Indirizzo: %p\n", *ptr, ptr);
    return 0;
}
```

---

### **4. Linguaggio compilato**
- I programmi scritti in C devono essere compilati prima di essere eseguiti.
- Il **compilatore** traduce il codice sorgente in un linguaggio macchina altamente ottimizzato, garantendo alte prestazioni.

---

### **5. Librerie standard**
- Il C offre un'ampia gamma di librerie standard che facilitano lo sviluppo di applicazioni.
- Librerie come `<stdio.h>` (per input/output), `<stdlib.h>` (per funzioni di utilità generale) e `<math.h>` (per calcoli matematici) sono esempi delle funzionalità disponibili.

**Esempio di libreria standard (`<stdio.h>`):**
```c
#include <stdio.h>

int main() {
    printf("Questo è un esempio di output.\n");
    return 0;
}
```

---

### **6. Estensibilità**
- I programmatori possono estendere le funzionalità del linguaggio creando librerie personalizzate e utilizzandole nei programmi.

---

### **7. Efficiente e veloce**
- Grazie alla sua vicinanza all'hardware, il C produce codice altamente ottimizzato, che lo rende adatto per applicazioni che richiedono prestazioni elevate, come motori di giochi e applicazioni scientifiche.

---

### **8. Uso diffuso**
- C è ancora oggi uno dei linguaggi più utilizzati, non solo per applicazioni di sistema, ma anche per programmare hardware embedded, microcontrollori e sistemi operativi.

---

#### **Il linguaggio C moderno**
1. **C ANSI/ISO (1989/1990):**
   - La standardizzazione del linguaggio C è iniziata con l'introduzione di **ANSI C (C89)** nel 1989 e **ISO C (C90)** nel 1990.
   - Ha stabilito un insieme standard di regole e funzioni per rendere il C portabile e uniforme.

2. **Versioni successive:**
   - **C99 (1999):** Introduzione di nuove funzionalità come tipi di dati `long long`, variabili dichiarate in qualsiasi punto del codice, e il supporto per i commenti a doppio slash (`//`).
   - **C11 (2011):** Miglioramenti per la concorrenza, Unicode e gestione della memoria.
   - **C17 (2017):** Miglioramenti minori e bug fix.
   - **C23 (2023):** Introduzione di nuove funzionalità, tra cui supporto migliorato per la sicurezza e aggiornamenti della sintassi.

---

### **Importanza del linguaggio C**
1. **Base di molti linguaggi moderni:**
   - Il C è alla base di linguaggi come C++, Java, C#, e molti altri, che ne ereditano la sintassi e i concetti fondamentali.
2. **Adatto a progetti di sistema e embedded:**
   - La sua efficienza e controllo lo rendono ideale per la programmazione di sistemi operativi (come UNIX e Linux), dispositivi embedded e applicazioni critiche.
3. **Ecosistema consolidato:**
   - Grazie alla sua lunga storia, il C ha una vasta comunità, una documentazione completa e risorse per l'apprendimento.

---

### **Conclusione**
Il linguaggio C ha trasformato il panorama della programmazione grazie alla sua semplicità, efficienza e portabilità. Nonostante l'emergere di linguaggi moderni, rimane un pilastro fondamentale dell'informatica, essenziale per comprendere i concetti di programmazione e per lo sviluppo di software di sistema.