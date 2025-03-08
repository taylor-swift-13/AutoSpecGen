
#include "Delay.h"
#include "DiviationToFloat.h"
#include "DSSDataGet.h"

/*@ axiomatic MemoryAccess {
      logic integer ADDR_READ(integer addr) reads *((char*)addr);
      logic integer ADDR_WRITE(integer addr, integer value) writes *((char*)addr);
   }
*/

/*@ requires \valid(pIp) && \valid(pIp->pDSSData);
    assigns pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B, pIp->pDSSData->flgSP,
            pIp->pDSSData->royaw, pIp->pDSSData->piyaw, *((char*)0xE000), *((char*)0xC000),
            *((char*)0xA100), *((char*)0xA000), *((char*)0xA003), *((char*)0xA001);
*/
void DSSDataGetFun(DSSDataGet *pIp)
{
    unint08 si;
    unint08 tmp_ad_start;
    unint08 stateFlag;
    unint16 wd;
    unint16 tmp_hi8, tmp_lo4;

    /*@ assigns pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B;
        ensures pIp->pDSSData->stateFlag_A == 0 && pIp->pDSSData->stateFlag_B == 0;
    */
    pIp->pDSSData->stateFlag_A = 0;
    pIp->pDSSData->stateFlag_B = 0;

    /*@ assigns pIp->pDSSData->flgSP;
        ensures pIp->pDSSData->flgSP == ((ADDR_READ(0xE000) >> 5) & 0x01);
    */
    pIp->pDSSData->flgSP = (ADDR_READ(0xE000) >> 5) & 0x01;

    /*@ loop invariant 0 <= si <= 2;
        loop assigns si, stateFlag, pIp->pDSSData->stateFlag_A, pIp->pDSSData->stateFlag_B;
        loop variant 2 - si;
    */
    for (si = 0; si < 2; si++)
    {
        /*@ assigns stateFlag;
            ensures stateFlag == (ADDR_READ(0xC000) & 0x3);
        */
        stateFlag = ADDR_READ(0xC000) & 0x3;

        if ((stateFlag & 0x1) == 0x1)
        {
            /*@ assigns pIp->pDSSData->stateFlag_A;
                ensures pIp->pDSSData->stateFlag_A == 1;
            */
            pIp->pDSSData->stateFlag_A = 1;
        }

        if ((stateFlag & 0x2) == 0x2)
        {
            /*@ assigns pIp->pDSSData->stateFlag_B;
                ensures pIp->pDSSData->stateFlag_B == 1;
            */
            pIp->pDSSData->stateFlag_B = 1;
        }
    }

    if (stateFlag > 0)
    {
        /*@ assigns *((char*)0xA100);
            ensures *((char*)0xA100) == (0xC + si);
        */
        ADDR_WRITE(0xA100, (0xC + si));

        IPCREATE(Delay, ipDelay, .delaytime = 500);
        IPCALL(ipDelay);

        /*@ assigns tmp_ad_start;
            ensures tmp_ad_start == ADDR_READ(0xA000);
        */
        tmp_ad_start = ADDR_READ(0xA000);

        IPCREATE(Delay, ipDelay, .delaytime = 40);
        IPCALL(ipDelay);

        /*@ assigns tmp_lo4;
            ensures tmp_lo4 == ADDR_READ(0xA003);
        */
        tmp_lo4 = ADDR_READ(0xA003);

        /*@ assigns tmp_hi8;
            ensures tmp_hi8 == ADDR_READ(0xA001);
        */
        tmp_hi8 = ADDR_READ(0xA001);

        /*@ assigns wd;
            ensures wd == ((tmp_hi8 << 4) & 0x0FF0) | ((tmp_lo4 >> 4) & 0xF);
        */
        wd = ((tmp_hi8 << 4) & 0x0FF0) | ((tmp_lo4 >> 4) & 0xF);

        switch (si)
        {
            case 0:
            {
                float32 DiviationToFloat_ret;
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                /*@ assigns pIp->pDSSData->royaw;
                    ensures pIp->pDSSData->royaw == DiviationToFloat_ret;
                */
                pIp->pDSSData->royaw = DiviationToFloat_ret;
                break;
            }
            case 1:
            {
                float32 DiviationToFloat_ret;
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = wd, .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                /*@ assigns pIp->pDSSData->piyaw;
                    ensures pIp->pDSSData->piyaw == DiviationToFloat_ret;
                */
                pIp->pDSSData->piyaw = DiviationToFloat_ret;
                break;
            }
            default:
                break;
        }
    }

    return;
}
