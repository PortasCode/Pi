#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_LEN 64
#define MAX_IDS 1024
#define MAX_LINE 128

char identifiers[MAX_IDS][MAX_ID_LEN];

const char *keywords[] = {"auto",     "break",   "case",   "char",     "const",
                          "continue", "default", "do",     "double",   "else",
                          "enum",     "extern",  "float",  "for",      "goto",
                          "if",       "int",     "long",   "register", "return",
                          "short",    "signed",  "sizeof", "static",   "struct",
                          "switch",   "typedef", "union",  "unsigned", "void",
                          "volatile", "while"};

// Funkcja pomocnicza do omijania stringów i znaków z uwzględnieniem znaków
// ucieczki '\'
void skip_string_or_char(char terminator) {
  int c;
  int prev_c = 0;
  while ((c = getchar()) != EOF) {
    if (c == terminator && prev_c != '\\')
      break;
    // Jeśli mamy podwójny backslash, np. "\\", to on się nawzajem anuluje
    if (prev_c == '\\' && c == '\\')
      prev_c = 0;
    else
      prev_c = c;
  }
}

void find_comments(int *line_comment_counter, int *block_comment_counter) {
  int c, flaga = 0, poprzedni_znak = 0;
  *line_comment_counter = 0;
  *block_comment_counter = 0;

  while ((c = getchar()) != EOF) {
    if (flaga == 0) {
      if (c == '/') {
        c = getchar();
        if (c == '/') {
          (*line_comment_counter)++;
          while ((c = getchar()) != '\n' && c != EOF) {
          }
        } else if (c == '*') {
          (*block_comment_counter)++;
          flaga = 1;
          poprzedni_znak = 0;
        } else {
          if (c != EOF)
            ungetc(c, stdin); // Naprawa: zwracanie znaku do strumienia
        }
      } else if (c == '"') { // Naprawa: ignorowanie napisów
        skip_string_or_char('"');
      } else if (c == '\'') { // Naprawa: ignorowanie znaków
        skip_string_or_char('\'');
      }
    } else {
      if (c == '/' && poprzedni_znak == '*') {
        flaga = 0;
      }
      poprzedni_znak = c;
    }
  }
}

int find_idents(void) {
  char slowo[MAX_ID_LEN];
  int c, flaga = 0, poprzedni_znak = 0;
  int current = 0, result = 0;

  while ((c = getchar()) != EOF) {
    if (flaga == 0) { // Poza komentarzem blokowym
      if (c == '/') {
        c = getchar();
        if (c == '/') {
          while ((c = getchar()) != '\n' && c != EOF) {
          }
        } else if (c == '*') {
          flaga = 1;
          poprzedni_znak = 0;
        } else {
          if (c != EOF)
            ungetc(c, stdin);
        }
      } else if (c == '"') {
        skip_string_or_char('"'); // Ulepszone omijanie (escapy)
      } else if (c == '\'') {
        skip_string_or_char('\'');
      } else if (isalpha(c) || c == '_') { // Naprawa: Ten blok musi być TU!
                                           // (wewnątrz flaga == 0)
        slowo[0] = (char)c;
        current = 1;

        while ((c = getchar()) != EOF && (isalnum(c) || c == '_')) {
          if (current < MAX_ID_LEN - 1) { // Zabezpieczenie przed przepełnieniem
            slowo[current] = (char)c;
            current++;
          }
        }
        slowo[current] = '\0';

        // Trzeba oddać ostatni wczytany znak, bo należy już do czegoś innego
        if (c != EOF)
          ungetc(c, stdin);

        int liczba_keywords = sizeof(keywords) / sizeof(keywords[0]);
        int czy_keyword = 0;

        for (int i = 0; i < liczba_keywords; i++) {
          if (strcmp(slowo, keywords[i]) == 0) {
            czy_keyword = 1;
            break;
          }
        }

        if (czy_keyword == 0) {
          int czy_bylo = 0;
          for (int i = 0; i < result; i++) {
            if (strcmp(slowo, identifiers[i]) == 0) {
              czy_bylo = 1;
              break;
            }
          }
          if (czy_bylo == 0 && result < MAX_IDS) {
            strcpy(identifiers[result], slowo);
            result++;
          }
        }
      }
    } else { // Wewnątrz komentarza blokowego (flaga == 1)
      if (c == '/' && poprzedni_znak == '*') {
        flaga = 0;
      }
      poprzedni_znak = c;
    }
  }
  return result;
}

int read_int() {
  char line[MAX_LINE];
  if (fgets(line, MAX_LINE, stdin) == NULL)
    return 0;
  return (int)strtol(line, NULL, 10);
}

int main(void) {
  int line_comment_counter, block_comment_counter;
  const int to_do = read_int();
  switch (to_do) {
  case 1:
    find_comments(&line_comment_counter, &block_comment_counter);
    printf("%d %d\n", block_comment_counter, line_comment_counter);
    break;
  case 2:
    printf("%d\n", find_idents());
    break;
  default:
    printf("NOTHING TO DO FOR %d\n", to_do);
    break;
  }
  return 0;
}
