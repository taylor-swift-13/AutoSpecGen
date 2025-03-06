
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  ensures *(pIp->ret) == 0;
  assigns *(pIp->ret) \from \nothing;
*/
void mainFun(main *pIp)
{
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    *(pIp -> ret) = 0;
}
