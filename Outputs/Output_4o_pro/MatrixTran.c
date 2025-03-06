
#include "MatrixTran.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->mat + (0 .. pIp->nrow * pIp->ncol - 1));
  requires \valid(pIp->tran + (0 .. pIp->nrow * pIp->ncol - 1));
  requires pIp->nrow > 0;
  requires pIp->ncol > 0;
  ensures \forall unsigned char i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==> 
          *(pIp->tran + j * pIp->nrow + i) == *(pIp->mat + i * pIp->ncol + j);
  assigns pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unsigned char i;
    unsigned char j;

    /*@
      loop invariant 0 <= i <= pIp->nrow;
      loop assigns i, j, pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@
          loop invariant 0 <= j <= pIp->ncol;
          loop invariant \forall unsigned char k; 0 <= k < j ==> 
                          *(pIp->tran + k * pIp->nrow + i) == *(pIp->mat + i * pIp->ncol + k);
          loop assigns j, pIp->tran[0 .. pIp->nrow * pIp->ncol - 1];
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
