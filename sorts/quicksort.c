/*
 * The quicksort sorting algorithm by Tony Hoare.
 *
 * This is the in-place version of the algorithm, which means that
 * instead of creating a sorted copy of the array, we sort the
 * elements of the original array using the same space.
 *
 * It takes as input the following:
 *
 * - An array 'A' containing 'N' elements of type int.
 * - An index 'i', which is the index of the leftmost element in the
 *   array, so initially it should be 0 (C arrays are 0-indexed).
 * - An index 'j', which is the index of the rightmost element in the
 *   array (the last one). Due to the 0-indexing nature of C, 'j'
 *   corresponds to the size of the array, minus one, or the same as:
 *
 *   j = N - 1
 */
void
quicksort(int A[], unsigned int i, unsigned int j)
{
    unsigned int k, z;
    int pivotValue, t;

    /* If 'j' is less-than-or-equal-to 'i', that means that we're
     * trying to sort an array of zero elements, which makes no
     * sense.
     *
     * If the difference between 'j' and 'i' is less-than-or-equal-to
     * 1, then it means that we're trying to sort an array of one
     * element, which, is already sorted.
     *
     * In either case, we abort the algorithm.
     */
    if(j <= i || 1 >= j - i) return;

    /*
     * The pivot is an important piece of the algorithm. In short, a
     * pivot is used for the following: Once we choose a pivot, we go
     * through all the elements of the array, comparing each element
     * with the pivot. If the A_k element is less-than-or-equal-to the
     * pivot (A_k <= pivotValue), then we swap the A_k element with the
     * A_z element. 'z' happens to be an index that we keep pointing
     * to the element following the last element that we swapped, and
     * it's initialized to the index of the leftmost element, which
     * is 'i'.
     */
    pivotValue = A[j];

    /* We go throught the array 'A', starting at k = i, and up to 
     * k = j - 1
     *
     * This part is called the 'partitioning'.
     */
    for(z = i, k = i; k < j; k++) {

        /* If the element A_k is less-than-or-equal-to the
         * pivotValue, we swap A_k with A_z, with A_z being the
         * element that follows the last element that we swapped.
         *
         * Also, we increase 'z' to indicate that A_z was already
         * swapped, so the element that follows is A_{z+1}, thus we
         * set: z = z + 1.
         */
        if(A[k] <= pivotValue) {
               t = A[k];
            A[k] = A[z];
            A[z] =    t;

            z++;
        }
    }

    /* After the loop, all the elements that are
     * less-than-or-equal-to the pivotValue are in the left side of
     * the array, so that the following is true:
     *
     *   For all A_k, with k < z, A_k <= pivotValue
     *
     * So, the elements to the left of A_z are less than the
     * pivotValue.
     *
     * And what is also true, is that now, the elements that are
     * greater-than-or-equal-to the pivotValue are in the right side
     * of the array, so that the following holds:
     *
     *   For all A_k, with k > z, A_k >= pivotValue
     *
     * Except for a little detail, we still haven't moved the pivot
     * the the place where it belongs, which is A_z, instead of being
     * in A_j, due to our choice of pivot. So, let's swap these
     * values to put it where it should be.
     */
       t = A[z];
    A[z] = A[j];
    A[j] = t;

    /* After these, we're left with an array looking like this:
     *
     * i               z               j
     * [a][b][c][d][e][p][f][g][l][m][n]
     *
     * So that all the elements from i to z - 1, are smaller or equal
     * to the pivot 'p', and all the elements from z + 1 to j are
     * bigger or equal to the pivot 'p'.
     *
     * The key part of the quicksort algorithm is the following
     * insight:
     *
     * If we apply the 'partitioning' step recursively to the left
     * and right resulting sub-arrays, we will reach a point where we
     * have a 3 element array, which looks like this:
     *
     * i   z   j
     * [a][p][c]
     *
     * Which after the partitioning, it will be sorted (it's easy to
     * see why, if you remember that the left of the pivot is less or
     * equal, and the right of the pivot is greater or equal).
     *
     * So, in the end, we use the algorithm on smaller and smaller
     * arrays each time, until we reach this case, which is trivial
     * to sort, and since we use the algorithm on pairs (the left and
     * right of the pivot), we'll find out that the pairs are also
     * sorted relative to each other:
     */

    if(z > i) {
        quicksort(A, i, z - 1);
    }

    quicksort(A, z + 1, j);
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
