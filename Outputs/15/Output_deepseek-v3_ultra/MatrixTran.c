
#include "MatrixTran.h"

/*@ axiomatic MatrixProperties {
      predicate valid_matrix(float32* mat, integer nrow, integer ncol) = 
         \valid(mat + (0..nrow*ncol-1));
      predicate valid_transpose(float32* tran, integer nrow, integer ncol) = 
         \valid(tran + (0..nrow*ncol-1));
    }
*/

/*@ requires \valid(pIp);
    requires valid_matrix(pIp->mat, pIp->nrow, pIp->ncol);
    requires valid_transpose(pIp->tran, pIp->ncol, pIp->nrow);
    ensures \forall unint08 i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==>
            *(pIp->tran + j * pIp->nrow + i) == \old(*(pIp->mat + i * pIp->ncol + j));
    assigns pIp->tran[0..(pIp->ncol * pIp->nrow - 1)];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    // Ghost variable to store the initial state of the matrix
    /*@ ghost float32 mat_initial[pIp->nrow * pIp->ncol]; */
    /*@ assert \forall unint08 k, l; 0 <= k < pIp->nrow && 0 <= l < pIp->ncol ==>
              mat_initial[k * pIp->ncol + l] == *(pIp->mat + k * pIp->ncol + l); */

    /*@ loop invariant 0 <= i <= pIp->nrow;
        loop invariant \forall unint08 k, l; 0 <= k < i && 0 <= l < pIp->ncol ==>
                       *(pIp->tran + l * pIp->nrow + k) == mat_initial[k * pIp->ncol + l];
        loop assigns i, j, pIp->tran[0..(pIp->ncol * pIp->nrow - 1)];
        loop variant pIp->nrow - i;
    */
    for (i = 0; i < pIp->nrow; i++)
    {
        /*@ loop invariant 0 <= j <= pIp->ncol;
            loop invariant \forall unint08 k; 0 <= k < j ==>
                           *(pIp->tran + k * pIp->nrow + i) == mat_initial[i * pIp->ncol + k];
            loop assigns j, pIp->tran[0..(pIp->ncol * pIp->nrow - 1)];
            loop variant pIp->ncol - j;
        */
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
