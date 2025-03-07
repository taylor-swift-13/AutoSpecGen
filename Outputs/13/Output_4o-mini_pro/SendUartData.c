
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0 .. pIp->len - 1));
  requires pIp->len >= 0;
  ensures \forall integer j; 0 <= j < pIp->len ==> 
          \at(pIp->data[j], Pre) == pIp->data[j]; 
  assigns \nothing;
*/
void SendUartDataFun(SendUartData *pIp)
{
    unsigned int i; // Fixed type from 'unsigned int32' to 'unsigned int'
    
    /*@ loop invariant 0 <= i <= pIp->len;
        loop assigns i;
        loop variant pIp->len - i;
    */
    for (i = 0; i < pIp->len; i++)
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
