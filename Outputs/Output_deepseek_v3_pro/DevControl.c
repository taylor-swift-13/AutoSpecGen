
#include "DevControl.h"

/*@ 
  requires \valid(pIp);
  assigns *(unsigned short*)0x881A, *(unsigned short*)0x8000, *(unsigned short*)0x8008;
*/
void DevControlFun(DevControl *pIp)
{
    // Write operations to specific memory addresses
    ADDR_WRITE(0x881A, 0xEB92);

    ADDR_WRITE(0x8000, 0x01);

    ADDR_WRITE(0x8008, 0xFC);

    return ;
}
