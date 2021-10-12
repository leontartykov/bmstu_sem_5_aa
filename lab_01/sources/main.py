from test_time import time_test
import sys
from menu import menu
from distance import *
from generate_string import generate_random_string
from graph import *
import cProfile, pstats

def main():
    str_1 = input("Введите первую строку: ")
    str_2 = input("Введите вторую строку: ")
    
    choice = -1
    while choice != 0:
        menu()
        choice = int(input("Выберите пункт меню: "))
        if choice == 0:
            sys.exit()
        elif choice == 1:
            distance = iterative_levenstein_two_rows(str_1, str_2)
            print(f"distance = {distance}")
        elif choice == 2:
            distance = recursive_levenstein(str_1, str_2)
            print(f"distance = {distance}")
        elif choice == 3:
            len_str_1 = len(str_1); len_str_2 = len(str_2)
            matrix = create_matrix(len_str_2 + 1, len_str_1 + 1)
            distance, matrix = recursive_levenstein_matrix(str_1, str_2, len_str_1, len_str_2, matrix)
            print(f"distance = {distance}")
        elif choice == 4:
            distance = recursive_dameray_levenstein(str_1, str_2)
            print(f"distance = {distance}")
        elif choice == 5:
            output_graph()
        elif choice == 6:
            str_1 = 'zxc'
            str_2 = 'vbn'
            
            cProfile.run("iterative_levenstein_two_rows('zxc', 'vbn')", "output.dat")
            with open ("output_time_1.txt", "w") as file:
                p = pstats.Stats("output.dat", stream=file)
                p.sort_stats("calls").print_stats()
            print(f"size_1 = {sys.getsizeof(iterative_levenstein_two_rows)}")
            
            cProfile.run("recursive_levenstein('zxc', 'vbn')", "output.dat")
            with open ("output_time_2.txt", "w") as file:
                p = pstats.Stats("output.dat", stream=file)
                p.sort_stats("calls").print_stats()

            cProfile.run("recursive_levenstein_matrix_input('zxc', 'vbn')", "output.dat")
            with open ("output_time_3.txt", "w") as file:
                p = pstats.Stats("output.dat", stream=file)
                p.sort_stats("calls").print_stats()

            cProfile.run("recursive_dameray_levenstein('zxc', 'vbn')", "output.dat")
            with open ("output_time_4.txt", "w") as file:
                p = pstats.Stats("output.dat", stream=file)
                p.sort_stats("calls").print_stats()
            


def recursive_levenstein_matrix_input(str_1, str_2):
    len_str_1 = len(str_1); len_str_2 = len(str_2)
    matrix = create_matrix(len_str_2 + 1, len_str_1 + 1)
    recursive_levenstein_matrix(str_1, str_2, len_str_1, len_str_2, matrix)



if __name__ == "__main__":
    main()