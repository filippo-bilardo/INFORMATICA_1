# precedenze operatori i C e C++

In C e C++, gli **operatori** sono valutati in base a regole di **precedenza** e **associatività**. La **precedenza** determina quali operatori sono valutati per primi, mentre l'**associatività** stabilisce la direzione in cui vengono valutati gli operatori di uguale precedenza (da sinistra a destra o da destra a sinistra).

### Precedenza degli operatori in C e C++

Gli operatori in C e C++ sono raggruppati in livelli di precedenza, dove gli operatori di precedenza più alta vengono valutati prima rispetto a quelli di precedenza inferiore. Di seguito, presento la tabella delle precedenze principali.

### 1. **Operatori unari e postfissi**:
   - **Precedenza più alta**
   - **Associatività da sinistra a destra** (per gli operatori postfissi)
   - **Operatori**: `++`, `--`, `()`, `[]`, `->`, `.`
   - Esempio:
     ```c
     int a = 5;
     a++;  // Incrementa a dopo il suo uso
     ```

### 2. **Operatori unari**:
   - **Associatività da destra a sinistra**
   - **Operatori**: `++`, `--`, `+` (unario), `-` (unario), `!`, `~`, `*` (dereferenziamento), `&` (indirizzo), `sizeof`, `(tipo)` (cast)
   - Esempio:
     ```c
     int a = 5;
     int b = -a;  // Inversione di segno
     ```

### 3. **Moltiplicazione, divisione e modulo**:
   - **Associatività da sinistra a destra**
   - **Operatori**: `*`, `/`, `%`
   - Esempio:
     ```c
     int a = 6, b = 2, c = 3;
     int result = a * b / c;  // La moltiplicazione e la divisione hanno la stessa precedenza, valutate da sinistra a destra
     ```

### 4. **Addizione e sottrazione**:
   - **Associatività da sinistra a destra**
   - **Operatori**: `+`, `-`
   - Esempio:
     ```c
     int a = 5 + 3 - 2;  // La somma e la sottrazione sono valutate da sinistra a destra
     ```

### 5. **Operatori di shift**:
   - **Associatività da sinistra a destra**
   - **Operatori**: `<<`, `>>`
   - Esempio:
     ```c
     int a = 1 << 2;  // Shift di 1 a sinistra di 2 posizioni
     ```

### 6. **Operatori di confronto relazionale**:
   - **Associatività da sinistra a destra**
   - **Operatori**: `<`, `<=`, `>`, `>=`
   - Esempio:
     ```c
     int a = 5;
     int result = a > 3;  // Valuta se a è maggiore di 3
     ```

### 7. **Operatori di uguaglianza**:
   - **Associatività da sinistra a destra**
   - **Operatori**: `==`, `!=`
   - Esempio:
     ```c
     int a = 5;
     int result = a == 5;  // Verifica se a è uguale a 5
     ```

### 8. **Operatori bit a bit AND**:
   - **Associatività da sinistra a destra**
   - **Operatore**: `&`
   - Esempio:
     ```c
     int a = 5 & 3;  // AND bit a bit tra 5 e 3
     ```

### 9. **Operatori bit a bit XOR**:
   - **Associatività da sinistra a destra**
   - **Operatore**: `^`
   - Esempio:
     ```c
     int a = 5 ^ 3;  // XOR bit a bit tra 5 e 3
     ```

### 10. **Operatori bit a bit OR**:
   - **Associatività da sinistra a destra**
   - **Operatore**: `|`
   - Esempio:
     ```c
     int a = 5 | 3;  // OR bit a bit tra 5 e 3
     ```

### 11. **Operatori logici AND**:
   - **Associatività da sinistra a destra**
   - **Operatore**: `&&`
   - Esempio:
     ```c
     int a = 5;
     int result = (a > 3) && (a < 10);  // Valuta se entrambe le condizioni sono vere
     ```

