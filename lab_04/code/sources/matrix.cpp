#include <iostream>
#include <new>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>
#include "../includes/matrix.hpp"
#include "../includes/constants.hpp"
#include "../includes/threads.hpp"

void free_array_double(double *avg_time_consistent);

int input_matrix_size()
{
    int size_array = 0;
    int flag_correct = INCORRECT_INPUT;
    while(flag_correct == INCORRECT_INPUT)
    {
        std::cout << "Введите размер массива: ";
        std::cin >> size_array;
        if (std::cin.fail() || size_array < 1)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неверный ввод размера массива. Повторите еще раз.\n";
        }
        else
            flag_correct = CORRECT_INPUT;
    }
    
    return size_array;
}

int **form_matrix_int(int size_matrix)
{
    std::srand(static_cast<unsigned int>(time(0)));
    int **matrix = nullptr;
    matrix = new int *[size_matrix];

    for (int i = 0; i < size_matrix; i++){
        matrix[i] = new int[size_matrix]{};
    }

    return matrix;
}

double **form_matrix_double(int size_matrix)
{
    std::srand(static_cast<unsigned int>(time(0)));
    double **matrix = nullptr;
    matrix = new double *[size_matrix];

    for (int i = 0; i < size_matrix; i++){
        matrix[i] = new double[size_matrix]{};
    }

    return matrix;
}

void form_random_values(int ***matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++){
            (*matrix)[i][j] = MIN_RAND_VALUE + rand() % (MAX_RAND_VALUE - MIN_RAND_VALUE + 1);
        }
    }
}

void output_matrix(int **matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

int find_matrix_min_value(int **matrix, int size_matrix)
{
    int min = matrix[0][0], local_min = matrix[0][0];
    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++)
        {
            if (matrix[i][j] < local_min)
                local_min = matrix[i][j];
        }
        if (local_min < min)
            min = local_min;
    }
    return min;
}

void *find_matrix_min_value_parallel(void *args)
{
    pthread_args_t *mult_args = (pthread_args_t *)args;
    int row_start = mult_args->thread_id * (mult_args->matrix_size / mult_args->count_threads);
    int row_end = (mult_args->thread_id + 1)* (mult_args->matrix_size / mult_args->count_threads);
    int **matrix = mult_args->args->matrix;
    mult_args->local_min = matrix[0][0];

    for (int i = row_start; i < row_end; i++)
    {
        for (int j = 0; j < mult_args->matrix_size; j++)
        {
            if (matrix[i][j] < mult_args->local_min)
                mult_args->local_min = matrix[i][j];
        }
    }

    return NULL;
}

void free_arrays(double *avg_time_consistent, double **avg_time_parallel, int size_matrix)
{
    free_array_double(avg_time_consistent);
    free_matrix_double(avg_time_parallel, size_matrix);
}

void free_array_double(double *avg_time_consistent)
{
    delete[] avg_time_consistent;
    avg_time_consistent = nullptr;
}

void free_matrix_double(double **matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

void free_matrix_int(int **matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}