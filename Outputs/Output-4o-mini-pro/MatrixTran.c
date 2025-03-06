
#include "MatrixTran.h"

/*@ 
    requires \valid(pIp);
    requires \valid(pIp->mat + (0..(pIp->nrow * pIp->ncol - 1)));
    requires \valid(pIp->tran + (0..(pIp->nrow * pIp->ncol - 1)));
    requires pIp->nrow > 0;
    requires pIp->ncol > 0;
    ensures \forall int i, j; 0 <= i < pIp->nrow && 0 <= j < pIp->ncol ==> 
        *(pIp->tran + j * pIp->nrow + i) == *(pIp->mat + i * pIp->ncol + j);
    assigns pIp->tran[0..(pIp->nrow * pIp->ncol - 1)];
*/
void MatrixTranFun(MatrixTran *pIp)
{
    unint08 i;
    unint08 j;

    for (i = 0; i < pIp->nrow; i++)
    {
        for (j = 0; j < pIp->ncol; j++)
        {
            *(pIp->tran + j * pIp->nrow + i) = *(pIp->mat + i * pIp->ncol + j);
        }
    }

    return;
}
