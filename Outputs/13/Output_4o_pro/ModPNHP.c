
#include "ModPNHP.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *(pIp->ret) == pIp->npp2;
  ensures pIp->npp2 == pIp->x - ((pIp->x + pIp->halfperiod) - ((pIp->x + pIp->halfperiod) / (2.0f * pIp->halfperiod)) * (2.0f * pIp->halfperiod));
  assigns pIp->npp2;
  assigns *(pIp->ret);
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    period = 2.0f * pIp->halfperiod;

    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    *(pIp->ret) = pIp->npp2;
}
