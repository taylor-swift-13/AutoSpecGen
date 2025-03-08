
#include "CheckCal.h"
#include "B_TcProcess.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->tcaData + (0..3));
  assigns chksum; // Specify that chksum is modified
  ensures \valid(&chksum); // Ensure chksum is valid after modification
*/
void B_TcProcessFun(B_TcProcess *pIp)
{
    unint08 chksum;
    unint08 i;

    /*@ loop invariant 0 <= i < 4; // Updated to ensure valid index for tcaData
      loop variant 4 - i; 
    */
    for (i = 0; i < 4; i++) {
        /*@ assert \valid(pIp->tcaData + i); // Validity check for current index
        */
    }

    if ((pIp->tcaData[0] == 0xE1) && (pIp->tcaData[1] == 0x00))
    {
        /*@ 
          requires \valid(&(pIp->tcaData[0]));
          assigns chksum; // Specify that chksum is modified
        */
        IPCREATE(CheckCal, ipCheckCal, .len = 3, .pkv = &(pIp->tcaData[0]), .chksum = &chksum);
        IPCALL(ipCheckCal);

        if (pIp->tcaData[3] == chksum)
        {
            if (pIp->tcaData[2] == 0)
            {
                TR32_FLGMODE_VALUE(SAM_DAMP);
            }
            else if (pIp->tcaData[2] == 1)
            {
                TR32_FLGMODE_VALUE(SAM_CRUISE);
            }
            else
            {
                TR32_FLGMODE_VALUE(NOCTRL);
            }
        }
    }

    return;
}
