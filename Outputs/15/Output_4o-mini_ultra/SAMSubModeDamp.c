
#include "TripleFabsMax.h"
#include "SAMSubModeDamp.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->rate + (0..2));
  ensures pIp->countPublic == \old(pIp->countPublic) + (TripleFabsMax_ret < pIp->max ? 1 : 0);
  assigns pIp->countPublic, pIp->countMode, pIp->flgMode;
*/
void SAMSubModeDampFun(SAMSubModeDamp *pIp)
{
    float32 fabsmax;

    float32 TripleFabsMax_ret;
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->rate[0], .fy2 =  pIp->rate[1], .fz3 =  pIp->rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@ assert pIp->countPublic >= 0; */
    if (fabsmax < pIp->max)
    {
        pIp->countPublic++;
    }

    /*@ assert pIp->countPublic >= 0 && pIp->countMode >= 0; */
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
