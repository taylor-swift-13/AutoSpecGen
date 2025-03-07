
#include "GetUartData.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires \valid(pIp->ret);
  ensures *pIp->ret == (fifoCnt == pIp->len ? 1 : 0);
  assigns pIp->bSucc, pIp->data[0..pIp->len - 1], *pIp->ret;
*/
void GetUartDataFun(GetUartData *pIp)
{
    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop assigns i, pIp->data[i];
      loop variant pIp->len - i;
    */
    unsigned int fifoCnt; 
    unsigned int i;      

    pIp -> bSucc = 0;
    fifoCnt = ADDR_READ(0x88D0);

    if (fifoCnt == pIp -> len)
    {
        for (i = 0; i < pIp -> len; i++)
        {
            pIp -> data[i] = ADDR_READ(pIp -> addr);
        }

        pIp -> bSucc = 1;
    }

    *(pIp -> ret) = pIp -> bSucc;
}
