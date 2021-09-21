import matplotlib.pyplot as plt

def create_graph(iterative_levenstein_list, recursive_levenstein_list,
                recursive_levenstein_matrix_list, recursive_dameray_levenstein_list, len_str):
    fig, ax = plt.subplots()
    print(iterative_levenstein_list)
    print(recursive_levenstein_list)
    print(recursive_dameray_levenstein_list)

    #ax.plot(len_str, iterative_levenstein_list, label="Левенштейн (итеративный)", marker='o')
    ax.plot(len_str, recursive_levenstein_list, label="Левенштейн (рекурсивный)", marker='o')
    #ax.plot(len_str, recursive_levenstein_matrix_list, label="Левенштейн (рекурсивный с матрицей)", marker='o')
    ax.plot(len_str, recursive_dameray_levenstein_list, label="Дамерау-Левенштейн (рекурсивный)", marker='o')

    ax.legend()
    ax.grid()
    ax.set_xlabel('Длина строки')
    ax.set_ylabel('Время (с)')

    plt.show()