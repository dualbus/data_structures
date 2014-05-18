/*
 * Verifies that an array of integers is sorted in ascending order.
 *
 * This is a simple procedure, we just have to make sure that for
 * every A_i, the condition A_i <= A_{i+1} holds true, or the
 * equivalent notion, that A_i > A_{i+1} is false.
 */
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
