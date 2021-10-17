#include <iostream>
#include <new>
#include "../includes/sort.hpp"
#include "../includes/threads.hpp"

void merge(int array[], int temp_array[], int from, int mid, int to, int size);
int min(int x, int y);

int min(int x, int y){
    return x < y ? x : y;
}
/*
void merge_sort_consistently(int *array, int *temp_array, int low, int high)
{
    int size = high - low;
    int from = 0, middle = 0, to = 0;
    for (int m = 1; m <= size; m *= 2)
        for (int i = low; i < high; i += 2*m)
        {
            from = i;
            middle = i + m - 1;
            to = min(i + 2*m - 1, high);
            merge(array, temp_array, from, middle, to, size + 1);
        }
}

void merge(int array[], int temp_array[], int from, int mid, int to, int size)
{
    int index_sequence = from, index_left = from, index_right = mid + 1;
 
    while (index_left <= mid && index_right <= to)
    {
        if (array[index_left] < array[index_right]) {
            temp_array[index_sequence++] = array[index_left++];
        }
        else {
            temp_array[index_sequence++] = array[index_right++];
        }
    }
 
    while (index_left < size && index_left <= mid) {
        temp_array[index_sequence++] = array[index_left++];
    }

    for (int i = from; i <= to; i++) {
        array[i] = temp_array[i];
    }
}

/*void *merge_sort_parallelly(void *args)
{
    pthread_args_t *args_in = (pthread_args_t *)args;
    //pthread_mutex_lock(&(args_in->mutex));
    std::cout << "Номер потока " << args_in->thread_id << std::endl;
    int part = args_in->array_size / args_in->count_threads;
    int low = args_in->thread_id * part; 
    int high = (args_in->thread_id + 1) * part - 1;
    std::cout << "low: " << low << std::endl;
    std::cout << "array[low] = " << args_in->sort_args->array[low] << std::endl;
    std::cout << "high: " << high << std::endl;

    int size = high - low;
    std::cout << "Адрес size = " << &size << std::endl;
    int from = 0, middle = 0, to = 0;
    for (int m = 1; m <= size; m *= 2)
        for (int i = low; i < high; i += 2*m)
        {
            from = i;
            middle = i + m - 1;
            std::cout << "middle = " << middle << std::endl;
            to = min(i + 2*m - 1, high);
            std::cout << "to = " << to << std::endl;
            merge(args_in->sort_args->array, args_in->sort_args->temp_array, from, middle, to, size + 1);
        }
    std::cout << std::endl;
    //pthread_mutex_unlock(&(args_in->mutex));
    return NULL;
}

void *double_value(void *args)
{
    pthread_args_t *args_in = (pthread_args_t *)args;
    int part = args_in->array_size / args_in->count_threads;
    int low = args_in->thread_id * part; 
    int high = (args_in->thread_id + 1) * part - 1;

    for (int i = low; i < high; i++){
        args_in->sort_args->array[i] *= 2 - 50;
    }

    return NULL;
}
*/