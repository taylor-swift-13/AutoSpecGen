
#include "CalculateGyroRs.h"
#include "CalculateGyroDg.h"
#include "GyroChoose.h"
#include "GyroPick.h"
#include "ModPNHP.h"
#include "GyroProceed.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mGyroData));
  assigns pIp->mGyroData;
*/
void GyroProceedFun(GyroProceed *pIp)
{
    float32 dgi[2];

    /*@ assert \valid(&(pIp->mGyroData)); */
    IPCREATE(GyroPick, ipGyroPick, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroPick);

    /*@ assert \valid(&(pIp->mGyroData)); */
    IPCREATE(GyroChoose, ipGyroChoose, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipGyroChoose);

    /*@ assert \valid(&(pIp->mGyroData)); */
    IPCREATE(CalculateGyroRs, ipCalculateGyroRs, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipCalculateGyroRs);

    /*@ assert \valid(&(pIp->mGyroData)); */
    IPCREATE(CalculateGyroDg, ipCalculateGyroDg, .pGyroData = &(pIp->mGyroData));
    IPCALL(ipCalculateGyroDg);

    /*@ assert \valid(&(pIp->mGyroData.Gi[0])) && \valid(&(pIp->mGyroData.W[0])); */
    dgi[0] = pIp->mGyroData.Gi[0] + pIp->mGyroData.W[0] * 0.160f;

    /*@ assert \valid(&(pIp->mGyroData.Gi[1])) && \valid(&(pIp->mGyroData.W[1])); */
    dgi[1] = pIp->mGyroData.Gi[1] + pIp->mGyroData.W[1] * 0.160f;

    float32 ModPNHP_ret_0;
    /*@ assert \valid(&ModPNHP_ret_0); */
    IPCREATE(ModPNHP, ipModPNHP_0, .x = dgi[0], .halfperiod = 180.0f, .ret = &(ModPNHP_ret_0));
    IPCALL(ipModPNHP_0);

    /*@ assert \valid(&(pIp->mGyroData.Gi[0])); */
    pIp->mGyroData.Gi[0] = ModPNHP_ret_0;

    float32 ModPNHP_ret_1;
    /*@ assert \valid(&ModPNHP_ret_1); */
    IPCREATE(ModPNHP, ipModPNHP_1, .x = dgi[1], .halfperiod = 180.0f, .ret = &(ModPNHP_ret_1));
    IPCALL(ipModPNHP_1);

    /*@ assert \valid(&(pIp->mGyroData.Gi[1])); */
    pIp->mGyroData.Gi[1] = ModPNHP_ret_1;

    return;
}
