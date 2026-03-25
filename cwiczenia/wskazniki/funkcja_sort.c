#include "funkcja_sort.h"
#include "funkcja_swap.h"
#include <stdio.h>

void funkcja_sort(int *a, int *b, int *c) {
  if (*a > *b) {
    funkcja_swap(a, b);
  }
  if (*a > *c) {
    funkcja_swap(a, c);
  }
  if (*b > *c) {
    funkcja_swap(b, c);
  }
}
