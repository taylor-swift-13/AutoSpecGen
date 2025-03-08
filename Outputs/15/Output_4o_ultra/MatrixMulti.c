
#include "MatrixMulti.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
*/
void MatrixMultiFun(MatrixMulti *pIp)
{
    unint08 ir;
    unint08 jc;
    unint08 nk;
    unint08 index;

    /*@ 
      loop invariant 0 <= ir <= pIp->nrow;
      loop assigns ir, jc, nk, index, pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
      loop variant pIp->nrow - ir;
    */
    for (ir = 0; ir < pIp->nrow; ir++)
    {
        /*@ 
          loop invariant 0 <= jc <= pIp->ncol;
          loop invariant \forall unint08 i, j; (i < ir || (i == ir && j < jc)) ==> pIp->product[i * pIp->ncol + j] == \sum(0, pIp->nrc, \lambda integer k; pIp->faciend[i * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + j]);
          loop assigns jc, nk, index, pIp->product[ir * pIp->ncol .. ir * pIp->ncol + pIp->ncol - 1];
          loop variant pIp->ncol - jc;
        */
        for (jc = 0; jc < pIp->ncol; jc++)
        {
            index = ir * pIp->ncol + jc;

            pIp->product[index] = 0.0f;

            /*@ 
              loop invariant 0 <= nk <= pIp->nrc;
              loop invariant pIp->product[index] == \sum(0, nk, \lambda integer k; pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + jc]);
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
