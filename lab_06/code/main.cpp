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

    array_t cities;
    create_cities(&cities, path.size_row);
    
    fill_cities(&cities);

    ant_colony_t colony;
    initialize_colony(&colony, &path);
    
    short_route_t shortest_route_ant, shortest_route_brute;
    shortest_route_brute.short_route.array = nullptr;
    shortest_route_brute.short_route.array = new int[path.size_row];
    shortest_route_brute.short_route.size_array = path.size_row;
    shortest_route_brute.length_short_route = 0;

    shortest_route_ant.short_route.array = nullptr;
    shortest_route_ant.short_route.array = new int[path.size_row];
    shortest_route_ant.short_route.size_array = path.size_row;
    shortest_route_ant.length_short_route = 0;

    int short_way_brute = find_short_way_by_brute_force(&cities, &shortest_route_brute, path.matrix);

    find_short_way_by_ant_algorithm(&shortest_route_ant, &path, &colony);

    printf("short_way_brute = %d\n", short_way_brute);
    std::cout << "(";
    for (int i = 0; i < shortest_route_brute.short_route.size_array; i++){
        std::cout <<  shortest_route_brute.short_route.array[i] << " ";
    }
    std::cout << ")" << std::endl;
    
    printf("short_way_ant = %d\n", shortest_route_ant.length_short_route);
    std::cout << "(";
    for (int i = 0; i < shortest_route_ant.short_route.size_array; i++){
        std::cout <<  shortest_route_ant.short_route.array[i] << " ";
    }
    std::cout << ")" << std::endl;

    
    return 0;
}