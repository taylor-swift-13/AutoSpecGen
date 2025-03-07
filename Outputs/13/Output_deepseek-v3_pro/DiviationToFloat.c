
#include "DiviationToFloat.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *pIp->ret == pIp->fresult;
  assigns pIp->fresult, *pIp->ret;
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ assert \valid(pIp) && \valid(pIp->ret); */

    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;

    /*@ assert *pIp->ret == pIp->fresult; */
}
