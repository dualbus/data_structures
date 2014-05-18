/*
 *
 */
void
insertionsort(int A[], unsigned int n)
{
    int i, j;

    if(1 >= n) return;

    for(i = 1; i < n; i++) {
        for(j = i; j > 0 && A[j-1] > A[j]; j--) {
            int t  = A[j-1];
            A[j-1] = A[j];
              A[j] =    t;
        }
    }
}



#ifdef DEBUG
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int A[] = { 5, 5, 8, 3, 4, 7, 1, 3, 4 };
    int n = 9, i;

    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    puts("insertionsort()");
    insertionsort(A, n);

    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 

    return 0;
}
#endif
