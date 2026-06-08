# Notatki do nauki: Pierwsze kroki w GCC i programowanie w C
**Akademia Górniczo-Hutnicza – Programowanie Imperatywne**

---

## SPIS TREŚCI

1. Zmienne i typy danych
2. Instrukcje sterujące (warunki i pętle)
3. Funkcje w języku C
4. Funkcja `printf` i formatowanie wyjścia
5. Kompilacja programu za pomocą GCC
6. Narzędzie `make` i plik Makefile – projekt jednoplikowy
7. Makefile dla wielu plików źródłowych
8. Rozbudowany Makefile z biblioteką statyczną i testami
9. Pliki nagłówkowe (`.h`) i podział projektu
10. Generator liczb pierwszych – praktyczny przykład

---

## TEMAT 1 – Zmienne i typy danych

### Teoria

Zmienna to nazwane miejsce w pamięci komputera, gdzie program może przechowywać wartość.
W języku C **każda zmienna musi mieć zadeklarowany typ przed użyciem** – kompilator musi
wiedzieć z góry, ile miejsca w pamięci zarezerwować i jak interpretować zapisane bajty.

Deklaracja bez wartości początkowej rezerwuje miejsce, ale zostawia w nim „śmieci" (losową
wartość z pamięci). Dlatego zawsze warto inicjalizować zmienne przy deklaracji.

Podstawowe typy:
- `int` – liczba całkowita ze znakiem (np. -5, 0, 42)
- `float` – liczba zmiennoprzecinkowa pojedynczej precyzji (ok. 7 cyfr znaczących)
- `double` – liczba zmiennoprzecinkowa podwójnej precyzji (ok. 15 cyfr znaczących)
- `bool` – wartość logiczna: `true` (prawda) lub `false` (fałsz), wymaga `<stdbool.h>`
- `void` – brak wartości (używany w sygnaturach funkcji)

### Kompletny kod z komentarzami

```c
#include <stdio.h>      /* dołączamy bibliotekę wejścia/wyjścia (potrzebna do printf) */
#include <stdbool.h>    /* dołączamy obsługę typu bool (true/false) */

int main(void) {

    /* --- DEKLARACJA BEZ INICJALIZACJI --- */
    int a;              /* zmienna całkowita – zawiera losowe "śmieci" z pamięci */
    a = 10;             /* dopiero tutaj nadajemy wartość */

    /* --- DEKLARACJA Z INICJALIZACJĄ (preferowany styl) --- */
    int b = 20;         /* zmienna całkowita od razu z wartością 20 */
    float pi = 3.14f;   /* zmienna zmiennoprzecinkowa; 'f' na końcu oznacza typ float */
    double dokladne = 3.14159265358979; /* double – większa precyzja, bez 'f' */
    bool prawda = true;     /* wartość logiczna – prawda */
    bool falsz = false;     /* wartość logiczna – fałsz */

    /* --- OPERACJE ARYTMETYCZNE --- */
    int suma = a + b;       /* dodawanie */
    int roznica = b - a;    /* odejmowanie */
    int iloczyn = a * b;    /* mnożenie */
    int iloraz = b / a;     /* dzielenie całkowite – wynik to liczba całkowita! */
    int reszta = b % a;     /* reszta z dzielenia (modulo) */

    /* --- WYŚWIETLENIE WYNIKÓW --- */
    printf("a = %d\n", a);                  /* %d – liczba całkowita dziesiętna */
    printf("b = %d\n", b);
    printf("pi = %f\n", pi);               /* %f – liczba zmiennoprzecinkowa */
    printf("dokladne = %lf\n", dokladne);  /* %lf – double (lf = long float) */
    printf("prawda = %d\n", prawda);       /* bool wyświetlamy jako int: 1=true, 0=false */
    printf("suma = %d\n", suma);
    printf("roznica = %d\n", roznica);
    printf("iloczyn = %d\n", iloczyn);
    printf("iloraz = %d\n", iloraz);
    printf("reszta = %d\n", reszta);

    return 0; /* zwracamy 0 – oznacza poprawne zakończenie programu */
}
```

### Przykład – co program wypisze

```
a = 10
b = 20
pi = 3.140000
dokladne = 3.141593
prawda = 1
suma = 30
roznica = 10
iloczyn = 200
iloraz = 2
reszta = 0
```

### Typowe błędy i jak ich unikać

**Błąd 1: Użycie niezainicjalizowanej zmiennej**
```c
int x;
printf("%d\n", x);  /* BŁĄD: x ma losową wartość z pamięci */
```
Jak unikać: zawsze inicjalizuj zmienne przy deklaracji: `int x = 0;`

**Błąd 2: Dzielenie całkowite zamiast zmiennoprzecinkowego**
```c
int a = 7, b = 2;
float wynik = a / b;    /* BŁĄD: wynik = 3.0, a nie 3.5 */
                         /* bo a/b to dzielenie całkowite! */
float poprawnie = (float)a / b;  /* OK: rzutowanie a na float przed dzieleniem */
```

**Błąd 3: Użycie `bool` bez nagłówka**
```c
bool x = true;  /* BŁĄD bez #include <stdbool.h> */
```
Jak unikać: zawsze dołączaj `#include <stdbool.h>` gdy używasz `bool`.

**Błąd 4: Literał float bez `f`**
```c
float pi = 3.14;   /* Ostrzeżenie: 3.14 to double, przypisywany do float */
float pi = 3.14f;  /* OK: literał float */
```

---

## TEMAT 2 – Instrukcje sterujące (warunki i pętle)

### Teoria

Instrukcje sterujące pozwalają programowi „podejmować decyzje" i „powtarzać czynności":

- **`if/else`** – wykonaj coś tylko jeśli warunek jest spełniony
- **`while`** – powtarzaj dopóki warunek jest prawdziwy (sprawdza PRZED wykonaniem)
- **`do...while`** – powtarzaj dopóki warunek jest prawdziwy (sprawdza PO wykonaniu, więc ciało wykona się co najmniej raz)
- **`for`** – powtarzaj określoną liczbę razy (z licznikiem)

Warunek to wyrażenie, które daje wynik `true` (niezerowy) lub `false` (zero).
W C każda liczba różna od 0 jest traktowana jako `true`, a 0 jako `false`.

### Kompletny kod z komentarzami

```c
#include <stdio.h>

int main(void) {

    int liczba = 7; /* liczba do sprawdzenia */

    /* ============================================
       INSTRUKCJA IF / ELSE IF / ELSE
       ============================================ */

    if (liczba > 0) {                       /* jeśli liczba jest większa od 0 */
        printf("%d jest dodatnia\n", liczba);
    } else if (liczba < 0) {                /* w przeciwnym razie, jeśli mniejsza od 0 */
        printf("%d jest ujemna\n", liczba);
    } else {                                /* w pozostałych przypadkach (liczba == 0) */
        printf("liczba wynosi zero\n");
    }

    /* Sprawdzenie parzystości – operator % daje resztę z dzielenia */
    if (liczba % 2 == 0) {                  /* jeśli reszta z dzielenia przez 2 wynosi 0 */
        printf("%d jest parzysta\n", liczba);
    } else {
        printf("%d jest nieparzysta\n", liczba);
    }

    /* ============================================
       PĘTLA WHILE
       Używana gdy nie wiemy z góry ile razy pętla się wykona
       ============================================ */

    int i = 1;                  /* inicjalizujemy licznik przed pętlą */
    printf("while: ");
    while (i <= 5) {            /* powtarzaj dopóki i jest <= 5 */
        printf("%d ", i);       /* wyświetl aktualną wartość i */
        i++;                    /* zwiększ i o 1 (i++ to skrót od i = i + 1) */
    }
    printf("\n");               /* nowa linia po zakończeniu pętli */

    /* ============================================
       PĘTLA DO...WHILE
       Ciało wykonuje się ZAWSZE co najmniej raz,
       bo warunek sprawdzany jest na końcu
       ============================================ */

    int j = 1;
    printf("do-while: ");
    do {
        printf("%d ", j);       /* wyświetl j */
        j++;                    /* zwiększ j */
    } while (j <= 5);           /* sprawdź warunek PO wykonaniu ciała */
    printf("\n");

    /* ============================================
       PĘTLA FOR
       Używana gdy wiemy dokładnie ile razy ma się wykonać
       Składnia: for(inicjacja; warunek; krok)
       ============================================ */

    printf("for: ");
    for (int k = 1; k <= 5; k++) { /* k zaczyna od 1, rośnie o 1, pętla trwa gdy k<=5 */
        printf("%d ", k);
    }
    printf("\n");

    /* ============================================
       ZAGNIEŻDŻONE PĘTLE – tabliczka mnożenia 3x3
       ============================================ */

    printf("Tabliczka mnozenia 3x3:\n");
    for (int wiersz = 1; wiersz <= 3; wiersz++) {      /* zewnętrzna pętla = wiersze */
        for (int kol = 1; kol <= 3; kol++) {           /* wewnętrzna pętla = kolumny */
            printf("%4d", wiersz * kol);               /* %4d = co najmniej 4 znaki szerokości */
        }
        printf("\n");   /* nowa linia po każdym wierszu */
    }

    return 0;
}
```

