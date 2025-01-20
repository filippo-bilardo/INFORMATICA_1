#include <stdio.h>

int potenza(int base, int esponente) {
  int risultato = 1;
  for (int i = 0; i < esponente; i++) {
    risultato *= base;
  }
  return risultato;
}

int main() {
  printf("5^4 = %d\n", potenza(5, 4));
  printf("12^3 = %d\n", potenza(12, 3));
  printf("20^2 = %d\n", potenza(20, 2));
  printf("15^0 = %d\n", potenza(15, 0));
  return 0;
}
