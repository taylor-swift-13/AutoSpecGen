
#include "SAMSubModeCruise.h"

/*@ 
    requires \valid(pIp);
    requires pIp->countMode == 4000 ==> \valid(&pIp->mFWarning);
    ensures pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == TRUE;
    assigns pIp->mFWarning.CWsp;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    if (pIp -> countMode == 4000)
    {
        pIp -> mFWarning.CWsp = TRUE ;
    }

    return ;
}
