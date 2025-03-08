
#include "GyroChoose.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->stateFlag + (0..8));
  requires \valid(pIp->pGyroData->SignFlag + (0..8));
  assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->SignFlag[0..8], 
          pIp->pGyroData->gyroStatus0; // Removed invalid \valid checks
*/
void GyroChooseFun(GyroChoose *pIp)
{
    /*@ loop invariant 0 <= i <= 9;
        loop assigns pIp->pGyroData->JoinTotal, pIp->pGyroData->gyroStatus0, 
                     pIp->pGyroData->SignFlag[0..8];
        loop variant 9 - i; 
    */
    for (unint08 i = 0; i < 9; i++)
    {
        /*@ requires \valid(pIp->pGyroData->stateFlag + i);
            ensures pIp->pGyroData->stateFlag[i] == TRUE ==> 
                   pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal] == i;
        */
        if (pIp->pGyroData->stateFlag[i] == TRUE)
        {
            pIp->pGyroData->SignFlag[pIp->pGyroData->JoinTotal] = i;
            pIp->pGyroData->JoinTotal++;
            pIp->pGyroData->gyroStatus0 = pIp->pGyroData->gyroStatus0 | (1 << i);
        }
    }

    return;
}
