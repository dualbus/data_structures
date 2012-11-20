#include <stdio.h>
#include <stdlib.h>

void quicksort(int A[], int i, int j);

int main (void) {
    int A[] = { 5, 5, 8, 3, 4, 7, 1, 3, 4 };
    int n = 9, i;
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    puts("quicksort()");
    quicksort(A, 0, n - 1);
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    exit(EXIT_SUCCESS);
}

void quicksort(int A[], int i, int j) {
    int a = i, b = j, c = j, p = A[c];

    if(0 > i || 0 >= j || 0 >= j - i) return;

    while(a != b) {
        if(A[b] <= p && p <= A[a] && A[a] != A[b]) {
            int t = A[b];
            A[b] = A[a];
            A[a] = t;
            c = (a == c) ? b : a;
        } else if(A[b] <= p) {
            a++;
        } else if(p <= A[a]) {
            b--;
        }
    }

    quicksort(A, 0, c - 1);
    quicksort(A, c + 1, j);
}
