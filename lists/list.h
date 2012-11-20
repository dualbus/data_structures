typedef struct lnode {
    struct lnode *next;
    void * element;
}           node_t;
node_t *    node_t_new(void *);
void        node_t_delete(node_t *);

typedef struct llist {
    struct lnode *first;
    size_t length;
}           list_t;
list_t *    list_t_new(void);
void        list_t_delete(list_t *);

void        list_t_add_at(list_t *, size_t, void *);
void        list_t_add(list_t *, void *);
void        list_t_add_first(list_t *, void *);
void        list_t_add_last(list_t *, void *);
void        list_t_clear(list_t *);
list_t *    list_t_clone(list_t *);
int         list_t_contains(list_t *, void *);
void *      list_t_get_at(list_t *, size_t);
void *      list_t_get_first(list_t *);
void *      list_t_get_last(list_t *);
size_t      list_t_index_of(list_t *, void *, int (*)(void *, void *));
size_t      list_t_last_index_of(list_t *, void *, int (*)(void *, void*));
void *      list_t_remove_at(list_t *, size_t);
void *      list_t_remove(list_t *, void *, int (*)(void *, void *));
void *      list_t_remove_first(list_t *);
void *      list_t_remove_last(list_t *);
void *      list_t_set_at(list_t *, size_t, void *);
size_t      list_t_size(list_t *);
