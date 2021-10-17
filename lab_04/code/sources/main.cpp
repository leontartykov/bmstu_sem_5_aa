#include <iostream>
#include <chrono>
#include "../includes/matrix.hpp"
#include "../includes/threads.hpp"

int main()
{
    int size_matrix = 0, count_threads = 4;
    int **matrix = nullptr;
    size_matrix = input_matrix_size();
    std::cout << "Размер квадратной матрицы: " << size_matrix << std::endl;
    matrix = form_random_matrix(size_matrix);
    std::cout << "матрица" << std::endl;
    output_matrix(matrix, size_matrix);

    std::cout << "Минимум матрицы = " << find_matrix_min_value(matrix, size_matrix) << std::endl;

    pthread_t *threads = new pthread_t[count_threads];
    pthread_args_t *args = new pthread_args_t[count_threads];

    args_t *args_matrix = new args_t[1];
    args_matrix->matrix = matrix;
    args_matrix->size_row = size_matrix;
    args_matrix->size_column = size_matrix;

    for (int i = 0; i < count_threads; i++)
    {
        args[i].thread_id = i;
        args[i].count_threads = count_threads;
        args[i].matrix_size = size_matrix;
        args[i].args = args_matrix;
        args[i].local_min = 0;   
    }

    for (int i = 0; i < count_threads; i++){
        pthread_create(threads + i, NULL, find_matrix_min_value_parallel, args + i);
    }

    for (int i = 0; i < count_threads; i++){
        pthread_join(threads[i], NULL);
    }

    std::cout << "Loc[0] = " << args[0].local_min << std::endl;
    std::cout << "Loc[1] = " << args[1].local_min << std::endl;
    std::cout << "Loc[2] = " << args[2].local_min << std::endl;
    std::cout << "Loc[3] = " << args[3].local_min << std::endl;

    //merge_sort_consistently(array, temp_array, 0, size_array - 1);
    /*
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size_array; i++){
        array[i] *= 2 - 50;
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Затраченное время (последовательно): " << time_span.count() << "секунд." << std::endl;
    

    pthread_t *threads = new pthread_t[count_threads];
    pthread_args_t *args_array = new pthread_args_t[1];

    args_t *sort_args = new args_t[count_threads];
    sort_args->array = nullptr, sort_args->temp_array = nullptr;
    sort_args->array = form_random_array(size_array);
    std::cout << "Изначальный массив 1: " << std::endl;
    output_array(sort_args->array, size_array);
    sort_args->temp_array = form_random_array(size_array);


    sort_t *sort_data = new sort_t[count_threads];

    for (int i = 0; i < count_threads; i++)
    {
        args_array[i].thread_id = i;
        args_array[i].count_threads = count_threads;
        args_array[i].array_size = size_array;
        args_array[i].sort_args = sort_args;
        
    }
    
    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_threads; i++){
        pthread_create(threads + i, NULL, double_value, args_array + i);
    }

    t2 = std::chrono::high_resolution_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Затраченное время (параллельно): " << time_span.count() << "секунд." << std::endl;
    for (int i = 0; i < count_threads; i++){
        pthread_join(threads[i], NULL);
    }*/
    /*
    std::cout << "Удвоенный массив первого потока: " << std::endl;
    int *array_1 = args_array[0].sort_args->array;
    output_array(array_1, size_array);

    std::cout << "Удвоенный массив второго потока: " << std::endl;
    int *array_2 = args_array[1].sort_args->array;
    output_array(array_2, size_array);*/

    /*
    std::cout << "Результат третьего потока: " << std::endl;
    int *array_3 = args_array[2].sort_args->array;
    output_array(array_3, size_array);


    std::cout << "Результат четвертого потока: " << std::endl;
    int *array_4 = args_array[3].sort_args->array;
    output_array(array_4, size_array);*/


    //delete[] array;
    return 0;
}