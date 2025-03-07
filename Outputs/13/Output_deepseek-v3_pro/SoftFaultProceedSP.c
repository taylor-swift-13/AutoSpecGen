
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@
  requires \valid(pIp);
  assigns pIp->mFWarning.countSPset;
  assigns pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, pIp->mFWarning.Wsp;
  assigns pIp->mController[0].Up, pIp->mController[1].Up, pIp->mController[2].Up;
  assigns pIp->countMode, pIp->countPublic;
  behavior case_5:
    assumes pIp->mFWarning.countSPset == 5;
    assigns \nothing; // No additional assignments in this case
  behavior case_10:
    assumes pIp->mFWarning.countSPset == 10;
    ensures pIp->mFWarning.CWsp == \false;
    ensures pIp->mFWarning.CWtf == \false;
    ensures pIp->mFWarning.countSPset == 0;
    ensures pIp->mFWarning.Wsp == \false;
    ensures pIp->mController[0].Up == 0.0f;
    ensures pIp->mController[1].Up == 0.0f;
    ensures pIp->mController[2].Up == 0.0f;
    ensures pIp->countMode == 0;
    ensures pIp->countPublic == 0;
  behavior default_case:
    assumes pIp->mFWarning.countSPset != 5 && pIp->mFWarning.countSPset != 10;
    assigns \nothing; // No additional assignments in this case
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
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
