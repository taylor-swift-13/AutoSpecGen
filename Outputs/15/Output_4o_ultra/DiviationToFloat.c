
#include "DiviationToFloat.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->ret);
ensures *(pIp->ret) == pIp->fresult;
assigns pIp->fresult, *(pIp->ret);
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    /*@ 
    requires \valid(pIp);
    requires \valid(pIp->ret);
    assigns pIp->fresult;
    ensures pIp->fresult == ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;
    */
    pIp->fresult = ((siint16)((pIp->input & pIp->mask) - pIp->offset)) * pIp->LSB;

    /*@ 
    requires \valid(pIp->ret);
    assigns *(pIp->ret);
    ensures *(pIp->ret) == pIp->fresult;
    */
    *(pIp->ret) = pIp->fresult;
}
