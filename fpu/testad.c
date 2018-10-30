#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ftools.c"
#include "fpu.c"

int main(void){

int a = 0b10000000001110000000000000000000;
int b = 0b10000011000111111111111111111111;
float c = float_get(a)+float_get(b);
float d = float_get(fadd(a,b));

if((c!=0&&fabsf(c-d)>c*0.0001)){
                        for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&a)>>(31-im))&0x1);
                        }
                        printf("\n");
                        for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&b)>>(31-im))&0x1);
                        }
                        printf("\n");
                        for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&c)>>(31-im))&0x1);
                        }
                        printf("\n");
                        for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&d)>>(31-im))&0x1);
                        }
                        printf("\n");

                         printf("%f + %f = %fなのに%f\n", float_get(a),float_get(b),c,d);

}
return 0;
}
