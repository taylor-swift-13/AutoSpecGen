
#include "SwitchSS.h"
#include "SoftFaultProceedSP.h"

/*@ axiomatic Counter {
      logic integer sum(int* array, integer begin, integer end) reads array[begin .. (end-1)];
      axiom empty:
      \forall int* a, integer b, e; b >= e ==> sum(a,b,e) == 0;
      axiom range:
      \forall int* a, integer b, e; b < e ==> sum(a,b,e) == sum(a,b,e-1) + a[e-1];
   }
*/

/*@ requires \valid(pIp);
    assigns pIp->mFWarning.countSPset, pIp->mFWarning.CWsp, pIp->mFWarning.CWtf, 
            pIp->mFWarning.Wsp, pIp->mController[0..2].Up, pIp->countMode, pIp->countPublic;
    ensures pIp->mFWarning.countSPset == \old(pIp->mFWarning.countSPset) + 1 || 
            pIp->mFWarning.countSPset == 0;
*/
void SoftFaultProceedSPFun(SoftFaultProceedSP *pIp)
{
    /*@ assert \valid(pIp); */
    pIp->mFWarning.countSPset++;

    switch (pIp->mFWarning.countSPset)
    {
        case 5:
            /*@ assert pIp->mFWarning.countSPset == 5; */
            IPCREATE(SwitchSS, ipSwitchSS);
            /*@ assert \valid(ipSwitchSS); */
            IPCALL(ipSwitchSS);
            break;

        case 10:
            /*@ assert pIp->mFWarning.countSPset == 10; */
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
            /*@ assert pIp->mFWarning.countSPset != 5 && pIp->mFWarning.countSPset != 10; */
            break;
    }

    return;
}
