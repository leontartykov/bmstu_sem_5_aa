def output_menu():
    print("Выберите алгоритм умножения матриц:\n" +
            "1.Стандартный способ.\n" +
            "2.Алгоритм Винограда.\n" +
            "3.Оптимизированный алгоритм Винограда.\n" +
            "4.Выполнить замеры времени.\n" +
            "0.Выход\n")

def input_menu_choice():
    choice = input("Введите пункт меню: ")
    if not choice.isdigit():
        print('Неверный пункт меню.\n')
        choice = False - 1
    else:
        choice = int(choice)
        if not (choice >= 0 and choice <= 4):
            print('Неверный пункт меню.\n')
            choice = False - 1
    return choice