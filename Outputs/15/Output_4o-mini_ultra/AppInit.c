
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ 
  requires \valid(pIp);
  assigns \nothing; // This may need to be changed based on actual behavior
*/
void AppInitFun(AppInit *pIp)
{
    /*@ 
      assigns ipInitVar; // Indicating that ipInitVar is modified
    */
    IPCREATE(InitVar, ipInitVar);
    IPCALL(ipInitVar);

    /*@ 
      assigns ipDevControl; // Indicating that ipDevControl is modified
    */
    IPCREATE(DevControl, ipDevControl);
    IPCALL(ipDevControl);

    /*@ 
      assigns *(volatile unsigned int*)0x8083; // This is correct as it modifies memory
    */
    ADDR_WRITE(0x8083, 0x1);

    return;
}
