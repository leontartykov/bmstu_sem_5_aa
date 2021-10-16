#include <new>
#include "../includes/sort.hpp"
#include "../includes/threads.hpp"

void merge(int array[], int temp_array[], int from, int mid, int to, int size);
int min(int x, int y);

int min(int x, int y){
    return x < y ? x : y;
}

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
