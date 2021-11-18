#ifndef _ANT_H_
#define _ANT_H_

#include <iostream>

#include "../matrix/matrix.h"
#include "../cities/cities.h"

typedef struct ant ant_t;
struct ant
{
    array *visit_cities;
    int count_visited_cities;
    double visited_way_length;
};

typedef struct ant_colony ant_colony_t;
struct ant_colony
{
    int t_max;
    double koeff_evaporation;
    double alpha;
    double beta;
    double Q;
    double start_evaporation;
    ant_t *ants;
    matrix_double_t pheromon;
};



int find_short_way_by_ant_algorithm(matrix_int_t *path, ant_colony_t *colony);
void initialize_colony(ant_colony_t *colony, int size_row, int size_column);



#endif