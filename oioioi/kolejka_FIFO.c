#include <stdio.h>

#define STACK_SIZE 10

enum state { OK = 0, UNDERFLOW = -1, OVERFLOW = -2 };

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

int queue_push(int in_nr) {
  int flaga = 0;
  for (int i = 0; i < in_nr; i++) {
    curr_nr++;
    if (in < 10) {
      queue[in] = curr_nr;
      in++;
    } else {
      flaga = 1;
    }
  }
  if (flaga == 0) {
    return OK;
  } else {
    return OVERFLOW;
  }
}

int queue_pop(int out_nr) {
  for (int i = 0; i < out_nr; i++) {
    for (int j = 0; j < 9; j++) {
      queue[j] = queue[j + 1];
    }
    queue[9] = 0;
    in--;
  }
  if (in < 0) {
    in = 0;
    return UNDERFLOW;
  } else {
    return in;
  }
}

int queue_state(void) { return in; }

void queue_print(void) {
  for (int i = 0; i < in; i++) {
    printf("%d ", queue[i]);
  }
  printf("\n");
}

int main(void) {
  int n, answer;
  do {
    scanf("%d", &n);
    if (n > 0) {
      if ((answer = queue_push(n)) < 0)
        printf("%d ", answer);
    } else if (n < 0) {
      if ((answer = queue_pop(-n)) < 0)
        printf("%d ", answer);
    } else {
      printf("\n%d\n", queue_state());
      queue_print();
    }
  } while (n != 0);

  return 0;
}
