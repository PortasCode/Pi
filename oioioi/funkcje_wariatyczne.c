#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double sum_var(int number, ...) {
  va_list args;
  double suma = 0;

  va_start(args, number);

  for (int i = 0; i < number; i++) {
    suma += va_arg(args, double);
  }

  va_end(args);
  return suma;
}

double average_var(int number, ...) {
  va_list args;
  double suma = 0;

  va_start(args, number);

  for (int i = 0; i < number; i++) {
    suma += va_arg(args, double);
  }

  va_end(args);

  return suma / number;
}

double median_var(int number, ...) {
  double tab[number];

  va_list args;
  va_start(args, number);

  for (int i = 0; i < number; i++) {
    tab[i] = va_arg(args, double);
  }

  va_end(args);

  double temp;
  for (int i = 0; i < number - 1; i++) {
    for (int j = 0; j < number - 1 - i; j++) {
      if (tab[j] > tab[j + 1]) {
        temp = tab[j];
        tab[j] = tab[j + 1];
        tab[j + 1] = temp;
      }
    }
  }
  if (number % 2 == 0) {
    return (tab[number / 2] + tab[(number - 1) / 2]) / 2;
  } else {
    return tab[number / 2];
  }
}

double min_var(int number, ...) {
  va_list args;
  va_start(args, number);
  double result;

  for (int i = 0; i < number; i++) {
    if (i == 0) {
      result = va_arg(args, double);
    } else {
      double temp = va_arg(args, double);
      if (temp < result) {
        result = temp;
      }
    }
  }

  va_end(args);

  return result;
}

double max_var(int number, ...) {
  va_list args;
  va_start(args, number);
  double result;

  for (int i = 0; i < number; i++) {
    if (i == 0) {
      result = va_arg(args, double);
    } else {
      double temp = va_arg(args, double);
      if (temp > result) {
        result = temp;
      }
    }
  }
  va_end(args);

  return result;
}

#define MAX_LINE 256
#define MAX_NUMBER 64
#define MAX_TEXTS 64

double sum(const int number, const double *values) {
  if (number == 0)
    return 0;
  double suma = 0;
  for (int i = 0; i < number; i++) {
    suma += values[i];
  }
  return suma;
}

double average(const int number, const double *values) {
  if (number == 0)
    return 0;
  return sum(number, values) / number;
}

double median(const int number, double *values) {
  if (number == 0)
    return 0;

  double temp;
  for (int i = 0; i < number - 1; i++) {
    for (int j = 0; j < number - 1 - i; j++) {
      if (values[j] > values[j + 1]) {
        temp = values[j];
        values[j] = values[j + 1];
        values[j + 1] = temp;
      }
    }
  }

  if (number % 2 == 0) {
    return (values[number / 2] + values[(number - 1) / 2]) / 2.0;
  } else {
    return values[number / 2];
  }
}

double min(const int number, const double *values) {
  if (number == 0)
    return 0;
  double result = values[0];

  for (int i = 1; i < number; i++) {
    if (values[i] < result) {
      result = values[i];
    }
  }
  return result;
}

double max(const int number, const double *values) {
  if (number == 0)
    return 0;
  double result = values[0];

  for (int i = 1; i < number; i++) {
    if (values[i] > result) {
      result = values[i];
    }
  }
  return result;
}

int read_from_line(char *c_buf, double *values, char **texts,
                   int *text_counter) {
  int val_count = 0;
  *text_counter = 0;

  char *word = strtok(c_buf, " \n");

  while (word != NULL) {
    char *endptr;
    double num = strtod(word, &endptr);

    if (endptr == word) {
      texts[*text_counter] = word;
      (*text_counter)++;
    } else if (*endptr == '\0') {
      values[val_count] = num;
      val_count++;
    } else {
      values[val_count] = num;
      val_count++;
      texts[*text_counter] = endptr;
      (*text_counter)++;
    }

    word = strtok(NULL, " \n");
  }
  return val_count;
}

int read_int(void) {
  char c_buf[MAX_LINE];
  fgets(c_buf, MAX_LINE, stdin);
  return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
  int number;
  double v1, v2, v3, v4, v5;

  char c_buf[MAX_LINE];
  double values[MAX_NUMBER];
  char *texts[MAX_TEXTS];
  int text_counter;

  const int to_do = read_int();

  switch (to_do) {
  case 1:
    number = 3;
    scanf("%lf%lf%lf", &v1, &v2, &v3);
    printf("%.2f %.2f %.2f %.2f %.2f\n", sum_var(number, v1, v2, v3),
           average_var(number, v1, v2, v3), median_var(number, v1, v2, v3),
           min_var(number, v1, v2, v3), max_var(number, v1, v2, v3));

    number = 5;
    scanf("%lf%lf%lf%lf%lf", &v1, &v2, &v3, &v4, &v5);
    printf("%.2f %.2f %.2f %.2f %.2f\n", sum_var(number, v1, v2, v3, v4, v5),
           average_var(number, v1, v2, v3, v4, v5),
           median_var(number, v1, v2, v3, v4, v5),
           min_var(number, v1, v2, v3, v4, v5),
           max_var(number, v1, v2, v3, v4, v5));
    break;
  case 2:
    fgets(c_buf, MAX_LINE, stdin);
    number = read_from_line(c_buf, values, texts, &text_counter);
    printf("%.2f %.2f %.2f %.2f %.2f\n", sum(number, values),
           average(number, values), median(number, values), min(number, values),
           max(number, values));

    for (int k = 0; k < text_counter; k++) {
      printf("%s\n", texts[k]);
    }
    break;
  default:
    printf("Nothing to do for n = %d\n", to_do);
    break;
  }

  return EXIT_SUCCESS;
}
