
#include "B_TcProcess.h"
#include "GetUartData.h"
#include "TcProcess.h"

/*@ 
  requires pIp != \null; 
  ensures \true; 
  assigns \nothing; 
*/
void TcProcessFun(TcProcess *pIp)
{
    /*@ 
      requires \valid(pIp); 
      ensures \forall integer i; 0 <= i < 32 ==> \valid(tcaData + i);
      assigns tcaData[0 .. 31]; 
    */
    unint08 tcaData[32];

    unint32 GetUartData_ret;
    
    /*@ 
      ensures GetUartData_ret == 1 ==> \valid(tcaData + (0 .. 31)); 
      assigns \nothing; 
    */
    IPCREATE(GetUartData, ipGetUartData, .len = 4, .addr =  0x88DA, .data =  &tcaData[0], .ret = &(GetUartData_ret));
    IPCALL(ipGetUartData);

    /*@ 
      behavior success:
        assumes GetUartData_ret == 1;
        ensures \valid(tcaData + (0 .. 31)); 
        assigns \nothing;
    */
    if (GetUartData_ret == 1)
    {
        /*@ 
          assigns \nothing; 
        */
        IPCREATE(B_TcProcess, ipB_TcProcess, .tcaData = &tcaData[0]);
        IPCALL(ipB_TcProcess);
    }

    return;
}
