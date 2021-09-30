from time import process_time
from numbers_array import *
from sorts import *

def timing_order_array(count_repeats: int, form_array):
    bubble_time = list()
    insert_time = list()
    shell_time = list()

    for size in range(100, 1001, 100):
        average_time_bubble = 0
        average_time_insert = 0
        average_time_shell = 0
        if size % 100 == 0:
            print(f"{size / 10} %")
        for j in range(count_repeats):
            order_array = form_array(size)
            time_start = process_time()
            bubble_sort(order_array, size)
            time_end = process_time()
            average_time_bubble += time_end - time_start

            order_array = form_array(size)
            time_start = process_time()
            insert_sort(order_array, size)
            time_end = process_time()
            average_time_insert += time_end - time_start

            order_array = form_array(size)
            time_start = process_time()
            shell_sort(order_array, size)
            time_end = process_time()
            average_time_shell += time_end - time_start
        average_time_bubble /= count_repeats
        average_time_insert /= count_repeats
        average_time_shell /= count_repeats
        bubble_time.append(average_time_bubble)
        insert_time.append(average_time_insert)
        shell_time.append(average_time_shell)

    return bubble_time, insert_time, shell_time