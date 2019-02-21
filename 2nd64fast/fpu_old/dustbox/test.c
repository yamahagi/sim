#include "fdiv2.h"
#include "fpu.c"
#include "ftools.c"
#include <stdio.h>
#include <stdlib.h> /* 乱数関数を利用するのに必要 */
#include <time.h>
#include <math.h>
#define GOSA 0.0001

int32_t fdiv(int32_t adata,int32_t bdata);

int main(void){

int n;
int t=0;
float a,b,c,d;
int l = 0;
	srand(time(NULL));
	 for(n = 0; n < 100000; ++n){
       a  = ((float)(RAND_MAX/2)-(float)rand())/(float)rand();    /* 乱数の取得 */
       b  = ((float)(RAND_MAX/2)-(float)rand())/(float)rand();    /* 乱数の取得 */
        c = a/b;
	d = float_get(fdiv(int_get(a),int_get(b)));
	if(c-d>fabsf(c)*GOSA||c-d<(-(fabsf(c)*GOSA))){
	printf("%f / %f = %fなのに%f\n", a,b,c,d);              /* 乱数の表示 */
    	l+=1;}
        c = a+b;
	d = float_get(fadd(int_get(a),int_get(b)));
	if(c-d>fabsf(c)*GOSA||c-d<(-(fabsf(c)*GOSA))){
		 printf("%f - %f = %fなのに%f\n", a,b,c,d);              /* 乱数の表示 */
        	l+=1;
	}
        c = a-b;
	d = float_get(fsub(int_get(a),int_get(b)));
	if(c-d>fabsf(c)*GOSA||c-d<(-(fabsf(c)*GOSA))){
	printf("%f - %f = %fなのに%f\n", a,b,c,d);              /* 乱数の表示 */
	l+=1;
	}
        c = a*b;
	d = float_get(fmul(int_get(a),int_get(b)));
	if(c-d>fabsf(c)*GOSA||c-d<(-(fabsf(c)*GOSA))){
	printf("%f * %f = %fなのに%f\n", a,b,c,d);              /* 乱数の表示 */
	l+=1;
	}
	}
	printf("l %d\n",l);
}

//とりあえず大きなバグはない？
//FADD,FSUB,FMULでは誤差はまあ0.0001%以内には収まってる？
