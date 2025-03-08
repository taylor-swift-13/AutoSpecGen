
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mGyroData.stateFlag[0])) && \valid(&(pIp->mGyroData.wa[0]));
  requires \valid(&(pIp->mDSSData));
  assigns \nothing; // No memory is modified
*/
void InputFun(Input *pIp)
{
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
