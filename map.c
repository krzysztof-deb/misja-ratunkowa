#include "map.h"
#include <stdio.h>
#include <stdlib.h>

Map *load_map(const char *filename) {
  int r, c;
  FILE *f = fopen(filename, "r");
  Map *m = NULL;

  if (f != NULL) {
    if (fscanf(f, "%d %d", &r, &c) != 2) {
      fprintf(stderr, "Złe dane rozmiaru mapy w pliku %s\n", filename);
      fclose(f);
      return NULL;
    }
    m = malloc(sizeof(Map));
    if (m != NULL) {
      m->width = c;
      m->height = r;
      m->val = (double **)malloc(sizeof(double *) * r);
      if (m->val != NULL) {
        for (int i = 0; i < r; i++) {
          m->val[i] = (double *)malloc(sizeof(double) * c);
          if (m->val[i] == NULL) {
            for (int j = 0; j < i; j++) {
              free(m->val[j]);
            }
            free(m->val);
            free(m);
            fclose(f);
            return NULL;
          }
        }
        for (int ir = 0; ir < r; ir++) {
          for (int ic = 0; ic < c; ic++) {
            if (fscanf(f, "%lf", &m->val[ir][ic]) != 1) {
              fprintf(stderr, "Złe dane mapy w pliku %s\n", filename);
              for (int i = 0; i < r; i++)
                free(m->val[i]);
              free(m->val);
              free(m);
              fclose(f);
              return NULL;
            }
          }
        }
      } else {
        free(m);
        fclose(f);
        return NULL;
      }
    } else {
      fclose(f);
      return NULL;
    }
    fclose(f);
  } else {
    fprintf(stderr, "Nie mogę otworzyć pliku o nazwie: %s\n", filename);
  }
  return m;
}
void free_map(Map *map) {
  for (int i = 0; i < map->height; i++) {
    free(map->val[i]);
  }
  free(map->val);
  free(map);
  return;
}
double get_map_value(Map *map, double x, double y);
