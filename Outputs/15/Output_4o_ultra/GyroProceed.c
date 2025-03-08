
#include "CalculateGyroRs.h"
#include "CalculateGyroDg.h"
#include "GyroChoose.h"
#include "GyroPick.h"
#include "ModPNHP.h"
#include "GyroProceed.h"

/*@ 
requires \valid(pIp);
requires \valid(&(pIp->mGyroData.Gi[0])) && \valid(&(pIp->mGyroData.Gi[1]));
requires \valid(&(pIp->mGyroData.W[0])) && \valid(&(pIp->mGyroData.W[1]));
assigns pIp->mGyroData.Gi[0], pIp->mGyroData.Gi[1];
ensures \old(pIp->mGyroData.Gi[0]) + pIp->mGyroData.W[0] * 0.160f == pIp->mGyroData.Gi[0];
ensures \old(pIp->mGyroData.Gi[1]) + pIp->mGyroData.W[1] * 0.160f == pIp->mGyroData.Gi[1];
*/
void GyroProceedFun(GyroProceed *pIp)
{
    float32 dgi[2];

    /*@ requires \valid(&(pIp->mGyroData));
        assigns pIp->mGyroData;
        ensures \valid(&(pIp->mGyroData));
    */
    IPCREATE(GyroPick, ipGyroPick, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroPick);

    /*@ requires \valid(&(pIp->mGyroData));
        assigns pIp->mGyroData;
        ensures \valid(&(pIp->mGyroData));
    */
    IPCREATE(GyroChoose, ipGyroChoose, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroChoose);

    /*@ requires \valid(&(pIp->mGyroData));
        assigns pIp->mGyroData;
        ensures \valid(&(pIp->mGyroData));
    */
    IPCREATE(CalculateGyroRs, ipCalculateGyroRs, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipCalculateGyroRs);

    /*@ requires \valid(&(pIp->mGyroData));
        assigns pIp->mGyroData;
        ensures \valid(&(pIp->mGyroData));
    */
    IPCREATE(CalculateGyroDg, ipCalculateGyroDg, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipCalculateGyroDg);

    dgi[0] = pIp->mGyroData.Gi[0] + pIp->mGyroData.W[0] * 0.160f;
    dgi[1] = pIp->mGyroData.Gi[1] + pIp->mGyroData.W[1] * 0.160f;

    float32 ModPNHP_ret_0;
    /*@ requires \valid(&(ModPNHP_ret_0));
        assigns ModPNHP_ret_0;
        ensures \valid(&(ModPNHP_ret_0));
    */
    IPCREATE(ModPNHP, ipModPNHP_0, .x = dgi[0], .halfperiod = 180.0f, .ret = &(ModPNHP_ret_0));
    IPCALL(ipModPNHP_0);

    pIp->mGyroData.Gi[0] = ModPNHP_ret_0;

    float32 ModPNHP_ret_1;
    /*@ requires \valid(&(ModPNHP_ret_1));
        assigns ModPNHP_ret_1;
        ensures \valid(&(ModPNHP_ret_1));
    */
    IPCREATE(ModPNHP, ipModPNHP_1, .x = dgi[1], .halfperiod = 180.0f, .ret = &(ModPNHP_ret_1));
    IPCALL(ipModPNHP_1);

    pIp->mGyroData.Gi[1] = ModPNHP_ret_1;

    return;
}
