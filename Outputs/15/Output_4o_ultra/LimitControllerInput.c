
#include "LimitCtrlRateInput.h"
#include "LimitCtrlAngleInput.h"
#include "LimitControllerInput.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mAttitude));
requires \valid(&(pIp->mController[0]));
assigns \nothing;
*/
void LimitControllerInputFun(LimitControllerInput *pIp)
{
    /*@ 
    requires \valid(&(pIp->mAttitude));
    requires \valid(&(pIp->mController[0]));
    assigns \nothing;
    */
    IPCREATE(LimitCtrlAngleInput, ipLimitCtrlAngleInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  0.8f);
    
    /*@ 
    requires \valid(&(ipLimitCtrlAngleInput));
    assigns \nothing;
    */
    IPCALL(ipLimitCtrlAngleInput);

    /*@ 
    requires \valid(&(pIp->mAttitude));
    requires \valid(&(pIp->mController[0]));
    assigns \nothing;
    */
    IPCREATE(LimitCtrlRateInput, ipLimitCtrlRateInput, .pSA = &(pIp->mAttitude), .pSCtrl =  &(pIp->mController[0]), .max =  1.2f);
    
    /*@ 
    requires \valid(&(ipLimitCtrlRateInput));
    assigns \nothing;
    */
    IPCALL(ipLimitCtrlRateInput);

    return;
}
