#ifndef list_h
#define list_h

#include "node.h"

typedef struct LinkedList
{
    Node *head;
    int length;

    void (*insert)(struct LinkedList *linked_list, int index, void *data, unsigned long size);
    void (*remove)(struct LinkedList *linked_list, int index);
    void * (*retrieve)(struct LinkedList *linked_list, int index);
    void (*sort)(struct LinkedList *linked_list, int (*compare)(void *a, void *b));
    short (*search)(struct LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));
} LinkedList;

LinkedList linked_list_constructor(void);
void linked_list_destructor(LinkedList *linked_list);

#endif