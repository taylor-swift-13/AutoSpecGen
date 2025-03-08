
#include "Delay.h"
#include "DiviationToFloat.h"
#include "SendUartData.h"
#include "GetUartData.h"
#include "GyroStateGet.h"

/*@ 
  requires \valid(pIp);
  requires \valid(pIp->wa + (0..pIp->NumGyro - 1));
  requires \valid(pIp->stateFlag + (0..pIp->NumGyro - 1));
  ensures \forall integer i; 0 <= i < pIp->NumGyro ==> \valid(pIp->wa + i) && \valid(pIp->stateFlag + i);
  assigns pIp->wa[0..pIp->NumGyro-1], pIp->stateFlag[0..pIp->NumGyro-1];
*/
void GyroStateGetFun(GyroStateGet *pIp)
{
    /*@ loop variant 30; */
    for (unint32 i = 0; i < 30; i++) {
        unint08 gyroSendData[2]; // Declare gyroSendData locally
        gyroSendData[0] = 0xEB;
        gyroSendData[1] = 0x91;

        IPCREATE(SendUartData, ipSendUartData, .data = &gyroSendData[0], .len =  2, .addr =  0x881A);
        IPCALL(ipSendUartData);

        IPCREATE(Delay, ipDelay, .delaytime = 500);
        IPCALL(ipDelay);

        unint32 GetUartData_ret;
        unint08 gyroRecvData[30]; // Declare gyroRecvData locally
        /*@ requires \valid(gyroRecvData + (0..29)); */
        IPCREATE(GetUartData, ipGetUartData, .len = 30, .addr =  0x881C, .data =  &gyroRecvData[0], .ret = &(GetUartData_ret));
        IPCALL(ipGetUartData);

        if ((gyroRecvData[0] == 0xEB) && (gyroRecvData[1] == 0x91)) {
            /*@ loop invariant 0 <= j < pIp->NumGyro;
              loop variant pIp->NumGyro - j; */
            for (unint32 j = 0; j < pIp->NumGyro; j++) {
                float32 DiviationToFloat_ret;
                IPCREATE(DiviationToFloat, ipDiviationToFloat, .input = (gyroRecvData[2 + j*2] << 8) | (gyroRecvData[2 + j*2 + 1]), .ret = &(DiviationToFloat_ret));
                IPCALL(ipDiviationToFloat);

                pIp->wa[j] = DiviationToFloat_ret;
                pIp->stateFlag[j] = gyroRecvData[19 + j];
            }
        }
    }

    return;
}
