#include "brute_force.h"

bool find_next_permutation(array_t *cities);
void swap_elems_array(int *array, int index_first, int index_second);
int find_way(array_t *cities, int **matrix);

int find_short_way_by_brute_force(array_t *cities, int **matrix)
{
    output_cities(cities);
    int short_length = 0, min_short_length = 0;
    int i = 0, min_i = 0;

    short_length = find_way(cities, matrix);
    min_short_length = short_length;
    i++;

    while (find_next_permutation(cities) == true)
    {
        output_cities(cities);
        short_length = find_way(cities, matrix);
        //printf("short_length = %d\n", short_length);
        if (short_length < min_short_length){
            min_short_length = short_length;
            min_i = i;
        }
        
        i++;
    }
    
    return min_short_length;
}

bool find_next_permutation(array_t *cities)
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

int find_way(array_t *cities, int **matrix)
{
    int short_length = 0;
    int size = (*cities).size_array;
    int index_i = 0, index_j = 0;
    //printf("short_length = %d\n", short_length);

    for (int i = 0; i < size - 1; i++)
    {
        index_i = (*cities).array[i];
        index_j = (*cities).array[i + 1];

        short_length += matrix[index_i][index_j];
        //printf("index_i = %d, index_j = %d, short_length = %d\n", index_i, index_j, short_length);
    }

    index_i = (*cities).array[size - 1];
    index_j = (*cities).array[0];
    short_length += matrix[index_i][index_j];

    return short_length;
}