#ifndef queue_h
#define queue_h

#include "list.h"

typedef struct Queue
{
    LinkedList list;
    
    void (*push)(struct Queue *queue, void *data, unsigned long size);
    void * (*peek)(struct Queue *queue);
    void (*pop)(struct Queue *queue);
} Queue;

Queue queue_constructor(void);
void queue_destructor(Queue *queue);

#endif