### Przykład – co program wypisze

```
7 jest dodatnia
7 jest nieparzysta
while: 1 2 3 4 5 
do-while: 1 2 3 4 5 
for: 1 2 3 4 5 
Tabliczka mnozenia 3x3:
   1   2   3
   2   4   6
   3   6   9
```

### Typowe błędy i jak ich unikać

**Błąd 1: Pętla nieskończona – zapomnienie o inkrementacji**
```c
int i = 0;
while (i < 5) {
    printf("%d\n", i);
    /* BŁĄD: brak i++, pętla nigdy się nie skończy! */
}
```

**Błąd 2: Użycie `=` zamiast `==` w warunku**
```c
if (x = 5) {   /* BŁĄD: to przypisanie, nie porównanie! x zostaje ustawione na 5 */
if (x == 5) {  /* OK: porównanie */
```
Jak unikać: pisz stałą po lewej stronie: `if (5 == x)` – kompilator zgłosi błąd przy `=`.

**Błąd 3: Średnik po `for` lub `while`**
```c
for (int i = 0; i < 5; i++);   /* BŁĄD: średnik tworzy pustą pętlę */
{
    printf("%d\n", i);          /* ten blok wykona się TYLKO RAZ po pętli */
}
```

**Błąd 4: Brak nawiasów klamrowych przy wielu instrukcjach**
```c
if (x > 0)
    printf("dodatnia\n");
    printf("na pewno\n");   /* BŁĄD: ta linia zawsze się wykona, nie jest częścią if! */
```
Jak unikać: zawsze używaj `{}`, nawet dla jednej instrukcji.

---

## TEMAT 3 – Funkcje w języku C

### Teoria

Funkcja to nazwany blok kodu, który wykonuje określone zadanie. Pozwala:
- **unikać powtarzania kodu** – piszesz raz, używasz wiele razy,
- **podzielić program na mniejsze, czytelne kawałki**,
- **testować poszczególne części oddzielnie**.

Każda funkcja ma:
- **typ zwracanej wartości** – co funkcja zwraca (`int`, `float`, `void` = nic)
- **nazwę** – jak się ją wywołuje
- **parametry** – dane wejściowe (może ich nie być – wtedy piszemy `void`)
- **ciało** – blok instrukcji w klamrach `{}`
- **instrukcję `return`** – co zwraca (nie ma jej gdy typ to `void`)

Program zawsze zaczyna się od funkcji `main()`.

**Ważna zasada:** funkcja musi być zadeklarowana lub zdefiniowana PRZED jej pierwszym
użyciem. Jeśli definicja jest niżej w pliku niż wywołanie, potrzebna jest **deklaracja zapowiadająca**
(prototyp) na górze pliku.

### Kompletny kod z komentarzami

```c
#include <stdio.h>

/* ============================================
   PROTOTYPY (deklaracje zapowiadające)
   Informują kompilator o istnieniu funkcji
   zanim je zdefiniujemy poniżej main()
   ============================================ */
int dodaj(int a, int b);
int odejmij(int a, int b);
int pomnoz(int a, int b);
float podziel(float a, float b);
int potega(int podstawa, int wykladnik);
int jest_parzysta(int n);        /* zwraca 1 (prawda) lub 0 (fałsz) */
void wypisz_linie(int dlugosc);  /* void – nie zwraca wartości */

/* ============================================
   FUNKCJA GŁÓWNA
   ============================================ */
int main(void) {

    int x = 12;
    int y = 4;

    /* Wywołanie funkcji – wynik trafia do zmiennej */
    int wynik_dodawania = dodaj(x, y);
    printf("%d + %d = %d\n", x, y, wynik_dodawania);

    /* Wywołanie funkcji bezpośrednio w printf */
    printf("%d - %d = %d\n", x, y, odejmij(x, y));
    printf("%d * %d = %d\n", x, y, pomnoz(x, y));
    printf("%d / %d = %.2f\n", x, y, podziel((float)x, (float)y));
    /* %.2f – wyświetl z dokładnością do 2 miejsc po przecinku */

    printf("2^10 = %d\n", potega(2, 10));

    /* Użycie funkcji zwracającej bool (0 lub 1) w warunku */
    if (jest_parzysta(x)) {
        printf("%d jest parzysta\n", x);
    } else {
        printf("%d jest nieparzysta\n", x);
    }

    /* Wywołanie funkcji void – tylko wykonuje działanie, nic nie zwraca */
    wypisz_linie(20);

    return 0;
}

/* ============================================
   DEFINICJE FUNKCJI
   ============================================ */

/* Zwraca sumę dwóch liczb całkowitych */
int dodaj(int a, int b) {
    return a + b;   /* wartość po return trafia do miejsca wywołania */
}

/* Zwraca różnicę dwóch liczb całkowitych */
int odejmij(int a, int b) {
    return a - b;
}

/* Zwraca iloczyn dwóch liczb całkowitych */
int pomnoz(int a, int b) {
    return a * b;
}

/* Zwraca iloraz dwóch liczb zmiennoprzecinkowych */
float podziel(float a, float b) {
    if (b == 0.0f) {        /* sprawdzamy czy nie dzielimy przez zero */
        printf("BLAD: dzielenie przez zero!\n");
        return 0.0f;         /* zwracamy 0 jako wartość błędu */
    }
    return a / b;
}

/* Oblicza podstawa^wykladnik dla nieujemnych wykładników */
int potega(int podstawa, int wykladnik) {
    int wynik = 1;                          /* wynik startuje od 1 */
    for (int i = 0; i < wykladnik; i++) {   /* mnożymy wykladnik razy */
        wynik = wynik * podstawa;
    }
    return wynik;
}

/* Sprawdza czy liczba jest parzysta, zwraca 1 (tak) lub 0 (nie) */
int jest_parzysta(int n) {
    return n % 2 == 0;  /* wyrażenie daje 1 (true) lub 0 (false) */
}

/* Wypisuje linię złożoną z myślników – nie zwraca żadnej wartości */
void wypisz_linie(int dlugosc) {
    for (int i = 0; i < dlugosc; i++) {
        printf("-");    /* wypisz jeden myślnik */
    }
    printf("\n");       /* zakończ nową linią */
    /* brak return – funkcja void kończy się automatycznie */
}
```

### Przykład – co program wypisze

```
12 + 4 = 16
12 - 4 = 8
12 * 4 = 48
12 / 4 = 3.00
2^10 = 1024
12 jest parzysta
--------------------
```

