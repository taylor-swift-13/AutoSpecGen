
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ 
  requires \valid(pIp);
  ensures \true;
*/
void AppInitFun(AppInit *pIp)
{
    IPCREATE(InitVar, ipInitVar);
    IPCALL(ipInitVar);

    IPCREATE(DevControl, ipDevControl);
    IPCALL(ipDevControl);

    ADDR_WRITE(0x8083, 0x1);

    return;
}
