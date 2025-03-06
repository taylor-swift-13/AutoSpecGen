
#include "GyroChoose.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0 .. 8));
  requires \valid(pIp->pGyroData->SignFlag + (0 .. 8));
  ensures pIp->pGyroData->JoinTotal >= 0 && pIp->pGyroData->JoinTotal <= 9;
  ensures \forall int i; 0 <= i < 9 ==> (pIp->pGyroData->stateFlag[i] == TRUE ==> pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == i);
  ensures \forall int i; 0 <= i < 9 ==> (pIp->pGyroData->stateFlag[i] == TRUE ==> (pIp->pGyroData->gyroStatus0 & (1 << i)) != 0);
  assigns pIp->pGyroData->JoinTotal;
  assigns pIp->pGyroData->gyroStatus0;
  assigns pIp->pGyroData->SignFlag[0 .. 8];
*/
void GyroChooseFun(GyroChoose *pIp)
{
    unint08 i;

    pIp->pGyroData->JoinTotal = 0;
    pIp->pGyroData->gyroStatus0 = 0;

    /*@
      loop invariant 0 <= i <= 9;
      loop invariant pIp->pGyroData->JoinTotal >= 0 && pIp->pGyroData->JoinTotal <= i;
      loop invariant \forall int j; 0 <= j < i ==> (pIp->pGyroData->stateFlag[j] == TRUE ==> pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal - 1] == j);
      loop invariant \forall int j; 0 <= j < i ==> (pIp->pGyroData->stateFlag[j] == TRUE ==> (pIp->pGyroData->gyroStatus0 & (1 << j)) != 0);
      loop assigns i, pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, pIp->pGyroData->SignFlag[0 .. 8];
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