### Typowe błędy i jak ich unikać

**Błąd 1: Brak prototypu gdy definicja jest po `main()`**
```c
int main(void) {
    int w = dodaj(3, 4);  /* BŁĄD: kompilator nie wie jeszcze co to dodaj() */
}
int dodaj(int a, int b) { return a + b; }
```
Jak unikać: dodaj prototyp `int dodaj(int a, int b);` przed `main()`.

**Błąd 2: Brak `return` w funkcji niezerowej**
```c
int dodaj(int a, int b) {
    int wynik = a + b;
    /* BŁĄD: brak return wynik; – kompilator może ostrzec lub zachowanie jest nieokreślone */
}
```

**Błąd 3: Próba zwrócenia wartości z funkcji `void`**
```c
void wypisz(void) {
    return 5;   /* BŁĄD: void nie może zwracać wartości */
}
```

**Błąd 4: Modyfikacja parametru nie zmienia oryginalnej zmiennej**
```c
void podwoj(int x) { x = x * 2; }   /* modyfikuje lokalną kopię! */
int main(void) {
    int a = 5;
    podwoj(a);
    printf("%d\n", a);   /* wypisze 5, a nie 10 – a się nie zmieniło */
}
```
Jak unikać: zwróć wartość przez `return` lub użyj wskaźników (temat na później).

---

## TEMAT 4 – Funkcja `printf` i formatowanie wyjścia

### Teoria

`printf` to funkcja z biblioteki standardowej C (`<stdio.h>`), służąca do wyświetlania tekstu
i wartości w konsoli. Jej nazwa pochodzi od *print formatted* (drukuj sformatowany).

Pierwszy argument to **ciąg formatujący** – tekst, w którym specjalne sekwencje zaczynające się
od `%` są zamieniane na wartości kolejnych argumentów.

Format specyfikatora: `%[szerokość][.precyzja]typ`

Tabela specyfikatorów:

| Specyfikator | Typ             | Opis                                     |
|:---:|:---:|:---|
| `%d`         | `int`           | Liczba całkowita dziesiętna ze znakiem   |
| `%u`         | `unsigned int`  | Liczba całkowita bez znaku               |
| `%f`         | `float/double`  | Liczba zmiennoprzecinkowa (domyślnie 6 miejsc) |
| `%e`         | `float/double`  | Zapis naukowy, małe litery (np. 1.5e+02) |
| `%E`         | `float/double`  | Zapis naukowy, wielkie litery (np. 1.5E+02) |
| `%lf`        | `double`        | Double (w scanf wymagane, w printf opcjonalne) |
| `%s`         | `char*`         | Łańcuch tekstowy                         |
| `%c`         | `char`          | Pojedynczy znak                          |
| `%x`         | `int`           | Szesnastkowy, małe litery (np. ff)       |
| `%X`         | `int`           | Szesnastkowy, wielkie litery (np. FF)    |
| `%o`         | `int`           | Ósemkowy (oktalny)                       |
| `%%`         | –               | Dosłowny znak procenta                   |

### Kompletny kod z komentarzami

```c
#include <stdio.h>

int main(void) {

    /* ============================================
       PODSTAWOWE SPECYFIKATORY
       ============================================ */
    int calkowita = 255;
    float zmiennoprzecinkowa = 3.14159f;
    double dokladna = 123456.789012345;
    char znak = 'A';
    char tekst[] = "Hello";   /* tablica znaków (napis) */

    printf("Calkowita: %d\n", calkowita);
    printf("Zmiennoprzecinkowa: %f\n", zmiennoprzecinkowa); /* domyślnie 6 miejsc po . */
    printf("Dokladna double: %lf\n", dokladna);
    printf("Znak: %c\n", znak);
    printf("Tekst: %s\n", tekst);

    /* ============================================
       RÓŻNE SYSTEMY LICZBOWE
       ============================================ */
    printf("\n--- Systemy liczbowe dla liczby 255 ---\n");
    printf("Dziesietny:    %d\n", calkowita);   /* 255 */
    printf("Szesnastkowy:  %x\n", calkowita);   /* ff  */
    printf("Szesnastkowy:  %X\n", calkowita);   /* FF  */
    printf("Osemkowy:      %o\n", calkowita);   /* 377 */

    /* ============================================
       KONTROLA SZEROKOŚCI I PRECYZJI
       Szerokość: minimalna liczba znaków zajmowana przez wartość
       Precyzja:  liczba cyfr po przecinku (dla %f)
       ============================================ */
    printf("\n--- Kontrola formatu ---\n");
    printf("[%10d]\n", 42);     /* 10 znaków, wyrównanie do prawej (domyślne) */
    printf("[%-10d]\n", 42);    /* 10 znaków, wyrównanie do lewej (minus przed szer.) */
    printf("[%010d]\n", 42);    /* uzupełnij zerami z lewej strony */
    printf("[%.2f]\n", zmiennoprzecinkowa);    /* 2 miejsca po przecinku */
    printf("[%10.3f]\n", zmiennoprzecinkowa); /* 10 znaków total, 3 po przecinku */
    printf("[%-10.3f]\n", zmiennoprzecinkowa);/* j.w. ale wyrównanie do lewej */

    /* ============================================
       ZAPIS NAUKOWY
       ============================================ */
    printf("\n--- Zapis naukowy ---\n");
    double wielka = 1234567.89;
    double mala = 0.000001234;
    printf("Zapis naukowy (maly): %e\n", wielka);   /* 1.234568e+06 */
    printf("Zapis naukowy (duzy): %E\n", wielka);   /* 1.234568E+06 */
    printf("Mala liczba: %e\n", mala);               /* 1.234000e-06 */

    /* ============================================
       ZNAKI SPECJALNE (SEKWENCJE UCIECZKI)
       ============================================ */
    printf("\n--- Znaki specjalne ---\n");
    printf("Nowa linia: linia1\nlinia2\n");   /* \n – nowa linia */
    printf("Tabulator:\tkolumna2\n");          /* \t – tabulator poziomy */
    printf("Cudzyslow: \"cytowany tekst\"\n"); /* \" – dosłowny cudzysłów */
    printf("Backslash: \\\n");                 /* \\ – dosłowny backslash */
    printf("Procent: 100%%\n");                /* %% – dosłowny procent */

    /* ============================================
       WIELE ARGUMENTÓW W JEDNYM PRINTF
       ============================================ */
    printf("\n--- Wiele argumentow ---\n");
    int a = 5, b = 3;
    printf("%d + %d = %d, %d - %d = %d\n", a, b, a+b, a, b, a-b);
    /* Kolejność: każde %... jest wypełniane kolejnym argumentem */

    return 0;
}
```

### Przykład – co program wypisze

```
Calkowita: 255
Zmiennoprzecinkowa: 3.141590
Dokladna double: 123456.789012
Znak: A
Tekst: Hello

--- Systemy liczbowe dla liczby 255 ---
Dziesietny:    255
Szesnastkowy:  ff
Szesnastkowy:  FF
Osemkowy:      377

--- Kontrola formatu ---
[        42]
[42        ]
[0000000042]
[3.14]
[     3.142]
[3.142     ]

--- Zapis naukowy ---
Zapis naukowy (maly): 1.234568e+06
Zapis naukowy (duzy): 1.234568E+06
Mala liczba: 1.234000e-06

--- Znaki specjalne ---
Nowa linia: linia1
linia2
Tabulator:	kolumna2
Cudzyslow: "cytowany tekst"
Backslash: \
Procent: 100%

--- Wiele argumentow ---
5 + 3 = 8, 5 - 3 = 2
```

### Typowe błędy i jak ich unikać

