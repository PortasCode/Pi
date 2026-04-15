#include "manipulator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
  char **tablica_slow = NULL;
  int licznik_slow = 0;
  char bufor[1000];
  int czy_wczytywac = 1;

  printf("Wpisuj tekst lub wpisz <STOP> aby zakończyć: \n");

  while (czy_wczytywac) {
    fgets(bufor, sizeof(bufor), stdin);

    // szukamy spacji lub enter znaku, dlatego taki jest sep
    char *schowek = strtok(bufor, " \n");

    while (schowek != NULL) {

      if (strcmp(schowek, "<STOP>") == 0) {
        czy_wczytywac = 0;
        break;
      }

      wyczysc_slowo(schowek);

      if (czy_palindrom(schowek) == 1) {
        printf("Wow, palindromy >> %s <<\n", schowek);
      }

      tablica_slow = realloc(tablica_slow, (licznik_slow + 1) * sizeof(char *));

      tablica_slow[licznik_slow] = strdup(schowek);
      licznik_slow++;

      schowek = strtok(NULL, " \n");
    }
  }

  wygeneruj_zdanie(tablica_slow, licznik_slow);

  for (int i = 0; i < licznik_slow; i++) {
    free(tablica_slow[i]);
  }
  free(tablica_slow);

  return 0;
}
