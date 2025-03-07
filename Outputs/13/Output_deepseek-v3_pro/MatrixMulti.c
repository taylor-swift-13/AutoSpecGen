
#include "MatrixMulti.h"

/*@
  requires \valid(pIp);
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  requires pIp->nrow > 0 && pIp->ncol > 0 && pIp->nrc > 0;
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
  ensures \forall unint08 ir, jc; 0 <= ir < pIp->nrow && 0 <= jc < pIp->ncol ==>
          pIp->product[ir * pIp->ncol + jc] == 
          (float) (\sum(0, pIp->nrc - 1, \lambda unint08 k; (float) (pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + jc])));
*/
void MatrixMultiFun(MatrixMulti *pIp)
{
    unint08 ir;
    unint08 jc;
    unint08 nk;
    unint08 index;

    /*@
      loop invariant 0 <= ir <= pIp->nrow;
      loop invariant \forall unint08 i, j; 0 <= i < ir && 0 <= j < pIp->ncol ==>
                     pIp->product[i * pIp->ncol + j] == 
                     (float) (\sum(0, pIp->nrc - 1, \lambda unint08 k; (float) (pIp->faciend[i * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + j])));
      loop assigns ir, jc, nk, index, pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
      loop variant pIp->nrow - ir;
    */
    for (ir = 0; ir < pIp->nrow; ir++)
    {
        /*@
          loop invariant 0 <= jc <= pIp->ncol;
          loop invariant \forall unint08 j; 0 <= j < jc ==>
                         pIp->product[ir * pIp->ncol + j] == 
                         (float) (\sum(0, pIp->nrc - 1, \lambda unint08 k; (float) (pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + j])));
          loop assigns jc, nk, index, pIp->product[ir * pIp->ncol + 0 .. pIp->ncol - 1];
          loop variant pIp->ncol - jc;
        */
        for (jc = 0; jc < pIp->ncol; jc++)
        {
            index = ir * pIp->ncol + jc;
            pIp->product[index] = 0.0f;

            /*@
              loop invariant 0 <= nk <= pIp->nrc;
              loop invariant pIp->product[index] == 
                             (float) (\sum(0, nk - 1, \lambda unint08 k; (float) (pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + jc])));
              loop assigns nk, pIp->product[index];
              loop variant pIp->nrc - nk;
            */
            for (nk = 0; nk < pIp->nrc; nk++)
            {
                pIp->product[index] = pIp->product[index] + pIp->faciend[ir * pIp->nrc + nk] * pIp->multiplier[nk * pIp->ncol + jc];
            }
        }
    }

    return;
}
