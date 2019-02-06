#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../ftools.h"
#include "../feq.h"

float ch22(float a){
int b = int_get(a);
int s = split_bit(b,31,31);
int e = split_bit(b,30,23);
int k = split_bit(b,22,0);
if(e<23){
return 0;
}
else{
int l = ((e-22)<<23)+k;
return *(float*)(&l);
}
}


int main(void){

int a = 0b10000100001110000000100000000000;
int b = 0b10000011000111111111111111111111;
a = 0b10000000010101011011111010011010;
b = 0b11010011100000000000000000000000;
float t = *(float *)(&(a));
float l = *(float *)(&(b));
int real;
if(t == l){
	real = 1;
}
else{
	real = 0;
}
int k = (feq(a,b));
printf("real %d\n",real);
printf("feq %d\n",k);

/*
float d = *(float *)(&k);
			 printf("diff ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&diff)>>(31-im))&0x1);
                        }
                        printf("\n");
                        printf("maxab ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&maxab)>>(31-im))&0x1);
                        }
                        printf("\n");
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
			printf("      ");
                        for(int im=0;im<32;im++){
				if(im==1||im==9){
					printf(" ");
				}
                                printf("%d",(*(int*)(&b)>>(31-im))&0x1);
                        }
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

                         printf("%f + %f = %fなのに%f\n", float_get(a),float_get(b),c,d);
*/
return 0;
}
