#include <iostream>

#include "./matrix/matrix.h"
#include "./brute_force/brute_force.h"
#include "./file/file.h"
#include "./cities/cities.h"

int main(int args, char *argv[])
{
    path_t path;

    parser_file(argv[1], &path);
    output_matrix(path.matrix, path.size_row, path.size_column);

    array_t cities;
    create_cities(&cities, path.size_row);
    
    fill_cities(&cities);
    
    
    calculate_permutations(&cities);

    
    return 0;
}