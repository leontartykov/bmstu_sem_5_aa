from distance import *
import time

def time_test(str_1: str, str_2: str, count_operations: int):
    time_start = time.process_time()
    for i in range(count_operations):
        iterative_levenstein_two_rows(str_1, str_2)
    time_stop = time.process_time()
    average_time = (int(time_stop) - int(time_start)) / count_operations
    print(f"Замеры времени итеративного Левенштейна для {count_operations} = {average_time}")

    time_start = time.process_time()
    for i in range(count_operations):
        recursive_levenstein(str_1, str_2)
    time_stop = time.process_time()
    average_time = (time_stop - time_start) / count_operations
    print(f"Замеры времени рекурсивного Левенштейна для {count_operations} = {average_time}")

    time_start = time.process_time()
    for i in range(count_operations):
        recursive_levenstein_matrix(str_1, str_2)
    time_stop = time.process_time()
    average_time = (time_stop - time_start) / count_operations
    print(f"Замеры времени рекурсивного Левенштейна с матрицей для {count_operations} = {average_time}")

    time_start = time.process_time()
    for i in range(count_operations):
        recursive_dameray_levenstein(str_1, str_2)
    time_stop = time.process_time()
    average_time = (time_stop - time_start) / count_operations
    print(f"Замеры времени рекурсивного Дамерау-Левенштейна для {count_operations} = {average_time}")