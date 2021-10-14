#include "../includes/sort.hpp"

void merge(int *array, int first, int last);

//рекурсивная процедура сортировки
void merge_sort_consistently(int *array, int first, int last)
{
  int middle = 0;
  if (first < last)
  {
      middle = (first + last) / 2;
      merge_sort_consistently(array, first, middle);
      merge_sort_consistently(array, middle + 1, last);
      merge(array, first, last);
  }
}

void merge(int *array, int first, int last)
{
    int middle, start, final, j;
    int *mas = new int[first + last];
    middle = (first + last) / 2;  //вычисление среднего элемента
    start = first;                //начало левой части
    final = middle + 1;           //начало правой части
    for (j = first; j <= last; j++)  //выполнять от начала до конца
    {
        if ((start <= middle) && ((final > last) || (array[start] < array[final])))
        {
          mas[j] = array[start];
          start++;
        }
        else
        {
          mas[j] = array[final];
          final++;
        }
    }
    //возвращение результата в список
    for (j = first; j <= last; j++)
      array[j] = mas[j];
    delete[] mas;
};
