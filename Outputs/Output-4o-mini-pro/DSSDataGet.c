
#include "Delay.h"
#include "DiviationToFloat.h"
#include "DSSDataGet.h"

/*@ 
  requires pIp != \null;
  requires \valid(pIp->pDSSData);
  ensures pIp->pDSSData->stateFlag_A == (ADDR_READ(0xC000) & 0x1);
  ensures pIp->pDSSData->stateFlag_B == (ADDR_READ(0xC000) & 0x2);
  assigns pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B, pIp->pDSSData->royaw, pIp->pDSSData->piyaw;
*/
void DSSDataGetFun(DSSDataGet *pIp)
{
    unint08 si;
    unint08 tmp_ad_start;
    unint08 stateFlag;
    unint16 wd;
    unint16 tmp_hi8, tmp_lo4;

    pIp -> pDSSData->stateFlag_A = 0;
    pIp -> pDSSData->stateFlag_B = 0;

    pIp -> pDSSData->flgSP = (ADDR_READ(0xE000) >> 5) & 0x01;

    /*@
      loop invariant 0 <= si <= 2;
      loop assigns si, pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B;
      loop variant 2 - si;
    */
    for ( si = 0; si < 2; si++ )
    {
        stateFlag = ADDR_READ(0xC000) & 0x3;

        if ((stateFlag & 0x1) == 0x1)
        {
            pIp -> pDSSData->stateFlag_A = 1;
        }

        if ((stateFlag & 0x2) == 0x2)
        {
            pIp -> pDSSData->stateFlag_B = 1;
        }
    }

    if (stateFlag > 0)
    {
        ADDR_WRITE(0xA100, (0xC + si));

        IPCREATE(Delay, ipDelay1, .delaytime = 500);
        IPCALL(ipDelay1);

        tmp_ad_start = ADDR_READ(0xA000);

        IPCREATE(Delay, ipDelay2, .delaytime = 40);
        IPCALL(ipDelay2);

        tmp_lo4 = ADDR_READ(0xA003);
        tmp_hi8 = ADDR_READ(0xA001);

        wd = ((tmp_hi8 << 4) & 0x0FF0) | ((tmp_lo4 >> 4) & 0xF);
        
        /*@
          behavior case_0:
            assumes si == 0;
            ensures pIp->pDSSData->royaw == \result;
          behavior case_1:
            assumes si == 1;
            ensures pIp->pDSSData->piyaw == \result;
        */
        switch(si)
        {
            case 0:
            {
                float32 DiviationToFloat_ret;
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                pIp -> pDSSData->royaw = DiviationToFloat_ret;
                break;
            }
            case 1:
            {
                float32 DiviationToFloat_ret;
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                pIp -> pDSSData->piyaw = DiviationToFloat_ret;
                break;
            }
            default:
                break;
        }
    }

    return;
}
