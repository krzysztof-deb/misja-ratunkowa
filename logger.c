#include "logger.h"
#include "pso.h"
#include <stdio.h>

const char *file_name = "log.csv";

void save_positions( Swarm *s, int iteration){
  FILE *in=fopen(file_name,"a");
  if(in==NULL)return;
  for(int i=0;i<s->count;i++){
    fprintf(in,"%d;%d;%lf;%lf\n",iteration,i,s->d[i].x,s->d[i].y);
  }
  fclose(in);
}
