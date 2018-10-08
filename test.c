#include <stdio.h>
#include "include/common.h"
#include "include/oc_sim.h"

int main(void){

int b = 0b00000000011001000000000000000001;
int a = get_opcode(b);
int c = get_rsi(b);
int d = get_rti(b);

printf("%d",a);
printf("%d",c);
printf("%d",d);


}
