#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../ftools.h"
#include "../fsqrt.h"
#include "../fi.h"
#include "math.h"
float ch20(float a){
int b = int_get(a);
int s = split_bit(b,31,31);
int e = split_bit(b,30,23);
int k = split_bit(b,22,0);
if(e<20){
return 0;
}
else{
int l = ((e-20)<<23)+k;
return *(float*)(&l);
}
}


int main(void){

int a = 0b11001110111111111111111111111111;
int  ai = *(float*)(&a);
int c = ftoi(a);

print_bit(ai);
print_bit(c);

/*
			 printf("diff ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&diff)>>(31-im))&0x1);
                        }
                        printf("\n");
                        printf("max ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&max)>>(31-im))&0x1);
                        }
                        printf("yp ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&yps)>>(31-im))&0x1);
                        }
                        printf("\n");




			printf("      ");
                        for(int im=0;im<32;im++){
				if(im==1||im==9){
					printf(" ");
				}
                                printf("%d",(*(int*)(&a)>>(31-im))&0x1);
                        }
                        printf("\n");
                        printf("\n");
			printf("      ");
                        for(int im=0;im<32;im++){
				if(im==1||im==9){
					printf(" ");
				}
                                printf("%d",(*(int*)(&c)>>(31-im))&0x1);
                        }
                        printf("\n");
			printf("      ");
                        for(int im=0;im<32;im++){
				if(im==1||im==9){
					printf(" ");
				}
                                printf("%d",(*(int*)(&d)>>(31-im))&0x1);
                        }
                        printf("\n");

                         printf("sqrt %f  = %fなのに%f\n", float_get(a),c,d);
*/
return 0;
}
