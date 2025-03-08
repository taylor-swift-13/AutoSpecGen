
#include "ModPNHP.h"

/*@ axiomatic FloatOperations {
      logic real float32_to_real(float32 x) = x;
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    ensures *pIp->ret == \old(pIp->x) - (\old(pIp->x) + \old(pIp->halfperiod)) / (2.0f * \old(pIp->halfperiod)) * (2.0f * \old(pIp->halfperiod));
    assigns *pIp->ret, pIp->npp2;
*/
void ModPNHPFun(ModPNHP *pIp)
{
    float32 period;

    /*@ assert \valid(pIp) && \valid(pIp->ret); */
    period = 2.0f * pIp->halfperiod;

    /*@ assert period == 2.0f * \at(pIp->halfperiod, Pre); */
    pIp->npp2 = pIp->x - (pIp->x + pIp->halfperiod) / period * period;

    /*@ assert pIp->npp2 == \at(pIp->x, Pre) - (\at(pIp->x, Pre) + \at(pIp->halfperiod, Pre)) / (2.0f * \at(pIp->halfperiod, Pre)) * (2.0f * \at(pIp->halfperiod, Pre)); */
    *(pIp->ret) = pIp->npp2;
}
