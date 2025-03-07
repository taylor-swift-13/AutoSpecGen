
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid_read(pIp->data + (0 .. pIp->len - 1));
  assigns \nothing;
  ensures \forall integer i; 0 <= i < pIp->len ==> ADDR_WRITE(pIp->addr, \old(pIp->data[i])) == \old(pIp->data[i]);
*/
void SendUartDataFun(SendUartData *pIp)
{
    unint32 i;

    /*@ 
      loop invariant 0 <= i <= pIp->len;
      loop invariant \forall integer j; 0 <= j < i ==> ADDR_WRITE(pIp->addr, pIp->data[j]) == pIp->data[j];
      loop assigns i;
      loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
