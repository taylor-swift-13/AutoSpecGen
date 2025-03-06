
#include "MatrixInv33F.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->src + (0 .. 8));
  requires \valid(pIp->inv + (0 .. 8));
  requires \valid(pIp->ret);

  assigns pIp->bAbleInv;
  assigns pIp->inv[0 .. 8];
  assigns *(pIp->ret);

  ensures *(pIp->ret) == pIp->bAbleInv;
  ensures pIp->bAbleInv == TRUE32 ==> 
    (\forall siint08 i; 0 <= i < 9 ==> pIp->inv[i] == \old(pIp->inv[i]) / (pIp->src[0] * \old(pIp->inv[0]) + pIp->src[1] * \old(pIp->inv[3]) + pIp->src[2] * \old(pIp->inv[6])));
  ensures pIp->bAbleInv == FALSE32 ==> 
    (\forall siint08 i; 0 <= i < 9 ==> pIp->inv[i] == \old(pIp->src[i]));
*/
void MatrixInv33FFun(MatrixInv33F *pIp)
{
    siint08 i;
    float32 rank;

    pIp -> bAbleInv = FALSE32;

    pIp -> inv[0] = pIp -> src[4] * pIp -> src[8] - pIp -> src[5] * pIp -> src[7];
    pIp -> inv[1] = pIp -> src[2] * pIp -> src[7] - pIp -> src[1] * pIp -> src[8];
    pIp -> inv[2] = pIp -> src[1] * pIp -> src[5] - pIp -> src[2] * pIp -> src[4];
    pIp -> inv[3] = pIp -> src[5] * pIp -> src[6] - pIp -> src[3] * pIp -> src[8];
    pIp -> inv[4] = pIp -> src[0] * pIp -> src[8] - pIp -> src[2] * pIp -> src[6];
    pIp -> inv[5] = pIp -> src[2] * pIp -> src[3] - pIp -> src[0] * pIp -> src[5];
    pIp -> inv[6] = pIp -> src[3] * pIp -> src[7] - pIp -> src[4] * pIp -> src[6];
    pIp -> inv[7] = pIp -> src[1] * pIp -> src[6] - pIp -> src[0] * pIp -> src[7];
    pIp -> inv[8] = pIp -> src[0] * pIp -> src[4] - pIp -> src[1] * pIp -> src[3];

    rank = pIp -> src[0] * pIp -> inv[0] + pIp -> src[1] * pIp -> inv[3] + pIp -> src[2] * pIp -> inv[6];

    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO))
    {
        pIp -> bAbleInv = TRUE32;

        /*@ 
          loop invariant 0 <= i <= 9;
          loop invariant \forall siint08 j; 0 <= j < i ==> pIp->inv[j] == \at(pIp->inv[j], Pre) / rank;
          loop assigns i, pIp->inv[0 .. 8];
          loop variant 9 - i;
        */
        for (i=0; i<9; i++)
        {
            pIp -> inv[i] = pIp -> inv[i] / rank;
        }
    }
    else
    {
        /*@ 
          loop invariant 0 <= i <= 9;
          loop invariant \forall siint08 j; 0 <= j < i ==> pIp->inv[j] == \at(pIp->src[j], Pre);
          loop assigns i, pIp->inv[0 .. 8];
          loop variant 9 - i;
        */
        for (i=0; i<9; i++)
        {
            pIp -> inv[i] = pIp -> src[i];
        }
    }

    *(pIp -> ret) = pIp -> bAbleInv;
}
