
#include "LimitFloat32.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->fbound >= 0; // Assuming fbound is a non-negative value
  requires \valid(pIp->fin);
  ensures *pIp->ret == (pIp->fin > pIp->fbound ? pIp->fbound : 
                        (pIp->fin < -pIp->fbound ? -pIp->fbound : pIp->fin));
  assigns pIp->fvalue, *pIp->ret;
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    if (pIp -> fin > pIp -> fbound)
    {
        pIp -> fvalue = pIp -> fbound ;
    }
    else if (pIp -> fin < -pIp -> fbound)
    {
        pIp -> fvalue = -pIp -> fbound ;
    }
    else
    {
        pIp -> fvalue = pIp -> fin ;
    }

    *(pIp -> ret) = pIp -> fvalue ;
}
