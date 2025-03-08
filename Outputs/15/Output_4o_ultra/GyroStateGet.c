
#include "Delay.h"
#include "DiviationToFloat.h"
#include "SendUartData.h"
#include "GetUartData.h"
#include "GyroStateGet.h"

/*@ 
requires \valid(pIp);
requires \valid(pIp->wa + (0..pIp->NumGyro-1));
requires \valid(pIp->stateFlag + (0..pIp->NumGyro-1));
assigns ((char*)pIp->wa)[0..sizeof(float32)*(pIp->NumGyro)-1], ((char*)pIp->stateFlag)[0..sizeof(unint08)*(pIp->NumGyro)-1];
ensures \forall int i; 0 <= i < pIp->NumGyro ==> pIp->wa[i] == \old(pIp->wa[i]);
ensures \forall int i; 0 <= i < pIp->NumGyro ==> pIp->stateFlag[i] == \old(pIp->stateFlag[i]);
*/
void GyroStateGetFun(GyroStateGet *pIp)
{
    unint32 i;
    unint08 gyroRecvData[30];
    unint08 gyroSendData[2];

    gyroSendData[0] = 0xEB;
    gyroSendData[1] = 0x91;

    IPCREATE(SendUartData, ipSendUartData, .data = &gyroSendData[0], .len =  2, .addr =  0x881A);
    IPCALL(ipSendUartData);

    IPCREATE(Delay, ipDelay, .delaytime = 500);
    IPCALL(ipDelay);

    unint32 GetUartData_ret;
    IPCREATE(GetUartData, ipGetUartData, .len = 30, .addr =  0x881C, .data =  &gyroRecvData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    if ( (gyroRecvData[0] == 0xEB) && (gyroRecvData[1] == 0x91) )
    {
        /*@ loop invariant 0 <= i <= pIp->NumGyro;
            loop invariant \forall integer j; 0 <= j < i ==> pIp->wa[j] == \at(pIp->wa[j], Pre);
            loop invariant \forall integer j; 0 <= j < i ==> pIp->stateFlag[j] == \at(pIp->stateFlag[j], Pre);
            loop assigns i, pIp->wa[0..pIp->NumGyro-1], pIp->stateFlag[0..pIp->NumGyro-1];
            loop variant pIp->NumGyro - i;
        */
        for ( i = 0; i < pIp->NumGyro; i++ )
        {
            float32 DiviationToFloat_ret;
            IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = (gyroRecvData[2 + i*2] << 8) | (gyroRecvData[2 + i*2 + 1]), .ret = &(DiviationToFloat_ret));
            IPCALL(ipDiviationToFloat);

            pIp->wa[i] = DiviationToFloat_ret;
            pIp->stateFlag[i] = gyroRecvData[19 + i];
        }
    }

    return;
}
