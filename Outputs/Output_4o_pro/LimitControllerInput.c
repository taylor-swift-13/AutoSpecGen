
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mAttitude));
  requires \valid(&(pIp->mController[0]));
  ensures \true;
  assigns pIp->mController[0]; // Assuming mController[0] is modified by IPCALL
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
      requires \valid(&(pIp->mAttitude));
      requires \valid(&(pIp->mController[0]));
      ensures \true;
      assigns pIp->mController[0]; // Assuming mController[0] is modified by IPCALL
    */
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      requires \valid(&(pIp->mAttitude));
      requires \valid(&(pIp->mController[0]));
      ensures \true;
      assigns pIp->mController[0]; // Assuming mController[0] is modified by IPCALL
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
