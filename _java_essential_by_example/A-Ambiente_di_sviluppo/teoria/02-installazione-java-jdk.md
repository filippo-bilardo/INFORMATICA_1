# 2. Installazione Java JDK

## 🎯 **Obiettivi del Capitolo**

- Comprendere la differenza tra JRE e JDK
- Installare correttamente Java JDK sul proprio sistema
- Configurare le variabili d'ambiente
- Verificare l'installazione

**⏱️ Tempo stimato:** 30-45 minuti

---

## 📋 **JDK vs JRE: Cosa Installare?**

### **JRE (Java Runtime Environment)**
- ✅ **Solo esecuzione** di programmi Java
- ✅ Include JVM (Java Virtual Machine)
- ❌ **NON** include compilatore (`javac`)
- ❌ **NON** include strumenti di sviluppo

### **JDK (Java Development Kit)**
- ✅ **Sviluppo e esecuzione** di programmi Java
- ✅ Include JRE completo
- ✅ Include compilatore (`javac`)
- ✅ Include strumenti di sviluppo e debugging

> **💡 Per questo corso:** Installiamo sempre il **JDK**, non solo JRE!

---

## 🖥️ **Installazione per Sistema Operativo**

### **Windows**

#### **Metodo 1: Download dal sito Oracle**
1. Vai su [https://www.oracle.com/java/technologies/downloads/](https://www.oracle.com/java/technologies/downloads/)
2. Seleziona **Windows** → **x64 Installer**
3. Scarica il file `.exe`
4. Esegui l'installer come amministratore
5. Segui la procedura guidata

#### **Metodo 2: OpenJDK (Gratuito e Open Source)**
1. Vai su [https://adoptium.net/](https://adoptium.net/)
2. Seleziona **Windows x64** → **JDK 11** o **17**
3. Scarica il file `.msi`
4. Installa seguendo le istruzioni

#### **Metodo 3: Package Manager (Avanzato)**
```cmd
# Con Chocolatey
choco install openjdk11

# Con Scoop
scoop install openjdk11
```

### **macOS**

#### **Metodo 1: Download Adoptium**
```bash
# Con Homebrew (consigliato)
brew install openjdk@11

# Aggiungi al PATH
echo 'export PATH="/opt/homebrew/opt/openjdk@11/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

#### **Metodo 2: Download manuale**
1. Visita [https://adoptium.net/](https://adoptium.net/)
2. Seleziona **macOS** → **Architecture** (x64 o aarch64 per M1/M2)
3. Scarica il file `.pkg`
4. Installa con doppio click

### **Linux (Ubuntu/Debian)**

#### **OpenJDK dal repository**
```bash
# Aggiorna il sistema
sudo apt update

# Installa OpenJDK 11
sudo apt install openjdk-11-jdk

# Verifica installazione
java -version
javac -version
```

#### **Per altre versioni**
```bash
# Lista versioni disponibili
apt list | grep openjdk

# Installa versione specifica
sudo apt install openjdk-17-jdk
```

### **Linux (Red Hat/CentOS/Fedora)**

```bash
# Con yum (CentOS/RHEL)
sudo yum install java-11-openjdk-devel

# Con dnf (Fedora)
sudo dnf install java-11-openjdk-devel
```

---

## ⚙️ **Configurazione Variabili d'Ambiente**

### **Windows**

#### **Metodo Grafico**
1. **Pannello di Controllo** → **Sistema** → **Impostazioni avanzate**
2. Click su **Variabili d'ambiente**
3. **Variabili di sistema** → **Nuova**

**JAVA_HOME:**
```
Nome: JAVA_HOME
Valore: C:\Program Files\Java\jdk-11.0.x
```

**PATH:**
```
Aggiungi: %JAVA_HOME%\bin
```

#### **Metodo Command Line**
```cmd
# Imposta JAVA_HOME (temporaneo)
set JAVA_HOME=C:\Program Files\Java\jdk-11.0.x

# Aggiungi al PATH (temporaneo)
set PATH=%JAVA_HOME%\bin;%PATH%

# Per renderlo permanente, usa setx
setx JAVA_HOME "C:\Program Files\Java\jdk-11.0.x"
setx PATH "%JAVA_HOME%\bin;%PATH%"
```

### **macOS/Linux**

#### **Bash (.bashrc o .bash_profile)**
```bash
# Apri il file di configurazione
nano ~/.bashrc    # Linux
nano ~/.bash_profile    # macOS

# Aggiungi queste righe
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64  # Linux
export JAVA_HOME=/usr/libexec/java_home -v 11         # macOS
export PATH=$JAVA_HOME/bin:$PATH

# Ricarica la configurazione
source ~/.bashrc
```

#### **Zsh (.zshrc) - macOS default**
```bash
# Apri il file di configurazione
nano ~/.zshrc

# Aggiungi queste righe
export JAVA_HOME=$(/usr/libexec/java_home -v 11)
export PATH=$JAVA_HOME/bin:$PATH

# Ricarica la configurazione
source ~/.zshrc
```

---

## ✅ **Verifica dell'Installazione**

### **Test Basic**
```bash
# Verifica versione Java Runtime
java -version

# Output atteso:
# openjdk version "11.0.x" 2023-xx-xx
# OpenJDK Runtime Environment (build 11.0.x+x)
# OpenJDK 64-Bit Server VM (build 11.0.x+x, mixed mode)

# Verifica versione Java Compiler
javac -version

# Output atteso:
# javac 11.0.x
```

### **Test Completo**
Crea un file di test `TestInstallazione.java`:

```java
/**
 * Test di verifica installazione Java
 * @author Il tuo nome
 * @version 1.0
 */
public class TestInstallazione {
    public static void main(String[] args) {
        // Test sistema
        System.out.println("=== Test Installazione Java ===");
        System.out.println("Java Version: " + System.getProperty("java.version"));
        System.out.println("Java Vendor: " + System.getProperty("java.vendor"));
        System.out.println("Java Home: " + System.getProperty("java.home"));
        System.out.println("OS Name: " + System.getProperty("os.name"));
        System.out.println("OS Version: " + System.getProperty("os.version"));
        
        // Test funzionalità base
        int somma = 5 + 3;
        System.out.println("Test calcolo: 5 + 3 = " + somma);
        
        // Test array
        String[] linguaggi = {"Java", "Python", "JavaScript"};
        System.out.print("Linguaggi supportati: ");
        for (String linguaggio : linguaggi) {
            System.out.print(linguaggio + " ");
        }
        System.out.println();
        
        System.out.println("✅ Installazione Java completata correttamente!");
    }
}
```

**Compila ed esegui:**
```bash
# Compila
javac TestInstallazione.java

# Esegui
java TestInstallazione
```

**Output atteso:**
```
=== Test Installazione Java ===
Java Version: 11.0.x
Java Vendor: Eclipse Adoptium
Java Home: /usr/lib/jvm/java-11-openjdk-amd64
OS Name: Linux
OS Version: 5.x.x
Test calcolo: 5 + 3 = 8
Linguaggi supportati: Java Python JavaScript 
✅ Installazione Java completata correttamente!
```

---

## 🔧 **Risoluzione Problemi Comuni**

### **"java: command not found"**
**Causa:** Java non è nel PATH o non è installato

**Soluzioni:**
1. Verifica installazione: `whereis java` (Linux/Mac)
2. Controlla PATH: `echo $PATH`
3. Reinstalla Java se necessario

### **"javac: command not found"**
**Causa:** Installato JRE invece di JDK

**Soluzione:** Installa JDK completo, non solo JRE

### **Versione sbagliata di Java**
```bash
# Controlla tutte le versioni installate (Linux)
sudo update-alternatives --config java

# Su macOS con più versioni
/usr/libexec/java_home -V
```

### **JAVA_HOME non impostato**
```bash
# Test immediato
echo $JAVA_HOME

# Se vuoto, imposta temporaneamente
export JAVA_HOME=/path/to/your/java
```

---

## 🎯 **Best Practices**

### **✅ Raccomandazioni**
- **Usa versioni LTS** (Long Term Support): 8, 11, 17, 21
- **OpenJDK** è gratuito e equivalente a Oracle JDK
- **Aggiorna regolarmente** per patch di sicurezza
- **Documenta la versione** usata nei tuoi progetti

### **❌ Cosa Evitare**
- Non installare JRE se stai sviluppando
- Non mischiare versioni diverse senza gestirle
- Non dimenticare di configurare JAVA_HOME
- Non usare versioni obsolete per nuovi progetti

---

## 📚 **Risorse Aggiuntive**

### **Download Ufficiali**
- [Oracle JDK](https://www.oracle.com/java/technologies/downloads/)
- [OpenJDK (Adoptium)](https://adoptium.net/)
- [Amazon Corretto](https://aws.amazon.com/corretto/)

### **Documentazione**
- [Java Installation Guide](https://docs.oracle.com/en/java/javase/11/install/)
- [OpenJDK Installation](https://openjdk.java.net/install/)

---

## ✅ **Checklist di Completamento**

Prima di procedere al prossimo capitolo, assicurati di aver:

- [ ] ✅ Installato Java JDK (non solo JRE)
- [ ] ✅ Configurato JAVA_HOME correttamente
- [ ] ✅ Aggiunto Java al PATH
- [ ] ✅ Verificato `java -version` funziona
- [ ] ✅ Verificato `javac -version` funziona
- [ ] ✅ Compilato ed eseguito TestInstallazione.java
- [ ] ✅ Compreso la differenza tra JDK e JRE

---

## 🧭 **Navigazione**

- [⬅️ Capitolo Precedente: Introduzione a Java](01-introduzione-java.md)
- [➡️ Capitolo Successivo: Installazione IDE](03-installazione-ide.md)
- [🏠 Torna al Modulo A](../README.md)
- [📑 Indice Generale](../../README.md)

---

*Prossimo step: [Installazione e configurazione IDE](03-installazione-ide.md)*
