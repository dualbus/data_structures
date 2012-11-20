#include <stdio.h>
#include <stdlib.h>

void mymergesort(int A[], int i, int j);
void merge(int A[], int i, int j, int x, int y);

int main (void)
{
    int A[] = { 5, 5, 8, 3, 4, 7, 1, 3, 4 };
    int n = 9, i;
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    puts("mymergesort()");
    mymergesort(A, 0, n - 1);
    for(i = 0; i < n; i++)
        printf("%d\n", A[i]); 
    exit(EXIT_SUCCESS);
}

void merge(int A[], int i, int j, int x, int y) {
    int a, b, c;
    int B[(j - i + 1) + (y - x + 1)];
    for(a = i, b = x, c = 0; a <= j || b <= y; ) {
        if (a <= j && b <= y) {
            if(A[a] < A[b]) {
                B[c++] = A[a++];
            } else {
                B[c++] = A[b++];
            }
        } else if(a <= j) {
            B[c++] = A[a++];
        } else if(b <= y) {
            B[c++] = A[b++];
        }
    }
    for(a = i, b = x, c = 0; a <= j || b <= y; ) {
        if(a <= j) {
            A[a++] = B[c++];
        } else {
            A[b++] = B[c++];
        }
    }
}

void mymergesort(int A[], int i, int j)
{
    int n = (j - i + 1) / 2;
    int d = j - i; 
    if(0 >= d) {
    } else if (1 == d) {
        if(A[i] > A[j]) {
            int t = A[i];
            A[i] = A[j];
            A[j] = t;
        }
    } else {
        mymergesort(A, i, i + n - 1);
        mymergesort(A, i + n, j);
        merge(A, i, i + n - 1, i + n, j);
    }
}
