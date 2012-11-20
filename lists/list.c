#include <stdlib.h>
#include "list.h"

node_t *
node_t_new(void *element)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if(NULL != node) {
        node->next = NULL;
        node->element = element;
    }
    return node;
}

void
node_t_delete(node_t *node)
{
    if(NULL != node)
        free(node);
}

list_t *
list_t_new(void)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    if(NULL != list) {
        list->first = NULL;
        list->length = 0;
    }
    return list;
}

void
list_t_delete(list_t *list)
{
    if(NULL != list) {
        list_t_clear(list);
        free(list);
    }
}

void
list_t_add_at(list_t *list, size_t index, void *element)
{
    node_t *node = node_t_new(element);
    if(NULL == list->first) {
        node->next = node;
        list->first = node;
    } else {
        node_t *tmp = list->first;
        while(list->first != tmp->next && --index)
            tmp = tmp->next;
        if(list->first == tmp->next) {
            node->next = list->first;
        } else {
            node->next = tmp->next;
        }
        tmp->next = node;
    }
    list->length++;
}

void
list_t_add(list_t *list, void *element)
{
    list_t_add_at(list, -1, element);
}

void
list_t_add_first(list_t *list, void *element)
{
    list_t_add_at(list, 0, element);
}

void
list_t_add_last(list_t *list, void *element)
{
    list_t_add(list, element);
}

void
list_t_clear(list_t *list)
{
    void *element;
    while(NULL != (element = list_t_remove_first(list)));
}

list_t *
list_t_clone(list_t *list)
{
    list_t *clone = list_t_new();
    node_t *tmp = list->first;
    if(NULL != tmp)
        do {
            list_t_add(clone, tmp->element);
            tmp = tmp->next;
        } while(list->first != tmp);
    return clone;
}

int
list_t_contains(list_t *list, void *element)
{
    int contains = 0;
    node_t *tmp = list->first;
    if(NULL != tmp)
        do {
            if(tmp->element == element) {
                contains = 1;
                break;
            }
            tmp = tmp->next;
        } while(list->first != tmp);
    return contains;
}

void *
list_t_get_at(list_t *list, size_t index)
{
    node_t *node = NULL;
    if(0 == index)
        return (NULL == list->first) ? list->first: list->first->element;
    node_t *tmp = list->first;
    if(NULL != tmp) {
        do {
            tmp = tmp->next;
        } while(list->first != tmp && --index);
        node = tmp;
    }
    return (NULL == node) ? node : node->element;
}

void *
list_t_get_first(list_t *list)
{
    return list_t_get_at(list, 0);
}

void *
list_t_get_last(list_t *list)
{
    return list_t_get_at(list, -1);
}

size_t
list_t_index_of(list_t *list, void *element, int (*compare)(void *, void *))
{
    size_t index = -1, i = 0;
    node_t *tmp = list->first;
    if(NULL != tmp)
        do {
            if(compare(tmp->element, element)) {
                index = i;
                break;
            }
            tmp = tmp->next;
            i++;
        } while(list->first != tmp);
    return index;
}

size_t
list_t_last_index_of(list_t *list, void *element, int (*compare)(void *, void *))
{
    size_t index = -1, i = 0;
    node_t *tmp = list->first;
    if(NULL != tmp)
        do {
            if(compare(tmp->element, element)) {
                index = i;
            }
            tmp = tmp->next;
            i++;
        } while(list->first != tmp);
    return index;
}

void *
list_t_remove_at(list_t *list, size_t index)
{
    void *element = NULL;
    node_t *node;
    node_t *tmp = list->first;
    if(NULL != tmp) {
        while(list->first != tmp->next && --index) {
            tmp = tmp->next;
        }
        node = tmp->next;
        if(list->first == node)
            if(node->next == node)
                list->first = NULL;
            else
                list->first = node->next;
        tmp->next = node->next;
        element = (NULL == node) ? node : node->element;
        node_t_delete(node);
        list->length--;
    }
    return element;
}

void *
list_t_remove(list_t *list, void *element, int (*compare)(void *, void *))
{
    void *previous = NULL;
    node_t *node;
    node_t *tmp = list->first;
    if(NULL != tmp)
        do {
            if(compare(tmp->next->element, element)) {
                node = tmp->next;
                if(list->first == node)
                    if(node->next == node)
                        list->first = NULL;
                    else
                        list->first = node->next;
                tmp->next = node->next;
                previous = (NULL == node) ? node : node->element;
                node_t_delete(node);
                list->length--;
                break;
            }
            tmp = tmp->next;
        } while(list->first != tmp);
    return previous;
}

void *
list_t_remove_first(list_t *list)
{
    return list_t_remove_at(list, 0);
}

void *
list_t_remove_last(list_t *list)
{
    return list_t_remove_at(list, -1);
}

void *
list_t_set_at(list_t *list, size_t index, void *element)
{
    void *previous = NULL;
    node_t *tmp = list->first;
    if(NULL != tmp) {
        do {
            tmp = tmp->next;
        } while(list->first != tmp && index--);
        previous = tmp->element;
        tmp->element = element;
    }
    return previous;
}

size_t
list_t_size(list_t *list)
{
    return list->length;
}
