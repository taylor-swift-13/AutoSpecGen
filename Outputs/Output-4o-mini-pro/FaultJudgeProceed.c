
#include "SoftFaultProceedSP.h"
#include "NoctrlJudge.h"
#include "SoftFaultJudgeSP.h"
#include "FaultJudgeProceed.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp->mFWarning);
  assigns \nothing;
*/
void FaultJudgeProceedFun(FaultJudgeProceed *pIp)
{
    /*@
      if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == FALSE)) 
      {
          /*@ assert pIp -> mFWarning.CWsp == TRUE; */
          /*@ assert pIp -> mFWarning.Wsp == FALSE; */
          IPCREATE(SoftFaultJudgeSP, ipSoftFaultJudgeSP);
          IPCALL(ipSoftFaultJudgeSP);
      }
    */

    /*@
      if ((pIp -> mFWarning.CWsp == TRUE) && (pIp -> mFWarning.Wsp == TRUE)) 
      {
          /*@ assert pIp -> mFWarning.CWsp == TRUE; */
          /*@ assert pIp -> mFWarning.Wsp == TRUE; */
          IPCREATE(SoftFaultProceedSP, ipSoftFaultProceedSP);
          IPCALL(ipSoftFaultProceedSP);
      }
    */

    /*@
      assigns \nothing;
      IPCREATE(NoctrlJudge, ipNoctrlJudge);
      IPCALL(ipNoctrlJudge);
    */

    return;
}
