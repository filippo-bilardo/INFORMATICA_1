# Esercizi su Variabili e Tipi di Dati in C

Questa cartella contiene tre esercizi che illustrano l'uso delle variabili e dei tipi di dati in C.

## Esercizio 1: Tipi di dati fondamentali

Questo esercizio dimostra l'uso dei tipi di dati fondamentali in C e le conversioni tra diversi tipi.

- Tipi interi: `char`, `short`, `int`, `long`
- Tipi in virgola mobile: `float`, `double`
- Conversioni di tipo (casting)

## Esercizio 2: Calcolo delle proprietà di un rettangolo

Questo esercizio calcola area, perimetro e diagonale di un rettangolo utilizzando i tipi di dati in virgola mobile.

- Uso di `double` per calcoli precisi
- Input da tastiera con `scanf`
- Uso della funzione `sqrt` dalla libreria `math.h`

## Esercizio 3: Conversione di temperature

Questo esercizio converte temperature tra diverse unità di misura: Celsius, Fahrenheit e Kelvin.

- Uso di costanti con `#define`
- Uso del tipo `bool` dalla libreria `stdbool.h`
- Struttura di controllo `switch`
- Controllo di validità dei dati

## Compilazione ed esecuzione

Per compilare gli esercizi, puoi utilizzare il comando `gcc` o il Makefile fornito:

```bash
# Compilare tutti gli esercizi
make all

# Compilare un singolo esercizio (esempio: esercizio1)
make esercizio1

# Eseguire un esercizio (esempio: esercizio1)
./esercizio1
```

## Note

- Assicurati di avere installato il compilatore GCC
- Per Windows, puoi utilizzare MinGW o WSL
- Per la compilazione manuale:
  ```bash
  gcc -o esercizio1 esercizio1.c
  gcc -o esercizio2 esercizio2.c -lm  # -lm per linkare la libreria matematica
  gcc -o esercizio3 esercizio3.c
  ```

## Soluzioni

Le soluzioni complete degli esercizi sono disponibili nella cartella `soluzioni`.