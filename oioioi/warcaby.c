#include <stdio.h>
#include <stdlib.h>
#define N 20

typedef enum { EMPTY = 0, PLAYER1, PLAYER2 } states;
int cnt[2];

void start(states board[][N], const int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = EMPTY;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < n; j++) {
      if ((i + j) % 2 == 0) {
        board[i][j] = PLAYER1;
      }
      if ((n - 1 - i + j) % 2 == 0) {
        board[n - 1 - i][j] = PLAYER2;
      }
    }
  }
}

int move(states board[][N], const int i, const int j, const int n) {
  int wektor = 0;
  if (board[i][j] == PLAYER1) {
    wektor = 1;
  } else {
    wektor = -1;
  }

  if ((i + wektor) >= 0 && (i + wektor) < n) {
    if ((j + 1) < n) {
      if (board[i + wektor][j + 1] == EMPTY) {
        board[i + wektor][j + 1] = board[i][j];
        board[i][j] = EMPTY;
        return 1;
      }
    }
    if ((j - 1) >= 0) {
      if (board[i + wektor][j - 1] == EMPTY) {
        board[i + wektor][j - 1] = board[i][j];
        board[i][j] = EMPTY;
        return 1;
      }
    }
  }
  return 0;
}

int capture(states board[][N], const int i, const int j, const int n) {
  int wektor = 0, mini_wektor = 0;
  if (board[i][j] == PLAYER1) {
    wektor = 2;
    mini_wektor = 1;
  } else {
    wektor = -2;
    mini_wektor = -1;
  }

  if ((i + wektor) >= 0 && (i + wektor) < n) {
    if ((j + 2) < n) {
      if (board[i + wektor][j + 2] == EMPTY &&
          board[i][j] != board[i + mini_wektor][j + 1] &&
          board[i + mini_wektor][j + 1] != EMPTY) {
        board[i + mini_wektor][j + 1] = EMPTY;
        board[i + wektor][j + 2] = board[i][j];
        board[i][j] = EMPTY;
        return 1;
      }
    }
    if ((j - 2) >= 0) {
      if (board[i + wektor][j - 2] == EMPTY &&
          board[i][j] != board[i + mini_wektor][j - 1] &&
          board[i + mini_wektor][j - 1] != EMPTY) {
        board[i + mini_wektor][j - 1] = EMPTY;
        board[i + wektor][j - 2] = board[i][j];
        board[i][j] = EMPTY;
        return 1;
      }
    }
  }
  return 0;
}

void step(states board[][N], const int n, const states player) {
  int i, j;
  do {
    i = rand() % n;
    j = rand() % n;
    if (board[i][j] == player) {
      if (capture(board, i, j, n) == 1) {
        cnt[player % 2]--;
      } else {
        move(board, i, j, n);
      }
      break;
    }
  } while (1);
}

int main(void) {
  states board[N][N];
  int n, steps;
  unsigned seed;

  scanf("%d %u %d", &n, &seed, &steps);
  srand(seed);
  cnt[0] = cnt[1] = 2 * n;
  start(board, n);
  for (int i = 0; i < steps; i++) {
    const states player = (i % 2 == 0) ? PLAYER1 : PLAYER2;
    if (cnt[player - 1] == 0) {
      break;
    }
    step(board, n, player);
  }
  printf("%d %d\n", cnt[0], cnt[1]);

  return 0;
}
