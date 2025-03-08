
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ 
  requires \valid(pIp);
  assigns tcaData[0..31], GetUartData_ret; // Correctly specifies the modified variables
*/
void TcProcessFun(TcProcess *pIp) 
{
    unint08 tcaData[32];

    unint32 GetUartData_ret;
    
    /*@ 
      assigns tcaData[0..31], GetUartData_ret; 
      ensures GetUartData_ret == 1 ==> \valid(pIp);
    */
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    /*@ 
      ensures GetUartData_ret == 1 ==> \valid(pIp);
    */
    if (GetUartData_ret == 1)
    {
        /*@ 
          assigns tcaData[0..31]; // Correctly specifies the modified variable
        */
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
