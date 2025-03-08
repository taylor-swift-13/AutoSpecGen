
#include "DiviationToFloat.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
  ensures *(pIp->ret) == \old(pIp->fresult);
  assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;
}
