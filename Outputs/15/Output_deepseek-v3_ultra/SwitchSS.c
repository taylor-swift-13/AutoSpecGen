
#include "SwitchSS.h"

/*@ 
  requires \valid(pIp);
  ensures pIp->mDSSData.stateFlag_A == 1 ==> \at(ADDR_READ(0x8000), Post) == 0x2;
  ensures pIp->mDSSData.stateFlag_A != 1 ==> \at(ADDR_READ(0x8000), Post) == 0x1;
  assigns \nothing;
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@ assert \valid(pIp); */
    if (pIp->mDSSData.stateFlag_A == 1)
    {
        /*@ assert pIp->mDSSData.stateFlag_A == 1; */
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        /*@ assert pIp->mDSSData.stateFlag_A != 1; */
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
