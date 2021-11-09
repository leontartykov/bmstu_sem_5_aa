#include "brute_force.h"

bool next_permutation(array_t *cities);
void swap_elems_array(int *array, int index_first, int index_second);

void calculate_permutations(array_t *cities)
{
    output_cities(cities);
    while (next_permutation(cities) == true){
        output_cities(cities);
    }
}

bool next_permutation(array_t *cities)
{
    int j = (*cities).size_array - 2;
    while (j != -1 && (*cities).array[j] >= (*cities).array[j + 1]){
        j--;
    }

    if (j == -1)
        return false;

    int k = (*cities).size_array - 1;
    while ((*cities).array[j] >= (*cities).array[k]){
        k--;
    }

    swap_elems_array(cities->array, j, k);
    int left = j + 1, right = (*cities).size_array - 1;

    while (left < right){
        swap_elems_array(cities->array, left++, right--);
    }

    return true;
}

void swap_elems_array(int *array, int index_first, int index_second)
{
    int temp = array[index_first];
    array[index_first] = array[index_second];
    array[index_second] = temp;
}