#include <stdio.h>
#include <stdlib.h>

void selectsort(int A[], int n) {
    int i, x, y;
    for(x = 0; x < (n - 1); x++) {
        i = x;
        for(y = x + 1; y < n; y++) {
            if(A[y] < A[i]) {
                i = y;
            }
        }
        if(x != i) {
            int t = A[x];
            A[x] = A[i];
            A[i] = t;
        }
    }
}

int main () {
    char b[1024];
    char c;
    int i, j;
    int n;
    printf("N: ");
    i = 0;
    while((c=getchar()) != EOF) {
        if(!isdigit(c)) break;
        b[i++] = c;
    }; b[i] = '\0';
    n = atoi(b);
    int a[n];
    for(j = 0; j < n; j++) {
        i = 0;
        printf("%d/%d> ", j+1, n);
        while((c=getchar()) != EOF && 1024 - 1 > i) {
            if('\n' == c && 0 == i) j--;
            if(!isdigit(c)) break;
            b[i++] = c;
        }; b[i] = '\0';
        a[j] = atoi(b);
    }
    
    selectsort(a, n);
    for(i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}
