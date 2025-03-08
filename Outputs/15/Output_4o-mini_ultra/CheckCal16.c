
#include "CheckCal16.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing;
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    unint32 chksum = 0; // Initialize chksum

    /*@ 
        loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == \sum(0, i, pIp->pkv); // Define chksum as the sum of elements
        loop assigns i, chksum; // Include chksum in assigns
        loop variant pIp->len - i;
    */
    for(unint32 i = 0; i < pIp -> len; i++)
    {
        /*@ requires \valid(pIp->pkv + i); */
        chksum = chksum + pIp -> pkv[i];
    }
    return;
}
