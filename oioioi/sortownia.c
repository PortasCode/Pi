#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int day;
  int month;
  int year;
} Date;

#define NAME_MAX 20
#define FOOD_MAX 30
#define RECORD_MAX 64

typedef struct {
  char name[NAME_MAX];
  float price;
  int amount;
  Date exp_date;
} Food;

typedef int (*CompareFp)(const void *, const void *);

int cmp_date(const void *d1, const void *d2) {
  const Date *a = (const Date *)d1;
  const Date *b = (const Date *)d2;
  if (a->year != b->year)
    return a->year - b->year;
  if (a->month != b->month)
    return a->month - b->month;
  return a->day - b->day;
}

int cmp(const void *a, const void *b) {
  const Food *f1 = (const Food *)a;
  const Food *f2 = (const Food *)b;

  int name_cmp = strcmp(f1->name, f2->name);
  if (name_cmp != 0)
    return name_cmp;

  if (f1->price < f2->price)
    return -1;
  if (f1->price > f2->price)
    return 1;

  return cmp_date(&f1->exp_date, &f2->exp_date);
}

void *bsearch2(const void *key, const void *base, const size_t n_items,
               const size_t size, const CompareFp compare, bool *result) {
  const char *ptr = (const char *)base;
  size_t left = 0;
  size_t right = n_items;

  while (left < right) {
    size_t mid = left + (right - left) / 2;
    const void *mid_elem = ptr + mid * size;
    int cmp_res = compare(key, mid_elem);

    if (cmp_res == 0) {
      *result = true;
      return (void *)mid_elem;
    } else if (cmp_res > 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  *result = false;
  return (void *)(ptr + left * size);
}

Food *add_record(const Food *tab, int *np, const CompareFp compare,
                 const Food *new) {
  bool found = false;
  Food *t = (Food *)tab;

  Food *pos = (Food *)bsearch2(new, t, *np, sizeof(Food), compare, &found);

  if (found) {
    pos->amount += new->amount;
    return pos;
  } else {
    int index = pos - t;
    for (int i = *np; i > index; i--) {
      t[i] = t[i - 1];
    }
    t[index] = *new;
    (*np)++;
    return &t[index];
  }
}

int read_goods(Food *tab, FILE *stream, const int sorted) {
  int n_lines;
  char buff[RECORD_MAX];

  if (!fgets(buff, RECORD_MAX, stream))
    return 0;
  sscanf(buff, "%d", &n_lines);

  int current_n = 0;
  for (int i = 0; i < n_lines; i++) {
    Food f;
    if (!fgets(buff, RECORD_MAX, stream))
      break;

    sscanf(buff, "%s %f %d %d.%d.%d", f.name, &f.price, &f.amount,
           &f.exp_date.day, &f.exp_date.month, &f.exp_date.year);

    if (sorted == 1) {
      add_record(tab, &current_n, cmp, &f);
    } else {
      tab[current_n++] = f;
    }
  }
  return current_n;
}

void print_art(Food *p, const int n, const char *art) {
  for (int i = 0; i < n; i++) {
    if (strcmp(p[i].name, art) == 0) {
      printf("%.2f %d %02d.%02d.%04d\n", p[i].price, p[i].amount,
             p[i].exp_date.day, p[i].exp_date.month, p[i].exp_date.year);
    }
  }
}

int cmp_food_date(const void *a, const void *b) {
  const Food *f1 = (const Food *)a;
  const Food *f2 = (const Food *)b;
  return cmp_date(&f1->exp_date, &f2->exp_date);
}

float value(Food *food_tab, const size_t n, const Date curr_date,
            const int days) {
  struct tm t = {0};
  t.tm_mday = curr_date.day + days;
  t.tm_mon = curr_date.month - 1;
  t.tm_year = curr_date.year - 1900;

  mktime(&t);

  Date target;
  target.day = t.tm_mday;
  target.month = t.tm_mon + 1;
  target.year = t.tm_year + 1900;

  qsort(food_tab, n, sizeof(Food), cmp_food_date);

  Food dummy = {0};
  dummy.exp_date = target;
  bool found;
  Food *pos = (Food *)bsearch2(&dummy, food_tab, n, sizeof(Food), cmp_food_date,
                               &found);

  float total_value = 0.0f;
  if (found) {
    int index = pos - food_tab;

    int left = index;
    while (left >= 0 && cmp_date(&food_tab[left].exp_date, &target) == 0) {
      total_value += food_tab[left].price * food_tab[left].amount;
      left--;
    }

    int right = index + 1;
    while (right < (int)n &&
           cmp_date(&food_tab[right].exp_date, &target) == 0) {
      total_value += food_tab[right].price * food_tab[right].amount;
      right++;
    }
  }

  return total_value;
}

int read_int() {
  char buff[RECORD_MAX];
  int value;
  fgets(buff, RECORD_MAX, stdin);
  sscanf(buff, "%d", &value);
  return value;
}

int main(void) {
  int n;
  Food food_tab[FOOD_MAX];
  char buff[RECORD_MAX];
  const int to_do = read_int();

  switch (to_do) {
  case 1:
    n = read_goods(food_tab, stdin, 1);
    scanf("%s", buff);
    print_art(food_tab, n, buff);
    break;
  case 2:
    n = read_goods(food_tab, stdin, 0);
    Date curr_date;
    int days;
    scanf("%d.%d.%d", &curr_date.day, &curr_date.month, &curr_date.year);
    scanf("%d", &days);
    printf("%.2f\n", value(food_tab, (size_t)n, curr_date, days));
    break;
  default:
    printf("NOTHING TO DO FOR %d\n", to_do);
  }
  return 0;
}
