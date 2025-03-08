
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->mDSSData);
  assigns *(int*)0x8000; // Memory at address 0x8000 is modified
*/
void SwitchSSFun(SwitchSS *pIp)
{
    if (pIp -> mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
