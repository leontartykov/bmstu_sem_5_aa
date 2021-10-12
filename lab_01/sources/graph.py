import matplotlib.pyplot as plt
from generate_string import *
from test_time import *

def create_graph(graph_1, graph_2, graph_3, graph_4, len_str):
    fig, ax = plt.subplots()

    if graph_1 != None:
        ax.plot(len_str, graph_1, label="Левенштейн (итеративный)", marker='o')
    if graph_2 != None:
        ax.plot(len_str, graph_2, label="Левенштейн (рекурсивный)", marker='o')
    if graph_3 != None:
        ax.plot(len_str, graph_3, label="Левенштейн (рекурсивный с матрицей)", marker='o')
    if graph_4 != None:
        ax.plot(len_str, graph_4, label="Дамерау-Левенштейн (рекурсивный)", marker='o')

    ax.legend()
    ax.grid()
    ax.set_xlabel('Длина строки')
    ax.set_ylabel('Время (с)')

    plt.show()

def output_graph() -> None:
    '''iterative_levenstein_list = list(); recursive_levenstein_list = list()
    recursive_levenstein_matrix_list = list(); recursive_dameray_levenstein_list = list()
    len_str = list()
    for i in range(3, 9, 1):
        len_rand_str = i
        count_operations = 1000
        str_rand_1 = generate_random_string(N=len_rand_str)
        str_rand_2 = generate_random_string(N=len_rand_str)
        time_test(str_rand_1, str_rand_2, count_operations,
                    iterative_levenstein_list, recursive_levenstein_list,
                    recursive_levenstein_matrix_list, recursive_dameray_levenstein_list)
        len_str.append(i)

    write_to_file(3, 'iterative_lev.txt', iterative_levenstein_list)
    write_to_file(3, 'recursive_lev.txt', recursive_levenstein_list)
    write_to_file(3, 'recursive_lev_matrix.txt', recursive_levenstein_matrix_list)
    write_to_file(3, 'recursive_lev_damerau.txt', recursive_dameray_levenstein_list)
    create_graph(iterative_levenstein_list, recursive_levenstein_list,
                    recursive_levenstein_matrix_list, recursive_dameray_levenstein_list, len_str)'''

    iterative_levenstein_list = list(); recursive_levenstein_matrix_list = list()
    len_str = list()
    for i in range(25, 151, 25):
        len_rand_str = i
        count_operations = 1000
        str_rand_1 = generate_random_string(N=len_rand_str)
        str_rand_2 = generate_random_string(N=len_rand_str)
        time_test(str_rand_1, str_rand_2, count_operations,
                    iterative_levenstein_list, None,
                    recursive_levenstein_matrix_list, None)
        len_str.append(i)

    write_to_file(25, 'iterative_lev_comp.txt', iterative_levenstein_list)
    write_to_file(25, 'recursive_lev_matrix_comp.txt', recursive_levenstein_matrix_list)
    create_graph(iterative_levenstein_list, None,
                    recursive_levenstein_matrix_list, None, len_str)

def write_to_file(value_n, string, array):
    with open(string, 'w') as file:
        for i in range(len(array)):
            file.write(str(i + value_n) + ' ' + str(array[i]) + '\n')