**Błąd 1: Zły specyfikator dla danego typu**
```c
float x = 3.14f;
printf("%d\n", x);   /* BŁĄD: %d oczekuje int, dostaje float – wypisze śmieciową wartość */
printf("%f\n", x);   /* OK */
```

**Błąd 2: Za mało lub za dużo argumentów**
```c
printf("%d i %d\n", 5);         /* BŁĄD: brakuje drugiego argumentu */
printf("%d\n", 5, "extra");     /* ostrzeżenie: za dużo argumentów */
```

**Błąd 3: Zapomnienie `\n` na końcu**
```c
printf("Wynik: %d", wynik);     /* brak nowej linii – kolejny printf będzie w tej samej linii */
printf("Wynik: %d\n", wynik);   /* OK */
```

**Błąd 4: Użycie `%f` dla `int` zamiast `%d`**
```c
int liczba = 42;
printf("%f\n", liczba);    /* BŁĄD: wypisze 0.000000 lub śmieci */
printf("%d\n", liczba);    /* OK */
```

---

## TEMAT 5 – Kompilacja programu za pomocą GCC

### Teoria

GCC (GNU Compiler Collection) to kompilator zamieniający kod źródłowy C na program wykonywalny.
Proces przebiega w kilku etapach:
1. **Preprocessing** – przetwarzanie dyrektyw `#include`, `#define` itp.
2. **Kompilacja** – tłumaczenie C na asembler
3. **Asemblacja** – tłumaczenie asemblera na kod maszynowy (plik `.o`)
4. **Linkowanie** – łączenie plików `.o` z bibliotekami w jeden plik wykonywalny

Flagi kompilatora używane w kursie:
- `-std=c23` – użyj standardu C23 (najnowszy; alternatywnie: c11, c99)
- `-pedantic` – ścisłe przestrzeganie standardu
- `-Werror=pedantic` – ostrzeżenia pedantic traktuj jako błędy
- `-Wall` – włącz wszystkie ważne ostrzeżenia
- `-Wextra` – włącz dodatkowe ostrzeżenia
- `-o nazwa` – określ nazwę pliku wyjściowego
- `-c` – tylko kompiluj (nie linkuj), generuje plik `.o`
- `-lm` – linkuj z biblioteką matematyczną (potrzebna do `sqrt`, `pow` itp.)

### Kompletny kod z komentarzami (hello.c)

```c
/* Plik: hello.c
   Cel: najprostszy program w C do nauki kompilacji GCC */

#include <stdio.h>      /* nagłówek biblioteki standardowej wejścia/wyjścia */

/* Funkcja main – punkt startowy każdego programu w C */
int main(void) {        /* void w nawiasach oznacza: brak argumentów */

    /* printf wyświetla tekst w konsoli */
    /* \n to znak nowej linii – bez niego kursor zostanie w tej samej linii */
    printf("Hello World\n");

    /* return 0 informuje system operacyjny że program zakończył się pomyślnie */
    /* Wartość inna niż 0 oznacza błąd */
    return 0;
}
```

### Polecenia kompilacji i uruchomienia

```bash
# Krok 1: utwórz folder projektu
mkdir Projekt01
cd Projekt01

# Krok 2: utwórz plik hello.c (wpisz kod z góry w edytorze, np. nano)
nano hello.c

# Krok 3: skompiluj plik
gcc -std=c23 -pedantic -Werror=pedantic -Wall -Wextra -o hello hello.c
#   ↑ kompilator
#              ↑ standard C23
#                       ↑ ścisłe przestrzeganie standardu
#                                         ↑ pedantic jako błąd
#                                                    ↑ wszystkie ważne ostrzeżenia
#                                                          ↑ dodatkowe ostrzeżenia
#                                                                 ↑ nazwa pliku wyjściowego
#                                                                    ↑ nazwa wynikowego pliku
#                                                                           ↑ plik źródłowy

# Krok 4: uruchom program
./hello
# ./ oznacza "w bieżącym folderze"
```

### Co kompilator wypisze przy błędzie

Przykład błędu – zapomniano `return 0;` i piszemy `Return 0;` (wielka litera):

```
hello.c:7:5: error: 'Return' undeclared (first use in this function)
    7 |     Return 0;
      |     ^~~~~~
```

Interpretacja: plik `hello.c`, linia 7, kolumna 5, błąd: `Return` nie jest zadeklarowane.

### Co wypisze program

```
Hello World
```

### Typowe błędy i jak ich unikać

**Błąd 1: Brak pliku nagłówkowego**
```c
/* brak #include <stdio.h> */
int main(void) {
    printf("test\n");  /* BŁĄD: printf nie jest znany */
}
```
Kompilator: `warning: implicit declaration of function 'printf'`

**Błąd 2: Uruchomienie bez `./`**
```bash
hello        # BŁĄD na wielu systemach: "command not found"
./hello      # OK: szukaj programu "hello" w bieżącym folderze
```

**Błąd 3: Kompilacja z błędem – próba uruchomienia starego pliku**
Jeśli kompilacja się nie powiodła, plik wykonywalny nie zostaje zaktualizowany.
Uruchamiasz wtedy starą wersję. Sprawdź, czy kompilacja zakończyła się bez błędów.

**Błąd 4: Brak `-lm` przy użyciu funkcji matematycznych**
```bash
gcc -o program program.c          # BŁĄD: undefined reference to 'sqrt'
gcc -o program program.c -lm      # OK: linkujemy bibliotekę matematyczną
```

---

## TEMAT 6 – Narzędzie `make` i plik Makefile – projekt jednoplikowy

### Teoria

`make` to narzędzie automatyzujące kompilację. Zamiast wpisywać długie polecenie gcc za każdym
razem, definiujesz reguły w pliku `Makefile`, a potem piszesz tylko `make`.

Kluczowa zaleta: `make` **kompiluje tylko te pliki, które zostały zmienione** po ostatniej
kompilacji. Oszczędza czas przy dużych projektach.

Struktura pliku Makefile:
```
cel: zależności
[TAB]polecenie
```
**Uwaga krytyczna:** przed poleceniem MUSI być znak tabulacji (TAB), nie spacje!

Zmienne w Makefile: `NAZWA = wartość`, używane jako `$(NAZWA)`.

Cel `clean` to konwencja do usuwania plików wynikowych (nie jest plikiem, więc deklarujemy
go jako `.PHONY` w zaawansowanych plikach).

### Kompletny kod

**Plik: hello.c**
```c
#include <stdio.h>      /* nagłówek printf */

int main(void) {
    printf("Hello World!\n");   /* wypisz powitanie */
    return 0;                   /* zakończ program pomyślnie */
}
```

**Plik: Makefile** (MUSI być w tym samym folderze co hello.c)
```makefile
# Definicja kompilatora
# CC to konwencjonalna nazwa zmiennej dla kompilatora C
CC = gcc

# Flagi kompilatora – zebrane w jedną zmienną dla łatwej zmiany
CFLAGS = -std=c23 -pedantic -Werror=pedantic -Wall -Wextra

# Reguła: jak zbudować plik "hello" z pliku "hello.o"
# "hello" to CEL, "hello.o" to ZALEŻNOŚĆ
hello: hello.o
	$(CC) $(CFLAGS) -o hello hello.o
#	↑ TAB (nie spacje!) przed poleceniem – to wymóg składni Makefile

# Reguła: jak zbudować plik "hello.o" z pliku "hello.c"
hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c
#	-c oznacza: tylko kompiluj, nie linkuj (generuje plik .o)

# Cel specjalny: usuń pliki wynikowe
# Używamy: make clean
clean:
	rm -f hello hello.o
#	-f oznacza: nie zgłaszaj błędu jeśli plik nie istnieje
```

### Jak używać

```bash
# Kompilacja (wykonaj reguły z Makefile)
make

# Uruchomienie
./hello

# Zmodyfikuj hello.c, np. zmień tekst w printf
# Ponowna kompilacja – make skompiluje tylko zmieniony plik
make

# Usunięcie plików wynikowych
make clean
```

