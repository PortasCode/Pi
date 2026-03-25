#include "tabela_akcje.h"
#include <stdio.h>

void przypisz_zera(float *t, int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    t[i] = 0;
  }
}

void przypisz_wartosc(float *t, float a, int indeks) { t[indeks] = a; }

void wypisz_wartosci(float *t, int a, int b) {
  for (int i = a; i <= b; i++) {
    printf("%f ", t[i]);
  }
  printf("\n");
}

float zwroc_sume(float *t, int a, int b) {
  float suma = 0;
  for (int i = a; i <= b; i++) {
    suma = suma + t[i];
  }
  return suma;
}

int ile_roznych(float *t, int rozmiar, float value) {
  int counter = 0;
  for (int i = 0; i < rozmiar; i++) {
    if (t[i] != value) {
      counter++;
    }
  }
  return counter;
}

void zamien_miejscami(float *t, int a, int b) {
  float temp = t[a];
  t[a] = t[b];
  t[b] = temp;
}
