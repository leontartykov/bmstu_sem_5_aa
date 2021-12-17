from os import write


def measure_compares(dictionary):   
    write_full_search_data("code/data/compare_full_search.txt", dictionary, 1)
    write_full_search_data("code/data/compare_full_search_back.txt", dictionary, -1)

    list_sorted = list()
    write_binary_data("code/data/compare_binary_0_450.txt", 0, 450, dictionary, list_sorted)
    write_binary_data("code/data/compare_binary_451_900.txt", 451, 900, dictionary, list_sorted)
    write_binary_data("code/data/compare_binary_901_1350.txt", 901, 1350, dictionary, list_sorted)
    write_binary_data("code/data/compare_binary_1351_1800.txt", 1351, 1800, dictionary, list_sorted)
    write_binary_data("code/data/compare_binary_1801_2241.txt", 1801, 2241, dictionary, list_sorted)
    
    list_sorted.sort(reverse=True)
    write_sorted_data("code/data/compare_binary_sorted_0_450.txt", 0, 450, list_sorted)
    write_sorted_data("code/data/compare_binary_sorted_451_900.txt", 451, 900, list_sorted) 
    write_sorted_data("code/data/compare_binary_sorted_901_1350.txt", 901, 1350, list_sorted) 
    write_sorted_data("code/data/compare_binary_sorted_1351_1800.txt", 1351, 1800, list_sorted) 
    write_sorted_data("code/data/compare_binary_sorted_1801_2241.txt", 1801, 2241, list_sorted) 

    list_sorted = list()
    write_segment_data("code/data/compare_segment_0_450.txt", 0, 450, dictionary, list_sorted)
    write_segment_data("code/data/compare_segment_451_900.txt", 451, 900, dictionary, list_sorted)
    write_segment_data("code/data/compare_segment_901_1350.txt", 901, 1350, dictionary, list_sorted)
    write_segment_data("code/data/compare_segment_1351_1800.txt", 1351, 1800, dictionary, list_sorted)
    write_segment_data("code/data/compare_segment_1801_2241.txt", 1801, 2241, dictionary, list_sorted)

    list_sorted.sort(reverse=True)
    print(len(list_sorted))
    write_sorted_data("code/data/compare_segment_sorted_0_450.txt", 0, 450, list_sorted)
    write_sorted_data("code/data/compare_segment_sorted_451_900.txt", 451, 900, list_sorted)
    write_sorted_data("code/data/compare_segment_sorted_901_1350.txt", 901, 1350, list_sorted)
    write_sorted_data("code/data/compare_segment_sorted_1351_1800.txt", 1351, 1800, list_sorted)
    write_sorted_data("code/data/compare_segment_sorted_1801_2241.txt", 1801, 2241, list_sorted)


def write_full_search_data(file_name, dictionary, direction):
    if direction == 1:
        start = 0; end = dictionary.len; step = 1
    else:
        start = dictionary.len; end = 0; step = -1
    with open(file_name, "w") as file:
        for i in range(start, end + step, step):
            string = str(i) + ' ' + str(i+1) + '\n'
            file.write(string)

def write_binary_data(file_name, left_board, right_board, dictionary, list_sorted):
    i = left_board
    with open(file_name, "w") as file:
        for key, value in dictionary.dictionary.items():
            if i == right_board:
                break
            elif i >= left_board and i < right_board:
                word = key
                result, count_compares = dictionary.find_by_binary_search(word) 
        
                string = str(i) + ' ' + str(count_compares) + '\n'
                list_sorted.append(count_compares)
                file.write(string)
                i += 1
    new = sorted(list_sorted, reverse=True)

def write_sorted_data(file_name, left_board, right_board, list_sorted):
    print(len(list_sorted))
    with open(file_name, "w") as file:
        for i in range(len(list_sorted)):
            if i >= left_board and i < right_board:
                count_compares = list_sorted[i] + 1
                string = str(i) + ' ' + str(count_compares) + '\n'
                file.write(string)
    

def write_segment_data(file_name, left_board, right_board, dictionary, list_sorted):
    i = left_board
    with open(file_name, "w") as file:
        for key, value in dictionary.dictionary.items():
            if i == right_board:
                break
            elif i >= left_board and i < right_board:
                word = key
                result, count_compares = dictionary.find_by_segment_search(word) 
        
                string = str(i) + ' ' + str(count_compares) + '\n'
                list_sorted.append(count_compares)
                file.write(string)
                i += 1