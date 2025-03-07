
#include "SAMSubModePitch.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp->pSDS);
  requires \valid(pIp->pCtrl + (0..2));
  ensures \old(pIp->countPublic) <= pIp->countPublic <= 16;
  ensures \forall int i; 0 <= i <= 2 ==> pIp->pCtrl[i].Up == 0.0f ==> \old(pIp->countPublic) > 16 ==> pIp->flgMode == SAM_CRUISE;
  ensures pIp->countMode >= 0;
  assigns pIp->countPublic, pIp->countMode, pIp->flgMode, pIp->pCtrl[0].Up, pIp->pCtrl[1].Up, pIp->pCtrl[2].Up;
*/
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{
    float32 pirawtmp;

    /*@
      loop invariant pIp->pSDS->flgSP == 1 ==> pirawtmp == fabs(pIp->pSDS->piyaw);
      loop assigns pirawtmp;
    */
    if (pIp->pSDS->flgSP == 1)
    {
        pirawtmp = fabs(pIp->pSDS->piyaw);

        /*@
          loop invariant pirawtmp > 1.0f ==> pIp->countPublic <= 16;
          loop assigns pIp->countPublic;
        */
        if (pirawtmp > 1.0f)
        {
            pIp->countPublic++;

            /*@
              ensures pIp->countPublic <= 16;
              assigns pIp->countPublic, pIp->flgMode, pIp->countMode;
            */
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

    /*@
      loop invariant pIp->countMode > 5625 ==> pIp->flgMode == SAM_ROLL;
      loop assigns pIp->flgMode, pIp->countMode, pIp->countPublic;
    */
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
