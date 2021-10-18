#include "../includes/threads.hpp"
#include "../includes/constants.hpp"

int input_count_threads()
{
    int count_threads = 0;
    int flag_correct = INCORRECT_COUNT_THREAD_INPUT;
    while(flag_correct == INCORRECT_COUNT_THREAD_INPUT)
    {
        std::cout << "Введите количество потоков: ";
        std::cin >> count_threads;
        if (std::cin.fail() || count_threads < 1)
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неверный ввод размера массива. Повторите еще раз.\n";
        }
        else
            flag_correct = CORRECT_COUNT_THREAD_INPUT;
    }
    
    return count_threads;
}