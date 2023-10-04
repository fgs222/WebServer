#ifndef threadpool_h
#define threadopool_h

#include <mqueue.h>
#include <pthread.h>

#include "data_structures/queue.h"

#define INACTIVE 0
#define ACTIVE   1

typedef struct ThreadTask
{
    void * (*task_func)(void *args);
    void *args;
} ThreadTask;

typedef struct ThreadPool
{
    int num_threads;
    int active;
    Queue work;
    pthread_t *pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;

    void (*add_work)(struct ThreadPool *thread_pool, ThreadTask thread_task);
} ThreadPool;

ThreadPool thread_pool_constructor(int num_threads, void * (thread_job_func));
ThreadTask thread_task_constructor(void * (*task_func)(void *args), void *args);

void thread_pool_destructor(struct ThreadPool *thread_pool);
void * thread_job_func(void *arg);

#endif