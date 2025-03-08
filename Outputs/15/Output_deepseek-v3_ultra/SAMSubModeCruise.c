
#include "SAMSubModeCruise.h"

/*@ 
  requires \valid(pIp);
  assigns pIp->mFWarning.CWsp;
  ensures pIp->countMode == 4000 ==> pIp->mFWarning.CWsp == \old(pIp->mFWarning.CWsp) || pIp->mFWarning.CWsp == TRUE;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    /*@ assert \valid(pIp); */
    if (pIp->countMode == 4000)
    {
        pIp->mFWarning.CWsp = TRUE;
    }

    return;
}
