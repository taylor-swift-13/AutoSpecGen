
#include "ModPNHP.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  requires \valid(pIp->halfperiod);
  ensures pIp->npp2 == pIp->x - (pIp->x + pIp->halfperiod) / (2.0f * pIp->halfperiod) * (2.0f * pIp->halfperiod);
  ensures *pIp->ret == pIp->npp2;
  assigns pIp->npp2, *pIp->ret;
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    period = 2.0f * pIp -> halfperiod;

    pIp -> npp2 = pIp -> x - (pIp -> x + pIp -> halfperiod) / period * period;

    *(pIp -> ret) = pIp -> npp2;
}
