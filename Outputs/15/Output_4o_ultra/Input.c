
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mGyroData.stateFlag[0]) + (0..8));
  requires \valid(&(pIp->mGyroData.wa[0]) + (0..8));
  requires \valid(&(pIp->mDSSData));
  assigns pIp->mGyroData.stateFlag[0..8];
  assigns pIp->mGyroData.wa[0..8];
  assigns pIp->mDSSData;
*/
void InputFun(Input *pIp)
{
    /*@ 
      requires \valid(&(pIp->mGyroData.stateFlag[0]) + (0..8));
      requires \valid(&(pIp->mGyroData.wa[0]) + (0..8));
      assigns pIp->mGyroData.stateFlag[0..8];
      assigns pIp->mGyroData.wa[0..8];
    */
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    /*@ 
      requires \valid(&(pIp->mDSSData));
      assigns pIp->mDSSData;
    */
    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
