#include <iostream>
#include "matrix.h"

int **create_matrix(int size_row, int size_column)
{
    int **matrix = nullptr;
    matrix = new int *[size_row];

    for (int i = 0; i < size_row; ++i){
        matrix[i] = new int[size_column]{};
    }

    return matrix;
}

void output_matrix(int **matrix, int size_row, int size_column)
{
    for (int i = 0; i < size_row; ++i){
        std::cout << "(";
        for (int j = 0; j < size_column; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << ")," << std::endl;
    }
}