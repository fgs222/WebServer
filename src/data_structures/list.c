#include "../../inc/data_structures/list.h"

#include <stdlib.h>
#include <stdio.h>

Node *create_node_ll(void *data, unsigned long size);
void destroy_node_ll(Node *node_to_destroy);

Node * iterate_ll(LinkedList *linked_list, int index);
void insert_ll(LinkedList *linked_list, int index, void *data, unsigned long size);
void remove_node_ll(LinkedList *linked_list, int index);
void * retrieve_ll(LinkedList *linked_list, int index);
void bubble_sort_ll(LinkedList *linked_list, int (*compare)(void *a, void *b));
short binary_search_ll(LinkedList *linked_list, void *query, int (*compare)(void *a, void *b));

LinkedList linked_list_constructor()
{
    LinkedList new_list;
    new_list.head = NULL;
    new_list.length = 0;

    new_list.insert = insert_ll;
    new_list.remove = remove_node_ll;
    new_list.retrieve = retrieve_ll;
    new_list.sort = bubble_sort_ll;
    new_list.search = binary_search_ll;
    
    return new_list;
}

void linked_list_destructor(LinkedList *linked_list)
{
    for (int i = 0; i < linked_list->length; i++)
    {
        linked_list->remove(linked_list, 0);
    }
}

Node * create_node_ll(void *data, unsigned long size)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    *new_node = node_constructor(data, size);
    
    return new_node;
}

void destroy_node_ll(Node *node_to_destroy)
{
    node_destructor(node_to_destroy);
}

Node * iterate_ll(LinkedList *linked_list, int index)
{
    // Confirma que el usuario especifico un indice valido
    if (index < 0 || index >= linked_list->length)
    {
        return NULL;
    }
    // Crea un nodo cursor para la iteracion
    Node *cursor = linked_list->head;
    // Itero la lista hasta llegar al nodo deseado
    for (int i = 0; i < index; i++)
    {
        cursor = cursor->next;
    }
    return cursor;
}

void insert_ll(LinkedList *linked_list, int index, void *data, unsigned long size)
{
    Node *node_to_insert = create_node_ll(data, size);
    // Verifico si el nodo se colocara el inicio de la lista
    if (index == 0)
    {
        // Si ya existen nodos en la lista
        if (linked_list->head != NULL) {
            node_to_insert->next = linked_list->head;
            node_to_insert->previous = NULL;
            linked_list->head->previous = node_to_insert;
        }
        linked_list->head = node_to_insert;
    }
    else
    {
        // Encuentro el nodo anterior al nodo a colocar
        Node *cursor = iterate_ll(linked_list, index - 1);
        node_to_insert->next = cursor->next;
        node_to_insert->previous = cursor;
        cursor->next = node_to_insert;
    }
    linked_list->length += 1;
}

void remove_node_ll(LinkedList *linked_list, int index)
{
    // Verifico si el nodo a remover esta en el inicio de la lista
    if (index == 0)
    {
        Node *node_to_remove = linked_list->head;
        // Defino el nodo de inicio de la lista
        if (node_to_remove && node_to_remove->next)
        {
            linked_list->head = node_to_remove->next;
            node_to_remove->next->previous = NULL;
            destroy_node_ll(node_to_remove);
        }
        else
        {
            linked_list->head = NULL;
            destroy_node_ll(node_to_remove);
        }
    }
    else
    {
        // Encuentro el nodo anterior al nodo a colocar
        Node *cursor = iterate_ll(linked_list, index - 1);
        Node *node_to_remove = cursor->next;
        cursor->next = node_to_remove->next;
        cursor->previous = node_to_remove->previous;
        destroy_node_ll(node_to_remove);
    }
    linked_list->length -= 1;
}

void * retrieve_ll(LinkedList *linked_list, int index)
{
    // Encuentro el nodo deseado y devuelvo su informacion
    Node *cursor = iterate_ll(linked_list, index);
    if (cursor)
    {
        return cursor->data;
    }
    else
    {
        return NULL;
    }
}

void bubble_sort_ll(LinkedList *linked_list, int (*compare)(void *a, void *b))
{
    for (Node *i = linked_list->retrieve(linked_list, 0); i; i = i->next)
    {
        for (Node *n = i->next; n; n = n->next)
        {
            if (compare(i->data, n->data) > 0)
            {
               // Swapeo
                void *temporary = n->data;
                n->data = i->data;
                i->data = temporary;
            }
        }
    }
}

short binary_search_ll(LinkedList *linked_list, void *query, int (*compare)(void *a, void *b))
{
    int position = linked_list->length / 2;
    int min_checked = 0;
    int max_checked = linked_list->length;

    while (max_checked > min_checked)
    {
        void *data = linked_list->retrieve(linked_list, position);
        if (compare(data, query) == 1)
        {
            max_checked = position;
            if (position != (min_checked + position) / 2)
            {
                position = (min_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else if (compare(data, query) == -1)
        {
            min_checked = position;
            if (position != (max_checked + position) / 2)
            {
                position = (max_checked + position) / 2;
            }
            else
            {
                break;
            }
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
