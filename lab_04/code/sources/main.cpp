#include <iostream>
#include "../includes/array.hpp"
#include "../includes/sort.hpp"

int main()
{
    int size_array = 0;
    size_array = input_array_size();
    std::cout << "Размер массива: " << size_array << std::endl;
    int *array = nullptr;
    array = form_random_array(size_array);
    output_array(array, size_array);

    //merge_sort_consistently(array, size_array - 1);
    merge_sort_parallel(array, size_array);

    std::cout << "Упорядоченный массив: " << std::endl;
    output_array(array, size_array);
    delete[] array;
    return 0;
}