#ifndef _CITIES_H_
#define _CITIES_H_

#include <iostream>

typedef struct array array_t;
struct array
{
    int *array;
    int size_array;
};

void create_cities(array_t *cities, int size_array);
void output_cities(array_t *cities);
void fill_cities(array_t *cities);

#endif