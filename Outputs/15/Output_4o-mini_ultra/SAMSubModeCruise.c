
#include "SAMSubModeCruise.h"

/*@ 
  requires \valid(pIp);
  ensures \valid(&pIp->mFWarning.CWsp); // Ensure the address of the field is valid
  assigns pIp->mFWarning.CWsp;
*/
void SAMSubModeCruiseFun(SAMSubModeCruise *pIp)
{
    // No loop present, so no loop annotations are needed.
	if (pIp->countMode == 4000)
	{
		pIp->mFWarning.CWsp = TRUE;
	}

	return;
}
