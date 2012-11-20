#include <stdlib.h>
#include <string.h>
#include "list.h"

#define REGISTERS_SIZE       8
#define MEMORY_SIZE         1024

typedef list_t stack_t;
stack_t *   stack_t_new(void);
void        stack_t_delete(stack_t *);

void        stack_t_push(stack_t *, void *);
void *      stack_t_pop(stack_t *);

typedef enum storage {
    CPU_REGISTER,
    CPU_MEMORY,
}           storage_t;

typedef struct cpu {
    unsigned char registers[REGISTERS_SIZE];
    unsigned char memory[MEMORY_SIZE];
    stack_t *stack;
}           cpu_t;

cpu_t *     cpu_t_new(void);
void        cpu_t_delete(cpu_t *);

void        cpu_t_idata(cpu_t *, size_t, char);
void        cpu_t_imov(cpu_t *, storage_t, size_t, storage_t, size_t);
void        cpu_t_ipush(cpu_t *, size_t);
void        cpu_t_ipop(cpu_t *, size_t);
void        cpu_t_ipusha(cpu_t *);
void        cpu_t_ipopa(cpu_t *);
void        cpu_t_show(cpu_t *cpu);

int
main(void)
{
    int option, a, b, c;
    cpu_t *cpu = cpu_t_new();
    do {
        puts("1. Push");
        puts("2. Pop");
        puts("3. Pusha");
        puts("4. Popa");
        puts("5. Mov");
        puts("6. Mostrar Reg");
        puts("7. Asignar a ram");
        puts("8. Salir");
        printf("= ");
        scanf("%d", &option);
        while('\n' != getchar());
        switch(option) {
            case 1:
                printf("= ");
                scanf("%d", &option);
                while('\n' != getchar());
                cpu_t_ipush(cpu, option);
                break;
            case 2:
                printf("= ");
                scanf("%d", &option);
                while('\n' != getchar());
                cpu_t_ipop(cpu, option);
                break;
            case 3:
                cpu_t_ipusha(cpu);
                break;
            case 4:
                cpu_t_ipopa(cpu);
                break;
            case 5:
                printf("= ");
                scanf("%c", &option);
                while('\n' != getchar());
                printf("= ");
                scanf("%d", &a);
                while('\n' != getchar());
                printf("= ");
                scanf("%c", &b);
                while('\n' != getchar());
                printf("= ");
                scanf("%d", &c);
                while('\n' != getchar());
                if('m' == option) {
                    option = CPU_MEMORY;
                } else {
                    option = CPU_REGISTER;
                }
                if('m' == b) {
                    b = CPU_MEMORY;
                } else {
                    b = CPU_REGISTER;
                }
                cpu_t_imov(cpu, option, a, b, c);
                break;
            case 6:
                cpu_t_show(cpu);
                break;
            case 7:
                printf("= ");
                scanf("%d", &option);
                while('\n' != getchar());
                printf("= ");
                scanf("%d", &a);
                while('\n' != getchar());
                cpu_t_idata(cpu, option, a);
                break;
            case 8:
                break;
        }
        puts("---");
    } while(8 != option);
}

stack_t *
stack_t_new(void)
{
    return list_t_new();
}

void
stack_t_delete(stack_t *stack)
{
    list_t_delete(stack);
}

void
stack_t_push(stack_t *stack, void *element)
{
    list_t_add_first(stack, element);
}

void *
stack_t_pop(stack_t *stack)
{
    return list_t_remove_first(stack);
}

cpu_t *
cpu_t_new(void)
{
    cpu_t *cpu = (cpu_t *)malloc(sizeof(cpu_t));
    if(NULL != cpu) {
        bzero(cpu->registers, REGISTERS_SIZE);
        bzero(cpu->memory, MEMORY_SIZE);
        cpu->stack = stack_t_new();
    }
    return cpu;
}

void
cpu_t_delete(cpu_t *cpu)
{
}


void
cpu_t_idata(cpu_t *cpu, size_t dst, char value)
{
    cpu->memory[dst] = value;
}

void
cpu_t_imov(cpu_t *cpu, storage_t src_type, size_t src, storage_t dst_type, size_t dst)
{
    if(CPU_REGISTER == src_type) {
        if(CPU_REGISTER == dst_type) {
            cpu->registers[dst] = cpu->registers[src];
        } else {
            cpu->memory[dst] = cpu->registers[src];
        }
    } else {
        if(CPU_REGISTER == dst_type) {
            cpu->registers[dst] = cpu->memory[src];
        } else {
            cpu->memory[dst] = cpu->memory[src];
        }
    }
}

void
cpu_t_ipush(cpu_t *cpu, size_t src)
{
    char *c = (char *)malloc(sizeof(char));
    *c = cpu->registers[src];
    stack_t_push(cpu->stack, c);
}

void
cpu_t_ipop(cpu_t *cpu, size_t dst)
{
    void *element = stack_t_pop(cpu->stack);
    if(NULL != element) {
        cpu->registers[dst] = *(char *)element;
        free(element);
        element = NULL;
    }
}

void
cpu_t_ipusha(cpu_t *cpu)
{
    size_t i;
    for(i = 0; i < REGISTERS_SIZE; i++) {
        cpu_t_ipush(cpu, i);
    }
}

void
cpu_t_ipopa(cpu_t *cpu)
{
    size_t i;
    for(i = 0; i < REGISTERS_SIZE; i++) {
        void *element = stack_t_pop(cpu->stack);
        if(NULL == element) {
            break;
        } else {
            cpu->registers[i] = *(char *)element;
            free(element);
            element = NULL;
        }
    }
}

void
cpu_t_show(cpu_t *cpu)
{
    static char names[] = "abcdefghijklmnopqrstuvwxyz";
    size_t i;
    for(i = 0; i < REGISTERS_SIZE; i++) {
        printf("%cx: %d\n", names[i], cpu->registers[i]);
    }
}
