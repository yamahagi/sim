#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include "ftools.h"
#include <math.h>

int32_t ftoi(int32_t adata){

int result;

if(split_bit(adata,31,31)==1){
	
	switch(split_bit(adata,30,23)){
	case 157:
	    result = (~((1<<30)+(split_bit(adata,22,0)<<7)))+1;
	break; case 156:
	    result = (~((1<<29)+(split_bit(adata,22,0)<<6)))+1;
	break; case 155:
	    result = (~((1<<28)+(split_bit(adata,22,0)<<5)))+1;
	break; case 154:
	    result = (~((1<<27)+(split_bit(adata,22,0)<<4)))+1;
	break; case 153:
	    result = (~((1<<26)+(split_bit(adata,22,0)<<3)))+1;
	break; case 152:
	    result = (~((1<<25)+(split_bit(adata,22,0)<<2)))+1;
	break; case 151:
	    result = (~((1<<24)+(split_bit(adata,22,0)<<1)))+1;
	break; case 150:
	    result = (~((1<<23)+(split_bit(adata,22,0))))+1;
	break; case 149:
	    result = split_bit(adata,0,0)==1 ? ~(((1<<22)+split_bit(adata,22,1))+1) + 1 : ~((1<<22)+split_bit(adata,22,1));
	break; case 148:
	    result = split_bit(adata,1,1)==1 ? ~(((1<<21)+split_bit(adata,22,2))+1) + 1 : ~((1<<21)+split_bit(adata,22,2));
	break; case 147:
	    result = split_bit(adata,2,2)==1 ? ~(((1<<20)+split_bit(adata,22,3))+1) + 1 : ~((1<<20)+split_bit(adata,22,3));
	break;
	case 146:
	    result = split_bit(adata,3,3)==1 ? ~(((1<<19)+split_bit(adata,22,4))+1) + 1 : ~((1<<19)+split_bit(adata,22,4)) + 1;
	break;
	case 145:
	    result = split_bit(adata,4,4)==1 ? ~(((1<<18)+split_bit(adata,22,5))+1) + 1 : ~((1<<18)+split_bit(adata,22,5)) + 1;
	break;
	case 144:
	    result = split_bit(adata,5,5)==1 ? ~(((1<<17)+split_bit(adata,22,6))+1) + 1 : ~((1<<17)+split_bit(adata,22,6)) + 1;
	break;
	case 143:
	    result = split_bit(adata,6,6)==1 ? ~(((1<<16)+split_bit(adata,22,7))+1) + 1 : ~((1<<16)+split_bit(adata,22,7)) + 1;
	break;
	case 142:
	    result = split_bit(adata,7,7)==1 ? ~(((1<<15)+split_bit(adata,22,8))+1) + 1 : ~((1<<15)+split_bit(adata,22,8)) + 1;
	break;
	case 141:
	    result = split_bit(adata,8,8)==1 ? ~(((1<<14)+split_bit(adata,22,9))+1) + 1 : ~((1<<14)+split_bit(adata,22,9)) + 1;
	break;
	case 140:
	    result = split_bit(adata,9,9)==1 ? ~(((1<<13)+split_bit(adata,22,10))+1) + 1 : ~((1<<13)+split_bit(adata,22,10)) + 1;
	break;
	case 139:
	    result = split_bit(adata,10,10)==1 ? ~(((1<<12)+split_bit(adata,22,11))+1) + 1 : ~((1<<12)+split_bit(adata,22,11)) + 1;
	break;
	case 138:
	    result = split_bit(adata,11,11)==1 ? ~(((1<<11)+split_bit(adata,22,12))+1) + 1 : ~((1<<11)+split_bit(adata,22,12)) + 1;
	break;
	case 137:
	    result = split_bit(adata,12,12)==1 ? ~(((1<<10)+split_bit(adata,22,13))+1) + 1 : ~((1<<10)+split_bit(adata,22,13)) + 1;
	break;
	case 136:
	    result = split_bit(adata,13,13)==1 ? ~(((1<<9)+split_bit(adata,22,14))+1) + 1 : ~((1<<9)+split_bit(adata,22,14)) + 1;
	break;
	case 135:
	    result = split_bit(adata,14,14)==1 ? ~(((1<<8)+split_bit(adata,22,15))+1) + 1 : ~((1<<8)+split_bit(adata,22,15)) + 1;
	break;
	case 134:
	    result = split_bit(adata,15,15)==1 ? ~(((1<<7)+split_bit(adata,22,16))+1) + 1 : ~((1<<7)+split_bit(adata,22,16)) + 1;
	break;
	case 133:
	    result = split_bit(adata,16,16)==1 ? ~(((1<<6)+split_bit(adata,22,17))+1) + 1 : ~((1<<6)+split_bit(adata,22,17)) + 1;
	break;
	case 132:
	    result = split_bit(adata,17,17)==1 ? ~(((1<<5)+split_bit(adata,22,18))+1) + 1 : ~((1<<5)+split_bit(adata,22,18)) + 1;
	break;
	case 131:
	    result = split_bit(adata,18,18)==1 ? ~(((1<<4)+split_bit(adata,22,19))+1) + 1 : ~((1<<4)+split_bit(adata,22,19)) + 1;
	break;
	case 130:
	    result = split_bit(adata,19,19)==1 ? ~(((1<<3)+split_bit(adata,22,20))+1) + 1 : ~((1<<3)+split_bit(adata,22,20)) + 1;
	break;
	case 129:
	    result = split_bit(adata,20,20)==1 ? ~(((1<<2)+split_bit(adata,22,21))+1) + 1 : ~((1<<2)+split_bit(adata,22,21)) + 1;
	break;
	case 128:
	    result = split_bit(adata,21,21)==1 ? ~(((1<<1)+split_bit(adata,22,22))+1) + 1 : ~((1<<1)+split_bit(adata,22,22)) + 1;
	break;
	case 127:
	    result = split_bit(adata,22,22)==1 ? ~(2)+1:~(1)+1;
	break; 
	case 126:
	    result = ~(1) + 1;
	break;
	default:
	    result = 0;
	}
} 
else{
switch (split_bit(adata,30,23)){
	case 157:
	    result = ((1<<30)+(split_bit(adata,22,0)<<7));
	break; case 156:
	    result = ((1<<29)+(split_bit(adata,22,0)<<6));
	break; case 155:
	    result = ((1<<28)+(split_bit(adata,22,0)<<5));
	break; case 154:
	    result = ((1<<27)+(split_bit(adata,22,0)<<4));
	break; case 153:
	    result = ((1<<26)+(split_bit(adata,22,0)<<3));
	break; case 152:
	    result = ((1<<25)+(split_bit(adata,22,0)<<2));
	break; case 151:
	    result = ((1<<24)+(split_bit(adata,22,0)<<1));
	break; case 150:
	    result = ((1<<23)+(split_bit(adata,22,0)));
	case 149:
	    result = split_bit(adata,0,0)==1 ? (((1<<22)+split_bit(adata,22,1))) + 1 : ((1<<22)+split_bit(adata,22,1));
	break;
	case 148:
	    result = split_bit(adata,1,1)==1 ? (((1<<21)+split_bit(adata,22,2))) + 1 : ((1<<21)+split_bit(adata,22,2));
	break;
	case 147:
	    result = split_bit(adata,2,2)==1 ? (((1<<20)+split_bit(adata,22,3))) + 1 : ((1<<20)+split_bit(adata,22,3));
	break;
	case 146:
	    result = split_bit(adata,3,3)==1 ? (((1<<19)+split_bit(adata,22,4))) + 1 : ((1<<19)+split_bit(adata,22,4));
	break;
	case 145:
	    result = split_bit(adata,4,4)==1 ? (((1<<18)+split_bit(adata,22,5))) + 1 : ((1<<18)+split_bit(adata,22,5));
	break;
	case 144:
	    result = split_bit(adata,5,5)==1 ? (((1<<17)+split_bit(adata,22,6))) + 1 : ((1<<17)+split_bit(adata,22,6));
	break;
	case 143:
	    result = split_bit(adata,6,6)==1 ? (((1<<16)+split_bit(adata,22,7))) + 1 : ((1<<16)+split_bit(adata,22,7));
	break;
	case 142:
	    result = split_bit(adata,7,7)==1 ? (((1<<15)+split_bit(adata,22,8))) + 1 : ((1<<15)+split_bit(adata,22,8));
	break;
	case 141:
	    result = split_bit(adata,8,8)==1 ? (((1<<14)+split_bit(adata,22,9))) + 1 : ((1<<14)+split_bit(adata,22,9));
	break;
	case 140:
	    result = split_bit(adata,9,9)==1 ? (((1<<13)+split_bit(adata,22,10))) + 1 : ((1<<13)+split_bit(adata,22,10));
	break;
	case 139:
	    result = split_bit(adata,10,10)==1 ? (((1<<12)+split_bit(adata,22,11))) + 1 : ((1<<12)+split_bit(adata,22,11));
	break;
	case 138:
	    result = split_bit(adata,11,11)==1 ? (((1<<11)+split_bit(adata,22,12))) + 1 : ((1<<11)+split_bit(adata,22,12));
	break;
	case 137:
	    result = split_bit(adata,12,12)==1 ? (((1<<10)+split_bit(adata,22,13))) + 1 : ((1<<10)+split_bit(adata,22,13));
	break;
	case 136:
	    result = split_bit(adata,13,13)==1 ? (((1<<9)+split_bit(adata,22,14))) + 1 : ((1<<9)+split_bit(adata,22,14));
	break;
	case 135:
	    result = split_bit(adata,14,14)==1 ? (((1<<8)+split_bit(adata,22,15))) + 1 : ((1<<8)+split_bit(adata,22,15));
	break;
	case 134:
	    result = split_bit(adata,15,15)==1 ? (((1<<7)+split_bit(adata,22,16))) + 1 : ((1<<7)+split_bit(adata,22,16));
	break;
	case 133:
	    result = split_bit(adata,16,16)==1 ? (((1<<6)+split_bit(adata,22,17))) + 1 : ((1<<6)+split_bit(adata,22,17));
	break;
	case 132:
	    result = split_bit(adata,17,17)==1 ? (((1<<5)+split_bit(adata,22,18))) + 1 : ((1<<5)+split_bit(adata,22,18));
	break;
	case 131:
	    result = split_bit(adata,18,18)==1 ? (((1<<4)+split_bit(adata,22,19))) + 1 : ((1<<4)+split_bit(adata,22,19));
	break;
	case 130:
	    result = split_bit(adata,19,19)==1 ? (((1<<3)+split_bit(adata,22,20))) + 1 : ((1<<3)+split_bit(adata,22,20));
	break;
	case 129:
	    result = split_bit(adata,20,20)==1 ? (((1<<2)+split_bit(adata,22,21))) + 1 : ((1<<2)+split_bit(adata,22,21));
	break;
	case 128:
	    result = split_bit(adata,21,21)==1 ? (((1<<1)+split_bit(adata,22,22))) + 1 : ((1<<1)+split_bit(adata,22,22));
	break;
	case 127:
	        result = split_bit(adata,22,22)==1 ? 2 : 1;
	break; 
	case 126:
	        result = 1;
	break;
	default:
	        result = 0;
	}
}


return     result;
}





