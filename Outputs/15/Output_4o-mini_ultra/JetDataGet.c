
#include "ThrABAutoChoose.h"
#include "JetDataGet.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mThrDistribute.stateFlag + (0..1));
  assigns pIp->mThrDistribute.stateFlag[0], pIp->mThrDistribute.stateFlag[1];
  ensures pIp->mThrDistribute.stateFlag[0] == 1 <==> ((ADDR_READ(0xE000) & 0x4) == 0x4);
  ensures pIp->mThrDistribute.stateFlag[1] == 1 <==> ((ADDR_READ(0xE000) & 0x8) == 0x8);
*/
void JetDataGetFun(JetDataGet *pIp)
{
    if((ADDR_READ(0xE000) & 0x4) == 0x4)
    {
        pIp -> mThrDistribute.stateFlag[0] = 1;
    }
    else
    {
        pIp -> mThrDistribute.stateFlag[0] = 0;
    }

    if((ADDR_READ(0xE000) & 0x8) == 0x8)
    {
        pIp -> mThrDistribute.stateFlag[1] = 1;
    }
    else
    {
        pIp -> mThrDistribute.stateFlag[1] = 0;
    }

    IPCREATE(ThrABAutoChoose, ipThrABAutoChoose);
    IPCALL(ipThrABAutoChoose);

    return;
}
