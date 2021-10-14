#include <thread>
#include <mutex>
#include "../includes/sort.hpp"

std::recursive_mutex rm;
int min_size_to_thread = 10000;
void merge(int *array, int size);

void merge_sort_consistently(int *array, int size)
{
  int middle = 0;
  if (size > 1)
  {
      middle = size / 2;
      merge_sort_consistently(array + 0, middle);
      merge_sort_consistently(array + middle, size - middle);
      merge(array, size);
  }
}

void merge_sort_parallel(int *array, int size)
{
  int middle = 0;
  if (size > 1)
  {
      middle = size / 2;
      if (size > min_size_to_thread)
      {
        std::thread t1(merge_sort_parallel, array, middle);
        std::thread t2(merge_sort_parallel, array + middle, size - middle);
        t1.join();
        t2.join();
      }
      merge(array, size);
  }
}

void merge(int *array, int size)
{
    int* sorted = new(std::nothrow)int[size];
    int middle = size / 2;

    int index_left = 0, index_right = middle;
    int index_sequence = 0;

    while (index_left < middle && index_right < size)
    {
        if (array[index_left] < array[index_right])
            sorted[index_sequence++] = array[index_left++];
        else
            sorted[index_sequence++] = array[index_right++];
    }

    while (index_left < middle)
        sorted[index_sequence++] = array[index_left++];

    while (index_right < size)
        sorted[index_sequence++] = array[index_right++];

    for (int i = 0; i < size; i++)
        array[i] = sorted[i];

    delete[] sorted;
};
