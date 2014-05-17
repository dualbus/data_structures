void
quicksort(int A[], unsigned int i, unsigned int j)
{
    unsigned int k, z;
    int pivotValue, t;

    if(j <= i || 1 > j - i) return;

    pivotValue = A[j];

    for(z = i, k = i; k < j; k++) {
        if(A[k] <= pivotValue) {
               t = A[k];
            A[k] = A[z];
            A[z] =    t;

            z++;
        }
    }

       t = A[z];
    A[z] = A[j];
    A[j] = t;


    if(z > i) {
        quicksort(A, i, z-1);
    }

    quicksort(A, z+1, j);
}



#ifdef DEBUG
#include <stdio.h>

int main (void) {
    int i, n;
    int A[] = { 5, 7, 1, 3, 4, 1, 3, 1, 2, 4, 7, 12 };

    n = sizeof(A)/sizeof(A[0]);

    for(i = 0; i < n; i++) {
        printf("%d\n", A[i]); 
    }

    quicksort(A, 0, n - 1);

    for(i = 0; i < n; i++) {
        printf("%d\n", A[i]); 
    }

    return 0;
}
#endif
