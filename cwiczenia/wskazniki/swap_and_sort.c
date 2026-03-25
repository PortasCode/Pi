#include "funkcja_sort.h"
#include "funkcja_swap.h"
#include <stdio.h>

int main() {
  int a, b, c;
  printf("Podaj zmienna a: \n");
  scanf("%d", &a);
  printf("Podaj zmienna b: \n");
  scanf("%d", &b);
  printf("a: %d, b: %d\n", a, b);
  funkcja_swap(&a, &b);

  printf("a: %d\n", a);
  printf("b: %d\n", b);

  printf("Podaj zmienna c: \n");
  scanf("%d", &c);

  funkcja_sort(&a, &b, &c);
  printf("a: %d, b: %d, c: %d\n", a, b, c);

  return 0;
}
