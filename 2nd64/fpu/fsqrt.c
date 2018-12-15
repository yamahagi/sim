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

int32_t fsqrt(int32_t adata){

int s[2048];
int tm[2048];
int te[2048];;

int se;
if(split_bit(adata,23,23)==1){
	se = (split_bit(adata,30,23)>>1)+64;
}
else{
	se = (split_bit(adata,30,23)>>1)+63;
}

int key;
key = split_bit(adata,23,13);

float x;
union {float t; int tbit;} hoge;
union {float u; int ubit;} fuga;
union {float s; int sbit;} piyo;

int te1,ue1;
int A1;
A1 = (key > 1023) ? key : key + 1024;
if (key < 1024) {
      x = 1.0/pow((A1+A1+1.0) / pow(2.0,10.0) , 0.5) ;
      piyo.s = 3.0*x*A1/pow(2.0,10.0) - x*x*x*A1*A1/pow(2.0,19.0);
      hoge.t = 3.0*x-x*x*x*A1/pow(2.0,8.0);
      fuga.u = x*x*x;
      te1 = (hoge.tbit & 0b01111111100000000000000000000000) >> 23;
      ue1 = (fuga.ubit & 0b01111111100000000000000000000000) >> 23;
      s[key] = (piyo.sbit & 0b00000000011111111111111111111111)-4;
      tm[key] = 4096+((hoge.tbit     & 0b00000000011111111111100000000000) >> 11);
      te[key] = (139-te1) > 26 ? 26 : 139-te1;
      }
      else {
            x = 1.0/pow((A1+A1+1.0) / pow(2.0,11.0) , 0.5) ;
      piyo.s = 3.0*x*A1/pow(2.0,11.0) - x*x*x*A1*A1/pow(2.0,21.0);
      hoge.t = 1.5*x-x*x*x*A1/pow(2.0,10.0);
      fuga.u = x*x*x;
      te1 = (hoge.tbit & 0b01111111100000000000000000000000) >> 23;
      ue1 = (fuga.ubit & 0b01111111100000000000000000000000) >> 23;
      s[key] = (piyo.sbit & 0b00000000011111111111111111111111)-4;
      tm[key] = 4096+((hoge.tbit     & 0b00000000011111111111100000000000) >> 11);
      te[key] = (139-te1) > 26 ? 26 : 139-te1;
      }


int ta;
ta = tm[key]*split_bit(adata,12,0);

int ta_reg;
int te_reg;
int s_reg;
int notzero_reg;
int se_reg;
ta_reg = ta;
te_reg = te[key];
s_reg = s[key];
notzero_reg = (split_bit(adata,30,23)>0)? 1 : 0;
se_reg = se;

int ta_s;
ta_s = (te_reg>13) ? 0 : ta_reg >> te_reg;

int kari;
kari = s_reg + ta_s;

int result;

result = (notzero_reg == 1)? (se_reg<<23)+kari : 0;

return result;
}





