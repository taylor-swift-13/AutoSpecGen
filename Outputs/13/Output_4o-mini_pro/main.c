
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
  requires pIp != \null; 
  requires \valid(pIp->ret); 
  ensures \old(*(pIp->ret)) == 0; 
  assigns *(pIp->ret);
*/
void mainFun(main *pIp)
{
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}
