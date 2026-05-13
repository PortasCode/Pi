#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define N 20

bool correct_placemenet(int *queens, const int ndx) {
  int x = ndx, y = queens[ndx];

  for (int i = 0; i < ndx; i++) {
    if (queens[i] == y) {
      return false;
    }
    if ((x - i) == abs(y - queens[i])) {
      return false;
    }
  }
  return true;
}

bool place_queens(int *queens, const int n, const int k, const int ndx) {
  static int counter = 0;

  if (ndx == n) {
    counter++;
    if (counter == k) {
      return true;
    }
    return false;
  }

  for (int kolumna = 0; kolumna < n; kolumna++) {
    queens[ndx] = kolumna;
    if (correct_placemenet(queens, ndx) == true) {
      bool temp = place_queens(queens, n, k, ndx + 1);
      if (temp == true) {
        return true;
      }
    }
    queens[ndx] = 0;
  }
  return false;
}

void print_board(const int *queens, const int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", queens[i]);
  }
  printf("\n");
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  int queens[N] = {0};
  if (place_queens(queens, n, k, 0)) {
    print_board(queens, n);
  } else {
    printf("-1\n");
  }

  return EXIT_SUCCESS;
}
