# Kompendium Notatek: Programowanie Imperatywne (Język C)

## Lekcja 1: Środowisko gcc i podstawy

### Podstawy składni i struktura programu
* Program rozpoczyna się od funkcji `main()`.
* Każda instrukcja musi kończyć się średnikiem `;`.
* Podstawowe typy: `int` (całkowita), `float` (zmiennoprzecinkowa), `bool` (logiczna), `void` (brak typu).
* Zwracanie wartości: jeśli funkcja nie jest `void`, kończymy ją instrukcją `return`.

### Wyświetlanie danych (`printf`)
* Wymaga nagłówka `<stdio.h>`.
* Formatowanie: `%d` (int), `%u` (unsigned int), `%f` (double), `%s` (string/łańcuch), `%X` / `%x` (hex).
* Znaki sterujące: `
` (nowa linia), `	` (tabulator), `\` (wypisanie backslasha).

### Kompilacja
* Narzędzie **gcc**: `gcc -std=c23 -pedantic -Wall -Wextra -o nazwa_pliku kod.c`
* Narzędzie **make**: Służy do automatyzacji kompilacji (wymaga pliku `Makefile`). Przebudowuje tylko te pliki, które uległy zmianie.

---

## Lekcja 2: Typy proste, instrukcje i pętle

### Komentarze i dyrektywy
* Komentarze: `// liniowy` lub `/* blokowy */`.
* Preprocesor: `#define NAZWA wartosc` zastępuje tekst w kodzie. `#if`, `#elif`, `#endif` pozwalają na kompilację warunkową.

### Pętle i instrukcje warunkowe
* Warunki: `if (...) ... else ...`, `switch (zmienna) { case X: ... default: ... }`.
* Pętle: `while (...)`, `do ... while (...)`, `for (inicjacja; warunek; krok)`.
* Skoki: `break`, `continue`, `return`.

### Typy proste i zakresy
* Zależą od implementacji (można sprawdzić makrami w `<limits.h>`, np. `INT_MAX`, `CHAR_MIN`).
* Modyfikatory: `signed` (ze znakiem), `unsigned` (bez znaku), `short`, `long`.
* Liczby zmiennoprzecinkowe: `float` (~7 cyfr), `double` (~15 cyfr), `long double` (~18-21 cyfr).
* Słowo kluczowe `const` tworzy stałą, której nie można nadpisać w kodzie.

### Pobieranie danych (`scanf`)
* Wymaga podania formatu oraz adresów zmiennych (np. `scanf("%d", &zmienna);`).
* Ważne: Po `scanf` warto opróżnić bufor np. `while (getchar() != '
');`.

---

## Lekcja 3: Złożone typy danych

### Typ wyliczeniowy (`enum`)
* Przypisuje wartości całkowite do identyfikatorów.
* Przykład: `enum dni {pn=1, wt, sr, cz, pt, sb, nd=0};`

### Struktury (`struct`)
* Grupują zmienne różnych typów w jednym obiekcie.
* Dostęp do pól: `nazwa_zmiennej.pole`.
* Przykład: `struct punkt {int x; int y;};`

### Tablice i aliasy (`typedef`)
* Deklaracja o stałym rozmiarze: `int tablica[100];`. Indeksowanie zaczyna się od `0`.
* `typedef`: Służy do tworzenia krótszych aliasów dla typów (np. `typedef struct { ... } NowyTyp;`).

---

## Lekcja 4: Wskaźniki

### Adresy i dereferencja
* Każdą zmienną w pamięci można namierzyć za pomocą operatora adresu `&` (np. `&liczba`).
* **Wskaźnik** to zmienna przechowująca adres innej zmiennej. Deklaracja: `int *wsk;`
* **Dereferencja** (wyłuskanie) `*wsk` pozwala odczytać lub zmodyfikować wartość, na którą wskazuje wskaźnik.
* Wskaźnik pusty: `nullptr` lub `NULL`. Wskaźnik uniwersalny: `void *`.

