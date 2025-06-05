# 3. Installazione e Configurazione IDE

## 🎯 **Obiettivi del Capitolo**

- Scegliere l'IDE più adatto per iniziare
- Installare e configurare l'IDE scelto
- Creare il primo progetto Java
- Configurare l'IDE per lo sviluppo efficiente

**⏱️ Tempo stimato:** 45-60 minuti

---

## 🤔 **Quale IDE Scegliere?**

### **🥇 IntelliJ IDEA Community (Consigliato per Principianti)**

**✅ Vantaggi:**
- Gratis e molto potente
- Ottimo supporto per Java
- Intellisense avanzato
- Debugging eccellente
- Git integrato
- Molti plugin disponibili

**❌ Svantaggi:**
- Può essere lento su PC datati
- Curva di apprendimento iniziale

**👥 Ideale per:** Principianti e professionisti

### **🥈 Visual Studio Code + Extension Pack for Java**

**✅ Vantaggi:**
- Leggero e veloce
- Gratis e open source
- Ottima interfaccia
- Molte estensioni
- Integrazione Git eccellente

**❌ Svantaggi:**
- Richiede configurazione estensioni
- Meno funzionalità "out of the box"

**👥 Ideale per:** Chi preferisce editor leggeri

### **🥉 Eclipse IDE**

**✅ Vantaggi:**
- Storico IDE Java
- Completamente gratuito
- Molto stabile
- Supporto enterprise

**❌ Svantaggi:**
- Interfaccia datata
- Configurazione più complessa
- Meno user-friendly

**👥 Ideale per:** Sviluppo enterprise, chi conosce già Eclipse

---

## 🚀 **Installazione IntelliJ IDEA Community**

### **Windows**

