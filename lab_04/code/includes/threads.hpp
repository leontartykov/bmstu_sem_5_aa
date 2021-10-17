#ifndef _THREADS_HPP_
#define _THREADS_HPP_

#include <pthread.h>

typedef struct use_mutex_tag {
    pthread_mutex_t mutex;
} use_mutex_t;

typedef struct args args_t;
struct args
{
    int **matrix;
    int size_row;
    int size_column;
};

typedef struct thread_data pthread_args_t;
struct thread_data
{
    int thread_id;
    int count_threads;
    int matrix_size;
    args_t *args;
    int local_min;
    use_mutex_t *mutex;
};

#endif