#ifndef _ANT_H_
#define _ANT_H_

#include <iostream>

#include "../matrix/matrix.h"
#include "../cities/cities.h"

typedef struct meta_data meta_t;
struct meta_data
{
    double koeff_evaporation;
    double alpha;
    double beta;
    double Q;
    double start_evaporation;
};

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
    meta_t meta_data_colony;
    ant_t *ants;
    matrix_double_t pheromon;
    matrix_double_t attractiveness;
};

typedef struct short_route short_route_t;
struct short_route
{
    int *short_route;
    int length_short_route;
};

ant_t *create_ants(int size_row, int size_column);
void find_short_way_by_ant_algorithm(short_route_t &shortest_route, matrix_int_t *path,
                                    ant_colony_t *colony);
void initialize_colony(ant_colony_t *colony, matrix_int_t *path);



#endif