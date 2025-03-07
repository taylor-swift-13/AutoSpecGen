
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mFWarning);
  requires \valid(pIp->mController + (0..2));
  ensures \old(pIp->mFWarning.countSPset) + 1 == pIp->mFWarning.countSPset;
  assigns pIp->mFWarning.countSPset;
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    pIp -> mFWarning.countSPset++ ;

    /*@ loop invariant pIp->mFWarning.countSPset >= 0;
        loop assigns pIp->mFWarning.countSPset;
        loop variant 10 - pIp->mFWarning.countSPset;
    */
    switch (pIp -> mFWarning.countSPset)
    {
        case 5:
            /*@ ensures pIp->mFWarning.countSPset == 5; */
            IPCREATE(SwitchSS, ipSwitchSS);
            IPCALL(ipSwitchSS);
            break ;

        case 10:
            /*@ ensures pIp->mFWarning.CWsp == FALSE; */
            pIp -> mFWarning.CWsp = FALSE ;
            /*@ ensures pIp->mFWarning.CWtf == FALSE; */
            pIp -> mFWarning.CWtf = FALSE ;
            /*@ ensures pIp->mFWarning.countSPset == 0; */
            pIp -> mFWarning.countSPset = 0 ;
            /*@ ensures pIp->mFWarning.Wsp == FALSE; */
            pIp -> mFWarning.Wsp = FALSE ;

            TR32_FLGMODE_VALUE(SAM_DAMP) ;
            TR32_BIAS_WXRO_VALUE(0.0f) ;
            TR32_BIAS_WYPI_VALUE(0.0f) ;
            /*@ ensures pIp->mController[0].Up == 0.0f; */
            pIp -> mController[0].Up = 0.0f ;
            /*@ ensures pIp->mController[1].Up == 0.0f; */
            pIp -> mController[1].Up = 0.0f ;
            /*@ ensures pIp->mController[2].Up == 0.0f; */
            pIp -> mController[2].Up = 0.0f ;

            /*@ ensures pIp->countMode == 0; */
            pIp -> countMode = 0 ;
            /*@ ensures pIp->countPublic == 0; */
            pIp -> countPublic = 0 ;
            break ;

        default:
            break ;
    }

    return ;
}
