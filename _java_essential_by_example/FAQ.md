# FAQ - Domande Frequenti

## 🤔 **Domande Generali**

### **Q: Quale versione di Java dovrei usare?**
**A:** Consigliamo Java 8 LTS o superiore. Le versioni LTS (Long Term Support) più recenti sono Java 11, 17, e 21. Per questo corso, Java 8+ è perfetto.

### **Q: Quanto tempo serve per completare tutto il libro?**
**A:** Dipende dal tuo livello:
- **Principiante completo:** 60-80 ore
- **Con esperienza base:** 40-50 ore  
- **Ripasso/Consultazione:** 20-30 ore

### **Q: Posso saltare alcuni moduli?**
**A:** Ogni modulo ha una sezione "Prerequisiti". Se hai già esperienza, puoi saltare ai moduli di interesse, ma assicurati di avere le conoscenze necessarie.

---

## 💻 **Problemi Tecnici**

### **Q: "java" comando non riconosciuto**
**A:** Verifica che:
1. Java sia installato correttamente
2. JAVA_HOME sia configurato
3. La directory bin di Java sia nel PATH
4. Riavvia il terminale dopo le modifiche

### **Q: L'IDE non trova il JDK**
**A:** Nell'IDE:
1. Vai in Settings/Preferences
2. Cerca "SDK" o "JDK"  
3. Configura il percorso corretto (es: `/usr/lib/jvm/java-11-openjdk`)

### **Q: Errore "Could not find or load main class"**
**A:** Verifica che:
1. Il nome della classe sia identico al nome del file
2. Stai eseguendo dalla directory corretta
3. Il file .class esista (compila prima con javac)

---

## 📚 **Contenuti e Studio**

### **Q: Gli esempi non funzionano nel mio ambiente**
**A:** Assicurati di:
1. Copiare tutto il codice inclusi gli import
2. Usare il nome file corretto
3. Verificare che la versione Java supporti le funzionalità usate

### **Q: Come posso esercitarmi di più?**
**A:** Suggerimenti:
1. Modifica gli esempi esistenti
2. Visita [Codewars](https://www.codewars.com) per esercizi extra
3. Prova [LeetCode](https://leetcode.com) per algoritmi
4. Crea progetti personali basati sui concetti appresi

### **Q: I quiz sono troppo difficili**
**A:** 
1. Rileggi la teoria del modulo
2. Studia gli esempi commentati
3. I quiz testano comprensione, non memorizzazione
4. Non c'è fretta - l'importante è capire i concetti

---

## 🛠️ **IDE e Strumenti**

### **Q: Quale IDE consigliate per principianti?**
**A:** **IntelliJ IDEA Community** è perfetto perché:
- Gratuito e completo
- Ottimo supporto Java
- Debugging integrato
- Suggerimenti automatici
- Gestione progetti semplice

### **Q: Posso usare un editor di testo semplice?**
**A:** Sì, ma un IDE ti aiuta molto con:
- Autocompletamento
- Rilevazione errori
- Debugging visuale
- Gestione progetti
- Refactoring automatico

---

## 🎯 **Apprendimento e Metodo**

### **Q: Come organizzo lo studio?**
**A:** Approccio consigliato:
1. **Teoria (30%):** Leggi e comprendi i concetti
2. **Esempi (30%):** Analizza e modifica il codice esistente  
3. **Esercizi (30%):** Scrivi codice originale
4. **Progetti (10%):** Applica tutto insieme

### **Q: Devo memorizzare la sintassi?**
**A:** No! Concentrati su:
- **Concetti** e logica di programmazione
- **Pattern** e strutture comuni
- **Problem solving** e algoritmi
- La sintassi si memorizza con la pratica

### **Q: Come capisco se sono pronto per il modulo successivo?**
**A:** Completa la checklist di ogni modulo:
- ✅ Teoria compresa
- ✅ Esempi eseguiti e modificati
- ✅ Esercizi completati
- ✅ Quiz superato (punteggio ≥ 70%)

---

## 🔧 **Problemi Specifici di Codice**

### **Q: Il mio programma va in loop infinito**
**A:** Controlla:
1. Le condizioni dei cicli while/for
2. Che le variabili di controllo vengano modificate
3. Usa il debugger per tracciare l'esecuzione
4. Inserisci print di debug temporanei

### **Q: "NullPointerException" - cosa significa?**
**A:** Stai cercando di usare un oggetto che vale `null`:
```java
String s = null;
int len = s.length(); // ❌ NullPointerException

// Soluzione:
if (s != null) {
    int len = s.length(); // ✅ OK
}
```

### **Q: I miei calcoli danno risultati sbagliati**
**A:** Problemi comuni:
1. **Divisione intera:** `5/2 = 2` (non 2.5)
   - Soluzione: `5.0/2` o `(double)5/2`
2. **Overflow:** numeri troppo grandi per il tipo
3. **Precisione float:** usa `BigDecimal` per calcoli precisi

---

## 📖 **Risorse Extra**

### **Q: Dove trovo altri tutorial Java?**
**A:** Risorse consigliate:
- **[Oracle Java Tutorials](https://docs.oracle.com/javase/tutorial/)**
- **[Java Code Geeks](https://www.javacodegeeks.com/)**
- **[Baeldung](https://www.baeldung.com/)**
- **[YouTube: Derek Banas](https://www.youtube.com/user/derekbanas)**

### **Q: Come tengo aggiornate le mie conoscenze Java?**
**A:** 
1. Segui il [blog Oracle Java](https://blogs.oracle.com/java/)
2. Partecipa a community come [Stack Overflow](https://stackoverflow.com/questions/tagged/java)
3. Leggi [Java Weekly](https://www.baeldung.com/java-weekly-briefing) di Baeldung
4. Prova le nuove versioni Java quando escono

---

## 💼 **Orientamento Carriera**

### **Q: Java è ancora rilevante nel 2025?**
**A:** Assolutamente sì! Java è:
- Top 3 nei linguaggi più richiesti
- Standard nell'enterprise
- Base per Android
- Ecosistema maturo e stabile
- Stipendi competitivi

### **Q: Dopo questo corso, cosa studio?**
**A:** Percorsi suggeriti:
1. **Framework:** Spring Boot, Hibernate
2. **Web:** Servlet, JSP, REST API
3. **Database:** JDBC, JPA
4. **Testing:** JUnit, Mockito
5. **Build Tools:** Maven, Gradle

### **Q: Come preparo un portfolio Java?**
**A:** Crea progetti che mostrino:
1. **CRUD Application** con database
2. **REST API** con Spring Boot
3. **Web application** completa
4. **Algoritmi** e strutture dati
5. Carica tutto su **GitHub**

---

## 🤝 **Supporto e Community**

### **Q: Dove posso chiedere aiuto?**
**A:** Community consigliate:
- **[Stack Overflow](https://stackoverflow.com/questions/tagged/java)** per problemi tecnici
- **[Reddit r/learnjava](https://www.reddit.com/r/learnjava/)** per principianti
- **[Discord Java](https://discord.gg/java)** per chat in tempo reale
- **[Java Ranch](https://coderanch.com/c/java)** forum specializzato

### **Q: Come contribuisco a progetti open source?**
**A:** Inizia con:
1. **Documenta** progetti esistenti
2. **Correggi bug** semplici
3. **Aggiungi test** a progetti senza copertura
4. **Traduci** documentazione
5. Man mano affrontare feature più complesse

---

*💡 **Non hai trovato la risposta che cercavi?** Apri una issue nel repository o contatta la community!*
