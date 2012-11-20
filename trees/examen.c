#include <stdio.h>
#include <stdlib.h>

typedef struct arbol {
    struct arbol *izq;
    struct arbol *der;
    int dato;
}       arbol_t;

arbol_t *   crear(int);
arbol_t *   insertar(arbol_t *, int);
void        inorden(arbol_t *);
void        postorden(arbol_t *);
void        preorden(arbol_t *);
int         altura(arbol_t *);

int
main()
{
    arbol_t *arbol = NULL;
    arbol = insertar(arbol, 10);
    arbol = insertar(arbol, 8);
    arbol = insertar(arbol, 7);
    arbol = insertar(arbol, 12);
    arbol = insertar(arbol, 11);
    arbol = insertar(arbol, 13);
    puts("preorden(arbol);");
    preorden(arbol);
    puts("inorden(arbol);");
    inorden(arbol);
    puts("postorden(arbol);");
    postorden(arbol);
    puts("altura(arbol);");
    printf("%d\n", altura(arbol));
}

arbol_t *
crear(int dato)
{
    arbol_t *arbol = (arbol_t *)malloc(sizeof(arbol_t));
    if(NULL != arbol) {
        arbol->izq = NULL;
        arbol->der = NULL;
        arbol->dato = dato;
    }
    return arbol;
}

arbol_t *
insertar(arbol_t *arbol, int dato)
{
    if(NULL == arbol)
        return crear(dato);
    if(dato < arbol->dato)
        arbol->izq = insertar(arbol->izq, dato);
    else
        arbol->der = insertar(arbol->der, dato);
    return arbol;
}

void
inorden(arbol_t *arbol)
{
    if(arbol != NULL) {
        inorden(arbol->izq);
        printf("%d\n", arbol->dato);
        inorden(arbol->der);
    }
}

void
postorden(arbol_t *arbol)
{
    if(arbol != NULL) {
        postorden(arbol->izq);
        postorden(arbol->der);
        printf("%d\n", arbol->dato);
    }
}

void
preorden(arbol_t *arbol)
{
    if(arbol != NULL) {
        printf("%d\n", arbol->dato);
        preorden(arbol->izq);
        preorden(arbol->der);
    }
}

int
altura(arbol_t *arbol)
{
    if(arbol != NULL) {
        int izq = altura(arbol->izq);
        int der = altura(arbol->der);
        if(der < izq) {
            return izq + 1;
        } else {
            return der + 1;
        }
    } else {
        return -1;
    }
}
