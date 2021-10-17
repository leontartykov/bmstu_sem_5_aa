#include <iostream>
#include <chrono>
#include "../includes/matrix.hpp"
#include "../includes/threads.hpp"

int main()
{
    int size_matrix = 0, count_threads = 16;
    int **matrix = nullptr;
    size_matrix = input_matrix_size();
    std::cout << "Размер квадратной матрицы: " << size_matrix << std::endl;
    matrix = form_random_matrix(size_matrix);
    std::cout << "матрица" << std::endl;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int global_min_1 = find_matrix_min_value(matrix, size_matrix);
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Затраченное время (последовательно): " << time_span.count() << "секунд." << std::endl;

    std::cout << "Глобальный минимум = " << global_min_1 << std::endl;
   

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

    t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_threads; i++){
        pthread_create(threads + i, NULL, find_matrix_min_value_parallel, args + i);
    }
    

    for (int i = 0; i < count_threads; i++){
        pthread_join(threads[i], NULL);
    }
    int global_min = args[0].local_min;
    for (int i = 1; i < count_threads; i++){
        if (args[i].local_min < global_min)
            global_min = args[i].local_min;
    }
    t2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < count_threads; i++){
        std::cout << "\n\nloc = " << args[i].local_min << std::endl;
    }
    std::cout << "Глобальный минимум = " << global_min << std::endl;
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "Затраченное время (параллельно): " << time_span.count() << "секунд." << std::endl;

    return 0;
}