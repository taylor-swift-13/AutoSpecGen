
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mAttitude.rate + (0..2));
  ensures \forall int i; 0 <= i < 3 ==> pIp->mAttitude.rate[i] == \old(pIp->mAttitude.rate[i]);
  assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav, pIp->nouse;
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@ 
      assigns TripleFabsMax_ret; 
      ensures TripleFabsMax_ret == \old(TripleFabsMax_ret);
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    if (fabsmax > 2.0f)
    {
        pIp -> mFWarning.countAV++;

        /*@ 
          ensures pIp->mFWarning.countAV <= 301; 
          assigns pIp->mFWarning.Wav;
        */
        if (pIp -> mFWarning.countAV > 300)
        {
            pIp -> mFWarning.Wav = TRUE;
        }
    }
    else if (pIp -> mFWarning.countAV > 0)
    {
        pIp -> mFWarning.countAV--;
    }
    else
    {
        /*@ 
          assigns pIp->nouse; 
          ensures pIp->nouse == \old(pIp->nouse);
        */
        pIp -> nouse = pIp -> nouse;
    }

    return;
}
