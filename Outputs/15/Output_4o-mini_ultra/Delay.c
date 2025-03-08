
#include "Delay.h"

/*@ 
  requires \valid(pIp);
  requires pIp->delaytime >= 0;
  assigns \nothing; // No memory is modified
*/
void DelayFun(Delay *pIp)
{
    /*@ loop invariant 0 <= uidt <= pIp->delaytime;
        loop assigns uidt;
        loop variant pIp->delaytime - uidt; 
    */
    for (unint16 uidt = 0; uidt < pIp->delaytime; uidt++)
    {
        ;
    }

    return;
}
