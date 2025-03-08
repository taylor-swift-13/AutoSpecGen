
#include "AppInit.h"
#include "PeriodControl.h"
#include "main.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->ret);
  assigns *(pIp->ret);
  ensures *(pIp->ret) == 0;
*/
void mainFun(main *pIp)
{
    /*@ 
      assigns \nothing; // Assuming IPCREATE and IPCALL do not modify global state
    */
    IPCREATE(AppInit, ipAppInit);
    IPCALL(ipAppInit);

    /*@ 
      assigns \nothing; // Assuming IPCREATE and IPCALL do not modify global state
    */
    IPCREATE(PeriodControl, ipPeriodControl);
    IPCALL(ipPeriodControl);

    /*@ 
      requires \valid(pIp->ret); // Ensure pIp->ret is valid before dereferencing
      assigns *(pIp->ret); // Specify that we are modifying *(pIp->ret)
    */
    *(pIp -> ret) = 0;
}
