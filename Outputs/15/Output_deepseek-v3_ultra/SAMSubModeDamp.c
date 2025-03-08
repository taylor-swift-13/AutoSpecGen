
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->rate + (0..2));
  assigns pIp->countPublic, pIp->flgMode, pIp->countMode;
  ensures pIp->countPublic == \old(pIp->countPublic) + ((\old(pIp->rate[0]) < \old(pIp->max) && \old(pIp->rate[1]) < \old(pIp->max) && \old(pIp->rate[2]) < \old(pIp->max)) ? 1 : 0);
  ensures ((\old(pIp->countPublic) > 350) || (\old(pIp->countMode) > 1000)) ==> (pIp->flgMode == SAM_PITCH && pIp->countMode == 0 && pIp->countPublic == 0);
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ assert \valid(pIp->rate + (0..2)); */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 = pIp->rate[0], .fy2 = pIp->rate[1], .fz3 = pIp->rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ assert \valid(pIp); */
    if (fabsmax < pIp->max)
    {
        pIp->countPublic++;
    }

    /*@ assert \valid(pIp); */
    if ((pIp->countPublic > 350) || (pIp->countMode > 1000))
    {
        pIp->flgMode = SAM_PITCH;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WYPI_VALUE(-0.5f);

        pIp->countMode = 0;
        pIp->countPublic = 0;
    }

    return;
}
