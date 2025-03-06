
#include "LimitFloat32.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires pIp->fbound >= 0.0f;
  ensures (*pIp->ret) == pIp->fvalue;
  ensures (pIp->fin > \old(pIp->fbound)) ==> (pIp->fvalue == \old(pIp->fbound));
  ensures (pIp->fin < -\old(pIp->fbound)) ==> (pIp->fvalue == -\old(pIp->fbound));
  ensures (pIp->fin >= -\old(pIp->fbound) && pIp->fin <= \old(pIp->fbound)) ==> (pIp->fvalue == \old(pIp->fin));
  assigns pIp->fvalue, *(pIp->ret);
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    if (pIp->fin > pIp->fbound)
    {
        pIp->fvalue = pIp->fbound;
    }
    else if (pIp->fin < -pIp->fbound)
    {
        pIp->fvalue = -pIp->fbound;
    }
    else
    {
        pIp->fvalue = pIp->fin;
    }

    *(pIp->ret) = pIp->fvalue;
}
