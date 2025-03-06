
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mAttitude);
  requires \valid(pIp->mController + (0..1)); // Assuming mController has at least 2 elements
  assigns \nothing;
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->mAttitude);
      requires \valid(pIp->mController + (0..1)); // Assuming mController has at least 2 elements
      assigns \nothing;
    */
	IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
	IPCALL(ipLimitCtrlAngleInput);

    /*@ 
      requires \valid(pIp);
      requires \valid(pIp->mAttitude);
      requires \valid(pIp->mController + (0..1)); // Assuming mController has at least 2 elements
      assigns \nothing;
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    IPCALL(ipLimitCtrlRateInput);

    return ;
}