### Co zostanie wypisane przy `make`

```
gcc -std=c23 -pedantic -Werror=pedantic -Wall -Wextra -c hello.c
gcc -std=c23 -pedantic -Werror=pedantic -Wall -Wextra -o hello hello.o
```

### Co wypisze `./hello`

```
Hello World!
```

### Typowe błędy i jak ich unikać

**Błąd 1: Spacje zamiast tabulatora**
```
Makefile:6: *** missing separator.  Stop.
```
Jak unikać: zawsze używaj klawisza TAB przed poleceniem, nigdy spacji.

**Błąd 2: Makefile o złej nazwie**
```bash
makefile     # działa na niektórych systemach
Makefile     # działa zawsze – to standardowa nazwa
```
Jak unikać: używaj `Makefile` z wielką literą M.

**Błąd 3: make mówi "Nothing to be done"**
```
make: 'hello' is up to date.
```
Nie to błąd! make widzi, że plik hello jest nowszy niż źródła. Jeśli chcesz wymusić rekompilację: `make clean && make`.

**Błąd 4: Brak pliku Makefile w bieżącym folderze**
```
make: *** No targets specified and no makefile found.  Stop.
```
Jak unikać: upewnij się, że jesteś w folderze z plikiem Makefile (`ls` pokaże pliki).

---

## TEMAT 7 – Makefile dla wielu plików źródłowych

### Teoria

Duże programy dzielimy na wiele plików `.c` – każdy odpowiada za inną funkcjonalność.
Korzyści:
- Lepszy porządek – każdy plik ma jasne zadanie
- Szybsza kompilacja – `make` kompiluje tylko zmienione pliki
- Łatwiejsze testowanie i wielokrotne użycie kodu

Struktura projektu z trzema plikami:
- `main.c` – funkcja `main()`, wywołuje funkcje z innych plików
- `utils.c` + `utils.h` – funkcje pomocnicze (wypisywanie itp.)
- `math_utils.c` + `math_utils.h` – funkcje matematyczne

Plik `.h` (nagłówkowy) to „menu" pliku `.c` – deklaruje co jest w środku.
Plik `.c` to implementacja – tutaj są ciała funkcji.

### Kompletny kod z komentarzami

**Plik: utils.h** – deklaracje funkcji z utils.c
```c
/* Strażnik przed wielokrotnym dołączeniem (include guard)
   Jeśli UTILS_H nie jest zdefiniowane – zdefiniuj je i dołącz treść
   Jeśli jest już zdefiniowane – pomiń całą zawartość pliku
   To zapobiega błędom gdy ten plik jest dołączony z wielu miejsc */
#ifndef UTILS_H
#define UTILS_H

/* Deklaracja (prototyp) funkcji – kompilator wie że istnieje */
void print_message(void);   /* void=nic nie zwraca, void=brak argumentów */

#endif  /* koniec bloku include guard */
```

**Plik: utils.c** – implementacja funkcji z utils.h
```c
#include <stdio.h>      /* potrzebujemy printf */
#include "utils.h"      /* dołączamy własny nagłówek w cudzysłowach "" nie <> */
                        /* "" = szukaj w bieżącym folderze, <> = szukaj w systemowych ścieżkach */

/* Definicja (implementacja) funkcji print_message */
void print_message(void) {
    printf("Hello from utils!\n");   /* wypisujemy powitanie */
}
```

**Plik: math_utils.h** – deklaracje funkcji z math_utils.c
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/* Deklaracja funkcji dodającej dwie liczby całkowite */
int add(int a, int b);

#endif
```

**Plik: math_utils.c** – implementacja funkcji matematycznych
```c
#include "math_utils.h"     /* dołączamy własny nagłówek */

/* Implementacja funkcji add */
int add(int a, int b) {
    return a + b;   /* zwróć sumę */
}
```

**Plik: main.c** – główny plik programu
```c
#include <stdio.h>          /* dla printf */
#include "utils.h"          /* dostęp do print_message() */
#include "math_utils.h"     /* dostęp do add() */

int main(void) {
    print_message();        /* wywołaj funkcję z utils.c */
    printf("2 + 3 = %d\n", add(2, 3));  /* wywołaj add() z math_utils.c */
    return 0;
}
```

**Plik: Makefile**
```makefile
# Kompilator i flagi
CC = gcc
CFLAGS = -std=c23 -pedantic -Werror=pedantic -Wall -Wextra

# Lista plików źródłowych
SRCS = main.c utils.c math_utils.c

# Lista plików obiektowych (.o) – automatycznie z .c na .o
# $(SRCS:.c=.o) zastępuje rozszerzenie .c na .o w zmiennej SRCS
OBJS = $(SRCS:.c=.o)

# Nazwa pliku wykonywalnego
TARGET = my_program

# Domyślna reguła (pierwsza reguła w pliku) – wykonywana przez samo "make"
all: $(TARGET)

# Reguła linkowania: z plików .o tworzymy plik wykonywalny
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Reguła generyczna: jak skompilować dowolny plik .c do .o
# $< to automatyczna zmienna = nazwa pliku źródłowego (zależności)
# $@ to automatyczna zmienna = nazwa celu (pliku .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Usunięcie plików tymczasowych
clean:
	rm -f $(OBJS) $(TARGET)
```

### Jak używać

```bash
# Kompilacja całego projektu
make

# Uruchomienie
./my_program

# Zmień coś w math_utils.c – make skompiluje TYLKO ten plik, potem zlinkuje
make

# Sprzątanie
make clean
```

### Co wypisze `./my_program`

```
Hello from utils!
2 + 3 = 5
```

### Typowe błędy i jak ich unikać

**Błąd 1: Brak pliku nagłówkowego przy użyciu funkcji z innego pliku**
```c
/* main.c – brak #include "utils.h" */
int main(void) {
    print_message();  /* BŁĄD: kompilator nie zna deklaracji tej funkcji */
}
```

**Błąd 2: Brak include guard w pliku .h**
```c
/* Jeśli plik jest dołączony dwa razy, deklaracje powtarzają się → błąd kompilacji */
/* Rozwiązanie: zawsze używaj #ifndef NAZWA_H / #define NAZWA_H / #endif */
```

**Błąd 3: Definicja funkcji w pliku .h zamiast deklaracji**
```c
/* BŁĄD w pliku .h: */
int add(int a, int b) { return a + b; }  /* definicja w .h – przy dołączeniu w wielu plikach .c → błąd "multiple definition" */

/* POPRAWNIE w pliku .h: */
int add(int a, int b);   /* tylko deklaracja */
/* A definicja (implementacja) idzie do pliku .c */
```

**Błąd 4: Cudzysłowy vs nawiasy przy #include**
```c
#include <utils.h>    /* BŁĄD: system będzie szukał w ścieżkach systemowych */
#include "utils.h"    /* OK: szuka w bieżącym folderze */
```

---

## TEMAT 8 – Rozbudowany Makefile z biblioteką statyczną i testami

### Teoria

W profesjonalnych projektach stosuje się bardziej zaawansowaną strukturę folderów:
- `src/` – pliki źródłowe
- `bin/` – pliki wykonywalne
- `lib/` – biblioteki statyczne (`.a`)
- `tests/` – testy automatyczne

**Biblioteka statyczna** (`.a`) to paczka skompilowanych plików `.o` zarchiwizowana razem.
Program linkowany z biblioteką statyczną „wbudowuje" jej kod w siebie. Tworzy się ją poleceniem `ar`.

**Testy automatyczne** – program który wywołuje nasze funkcje z różnymi wartościami i sprawdza
czy wyniki są poprawne. Funkcja `assert()` z `<assert.h>` zatrzymuje program jeśli warunek
jest fałszywy – to sygnał, że coś jest nie tak.

### Kompletny kod z komentarzami

**Struktura folderów:**
```
projekt/
├── Makefile
├── src/
│   ├── main.c
│   ├── math_utils.c
│   ├── math_utils.h
│   ├── utils.c
│   └── utils.h
├── tests/
│   └── tests.c
├── bin/          (tworzony automatycznie przez make)
└── lib/          (tworzony automatycznie przez make)
```

**Plik: src/math_utils.h**
```c
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int add(int a, int b);      /* deklaracja funkcji dodawania */

