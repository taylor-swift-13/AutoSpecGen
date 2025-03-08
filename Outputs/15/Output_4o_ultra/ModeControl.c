
#include "SAMSubModePitch.h"
#include "SAMSubModeCruise.h"
#include "SAMSubModeDamp.h"
#include "SAMSubModeRoll.h"
#include "Tr32Uint08.h"
#include "ModeControl.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mAttitude.rate[0]));
  requires \valid(&(pIp->mDSSData));
  requires \valid(&(pIp->mController[0]));
  ensures \valid(&(pIp->countMode));
  ensures \valid(&(pIp->countPublic));
  ensures \valid(&(pIp->Count160ms));
  ensures \valid(&(pIp->mFWarning));
  assigns pIp->countMode;
*/
void ModeControlFun(ModeControl *pIp)
{
    unint32 flgModetmp1;

    unint08 Tr32Uint08_ret;
    IPCREATE(Tr32Uint08, ipTr32Uint08, .pA = 0 , .ret = &(Tr32Uint08_ret));
    IPCALL(ipTr32Uint08);

    flgModetmp1 = Tr32Uint08_ret;

    pIp->countMode++;

    if (flgModetmp1 == SAM_DAMP)
    {
        /*@ 
          requires \valid(&(pIp->mAttitude.rate[0]));
          ensures \valid(&(pIp->countPublic));
          ensures \valid(&(pIp->countMode));
          assigns pIp->countMode;
        */
        IPCREATE(SAMSubModeDamp, ipSAMSubModeDamp, .rate = &(pIp->mAttitude.rate[0]), .max =  0.15f, .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode = SAM_DAMP);
        IPCALL(ipSAMSubModeDamp);
    }
    else if (flgModetmp1 == SAM_PITCH)
    {
        /*@ 
          requires \valid(&(pIp->mDSSData));
          requires \valid(&(pIp->mController[0]));
          ensures \valid(&(pIp->countPublic));
          ensures \valid(&(pIp->countMode));
          assigns pIp->countMode;
        */
        IPCREATE(SAMSubModePitch, ipSAMSubModePitch, .pSDS = &(pIp->mDSSData), .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode = SAM_PITCH, .pCtrl = &(pIp->mController[0]));
        IPCALL(ipSAMSubModePitch);
    }
    else if (flgModetmp1 == SAM_ROLL)
    {
        /*@ 
          requires \valid(&(pIp->mDSSData));
          requires \valid(&(pIp->mController[0]));
          ensures \valid(&(pIp->countPublic));
          ensures \valid(&(pIp->countMode));
          assigns pIp->countMode;
        */
        IPCREATE(SAMSubModeRoll, ipSAMSubModeRoll, .pSDS = &(pIp->mDSSData), .countPublic = pIp->countPublic, .countMode = pIp->countMode, .flgMode = SAM_ROLL, .pCtrl = &(pIp->mController[0]));
        IPCALL(ipSAMSubModeRoll);
    }
    else if (flgModetmp1 == SAM_CRUISE)
    {
        /*@ 
          ensures \valid(&(pIp->countMode));
          ensures \valid(&(pIp->Count160ms));
          ensures \valid(&(pIp->mFWarning));
          assigns pIp->countMode;
        */
        IPCREATE(SAMSubModeCruise, ipSAMSubModeCruise, .countMode = pIp->countMode, .Count160ms = pIp->Count160ms, .mFWarning = pIp->mFWarning);
        IPCALL(ipSAMSubModeCruise);
    }
    else
    {
        TR32_FLGMODE_VALUE(SAM_DAMP);
    }

    return;
}
