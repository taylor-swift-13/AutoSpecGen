
#include "GyroPick.h"

/*@ 
    requires \valid(pIp);
    requires \valid(pIp->pGyroData);
    requires \valid(pIp->pGyroData->wa + (0..8));
    requires \valid(pIp->pGyroData->wal + (0..8));
    requires \valid(pIp->pGyroData->countPick + (0..8));
    ensures \forall int i; 0 <= i < 9 ==> 
        (pIp->pGyroData->countPick[i] == \old(pIp->pGyroData->countPick[i]) + 
        (ABS(pIp->pGyroData->wa[i] - pIp->pGyroData->wal[i]) > 0.048f ? 1 : 0));
    assigns pIp->pGyroData->countPick[0..8], 
            pIp->pGyroData->wa[0..8], 
            pIp->pGyroData->wal[0..8];
*/
void GyroPickFun(GyroPick *pIp)
{
    unint08 iy;
    float32 tmpgi;

    /*@ loop invariant 0 <= iy <= 9;
        loop assigns iy, pIp->pGyroData->countPick[0..8], 
                     pIp->pGyroData->wa[0..8], 
                     pIp->pGyroData->wal[0..8];
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
