
#include "ThrABAutoChoose.h"

/*@
  requires \valid(pIp);
  ensures pIp->mThrDistribute.stateFlag[0] == 1 && pIp->mThrDistribute.stateFlag[1] == 1 ==> pIp->mThrDistribute.flgABChoose == TBS_AB;
  ensures pIp->mThrDistribute.stateFlag[0] == 0 && pIp->mThrDistribute.stateFlag[1] == 1 ==> pIp->mThrDistribute.flgABChoose == TBS_B;
  ensures pIp->mThrDistribute.stateFlag[0] != 1 || pIp->mThrDistribute.stateFlag[1] != 1 ==> pIp->mThrDistribute.flgABChoose == TBS_A;
  assigns pIp->mThrDistribute.flgABChoose;
*/
void ThrABAutoChooseFun(ThrABAutoChoose *pIp)
{
    /*@ assert \valid(pIp); */
    /*@ assert \valid(&pIp->mThrDistribute.stateFlag[0]); */
    /*@ assert \valid(&pIp->mThrDistribute.stateFlag[1]); */
    /*@ assert \valid(&pIp->mThrDistribute.flgABChoose); */

    if ((pIp->mThrDistribute.stateFlag[0] = 1) &&
        (pIp->mThrDistribute.stateFlag[1] = 1))
    {
        pIp->mThrDistribute.flgABChoose = TBS_AB;
    }
    else if ((pIp->mThrDistribute.stateFlag[0] = 0) &&
             (pIp->mThrDistribute.stateFlag[1] = 1))
    {
        pIp->mThrDistribute.flgABChoose = TBS_B;
    }
    else
    {
        pIp->mThrDistribute.flgABChoose = TBS_A;
    }

    return;
}
