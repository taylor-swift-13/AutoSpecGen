
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ 
  requires \valid(pIp);
  ensures \true;
*/
void TcProcessFun(TcProcess *pIp)
{
    unint08 tcaData[32];
    unint32 GetUartData_ret;

    /*@
      assigns tcaData[0..31];
      assigns GetUartData_ret;
      ensures GetUartData_ret == 1 ==> \initialized(&tcaData[0]);
    */
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    if (GetUartData_ret == 1)
    {
        /*@
          assigns tcaData[0..31];
        */
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
