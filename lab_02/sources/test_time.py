from time import process_time
from matrix import *

def measure_process_time(start, end, step):
    ordinary= []; vinograd = []; optimized_vinograd = []
    
    for i in range(start, end, step):
        matrix_a = Matrix(i, i)
        matrix_b = Matrix(i, i)
        avg_time_ordinary = 0
        avg_time_vinograd = 0
        avg_time_optimized_vinograd = 0
        for count in range(1,2):
            time_start = process_time()
            multiply_matrixes_ordinary(matrix_a, matrix_b)
            time_end = process_time()
            avg_time_ordinary += time_end - time_start
            '''
            time_start = process_time()
            multiply_matrixes_vinograd(matrix_a, matrix_b)
            time_end = process_time()
            avg_time_vinograd += time_end - time_start

            time_start = process_time()
            multiply_matrixes_vinograd_optimized(matrix_a, matrix_b)
            time_end = process_time()
            avg_time_optimized_vinograd += time_end - time_start
            '''
        ordinary.append(avg_time_ordinary/count)
        #vinograd.append(avg_time_vinograd/count)
        #optimized_vinograd.append(avg_time_optimized_vinograd/count)
        if start == 101 and (i - 1) % 100 == 0:
            print(f"{i / 10} %")
        elif start == 100 and i % 100 == 0:
            print(f"{i / 10} %") 
    return ordinary, vinograd, optimized_vinograd