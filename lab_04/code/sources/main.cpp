#include <iostream>
#include <chrono>
#include "../includes/array.hpp"
#include "../includes/sort.hpp"
#include "../includes/threads.hpp"



int main()
{
    int size_array = 0, count_threads = 4;
    int *array = nullptr, *temp_array = nullptr;

    pthread_t *threads = new pthread_t[count_threads];
    pthread_args_t *args_array = new pthread_args_t[count_threads];
    
    
    size_array = input_array_size();
    std::cout << "Размер массива: " << size_array << std::endl;
    
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
    std::cout << "Упорядоченный массив (последовательный алгоритм): " << std::endl;
    output_array(array, size_array);

    args_t *sort_args = new args_t[count_threads];
    sort_args->array = nullptr, sort_args->temp_array = nullptr;
    sort_args->array = form_random_array(size_array);
    sort_args->temp_array = form_random_array(size_array);
    sort_args->low = 0;
    sort_args->high = size_array;
    for (int i = 0; i < count_threads; i++)
    {
        args_array[i].thread_id = i;
        args_array[i].count_threads = count_threads;
        args_array[i].array_size = size_array;
        args_array[i].sort_args = sort_args;
    }

    delete[] array;
    return 0;
}