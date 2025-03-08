
#include "PseudoRateModulator.h"

/*@ axiomatic FloatOperations {
      logic real weighted_sum(real r, real weight1, real weight2) = weight1 * r + weight2;
    }
*/

/*@
  requires \valid(pIp) && \valid(pIp->pModulator);
  assigns pIp->pModulator->Yp, pIp->pModulator->Yn, pIp->pModulator->r;
  ensures \old(pIp->pModulator->u) - \old(pIp->pModulator->r) > \old(pIp->h1) ==> 
          pIp->pModulator->Yp == 0x0 && pIp->pModulator->Yn == 0xF &&
          pIp->pModulator->r == weighted_sum(\old(pIp->pModulator->r), 0.9231, 0.07688);
  ensures \old(pIp->pModulator->u) - \old(pIp->pModulator->r) < -\old(pIp->h1) ==> 
          pIp->pModulator->Yp == 0xF && pIp->pModulator->Yn == 0x0 &&
          pIp->pModulator->r == weighted_sum(\old(pIp->pModulator->r), 0.9231, -0.07688);
  ensures \old(pIp->pModulator->u) - \old(pIp->pModulator->r) >= -\old(pIp->h1) && 
          \old(pIp->pModulator->u) - \old(pIp->pModulator->r) <= \old(pIp->h1) ==> 
          pIp->pModulator->Yp == 0x0 && pIp->pModulator->Yn == 0x0 &&
          pIp->pModulator->r == weighted_sum(\old(pIp->pModulator->r), 0.9231, 0.0);
*/
void PseudoRateModulatorFun(PseudoRateModulator *pIp)
{
    if ((pIp->pModulator->u - pIp->pModulator->r) > pIp->h1)
    {
        pIp->pModulator->Yp = 0x0;
        pIp->pModulator->Yn = 0xF;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r + 0.07688f;
    }
    else if ((pIp->pModulator->u - pIp->pModulator->r) < -pIp->h1)
    {
        pIp->pModulator->Yp = 0xF;
        pIp->pModulator->Yn = 0x0;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r - 0.07688f;
    }
    else
    {
        pIp->pModulator->Yp = 0x0;
        pIp->pModulator->Yn = 0x0;
        pIp->pModulator->r = 0.9231f * pIp->pModulator->r;
    }

    return;
}
