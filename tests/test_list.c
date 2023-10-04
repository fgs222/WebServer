#include <stdio.h>
#include <stdlib.h>
#include "../inc/data_structures/list.h"

int main()
{
    LinkedList list = linked_list_constructor();

    for (int i = 0; i < 10; i++)
    {
        int *x = (int *)malloc(sizeof(int));
        *x = i;
        list.insert(&list, i, x, 10);
    }

    list.remove(&list, 2);
    list.remove(&list, 4);

    for (int i = 0; i < list.length; i++)
    {
        printf("%d\n", *(int *)list.retrieve(&list, i));
    }

    return 0;
}

// gcc -o test_list -g tests/test_list.c src/data_structures/list.c src/data_structures/node.c