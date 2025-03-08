
#include "GyroChoose.h"

/*@ 
  requires \valid(pIp) && \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0..8));
  requires \valid(pIp->pGyroData->SignFlag + (0..8));
  assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0..8];
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

    /*@ 
      loop invariant 0 <= i <= 9;
      loop invariant \forall unint08 j; 0 <= j < i ==> 
        (pIp->pGyroData->stateFlag[j] == TRUE ==> 
         pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == j &&
         (pIp->pGyroData->gyroStatus0 & (1 << j)) != 0);
      loop invariant \forall unint08 j; 0 <= j < i ==> 
        (pIp->pGyroData->stateFlag[j] == FALSE ==> 
         (pIp->pGyroData->gyroStatus0 & (1 << j)) == 0);
      loop assigns i, pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0..8];
      loop variant 9 - i;
    */
    for (i = 0; i < 9; i++)
    {
        if (pIp->pGyroData->stateFlag[i] == TRUE)
        {
            pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal] = i;
            pIp->pGyroData->JoinTotal++;
            pIp->pGyroData->gyroStatus0 = pIp->pGyroData->gyroStatus0 | (1 << i);
        }
    }

    return;
}