int32_t itof(int32_t adata){

int result;

int32_t hosuu;
hosuu = ~adata+1;

int32_t kuriage30;
kuriage30 = ~adata+257;

int32_t kuriage29;
kuriage29 = ~adata + 129;

int32_t kuriage28;
kuriage28 = ~adata + 65;

int32_t kuriage27;
kuriage27 = ~adata + 33;

int32_t kuriage26;
kuriage26 = ~adata + 17;

int32_t kuriage25;
kuriage25 = ~adata + 9;

int32_t kuriage24;
kuriage24 = ~adata + 5;

int32_t kuriage23;
kuriage23 = ~adata + 3;

int32_t a_kuriage30;
a_kuriage30 = adata + 256;

int32_t a_kuriage29;
a_kuriage29 = adata + 128;

int32_t a_kuriage28;
a_kuriage28 = adata + 64;

int32_t a_kuriage27;
a_kuriage27 = adata + 32;

int32_t a_kuriage26;
a_kuriage26 = adata + 16;

int32_t a_kuriage25;
a_kuriage25 = adata + 8;

int32_t a_kuriage24;
a_kuriage24 = adata + 4;

int32_t a_kuriage23;
a_kuriage23 = adata + 2;


if(split_bit(adata,31,31)==1){

	for(int i=0;i<32;i++){
		if(split_bit(hosuu,31-i,31-i)==1){
			if(i==0){
				result = split_bit(hosuu,7,7)==1 ? (((414<<23)+split_bit(kuriage30,30,8))) : ((414<<23)+split_bit(hosuu,30,8));
				break;
			}
			else if(i==1){
				result = split_bit(hosuu,6,6)==1 ? (((413<<23)+split_bit(kuriage29,29,7))) : ((413<<23)+split_bit(hosuu,29,7));
				break;
			}
			else if(i==2){
				result = split_bit(hosuu,5,5)==1 ? (((412<<23)+split_bit(kuriage28,28,6))) : ((412<<23)+split_bit(hosuu,28,6));
				break;
			}
			else if(i==3){
				result = split_bit(hosuu,4,4)==1 ? (((411<<23)+split_bit(kuriage27,27,5))) : ((411<<23)+split_bit(hosuu,27,5));
				break;
			}
			else if(i==4){
				result = split_bit(hosuu,3,3)==1 ? (((410<<23)+split_bit(kuriage26,26,4))) : ((410<<23)+split_bit(hosuu,26,4));
				break;
			}
			else if(i==5){
				result = split_bit(hosuu,2,2)==1 ? (((409<<23)+split_bit(kuriage25,25,3))) : ((409<<23)+split_bit(hosuu,25,3));
				break;
			}
			else if(i==6){
				result = split_bit(hosuu,1,1)==1 ? (((408<<23)+split_bit(kuriage24,24,2))) : ((408<<23)+split_bit(hosuu,24,2));
				break;
			}
			else if(i==7){
				result = split_bit(hosuu,0,0)==1 ? (((407<<23)+split_bit(kuriage23,23,1))) : ((407<<23)+split_bit(hosuu,23,1));
				break;
			}
			else if(i<31){
				result = ((414-i)<<23)+((split_bit(hosuu,30-i,0)<<(i-8)));
				break;
			}
			else{
				result = 3212836864;
				break;
			}
		}
	}
}
else{
	 for(int i=0;i<32;i++){
                if(split_bit(adata,31-i,31-i)==1){

			if(i==0){
				result = split_bit(adata,7,7)==1 ? (((158<<23)+split_bit(a_kuriage30,30,8))) : ((158<<23)+split_bit(adata,30,8));
                                break;
				}
			else if(i==1){
				result = split_bit(adata,6,6)==1 ? (((157<<23)+split_bit(a_kuriage29,29,7))) : ((157<<23)+split_bit(adata,29,7));
                                break;
			}
			else if(i==2){
				result = split_bit(adata,5,5)==1 ? (((156<<23)+split_bit(a_kuriage28,28,6))) : ((156<<23)+split_bit(adata,28,6));
                                break;
			}
			else if(i==3){
				result = split_bit(adata,4,4)==1 ? (((155<<23)+split_bit(a_kuriage27,27,5))) : ((155<<23)+split_bit(adata,27,5));
                                break;
			}
			else if(i==4){
				result = split_bit(adata,3,3)==1 ? (((154<<23)+split_bit(a_kuriage26,26,4))) : ((154<<23)+split_bit(adata,26,4));
                                break;
			}
			else if(i==5){
				result = split_bit(adata,2,2)==1 ? (((153<<23)+split_bit(a_kuriage25,25,3))) : ((153<<23)+split_bit(adata,25,3));
                                break;
			}
			else if(i==6){
				result = split_bit(adata,1,1)==1 ? (((152<<23)+split_bit(a_kuriage24,24,2))) : ((152<<23)+split_bit(adata,24,2));
                                break;
			}
			else if(i==7){
				result = split_bit(adata,0,0)==1 ? (((151<<23)+split_bit(a_kuriage23,23,1))) : ((151<<23)+split_bit(adata,23,1));
                                break;
			}
			else if(i<31){
                                result = ((158-i)<<23)+((split_bit(adata,30-i,0)<<(i-8)));
                                break;
                        }
                        else{
                                result = 1065353216;
                                break;
                        }
		}
	}
}


return result;


}


/*
int main(void){

int adata = 257;

print_bit(adata);
print_bit(~adata+257);

return 0;
}
*/
