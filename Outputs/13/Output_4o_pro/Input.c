
#include "DSSDataGet.h"
#include "JetDataGet.h"
#include "GyroStateGet.h"
#include "Input.h"

/*@
  requires \valid(pIp);
  requires \valid(&(pIp->mGyroData.stateFlag[0]));
  requires \valid(&(pIp->mGyroData.wa[0]));
  requires \valid(&(pIp->mDSSData));
  ensures \true;
*/
void InputFun(Input *pIp)
{
    /*@
      assigns pIp->mGyroData.stateFlag[0];
      assigns pIp->mGyroData.wa[0];
    */
    IPCREATE(GyroStateGet, ipGyroStateGet, .NumGyro = 9, .stateFlag =  &(pIp->mGyroData.stateFlag[0]), .wa =  &(pIp->mGyroData.wa[0]));
    IPCALL(ipGyroStateGet);

    /*@
      assigns pIp->mDSSData;
    */
    IPCREATE(DSSDataGet, ipDSSDataGet, .pDSSData = &(pIp->mDSSData));
    IPCALL(ipDSSDataGet);

    /*@
      assigns \nothing;
    */
    IPCREATE(JetDataGet, ipJetDataGet);
    IPCALL(ipJetDataGet);

    return;
}
