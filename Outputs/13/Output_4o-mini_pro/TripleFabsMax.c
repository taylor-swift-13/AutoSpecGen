
#include "TripleFabsMax.h"

/*@ 
    requires \valid(pIp);
    requires \valid(pIp->ret);
    ensures \forall float32 x; x == pIp->fx1 || x == pIp->fy2 || x == pIp->fz3 ==> x >= 0.0f;
    ensures pIp->tmax == \max(\max(\old(fabsfx1), \old(fabsfy2)), \old(fabsfz3));
    assigns pIp->tmax, *(pIp->ret);
*/
void TripleFabsMaxFun(TripleFabsMax *pIp)
{
    float32 fabsfx1;
    float32 fabsfy2;
    float32 fabsfz3;

    fabsfx1 = pIp->fx1;
    fabsfy2 = pIp->fy2;
    fabsfz3 = pIp->fz3;

    /*@ 
        loop invariant fabsfx1 == pIp->fx1 || fabsfx1 == -pIp->fx1;
        loop invariant fabsfy2 == pIp->fy2 || fabsfy2 == -pIp->fy2;
        loop invariant fabsfz3 == pIp->fz3 || fabsfz3 == -pIp->fz3;
        loop assigns fabsfx1, fabsfy2, fabsfz3;
    */
    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    if (pIp->fz3 < 0.0f)
    {
        fabsfz3 = -pIp->fz3;
    }

    /*@ assert fabsfx1 >= 0.0f; */
    /*@ assert fabsfy2 >= 0.0f; */
    /*@ assert fabsfz3 >= 0.0f; */

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
