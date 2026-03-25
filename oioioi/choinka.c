#include <stdio.h>

void tree(int k, int p) {
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= k - i; j++) {
      printf(" ");
    }
    for (int j = 1; j <= 2 * i - 1; j++) {
      printf("*");
    }
    printf("\n");
  }
  for (int i = 1; i <= p; i++) {
    for (int j = 1; j <= k - i; j++) {
      printf(" ");
    }
    for (int j = 1; j <= 2 * i - 1; j++) {
      printf("*");
    }
    printf("\n");
  }
}

int main(void) {
  int k, p;
  scanf("%d %d", &k, &p);
  tree(k, p);
  return 0;
}
