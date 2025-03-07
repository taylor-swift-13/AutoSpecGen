
#include "ThrABAutoChoose.h"

/*@ 
  requires pIp != NULL; 
  requires \valid(pIp->mThrDistribute.stateFlag + (0..1));
  requires \valid(pIp->mThrDistribute.flgABChoose);
  ensures \result == 0; // The function returns void, so we ensure it has no effect on the return value.
  assigns pIp->mThrDistribute.flgABChoose;
*/
void ThrABAutoChooseFun(ThrABAutoChoose *pIp)
{
    /*@ 
      loop invariant \valid(pIp);
      loop assigns pIp->mThrDistribute.flgABChoose;
    */
    if ((pIp -> mThrDistribute.stateFlag[0] == 1) &&
        (pIp -> mThrDistribute.stateFlag[1] == 1))
    {
        pIp -> mThrDistribute.flgABChoose = TBS_AB;
    }
    else if ((pIp -> mThrDistribute.stateFlag[0] == 0) &&
             (pIp -> mThrDistribute.stateFlag[1] == 1))
    {
        pIp -> mThrDistribute.flgABChoose = TBS_B;
    }
    else
    {
        pIp -> mThrDistribute.flgABChoose = TBS_A;
    }

    return;
}
