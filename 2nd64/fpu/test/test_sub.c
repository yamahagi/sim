#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../ftools.h"
#include "../fpu.h"

#define NSTAGE 4

int jyou2(int a){
int b = a;
	while(1==1){
		if(b==1) break;
		if(b%2==1) break;
		b = b/2;
	}
	return b;
}

float ch23(float a){

int b = int_get(a);
int s = split_bit(b,31,31);
int e = split_bit(b,30,23);
int k = split_bit(b,22,0);
if(e<23){
return 0;
}
else{
int l = ((e-23)<<23)+k;
return *(float*)(&l);
}
}

int main(void){

int y;
float fx1,fx2,fy;

int i,j,k,it,jt;
int m1,m2;
int dum1,dum2;
int fybit;
int s1,s2;
int dy;
int tm;

int x1_reg[NSTAGE+1];
int x2_reg[NSTAGE+1];
int val[NSTAGE+1];

#define x1 x1_reg[0]
#define x2 x2_reg[0]

int counter1;
int counter2;
int counter3;
int counter = 0;
val[0]=0;
val[1]=0;
val[2]=0;
val[3]=0;
x1_reg[0] = 0;
x2_reg[0] = 0;
counter1 = 0;

counter1 = counter1+1;
counter1 = counter1+1;
for(i=0;i<255;i++){
   for(j=0;j<255;j++){
      for(s1=0;s1<2;s1++){
         for(s2=0;s2<2;s2++){
            for(it=0;it<10;it++){
		for(jt=0;jt<10;jt++){
		   switch(it){
			case 0:
				m1 = 0;
				break;
			case 1:			
				m1 = 1;
				break;
			case 2:			
				m1 = 2;
				break;
			case 3:			
				m1 = 7<<19;
				break;
			case 4:			
				m1 = 1<<23;
				break;
			case 5:			
				m1 = (1<<23) + 0x1fffff;
				break;
			case 6:			
				m1 = 0x7fffff;
				break;
			default:
				if(i==256){
					m1 = 0;
					dum1 = 0;
				}
				else{
					m1 = split_bit(rand(),22,0);
					dum1 = split_bit(rand(),9,0);
				}
				break;
		   }
		   switch(jt){
			case 0:
				m2 = 0;
				break;
			case 1:			
				m2 = 1;
				break;
			case 2:			
				m2 = 2;
				break;
			case 3:			
				m2 = 7<<19;
				break;
			case 4:			
				m2 = 1<<23;
				break;
			case 5:			
				m2 = (1<<23) + 0x1fffff;
				break;
			case 6:			
				m2 = 0x7fffff;
				break;
			default:
				if(i==256){
					m2 = 0;
					dum2 = 0;
				}
				else{
					m2 = split_bit(rand(),22,0);
					dum2 = split_bit(rand(),9,0);
				}
				break;
		   }

		   x1_reg[0] = (s1<<31)+(split_bit(i,7,0)<<23)+m1;
		   x2_reg[0] = (s2<<31)+(split_bit(j,7,0)<<23)+m2;

		
		float am = *(float*)(&x1_reg[0]);
		float bm = *(float*)(&x2_reg[0]);
		float cm = am-bm;
		int n = (fsub(x1_reg[0],x2_reg[0]));
                float dm = *(float*)(&n);
                float diff = fabs(cm-dm);
		int yp = 0x800000;
                float yps = *(float*)(&yp);
                float maxa = ch23(am);
                float maxb = ch23(bm);
                float maxab = ch23(cm);

		if((!(split_bit(*(int*)(&cm),30,23)==0&&split_bit(*(int*)(&dm),30,23)==0))&&(diff>maxa&&diff>maxb&&diff>maxab&&diff>yps)&&(!isinf(bm))&&(!isinf(cm))&&(!isinf(am))){
			
			for(int im=0;im<32;im++){
				printf("%d",(*(int*)(&am)>>(31-im))&0x1);
			}
			printf("\n");
			for(int im=0;im<32;im++){
				printf("%d",(*(int*)(&bm)>>(31-im))&0x1);
			}
			printf("\n");
			for(int im=0;im<32;im++){
				printf("%d",(*(int*)(&cm)>>(31-im))&0x1);
			}
			printf("\n");
			for(int im=0;im<32;im++){
				printf("%d",(*(int*)(&dm)>>(31-im))&0x1);
			}
			printf("\n");
			
			 printf("%f-%f = %fなのに%f\n", am,bm,cm,dm);
			counter +=1;
		}
		}
		}
	      }
	    }
	}
}

printf("count %d\n",counter);

return 0;




}
