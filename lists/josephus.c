#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define     WARRIOR_N   17
#define     HOPS        1

int
main ()
{
    list_t *list = list_t_new();
    int i;
    for(i = 1; i <= WARRIOR_N; i++) {
        int *j = (int *)malloc(sizeof(int));
        *j = i;
        list_t_add(list, j);
    }
    node_t *n = list->first, *t;
    do {
        n = n->next;
    } while(list->first != n->next);
    i = 0;
    do {
        if(HOPS > i) {
            i++;
            n = n->next;
        } else {
            i = 0;
            t = n->next;
            printf("+ %d\n", *(int *)t->element);
            n->next = t->next;
            list->length--;
            if(list->first == t) {
                list->first = t->next;
            }
        }
    } while (1 < list->length);
    printf("%d\n", *(int *)(list->first->element));
}
