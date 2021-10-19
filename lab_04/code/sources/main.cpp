#include <iostream>
#include <chrono>
#include "../includes/time_measure.hpp"
#include "../includes/matrix.hpp"
#include "../includes/threads.hpp"

int main()
{
    int size_matrix_sizes = 7;
    int matrix_sizes[size_matrix_sizes] = {100, 250, 500, 1000, 2000, 3500, 5000};
    double *avg_time_consistent = nullptr, **avg_time_parallel = nullptr;

    avg_time_consistent = measure_time_consistent(matrix_sizes, size_matrix_sizes);
    avg_time_parallel = measure_time_parallel(matrix_sizes, size_matrix_sizes);

    output_table_time(avg_time_consistent, avg_time_parallel, matrix_sizes, size_matrix_sizes);

    free_arrays(avg_time_consistent, avg_time_parallel, size_matrix_sizes);

    return 0;
}