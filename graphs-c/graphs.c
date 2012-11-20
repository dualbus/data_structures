typedef struct edge {
    struct edge *next;
    struct vertex *dest;
    int value;
}           edge_t;

edge_t *    edge_t_new(int);
void        edge_t_delete(edge_t *);

typedef struct vertex {
    struct vertex *next;
    struct edge *root;
}           vertex_t;

vertex_t *  vertex_t_new();
void        vertex_t_delete(vertex_t *);
void        vertex_t_connect(vertex_t *, vertex_t *, int);

typedef struct graph {
    struct vertex *root;
}           graph_t;

graph_t *   graph_t_new();
void        graph_t_delete(graph_t *);
void        graph_t_insert(graph_t *, vertex_t *);
void        graph_t_connect(graph_t *, vertex_t *, vertex_t *, int);

#include <stdlib.h>
#include <stdio.h>

int
main()
{
    graph_t *graph = graph_t_new();
    vertex_t *vertex_a = vertex_t_new();
    vertex_t *vertex_b = vertex_t_new();
    vertex_t *vertex_c = vertex_t_new();
    vertex_t *vertex_d = vertex_t_new();
    graph_t_insert(graph, vertex_a);
    graph_t_insert(graph, vertex_b);
    graph_t_insert(graph, vertex_c);
    graph_t_insert(graph, vertex_d);
    graph_t_connect(graph, vertex_a, vertex_b, 5);
    graph_t_connect(graph, vertex_b, vertex_c, 3);
    graph_t_connect(graph, vertex_b, vertex_d, 9);
    graph_t_connect(graph, vertex_c, vertex_d, 8);
    vertex_t *tmp = graph->root;
    while(NULL != tmp) {
        edge_t *edge = tmp->root;
        while(NULL != edge) {
            printf("%p => %p: %d\n", tmp, edge->dest, edge->value);
            edge = edge->next;
        }
        tmp = tmp->next;
    }
    return 0;
}

edge_t *
edge_t_new(int value)
{
    edge_t *edge = (edge_t *)malloc(sizeof(edge_t));
    if(NULL != edge) {
        edge->next = NULL;
        edge->dest = NULL;
        edge->value = value;
    }
    return edge;
}

void
edge_t_delete(edge_t *edge)
{
}

vertex_t *
vertex_t_new()
{
    vertex_t *vertex = (vertex_t *)malloc(sizeof(vertex_t));
    if(NULL != vertex) {
        vertex->next = NULL;
    }
    return vertex;
}

void
vertex_t_delete(vertex_t *vertex)
{
}

void
vertex_t_connect(vertex_t *vertex_a, vertex_t *vertex_b, int value)
{
    edge_t *edge_a = edge_t_new(value);
    edge_t *edge_b = edge_t_new(value);
    if(NULL == vertex_a->root) {
        vertex_a->root = edge_a;
    } else {
        edge_t *tmp = vertex_a->root;
        while(NULL != tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = edge_a;
    }
    if(NULL == vertex_b->root) {
        vertex_b->root = edge_b;
    } else {
        edge_t *tmp = vertex_b->root;
        while(NULL != tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = edge_b;
    }
    edge_a->dest = vertex_b;
    edge_b->dest = vertex_a;
}

graph_t *
graph_t_new()
{
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
    if(NULL != graph) {
        graph->root = NULL;
    }
    return graph;
}

void
graph_t_delete(graph_t *graph)
{
}

void
graph_t_insert(graph_t *graph, vertex_t *vertex)
{
    if(NULL == graph->root) {
        graph->root = vertex;
    } else {
        vertex_t *tmp = graph->root;
        while(NULL != tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = vertex;
    }
}

void
graph_t_connect(graph_t *graph, vertex_t *vertex_a, vertex_t *vertex_b, int
                    value)
{
    vertex_t_connect(vertex_a, vertex_b, value);
}
