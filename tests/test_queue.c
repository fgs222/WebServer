#include <stdio.h>
#include <stdlib.h>
#include "../inc/data_structures/queue.h"

int main()
{
    Queue queue = queue_constructor();

    for (int i = 0; i < 10; i++)
    {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        queue.push(&queue, x, sizeof(x));
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", *(int *)queue.peek(&queue));
        queue.pop(&queue);
    }

    return 0;
}

// gcc -o test_queue -g tests/test_queue.c src/data_structures/queue.c src/data_structures/list.c src/data_structures/node.c