#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

int input_matrix_size();
int **form_random_matrix(int size_matrix);
void output_matrix(int **matrix, int size_matrix);

int find_matrix_min_value(int **matrix, int size_matrix);
void *find_matrix_min_value_parallel(void *args);

#endif