
#include "SwitchSS.h"

/*@ 
    requires pIp != NULL; 
    requires \valid(pIp); 
    requires \valid(pIp->mDSSData); 
    ensures \result == (pIp->mDSSData.stateFlag_A == 1 ? 0x2 : 0x1);
    assigns \nothing;
*/
void SwitchSSFun(SwitchSS *pIp)
{
    /*@
        loop assigns \nothing;
    */
    /*@ assert \valid(&pIp->mDSSData.stateFlag_A); */
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