### 12. **Operatori logici OR**:
   - **Associatività da sinistra a destra**
   - **Operatore**: `||`
   - Esempio:
     ```c
     int a = 5;
     int result = (a > 3) || (a < 2);  // Valuta se almeno una delle due condizioni è vera
     ```

### 13. **Operatore ternario (condizionale)**:
   - **Associatività da destra a sinistra**
   - **Operatore**: `?:`
   - Esempio:
     ```c
     int a = 5;
     int result = (a > 3) ? 1 : 0;  // Se a è maggiore di 3, assegna 1, altrimenti 0
     ```

### 14. **Operatore di assegnazione**:
   - **Associatività da destra a sinistra**
   - **Operatori**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=`, `&=`, `^=`, `|=`
   - Esempio:
     ```c
     int a = 5;
     a += 3;  // Assegna a = a + 3
     ```

### 15. **Operatore di virgola**:
   - **Precedenza più bassa**
   - **Associatività da sinistra a destra**
   - **Operatore**: `,`
   - Esempio:
     ```c
     int a = (5, 6);  // Valuta 5, poi 6, e assegna a 6
     ```

### Esempio completo di precedenza e associatività:

```c
#include <stdio.h>

int main() {
    int a = 5, b = 10, c = 15;
    int result;

    result = a + b * c;  // La moltiplicazione viene valutata prima
    printf("Risultato 1: %d\n", result);  // Output: 155

    result = (a + b) * c;  // Le parentesi forzano la somma a essere valutata prima
    printf("Risultato 2: %d\n", result);  // Output: 225

    result = a > b && b < c;  // Gli operatori di confronto hanno precedenza su &&, quindi vengono valutati per primi
    printf("Risultato 3: %d\n", result);  // Output: 0 (falso)

    return 0;
}
```

In questo esempio, la **precedenza** e l'**associatività** determinano l'ordine in cui vengono valutati gli operatori. Se c'è ambiguità, è consigliabile usare le **parentesi** per rendere esplicito l'ordine di valutazione.

# riepilogo 

Ecco un riepilogo compatto delle **precedenze** e **associatività** degli operatori in C e C++:

### Precedenza degli operatori (dalla più alta alla più bassa):

1. **Postfissi**: `a++`, `a--`, `()`, `[]`, `->`, `.`
   - **Associatività**: sinistra → destra

2. **Unari**: `++a`, `--a`, `+`, `-`, `!`, `~`, `*` (dereferenziamento), `&` (indirizzo), `sizeof`, cast `(type)`
   - **Associatività**: destra → sinistra

3. **Moltiplicazione e divisione**: `*`, `/`, `%`
   - **Associatività**: sinistra → destra

4. **Addizione e sottrazione**: `+`, `-`
   - **Associatività**: sinistra → destra

5. **Shift**: `<<`, `>>`
   - **Associatività**: sinistra → destra

6. **Relazionali**: `<`, `<=`, `>`, `>=`
   - **Associatività**: sinistra → destra

7. **Uguaglianza**: `==`, `!=`
   - **Associatività**: sinistra → destra

8. **Bit a bit AND**: `&`
   - **Associatività**: sinistra → destra

9. **Bit a bit XOR**: `^`
   - **Associatività**: sinistra → destra

10. **Bit a bit OR**: `|`
    - **Associatività**: sinistra → destra

11. **Logico AND**: `&&`
    - **Associatività**: sinistra → destra

12. **Logico OR**: `||`
    - **Associatività**: sinistra → destra

13. **Ternario (condizionale)**: `? :`
    - **Associatività**: destra → sinistra

14. **Assegnazione**: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, `<<=`, `>>=`, `&=`, `^=`, `|=`
    - **Associatività**: destra → sinistra

15. **Virgola**: `,`
    - **Associatività**: sinistra → destra

### Nota:

- **Operatori con la stessa precedenza** vengono valutati secondo la loro **associatività**.
- L'uso delle **parentesi** può modificare l'ordine di valutazione.

