from matrix import *
import sys

def main():
    row = 3; column = 4
    matrix_a = Matrix(row, column)
    matrix_a.fill_matrix_random_values()
    matrix_a.output_matrix()

    matrix_b = Matrix(4, 2)
    matrix_b.fill_matrix_random_values()
    matrix_b.output_matrix()
    
    choice = -1
    while choice != 0:
        choice = int(input("Введите пункт меню: "))
        if choice == 0:
            sys.exit()
        elif choice == 1:
            matrix_result = multiply_matrixes_ordinary(matrix_a, matrix_b)
            matrix_result.output_matrix()
        elif choice == 2:
            matrix_result = multiply_matrixes_vinograd(matrix_a, matrix_b)
            matrix_result.output_matrix()

if __name__ == "__main__":
    main()