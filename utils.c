#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

double random_double(double min,double max){
    double liczba=0;
    liczba=min+((double)rand()/RAND_MAX)*(max-min);
    return liczba;
}
Config load_config(char *file_name){
    FILE *in=fopen(file_name,"r");
    Config wartosci={0,0,0};
    if(in==NULL)return wartosci;
    double liczba;
    char napis[50];
    while(fscanf(in,"%s %lf",napis,&liczba)==2){
       if(strcmp(napis,"w")==0){
        wartosci.w=liczba;
       }
       else if(strcmp(napis,"c1")==0){
        wartosci.c1=liczba;
       } 
       else if(strcmp(napis,"c2")==0){
        wartosci.c2=liczba;
       } 
    }
    fclose(in);
    return wartosci;
    
}