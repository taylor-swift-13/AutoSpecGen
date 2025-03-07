
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@
  requires \valid(pIp);
  assigns pIp->mFWarning.CWsp, pIp->mFWarning.Wsp;
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@
      assert \valid(pIp);
    */

    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {
        /*@
          assigns pIp->mFWarning.CWsp, pIp->mFWarning.Wsp;
        */
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);
    }

    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {
        /*@
          assigns pIp->mFWarning.CWsp, pIp->mFWarning.Wsp;
        */
        IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
        IPCALL(ipSoftFaultProceedSP);
    }

    /*@
      assigns pIp->mFWarning.CWsp, pIp->mFWarning.Wsp;
    */
    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    IPCALL(ipNoctrlJudge);

    return;
}
