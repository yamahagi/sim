#include <stdio.h>
#include <stdint.h>
#include "../../include/oc_sim.h"


int main(void){

uint64_t ir = 0b0100110010100000000000000000000010111111000000000000000000000000;

printf("%d",get_siw(ir));


return 0;
}
