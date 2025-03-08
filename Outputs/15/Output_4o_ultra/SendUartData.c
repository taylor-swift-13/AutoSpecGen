
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len-1));
  requires pIp->len >= 0;
  assigns pIp->addr[0..pIp->len-1];
  ensures \forall integer i; 0 <= i < pIp->len ==> \valid(pIp->addr) && \valid(pIp->data + i);
*/
void SendUartDataFun(SendUartData *pIp)
{
    unint32 i;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant \forall integer j; 0 <= j < i ==> \valid(pIp->addr) && \valid(pIp->data + j);
      loop assigns i, pIp->addr[0..pIp->len-1];
      loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
