#ifndef _THREADS_HPP_
#define _THREADS_HPP_

#include <pthread.h>

typedef struct args args_t;
struct args
{
    int *array;
    int *temp_array;
    int low;
    int high;
};

typedef struct thread_data pthread_args_t;
struct thread_data
{
    int thread_id;
    int count_threads;
    int array_size;
    args_t *sort_args;
};

#endif