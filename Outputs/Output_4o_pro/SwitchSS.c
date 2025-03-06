
#include "SwitchSS.h"

/*@
  requires \valid(pIp);
  assigns *(volatile unsigned int *)0x8000;
  ensures *(volatile unsigned int *)0x8000 == (pIp->mDSSData.stateFlag_A == 1 ? 0x2 : 0x1);
*/
void SwitchSSFun(SwitchSS *pIp)
{
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000,0x2);
    }
    else
    {
        ADDR_WRITE(0x8000,0x1);
    }

    return ;
}
