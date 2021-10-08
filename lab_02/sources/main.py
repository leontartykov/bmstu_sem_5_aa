from matrix import *
from test_time import *
import sys

def main():
    row = 101; column = 101
    matrix_a = Matrix(row, column)
    matrix_a.fill_matrix_random_values()
    #matrix_a.output_matrix()

    matrix_b = Matrix(101, 101)
    matrix_b.fill_matrix_random_values()
    #matrix_b.output_matrix()
    
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
        elif choice == 3:
            matrix_result = multiply_matrixes_vinograd_optimized(matrix_a, matrix_b)
            matrix_result.output_matrix()
        elif choice == 4:
            print("Лучший случай:")
            best_ordinary, best_vinograd, best_optimized_vinograd = measure_process_time(100, 1001, 100)

            print("Лучший случай:")
            print(f"Обычный:", best_ordinary)
            print(f"Виноград:",best_vinograd)
            print(f"Оптимизированный:",best_optimized_vinograd)

            with open('file_1.txt', 'w') as filehandle:  
                for listitem in best_ordinary:
                    filehandle.write(str(listitem) + '\n')

            with open('file_2.txt', 'w') as filehandle:  
                for listitem in best_vinograd:
                    filehandle.write(str(listitem) + '\n')

            with open('file_3.txt', 'w') as filehandle:  
                for listitem in best_optimized_vinograd:
                    filehandle.write(str(listitem) + '\n')
            print("Худший случай:")
            worst_ordinary, worst_vinograd, worst_optimized_vinograd = measure_process_time(101, 1002, 100)
            

            print("Худший случай:")
            print(f"Обычный:", worst_ordinary)
            print(f"Виноград:", worst_vinograd)
            print(f"Оптимизированный:", worst_optimized_vinograd)

            

            with open('file_4.txt', 'w') as filehandle:  
                for listitem in worst_ordinary:
                    filehandle.write(str(listitem) + '\n')

            with open('file_5.txt', 'w') as filehandle:  
                for listitem in worst_vinograd:
                    filehandle.write(str(listitem) + '\n')

            with open('file_6.txt', 'w') as filehandle:  
                for listitem in worst_optimized_vinograd:
                    filehandle.write(str(listitem) + '\n')

if __name__ == "__main__":
    main()