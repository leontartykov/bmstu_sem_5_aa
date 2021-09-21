from typing import Tuple
from copy import deepcopy
from memory_profiler import profile

@profile
def iterative_levenstein_two_rows(str_1: str, str_2: str) -> int:
    len_str_1 = len(str_1); len_str_2 = len(str_2)
    flag_first_row = 1; flag_second_row = 2

    row_1 = create_row(len_str_1 + 1, flag_first_row)
    row_2 = create_row(len_str_1 + 1, flag_second_row)

    for i in range(len_str_2):
        row_2[0] = i + 1
        for j in range(len_str_1):
            deletion_cost = row_1[j + 1] + 1
            insert_cost = row_2[j] + 1
            replace_cost = row_1[j] if str_1[j - 1] == str_2[i - 1] else row_1[j] + 1

            row_2[j + 1] = min(deletion_cost, insert_cost, replace_cost)
        row_1, row_2 = swap_rows(row_1, row_2)
    distance = row_1[-1]
    return distance

@profile
def recursive_levenstein(str_1: str, str_2: str) -> int:
    if str_1 == '' or str_2 == '':
        return abs(len(str_1) - len(str_2))
    match = 0 if str_1[-1] == str_2[-1] else 1
    distance = min(recursive_levenstein(str_1, str_2[:-1]) + 1,
                   recursive_levenstein(str_1[:-1], str_2) + 1,
                   recursive_levenstein(str_1[:-1], str_2[:-1]) + match)
    return distance

@profile
def recursive_levenstein_matrix(str_1: str, str_2: str, i: int, j: int, matrix: list[list[int]]) \
                                -> Tuple[int, list[list[int]]]:
    if i == 0:
        return j, matrix
    if j == 0:
        return i, matrix
    if matrix[i][j] != -1:
        return matrix[i][j], matrix
    match = 0 if str_1[-1] == str_2[-1] else 1

    insert, matrix = recursive_levenstein_matrix(str_1, str_2[:-1], i, j - 1, matrix)
    delete, matrix = recursive_levenstein_matrix(str_1[:-1], str_2, i - 1, j, matrix)
    replace, matrix = recursive_levenstein_matrix(str_1[:-1], str_2[:-1], i - 1, j - 1, matrix)
    insert += 1; delete += 1; replace += match

    distance = min(insert, delete, replace)
    matrix[i][j] = distance
    return distance, matrix

@profile
def recursive_dameray_levenstein(str_1: str, str_2: str) -> int:
    if str_1 == '' or str_2 == '':
        return abs(len(str_1) - len(str_2))
    match = 0 if str_1[-1] == str_2[-1] else 1
    insert = recursive_dameray_levenstein(str_1, str_2[:-1]) + 1
    delete = recursive_dameray_levenstein(str_1[:-1], str_2) + 1
    replace = recursive_dameray_levenstein(str_1[:-1], str_2[:-1]) + match

    if len(str_1) > 1 and len(str_2) > 1 and str_1[-1] == str_2[-2] and \
    str_2[-1] == str_1[-2]:
        distance = min(insert, delete, replace, recursive_dameray_levenstein(str_1[:-2], str_2[:-2]) + 1)
    else:
        distance = min(insert, delete, replace)
    return distance

def create_row(len_row: int, flag_row: int) -> list[int]:
    row = list()
    if flag_row == 1:
        for i in range(len_row):
            row.append(i)
    else:
        for i in range(len_row):
            row.append(0)
    return row

def swap_rows(row_1: list[int], row_2: list[int]) -> Tuple[list[int], list[int]]:
    temp_row = list()
    temp_row = deepcopy(row_1)
    row_1 = deepcopy(row_2)
    row_2 = deepcopy(temp_row)
    return row_1, row_2

def create_matrix(len_str_1: int, len_str_2: int) -> list[list]:
    matrix = list()
    for i in range(len_str_2):
        matrix.append([-1] * len_str_1)
    return matrix