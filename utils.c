#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double random_double(double min, double max) {
  double liczba = 0;
  liczba = min + ((double)rand() / RAND_MAX) * (max - min);
  return liczba;
}
void load_config(char *file_name, double *w, double *c_1, double *c_2) {
  FILE *conf = fopen(file_name, "r");
  if (conf != NULL) {
    fscanf(conf, "%lf %lf %*f %lf %*f", w, c_1, c_2);
    fclose(conf);
  } else {
    fprintf(stderr, "Błąd otwierania pliku konfiguracyjnego!\n");
  }
}
