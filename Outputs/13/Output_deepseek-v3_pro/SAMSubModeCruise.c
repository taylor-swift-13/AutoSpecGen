
#include "SAMSubModeCruise.h"

/*@
  requires \valid(pIp);
  assigns pIp->mFWarning.CWsp;
  behavior countMode_4000:
    assumes pIp->countMode == 4000;
    ensures pIp->mFWarning.CWsp == \true;
  behavior countMode_not_4000:
    assumes pIp->countMode != 4000;
    ensures pIp->mFWarning.CWsp == \old(pIp->mFWarning.CWsp);
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    if (pIp->countMode == 4000)
    {
        pIp->mFWarning.CWsp = TRUE;
    }

    return;
}
