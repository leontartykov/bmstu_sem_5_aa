from test_time import time_test
import sys
from menu import menu
from distance import *
from generate_string import generate_random_string

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
            for i in range(3, 9):
                len_rand_str = i
                count_operations = 1000
                str_rand_1 = generate_random_string(N=len_rand_str)
                str_rand_2 = generate_random_string(N=len_rand_str)
                time_test(str_rand_1, str_rand_2, count_operations)



if __name__ == "__main__":
    main()