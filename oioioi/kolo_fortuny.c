#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr int MAX_TEXTS = 20;

int guess_a_letter(char *text, const char *original_text) {
  char wylosowana = 'A' + (rand() % 26);
  int sukces = 0, dlugosc_slowa = strlen(original_text);

  for (int i = 0; i < dlugosc_slowa; i++) {
    if (original_text[i] == wylosowana && text[i] == '_') {
      sukces = 1;
      text[i] = wylosowana;
    }
  }
  return sukces;
}

char *play(const char *original_text, const int number_of_players,
           const int turns, int *p_player) {
  int dlugosc_slowa = strlen(original_text);
  char *tekst = malloc((dlugosc_slowa + 1) * sizeof(char));

  for (int i = 0; i < dlugosc_slowa; i++) {
    if (original_text[i] == ' ') {
      tekst[i] = ' ';
    } else {
      tekst[i] = '_';
    }
  }
  tekst[dlugosc_slowa] = '\0';

  for (int i = 0; i < turns; i++) {
    *p_player = (*p_player + 1) % number_of_players;
    while (1) {
      if (guess_a_letter(tekst, original_text) == 0) {
        break;
      } else {
        if (strchr(tekst, '_') == NULL) {
          break;
        }
      }
    }
    if (strchr(tekst, '_') == NULL) {
      break;
    }
  }
  return tekst;
}

int main() {

  const char *texts[MAX_TEXTS] = {"DUTY AND HONOR",
                                  "SUPPORT AND DEFEND",
                                  "SHADOW OF THE DRAGON",
                                  "FULL FORCE AND EFFECT",
                                  "THE TEETH OF THE TIGER",
                                  "CLEAR AND PRESENT DANGER",
                                  "QUO VADIS",
                                  "ADAM MICKIEWICZ",
                                  "ALBERT EINSTEIN",
                                  "DENNIS RITCHIE",
                                  "FIZYKA KWANTOWA",
                                  "PROGRAMOWANIE IMPERATYWNE",
                                  "ALGORYTMY I STRUKTURY DANYCH",
                                  "BRIAN KERNIGHAN",
                                  "COMMAND AUTHORITY",
                                  "POINT OF CONTACT",
                                  "WILLIAM SHAKESPEARE",
                                  "THE BEAR AND THE DRAGON",
                                  "LINE OF DEMARCATION",
                                  "TARGET ACQUIRED"};

  int number_of_players, turns, player = -1;
  unsigned seed;

  scanf("%d %u %d", &number_of_players, &seed, &turns);
  srand(seed);
  const int number = rand() % MAX_TEXTS;
  char *text = play(texts[number], number_of_players, turns, &player);
  printf("%s\n", text);
  printf("%d\n", player);
  free(text);

  return EXIT_SUCCESS;
}
