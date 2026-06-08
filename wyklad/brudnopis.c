#include <stdio.h>

/* Funkcja wypisująca liczbę w formacie binarnym (32 bity) */
void printBinary(int liczba) {
  // Zaczynamy od najważniejszego bitu (po lewej stronie)
  for (int i = 31; i >= 0; i--) {
    // Przesuwamy bit na pierwszą pozycję i sprawdzamy czy to 1 czy 0
    int bit = (liczba >> i) & 1;
    printf("%d", bit);

    // Dodatkowa spacja co 4 bity dla lepszej czytelności
    if (i % 4 == 0) {
      printf(" ");
    }
  }
  printf("\n");
}

int main() {
  int x = 20;

  printf("Dziesietnie: %d\n", x);
  printf("Szesnastkowo: %x\n", x);
  printf("Binarnie: ");
  printBinary(x);

  return 0;
}
