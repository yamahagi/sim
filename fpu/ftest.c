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

float float_get(int32_t b){
	uint32_t s = (b>>31)&0x1;
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

}


int32_t int_get(float b) {

    /* float型のデータサイズは32ビットなので、32ビット整数型（ int ）とコンビを組みます */
    union { float f; int i; } a;
    int i;
    a.f = b;

    int32_t c=0;
    /* ビットの列を表示します */
    for( i = 31; i >= 0; i-- ){
        c = c | (((a.i>>i)&1)<<i);
    }
    printf( "\n" );

    /* 指数部（ 1ビット ）、指数部（ 8ビット ）、仮数部（ 23ビット ）を取り出します */

    return c;
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
