#include "../inc/threadpool.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 10

typedef struct FUNC_ARGS
{
    int a;
    int b;
} FUNC_ARGS;

// Funciones a ejecutar por los threads
void sum(FUNC_ARGS *args) {
    usleep(50000);
    int sum = args->a + args->b;
    printf("Sum of %d and %d is %d\n", args->a, args->b, sum);
}

void product(FUNC_ARGS *args) {
    usleep(50000);
    int prod = args->a * args->b;
    printf("Product of %d and %d is %d\n", args->a, args->b, prod);
}

int main() {
    ThreadPool *thread_pool = thread_pool_constructor(NUM_THREADS);

    srand(time(NULL));
    // Crea y agrega tareas al thread pool
    for (int i = 0; i < NUM_THREADS; i++) {
        void * task_func = i % 2 == 0 ? &sum : &product;
        FUNC_ARGS *func_args = malloc(sizeof(FUNC_ARGS));
        func_args->a = rand() % 100;
        func_args->b = rand() % 100;

        ThreadTask thread_task = thread_task_constructor(task_func, func_args);
        thread_pool->add_work(thread_pool, thread_task);
    }

    thread_pool_destructor(thread_pool);

    return 0;
}

// gcc -o test_threadpool -Wall -g tests/test_threadpool.c src/data_structures/queue.c src/data_structures/list.c src/data_structures/node.c src/threadpool.c -lpthread
// gcc -o test_threadpool -g3 -fsanitize=thread,undefined src/data_structures/node.c src/data_structures/list.c src/data_structures/queue.c src/threadpool.c tests/test_threadpool.c