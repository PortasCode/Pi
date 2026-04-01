#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct t_towar {
  char nazwa[50];
  float cena;
};

int main() {
  struct t_towar *magazyn = NULL; // Nasz glowny wskaznik na dane
  int pojemnosc = 0;      // Ile towarow zmiesci sie w zaalokowanej pamieci
  int liczba_towarow = 0; // Ile towarow faktycznie juz wprowadzilismy
  int wybor;

  do {
    printf("\n=== MENU MAGAZYNU ===\n");
    printf("1. Dodaj nowy towar\n");
    printf("2. Wyswietl wszystkie towary\n");
    printf("0. Zakoncz program\n");
    printf("Wybor: ");

    if (scanf("%d", &wybor) != 1) {
      while (getchar() != '\n')
        ;
      printf("Blad: Wprowadz cyfre!\n");
      continue;
    }

    switch (wybor) {
    case 1:

      if (pojemnosc == 0) {
        magazyn = (struct t_towar *)malloc(sizeof(struct t_towar));
        if (magazyn == NULL) {
          perror("KRYTYCZNY BLAD: Brak pamieci na pierwszy towar!");
          return 1; // Przerywamy program
        }
        pojemnosc = 1;
        printf("[System] Zaalokowano pamiec na 1 towar.\n");
      } else if (liczba_towarow == pojemnosc) {
        int nowa_pojemnosc = pojemnosc * 2;
        struct t_towar *tymczasowy = (struct t_towar *)realloc(
            magazyn, nowa_pojemnosc * sizeof(struct t_towar));
        if (tymczasowy == NULL) {
          printf("BLAD: Brak pamieci na powiekszenie magazynu!\n");
          break;
        }

        magazyn = tymczasowy;
        pojemnosc = nowa_pojemnosc;
        printf("[System] Powiekszono magazyn! Nowa pojemnosc: %d towarow.\n",
               pojemnosc);
      }
      printf("\n--- Wprowadzanie towaru nr %d ---\n", liczba_towarow + 1);

      printf("Podaj nazwe towaru: ");
      scanf(" %49s", magazyn[liczba_towarow].nazwa);

      printf("Podaj cene towaru: ");
      scanf("%f", &magazyn[liczba_towarow].cena);

      liczba_towarow++;
      printf("Towar dodany pomyslnie!\n");
      break;

    case 2:
      if (liczba_towarow == 0) {
        printf("Magazyn jest pusty!\n");
      } else {
        printf("\n--- STAN MAGAZYNU ---\n");
        for (int i = 0; i < liczba_towarow; i++) {
          printf("%d. %s - %.2f PLN\n", i + 1, magazyn[i].nazwa,
                 magazyn[i].cena);
        }
      }
      break;

    case 0:
      printf("Zamykanie programu. Sprzatanie pamieci...\n");
      break;

    default:
      printf("Nieznana opcja. Sprobuj ponownie.\n");
    }
  } while (wybor != 0);

  if (magazyn != NULL) {
    free(magazyn);
  }

  return 0;
}
