
#include "ThrusterCtrlLogic.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mModulator + (0..2));
  requires \valid(&pIp->mThrDistribute);
  assigns pIp->mThrDistribute.wPulse;
  ensures (pIp->mModulator[0].Yp != 0) ==> (pIp->mThrDistribute.wPulse & 0x04) != 0;
  ensures (pIp->mModulator[0].Yn != 0) ==> (pIp->mThrDistribute.wPulse & 0x08) != 0;
  ensures (pIp->mModulator[1].Yp != 0) ==> (pIp->mThrDistribute.wPulse & 0x10) != 0;
  ensures (pIp->mModulator[1].Yn != 0) ==> (pIp->mThrDistribute.wPulse & 0x20) != 0;
  ensures (pIp->mModulator[2].Yp != 0) ==> (pIp->mThrDistribute.wPulse & 0x40) != 0;
  ensures (pIp->mModulator[2].Yn != 0) ==> (pIp->mThrDistribute.wPulse & 0x80) != 0;
*/
void ThrusterCtrlLogicFun(ThrusterCtrlLogic *pIp)
{
    /*@ assert \valid(pIp); */
    /*@ assert \valid(pIp->mModulator + (0..2)); */
    /*@ assert \valid(&pIp->mThrDistribute); */

    if (pIp->mModulator[0].Yp != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x04;
    }

    if (pIp->mModulator[0].Yn != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x08;
    }

    if (pIp->mModulator[1].Yp != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x10;
    }

    if (pIp->mModulator[1].Yn != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x20;
    }

    if (pIp->mModulator[2].Yp != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x40;
    }

    if (pIp->mModulator[2].Yn != 0)
    {
        pIp->mThrDistribute.wPulse = pIp->mThrDistribute.wPulse | 0x80;
    }

    return;
}
