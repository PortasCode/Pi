#include "tabela_akcje.h"
#include <stdio.h>

int main() {
  int rozmiar;
  printf("Podaj rozmiar tablicy: \n");
  scanf("%d", &rozmiar);
  int flaga = 1;

  float tablica[rozmiar];
  float *wsk = tablica;

  typedef enum {
    op_przypisz_zera,    // 0
    op_przypisz_wartosc, // 1
    op_wypisz_wartosci,  // 2
    op_zwroc_sume,       // 3
    op_zamien_miejscami, // 4
    op_ile_roznych,      // 5
    op_zakoncz           // 6
  } opcje;

  while (flaga) {
    int opcja;

    // ZMIANA 3: Wyświetlamy użytkownikowi dostępne opcje
    printf("\n--- MENU ---\n");
    printf("0. Przypisz zera\n");
    printf("1. Przypisz wartosc do indeksu\n");
    printf("2. Wypisz wartosci w zakresie\n");
    printf("3. Zwroc sume w zakresie\n");
    printf("4. Zamien miejscami (podaj dwa indeksy)\n");
    printf("5. Ile elementow roznych od podanego (podaj zakres)\n");
    printf("6. Zakoncz program\n");
    printf("Podaj co chcesz wykonac: ");

    scanf("%d", &opcja);

    switch (opcja) {
    case op_przypisz_zera:
      // ZMIANA 2: Wszędzie używamy 'tablica', a nie 'wsk'
      przypisz_zera(wsk, rozmiar);
      break;

    case op_przypisz_wartosc: {
      int indeks;
      float a;
      printf("Podaj wartosc: \n");
      scanf("%f", &a);
      printf("Podaj indeks: \n");
      scanf("%d", &indeks);
      przypisz_wartosc(wsk, a, indeks);
      break;
    }
    case op_wypisz_wartosci: {
      int a, b;
      printf("Podaj pierwszy indeks: \n");
      scanf("%d", &a);
      printf("Podaj drugi indeks: \n");
      scanf("%d", &b);
      wypisz_wartosci(wsk, a, b);
      break;
    }
    case op_zwroc_sume: {
      int a, b;
      float suma;
      printf("Podaj pierwszy indeks: \n");
      scanf("%d", &a);
      printf("Podaj drugi indeks: \n");
      scanf("%d", &b);
      suma = zwroc_sume(wsk, a, b);
      printf("Suma: %f\n", suma);
      break;
    }

    case op_zamien_miejscami: {
      int a, b;
      printf("Podaj pierwszy indeks: \n");
      scanf("%d", &a);
      printf("Podaj drugi indeks: \n");
      scanf("%d", &b);
      zamien_miejscami(wsk, a, b);
      break;
    }
    case op_ile_roznych: {
      int counter;
      int a, b;
      printf("Podaj pierwszy indeks: \n");
      scanf("%d", &a);
      printf("Podaj drugi indeks: \n");
      scanf("%d", &b);
      counter = ile_roznych(wsk, a, b);
      printf("Ilosc elementow: %d\n", counter);
      break;
    }
    case op_zakoncz:
      printf("Koniec programu.\n");
      flaga = 0;
      break;

    default:
      // Dodatkowy bonus: zabezpieczenie przed złą liczbą
      printf("Nieznana opcja. Sprobuj ponownie.\n");
      break;
    }
  }
  return 0;
}
