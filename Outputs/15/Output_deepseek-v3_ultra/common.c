
#include "common.h"

/*@ requires \valid(a + (0..n-1));
    requires \valid(b + (0..n-1));
    requires n >= 0;
    ensures \forall integer i; 0 <= i < n ==> a[i] == \old(b[i]);
    ensures \forall integer i; 0 <= i < n ==> b[i] == \old(a[i]);
    assigns a[0..n-1], b[0..n-1];
*/
void swap_arrays(int* a, int* b, int n) {
    // Logic variables to store initial values of a and b
    /*@ ghost int* initial_a = a; */
    /*@ ghost int* initial_b = b; */

    /*@ loop invariant 0 <= i <= n;
        loop invariant \forall integer j; 0 <= j < i ==> a[j] == initial_b[j];
        loop invariant \forall integer j; 0 <= j < i ==> b[j] == initial_a[j];
        loop assigns a[0..n-1], b[0..n-1];
        loop variant n - i;
    */
    for (int i = 0; i < n; i++) {
        int temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}
