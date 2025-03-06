
#include "DiviationToFloat.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->input);
  requires \valid(pIp->mask);
  requires \valid(pIp->offset);
  requires \valid(pIp->LSB);
  ensures *pIp->ret == pIp->fresult;
  assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ 
      ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB);
      assigns pIp->fresult;
    */
    pIp -> fresult = ((siint16)((pIp -> input & pIp -> mask) - pIp -> offset)) * pIp -> LSB ;

    *(pIp -> ret) = pIp -> fresult;
}
