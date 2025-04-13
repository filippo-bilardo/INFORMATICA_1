# Complessità computazionale: concetti base

La complessità computazionale è una branca dell'informatica teorica che studia le risorse (principalmente tempo e spazio) necessarie per risolvere un problema computazionale. Comprendere i concetti base della complessità computazionale è fondamentale per progettare algoritmi efficienti.

## Cos'è la complessità computazionale

La complessità computazionale misura l'efficienza di un algoritmo in termini di:

1. **Tempo di esecuzione**: Quanto tempo impiega l'algoritmo a completare l'esecuzione.
2. **Spazio di memoria**: Quanta memoria richiede l'algoritmo durante l'esecuzione.

Queste misure sono espresse in funzione della dimensione dell'input, indicata generalmente con n.

## Notazione asintotica

La notazione asintotica è utilizzata per descrivere il comportamento di un algoritmo quando la dimensione dell'input tende all'infinito. Le notazioni più comuni sono:

### 1. Notazione O grande (Big O)

La notazione O(f(n)) rappresenta il limite superiore asintotico della complessità di un algoritmo. In altre parole, descrive il caso peggiore.

Esempi comuni:
- O(1): Complessità costante (indipendente dalla dimensione dell'input)
- O(log n): Complessità logaritmica
- O(n): Complessità lineare
- O(n log n): Complessità linearitmica
- O(n²): Complessità quadratica
- O(2^n): Complessità esponenziale

### 2. Notazione Omega (Ω)

La notazione Ω(f(n)) rappresenta il limite inferiore asintotico della complessità di un algoritmo. Descrive il caso migliore.

### 3. Notazione Theta (Θ)

La notazione Θ(f(n)) rappresenta sia il limite superiore che inferiore della complessità di un algoritmo. Indica che l'algoritmo ha lo stesso comportamento asintotico nel caso migliore e nel caso peggiore.

## Classi di complessità comuni

### 1. Complessità costante - O(1)

L'algoritmo richiede sempre lo stesso tempo o spazio, indipendentemente dalla dimensione dell'input.

**Esempio**: Accesso a un elemento di un array tramite indice.

```
funzione getElemento(array, indice):
    return array[indice]
```

### 2. Complessità logaritmica - O(log n)

Il tempo di esecuzione cresce logaritmicamente con la dimensione dell'input. Questi algoritmi tipicamente riducono il problema a metà ad ogni passo.

**Esempio**: Ricerca binaria in un array ordinato.

```
funzione ricercaBinaria(array, target, inizio, fine):
    se inizio > fine:
        return -1
    
    medio = (inizio + fine) / 2
    
    se array[medio] == target:
        return medio
    altrimenti se array[medio] > target:
        return ricercaBinaria(array, target, inizio, medio-1)
    altrimenti:
        return ricercaBinaria(array, target, medio+1, fine)
```

### 3. Complessità lineare - O(n)

Il tempo di esecuzione cresce linearmente con la dimensione dell'input.

**Esempio**: Ricerca sequenziale in un array.

```
funzione ricercaSequenziale(array, target):
    per i da 0 a lunghezza(array)-1:
        se array[i] == target:
            return i
    return -1
```

### 4. Complessità linearitmica - O(n log n)

Comune negli algoritmi di ordinamento efficienti.

**Esempio**: Merge Sort, Quick Sort (caso medio).

### 5. Complessità quadratica - O(n²)

Il tempo di esecuzione cresce con il quadrato della dimensione dell'input.

**Esempio**: Bubble Sort, Selection Sort.

```
funzione bubbleSort(array):
    per i da 0 a lunghezza(array)-1:
        per j da 0 a lunghezza(array)-i-2:
            se array[j] > array[j+1]:
                scambia array[j] e array[j+1]
```

### 6. Complessità esponenziale - O(2^n)

Il tempo di esecuzione raddoppia (o cresce esponenzialmente) con ogni elemento aggiuntivo nell'input.

**Esempio**: Calcolo ricorsivo dei numeri di Fibonacci senza memorizzazione.

```
funzione fibonacci(n):
    se n <= 1:
        return n
    return fibonacci(n-1) + fibonacci(n-2)
```

## Complessità spaziale

La complessità spaziale misura la quantità di memoria richiesta da un algoritmo in funzione della dimensione dell'input.

Esempi:
- O(1): Spazio costante (indipendente dalla dimensione dell'input)
- O(n): Spazio lineare (proporzionale alla dimensione dell'input)
- O(n²): Spazio quadratico

## Analisi della complessità

Per analizzare la complessità di un algoritmo:

1. **Identificare le operazioni di base**: Determinare quali operazioni sono eseguite dall'algoritmo.

2. **Contare le operazioni**: Determinare quante volte ogni operazione viene eseguita in funzione della dimensione dell'input.

3. **Sommare i conteggi**: Sommare il numero totale di operazioni.

4. **Semplificare**: Esprimere il risultato utilizzando la notazione asintotica, mantenendo solo il termine dominante.

## Importanza pratica della complessità computazionale

1. **Previsione delle prestazioni**: Permette di prevedere come le prestazioni di un algoritmo cambieranno con l'aumentare della dimensione dell'input.

2. **Confronto di algoritmi**: Fornisce un modo oggettivo per confrontare l'efficienza di diversi algoritmi.

3. **Ottimizzazione**: Aiuta a identificare i colli di bottiglia e le aree di miglioramento.

4. **Scalabilità**: Permette di valutare se un algoritmo sarà praticabile per grandi insiemi di dati.

Comprendere la complessità computazionale è essenziale per sviluppare software efficiente e scalabile, specialmente quando si lavora con grandi quantità di dati o in sistemi con risorse limitate.