1. **Download:**
   - Vai su [https://www.jetbrains.com/idea/download/](https://www.jetbrains.com/idea/download/)
   - Seleziona **Community** (gratuito)
   - Download per Windows

2. **Installazione:**
   ```
   • Esegui il file .exe scaricato
   • Next → Next → ✅ Crea shortcut desktop
   • ✅ Aggiungi "Open Folder as IntelliJ Project"
   • ✅ Associa file .java
   • Install → Finish
   ```

3. **Primo Avvio:**
   ```
   • Non importare settings (prima installazione)
   • Scegli tema: Darcula (scuro) o IntelliJ Light
   • Skip plugin aggiuntivi (per ora)
   ```

### **macOS**

```bash
# Con Homebrew (consigliato)
brew install --cask intellij-idea-ce

# O download manuale dal sito JetBrains
```

### **Linux (Ubuntu/Debian)**

#### **Metodo 1: Snap Package (più semplice)**
```bash
sudo snap install intellij-idea-community --classic
```

#### **Metodo 2: Download manuale**
```bash
# Download
wget https://download.jetbrains.com/idea/ideaIC-2023.x.x.tar.gz

# Estrai
tar -xzf ideaIC-2023.x.x.tar.gz

# Sposta in /opt
sudo mv idea-IC-* /opt/intellij-idea

# Crea link simbolico
sudo ln -s /opt/intellij-idea/bin/idea.sh /usr/local/bin/idea

# Avvia
idea
```

---

## ⚙️ **Configurazione Iniziale IntelliJ IDEA**

### **1. Configurazione Java SDK**

```
1. File → Project Structure → Project Settings → Project
2. Project SDK → Add SDK → Download JDK
3. Scegli versione: OpenJDK 11 o 17
4. Project Language Level: stesso della versione JDK
5. Apply → OK
```

### **2. Impostazioni Generali**

```
File → Settings (Ctrl+Alt+S)

📁 Appearance & Behavior
   └── Appearance
       • Theme: Darcula o IntelliJ Light
       • ✅ Show tool window bars
       
📁 Editor
   └── General
       • ✅ Show line numbers
       • ✅ Show whitespaces
   └── Code Style → Java
       • Tab size: 4
       • Indent: 4
       • ✅ Use tab character: NO (usa spazi)
       
📁 Build, Execution, Deployment
   └── Compiler
       • ✅ Build project automatically
```

### **3. Plugin Essenziali**

```
File → Settings → Plugins

Plugin già installati utili:
• Git Integration
• Maven
• Terminal
• TODO
• Database Tools

Plugin aggiuntivi consigliati:
• Key Promoter X (impara shortcuts)
• Rainbow Brackets (parentesi colorate)
• GitToolBox (info Git avanzate)
```

---

## 📁 **Creazione del Primo Progetto**

### **Nuovo Progetto Java**

1. **Avvia IntelliJ IDEA**
2. **New Project**
3. **Configura progetto:**
   ```
   • Template: IntelliJ (default)
   • Name: MioPrimoProgetto
   • Location: C:\Users\TuoNome\IdeaProjects\ (o percorso preferito)
   • Language: Java
   • Build System: IntelliJ (per ora)
   • JDK: 11 o 17 (quella installata)
   • ✅ Add sample code
   ```
4. **Create**

### **Struttura Progetto Creata**

```
MioPrimoProgetto/
├── .idea/                 # Configurazioni IntelliJ
├── src/                   # Codice sorgente
│   └── Main.java         # Classe principale
├── MioPrimoProgetto.iml  # File progetto IntelliJ
└── out/                  # File compilati (generato automaticamente)
```

### **Il File Main.java**

```java
/**
 * Primo programma Java creato con IntelliJ IDEA
 * 
 * @author Il tuo nome
 * @version 1.0
 * @since 2025-06-05
 */
public class Main {
    /**
     * Metodo principale - punto di ingresso del programma
     * 
     * @param args argomenti da linea di comando
     */
    public static void main(String[] args) {
        // Il classico primo programma
        System.out.println("Hello World!");
        
        // Informazioni sul sistema
        System.out.println("Versione Java: " + System.getProperty("java.version"));
        System.out.println("IDE: IntelliJ IDEA");
        System.out.println("Autore: " + System.getProperty("user.name"));
        
        // Test operazioni base
        int a = 10;
        int b = 5;
        System.out.println("Calcolo: " + a + " + " + b + " = " + (a + b));
    }
}
```

---

## ▶️ **Esecuzione del Programma**

### **Metodo 1: Click sulla freccia verde**
- Clicca sulla freccia verde accanto al metodo `main`
- Oppure accanto al nome della classe

### **Metodo 2: Menu Run**
```
Run → Run 'Main' (Ctrl+Shift+F10)
```

### **Metodo 3: Tasto destro**
```
Tasto destro su Main.java → Run 'Main.main()'
```

### **Output Atteso**
```
Hello World!
Versione Java: 11.0.x
IDE: IntelliJ IDEA  
Autore: TuoNome
Calcolo: 10 + 5 = 15

Process finished with exit code 0
```

---

## 🛠️ **Alternative: Visual Studio Code**

### **Installazione VS Code + Java**

#### **1. Installa VS Code**
- Download da [https://code.visualstudio.com/](https://code.visualstudio.com/)
- Installa seguendo le istruzioni del sistema operativo

#### **2. Installa Extension Pack for Java**
```
1. Apri VS Code
2. Ctrl+Shift+X (Extensions)
3. Cerca "Extension Pack for Java"
4. Installa (include 6 estensioni essenziali)
```

#### **3. Crea Progetto Java**
```
1. Ctrl+Shift+P → "Java: Create Java Project"
2. Seleziona "No build tools"
3. Scegli cartella del progetto
4. Inserisci nome progetto
```

### **Configurazione VS Code**

#### **settings.json**
```json
{
    "java.home": "/path/to/your/java/home",
    "java.configuration.runtimes": [
        {
            "name": "JavaSE-11",
            "path": "/path/to/jdk-11"
        }
    ],
    "editor.fontSize": 14,
    "editor.tabSize": 4,
    "editor.insertSpaces": true,
    "files.autoSave": "afterDelay"
}
```

---

## 📚 **Funzionalità IDE Essenziali**

### **🔍 Navigazione Codice**

#### **IntelliJ IDEA**
```
• Ctrl+N: Trova classe
• Ctrl+Shift+N: Trova file
• Ctrl+Click: Vai alla definizione
• Alt+F7: Trova usages
• Ctrl+B: Vai alla dichiarazione
```

#### **VS Code**
```
• Ctrl+P: Trova file
• Ctrl+Shift+P: Command palette
• F12: Vai alla definizione
• Shift+F12: Trova references
• Ctrl+G: Vai alla riga
```

### **✏️ Editing Avanzato**

#### **Auto-completamento**
- **IntelliJ:** Ctrl+Space
- **VS Code:** Ctrl+Space

```java
// Digita "syso" + Tab → System.out.println()
// Digita "main" + Tab → metodo main completo
// Digita "for" + Tab → ciclo for
```

#### **Refactoring**
- **Rinomina variabile:** Shift+F6 (IntelliJ) / F2 (VS Code)
- **Estrai metodo:** Ctrl+Alt+M (IntelliJ) / Ctrl+Shift+R (VS Code)

### **🐛 Debugging**

#### **Impostare Breakpoint**
- Click sul margine sinistro della riga
- Linea diventa rossa/evidenziata

#### **Avviare Debug**
- **IntelliJ:** Shift+F9 o click su icona bug
- **VS Code:** F5

#### **Controlli Debug**
```
• F8: Step Over (salta al prossimo statement)
• F7: Step Into (entra nei metodi)
• Shift+F8: Step Out (esci dal metodo)
• F9: Continue (continua esecuzione)
```

---

## 🎨 **Personalizzazione IDE**

### **Temi e Aspetto**

#### **IntelliJ IDEA**
```
File → Settings → Appearance & Behavior → Appearance
• Darcula (tema scuro)
• IntelliJ Light (tema chiaro)
• High Contrast (alta leggibilità)
```

#### **VS Code**
```
File → Preferences → Color Theme
• Dark+ (default dark)
• Light+ (default light)
• Monokai (popolare)
• Solarized Dark/Light
```

### **Font e Dimensioni**

#### **IntelliJ IDEA**
```
Settings → Editor → Font
• Font: JetBrains Mono, Consolas, Source Code Pro
• Size: 14-16
• Line spacing: 1.2
```

#### **VS Code**
```json
{
    "editor.fontFamily": "'JetBrains Mono', 'Consolas', monospace",
    "editor.fontSize": 14,
    "editor.lineHeight": 1.5
}
```

---

## ✅ **Verifica Setup Completo**

### **Test Completo IDE**

Crea questo file di test `TestIDE.java`:

```java
import java.util.Scanner;
import java.util.ArrayList;

/**
 * Test completo funzionalità IDE
 */
public class TestIDE {
    public static void main(String[] args) {
        System.out.println("=== Test IDE Setup ===");
        
        // Test auto-completamento
        testAutoCompletamento();
        
        // Test debugging (metti breakpoint qui)
        testDebugging();
        
        // Test input utente
        testInput();
    }
    
    /**
     * Test funzionalità auto-completamento
     */
    private static void testAutoCompletamento() {
        // Test: digita "Array" e premi Ctrl+Space
        ArrayList<String> lista = new ArrayList<>();
        lista.add("IntelliJ");
        lista.add("VS Code");
        lista.add("Eclipse");
        
        System.out.println("IDE disponibili:");
        for (String ide : lista) {
            System.out.println("- " + ide);
        }
    }
    
    /**
     * Test debugging - metti breakpoint su questa riga
     */
    private static void testDebugging() {
        int x = 10;  // ← Metti breakpoint qui
        int y = 20;
        int somma = x + y;
        System.out.println("Debug test: " + x + " + " + y + " = " + somma);
    }
    
    /**
     * Test input da console
     */
    private static void testInput() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Inserisci il tuo nome: ");
        String nome = scanner.nextLine();
        System.out.println("Ciao " + nome + "! Setup completato ✅");
        scanner.close();
    }
}
```

### **Test da Eseguire:**

1. **✅ Auto-completamento:** Digita codice e verifica suggestions
2. **✅ Syntax highlighting:** Il codice è colorato correttamente
3. **✅ Error detection:** L'IDE mostra errori di sintassi
4. **✅ Compilazione:** Il programma compila senza errori
5. **✅ Esecuzione:** Il programma si avvia e funziona
6. **✅ Debugging:** Breakpoint funziona, step-by-step OK
7. **✅ Input/Output:** Console interattiva funziona

---

## 🔧 **Risoluzione Problemi Comuni**

### **"Project SDK not defined"**
```
File → Project Structure → Project → Project SDK
Seleziona la versione Java installata
```

### **"Cannot resolve symbol 'String'"**
```
Problema di configurazione JDK
File → Invalidate Caches → Invalidate and Restart
```

### **Programma non si avvia**
```
1. Verifica che la classe abbia metodo main
2. Controlla la configurazione Run
3. Run → Edit Configurations → verifica Main class
```

### **VS Code non riconosce Java**
```
1. Ctrl+Shift+P → "Java: Reload Projects"
2. Verifica Extension Pack for Java installato
3. Controlla java.home nelle settings
```

---

## 📋 **Checklist di Completamento**

Prima di procedere, assicurati di aver:

- [ ] ✅ Installato IDE scelto (IntelliJ/VS Code/Eclipse)
- [ ] ✅ Configurato Java SDK nell'IDE
- [ ] ✅ Creato primo progetto Java
- [ ] ✅ Scritto e eseguito "Hello World"
- [ ] ✅ Testato auto-completamento (Ctrl+Space)
- [ ] ✅ Testato debugging con breakpoint
- [ ] ✅ Personalizzato tema e font
- [ ] ✅ Imparato i shortcut di base
- [ ] ✅ Eseguito TestIDE.java con successo

---

## 🎯 **Prossimi Passi**

Ora che hai un ambiente di sviluppo funzionante:

1. **📖 Familiarizza** con l'interfaccia dell'IDE
2. **⌨️ Memorizza** i shortcut più utili
3. **🔧 Esplora** le impostazioni e personalizzazioni
4. **📚 Prosegui** con il Modulo B - Problemi ed Algoritmi

---

## 🧭 **Navigazione**

- [⬅️ Capitolo Precedente: Installazione Java JDK](02-installazione-java-jdk.md)
- [➡️ Capitolo Successivo: Primo Programma Java](04-primo-programma-java.md)
- [🏠 Torna al Modulo A](../README.md)
- [📑 Indice Generale](../../README.md)

---

*Prossimo step: [Il tuo primo programma Java](04-primo-programma-java.md)*
