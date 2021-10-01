def bubble_sort(array: list[int], N: int) -> list[int]:
    for i in range(N):
        for j in range(N - i):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]

def insert_sort(array: list[int], N: int) -> list[int]:
    for i in range(1, N):
        select_item = array[i]
        j = i - 1
        while j >= 0 and select_item < array[j]:
            array[j+1] = array[j]
            j -= 1
        array[j + 1] = select_item

def shell_sort(array: list[int], N:int) -> list[int]:
    distance = N // 2
    while distance > 0:
        for i in range(N - distance):
            j = i
            while j >= 0 and array[j] > array[j + distance]:
                array[j + distance], array[j] = array[j], array[j + distance]
                j -= 1
        distance //= 2