#endif
```

**Plik: src/math_utils.c**
```c
#include "math_utils.h"     /* dołączamy własny nagłówek */

int add(int a, int b) {
    return a + b;           /* zwróć sumę */
}
```

**Plik: src/utils.h**
```c
#ifndef UTILS_H
#define UTILS_H

void print_message(void);   /* deklaracja funkcji wypisującej wiadomość */

#endif
```

**Plik: src/utils.c**
```c
#include <stdio.h>
#include "utils.h"

void print_message(void) {
    printf("Hello from utils!\n");
}
```

**Plik: src/main.c**
```c
#include <stdio.h>
#include "utils.h"
#include "math_utils.h"

int main(void) {
    print_message();
    printf("2 + 3 = %d\n", add(2, 3));
    return 0;
}
```

**Plik: tests/tests.c**
```c
#include <stdio.h>          /* dla printf */
#include <assert.h>         /* dla assert() – sprawdzenie warunków */
#include "../src/math_utils.h"  /* dołączamy nagłówek testowanego modułu */
                                /* ../ oznacza folder nadrzędny */

/* Funkcja testująca add() */
void test_add(void) {
    /* assert(warunek) – jeśli warunek fałszywy, program zatrzymuje się z błędem */
    assert(add(2, 3) == 5);     /* sprawdź: 2+3=5 */
    assert(add(-1, 1) == 0);    /* sprawdź: -1+1=0 */
    assert(add(0, 0) == 0);     /* sprawdź: 0+0=0 */
    assert(add(-5, -3) == -8);  /* sprawdź: suma ujemnych */
    printf("Test add() passed!\n"); /* informacja że testy przeszły */
}

/* Główna funkcja programu testowego */
int main(void) {
    test_add();                 /* uruchom testy funkcji add */
    printf("All tests passed!\n");  /* wszystkie testy zaliczone */
    return 0;
}
```

**Plik: Makefile**
```makefile
# Kompilator i flagi
CC = gcc
CFLAGS = -std=c23 -pedantic -Werror=pedantic -Wall -Wextra

# Definicje folderów
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib
TEST_DIR = tests

# Pliki źródłowe głównego programu
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/math_utils.c $(SRC_DIR)/utils.c

# Pliki składające się na bibliotekę statyczną (wszystko oprócz main.c)
LIB_SRCS = $(SRC_DIR)/utils.c

# Pliki obiektowe (.o) – automatycznie z .c na .o
OBJS = $(SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Ścieżki do pliku wykonywalnego i biblioteki
LIBRARY = $(LIB_DIR)/libutils.a
TARGET = $(BIN_DIR)/my_program
TEST_TARGET = $(BIN_DIR)/test_runner

# Domyślna reguła – buduje główny program
all: $(BIN_DIR) $(LIB_DIR) $(TARGET)

# Reguła tworzenia folderów bin i lib jeśli nie istnieją
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Reguła: budowanie biblioteki statycznej z plików obiektowych
# ar rcs = Archive Replace Create Sorted (stwórz/aktualizuj archiwum)
$(LIBRARY): $(LIB_OBJS)
	ar rcs $(LIBRARY) $(LIB_OBJS)

# Reguła: linkowanie głównego programu z biblioteką
# -L$(LIB_DIR) – szukaj bibliotek w folderze lib/
# -lutils – linkuj bibliotekę libutils.a
$(TARGET): $(OBJS) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -L$(LIB_DIR) -lutils

# Reguła: kompilacja programu testowego
$(TEST_TARGET): $(TEST_DIR)/tests.c $(SRC_DIR)/math_utils.c
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_DIR)/tests.c $(SRC_DIR)/math_utils.c

# Reguła: uruchomienie testów (make test)
test: $(BIN_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)

# Reguła generyczna: .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Sprzątanie
clean:
	rm -f $(OBJS) $(LIB_OBJS) $(TARGET) $(TEST_TARGET) $(LIBRARY)
```

### Jak używać

```bash
# Stwórz foldery struktury projektu
mkdir -p projekt/src projekt/tests
cd projekt

# Umieść pliki w odpowiednich folderach, potem:

# Kompilacja programu
make

# Uruchomienie
./bin/my_program

# Uruchomienie testów
make test

# Sprzątanie
make clean
```

### Co wypisze `./bin/my_program`

```
Hello from utils!
2 + 3 = 5
```

### Co wypisze `make test`

```
gcc ... -o bin/test_runner tests/tests.c src/math_utils.c
./bin/test_runner
Test add() passed!
All tests passed!
```

### Typowe błędy i jak ich unikać

**Błąd 1: Zła ścieżka w include testu**
```c
#include "math_utils.h"        /* BŁĄD jeśli tests.c jest w folderze tests/ */
#include "../src/math_utils.h" /* OK: jeden poziom wyżej, potem do src/ */
```

**Błąd 2: Brak `-lm` dla biblioteki matematycznej**
```makefile
# Jeśli używasz sqrt(), sin(), pow() itp., dodaj -lm na końcu linkowania:
$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lm
```

**Błąd 3: assert() nie wypisuje co poszło nie tak**
```c
assert(add(2, 3) == 5);   /* przy błędzie: "Assertion failed: add(2,3)==5, file tests.c, line 8" */
/* Aby wiedzieć więcej, można wypisać wartość przed assercją: */
int wynik = add(2, 3);
printf("add(2,3) = %d (oczekiwano 5)\n", wynik);
assert(wynik == 5);
```

**Błąd 4: Foldery bin/ i lib/ nie istnieją**
```
gcc: error: bin/my_program: No such file or directory
```
Jak unikać: dodaj reguły `mkdir -p` do Makefile, jak w przykładzie powyżej.

---

## TEMAT 9 – Pliki nagłówkowe – szczegółowe omówienie

### Teoria

Plik nagłówkowy (`.h`) to **interfejs modułu** – mówi światu, co dany plik `.c` oferuje.
Zawiera tylko deklaracje (prototypy), nigdy definicje funkcji (wyjątkiem są inline i makra).

**Dlaczego include guard jest niezbędny?**
Bez strażnika, jeśli plik `.h` jest dołączony przez dwa różne pliki `.c`, a oba są kompilowane,
powtórzone deklaracje mogą powodować błędy. Strażnik sprawia, że zawartość `.h` jest
przetwarzana tylko raz.

```c
#ifndef NAZWA_H    /* jeżeli NAZWA_H NIE jest zdefiniowane */
#define NAZWA_H    /* zdefiniuj NAZWA_H (zabezpiecz przed ponownym przetworzeniem) */

/* tu treść pliku nagłówkowego */

#endif             /* koniec bloku warunkowego */
```

Alternatywnie, wiele kompilatorów (w tym GCC) obsługuje `#pragma once` na początku pliku.

### Kompletny przykład – moduł z wieloma funkcjami

**Plik: kalkulator.h**
```c
/* kalkulator.h – interfejs modułu kalkulatora */
#ifndef KALKULATOR_H    /* include guard – zapobiegamy wielokrotnemu dołączeniu */
#define KALKULATOR_H

/* Deklaracje funkcji – tylko sygnatury, bez ciał */
int dodaj(int a, int b);
int odejmij(int a, int b);
int pomnoz(int a, int b);
float podziel(float a, float b);     /* zwraca float bo dzielenie może dać ułamek */
int modulo(int a, int b);            /* reszta z dzielenia */

/* Można też deklarować stałe */
#define PI 3.14159265f  /* stała PI dla modułu (makro preprocesora) */

#endif  /* KALKULATOR_H */
```

