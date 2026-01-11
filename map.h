#ifndef MAP_H
#define MAP_H

typedef struct {
  int width;
  int height;
  double **val;
} Map;

Map *load_map(const char *filename);
void free_map(Map *map);
double get_map_value(Map *map, double x, double y);

#endif
