#include "utils.h"
#include <stdlib.h>

double random_double(double min,double max){
    double liczba=0;
    liczba=min+((double)rand()/RAND_MAX)*(max-min);
    return liczba;
}