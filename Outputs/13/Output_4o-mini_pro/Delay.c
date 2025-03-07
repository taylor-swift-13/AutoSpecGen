
#include "Delay.h"

/*@ 
    requires \valid(pIp);
    requires pIp->delaytime >= 0;
    ensures \true; // The function returns void, so no result to specify.
    assigns \nothing; // The function does not modify any state.
*/
void DelayFun(Delay *pIp)
{
    unint16 uidt;

    /*@
        loop invariant 0 <= uidt <= pIp->delaytime;
        loop assigns uidt;
        loop variant pIp->delaytime - uidt;
    */
    for (uidt = 0; uidt < pIp->delaytime; uidt++)
    {
        ;
    }

    return;
}
