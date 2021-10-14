#include <iostream>
#include <new>
#include <cstdlib> // для функций rand() и srand()
#include <ctime>
#include "../includes/array.hpp"
#include "../includes/constants.hpp"

int input_array_size()
{
    int size_array = 0;
    int flag_correct = INCORRECT_INPUT;
    while(flag_correct == INCORRECT_INPUT)
    {
        std::cout << "Введите размер массива: ";
        std::cin >> size_array;
        if (std::cin.fail() || size_array < 1)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неверный ввод размера массива. Повторите еще раз.\n";
        }
        else
            flag_correct = CORRECT_INPUT;
    }
    
    return size_array;
}

int* form_random_array(int size_array)
{
    std::srand(std::time(NULL));
    int *array = nullptr;
    array = new(std::nothrow)int[size_array]();
    
    for (int i = 0; i < size_array; i++)
        array[i] = MIN_RAND_VALUE + rand() % MAX_RAND_VALUE;

    return array;
}

void output_array(int* array, int size_array)
{
    for (int i = 0; i < size_array; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}