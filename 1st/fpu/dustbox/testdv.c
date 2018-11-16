#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ftools.h"
#include "fdiv2.h"
#include "fdiv.h"

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

int a = 0b00000000010110101100100010100010;
int b = 0b10000000011101100110011110001100;
float t = *(float *)(&(a));
float l = *(float *)(&(b));
float c = t/l;
int k = (fdiv(a,b));
 int yp = 0x800000;
                float yps = *(float*)(&yp);
                float maxa = ch20(t);
                float maxb = ch20(l);
                float maxab = ch20(c);
		float kf = *(float*)(&k);
		float diff = fabs(c-kf);
		 if((diff>maxab&&diff>yps)){
			printf("boom\n");
		}



float d = *(float *)(&k);
			 printf("diff ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&diff)>>(31-im))&0x1);
                        }
                        printf("\n");
                        printf("maxa ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&maxa)>>(31-im))&0x1);
                        }
                        printf("\n");
                        printf("maxb ");
                         for(int im=0;im<32;im++){
                                printf("%d",(*(int*)(&maxb)>>(31-im))&0x1);
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

                         printf("%f +/ %f = %fなのに%f\n", float_get(a),float_get(b),c,d);

return 0;
}
