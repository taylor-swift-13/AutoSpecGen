
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mAttitude));
  requires \valid(&(pIp->mController[0]));
  assigns pIp->mAttitude, pIp->mController[0]; // Specify the modified locations
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
      requires \valid(&(pIp->mAttitude));
      requires \valid(&(pIp->mController[0]));
      assigns pIp->mAttitude, pIp->mController[0]; // Specify the modified locations
    */
    IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
    IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      requires \valid(&(pIp->mAttitude));
      requires \valid(&(pIp->mController[0]));
      assigns pIp->mAttitude, pIp->mController[0]; // Specify the modified locations
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return;
}
