#ifndef _TIME_MEASURE_HPP_
#define _TIME_MEASURE_HPP_

#include "../includes/threads.hpp"
#include "../includes/constants.hpp"

double *measure_time_consistent(int *matrix_sizes, int size_matrix_sizes);
double **measure_time_parallel(int *matrix_sizes, int size_matrix_sizes);

void output_table_time(double *avg_time_consistent, double **avg_time_parallel, int *matrix_sizes,
                        int count_size_matrixes);

#endif