
#include "SoftFaultJudgeSP.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mDSSData) && \valid(&pIp->mFWarning);
  ensures pIp->mDSSData.flgSP == 0 ==> pIp->mFWarning.countSPLost == \old(pIp->mFWarning.countSPLost) + 1;
  ensures pIp->mDSSData.flgSP == 0 ==> pIp->mFWarning.countSPSeen == 0;
  ensures pIp->mDSSData.flgSP != 0 && \old(pIp->mFWarning.countSPLost) != 0 ==> pIp->mFWarning.countSPSeen == \old(pIp->mFWarning.countSPSeen) + 1;
  ensures pIp->mDSSData.flgSP != 0 && \old(pIp->mFWarning.countSPSeen) > 2 ==> pIp->mFWarning.countSPLost == 0;
  ensures pIp->mDSSData.flgSP != 0 && \old(pIp->mFWarning.countSPSeen) > 2 ==> pIp->mFWarning.countSPSeen == 0;
  ensures pIp->mFWarning.countSPLost > 33750 ==> pIp->mFWarning.Wsp == TRUE;
  ensures pIp->mFWarning.countSPLost > 33750 ==> pIp->mFWarning.countSPLost == 0;
  ensures pIp->mFWarning.countSPLost > 33750 ==> pIp->mFWarning.countSPset == 0;
  assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset;
*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    if (pIp->mDSSData.flgSP == 0)
    {
        pIp->mFWarning.countSPLost++;
        pIp->mFWarning.countSPSeen = 0;
    }
    else
    {
        if (pIp->mFWarning.countSPLost != 0)
        {
            pIp->mFWarning.countSPSeen++;
        }

        if (pIp->mFWarning.countSPSeen > 2)
        {
            pIp->mFWarning.countSPLost = 0;
            pIp->mFWarning.countSPSeen = 0;
        }
    }

    if (pIp->mFWarning.countSPLost > 33750)
    {
        pIp->mFWarning.Wsp = TRUE;
        pIp->mFWarning.countSPLost = 0;
        pIp->mFWarning.countSPset = 0;
    }

    return;
}
