
#include "CheckCal16.h"

/*@ 
    requires \valid(pIp);
    requires pIp->len >= 0;
    requires \valid(pIp->pkv + (0 .. pIp->len - 1));
    assigns \nothing;
*/
void CheckCal16Fun(CheckCal16 *pIp)
{
    /*@ 
        loop invariant 0 <= i <= pIp->len;
        loop invariant chksum == \sum_{j=0}^{i-1} pIp->pkv[j];
        loop assigns i, chksum;
        loop variant pIp->len - i;
    */
    for(unsigned int i = 0; i < pIp->len; i++)
    {
        chksum = chksum + pIp->pkv[i];
    }
    return;
}
