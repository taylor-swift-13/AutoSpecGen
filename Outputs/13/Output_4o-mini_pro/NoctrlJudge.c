
#include "TripleFabsMax.h"
#include "NoctrlJudge.h"

/*@ 
  requires pIp != NULL;
  requires \valid(pIp);
  requires \valid(pIp->mAttitude.rate);
  requires \valid(pIp->mFWarning);
  ensures pIp->mFWarning.countAV >= 0;
*/
void NoctrlJudgeFun(NoctrlJudge *pIp)
{
    float32 fabsmax;
    float32 TripleFabsMax_ret;

    /*@
      requires \valid(pIp->mAttitude.rate);
      assigns TripleFabsMax_ret;
      ensures fabsmax == TripleFabsMax_ret;
    */
    IPCREATE(TripleFabsMax, ipTripleFabsMax, .fx1 =  pIp->mAttitude.rate[0], .fy2 =  pIp->mAttitude.rate[1], .fz3 =  pIp->mAttitude.rate[2], .ret = &(TripleFabsMax_ret));
    IPCALL(ipTripleFabsMax);

    fabsmax = TripleFabsMax_ret;

    /*@
      loop invariant pIp->mFWarning.countAV >= 0;
      loop assigns pIp->mFWarning.countAV, pIp->mFWarning.Wav;
      loop variant 301 - pIp->mFWarning.countAV;
    */
    if (fabsmax > 2.0f)
    {
        pIp -> mFWarning.countAV++;

        /*@
          ensures pIp->mFWarning.countAV <= 301;
          ensures pIp->mFWarning.Wav == TRUE ==> pIp->mFWarning.countAV > 300;
        */
        if (pIp -> mFWarning.countAV > 300)
        {
            pIp -> mFWarning.Wav = TRUE;
        }
    }
    else if(pIp -> mFWarning.countAV > 0)
    {
        pIp -> mFWarning.countAV--;
    }
    else
    {
        /*@
          assigns pIp->nouse;
        */
        pIp -> nouse = pIp -> nouse;
    }

    return;
}
