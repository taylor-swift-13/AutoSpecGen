
#include "DevControl.h"

/*@ 
  requires \valid(pIp);
  ensures \true;
  assigns \nothing;
*/
void DevControlFun(DevControl *pIp)
{
    /*@ assigns *((unsigned char *)0x881A); */
    ADDR_WRITE(0x881A, 0xEB92);

    /*@ assigns *((unsigned char *)0x8000); */
    ADDR_WRITE(0x8000, 0x01);

    /*@ assigns *((unsigned char *)0x8008); */
    ADDR_WRITE(0x8008, 0xFC);

    return;
}
