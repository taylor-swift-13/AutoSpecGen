
#include "CheckCal.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pkv + (0 .. pIp->len-1));
  requires pIp->len > 0;
  assigns \nothing;
  ensures \forall integer i; 0 <= i < pIp->len ==> \old(pIp->pkv[i]) == pIp->pkv[i];
*/
void CheckCalFun(CheckCal *pIp)
{
    unint32 i;
    unint08 chksum = 0;

    /*@
      loop invariant 0 <= i <= pIp->len;
      loop invariant chksum == \sum(0, i, pIp->pkv);
      loop assigns i, chksum;
      loop variant pIp->len - i;
    */
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
