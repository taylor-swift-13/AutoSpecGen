
#include "DiviationToFloat.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->mask); // Assuming mask is a pointer
  requires \valid(pIp->offset); // Assuming offset is a pointer
  ensures \valid(pIp->ret);
  ensures *pIp->ret == ((siint16)((pIp->input & *pIp->mask) - *pIp->offset)) * pIp->LSB; // Ensure clause updated to dereference mask and offset
*/
void DiviationToFloatFun(DiviationToFloat *pIp)
{
    pIp->fresult = ((siint16)((pIp->input & *pIp->mask) - *pIp->offset)) * pIp->LSB;

    *(pIp->ret) = pIp->fresult;
}
