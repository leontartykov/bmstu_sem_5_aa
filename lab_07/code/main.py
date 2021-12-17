from dictionary import *
from menu import *
from word import *
from compare_measure import *

def main():
    dictionary = Dictionary()
    dictionary.parser("code/data/text.txt")
    dictionary.output()

    word = input("Введите ключ, по которому необходимо выполнить поиск в словаре: ")
    choice = -1; count_compares = 0
    while choice != 0:
        output_menu()
        choice = int(input("Выберите пункт меню: "))
        result = None
        if choice == 1:
            result, count_compares = dictionary.find_by_full_search(word)
        elif choice == 2:
            result, count_compares = dictionary.find_by_binary_search(word)
        elif choice == 3:
            result, count_compares = dictionary.find_by_segment_search(word)
        elif choice == 4:
            word = change_word()
        elif choice == 5:
            measure_compares(dictionary)
        elif choice != 0:
            output_menu_error()
        
        if result != None:
            output_result(word, result, count_compares)

if __name__ == "__main__":
    main()