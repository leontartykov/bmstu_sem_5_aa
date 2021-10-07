from constants import *
from numbers_array import *
from sorts import *
from test_time import *
from graph import *
from menu import *
import sys

def main():
    choice = -1
    while choice != 0:
        menu()
        choice = int(input("Выберите пункт меню: "))
        if choice == 0:
            sys.exit()
        elif choice == 1:
            print('Исходный массив')
            array = form_random_array(MAX_SIZE_ARRAY)
            output_array(array, len(array))
            bubble_sort(array, len(array))
            print('Отсортированный массив')
            output_array(array, len(array))
        elif choice == 2:
            print('Исходный массив')
            array = form_random_array(MAX_SIZE_ARRAY)
            output_array(array, len(array))
            bubble_sort(array, len(array))
            print('Отсортированный массив')
            output_array(array, len(array))
        elif choice == 3:
            print('Исходный массив')
            array = form_random_array(MAX_SIZE_ARRAY)
            output_array(array, len(array))
            bubble_sort(array, len(array))
            print('Отсортированный массив')
            output_array(array, len(array))
        elif choice == 4:
            output_graph()
if __name__ == "__main__":
    main()