### Wskaźniki a tablice
* Nazwa tablicy to wskaźnik na jej pierwszy element (`tablica == &tablica[0]`).
* Arytmetyka: `wsk+1` przesuwa wskaźnik o rozmiar typu do następnego elementu w pamięci.

### Przekazywanie przez referencję
* Pozwala funkcji na modyfikowanie oryginalnych zmiennych poprzez przyjęcie ich adresów (wskaźników) w parametrach, np. `void zamien(int *a, int *b)`.

---

## Lekcja 5: Dynamiczne zarządzanie pamięcią

Wymaga dołączenia biblioteki `<stdlib.h>`.

### Alokacja (rezerwowanie) pamięci
* `malloc(size)`: Rezerwuje blok pamięci o rozmiarze `size` bajtów. Zawiera "śmieci".
* `calloc(num, size)`: Rezerwuje blok dla `num` elementów o rozmiarze `size`. Zeruje pamięć.
* `realloc(ptr, size)`: Zmienia rozmiar wcześniej zaalokowanego bloku. Zachowuje stare dane.
* Zawsze należy sprawdzić, czy funkcja nie zwróciła `NULL` (brak pamięci).

### Zwalnianie pamięci
* `free(ptr)`: Zwalnia zaalokowaną pamięć. Zapobiega wyciekom pamięci.

---

## Lekcja 6: Przetwarzanie tekstu

### Typy znakowe
* `char` (8 bitów, domyślne kodowanie).
* Posiada nowsze, specyficzne typy dla Unicode (C11/C23): `char8_t`, `char16_t`, `char32_t`, `wchar_t` (wymagają `<uchar.h>`).

### Biblioteka `<string.h>`
* `strcpy`, `strncpy`: Kopiowanie łańcuchów.
* `strcat`, `strncat`: Łączenie (konkatenacja) łańcuchów.
* `strcmp`, `strncmp`: Porównywanie łańcuchów (zwraca `0` gdy są identyczne).
* `strlen`: Obliczanie długości łańcucha (bez znaku ` `).
* `strchr`, `strstr`: Wyszukiwanie znaku / podciągu w tekście.

### Biblioteka `<ctype.h>`
* Funkcje sprawdzające rodzaj znaku: `isalpha` (litera), `isdigit` (cyfra), `isspace` (biały znak), `isalnum` (litera/cyfra).
* Zmiana wielkości liter: `toupper()`, `tolower()`.

---

## Lekcja 7: Strumienie (Operacje na plikach)

### Tryby dostępu
* `r` (odczyt), `w` (zapis, kasuje zawartość), `a` (dopisywanie na końcu).
* Modyfikatory: `b` (binarny), `+` (odczyt i zapis).

### Podstawowe funkcje `<stdio.h>`
* `fopen(nazwa, tryb)`: Otwiera plik, zwraca wskaźnik `FILE *`.
* `fclose(plik)`: Zamyka plik.
* `feof(plik)`: Sprawdza, czy osiągnięto koniec pliku.
* **Odczyt/Zapis znakowy:** `fgetc()`, `fputc()`.
* **Odczyt/Zapis łańcuchów:** `fgets(bufor, rozmiar, plik)`, `fputs()`.
* **Nawigacja w pliku:** `fseek()` (przeskok), `ftell()` (obecna pozycja), `rewind()` (powrót na początek).
* **Pliki binarne:** `fread()`, `fwrite()`.

---

## Lekcja 8: Tablice wielowymiarowe

### Dynamiczna alokacja
1. **Płaska tablica 1D jako 2D:**
   `int *dane = malloc(wiersze * kolumny * sizeof(int));`
   Dostęp za pomocą obliczania indeksu: `dane[w * kolumny + k]`.
2. **Tablica 2D o znanym rozmiarze kolumn:**
   `int (*dane)[20] = malloc(wiersze * 20 * sizeof(int));`
