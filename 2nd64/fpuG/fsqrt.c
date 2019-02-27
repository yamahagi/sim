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

int se;
if(split_bit(adata,23,23)==1){
	se = (split_bit(adata,30,23)>>1)+64;
}
else{
	se = (split_bit(adata,30,23)>>1)+63;
}

int index,nextindex;
index = split_bit(adata,23,15);
nextindex = index+1;
int key[512];
int key2[512];

//printf("index %d\n",index);

int rx;
  int trxb1;
  int r2x;
  int r2xb1;
  union {float f;int b;} keyu;
  union {float f;int b;} key2u;
if (index > 255) {
      keyu.f = pow(index/256.0,0.5);
      key2u.f = 1.0/(2.0*pow(index/256.0,0.5));
      rx = keyu.b & 0b00000000011111111111111111111111;
      trxb1 = ((key2u.b & 0b00000000011111111111100000000000) >> 11) + 4096;
	key[index] = rx;
	key2[index] = trxb1;
      keyu.f = pow(nextindex/256.0,0.5);
      key2u.f = 1.0/(2.0*pow(nextindex/256.0,0.5));
      rx = keyu.b & 0b00000000011111111111111111111111;
      trxb1 = ((key2u.b & 0b00000000011111111111100000000000) >> 11) + 4096;
	key[nextindex] = rx;
	key2[nextindex] = trxb1;
	}
else {
      keyu.f = pow((256.0+index)*2.0/256.0,0.5);
      key2u.f = 1.0/pow((256.0+index)*2.0/256.0,0.5);
      r2x = keyu.b & 0b00000000011111111111111111111111;
      r2xb1 = ((key2u.b & 0b00000000011111111111110000000000) >> 10) + 8192;
	key[index] = r2x;
        key2[index] = r2xb1;
      keyu.f = pow((256.0+nextindex)*2.0/256.0,0.5);
      key2u.f = 1.0/pow((256.0+nextindex)*2.0/256.0,0.5);
      r2x = keyu.b & 0b00000000011111111111111111111111;
      r2xb1 = ((key2u.b & 0b00000000011111111111110000000000) >> 10) + 8192;
	key[nextindex] = r2x;
        key2[nextindex] = r2xb1;
}

key[256] = 0;
key2[256] = 8192;
/*
printf("key %d\n",key[index]);
printf("keynext %d\n",key[nextindex]);
printf("key2 %d\n",key2[index]);
printf("keynext %d\n",key2[nextindex]);
*/
int a;
a = (split_bit(adata,14,14)==1) ? key[nextindex] : key[index];

//printf("a %d\n",a);

int check;
int aneg;
/*
printf("~adata[22,14] ");
print_bit(~(split_bit(adata,22,14)));
*/
aneg = ~(split_bit(adata,22,14));
if((split_bit(aneg,8,0))>0){
	check = 0;
}
else{
	check = 1;
}
//printf("check %d\n",check);
//check = ~(|(~(split_bit(adata,22,14))));

int kuso;
aneg = ~(split_bit(adata,14,0));
/*
printf("aneg ");
print_sqrtbit(aneg);
*/
kuso = split_bit(aneg,14,0)+0x1;
/*
printf("kuso ");
print_sqrtbit(kuso);
printf("kuso %d\n",kuso);
*/
int bkxk;
bkxk = kuso * 5792;
/*
printf("kuso*5792 %d\n",bkxk);
*/
int bkxg;
bkxg = kuso * 8192;

int bkn;
 bkn = kuso * key2[index+1];
//printf("bkn %d\n",bkn);

int bkp;
bkp = split_bit(adata,14,0)*key2[index];
/*
printf("adata[14;0] %d\n",split_bit(adata,14,0));
printf("bkp %d\n",bkp);
*/
int a_reg;
int check_reg;
int bkxk_reg;
int bkxg_reg;
int bkn_reg;
int bkp_reg;
int notzero_reg;
int se_reg;
int adata14_reg;
int adata23_reg;

a_reg = (check==1)? ((split_bit(adata,23,23)==1)? 3474675 : 8388607) : a;
check_reg = check;
bkxk_reg = bkxk;
bkxg_reg = bkxg;
bkn_reg = bkn;
bkp_reg = bkp;
if((split_bit(adata,30,23))>0){
	notzero_reg = 1;
}
else{
	notzero_reg = 0;
} 
//notzero_reg = |(split_bit(adata,30,23));
se_reg = se;

adata14_reg = split_bit(adata,14,14);
adata23_reg = split_bit(adata,23,23);

int bk;
bk = (check_reg ==1)? ((adata23_reg ==1)? bkxk_reg : bkxg_reg) : ((adata14_reg ==1)? bkn_reg : bkp_reg);
/*
printf("bk\n");
print_sqrtbit(bk);
printf("bk %d\n",bk);
*/
int bk2;
bk2 = split_bit(bk,28,14);
/*
printf("bk2\n");
print_sqrtbit(bk2);
printf("bk2 %d\n",bk2);
printf("a_reg %d\n",a_reg);
*/
int kari;
kari = (adata14_reg ==1)? a_reg - bk2 : a_reg + bk2;
/*
printf("kari %d\n",kari);
print_sqrtbit(a_reg);
print_sqrtbit(bk2);
print_sqrtbit(kari);
*/
int result;

result = (notzero_reg == 1)? (se_reg<<23)+split_bit(kari,22,0) : 0;


return result;
}





