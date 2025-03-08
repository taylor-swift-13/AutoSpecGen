
#include "TripleFabsMax.h"

/*@ axiomatic FloatProperties {
      logic real fabs(real x) = x < 0.0 ? -x : x;
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->ret);
    assigns pIp->tmax, *(pIp->ret);
    ensures *(pIp->ret) == \max(fabs(\at(pIp->fx1, Pre)), \max(fabs(\at(pIp->fy2, Pre)), fabs(\at(pIp->fz3, Pre))));
    ensures pIp->tmax == \max(fabs(\at(pIp->fx1, Pre)), \max(fabs(\at(pIp->fy2, Pre)), fabs(\at(pIp->fz3, Pre))));
*/
void TripleFabsMaxFun(TripleFabsMax *pIp)
{
    float32 fabsfx1;
    float32 fabsfy2;
    float32 fabsfz3;

    fabsfx1 = pIp->fx1;
    fabsfy2 = pIp->fy2;
    fabsfz3 = pIp->fz3;

    /*@ assert fabsfx1 == fabs(pIp->fx1); */
    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    /*@ assert fabsfy2 == fabs(pIp->fy2); */
    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    /*@ assert fabsfz3 == fabs(pIp->fz3); */
    if (pIp->fz3 < 0.0f)
    {
        fabsfz3 = -pIp->fz3;
    }

    if (fabsfx1 > fabsfy2)
    {
        pIp->tmax = fabsfx1;
    }
    else
    {
        pIp->tmax = fabsfy2;
    }

    if (fabsfz3 > pIp->tmax)
    {
        pIp->tmax = fabsfz3;
    }

    *(pIp->ret) = pIp->tmax;
}
