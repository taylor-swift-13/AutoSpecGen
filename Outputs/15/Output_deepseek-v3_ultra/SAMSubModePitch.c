
#include "SAMSubModePitch.h"

/*@ axiomatic SAMSubModePitch {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pSDS);
    requires \valid(pIp->pCtrl + (0..2));
    assigns pIp->countPublic, pIp->flgMode, pIp->countMode, pIp->pCtrl[0..2].Up;
*/
void SAMSubModePitchFun(SAMSubModePitch *pIp)
{
    float32 pirawtmp;

    /*@ assert \valid(pIp->pSDS); */
    if ( pIp -> pSDS->flgSP == 1 )
    {
        pirawtmp =  fabs( pIp -> pSDS->piyaw );

        /*@ assert pirawtmp >= 0.0; */
        if ( pirawtmp > 1.0f )
        {
            pIp -> countPublic++;

            /*@ assert 0 <= pIp->countPublic <= 17; */
            if ( pIp -> countPublic > 16 )
            {
                TR32_BIAS_WYPI_VALUE( 0.0f );

                pIp->flgMode = SAM_CRUISE;
                TR32_FLGMODE_VALUE(pIp->flgMode);
                pIp -> countMode = 0;
                pIp -> countPublic = 0;
            }
            else
            {
                pIp -> pCtrl[0].Up = 0.0f;
                pIp -> pCtrl[1].Up = 0.0f;
                pIp -> pCtrl[2].Up = 0.0f;
            }
        }
    }
    else
    {
        pIp -> countPublic = 0;
    }

    /*@ assert \valid(pIp); */
    if (pIp -> countMode > 5625)
    {
        pIp->flgMode = SAM_ROLL;
        TR32_FLGMODE_VALUE(pIp->flgMode);
        TR32_BIAS_WXRO_VALUE(0.5f);
        TR32_BIAS_WYPI_VALUE(0.0f);

        pIp -> countMode = 0;
        pIp -> countPublic = 0;
    }

    return;
}
