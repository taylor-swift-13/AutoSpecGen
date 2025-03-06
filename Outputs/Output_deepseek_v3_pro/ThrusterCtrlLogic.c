
#include "ThrusterCtrlLogic.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mThrDistribute.wPulse;
  ensures pIp->mThrDistribute.wPulse == \old(
    (pIp->mModulator[0].Yp != 0 ? pIp->mThrDistribute.wPulse | 0x04 : pIp->mThrDistribute.wPulse) |
    (pIp->mModulator[0].Yn != 0 ? pIp->mThrDistribute.wPulse | 0x08 : pIp->mThrDistribute.wPulse) |
    (pIp->mModulator[1].Yp != 0 ? pIp->mThrDistribute.wPulse | 0x10 : pIp->mThrDistribute.wPulse) |
    (pIp->mModulator[1].Yn != 0 ? pIp->mThrDistribute.wPulse | 0x20 : pIp->mThrDistribute.wPulse) |
    (pIp->mModulator[2].Yp != 0 ? pIp->mThrDistribute.wPulse | 0x40 : pIp->mThrDistribute.wPulse) |
    (pIp->mModulator[2].Yn != 0 ? pIp->mThrDistribute.wPulse | 0x80 : pIp->mThrDistribute.wPulse)
  );
*/
void ThrusterCtrlLogicFun(ThrusterCtrlLogic *pIp)
{
    if ( pIp -> mModulator[0].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x04 ;
    }

    if ( pIp -> mModulator[0].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x08 ;
    }

    if ( pIp -> mModulator[1].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x10 ;
    }

    if ( pIp -> mModulator[1].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x20 ;
    }

    if ( pIp -> mModulator[2].Yp != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x40 ;
    }

    if ( pIp -> mModulator[2].Yn != 0)
    {
        pIp -> mThrDistribute.wPulse = pIp -> mThrDistribute.wPulse | 0x80 ;
    }

    return ;
}
