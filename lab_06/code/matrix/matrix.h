#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>

typedef struct matrix_int matrix_int_t;
struct matrix_int
{
    int **matrix;
    int size_row;
    int size_column;
};

typedef struct matrix_double matrix_double_t;
struct matrix_double
{
    double **matrix;
    int size_row;
    int size_column;
};

int **create_int_matrix(int size_row, int size_column);
double **create_double_matrix(int size_row, int size_column);

void output_matrix(int **matrix, int size_row, int size_column);
void output_matrix_double(double **matrix, int size_row, int size_column);

#endif