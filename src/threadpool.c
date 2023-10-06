#include "../inc/threadpool.h"

#include <stdio.h>
#include <stdlib.h>

void * thread_job_func(void *arg);
void add_work(ThreadPool *thread_pool, ThreadTask thread_task);

ThreadPool *thread_pool_constructor(int num_threads)
{
    ThreadPool *thread_pool = malloc(sizeof(ThreadPool));
    thread_pool->num_threads = num_threads;
    thread_pool->active = ACTIVE;
    thread_pool->work = queue_constructor();

    pthread_mutex_init(&thread_pool->lock, NULL);
    pthread_cond_init(&thread_pool->signal, NULL);

    // pthread_mutex_lock(&thread_pool->lock);
    thread_pool->pool = malloc(sizeof(pthread_t[num_threads]));

    // Creo los threads
    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_create(&(thread_pool->pool[i]), NULL, thread_job_func, thread_pool) != 0) {
            perror("Failed to create the thread");
            exit(1);
        }
    }

    // pthread_mutex_unlock(&thread_pool->lock);
    thread_pool->add_work = add_work;

    return thread_pool;
}

ThreadTask thread_task_constructor(void * (*task_func)(void *args), void *args)
{
    ThreadTask thread_task;
    thread_task.task_func = task_func;
    thread_task.args = args;

    return thread_task;
}

void thread_pool_destructor(ThreadPool *thread_pool)
{
    thread_pool->active = INACTIVE;
    for (int i = 0; i < thread_pool->num_threads; i++)
    {
        pthread_cond_signal(&thread_pool->signal);
    }

    // Debe ejecutarse en otro for para asegurarse que el thread que termine de ejecutar sea el esperado
    for (int i = 0; i < thread_pool->num_threads; i++)
    {
        pthread_join(thread_pool->pool[i], NULL);
    }

    free(thread_pool->pool);

    pthread_mutex_destroy(&thread_pool->lock);
    pthread_cond_destroy(&thread_pool->signal);

    queue_destructor(&thread_pool->work);
}

void * thread_job_func(void *arg)
{
    ThreadPool *thread_pool = (ThreadPool *)arg;

    while(thread_pool->active == ACTIVE)
    {   
        ThreadTask thread_task;

        // Lockeo el ThreadPool
        pthread_mutex_lock(&thread_pool->lock);

        // Espera hasta que se agregue una nueva tarea a la Queue
        while (thread_pool->work.list.length == 0) {
            pthread_cond_wait(&thread_pool->signal, &thread_pool->lock);
        }
        
        // Verifico si hay alguna tarea para ejecutar
        thread_task = *(ThreadTask *)thread_pool->work.peek(&thread_pool->work);
        thread_pool->work.pop(&thread_pool->work);
        
        // Desbloqueo el ThreadPool
        pthread_mutex_unlock(&thread_pool->lock);

        if(thread_task.task_func)
        {
            // Ejecuta la funcion que se le asigno a job
            thread_task.task_func(thread_task.args);
        }
    }
    return NULL;
}

void add_work(ThreadPool *thread_pool, ThreadTask thread_task)
{
    pthread_mutex_lock(&thread_pool->lock);
    
    thread_pool->work.push(&thread_pool->work, &thread_task, sizeof(thread_task));

    pthread_mutex_unlock(&thread_pool->lock);
    pthread_cond_signal(&thread_pool->signal);
}