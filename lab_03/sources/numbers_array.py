from random import randint
from constants import *

def form_order_array(count: int) -> list[int]:
    array = list()
    for i in range(count):
        array.append(i)
    
    return array

def form_reverse_order_array(count: int) -> list[int]:
    array = list()
    for i in range(count):
        array.append(count - i - 1)
    
    return array

def form_random_array(count: int) -> list[int]:
    array = list()
    for i in range(count):
        array.append(randint(MIN_NUMBER, MAX_NUMBER))

    return array

def output_array(array: list[int], count: int) -> None:
    for i in range(count):
        if i != count - 1:
            print(array[i], end = ',')
        else:
            print(array[i])
    print()