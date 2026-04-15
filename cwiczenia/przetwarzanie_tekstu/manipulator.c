#include "manipulator.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wyczysc_slowo(char *slowo) {
  int czytaj = 0;
  int pisz = 0;

  while (slowo[czytaj] != '\0') {
    if (isalpha(slowo[czytaj])) {
      slowo[pisz] = slowo[czytaj];
      pisz++;
    }
    czytaj++;
  }
  slowo[pisz] = '\0';
}

int czy_palindrom(const char *slowo) {
  int dlugosc = strlen(slowo);

  if (dlugosc <= 1) {
    return 0;
  }

  int lewy = 0, prawy = dlugosc - 1;
  while (lewy < prawy) {
    if (tolower(slowo[lewy]) != tolower(slowo[prawy])) {
      return 0;
    }
    lewy++;
    prawy--;
  }
  return 1;
}

void wygeneruj_zdanie(char **tablica_slow, int liczba_slow) {
  char *temp;

  for (int i = 0; i < liczba_slow; i++) {
    int indeks = rand() % liczba_slow;
    temp = tablica_slow[indeks];
    tablica_slow[indeks] = tablica_slow[i];
    tablica_slow[i] = temp;
  }

  tablica_slow[0][0] = toupper(tablica_slow[0][0]);
  for (int i = 0; i < liczba_slow; i++) {
    printf("%s", tablica_slow[i]);
    if (i != liczba_slow - 1) {
      printf(" ");
    }
  }
  printf(".");

  tablica_slow[0][0] = tolower(tablica_slow[0][0]);
}
