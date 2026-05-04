#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAB_SIZE 1024
#define BUF_SIZE 1024

// 1
////////////////////////////////////////////////////////////

int get(int cols, int row, int col, const int *A) {
  return A[row * cols + col];
}

void set(int cols, int row, int col, int *A, int value) {
  A[row * cols + col] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
  int value;
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      value = 0;
      for (int k = 0; k < colsA; k++) {
        value = value + (get(colsA, i, k, A) * get(colsB, k, j, B));
      }
      set(colsB, i, j, AB, value);
    }
  }
}

void read_mat(int rows, int cols, int *t) {
  int a;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      scanf("%d", &a);
      set(cols, i, j, t, a);
    }
  }
}

void print_mat(int rows, int cols, int *t) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", get(cols, i, j, t));
    }
    printf("\n");
  }
}

// 2
/////////////////////////////////////////////////////////////
int read_int_lines_cont(int *ptr_array[]) {
  char bufor[BUF_SIZE];

  int wiersz = 0;
  int *kursor = ptr_array[0];

  while (fgets(bufor, BUF_SIZE, stdin) != NULL) {

    char *ptr = bufor;
    char *endptr;

    while (1) {

      int liczba = (int)strtol(ptr, &endptr, 10);

      if (ptr == endptr) {
        break;
      }

      *kursor = liczba;
      kursor++;

      ptr = endptr;
    }

    wiersz++;

    ptr_array[wiersz] = kursor;
  }

  return wiersz;
}

void write_int_line_cont(int *ptr_array[], int n) {
  int *kursor = ptr_array[n];
  int *endptr = ptr_array[n + 1];

  while (kursor != endptr) {
    printf("%d ", (*kursor * *kursor));
    kursor++;
  }
  printf("\n");
}

// 3
///////////////////////////////////////////////////////////

int read_char_lines(char *array[]) {
  char bufor[BUF_SIZE];
  int count = 0;

  while (fgets(bufor, BUF_SIZE, stdin) != NULL) {
    array[count] = malloc((strlen(bufor) + 1) * sizeof(char));

    if (array[count] != NULL) {
      strcpy(array[count], bufor);
      count++;
    }
  }
  return count;
}

void write_char_line(char *array[], int n) {
  if (array[n] != NULL) {
    printf("%s", array[n]);
  }
}

void delete_lines(char *array[]) {
  int i = 0;
  while (array[i] != NULL) {
    free(array[i]);
    array[i] = NULL;
    i++;
  }
}

// auxiliary
////////////////////////////////////////////////////////////

int read_int(void) {
  char c_buf[BUF_SIZE];
  fgets(c_buf, BUF_SIZE, stdin);
  return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
  const int to_do = read_int();

  int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
  int n, rowsA, colsA, rowsB, colsB;
  char *char_lines_array[TAB_SIZE] = {NULL};
  int continuous_array[TAB_SIZE];
  int *ptr_array[TAB_SIZE];

  switch (to_do) {
  case 1:
    scanf("%d %d", &rowsA, &colsA);
    read_mat(rowsA, colsA, A);
    scanf("%d %d", &rowsB, &colsB);
    read_mat(rowsB, colsB, B);
    prod_mat(rowsA, colsA, colsB, A, B, AB);
    print_mat(rowsA, colsB, AB);
    break;
  case 2:
    n = read_int() - 1; // we count from 1 :)
    ptr_array[0] = continuous_array;
    read_int_lines_cont(ptr_array);
    write_int_line_cont(ptr_array, n);
    break;
  case 3:
    n = read_int() - 1;
    read_char_lines(char_lines_array);
    write_char_line(char_lines_array, n);
    delete_lines(char_lines_array);
    break;
  default:
    printf("NOTHING TO DO FOR %d\n", to_do);
    break;
  }
  return 0;
}
