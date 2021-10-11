import matplotlib.pyplot as plt
from test_time import *

def output_graph() -> None:
    print('Лучший случай')
    best_bubble_time, best_insert_time, best_shell_time = timing_order_array(COUNT_ITERATIONS, form_order_array)
    print('Обычный случай')
    usual_bubble_time, usual_insert_time, usual_shell_time = timing_order_array(COUNT_ITERATIONS, form_random_array)
    print('Худший случай')
    worst_bubble_time, worst_insert_time, worst_shell_time = timing_order_array(COUNT_ITERATIONS, form_reverse_order_array)

    write_to_file('best_bubble_time.txt', best_bubble_time)
    write_to_file('best_insert_time.txt', best_insert_time)
    write_to_file('best_shell_time.txt', best_shell_time)
    write_to_file('usual_bubble_time.txt', usual_bubble_time)
    write_to_file('usual_insert_time.txt', usual_insert_time)
    write_to_file('usual_shell_time.txt', usual_shell_time)
    write_to_file('worst_bubble_time.txt', worst_bubble_time)
    write_to_file('worst_insert_time.txt', worst_insert_time)
    write_to_file('worst_shell_time.txt', worst_shell_time)

    create_graph(best_bubble_time, best_insert_time, best_shell_time, 'Лучший случай')
    create_graph(usual_bubble_time, usual_insert_time, worst_shell_time, 'Обычный случай')
    create_graph(worst_bubble_time, worst_insert_time, usual_shell_time, 'Худший случай')

def write_to_file(string, array):
    with open(string, 'w') as file:
        for i in range(len(array)):
            file.write(str((i+1) * 100) + ' ' + str(array[i]) + '\n')


def create_graph(bubble_time:list[int], insert_time:list[int],
                shell_time:list[int], title:str):
    ax = plt.subplot(121)
    len_array = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]

    plt.title(title)
    ax.plot(len_array, bubble_time, label="Пузырек", marker='o')
    ax.plot(len_array, insert_time, label="Простые вставки", marker='o')
    ax.plot(len_array, shell_time, label="Шелл", marker='o')

    plt.legend(loc=2, bbox_to_anchor=(1, 0.5))
    ax.grid()
    ax.set_xlabel('Число элементов')
    ax.set_ylabel('Время (с)')
    ax.set_xlim([0, 1050])

    plt.show()