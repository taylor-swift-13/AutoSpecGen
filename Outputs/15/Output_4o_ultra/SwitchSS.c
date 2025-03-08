
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&(pIp->mDSSData));
  assigns *(volatile unsigned int *)0x8000;
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ 
      requires \valid(&(pIp->mDSSData.stateFlag_A));
      assigns *(volatile unsigned int *)0x8000;
      ensures *(volatile unsigned int *)0x8000 == ((pIp->mDSSData.stateFlag_A == 1) ? 0x2 : 0x1);
    */
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000,0x2);
    }
    else
    {
        ADDR_WRITE(0x8000,0x1);
    }

    return;
}
