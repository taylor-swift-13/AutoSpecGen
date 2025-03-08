
#include "GyroPick.h"

/*@ axiomatic GyroPickLogic {
      logic real ABS(logic real x) = if x >= 0.0 then x else -x;
    }
*/

/*@ requires \valid(pIp);
    requires \valid(pIp->pGyroData);
    requires \valid(pIp->pGyroData->wa + (0..8));
    requires \valid(pIp->pGyroData->wal + (0..8));
    requires \valid(pIp->pGyroData->countPick + (0..8));
    assigns pIp->pGyroData->wa[0..8];
    assigns pIp->pGyroData->wal[0..8];
    assigns pIp->pGyroData->countPick[0..8];
*/
void GyroPickFun(GyroPick *pIp)
{
    unint08 iy;
    float32 tmpgi;

    /*@ loop invariant 0 <= iy <= 9;
        loop invariant \forall unint08 j; 0 <= j < iy ==> 
            pIp->pGyroData->wa[j] == \at(pIp->pGyroData->wa[j], Pre) || 
            pIp->pGyroData->wa[j] == pIp->pGyroData->wal[j];
        loop invariant \forall unint08 j; 0 <= j < iy ==> 
            pIp->pGyroData->wal[j] == \at(pIp->pGyroData->wal[j], Pre) || 
            pIp->pGyroData->wal[j] == pIp->pGyroData->wa[j];
        loop invariant \forall unint08 j; 0 <= j < iy ==> 
            pIp->pGyroData->countPick[j] == \at(pIp->pGyroData->countPick[j], Pre) || 
            pIp->pGyroData->countPick[j] == 0;
        loop assigns pIp->pGyroData->wa[0..8], pIp->pGyroData->wal[0..8], pIp->pGyroData->countPick[0..8];
        loop variant 9 - iy;
    */
    for (iy = 0; iy < 9; iy++)
    {
        tmpgi = ABS(pIp->pGyroData->wa[iy] - pIp->pGyroData->wal[iy]);

        if (tmpgi > 0.048f)
        {
            pIp->pGyroData->countPick[iy]++;

            if (pIp->pGyroData->countPick[iy] < 6)
            {
                pIp->pGyroData->wa[iy] = pIp->pGyroData->wal[iy];
            }
            else
            {
                pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
                pIp->pGyroData->countPick[iy] = 0;
            }
        }
        else
        {
            pIp->pGyroData->wal[iy] = pIp->pGyroData->wa[iy];
            pIp->pGyroData->countPick[iy] = 0;
        }
    }

    return;
}
