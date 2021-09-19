import sys
from menu import menu
from distance import *

def main():
    
    str_1 = input("Введите первую строку: ")
    str_2 = input("Введите вторую строку: ")
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
        recursive_levenstein_matrix()
    elif choice == 4:
        recursive_dameray_levenstein()


if __name__ == "__main__":
    main()