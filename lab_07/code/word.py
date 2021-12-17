def output_result(key, result, count_compares):
    print(f"Результат для ключа '{key}' равен {result}; количество сравнений {count_compares}")

def change_word():
    word = input("Введите ключ, по которому необходимо выполнить поиск в словаре: ")
    return word