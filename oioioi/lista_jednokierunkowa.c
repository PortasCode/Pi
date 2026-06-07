#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define BUFFER_SIZE 1024

typedef void (*DataFp)(void *);
typedef void (*ConstDataFp)(const void *);
typedef int (*CompareDataFp)(const void *, const void *);

typedef struct ListElement {
  struct ListElement *next;
  void *data;
} ListElement;

typedef struct {
  ListElement *head;
  ListElement *tail;
  ConstDataFp dump_data;
  DataFp free_data;
  CompareDataFp compare_data;
  DataFp modify_data;
} List;

void *safe_malloc(const size_t size) {
  void *ptr = malloc(size);
  if (ptr)
    return ptr;
  printf("malloc error\n");
  exit(EXIT_FAILURE);
}

void *safe_strdup(const char *string) {
  void *ptr = safe_malloc(strlen(string) + 1);
  strcpy(ptr, string);
  return ptr;
}

// generic functions for any data type

void init_list(List *p_list, const ConstDataFp dump_data,
               const DataFp free_data, const CompareDataFp compare_data,
               const DataFp modify_data) {
  p_list->head = NULL;
  p_list->tail = NULL;
  p_list->dump_data = dump_data;
  p_list->free_data = free_data;
  p_list->compare_data = compare_data;
  p_list->modify_data = modify_data;
}

// Print elements of the list
void dump_list(const List *p_list) {
  ListElement *curr = p_list->head;
  while (curr != NULL) {
    p_list->dump_data(curr->data);
    curr = curr->next;
  }
  printf("\n");
}

// Print elements of the list if comparable to data
void dump_list_if(const List *p_list, const void *data) {
  ListElement *curr = p_list->head;
  while (curr != NULL) {
    if (p_list->compare_data(curr->data, data) == 0) {
      p_list->dump_data(curr->data);
    }
    curr = curr->next;
  }
  printf("\n");
}

// Remove the first element
void pop_front(List *p_list) {
  if (p_list->head == NULL)
    return;

  ListElement *to_delete = p_list->head;
  p_list->head = p_list->head->next;

  if (p_list->head == NULL) {
    p_list->tail = NULL;
  }

  if (p_list->free_data) {
    p_list->free_data(to_delete->data);
  }
  free(to_delete);
}

// Free all elements of the list
void free_list(List *p_list) {
  while (p_list->head != NULL) {
    pop_front(p_list);
  }
}

// Push element at the beginning of the list
void push_front(List *p_list, void *data) {
  ListElement *new_element = safe_malloc(sizeof(ListElement));
  new_element->data = data;
  new_element->next = p_list->head;
  p_list->head = new_element;

  if (p_list->tail == NULL) {
    p_list->tail = new_element;
  }
}

// Push element at the end of the list
void push_back(List *p_list, void *data) {
  ListElement *new_element = safe_malloc(sizeof(ListElement));
  new_element->data = data;
  new_element->next = NULL;

  if (p_list->tail == NULL) {
    p_list->head = new_element;
    p_list->tail = new_element;
  } else {
    p_list->tail->next = new_element;
    p_list->tail = new_element;
  }
}
// Reverse the list
void reverse(List *p_list) {
  ListElement *prev = NULL;
  ListElement *curr = p_list->head;
  ListElement *next = NULL;

  p_list->tail = p_list->head;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  p_list->head = prev;
}

