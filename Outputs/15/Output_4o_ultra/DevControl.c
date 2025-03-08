
#include "DevControl.h"

/*@ 
  requires \valid(pIp);
  assigns *(volatile unsigned int*)0x881A, *(volatile unsigned int*)0x8000, *(volatile unsigned int*)0x8008;
*/
void DevControlFun(DevControl *pIp)
{
    /*@ assert \valid((volatile unsigned int*)0x881A); */
    ADDR_WRITE(0x881A, 0xEB92);

    /*@ assert \valid((volatile unsigned int*)0x8000); */
    ADDR_WRITE(0x8000, 0x01);

    /*@ assert \valid((volatile unsigned int*)0x8008); */
    ADDR_WRITE(0x8008, 0xFC);

    return;
}
