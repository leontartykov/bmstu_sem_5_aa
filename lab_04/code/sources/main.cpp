#include <iostream>
#include <chrono>
#include "../includes/array.hpp"
#include "../includes/sort.hpp"


int main()
{
    int size_array = 0;
    size_array = input_array_size();
    std::cout << "Размер массива: " << size_array << std::endl;
    int *array = nullptr, *temp_array = nullptr;
    array = form_random_array(size_array);
    temp_array = form_random_array(size_array);
    std::cout << "Изначальный массив 1: " << std::endl;
    output_array(array, size_array);
    merge_sort_consistently(array, temp_array, 0, size_array - 1);
    /*
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Затраченное время (последовательно): " << time_span.count() << "секунд." << std::endl;*/
    std::cout << "Упорядоченный массив 1: " << std::endl;
    output_array(array, size_array);
    

    delete[] array;
    return 0;
}