#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"
void FaultJudgeProceedFun(void *p)
{
    FaultJudgeProceed *pIp = (FaultJudgeProceed*)p;

	if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE))
    {

        IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
        IPCALL(ipSoftFaultJudgeSP);

    }

    if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE))
    {

    	IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
    	IPCALL(ipSoftFaultProceedSP);

    }

        IPCREATE(NoctrlJudge, ipNoctrlJudge);
        IPCALL(ipNoctrlJudge);

	return ;
}