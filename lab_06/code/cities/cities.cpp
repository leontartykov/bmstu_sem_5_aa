#include "cities.h"

void create_cities(array_t *cities, int size_array)
{
    (*cities).array = nullptr;
    (*cities).array = new int[size_array]{};
    (*cities).size_array = size_array;
}

void output_cities(array_t *cities)
{
    int size_array = (*cities).size_array;
    std::cout << "(";
    for (int i = 0; i < size_array; ++i){
        std::cout << (*cities).array[i] << " ";
    }
    std::cout << ")" << std::endl;
}

void fill_cities(array_t *cities)
{
    int size_array = (*cities).size_array;
    for (int i = 0; i < size_array; ++i){
        ((*cities).array)[i] = i;
    }
}
