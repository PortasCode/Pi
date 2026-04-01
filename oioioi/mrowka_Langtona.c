#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int pi, pj;
  int direction;
} Ant;

enum Kierunek { N = 0, E = 1, S = 2, W = 3 };

void print_board(int **board, const int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", board[i][j]);
    }
    printf("\n");
  }
}

void print_ant(const Ant ant) {
  char dir;
  switch (ant.direction) {
  case 0:
    dir = 'N';
    break;
  case 1:
    dir = 'E';
    break;
  case 2:
    dir = 'S';
    break;
  case 3:
    dir = 'W';
    break;
  }
  printf("%d %d %c\n", ant.pi, ant.pj, dir);
}

void init_board(int ***board, const int n) {
  *board = malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    (*board)[i] = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      (*board)[i][j] = (rand() % 8) + 1;
    }
  }
}

void free_board(int **board, const int n) {
  for (int i = 0; i < n; i++) {
    free(board[i]);
  }
  free(board);
}

void ant_move(int **board, const int n, Ant *ant) {
  int current_state = board[ant->pi][ant->pj];

  switch (current_state) {
  case 1:
    board[ant->pi][ant->pj] = 7;
    break;
  case 2:
    board[ant->pi][ant->pj] = 4;
    break;
  case 3:
    board[ant->pi][ant->pj] = 2;
    break;
  case 4:
    board[ant->pi][ant->pj] = 6;
    break;
  case 5:
    board[ant->pi][ant->pj] = 3;
    break;
  case 6:
    board[ant->pi][ant->pj] = 5;
    break;
  case 7:
    board[ant->pi][ant->pj] = 8;
    break;
  case 8:
    board[ant->pi][ant->pj] = 1;
    break;
  }

  switch (current_state) {
  case 1: // krok w przód
    if (ant->direction == N)
      ant->pi = (ant->pi - 1 + n) % n;
    if (ant->direction == E)
      ant->pj = (ant->pj + 1) % n;
    if (ant->direction == S)
      ant->pi = (ant->pi + 1) % n;
    if (ant->direction == W)
      ant->pj = (ant->pj - 1 + n) % n;
    break;
  case 2: // obrót w prawo
    ant->direction = (ant->direction + 1) % 4;
    break;
  case 3: // obrót w lewo
    ant->direction = (ant->direction + 3) % 4;
    break;
  case 4: // krok w prawy bok
    if (ant->direction == N)
      ant->pj = (ant->pj + 1) % n;
    if (ant->direction == E)
      ant->pi = (ant->pi + 1) % n;
    if (ant->direction == S)
      ant->pj = (ant->pj - 1 + n) % n;
    if (ant->direction == W)
      ant->pi = (ant->pi - 1 + n) % n;
    break;
  case 5: // krok w lewy bok
    if (ant->direction == N)
      ant->pj = (ant->pj - 1 + n) % n;
    if (ant->direction == E)
      ant->pi = (ant->pi - 1 + n) % n;
    if (ant->direction == S)
      ant->pj = (ant->pj + 1) % n;
    if (ant->direction == W)
      ant->pi = (ant->pi + 1) % n;
    break;
  case 6: // krok w tył
    if (ant->direction == N)
      ant->pi = (ant->pi + 1) % n;
    if (ant->direction == E)
      ant->pj = (ant->pj - 1 + n) % n;
    if (ant->direction == S)
      ant->pi = (ant->pi - 1 + n) % n;
    if (ant->direction == W)
      ant->pj = (ant->pj + 1) % n;
    break;
  case 7: // w tył zwrot
    ant->direction = (ant->direction + 2) % 4;
    break;
  case 8: // nic nie robi
    break;
  }
}
void ant_simulation(int **board, const int n, Ant *ant, const int steps) {
  ant->pi = 0;
  ant->pj = 0;
  ant->direction = E;

  for (int i = 0; i < steps; i++) {
    ant_move(board, n, ant);
  }
}

int main(void) {
  int **board;
  int n, steps;
  unsigned seed;
  Ant ant;

  scanf("%d %d %d", &n, &seed, &steps);
  srand(seed);
  init_board(&board, n);
  ant_simulation(board, n, &ant, steps);
  print_board(board, n);
  print_ant(ant);

  free_board(board, n);

  return 0;
}
