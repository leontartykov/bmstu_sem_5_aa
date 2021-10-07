from random import randint
from constants import *

class Matrix():
    def __init__(self, n, m):
        self.__n, self.__m = n, m
        self.create_matrix()

    def create_matrix(self):
        self.matrix = [[0] * self.__m for i in range(self.__n)]

    def output_matrix(self):
        for i in range(self.__n):
            for j in range(self.__m):
                print(self.matrix[i][j], end=' ')
            print()

    def __getitem__(self, index):
        return self.matrix[index]

    def __setitem__(self, key, value):
        self.matrix[key] = value

    def get_size(self):
        return self.__n, self.__m

    def fill_matrix_random_values(self):
        for i in range(self.__n):
            for j in range(self.__m):
                self.matrix[i][j] = randint(MIN_RAND, MAX_RAND)

def multiply_matrixes_ordinary(matrix_a, matrix_b) -> list[list[int]]:
    n, m = matrix_a.get_size()
    q, p = matrix_b.get_size()
    if m != q:
        print('Несовпадение размеров матриц')
        return
    else:
        matrix_result = Matrix(n, p)
        for i in range(n):
            for j in range(p):
                for k in range(m):
                    matrix_result[i][j] += matrix_a[i][k] * matrix_b[k][j]
        return matrix_result

def multiply_matrixes_vinograd(matrix_a, matrix_b) -> list[list[int]]:
    n, m = matrix_a.get_size()
    q, p = matrix_b.get_size()
    if m != q:
        print('Несовпадение размеров матриц')
        return
    else:
        matrix_result = Matrix(n, p)
        mul_u = [0] * n
        for i in range(n):
            for j in range(int(m / 2)):
                mul_u[i] = mul_u[i] + matrix_a[i][2*j] * matrix_a[i][2*j + 1]

        mul_w = [0] * p
        for i in range(p):
            for j in range(int(m / 2)):
                mul_w[i] = mul_w[i] + matrix_b[2*j][i] * matrix_b[2*j + 1][i]

        for i in range(n):
            for j in range(p):
                matrix_result[i][j] = -mul_u[i] - mul_w[j]
                for k in range(int(m / 2)):
                    matrix_result[i][j] = matrix_result[i][j] + (matrix_a[i][2*k] + matrix_b[2*k+1][j]) * \
                                                                (matrix_a[i][2*k+1] + matrix_b[2*k][j])
                                                    
        if m % 2 == 1:
            for i in range(n):
                for j in range(p):
                    matrix_result[i][j] = matrix_result[i][j] + matrix_a[i][m-1] * matrix_b[m-1][j]

        return matrix_result