from matrix import *
from test_time import *
from menu import *
import sys

def main():
    row = 3; column = 2
    matrix_a = Matrix(row, column)
    matrix_a.fill_matrix_random_values()
    matrix_a.output_matrix()

    matrix_b = Matrix(2, 3)
    matrix_b.fill_matrix_random_values()
    matrix_b.output_matrix()
    
    choice = -1
    while choice != 0:
        output_menu()
        choice = input_menu_choice()
        if choice != False - 1:
            if choice == 0:
                sys.exit()
            elif choice == 1:
                matrix_result = multiply_matrixes_ordinary(matrix_a, matrix_b)
                matrix_result.output_matrix()
            elif choice == 2:
                matrix_result = multiply_matrixes_vinograd(matrix_a, matrix_b)
                matrix_result.output_matrix()
            elif choice == 3:
                matrix_result = multiply_matrixes_vinograd_optimized(matrix_a, matrix_b)
                matrix_result.output_matrix()
            elif choice == 4:
                measure_time()

if __name__ == "__main__":
    main()