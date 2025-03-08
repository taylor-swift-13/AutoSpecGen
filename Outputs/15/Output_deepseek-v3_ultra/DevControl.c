
#include "DevControl.h"

/*@ axiomatic MemoryOperations {
      logic integer memory_value{L}(integer addr) reads \at(addr, L);
      axiom write_effect:
        \forall integer addr, value; 
        \at(memory_value{Pre}, addr) != \at(memory_value{Post}, addr) ==> 
        \at(memory_value{Post}, addr) == value;
    }
*/

/*@ requires \valid(pIp);
    assigns \nothing;
    ensures \forall integer addr; 
            addr == 0x881A ==> memory_value{Post}(addr) == 0xEB92;
    ensures \forall integer addr; 
            addr == 0x8000 ==> memory_value{Post}(addr) == 0x01;
    ensures \forall integer addr; 
            addr == 0x8008 ==> memory_value{Post}(addr) == 0xFC;
*/
void DevControlFun(DevControl *pIp)
{
    /*@ assert \valid(pIp); */

    ADDR_WRITE(0x881A, 0xEB92);

    /*@ assert memory_value{Here}(0x881A) == 0xEB92; */

    ADDR_WRITE(0x8000, 0x01);

    /*@ assert memory_value{Here}(0x8000) == 0x01; */

    ADDR_WRITE(0x8008, 0xFC);

    /*@ assert memory_value{Here}(0x8008) == 0xFC; */

    return ;
}
