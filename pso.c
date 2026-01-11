#include "pso.h"
#include "map.h"
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

int init_swarm(Swarm *s, Map *m, double w, double c_1, double c_2, int count) {
  s->count = count;
  s->w = w;
  s->c_1 = c_1;
  s->c_2 = c_2;
  s->gBest_val = -1000;
  s->gBest_x = 0;
  s->gBest_y = 0;
  s->d = (Dron *)malloc(sizeof(Dron) * count);
  if (s->d != NULL) {
    for (int i = 0; i < count; i++) {
      double x = (double)rand() / RAND_MAX * m->width;
      double y = (double)rand() / RAND_MAX * m->height;
      s->d[i].x = x;
      s->d[i].y = y;
      double val = get_map_value(m, x, y);
      s->d[i].val = val;
      s->d[i].pBest_val = val;
      s->d[i].pBest_x = x;
      s->d[i].pBest_y = y;
      s->d[i].v_x = (double)rand() / RAND_MAX * 2.0 - 1;
      s->d[i].v_y = (double)rand() / RAND_MAX * 2.0 - 1;
      if (i == 0 || val > s->gBest_val) {
        s->gBest_val = val;
        s->gBest_x = x;
        s->gBest_y = y;
      }
    }
    return 0;
  } else {
    fprintf(stderr, "Błąd przy allokowaniu pamięci dla dronów w roju!");
    return -1;
  }
}
void free_swarm(Swarm *s) {
  if (s != NULL) {
    free(s->d);
    return;
  } else
    return;
}
void update_swarm(Swarm *s, Map *m) {
  if (s == NULL || m == NULL)
    return;
  for (int i = 0; i < s->count; i++) {
    double r_1 = (double)rand() / RAND_MAX;
    double r_2 = (double)rand() / RAND_MAX;
    double v_x = s->d[i].v_x;
    s->d[i].v_x = v_x * s->w + s->c_1 * r_1 * (s->d[i].pBest_x - s->d[i].x) +
                  s->c_2 * r_2 * (s->gBest_x - s->d[i].x);
    s->d[i].x = s->d[i].x + s->d[i].v_x;
    double v_y = s->d[i].v_y;
    s->d[i].v_y = v_y * s->w + s->c_1 * r_1 * (s->d[i].pBest_y - s->d[i].y) +
                  s->c_2 * r_2 * (s->gBest_y - s->d[i].y);
    s->d[i].y = s->d[i].y + s->d[i].v_y;
    double val = get_map_value(m, s->d[i].x, s->d[i].y);
    s->d[i].val = val;
    if (val > s->d[i].pBest_val) {
      s->d[i].pBest_val = val;
      s->d[i].pBest_x = s->d[i].x;
      s->d[i].pBest_y = s->d[i].y;
      if (val > s->gBest_val) {
        s->gBest_val = val;
        s->gBest_x = s->d[i].x;
        s->gBest_y = s->d[i].y;
      }
    }
  }
  return;
}
