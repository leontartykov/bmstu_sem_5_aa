#include <iostream>
#include <chrono>
#include <iomanip>
#include "../includes/matrix.hpp"
#include "../includes/threads.hpp"
#include "../includes/time_measure.hpp"
#include "../includes/constants.hpp"

double *measure_time_consistent(int *matrix_sizes, int size_matrix_sizes)
{
    double *avg_time_consistently = new double[6]{};

    std::chrono::duration<double> time_span;
    std::chrono::high_resolution_clock::time_point t1, t2;

    int **matrix = nullptr, size_matrix = 0;
    double sum_time = 0;

    for (int i = 0; i < size_matrix_sizes; i++)
    {
        sum_time = 0;
        size_matrix = matrix_sizes[i];
        matrix = form_matrix_int(size_matrix);
        form_random_values(&matrix, size_matrix);
        
        for (int j = 0; j < COUNT_REPEATS; j++)
        {
            t1 = std::chrono::high_resolution_clock::now();
            find_matrix_min_value(matrix, size_matrix);
            t2 = std::chrono::high_resolution_clock::now();

            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
            sum_time += time_span.count();
        }
        sum_time /= COUNT_REPEATS;
        avg_time_consistently[i] = sum_time;
        free_matrix_int(matrix, size_matrix);
    }

    return avg_time_consistently;
}

double **measure_time_parallel(int *matrix_sizes, int size_matrix_sizes)
{   
    double **avg_times_parallel = nullptr;
    avg_times_parallel = form_matrix_double(size_matrix_sizes);

    std::chrono::duration<double> time_span;
    std::chrono::high_resolution_clock::time_point t1, t2;

    int **matrix = nullptr, size_matrix = 0;
    double sum_time = 0;
    int inc_thread = 0;
    
    for (int count_threads = 1; count_threads <= 32; count_threads *= 2)
    {
        for (int i = 0; i < size_matrix_sizes; i++)
        {
            sum_time = 0;
            size_matrix = matrix_sizes[i];
            matrix = form_matrix_int(size_matrix);
            pthread_t *threads = new pthread_t[count_threads];
            pthread_args_t *args = new pthread_args_t[count_threads];

            args_t *args_matrix = new args_t[1];
            args_matrix->matrix = matrix;
            args_matrix->size_row = size_matrix;
            args_matrix->size_column = size_matrix;
            for (int j = 0; j < count_threads; j++)
            {
                args[j].thread_id = j;
                args[j].count_threads = count_threads;
                args[j].matrix_size = size_matrix;
                args[j].args = args_matrix;
                args[j].local_min = 0;   
            }

            for (int j = 0; j < COUNT_REPEATS; j++)
            {
                t1 = std::chrono::high_resolution_clock::now();
                for (int k = 0; k < count_threads; k++){
                    pthread_create(threads + k, NULL, find_matrix_min_value_parallel, args + k);
                }
                
                for (int k = 0; k < count_threads; k++){
                    pthread_join(threads[k], NULL);
                }
                t2 = std::chrono::high_resolution_clock::now();
                int global_min = args[0].local_min;
                for (int i = 1; i < count_threads; i++){
                    if (args[i].local_min < global_min)
                        global_min = args[i].local_min;
                }
                time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
                sum_time += time_span.count();
            }
            avg_times_parallel[inc_thread][i] = sum_time / COUNT_REPEATS;            
            free_matrix_int(matrix, size_matrix);
        }
        inc_thread++;
    }

    return avg_times_parallel;
}

void output_table_time(double *avg_time_consistent, double **avg_time_parallel)
{
    int count_size_matrixes = 6;
    int matrix_sizes[count_size_matrixes] = {100, 250, 500, 1000, 2000, 3000};
    std::cout << "Таблица времени реализации последовательного и параллельного алгоритмов:" << std::endl;
    std::cout << "Размер матрицы |Последовательный| 1 поток        | 2 потока       | 4 потока       |"
                 " 8 потоков      | 16  потоков    | 32 потока      |" \
              << std::endl;
    std::cout << "------------------------------------------------------------------------------------"
                 "---------------------------------------------------" << std::endl;

    for (int i = 0; i < count_size_matrixes; i++)
    {
        std::cout << "\t" << std::left << std::setw(7) << matrix_sizes[i] << "| " \
                    << std::left << std::setw(15) << avg_time_consistent[i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[0][i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[1][i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[2][i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[3][i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[4][i] << "| " \
                    << std::left << std::setw(15) << avg_time_parallel[5][i] << "| " << std::endl;
    }
}