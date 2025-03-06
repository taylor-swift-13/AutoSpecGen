
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0 .. pIp->len-1));
  requires pIp->len >= 0;
  ensures \forall integer j; 0 <= j < pIp->len ==> \initialized(&pIp->data[j]);
  assigns pIp->data[0 .. pIp->len-1];
*/
void SendUartDataFun(SendUartData *pIp)
{
    unint32 i;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant \forall integer j; 0 <= j < i ==> \initialized(&pIp->data[j]);
      loop assigns i;
      loop variant pIp->len - i;
    */
    for (i = 0; i < pIp -> len; i++)
    {
        ADDR_WRITE(pIp -> addr, pIp -> data[i]);
    }
    return;
}
