
#include "GetUartData.h"

/*@ axiomatic Sum_array {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    requires \valid(pIp->data + (0 .. pIp->len - 1));
    assigns pIp->bSucc, pIp->data[0 .. pIp->len - 1], *(pIp->ret);
    ensures *(pIp->ret) == pIp->bSucc;
    ensures pIp->bSucc == 1 ==> \forall integer i; 0 <= i < pIp->len ==> pIp->data[i] == ADDR_READ(pIp->addr);
*/
void GetUartDataFun(GetUartData *pIp)
{
    unint32 fifoCnt;
    unint32 i;

    pIp->bSucc = 0;
    fifoCnt = ADDR_READ(0x88D0);

    if (fifoCnt == pIp->len)
    {
        /*@ loop invariant 0 <= i <= pIp->len;
            loop invariant \forall integer j; 0 <= j < i ==> pIp->data[j] == ADDR_READ(pIp->addr);
            loop assigns i, pIp->data[0 .. pIp->len - 1];
            loop variant pIp->len - i;
        */
        for (i = 0; i < pIp->len; i++)
        {
            pIp->data[i] = ADDR_READ(pIp->addr);
        }

        pIp->bSucc = 1;
    }

    *(pIp->ret) = pIp->bSucc;
}
