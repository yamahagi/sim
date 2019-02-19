#include <stdio.h>
#include <stdint.h>
#include "../../include/common.h"
#include "../../include/oc_sim.h"
#include "../../include/print_reg.h"


int main(void){

uint32_t ir = 0b00000000000000001000111111111111;
print_data(ir);
uint32_t si = get_si(ir);
                        if(((si>>15)&0x1)==1){
                                print_data((0xffff0000|(si&0xffff)));
                        }
                        else if(((si>>15)&0x1)==0){
                                print_data((0xffff&si));
                        }

ir = 0b00000000000000000100111111111111;
print_data(ir);
si = get_si(ir);
                        if(((si>>15)&0x1)==1){
                                print_data((0xffff0000|(si&0xffff)));
                        }
                        else if(((si>>15)&0x1)==0){
                                print_data((0xffff&si));
                        }


return 0;
}
