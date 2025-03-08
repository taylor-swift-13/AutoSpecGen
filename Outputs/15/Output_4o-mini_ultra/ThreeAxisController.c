
#include "ThrusterCtrlLogic.h"
#include "PseudoRateModulator.h"
#include "LimitFloat32.h"
#include "ThreeAxisController.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mController + (0..2));
  requires \valid(pIp->CTRL_PARAM_SAM + (0..2));
  requires \valid(pIp->mModulator + (0..2));
  ensures \valid(pIp->mModulator + (0..2));
  assigns pIp->mController[0].fy, pIp->mController[1].fy, pIp->mController[2].fy,
          pIp->mModulator[0].u, pIp->mModulator[1].u, pIp->mModulator[2].u;
*/
void ThreeAxisControllerFun(ThreeAxisController *pIp)
{
    /*@ loop invariant 0 <= i <= 2;
        loop assigns pIp->mController[i].fy;
        loop variant 3 - i;
    */
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            pIp->mController[i].fy = pIp->mController[i].Up * pIp->CTRL_PARAM_SAM[i].Kp + pIp->mController[i].Ud * pIp->CTRL_PARAM_SAM[i].Kd;
        } else if (i == 1) {
            pIp->mController[i].fy = pIp->mController[i].Up * pIp->CTRL_PARAM_SAM[i].Kp + pIp->mController[i].Ud * pIp->CTRL_PARAM_SAM[i].Kd;
        } else {
            pIp->mController[i].fy = pIp->mController[i].Ud * pIp->CTRL_PARAM_SAM[i].Kd;
        }
    }

    float32 LimitFloat32_ret_0;
    /*@ requires \valid(&LimitFloat32_ret_0);
        assigns LimitFloat32_ret_0;
    */
    IPCREATE(LimitFloat32, ipLimitFloat32_0, .fin = pIp->mController[0].fy, .fbound = 1.3, .ret = &(LimitFloat32_ret_0));
    IPCALL(ipLimitFloat32_0);
    pIp->mModulator[0].u = LimitFloat32_ret_0;

    float32 LimitFloat32_ret_1;
    /*@ requires \valid(&LimitFloat32_ret_1);
        assigns LimitFloat32_ret_1;
    */
    IPCREATE(LimitFloat32, ipLimitFloat32_1, .fin = pIp->mController[1].fy, .fbound = 1.3, .ret = &(LimitFloat32_ret_1));
    IPCALL(ipLimitFloat32_1);
    pIp->mModulator[1].u = LimitFloat32_ret_1;

    float32 LimitFloat32_ret_2;
    /*@ requires \valid(&LimitFloat32_ret_2);
        assigns LimitFloat32_ret_2;
    */
    IPCREATE(LimitFloat32, ipLimitFloat32_2, .fin = pIp->mController[2].fy, .fbound = 1.3, .ret = &(LimitFloat32_ret_2));
    IPCALL(ipLimitFloat32_2);
    pIp->mModulator[2].u = LimitFloat32_ret_2;

    /*@ requires \valid(&(pIp->mModulator[0]));
        assigns pIp->mModulator[0];
    */
    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_0, .pModulator = &(pIp->mModulator[0]), .h1 = pIp->CTRL_PARAM_SAM[0].h1);
    IPCALL(ipPseudoRateModulator_0);

    /*@ requires \valid(&(pIp->mModulator[1]));
        assigns pIp->mModulator[1];
    */
    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_1, .pModulator = &(pIp->mModulator[1]), .h1 = pIp->CTRL_PARAM_SAM[1].h1);
    IPCALL(ipPseudoRateModulator_1);

    /*@ requires \valid(&(pIp->mModulator[2]));
        assigns pIp->mModulator[2];
    */
    IPCREATE(PseudoRateModulator, ipPseudoRateModulator_2, .pModulator = &(pIp->mModulator[2]), .h1 = pIp->CTRL_PARAM_SAM[2].h1);
    IPCALL(ipPseudoRateModulator_2);

    /*@ assigns pIp->mModulator[0], pIp->mModulator[1], pIp->mModulator[2];
    */
    IPCREATE(ThrusterCtrlLogic, ipThrusterCtrlLogic);
    IPCALL(ipThrusterCtrlLogic);

    return;
}
