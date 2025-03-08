
#include "Delay.h"

/*@ axiomatic Delay {
      logic integer delay_time(Delay *p) reads p->delaytime;
      axiom delay_time_def: 
        \forall Delay *p; delay_time(p) == p->delaytime;
   }
*/

/*@ 
  requires \valid(pIp);
  requires \valid(&pIp->delaytime);
  ensures delay_time(pIp) == \old(delay_time(pIp));
  assigns \nothing;
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