// find an element in a sorted list after which to insert a given element
ListElement *find_insertion_point(const List *p_list,
                                  const ListElement *p_element) {
  ListElement *prev = NULL;
  ListElement *curr = p_list->head;

  while (curr != NULL) {
    if (p_list->compare_data(p_element->data, curr->data) <= 0) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  return prev;
}

// Insert element after 'previous'
void push_after(List *p_list, void *data, ListElement *previous) {
  if (previous == NULL) {
    push_front(p_list, data);
  } else {
    ListElement *new_element = safe_malloc(sizeof(ListElement));
    new_element->data = data;
    new_element->next = previous->next;
    previous->next = new_element;

    if (new_element->next == NULL) {
      p_list->tail = new_element;
    }
  }
}

// Insert element preserving order
void insert_in_order(List *p_list, void *p_data) {
  ListElement *curr = p_list->head;
  ListElement *prev = NULL;

  while (curr != NULL) {
    int cmp = p_list->compare_data(p_data, curr->data);
    if (cmp == 0) {
      if (p_list->modify_data) {
        p_list->modify_data(curr->data);
      }
      if (p_list->free_data) {
        p_list->free_data(p_data);
      }
      return;
    }
    if (cmp < 0) {
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  push_after(p_list, p_data, prev);
}

// type-specific definitions

// int element

void dump_int(const void *d) { printf("%d ", *(const int *)d); }

void free_int(void *d) { free(d); }

int cmp_int(const void *a, const void *b) {
  int val_a = *(const int *)a;
  int val_b = *(const int *)b;
  if (val_a < val_b)
    return -1;
  if (val_a > val_b)
    return 1;
  return 0;
}

int *create_data_int(const int v) {
  int *ptr = safe_malloc(sizeof(int));
  *ptr = v;
  return ptr;
}

// Word element

typedef struct DataWord {
  char *word;
  int counter;
} DataWord;

void dump_word(const void *d) {
  const DataWord *dw = (const DataWord *)d;
  printf("%s ", dw->word);
}

void dump_word_lowercase(const void *d) {
  const DataWord *dw = (const DataWord *)d;
  for (int i = 0; dw->word[i]; i++) {
    printf("%c", tolower((unsigned char)dw->word[i]));
  }
  printf(" ");
}

void free_word(void *d) {
  DataWord *dw = (DataWord *)d;
  free(dw->word);
  free(dw);
}

int cmp_word_alphabet(const void *a, const void *b) {
  const DataWord *wa = (const DataWord *)a;
  const DataWord *wb = (const DataWord *)b;
  return strcasecmp(wa->word, wb->word);
}

int cmp_word_counter(const void *a, const void *b) {
  const DataWord *wa = (const DataWord *)a;
  const DataWord *wb = (const DataWord *)b;
  return wa->counter - wb->counter;
}

void modify_word(void *p) {
  DataWord *dw = (DataWord *)p;
  dw->counter++;
}

void *create_data_word(const char *string, const int counter) {
  DataWord *dw = safe_malloc(sizeof(DataWord));
  dw->word = safe_strdup(string);
  dw->counter = counter;
  return dw;
}

// Read text, parse it to words, and insert those words to the list.
void stream_to_list(List *p_list, FILE *stream) {
  const char delimits[] = " \r\t\n.,?!:;-";
  char buffer[BUFFER_SIZE];

  while (fgets(buffer, BUFFER_SIZE, stream)) {
    char *token = strtok(buffer, delimits);
    while (token != NULL) {
      void *data = create_data_word(token, 1);
      if (p_list->compare_data != NULL) {
        insert_in_order(p_list, data);
      } else {
        push_back(p_list, data);
      }
      token = strtok(NULL, delimits);
    }
  }
}

// test an integer list
void list_test(List *p_list, const int n) {
  char op;
  int v;
  for (int i = 0; i < n; ++i) {
    scanf(" %c", &op);
    switch (op) {
    case 'f':
      scanf("%d", &v);
      push_front(p_list, create_data_int(v));
      break;
    case 'b':
      scanf("%d", &v);
      push_back(p_list, create_data_int(v));
      break;
    case 'd':
      pop_front(p_list);
      break;
    case 'r':
      reverse(p_list);
      break;
    case 'i':
      scanf("%d", &v);
      insert_in_order(p_list, create_data_int(v));
      break;
    default:
      printf("No such operation: %c\n", op);
      break;
    }
  }
}

int main(void) {
  int to_do, n;
  List list;

  scanf("%d", &to_do);
  switch (to_do) {
  case 1: // test an integer list
    scanf("%d", &n);
    init_list(&list, dump_int, free_int, cmp_int, NULL);
    list_test(&list, n);
    dump_list(&list);
    free_list(&list);
    break;
  case 2: // read words from a text, insert into a list, and print
    init_list(&list, dump_word, free_word, NULL, NULL);
    stream_to_list(&list, stdin);
    dump_list(&list);
    free_list(&list);
    break;
  case 3: // read words, insert into a list alphabetically, print words
          // encountered n times
    scanf("%d", &n);
    init_list(&list, dump_word_lowercase, free_word, cmp_word_alphabet,
              modify_word);
    stream_to_list(&list, stdin);
    list.compare_data = cmp_word_counter;
    const DataWord data = {NULL, n};
    dump_list_if(&list, &data);
    free_list(&list);
    break;
  default:
    printf("NOTHING TO DO FOR %d\n", to_do);
    break;
  }
  return 0;
}
