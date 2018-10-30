#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ftools.c"
#include "fpu.c"

int main(void){

int a = 0b10000000100111000101101110100010;
uint32_t b =0b10000000100111000101101110100010;
b = a;

int a1 = a>>1;
int b1 = b>>1;

int a132 = a>>31;
int b132 = b>>31;

printf("a1   ");
for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&a1)>>(31-im))&0x1);
                        }

printf("\n");
printf("b1   ");
for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&b1)>>(31-im))&0x1);
                        }

printf("\n");
printf("a132  ");
for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&a132)>>(31-im))&0x1);
                        }

printf("\n");
printf("b132  ");
for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&b132)>>(31-im))&0x1);
                        }
}
