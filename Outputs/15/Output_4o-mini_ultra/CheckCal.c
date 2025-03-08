
#include "CheckCal.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing;
*/
void CheckCalFun(CheckCal *pIp)
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop invariant \forall integer j; 0 <= j < i ==> 
            \exists integer chksum; chksum == sum(pIp->pkv, 0, j + 1); // Use axiomatic sum for array
        loop assigns \nothing; // No assignments to chksum, as it is not a variable in this scope
        loop variant pIp->len - i;
    */
    for(unint32 i = 0; i < pIp->len; i++)
    {
        /*@ requires \valid(pIp->pkv + i); */
        chksum = chksum + pIp->pkv[i]; // This line will still need to be valid in the context of the function
    }

    return;
}
