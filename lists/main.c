#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "list.h"

#define ALUMNO_LEN      25
#define CARRERA_LEN     15

typedef struct alumno {
    int matricula;
    char *nombre;
    char *carrera;
} alumno_t;
alumno_t *  alumno_t_new();
void        alumno_t_delete(alumno_t *alumno);

int compare(void *a, void *b)
{
    return ((alumno_t *)a)->matricula == ((alumno_t *)b)->matricula;
}

int
main()
{
    list_t *list = list_t_new();
    node_t *tmp;
    alumno_t *alumno;
    size_t index;
    int input = 0, c, matricula = 0;
    size_t linecap;
    do {
        puts("1. Insertar.");
        puts("2. Buscar.");
        puts("3. Eliminar.");
        puts("4. Modificar.");
        puts("5. Imprimir.");
        puts("6. Salir.");
        printf("---\n> ");
        if(0 >= scanf("%d", &input))
            exit(EXIT_FAILURE);
        while(EOF != (c = getchar()) && '\n' != c);
        puts("");
        switch(input) {
            case 1:
                /* Insertar */
                alumno = alumno_t_new(); 
                alumno->matricula = matricula++;
                printf("Nombre = ");
                linecap = ALUMNO_LEN;
                if(0 >= (c=getline(&(alumno->nombre), &linecap, stdin)))
                    exit(EXIT_FAILURE);
                alumno->nombre[c - 1] = '\0';
                printf("Carrera = ");
                linecap = CARRERA_LEN;
                if(0 >= (c=getline(&(alumno->carrera), &linecap, stdin)))
                    exit(EXIT_FAILURE);
                alumno->carrera[c - 1] = '\0';
                list_t_add(list, alumno);
                printf("Matricula: %d\n\n", alumno->matricula);
                break;
            case 2:
                /* Buscar */
                alumno = alumno_t_new(); 
                printf("Matricula = ");
                if(0 >= scanf("%d", &(alumno->matricula)))
                    exit(EXIT_FAILURE);
                while(EOF != (c = getchar()) && '\n' != c);
                alumno_t_delete(alumno);
                index = list_t_index_of(list, alumno, compare);
                if(0 <= index) {
                    alumno = ((alumno_t *)list_t_get_at(list, index));
                    printf("Nombre: %s\n", alumno->nombre);
                    printf("Carrera: %s\n", alumno->carrera);
                } else {
                    puts("No se encontro tal alumno");
                }
                puts("\n");
                break;
            case 3:
                /* Eliminar */
                alumno = alumno_t_new(); 
                printf("Matricula = ");
                if(0 >= scanf("%d", &(alumno->matricula)))
                    exit(EXIT_FAILURE);
                while(EOF != (c = getchar()) && '\n' != c);
                alumno_t_delete(list_t_remove(list, alumno, compare));
                alumno_t_delete(alumno);
                puts("\n");
                break;
            case 4:
                /* Modificar */
                alumno = alumno_t_new(); 
                printf("Matricula = ");
                if(0 >= scanf("%d", &(alumno->matricula)))
                    exit(EXIT_FAILURE);
                while(EOF != (c = getchar()) && '\n' != c);
                index = list_t_index_of(list, alumno, compare);
                puts("1. Nombre.");
                puts("2. Carrera.");
                printf("Modificar = ");
                if(0 >= scanf("%d", &input))
                    exit(EXIT_FAILURE);
                while(EOF != (c = getchar()) && '\n' != c);
                alumno_t_delete(alumno);
                alumno = list_t_get_at(list, index);
                switch(input) {
                    case 1:
                        printf("Nombre = ");
                        linecap = ALUMNO_LEN;
                        if(0 >= (c=getline(&(alumno->nombre), &linecap, stdin)))
                            exit(EXIT_FAILURE);
                        alumno->nombre[c - 1] = '\0';
                        break;
                    case 2:
                        printf("Carrera = ");
                        linecap = CARRERA_LEN;
                        if(0 >= (c=getline(&(alumno->carrera), &linecap, stdin)))
                            exit(EXIT_FAILURE);
                        alumno->carrera[c - 1] = '\0';
                        break;
                }
                puts("\n");
                break;
            case 5:
                /* Imprimir */
                puts("---");
                tmp = list->first;
                if(NULL != list->first)
                    do {
                        printf( "Matricula: %d\n"
                                "Nombre: %s\n" 
                                "Carrera: %s\n\n", 
                            ((alumno_t *)tmp->element)->matricula,
                            ((alumno_t *)tmp->element)->nombre,
                            ((alumno_t *)tmp->element)->carrera);
                        tmp = tmp->next;
                    } while(list->first != tmp);
                printf("---\n");
                break;
        }
    } while(6 != input);
    exit(EXIT_SUCCESS);
}

alumno_t *
alumno_t_new()
{
    alumno_t *alumno = (alumno_t *)malloc(sizeof(alumno_t));
    alumno->matricula = -1;
    alumno->nombre = (char *)malloc(sizeof(char) * ALUMNO_LEN);
    alumno->carrera = (char *)malloc(sizeof(char) * CARRERA_LEN);
    return alumno;
}

void
alumno_t_delete(alumno_t *alumno)
{
    if(NULL != alumno) {
        free(alumno->nombre);
        free(alumno->carrera);
        free(alumno);
    }
}
