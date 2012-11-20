#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFSIZE 1024

struct list_t {
    long size;
    struct node_t *root;
};

struct node_t {
    char *data;
    struct node_t *next;
};

void insert (struct list_t *, char *);

int main () {
    char **lines = NULL;
    char *line = NULL;

    struct list_t list;
        list.size = 0;
        list.root = NULL;

    char c;
    char buf[BUFSIZE];
    int i = -1;
    while((c=getchar()) != EOF) {
        if(++i>=BUFSIZE-1 || '\n'==c) {
            line = malloc(sizeof(size_t) * (i+1));
            buf[i] = '\0'; i = -1;
            strcpy(line, buf);
            insert(&list, line);
        } else {
            buf[i] = c;
        }
    }

   struct node_t *ptr= list.root;
   while(NULL != ptr->next) {
        if(strcoll()) {
        } else {
        }
   }

    struct node_t *ptr = list.root;
    while(NULL != ptr) {
        puts(ptr->data);
        ptr = ptr->next;
    }

    exit(EXIT_SUCCESS);
}

void insert (struct list_t *list, char *data) {
    struct node_t *node = (struct node_t *) malloc(sizeof(struct node_t));
        node->data = data;
        node->next = NULL;
    if(NULL == list->root) {
        list->root = node;
    } else {
        struct node_t *ptr = list->root;
        while(NULL != ptr->next) {
            ptr++;
        }
        ptr->next = node;
    }
    list->size++;
}
