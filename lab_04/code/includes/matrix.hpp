#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

int input_matrix_size();
int **form_matrix_int(int size_matrix);
double **form_matrix_double(int size_matrix);

void free_matrix_int(int **matrix, int size_matrix);
void free_matrix_double(double **matrix, int size_matrix);
void free_arrays(double *avg_time_consistent, double **avg_time_parallel, int size_matrix);

void form_random_values(int ***matrix, int size_matrix);
void output_matrix(int **matrix, int size_matrix);

int find_matrix_min_value(int **matrix, int size_matrix);
void *find_matrix_min_value_parallel(void *args);

#endif