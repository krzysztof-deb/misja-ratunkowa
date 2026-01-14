#ifndef _UTILS_H
#define _UTILS_H

double random_double(double min, double max);

typedef struct{
    double w;
    double c1;
    double c2;
}Config;

Config load_config(char *file_name);

#endif