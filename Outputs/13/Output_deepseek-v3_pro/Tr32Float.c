
#include "Tr32Float.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->pA) && \valid(pIp->pB) && \valid(pIp->pC) && \valid(pIp->ret);
  assigns *(pIp->pA), *(pIp->pB), *(pIp->pC), *(pIp->ret), pIp->ui2f.ui32;
  ensures *(pIp->pA) == pIp->ui2f.flt32;
  ensures *(pIp->pB) == pIp->ui2f.flt32;
  ensures *(pIp->pC) == pIp->ui2f.flt32;
  ensures *(pIp->ret) == pIp->ui2f.flt32;
*/
void Tr32FloatFun(Tr32Float *pIp) {
    UDTConvert f2ui1;
    UDTConvert f2ui2;
    UDTConvert f2ui3;

    unint32 uitemp1;
    unint32 uitemp2;
    unint32 uitemp3;

    f2ui1.flt32 = *(pIp->pA);
    f2ui2.flt32 = *(pIp->pB);
    f2ui3.flt32 = *(pIp->pC);

    uitemp1 = f2ui1.ui32 & f2ui2.ui32;
    uitemp2 = f2ui1.ui32 & f2ui3.ui32;
    uitemp3 = f2ui2.ui32 & f2ui3.ui32;
    pIp->ui2f.ui32 = uitemp1 | uitemp2 | uitemp3;

    *(pIp->pA) = pIp->ui2f.flt32;
    *(pIp->pB) = pIp->ui2f.flt32;
    *(pIp->pC) = pIp->ui2f.flt32;

    *(pIp->ret) = pIp->ui2f.flt32;
}
