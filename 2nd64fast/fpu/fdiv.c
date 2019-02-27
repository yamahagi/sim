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

int32_t fdiv(int32_t adata,int32_t bdata){

int s[2048];
int t[2048];
float x0;
unsigned long long x0int;
unsigned long long s12;
unsigned long long ss;
unsigned long long t12;
union {float x0; int x0bit;} hoge;
union {float x02jyou; int x02jyoubit;} fuga;

int key;
key = split_bit(bdata,22,12);

int A2;
A2 = split_bit(bdata,11,0);

x0int = 0;
hoge.x0 = ((2048.0 / (key + 2048.0)) + (2048.0 / ((key+1.0) + 2048.0)))/2.0;
for(int j = 0; j <23 ; j++ ){
                 x0int = x0int + ((( hoge.x0bit >> j ) & 1 ) << j);
        }
x0int = x0int + (1 << 23);
s12 = ((2048 + key) * x0int * x0int);
ss =  2 * x0int - (s12 >> 35);
t12 = (x0int * x0int) >> 35;

s[key] = ss;
t[key] = t12;



int S;
S = s[key];

int T;
T = t[key];

int S_TA_1;
S_TA_1 = (T*A2);

int one;
if(split_bit(bdata,22,0)>0){
	one = 0;
}
else{
	one = 1;
}

int S_TA_1_reg;
int S_reg;
int one_reg_1;
int s1_1;
int ea126_1;
int ea127_1;
int ea128_1;
int eb_1;
int notzero_1;
int akasuu_1;

akasuu_1 = (1<<23)+split_bit(adata,22,0);
S_TA_1_reg = S_TA_1;
S_reg = S;
one_reg_1 = one;
if(split_bit(adata,31,31)!=split_bit(bdata,31,31)){
	s1_1 = 1;
}
else{
	s1_1 = 0;
}
ea126_1 = split_bit(adata,30,23)+126;
ea127_1 = split_bit(adata,30,23)+127;
ea128_1 = split_bit(adata,30,23)+128;
eb_1 = split_bit(bdata,30,23);
if(split_bit(adata,30,23)>0){
	notzero_1 = 1;
}
else{
	notzero_1 = 0;
}

int S_TA;
S_TA = S_reg - (S_TA_1_reg >> 12);

int one_reg;
int s1;
int ea126;
int ea127;
int ea128;
int eb;
int akasuu;
int bkasuu;
int notzero_2;

akasuu = akasuu_1;
if(one_reg_1==1){
	bkasuu = split_bit(S_TA,24,1);
}
else{
	bkasuu = split_bit(S_TA,23,0);
}
one_reg = one_reg_1;
s1 = s1_1;
ea126 = ea126_1;
ea127 = ea127_1;
ea128 = ea128_1;
eb = eb_1;
notzero_2 = notzero_1;

int a0;
a0 = split_bit(akasuu,23,10);

int b0;
b0 = split_bit(bkasuu,23,10);

int a1;
a1 = split_bit(akasuu,9,0);

int b1;
b1 = split_bit(bkasuu,9,0);

int a0b0;
int a1b0;
int a0b1;
int e;
int e_kuriage;
int s2;
int notzero;

a0b0 = a0*b0;
a1b0 = a1*b0;
a0b1 = a0*b1;
if(one_reg==1){
	if(ea127<eb){
		e = 0;
	}
	else{
		e = ea127-eb;
	}
}
else{
	if(ea126<eb){
                e = 0;
        }
        else{
                e = ea126-eb;
        }
}

if(one_reg==1){
        if(ea127<eb){
                e_kuriage = 0;
        }
        else{
                e_kuriage = ea128-eb;
        }
}
else{
        if(ea126<eb){
                e_kuriage = 0;
        }
        else{
                e_kuriage = ea127-eb;
        }
}

s2 = s1;
notzero = notzero_2;

int a0b1tasua1b0;
a0b1tasua1b0 = split_bit(a1b0,23,10) + split_bit(a0b1,23,10);

int kekka_L;
kekka_L = a0b1tasua1b0 + split_bit(a0b0,14,0);

int kekka_H_carry;
kekka_H_carry = split_bit(a0b0,27,15) + 1;

int kekka_H_nocarry;
kekka_H_nocarry = split_bit(a0b0,27,15);

int carry;
carry = split_bit(kekka_L,15,15);

int kekka;
if(carry == 1){
	kekka = (kekka_H_carry<<12)+split_bit(kekka_L,14,3);
}
else{
	kekka = (kekka_H_nocarry<<12)+split_bit(kekka_L,14,3);
}

int kotae;
if(notzero==1){
	if(split_bit(kekka,24,24)==1){
		kotae = (s2<<31)+(e_kuriage<<23)+(split_bit(kekka,23,1));
	}
	else{
		kotae = (s2<<31)+(e<<23)+(split_bit(kekka,22,0));
	}
}
else{
	kotae = 0;
}

int result;

result = kotae;

return result;
}




