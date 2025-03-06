#include "CheckCal16.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0 .. pIp->len-1));
  requires pIp->len > 0;
  ensures \forall integer i; 0 <= i < pIp->len ==> \old(pIp->pkv[i]) == pIp->pkv[i];
  assigns pIp->pkv[0 .. pIp->len-1];
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    unint32 i;
    unint16 chksum = 0;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant \forall integer k; 0 <= k < i ==> chksum == \sum(pIp->pkv[0 .. k]);
      loop assigns i, chksum;
      loop variant pIp->len - i;
    */
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }
    return;
}
