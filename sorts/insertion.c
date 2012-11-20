#include <stdio.h>
#include <stdlib.h>

void insertionsort(int A[], int n);

int main (void) {
    int A[] = { 5, 5, 8, 3, 4, 7, 1, 3, 4 };
    int n = 9, i;
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    puts("insertionsort()");
    insertionsort(A, n);
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    exit(EXIT_SUCCESS);
}

void insertionsort(int A[], int n) {
    int i, j;

    if(0 >= n) return;

    for(i = 1; i < n; i++) {
        int t = A[i];
        for(j = i - 1; j >= 0; j--) {
            if (A[j] <= t) break;
            A[j+1] = A[j];
        }
        A[j+1] = t;
    }
}
