#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>

typedef struct matrix matrix_t;
struct matrix
{
    int **matrix;
    int size_row;
    int size_column;
};

int **create_matrix(int size_row, int size_column);
void output_matrix(int **matrix, int size_row, int size_column);

#endif