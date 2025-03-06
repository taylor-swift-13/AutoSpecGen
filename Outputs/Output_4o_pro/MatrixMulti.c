
#include "MatrixMulti.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->faciend + (0 .. pIp->nrow * pIp->nrc - 1));
  requires \valid(pIp->multiplier + (0 .. pIp->nrc * pIp->ncol - 1));
  requires \valid(pIp->product + (0 .. pIp->nrow * pIp->ncol - 1));
  requires pIp->nrow > 0;
  requires pIp->ncol > 0;
  requires pIp->nrc > 0;
  assigns pIp->product[0 .. pIp->nrow * pIp->ncol - 1];
  ensures \forall int ir, jc; 0 <= ir < pIp->nrow && 0 <= jc < pIp->ncol ==>
            pIp->product[ir * pIp->ncol + jc] == \sum(int nk; 0 <= nk < pIp->nrc; 
            pIp->faciend[ir * pIp->nrc + nk] * pIp->multiplier[nk * pIp->ncol + jc]);
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
    */
    for (ir = 0; ir < pIp->nrow; ir++)
    {
        /*@
          loop invariant 0 <= jc <= pIp->ncol;
          loop assigns jc, nk, index, pIp->product[ir * pIp->ncol .. ir * pIp->ncol + pIp->ncol - 1];
        */
        for (jc = 0; jc < pIp->ncol; jc++)
        {
            index = ir * pIp->ncol + jc;
            pIp->product[index] = 0.0f;

            /*@
              loop invariant 0 <= nk <= pIp->nrc;
              loop invariant pIp->product[index] == \sum(int k; 0 <= k < nk; 
                pIp->faciend[ir * pIp->nrc + k] * pIp->multiplier[k * pIp->ncol + jc]);
              loop assigns nk, pIp->product[index];
            */
            for (nk = 0; nk < pIp->nrc; nk++)
            {
                pIp->product[index] = pIp->product[index] + pIp->faciend[ir * pIp->nrc + nk] * pIp->multiplier[nk * pIp->ncol + jc];
            }
        }
    }

    return;
}
