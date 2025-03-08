
#include "MatrixInv33F.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->src + (0..8));
  requires \valid(pIp->inv + (0..8));
  requires \valid(pIp->ret);
  ensures *pIp->ret == pIp->bAbleInv;
*/
void MatrixInv33FFun(MatrixInv33F *pIp)
{
    /*@ loop invariant 0 <= i <= 8; // Corrected invariant
      loop variant 8 - i; // Corrected variant
    */
    for (siint08 i = 0; i < 9; i++) {
        pIp->inv[i] = pIp->src[i]; // Initialize inv to src
    }

    pIp->bAbleInv = FALSE32;

    pIp->inv[0] = pIp->src[4] * pIp->src[8] - pIp->src[5] * pIp->src[7];
    pIp->inv[1] = pIp->src[2] * pIp->src[7] - pIp->src[1] * pIp->src[8];
    pIp->inv[2] = pIp->src[1] * pIp->src[5] - pIp->src[2] * pIp->src[4];
    pIp->inv[3] = pIp->src[5] * pIp->src[6] - pIp->src[3] * pIp->src[8];
    pIp->inv[4] = pIp->src[0] * pIp->src[8] - pIp->src[2] * pIp->src[6];
    pIp->inv[5] = pIp->src[2] * pIp->src[3] - pIp->src[0] * pIp->src[5];
    pIp->inv[6] = pIp->src[3] * pIp->src[7] - pIp->src[4] * pIp->src[6];
    pIp->inv[7] = pIp->src[1] * pIp->src[6] - pIp->src[0] * pIp->src[7];
    pIp->inv[8] = pIp->src[0] * pIp->src[4] - pIp->src[1] * pIp->src[3];

    float32 rank = pIp->src[0] * pIp->inv[0] + pIp->src[1] * pIp->inv[3] + pIp->src[2] * pIp->inv[6];

    if ((FLT32_ZERO < rank) || (rank < -FLT32_ZERO)) {
        pIp->bAbleInv = TRUE32;

        /*@ loop invariant 0 <= i <= 8; // Corrected invariant
          loop variant 8 - i; // Corrected variant
        */
        for (siint08 i = 0; i < 9; i++) {
            pIp->inv[i] = pIp->inv[i] / rank;
        }
    } else {
        /*@ loop invariant 0 <= i <= 8; // Corrected invariant
          loop variant 8 - i; // Corrected variant
        */
        for (siint08 i = 0; i < 9; i++) {
            pIp->inv[i] = pIp->src[i];
        }
    }

    *(pIp->ret) = pIp->bAbleInv;
}