**Plik: kalkulator.c**
```c
/* kalkulator.c – implementacja modułu kalkulatora */
#include <stdio.h>          /* printf do obsługi błędów */
#include "kalkulator.h"     /* dołączamy własny nagłówek */

/* Implementacje funkcji – ciała funkcji */

int dodaj(int a, int b) {
    return a + b;   /* prosta suma */
}

int odejmij(int a, int b) {
    return a - b;   /* prosta różnica */
}

int pomnoz(int a, int b) {
    return a * b;   /* prosty iloczyn */
}

float podziel(float a, float b) {
    if (b == 0.0f) {                    /* ochrona przed dzieleniem przez zero */
        printf("Blad: dzielenie przez zero!\n");
        return 0.0f;
    }
    return a / b;
}

int modulo(int a, int b) {
    if (b == 0) {                       /* ochrona przed dzieleniem przez zero */
        printf("Blad: modulo przez zero!\n");
        return 0;
    }
    return a % b;   /* reszta z dzielenia */
}
```

**Plik: main.c**
```c
/* main.c – główny plik programu */
#include <stdio.h>
#include "kalkulator.h"     /* dołączamy moduł kalkulatora */

int main(void) {
    int a = 17;
    int b = 5;

    /* Używamy funkcji z modułu kalkulator */
    printf("%d + %d = %d\n", a, b, dodaj(a, b));
    printf("%d - %d = %d\n", a, b, odejmij(a, b));
    printf("%d * %d = %d\n", a, b, pomnoz(a, b));
    printf("%d / %d = %.2f\n", a, b, podziel((float)a, (float)b));
    printf("%d %% %d = %d\n", a, b, modulo(a, b));  /* %% = dosłowny znak % */
    printf("PI = %f\n", PI);       /* stała z nagłówka */

    return 0;
}
```

**Plik: Makefile**
```makefile
CC = gcc
CFLAGS = -std=c23 -pedantic -Werror=pedantic -Wall -Wextra

SRCS = main.c kalkulator.c
OBJS = $(SRCS:.c=.o)
TARGET = kalkulator_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
```

### Co wypisze program

```
17 + 5 = 22
17 - 5 = 12
17 * 5 = 85
17 / 5 = 3.40
17 % 5 = 2
PI = 3.141593
```

### Typowe błędy i jak ich unikać

**Błąd 1: Definicja zmiennej globalnej w pliku .h**
```c
/* BŁĄD w .h – jeśli dołączony w wielu plikach .c, zmienna jest definiowana wiele razy */
int licznik = 0;

/* POPRAWNIE w .h – deklaracja extern */
extern int licznik;   /* informuje: istnieje gdzieś indziej */
/* A w jednym pliku .c: */
int licznik = 0;      /* tutaj faktyczna definicja */
```

**Błąd 2: Brak include guard → podwójne deklaracje**
```
error: redefinition of 'struct Punkt'
```
Jak unikać: zawsze dodawaj `#ifndef / #define / #endif`.

---

## TEMAT 10 – Generator liczb pierwszych – praktyczny przykład

### Teoria

Liczba pierwsza to liczba naturalna większa od 1, która dzieli się bez reszty tylko przez 1
i przez siebie samą (np. 2, 3, 5, 7, 11, 13...).

Algorytm sprawdzania:
1. Jeśli liczba ≤ 1 → nie jest pierwsza
2. Sprawdzamy czy liczba dzieli się przez jakąkolwiek liczbę od 2 do √n
3. Jeśli tak → nie jest pierwsza
4. Jeśli żadna nie dzieli → jest pierwsza

Dlaczego wystarczy sprawdzać do √n? Bo jeśli n = a × b i a > √n, to b < √n. Wystarczy
więc sprawdzić mniejszy z dzielników.

Potrzebne elementy języka C:
- `sqrt(x)` z `<math.h>` – pierwiastek kwadratowy
- `(int)sqrt(x)` – konwersja wyniku double na int
- Operator `%` – reszta z dzielenia
- Pętla `for` – iteracja po liczbach

### Kompletny kod z komentarzami

**Plik: prime_utils.h**
```c
/* prime_utils.h – deklaracje funkcji dla modułu liczb pierwszych */
#ifndef PRIME_UTILS_H
#define PRIME_UTILS_H

/* Sprawdza czy n jest liczbą pierwszą
   Zwraca: 1 (tak, jest pierwsza) lub 0 (nie jest pierwsza) */
int jest_pierwsza(int n);

/* Wypisuje wszystkie liczby pierwsze od 2 do max */
void wypisz_pierwsze(int max);

/* Zwraca ilość liczb pierwszych w przedziale [2, max] */
int ile_pierwszych(int max);

#endif
```

**Plik: prime_utils.c**
```c
/* prime_utils.c – implementacja funkcji sprawdzających liczby pierwsze */
#include <stdio.h>          /* printf */
#include <math.h>           /* sqrt */
#include "prime_utils.h"    /* własny nagłówek */

/* Sprawdza czy n jest liczbą pierwszą */
int jest_pierwsza(int n) {
    if (n <= 1) {           /* liczby <= 1 nie są pierwsze z definicji */
        return 0;           /* 0 = fałsz = nie jest pierwsza */
    }
    if (n == 2) {           /* 2 jest pierwsza (jedyna parzysta pierwsza) */
        return 1;           /* 1 = prawda = jest pierwsza */
    }
    if (n % 2 == 0) {       /* parzyste liczby większe niż 2 nie są pierwsze */
        return 0;
    }

    /* Sprawdzamy dzielniki od 3 do sqrt(n), co 2 (tylko nieparzyste) */
    int granica = (int)sqrt((double)n); /* rzutowanie na int obcina część ułamkową */
    for (int i = 3; i <= granica; i += 2) {  /* i += 2 = skaczemy o 2 (pomijamy parzyste) */
        if (n % i == 0) {   /* jeśli n dzieli się przez i bez reszty */
            return 0;       /* to n nie jest pierwsza */
        }
    }

    return 1;   /* jeśli żaden dzielnik nie pasował – n jest pierwsza */
}

/* Wypisuje wszystkie liczby pierwsze od 2 do max */
void wypisz_pierwsze(int max) {
    printf("Liczby pierwsze od 2 do %d:\n", max);
    int licznik = 0;    /* ile liczb pierwszych znaleźliśmy */
    for (int i = 2; i <= max; i++) {    /* sprawdzamy każdą liczbę od 2 do max */
        if (jest_pierwsza(i)) {         /* jeśli i jest pierwsza */
            printf("%d", i);
            licznik++;
            if (i < max) {              /* po ostatniej liczbie nie dodajemy przecinka */
                printf(", ");
            }
            if (licznik % 10 == 0) {    /* co 10 liczb – nowa linia (czytelność) */
                printf("\n");
            }
        }
    }
    printf("\n");
    printf("Znaleziono %d liczb pierwszych.\n", licznik);
}

/* Zwraca ilość liczb pierwszych od 2 do max */
int ile_pierwszych(int max) {
    int licznik = 0;
    for (int i = 2; i <= max; i++) {
        if (jest_pierwsza(i)) {
            licznik++;
        }
    }
    return licznik;
}
```

