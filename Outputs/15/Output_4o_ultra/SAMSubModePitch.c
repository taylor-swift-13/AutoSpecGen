
#include "SAMSubModePitch.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pSDS);
  requires \valid(pIp->pCtrl + (0..2));
  assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
  ensures pIp->countPublic == 0 || pIp->countPublic <= 17;
  ensures pIp->countMode == 0 || pIp->countMode <= 5626;
*/
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{
    float32 pirawtmp;

    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->pSDS);
      assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
      ensures pIp->countPublic == 0 || pIp->countPublic <= 17;
      ensures pIp->countMode == 0 || pIp->countMode <= 5626;
    */
    if (pIp->pSDS->flgSP == 1)
    {
        pirawtmp = fabs(pIp->pSDS->piyaw);

        if (pirawtmp > 1.0f)
        {
            pIp->countPublic++;

            if (pIp->countPublic > 16)
            {
                TR32_BIAS_WYPI_VALUE(0.0f);

                pIp->flgMode = SAM_CRUISE;
                TR32_FLGMODE_VALUE(pIp->flgMode);
                pIp->countMode = 0;
                pIp->countPublic = 0;
            }
            else
            {
                pIp->pCtrl[0].Up = 0.0f;
                pIp->pCtrl[1].Up = 0.0f;
                pIp->pCtrl[2].Up = 0.0f;
            }
        }
    }
    else
    {
        pIp->countPublic = 0;
    }

    if (pIp->countMode > 5625)
    {
        pIp->flgMode = SAM_ROLL;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WXRO_VALUE(0.5f);
        TR32_BIAS_WYPI_VALUE(0.0f);

        pIp->countMode = 0;
        pIp->countPublic = 0;
    }

    return;
}
