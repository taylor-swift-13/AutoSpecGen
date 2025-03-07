
#include "ModPNHP.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *pIp->ret == \old(pIp->x) - (\old(pIp->x) + \old(pIp->halfperiod)) / (2.0f * \old(pIp->halfperiod)) * (2.0f * \old(pIp->halfperiod));
  assigns pIp->npp2, *(pIp->ret);
*/
void ModPNHPFun(ModPNHP *pIp) {
    float32 period;

    period = 2.0f * pIp->halfperiod;

    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    *(pIp->ret) = pIp->npp2;
}
