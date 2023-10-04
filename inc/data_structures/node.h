#ifndef node_h
#define node_h

typedef struct Node
{
    void *data;
    struct Node *next;
    struct Node *previous;
} Node;

Node node_constructor(void *data, unsigned long size);
void node_destructor(Node *node);

#endif