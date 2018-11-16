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
#include <math.h>


//010101010101010101010110101

int32_t split_bit(int32_t data,int start,int end){

int32_t result = ((0xffffffff>>(31-start))&data)>>end;

return result;

}

void print_bit(int32_t data){
	for(int i=0;i<32;i++){
		if(i==1||i==9) printf(" ");
		printf("%d",((data>>(31-i))&0x1));
	}
	printf("\n");
}

void print_bit64(int64_t data){
	for(int i=0;i<64;i++){
		printf("%d",((data>>(63-i))&0x1));
	}
	printf("\n");
}
int32_t split_bit64(int64_t data,int start,int end){

int32_t result = ((0xffffffffffffffff>>(63-start))&data)>>end;

return result;

}
float float_get(int32_t b){

return *(float*)(&b);

/*	uint32_t s = (b>>31)&0x1;
	uint32_t exp = (b>>23)&0xff;
	uint32_t frac = b&0x7fffff;
	
	float a = 0;
	int i;
	int j;
	for(i=0;i<23;i++){
		float b = 0.5;
		if (((frac>>(23-i-1))&0x1)==1){
			for(j=0;j<i;j++){
				b = b/2;
			}
		a+=b;
		}
	}

	int exp1 = exp-127;
	float k=1.0;
	if(exp1>=0){
		for(i=0;i<exp1;i++){
			k*=2;
		}
	}
	else{
		for(i=0;i<(-exp1);i++){
			k/=2;
		}
	}

	float l;

	if(s==0){

		l = k*(1+a);

	}
	else{

		l = -k*(1+a);

	}



	return l;
*/
}


int32_t int_get(float b) {

	return *(int*)(&b);

/*
    union { float f; int i; } a;
    int i;
    a.f = b;

    int32_t c=0;
    for( i = 31; i >= 0; i-- ){
        c = c | (((a.i>>i)&1)<<i);
    }

    return c;
*/
}
/*
int main(void){

int32_t a = 0x40200000;
float b = 1.5;

float c = b+float_get(a);

int32_t d = int_get(c);

printf("%f\n",c);
printf("%d\n",d);

return 0;
}
*/
