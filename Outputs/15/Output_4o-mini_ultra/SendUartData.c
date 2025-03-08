
#include "SendUartData.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->data + (0..pIp->len - 1));
  requires pIp->len >= 0;
  assigns \nothing; // No variables are modified in this function
*/
void SendUartDataFun(SendUartData *pIp) 
{
    /*@ loop invariant 0 <= i <= pIp->len;
        loop assigns \nothing; // No variables are modified in the loop
        loop variant pIp->len - i; 
    */
    for (unint32 i = 0; i < pIp->len; i++) 
    {
        ADDR_WRITE(pIp->addr, pIp->data[i]);
    }
    return;
}