**Plik: main.c**
```c
/* main.c – program demonstracyjny generatora liczb pierwszych */
#include <stdio.h>
#include "prime_utils.h"    /* dołączamy moduł liczb pierwszych */

int main(void) {

    /* Sprawdzenie kilku konkretnych liczb */
    printf("--- Sprawdzanie konkretnych liczb ---\n");
    int testowe[] = {1, 2, 3, 4, 7, 10, 13, 25, 97, 100};  /* tablica testowych liczb */
    int ile = 10;   /* ile elementów w tablicy */

    for (int i = 0; i < ile; i++) {     /* iterujemy po tablicy */
        printf("%3d: %s\n",
               testowe[i],
               jest_pierwsza(testowe[i]) ? "PIERWSZA" : "nie pierwsza");
        /* operator ternary: warunek ? wartość_jeśli_prawda : wartość_jeśli_fałsz */
    }

    /* Wypisanie wszystkich liczb pierwszych do 100 */
    printf("\n--- Wszystkie pierwsze do 100 ---\n");
    wypisz_pierwsze(100);

    /* Ile jest liczb pierwszych do 1000? */
    printf("\n--- Statystyki ---\n");
    printf("Liczb pierwszych do 1000: %d\n", ile_pierwszych(1000));

    return 0;
}
```

**Plik: tests/prime_tests.c**
```c
/* prime_tests.c – testy automatyczne funkcji jest_pierwsza */
#include <stdio.h>
#include <assert.h>
#include "../prime_utils.h"   /* testowany moduł */

/* Test: czy funkcja poprawnie rozpoznaje liczby pierwsze */
void test_jest_pierwsza_true(void) {
    assert(jest_pierwsza(2)  == 1);   /* 2 jest pierwsza */
    assert(jest_pierwsza(3)  == 1);   /* 3 jest pierwsza */
    assert(jest_pierwsza(5)  == 1);   /* 5 jest pierwsza */
    assert(jest_pierwsza(7)  == 1);   /* 7 jest pierwsza */
    assert(jest_pierwsza(11) == 1);   /* 11 jest pierwsza */
    assert(jest_pierwsza(97) == 1);   /* 97 jest pierwsza */
    printf("test_jest_pierwsza_true: OK\n");
}

/* Test: czy funkcja poprawnie odrzuca liczby niezłożone */
void test_jest_pierwsza_false(void) {
    assert(jest_pierwsza(0)  == 0);   /* 0 nie jest pierwsza */
    assert(jest_pierwsza(1)  == 0);   /* 1 nie jest pierwsza */
    assert(jest_pierwsza(4)  == 0);   /* 4 = 2*2 */
    assert(jest_pierwsza(6)  == 0);   /* 6 = 2*3 */
    assert(jest_pierwsza(9)  == 0);   /* 9 = 3*3 */
    assert(jest_pierwsza(100)== 0);   /* 100 = 4*25 */
    printf("test_jest_pierwsza_false: OK\n");
}

/* Test: ile liczb pierwszych do 100 (powinno być 25) */
void test_ile_pierwszych(void) {
    assert(ile_pierwszych(10)  == 4);    /* 2,3,5,7 */
    assert(ile_pierwszych(100) == 25);   /* znane z matematyki */
    printf("test_ile_pierwszych: OK\n");
}

int main(void) {
    test_jest_pierwsza_true();
    test_jest_pierwsza_false();
    test_ile_pierwszych();
    printf("Wszystkie testy zaliczone!\n");
    return 0;
}
```

**Plik: Makefile**
```makefile
CC = gcc
CFLAGS = -std=c23 -pedantic -Werror=pedantic -Wall -Wextra
# -lm potrzebne bo używamy sqrt() z math.h
LDFLAGS = -lm

SRCS = main.c prime_utils.c
OBJS = $(SRCS:.c=.o)
TARGET = prime_generator
TEST_TARGET = prime_tests

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

prime_utils.o: prime_utils.c prime_utils.h
	$(CC) $(CFLAGS) -c prime_utils.c -o prime_utils.o

main.o: main.c prime_utils.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Budowanie i uruchamianie testów
$(TEST_TARGET): tests/prime_tests.c prime_utils.c prime_utils.h
	$(CC) $(CFLAGS) -o $(TEST_TARGET) tests/prime_tests.c prime_utils.c $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET)
```

### Jak używać

```bash
# Utwórz folder tests/
mkdir tests
# Wstaw pliki na swoje miejsca, potem:

# Kompilacja i uruchomienie
make
./prime_generator

# Uruchomienie testów
make test
```

### Co wypisze `./prime_generator`

```
--- Sprawdzanie konkretnych liczb ---
  1: nie pierwsza
  2: PIERWSZA
  3: PIERWSZA
  4: nie pierwsza
  7: PIERWSZA
 10: nie pierwsza
 13: PIERWSZA
 25: nie pierwsza
 97: PIERWSZA
100: nie pierwsza

--- Wszystkie pierwsze do 100 ---
Liczby pierwsze od 2 do 100:
2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
73, 79, 83, 89, 97
Znaleziono 25 liczb pierwszych.

--- Statystyki ---
Liczb pierwszych do 1000: 168
```

### Co wypisze `make test`

```
Test add() passed!
test_jest_pierwsza_true: OK
test_jest_pierwsza_false: OK
test_ile_pierwszych: OK
Wszystkie testy zaliczone!
```

### Typowe błędy i jak ich unikać

**Błąd 1: Brak `-lm` przy linkwaniu z math.h**
```
undefined reference to `sqrt'
```
Jak unikać: dodaj `-lm` na końcu polecenia linkowania w Makefile.

**Błąd 2: Błędna granica pętli sprawdzania**
```c
for (int i = 2; i < n; i++) {       /* sprawdza do n-1 – poprawne ale wolne */
for (int i = 2; i <= granica; i++)  /* sprawdza do sqrt(n) – poprawne i szybkie */
```

**Błąd 3: Zapomnienie o przypadkach brzegowych (0, 1, 2)**
```c
int jest_pierwsza(int n) {
    /* BEZ obsługi 0, 1 i 2 funkcja może dać zły wynik */
    for (int i = 2; i <= (int)sqrt(n); i++) { ... }
}
```
Jak unikać: zawsze zacznij od sprawdzenia przypadków specjalnych.

**Błąd 4: Konwersja sqrt bez rzutowania**
```c
int granica = sqrt(n);      /* ostrzeżenie: konwersja double do int */
int granica = (int)sqrt(n); /* OK: jawna konwersja */
```

---

## PODSUMOWANIE – Szybka ściąga

### Kompilacja

```bash
gcc -std=c23 -Wall -Wextra -o program plik.c        # prosty program
gcc -std=c23 -Wall -Wextra -o program plik.c -lm    # z matematyką
gcc -std=c23 -Wall -Wextra -c plik.c -o plik.o      # tylko kompilacja (bez linkowania)
gcc -std=c23 -Wall -Wextra -o program a.o b.o       # linkowanie plików .o
```

### Makefile – minimalna struktura

```makefile
CC = gcc
CFLAGS = -std=c23 -Wall -Wextra
TARGET = program
SRCS = main.c modul.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
```

### Plik nagłówkowy – szablon

```c
#ifndef NAZWA_MODULU_H
#define NAZWA_MODULU_H

/* deklaracje funkcji */
int funkcja(int a, int b);

#endif
```

### Specyfikatory printf

| Typ    | Specyfikator | Przykład                        |
|:-------|:---:|:---|
| int    | `%d`         | `printf("%d", 42)`    → `42`    |
| float  | `%f`         | `printf("%.2f", 3.1)` → `3.10` |
| double | `%lf`        | `printf("%lf", 3.14)` → `3.140000` |
| char   | `%c`         | `printf("%c", 'A')`   → `A`    |
| string | `%s`         | `printf("%s", "abc")` → `abc`  |
| hex    | `%x`         | `printf("%x", 255)`   → `ff`   |

---

*Notatki opracowane na podstawie materiałów dydaktycznych AGH – Programowanie Imperatywne, wersja 1.0.3*
