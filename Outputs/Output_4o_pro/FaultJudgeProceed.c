
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mFWarning);
  ensures \true;
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@ assert \valid(pIp); */
    /*@ assert \valid(&pIp->mFWarning); */

    if ((pIp->mFWarning.CWsp == TRUE) && (pIp->mFWarning.Wsp == FALSE))
    {
        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);
    }

    if ((pIp->mFWarning.CWsp == TRUE) && (pIp->mFWarning.Wsp == TRUE))
    {
        IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
        IPCALL(ipSoftFaultProceedSP);
    }

    IPCREATE(NoctrlJudge, ipNoctrlJudge);
    IPCALL(ipNoctrlJudge);

    return;
}