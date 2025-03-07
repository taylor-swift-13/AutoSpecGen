
#include "CheckCal.h"

/*@ 
  requires \valid(pIp);
  requires pIp->len >= 0;
  requires \valid(pIp->pkv + (0 .. pIp->len - 1));
  assigns pIp->pkv[0 .. pIp->len - 1]; 
*/
void CheckCalFun(CheckCal *pIp)
{
    unint32 i;
    unint08 chksum = 0;

    /*@
      loop invariant 0 <= i <= pIp->len;
      loop invariant chksum == \sum_{j=0}^{i-1} pIp->pkv[j];
      loop assigns i, chksum;
      loop variant pIp->len - i;
    */
    for(i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }

    return;
}
