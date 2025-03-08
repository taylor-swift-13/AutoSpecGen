
#include "TripleFabsMax.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures \valid(pIp->ret);
  ensures *pIp->ret == (\old(pIp->fx1) < 0.0f ? -\old(pIp->fx1) : \old(pIp->fx1)) >= 
                       (\old(pIp->fy2) < 0.0f ? -\old(pIp->fy2) : \old(pIp->fy2)) ? 
                       (\old(pIp->fx1) < 0.0f ? -\old(pIp->fx1) : \old(pIp->fx1)) : 
                       (\old(pIp->fy2) < 0.0f ? -\old(pIp->fy2) : \old(pIp->fy2)) >= 
                       (\old(pIp->fz3) < 0.0f ? -\old(pIp->fz3) : \old(pIp->fz3)) ? 
                       (\old(pIp->fy2) < 0.0f ? -\old(pIp->fy2) : \old(pIp->fy2)) : 
                       (\old(pIp->fz3) < 0.0f ? -\old(pIp->fz3) : \old(pIp->fz3));
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

    /*@ requires pIp->fx1 < 0.0f;
        assigns fabsfx1;
        ensures fabsfx1 == -pIp->fx1;
    */
    if (pIp->fx1 < 0.0f)
    {
        fabsfx1 = -pIp->fx1;
    }

    /*@ requires pIp->fy2 < 0.0f;
        assigns fabsfy2;
        ensures fabsfy2 == -pIp->fy2;
    */
    if (pIp->fy2 < 0.0f)
    {
        fabsfy2 = -pIp->fy2;
    }

    /*@ requires pIp->fz3 < 0.0f;
        assigns fabsfz3;
        ensures fabsfz3 == -pIp->fz3;
    */
    if (pIp->fz3 < 0.0f)
    {
        fabsfz3 = -pIp->fz3;
    }

    /*@ ensures fabsfx1 >= 0.0f && fabsfy2 >= 0.0f && fabsfz3 >= 0.0f;
        assigns pIp->tmax;
    */
    if (fabsfx1 > fabsfy2)
    {
        pIp->tmax = fabsfx1;
    }
    else
    {
        pIp->tmax = fabsfy2;
    }

    /*@ ensures pIp->tmax >= 0.0f && fabsfz3 >= 0.0f;
        assigns pIp->tmax;
    */
    if (fabsfz3 > pIp->tmax)
    {
        pIp->tmax = fabsfz3;
    }

    *(pIp->ret) = pIp->tmax;
}
