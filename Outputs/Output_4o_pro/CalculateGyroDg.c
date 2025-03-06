
#include "MatrixMulti.h"
#include "CalculateGyroDg.h"
#include "MatrixMulti.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->pGyroData);
  requires \valid(pIp->pGyroData->SignFlag + (0 .. pIp->pGyroData->JoinTotal-1));
  requires \valid(pIp->pGyroData->wa + (0 .. 4));
  requires \valid(pIp->pGyroData->W + (0 .. 2));
  requires \valid(pIp->pGyroData->Rtemp + (0 .. 2));
  requires \valid(pIp->pGyroData->Rtemp[0] + (0 .. 4));
  requires \valid(pIp->pGyroData->Rtemp[1] + (0 .. 4));
  requires \valid(pIp->pGyroData->Rtemp[2] + (0 .. 4));
  ensures \forall int i; 0 <= i < 5 ==> (\old(pIp->pGyroData->JoinTotal) <= i ==> \at(tmpwa[i], Post) == 0) || (i < \old(pIp->pGyroData->JoinTotal) ==> \at(tmpwa[i], Post) == \old(pIp->pGyroData->wa[\old(pIp->pGyroData->SignFlag[i])]));
  ensures pIp->pGyroData->JoinTotal < 3 ==> (pIp->pGyroData->W[0] == 0.0f && pIp->pGyroData->W[1] == 0.0f && pIp->pGyroData->W[2] == 0.0f);
*/
void CalculateGyroDgFun(CalculateGyroDg *pIp)
{
    unint08 j;
    unint08 k;
    float32 tmpwa[5];

    /*@ 
      loop invariant 0 <= j <= 5;
      loop assigns j, tmpwa[0 .. 4];
    */
    for (j = 0; j < 5; j++)
    {
        tmpwa[j] = 0;
    }

    /*@ 
      loop invariant 0 <= j <= pIp->pGyroData->JoinTotal;
      loop assigns j, k, tmpwa[0 .. 4];
    */
    for (j = 0; j < pIp->pGyroData->JoinTotal; j++)
    {
        k = pIp->pGyroData->SignFlag[j];
        tmpwa[j] = pIp->pGyroData->wa[k];
    }

    if (pIp->pGyroData->JoinTotal >= 3)
    {
        IPCREATE(MatrixMulti, ipMatrixMulti, .product = &(pIp->pGyroData->W[0]), .faciend = &(pIp->pGyroData->Rtemp[0][0]), .multiplier = &tmpwa[0], .nrow = 3, .nrc = 5, .ncol = 1);
        IPCALL(ipMatrixMulti);
    }
    else
    {
        pIp->pGyroData->W[0] = 0.0f;
        pIp->pGyroData->W[1] = 0.0f;
        pIp->pGyroData->W[2] = 0.0f;
    }

    return;
}
