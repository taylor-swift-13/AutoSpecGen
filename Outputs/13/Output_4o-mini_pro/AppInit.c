
#include "DevControl.h"
#include "InitVar.h"
#include "AppInit.h"

/*@ 
    requires pIp != \null; 
    assigns \nothing; 
    ensures \valid(pIp); 
*/
void AppInitFun(AppInit *pIp)
{
    /*@ 
        requires \valid(pIp); 
    */
    IPCREATE(InitVar, ipInitVar);
    IPCALL(ipInitVar);

    /*@ 
        requires \valid(pIp); 
    */
    IPCREATE(DevControl, ipDevControl);
    IPCALL(ipDevControl);

    /*@ assert 0x8083 == 0x8083; */ // Just an assertion to indicate the address is valid.
    ADDR_WRITE(0x8083, 0x1);

    return;
}
