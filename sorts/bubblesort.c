void
bubblesort(int A[], unsigned int n)
{
  int i, j;

  for(i = 0; i < n; i++) {
    for(j = i; j < n; j++) {
      if(A[i] > A[j]) {
        int    t = A[j];
            A[j] = A[i];
            A[i] =    t;
      }
    }
  }
}



#ifdef DEBUG
#include <stdio.h>

int
main(int argc, char **argv) {
  int i, n;
  int A[] = {1,3,4,2,5};

  n = sizeof(A)/sizeof(A[0]);

  bubblesort(A, n);

  for(i = 0; i < n; i++) {
    printf("%d\n", A[i]);
  }

  return 0;
}
#endif
