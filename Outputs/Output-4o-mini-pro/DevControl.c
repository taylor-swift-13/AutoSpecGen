
#include "DevControl.h"

/*@ 
  requires pIp != \null; 
  ensures \result == \null; 
  assigns \nothing; 
*/
void DevControlFun(DevControl *pIp)
{
    /*@ 
      ensures \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x881A, 0xEB92);
    
    /*@ 
      ensures \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8000, 0x01);
    
    /*@ 
      ensures \valid(pIp); 
      assigns \nothing; 
    */
    ADDR_WRITE(0x8008, 0xFC);

    return ;
}
