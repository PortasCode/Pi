#include <stdio.h>
#include <string.h>

int main() {
  printf("Podaj nazwę pliku tekstowego na którym chcesz pracować: \n");

  while (1) {
    printf("------MENU------\n");
    printf(" [1] - Utwórz nowy plik i dodaj do niego tekst\n");
    printf(" [2] - Dopisz do istniejącgo pliku\n");
    printf(" [3] - Odczytaj zawartość pliku\n");
    printf(" [4] - Zakończ działanie programu\n");
    int wybor;
    printf("\n");
    printf("Podaj swoj wybor: \n");
    scanf("%d", &wybor);

    switch (wybor) {

    case 1: {
      char nazwa_pliku[50];
      printf("Podaj nazwę pliku, który chcesz utworzyć:\n");
      scanf("%s", nazwa_pliku);
      getchar();
      FILE *plik = fopen(nazwa_pliku, "w");

      if (plik == NULL) {
        printf("Błąd: Pliku nie udalo sie utworzyć\n");
        break;
      }
      while (1) {
        char tekst[100];
        printf("Podaj tekst:\n");
        fgets(tekst, sizeof(tekst), stdin);

        if (strcmp(tekst, "<STOP>\n") == 0) {
          break;
        }
        fputs(tekst, plik);
      }
      fclose(plik);
      break;
    }

    case 2: {
      char nazwa_pliku[50];
      printf("Podaj nazwę pliku, do którego chcesz dopisać tekst:\n");
      scanf("%s", nazwa_pliku);
      getchar();
      FILE *plik = fopen(nazwa_pliku, "a");

      if (plik == NULL) {
        printf("Błąd: Nie można otworzyć pliku do dopisywania (może nie "
               "istnieje?).\n");
        break;
      }
      while (1) {
        char tekst[100];
        printf("Podaj tekst do dopisania:\n");
        fgets(tekst, sizeof(tekst), stdin);

        if (strcmp(tekst, "<STOP>\n") == 0) {
          break;
        }
        fputs(tekst, plik);
      }
      fclose(plik);
      break;
    }

    case 3: {
      char nazwa_pliku[50];
      printf("Podaj nazwę pliku, który chcesz odczytać:\n");
      scanf("%s", nazwa_pliku);
      getchar();
      FILE *plik = fopen(nazwa_pliku, "r");

      if (plik == NULL) {
        printf("Błąd: Plik nie istnieje lub brak dostępu.\n");
        break;
      }

      char linia[100];
      printf("\n--- Zawartość pliku %s ---\n", nazwa_pliku);

      while (fgets(linia, sizeof(linia), plik) != NULL) {
        printf("%s", linia);
      }
      printf("\n---------------------------\n");

      fclose(plik);
      break;
    }

    case 4: {
      printf("Zamykanie programu...\n");
      return 0;
    }

    default:
      printf("Nieznana opcja, spróbuj ponownie.\n");
      break;
    }
  }
}
