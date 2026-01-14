#include "logger.h"
#include <stdio.h>

const char *file_name = "log.csv";

void init_log_file() {
  FILE *in = fopen(file_name, "w");
  if (in == NULL)
    return;
  fprintf(in, "Iteracja, najlepszy wynik\n");
  fclose(in);
}

void add_line_to_file(int iteration, double best) {
  FILE *in = fopen(file_name, "a");
  if (in == NULL)
    return;
  fprintf(in, "%d, %lf\n", iteration, best);
  fclose(in);
}
