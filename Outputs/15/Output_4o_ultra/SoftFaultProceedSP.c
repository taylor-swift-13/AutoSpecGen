
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->mFWarning.countSPset == \old(pIp->mFWarning.countSPset) + 1;
  ensures \old(pIp->mFWarning.countSPset) != 10 ==> \unchanged(pIp->mFWarning.CWsp) && \unchanged(pIp->mFWarning.CWtf) && \unchanged(pIp->mFWarning.Wsp);
  ensures \old(pIp->mFWarning.countSPset) == 10 ==> pIp->mFWarning.CWsp == \false && pIp->mFWarning.CWtf == \false && pIp->mFWarning.countSPset == 0 && pIp->mFWarning.Wsp == \false;
  ensures \old(pIp->mFWarning.countSPset) == 10 ==> pIp->mController[0].Up == 0.0f && pIp->mController[1].Up == 0.0f && pIp->mController[2].Up == 0.0f;
  ensures \old(pIp->mFWarning.countSPset) == 10 ==> pIp->countMode == 0 && pIp->countPublic == 0;
  assigns pIp->mFWarning.countSPset;
  assigns pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, pIp->mFWarning.Wsp;
  assigns pIp->mController[0].Up, pIp->mController[1].Up, pIp->mController[2].Up;
  assigns pIp->countMode, pIp->countPublic;
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    /*@ assert \valid(pIp); */
    pIp->mFWarning.countSPset++;

    switch (pIp->mFWarning.countSPset)
    {
        case 5:
            IPCREATE(SwitchSS, ipSwitchSS);
            IPCALL(ipSwitchSS);
            break;

        case 10:
            pIp->mFWarning.CWsp = FALSE;
            pIp->mFWarning.CWtf = FALSE;
            pIp->mFWarning.countSPset = 0;
            pIp->mFWarning.Wsp = FALSE;

            TR32_FLGMODE_VALUE(SAM_DAMP);
            TR32_BIAS_WXRO_VALUE(0.0f);
            TR32_BIAS_WYPI_VALUE(0.0f);
            pIp->mController[0].Up = 0.0f;
            pIp->mController[1].Up = 0.0f;
            pIp->mController[2].Up = 0.0f;

            pIp->countMode = 0;
            pIp->countPublic = 0;
            break;

        default:
            break;
    }

    return;
}
