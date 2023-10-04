#include "../../inc/data_structures/queue.h"

void push(Queue *queue, void *data, unsigned long size);
void * peek(Queue *queue);
void pop (Queue *queue);

Queue queue_constructor()
{
    Queue queue;
    queue.list = linked_list_constructor();
    
    queue.push = push;
    queue.peek = peek;
    queue.pop = pop;
    
    return queue;
}

void queue_destructor(Queue *queue)
{
    linked_list_destructor(&queue->list);
}

void push(Queue *queue, void *data, unsigned long size)
{
    queue->list.insert(&queue->list, queue->list.length, data, size);
}

// Devuelve el valor del primer dato disponible
void * peek(Queue *queue)
{
    void *data = queue->list.retrieve(&queue->list, 0);
    return data;
}

void pop(Queue *queue)
{
    queue->list.remove(&queue->list, 0);
}