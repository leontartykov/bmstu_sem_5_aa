def bubble_sort(array: list[int], count: int) -> list[int]:
    for i in range(count):
        for j in range(count - i - 1):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]

def insert_sort(array: list[int], count: int) -> list[int]:
    for i in range(1, count):
        select_item = array[i]
        j = i - 1
        while j >= 0 and select_item < array[j]:
            array[j+1] = array[j]
            j -= 1
        array[j + 1] = select_item

def shell_sort(array: list[int], count:int) -> list[int]:
    distance = count // 2
    while distance > 0:
        for i in range(count - distance):
            j = i
            while j >= 0 and array[j] > array[j + distance]:
                array[j + distance], array[j] = array[j], array[j + distance]
                j -= 1
        distance //= 2