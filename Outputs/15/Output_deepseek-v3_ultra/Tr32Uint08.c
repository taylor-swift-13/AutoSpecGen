
#include "Tr32Uint08.h"

/*@ axiomatic BitwiseOperations {
      logic integer bitwise_and(integer a, integer b) = a & b;
      logic integer bitwise_or(integer a, integer b) = a | b;
    }
*/

/*@
  requires \valid(pIp);
  requires \valid(pIp->pA) && \valid(pIp->pB) && \valid(pIp->pC) && \valid(pIp->ret);
  assigns *(pIp->pA), *(pIp->pB), *(pIp->pC), pIp->uiresult, *(pIp->ret);
  ensures *(pIp->ret) == pIp->uiresult;
  ensures (*(pIp->pA) == *(pIp->pB) && *(pIp->pA) == *(pIp->pC)) ==> 
          (pIp->uiresult == *(pIp->pA));
  ensures (*(pIp->pA) != *(pIp->pB) || *(pIp->pA) != *(pIp->pC)) ==> 
          (pIp->uiresult == bitwise_or(bitwise_and(*(pIp->pA), *(pIp->pB)), 
                                      bitwise_or(bitwise_and(*(pIp->pA), *(pIp->pC)), 
                                                 bitwise_and(*(pIp->pB), *(pIp->pC)))));
*/
void Tr32Uint08Fun(Tr32Uint08 *pIp)
{
    unint08 uitemp1;
    unint08 uitemp2;
    unint08 uitemp3;

    /*@ assert \valid(pIp->pA) && \valid(pIp->pB) && \valid(pIp->pC); */

    if ((*(pIp->pA) == *(pIp->pB)) && (*(pIp->pA) == *(pIp->pC)))
    {
        pIp->uiresult = *(pIp->pA);
    }
    else
    {
        uitemp1 = *(pIp->pA) & *(pIp->pB);
        uitemp2 = *(pIp->pA) & *(pIp->pC);
        uitemp3 = *(pIp->pB) & *(pIp->pC);
        pIp->uiresult = uitemp1 | uitemp2 | uitemp3;

        *(pIp->pA) = pIp->uiresult;
        *(pIp->pB) = pIp->uiresult;
        *(pIp->pC) = pIp->uiresult;
    }

    *(pIp->ret) = pIp->uiresult;
}
