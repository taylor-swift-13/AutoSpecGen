
#include "SAMSubModeCruise.h"

/*@
  requires \valid(pIp);
  requires \valid(&(pIp->mFWarning));
  ensures pIp->countMode != 4000 ==> pIp->mFWarning.CWsp == \old(pIp->mFWarning.CWsp);
  ensures pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == TRUE;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    if (pIp->countMode == 4000)
    {
        pIp->mFWarning.CWsp = TRUE;
    }

    return;
}
