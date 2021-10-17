#include <iostream>
#include <chrono>
#include "../includes/matrix.hpp"
#include "../includes/threads.hpp"
#include "../includes/time_measure.hpp"
#include "../includes/constants.hpp"

void measure_time_consistent()
{
    int matrix_sizes[6] = {100, 250, 500, 1000, 1500, 2000};
    double *avg_time_consistently = new double[6]{};

    std::chrono::duration<double> time_span;
    std::chrono::high_resolution_clock::time_point t1, t2;

    int **matrix = nullptr, size_matrix = 0;
    double sum_time = 0;

    for (int i = 0; i < 6; i++)
    {
        sum_time = 0;
        matrix = form_matrix(matrix_sizes[i]);
        form_random_values(&matrix, size_matrix);
        for (int j = 0; j < COUNT_REPEATS; j++)
        {
            t1 = std::chrono::high_resolution_clock::now();
            find_matrix_min_value(matrix, size_matrix);
            t2 = std::chrono::high_resolution_clock::now();

            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            sum_time += time_span.count();
        }
        avg_time_consistently[i] = sum_time / COUNT_REPEATS;
        free_matrix(matrix, size_matrix);
    }

    std::cout << "Последовательный алгоритм" << std::endl;
    for (int i = 0; i < 6; i++){
        std::cout << "Размер = " << matrix_sizes[i] << " Время = " << avg_time_consistently[i] << std::endl;
    }

    delete[] avg_time_consistently;
}

void measure_time_parallel()
{   /*
    int matrix_sizes[6] = {100, 250, 500, 1000, 1500, 2000};
    double **avg_times_parallel = nullptr;
    avg_times_parallel = form_matrix(6);

    std::chrono::duration<double> time_span;
    std::chrono::high_resolution_clock::time_point t1, t2;

    int **matrix = nullptr, size_matrix = 0;
    double sum_time = 0;

    int count_threads = 0;
    for (int i = 1; i < 32; i++)
    {
        count_threads = i;
        for (int j = 0; j < 6; j++)
        {
            sum_time = 0;
            matrix = form_matrix(matrix_sizes[j]);
            for (int k = 0; k < COUNT_REPEATS; k++)
            {
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
                time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
                sum_time += time_span.count();
            }
            avg_time_parallel[j] = sum_time / COUNT_REPEATS;
            free_matrix(matrix, size_matrix);
        }
    }
    std::cout << "Параллельный алгоритм (2 потока)" << std::endl;
    for (int i = 0; i < 6; i++){
        std::cout << "Размер = " << matrix_sizes[i] << " Время = " << avg_time_parallel_2[i] << std::endl;
    }
    delete[] avg_time_parallel_2;*/
}