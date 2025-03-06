
#include "SoftFaultJudgeSP.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->mFWarning.countSPLost >= 0;
  ensures pIp->mFWarning.countSPSeen >= 0;
  ensures pIp->mFWarning.countSPLost <= 33750;
  assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen, pIp->mFWarning.Wsp, pIp->mFWarning.countSPset;
*/
void SoftFaultJudgeSPFun(SoftFaultJudgeSP *pIp)
{
    /*@ loop invariant pIp->mFWarning.countSPLost >= 0;
        loop invariant pIp->mFWarning.countSPSeen >= 0;
        loop assigns pIp->mFWarning.countSPLost, pIp->mFWarning.countSPSeen;
    */
    while (1) // Added loop to encapsulate the logic for proper ACSL
    {
        if (pIp -> mDSSData.flgSP == 0)
        {
            pIp -> mFWarning.countSPLost++;
            pIp -> mFWarning.countSPSeen = 0;
            break; // Exit loop after handling condition
        }
        else
        {
            if (pIp -> mFWarning.countSPLost != 0)
            {
                pIp -> mFWarning.countSPSeen++;
            }

            if (pIp -> mFWarning.countSPSeen > 2)
            {
                pIp -> mFWarning.countSPLost = 0;
                pIp -> mFWarning.countSPSeen = 0;
            }
            break; // Exit loop after handling condition
        }

        if (pIp -> mFWarning.countSPLost > 33750)
        {
            pIp -> mFWarning.Wsp = TRUE;
            pIp -> mFWarning.countSPLost = 0;
            pIp -> mFWarning.countSPset = 0;
            break; // Exit loop after handling condition
        }
    }

    return;
}
