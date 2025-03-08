
#include "LimitFloat32.h"

/*@ axiomatic FloatLimits {
      logic real limit(real fin, real fbound) =
        fin > fbound ? fbound : (fin < -fbound ? -fbound : fin);
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    ensures *pIp->ret == limit(pIp->fin, pIp->fbound);
    ensures pIp->fvalue == limit(pIp->fin, pIp->fbound);
    assigns pIp->fvalue, *pIp->ret;
*/
void LimitFloat32Fun(LimitFloat32 *pIp)
{
    /*@ assert \valid(pIp) && \valid(pIp->ret); */

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
