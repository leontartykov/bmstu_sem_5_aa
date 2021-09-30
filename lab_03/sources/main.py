from constants import *
from numbers_array import *
from sorts import *
from test_time import *
from graph import *

def main():
    print('Лучший случай')
    #best_bubble_time, best_insert_time, best_shell_time = timing_order_array(COUNT_ITERATIONS, form_order_array)
    print('Обычный случай')
    usual_bubble_time, usual_insert_time, worst_shell_time = timing_order_array(COUNT_ITERATIONS, form_random_array)
    print('Худший случай')
    worst_bubble_time, worst_insert_time, usual_shell_time = timing_order_array(COUNT_ITERATIONS, form_reverse_order_array)

    #create_graph(best_bubble_time, best_insert_time, best_shell_time, 'Лучший случай')
    create_graph(usual_bubble_time, usual_insert_time, usual_shell_time, 'Обычный случай')
    create_graph(worst_bubble_time, worst_insert_time, worst_shell_time, 'Худший случай')
if __name__ == "__main__":
    main()