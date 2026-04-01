#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double srednia(int *tablica, int rozmiar) {
  int suma = 0;
  for (int i = 0; i < rozmiar; i++) {
    suma = suma + tablica[i];
  }
  return (double)suma / rozmiar;
}

void wyswietl_dane(int *tablica, int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    printf("%d ", tablica[i]);
  }
}

int main() {
  int ile_liczb, maksymalna;
  printf("Podaj ile liczb chcesz zaalokować w pamięci: \n");
  scanf("%d", &ile_liczb);
  printf("Podaj maksymalny zakres mozliwych liczb do wylosowania: \n");
  scanf("%d", &maksymalna);
  int *wskaznik = malloc(ile_liczb * sizeof(int));
  if (!wskaznik) {
    perror("Nie ma wystarczająco pamięci!");
    return 1;
  }
  for (int i = 0; i < ile_liczb; i++) {
    wskaznik[i] = rand() % (maksymalna + 1);
  }

  printf("Srednia wylosowanych liczb to: %f\n", srednia(wskaznik, ile_liczb));
  wyswietl_dane(wskaznik, ile_liczb);
  printf("\n");
  free(wskaznik);
  return 0;
}
