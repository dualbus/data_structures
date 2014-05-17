#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#define ITEMS 10000



void bubblesort (int A[], unsigned int n);
void quicksort  (int A[], unsigned int i, unsigned int j);
int  verify     (int A[], unsigned int n);


unsigned int rng();
void rng_seed(unsigned int, unsigned int, unsigned int);



int main() {
  int *A, *B;
  unsigned int i;
  struct timeval r_tv, tv_Ax, tv_Ay, tv_Bx, tv_By;
  
  A = (int *)malloc(sizeof(int) * ITEMS);
  B = (int *)malloc(sizeof(int) * ITEMS);

  if(B == NULL || A == NULL) return 1;


  gettimeofday(&r_tv, NULL);
  rng_seed(r_tv.tv_sec ^ r_tv.tv_usec, getpid(), 12345);


  for(i = 0; i < ITEMS; i++) {
    int random = (int)rng();

    A[i] = random;
    B[i] = random;
  }

  gettimeofday(&tv_Ax, NULL);
  bubblesort(A, ITEMS);
  gettimeofday(&tv_Ay, NULL);

  gettimeofday(&tv_Bx, NULL);
  quicksort (B, 0, ITEMS - 1);
  gettimeofday(&tv_By, NULL);


  printf("bubblesort| [%s] %u.%u (sec)\n",
      verify(A, ITEMS) ? "YES" : "NO ",
      tv_Ay.tv_sec - tv_Ax.tv_sec,
      tv_Ay.tv_usec - tv_Ax.tv_usec
      );

  printf("quicksort | [%s] %u.%u (sec)\n",
      verify(B, ITEMS) ? "YES" : "NO ",
      tv_By.tv_sec - tv_Bx.tv_sec,
      tv_By.tv_usec - tv_Bx.tv_usec
      );

  return 0;
}


int
verify(int A[], unsigned int n)
{
  unsigned int i, m;

  for(i = 0, m = n - 1; i < m; i++) {
    if(A[i] > A[i+1]) {
      return 0;
    }
  }

  return 1;
}
