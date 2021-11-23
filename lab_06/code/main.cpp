#include <iostream>

#include "./ant/ant.h"
#include "./matrix/matrix.h"
#include "./brute_force/brute_force.h"
#include "./file/file.h"
#include "./cities/cities.h"


int main(int args, char *argv[])
{
    matrix_int_t path;

    parser_file(argv[1], &path);
    output_matrix(path.matrix, path.size_row, path.size_column);

    array_t cities;
    create_cities(&cities, path.size_row);
    
    fill_cities(&cities);

    ant_colony_t colony;
    initialize_colony(&colony, &path);
    
    //int short_way_brute = find_short_way_by_brute_force(&cities, path.matrix);
    short_route_t shortest_route;
    shortest_route.short_route = new int[path.size_row];
    shortest_route.length_short_route = 0;

    find_short_way_by_ant_algorithm(shortest_route, &path, &colony);

    //printf("short_way_brute = %d\n", short_way_brute);
    printf("short_way_ant = %d\n", shortest_route.length_short_route);

    
    return 0;
}