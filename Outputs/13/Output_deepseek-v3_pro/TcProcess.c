
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@
  requires \valid(pIp);
  assigns tcaData[0..31], \at(GetUartData_ret, Post);
  ensures \at(GetUartData_ret, Post) == 0 || \at(GetUartData_ret, Post) == 1;
*/
void TcProcessFun(TcProcess *pIp)
{
    unint08 tcaData[32];

    unint32 GetUartData_ret;

    /*@
      assigns tcaData[0..3], \at(GetUartData_ret, Post);
      ensures \valid_read(tcaData + (0..3));
    */
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));

    /*@
      assigns \at(GetUartData_ret, Post);
      ensures \at(GetUartData_ret, Post) == 0 || \at(GetUartData_ret, Post) == 1;
    */
    IPCALL(ipGetUartData);

    if (GetUartData_ret == 1)
    {
        /*@
          assigns tcaData[0..31];
          ensures \valid_read(tcaData + (0..31));
        */
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);

        /*@
          assigns tcaData[0..31];
        */
        IPCALL(ipB_TcProcess);
    }

    return;
}
