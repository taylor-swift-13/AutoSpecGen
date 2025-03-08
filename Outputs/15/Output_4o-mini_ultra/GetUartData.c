
#include "GetUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires \valid(pIp->ret);
  requires pIp->len > 0;
  ensures *pIp->ret == (ADDR_READ(0x88D0) == pIp->len ? 1 : 0);
  assigns pIp->bSucc, pIp->data[0..pIp->len - 1], *pIp->ret;
*/
void GetUartDataFun(GetUartData *pIp)
{
    unint32 fifoCnt;
    fifoCnt = ADDR_READ(0x88D0);
    
    pIp->bSucc = 0;

    /*@ loop invariant 0 <= i <= pIp->len;
        loop variant pIp->len - i;
    */
    for (unint32 i = 0; i < pIp->len; i++)
    {
        pIp->data[i] = ADDR_READ(pIp->addr);
    }

    if (fifoCnt == pIp->len)
    {
        pIp->bSucc = 1;
    }

    *(pIp->ret) = pIp->bSucc;
}