3. **Tablica wskaźników do tablic 1D (najbardziej elastyczna):**
   Najpierw alokujemy tablicę wskaźników (`int **dane`), a w pętli dla każdego wskaźnika alokujemy wiersz. 
   Przy zwalnianiu trzeba użyć pętli, aby zwolnić każdy wiersz przed zwolnieniem głównej tablicy.

---

## Lekcja 9: Funkcje wariadyczne i argumenty `main`

### Argumenty programu (w `main`)
* `int main(int argc, char *argv[])`
* `argc`: Liczba argumentów (zawsze $\ge 1$).
* `argv`: Tablica łańcuchów. `argv[0]` to nazwa uruchomionego programu, `argv[1]` to pierwszy argument, itd.

### Funkcje wariadyczne (zmienna liczba argumentów)
* Wymagają nagłówka `<stdarg.h>`.
* Deklaracja: `int funkcja(int staly_arg, ...)`
* Obsługa za pomocą typu `va_list` oraz makr:
    * `va_start(lista, ostatni_staly_arg)`: Inicjalizuje listę.
    * `va_arg(lista, typ)`: Pobiera kolejny argument.
    * `va_end(lista)`: Sprząta listę po użyciu.

### Funkcje bez powrotu
* Funkcja `exit(status)` z `<stdlib.h>` natychmiast kończy program (status `EXIT_SUCCESS` lub `EXIT_FAILURE`).

---

## Lekcja 10: Funkcje rekurencyjne i biblioteki

### Rekurencja
* **Rekurencja prosta:** Funkcja wywołuje samą siebie. Zależnie od warunku bazowego zatrzymuje się. Odkłada każdy stan na stos wywołań.
* **Rekurencja ogonowa:** Ostatnią operacją funkcji jest wywołanie samej siebie, a wynik jest od razu przekazywany wyżej (wymaga dodatkowego parametru przechowującego stan/wynik). Często kompilator potrafi to zoptymalizować do zwykłej pętli, oszczędzając pamięć stosu.
* **Rekurencja wzajemna:** Funkcja A wywołuje funkcję B, a funkcja B wywołuje funkcję A. (Wymaga wstępnych deklaracji funkcji - tzw. nagłówków w kodzie).

### Biblioteki
1. **Biblioteki statyczne (`.a`)**
    * Kompilacja: `gcc -c plik.c -o plik.o`
    * Pakowanie narzędziem `ar`: `ar rcs libmojabibl.a plik.o`
    * Użycie: `gcc main.c -L. -lmojabibl -o program`
2. **Biblioteki dynamiczne (`.so`)**
    * Kompilacja: `gcc -fPIC -c plik.c -o plik.o`
    * Tworzenie współdzielonego obiektu: `gcc -shared -o libmojabibl.so plik.o`
    * Użycie: `gcc main.c -L. -lmojabibl -o program` (często wymaga eksportu zmiennej środowiskowej `LD_LIBRARY_PATH`).

```markdown
### Pomiar czasu w języku C

Aby zmierzyć czas wykonywania fragmentu kodu, należy użyć biblioteki `<time.h>`.

* **`#include <time.h>`** – nagłówek dla funkcji obsługi czasu.
* **`clock_t clock();`** – zwraca aktualny czas procesora.
* **`CLOCKS_PER_SEC`** – makro określające liczbę jednostek funkcji `clock()` na sekundę.

**Przykład użycia:**
```c
#include <time.h>

// Rozpoczęcie pomiaru
clock_t czas_start = clock();

// ... (tutaj kod, którego czas wykonania chcemy zmierzyć) ...

// Zakończenie pomiaru
clock_t czas_stop = clock();

// Obliczenie czasu wykonania w sekundach
double czas_wykonania = ((double) czas_stop - czas_start) / CLOCKS_PER_SEC;
