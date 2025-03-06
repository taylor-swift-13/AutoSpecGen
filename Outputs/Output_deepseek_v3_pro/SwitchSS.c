
#include "SwitchSS.h"

/*@
  requires \valid(pIp);
  assigns \nothing;
  behavior stateFlag_A_is_1:
    assumes pIp->mDSSData.stateFlag_A == 1;
    ensures \true;
  behavior stateFlag_A_is_not_1:
    assumes pIp->mDSSData.stateFlag_A != 1;
    ensures \true;
  complete behaviors;
  disjoint behaviors;
*/
void SwitchSSFun(SwitchSS *pIp)
{
    if (pIp->mDSSData.stateFlag_A == 1)
    {
        ADDR_WRITE(0x8000, 0x2);
    }
    else
    {
        ADDR_WRITE(0x8000, 0x1);
    }

    return;
}
