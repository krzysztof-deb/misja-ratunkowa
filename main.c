#include "logger.h"
#include "map.h"
#include "pso.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
/* /pso <plik_mapy> -p <liczba_czastek> -i <liczba_iteracji> -c
<plik_konfiguracyjny z parametrami_PSO> -n <co_ktora_iteracje_zapis_postepow> */
void print_usage(char *prog_name) {
  fprintf(stderr, "Użycie: %s <plik_mapy> [-p n] [-i n] [-c plik] [-n n]\n",
          prog_name);
  fprintf(stderr, "Opcje: \n");
  fprintf(stderr, " -p <int>      Liczba dronów(domyślnie 30)\n");
  fprintf(stderr, " -i <int>      Liczba iteracji(domyślnie 100)\n");
  fprintf(stderr,
          " -c <ścieżka>  Ścieżka pliku konfiguracyjnego z parametrami PSO\n");
  fprintf(stderr, " -n <int>      Częstotliwość zapisu danych(domyślnie 0)\n");
}
int main(int argc, char *argv[]) {
  srand(time(NULL));
  int dron_count = 30;
  int iterations = 100;
  int log_interval = 0;
  char *config_file = NULL;
  char *map_file = NULL;

  int opt;
  while ((opt = getopt(argc, argv, "p:i:c:n:")) != -1) {
    switch (opt) {
    case 'p':
      dron_count = atoi(optarg);
      break;
    case 'i':
      iterations = atoi(optarg);
      break;
    case 'c':
      config_file = optarg;
      break;
    case 'n':
      log_interval = atoi(optarg);
      break;
    default:
      print_usage(argv[0]);
      return 1;
    }
  }
  if (optind < argc) {
    map_file = argv[optind];
  } else {
    fprintf(stderr, "Błąd: Nie podano pliku mapy!\n");
    print_usage(argv[0]);
    return 1;
  }

  Map *map = load_map(map_file);
  if (map == NULL) {
    fprintf(stderr, "Błąd: Mapa sie nie wczytała");
    return 1;
  }
  double w = 0.5;
  double c_1 = 1;
  double c_2 = 1;
  if (config_file != NULL) {
    load_config(config_file, &w, &c_1, &c_2);
  }

  Swarm *s = malloc(sizeof(Swarm));
  if (s != NULL) {
    if (init_swarm(s, map, w, c_1, c_2, dron_count) == -1) {
      fprintf(stderr, "Błąd przy alokacji pamięci dla inicjalizacji roju!\n");
      free_map(map);
      return 1;
    }
  } else {
    fprintf(stderr, "Błąd przy alokacji pamięci dla roju!\n");
    free_map(map);
    return 1;
  }

  if (log_interval > 0)
    init_log_file();

  for (int i = 0; i < iterations; i++) {
    update_swarm(s, map);
    if (log_interval > 0 && (i % log_interval == 0))
      add_line_to_file(i, s->gBest_val);
  }

  printf("Symulacja zakończona!\n");
  printf("Najlepsza znaleziona wartość sygnału %lf\n", s->gBest_val);
  printf("Współrzędne źródła: X = %d, Y = %d\n", (int)s->gBest_x,
         (int)s->gBest_y);

  free_swarm(s);
  free(s);
  free_map(map);
  return 0;
}
