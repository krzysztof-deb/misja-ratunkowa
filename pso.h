#ifndef PSO_H
#define PSO_H
#include "map.h"

typedef struct {
  double x, y;
  double v_x, v_y;
  double pBest_val, pBest_x, pBest_y;
  double val;
} Dron;
typedef struct {
  Dron *d;
  int count;
  double gBest_val, gBest_x, gBest_y;
  double w, c_1, c_2;
} Swarm;

int init_swarm(Swarm *s, Map *m, double w, double c_1, double c_2, int count);
void free_swarm(Swarm *s);
void update_swarm(Swarm *s, Map *m);
#endif
