from distance import *
import time

def time_test(str_1: str, str_2: str, count_operations: int,
              iterative_levenstein_list, recursive_levenstein_list,
              recursive_levenstein_matrix_list, recursive_dameray_levenstein_list):
    len_str = len(str_1)
    
    if iterative_levenstein_list != None:
        time_start = time.process_time()
        for i in range(count_operations):
            iterative_levenstein_two_rows(str_1, str_2)
        time_stop = time.process_time()
        average_time = (time_stop - time_start) / count_operations
        iterative_levenstein_list.append(average_time)
        print("Итеративного Левенштейна для {} = {:.15f}".format(len_str, average_time))
    
    print(recursive_levenstein_list)
    if recursive_levenstein_list != None:
        time_start = time.process_time()
        for i in range(count_operations):
            recursive_levenstein(str_1, str_2)
        time_stop = time.process_time()
        average_time = (time_stop - time_start) / count_operations
        recursive_levenstein_list.append(average_time)
        print("Рекурсивного Левенштейна для {} = {:.15f}".format(len_str, average_time))
    
    if recursive_levenstein_matrix_list != None:
        len_str_1 = len(str_1); len_str_2 = len(str_2)
        time_start = time.process_time()
        for i in range(count_operations):
            matrix = create_matrix(len_str_2 + 1, len_str_1 + 1)
        time_stop = time.process_time()
        average_matrix = (time_stop - time_start) / count_operations
        print("Создание матрицы {} = {:.15f}".format(len_str, average_matrix))
        
        time_start = time.process_time()
        for i in range(count_operations):
            matrix = create_matrix(len_str + 1, len_str + 1)
            recursive_levenstein_matrix(str_1, str_2, len_str, len_str, matrix)
        time_stop = time.process_time()
        average_time = (time_stop - time_start) / count_operations - average_matrix
        recursive_levenstein_matrix_list.append(average_time)
        print("Рекурсивного Левенштейна с матрицей для {} = {:.15f}".format(len_str, average_time))
    
    if recursive_dameray_levenstein_list != None:
        time_start = time.process_time()
        for i in range(count_operations):
            recursive_dameray_levenstein(str_1, str_2)
        time_stop = time.process_time()
        average_time = (time_stop - time_start) / count_operations
        recursive_dameray_levenstein_list.append(average_time)
        print("Рекурсивного Дамерау-Левенштейна для {} = {:.15f}".format(len_str, average_time))
    