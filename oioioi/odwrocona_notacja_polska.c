#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr int BUFFER_SIZE = 128;

void to_onp(char *expression, char *onp) {
  char op_stack[BUFFER_SIZE];
  int op_top = -1;

  char *token = strtok(expression, " \t\n\r");
  int out_idx = 0;

  while (token != NULL) {
    if (isdigit(token[0]) || (token[0] == '-' && token[1] != '\0')) {
      int len = strlen(token);
      for (int i = 0; i < len; ++i) {
        onp[out_idx++] = token[i];
      }
      onp[out_idx++] = ' ';
    } else if (token[0] == '(') {
      op_stack[++op_top] = '(';
    } else if (token[0] == ')') {
      while (op_top >= 0 && op_stack[op_top] != '(') {
        onp[out_idx++] = op_stack[op_top--];
        onp[out_idx++] = ' ';
      }
      if (op_top >= 0) {
        op_top--;
      }
    } else {
      char o1 = token[0];
      int p1 = (o1 == '*' || o1 == '/') ? 2 : 1;

      while (op_top >= 0 && op_stack[op_top] != '(') {
        char o2 = op_stack[op_top];
        int p2 = (o2 == '*' || o2 == '/') ? 2 : 1;

        if (p2 >= p1) {
          onp[out_idx++] = op_stack[op_top--];
          onp[out_idx++] = ' ';
        } else {
          break;
        }
      }
      op_stack[++op_top] = o1;
    }
    token = strtok(NULL, " \t\n\r");
  }

  while (op_top >= 0) {
    onp[out_idx++] = op_stack[op_top--];
    onp[out_idx++] = ' ';
  }

  if (out_idx > 0) {
    onp[out_idx - 1] = '\0';
  } else {
    onp[0] = '\0';
  }
}

int evaluate_onp(char *onp) {
  int val_stack[BUFFER_SIZE];
  int val_top = -1;

  char *token = strtok(onp, " \t\n\r");

  while (token != NULL) {
    if (isdigit(token[0]) || (token[0] == '-' && token[1] != '\0')) {
      val_stack[++val_top] = atoi(token);
    } else {
      int right = val_stack[val_top--];
      int left = val_stack[val_top--];

      if (token[0] == '+')
        val_stack[++val_top] = left + right;
      else if (token[0] == '-')
        val_stack[++val_top] = left - right;
      else if (token[0] == '*')
        val_stack[++val_top] = left * right;
      else if (token[0] == '/')
        val_stack[++val_top] = left / right;
    }
    token = strtok(NULL, " \t\n\r");
  }

  return val_stack[val_top];
}

int main() {
  char buffer[BUFFER_SIZE];
  char onp[BUFFER_SIZE] = {'\0'};
  fgets(buffer, BUFFER_SIZE, stdin);
  to_onp(buffer, onp);
  printf("%s\n", onp);
  printf("%d\n", evaluate_onp(onp));

  return 0;
}
