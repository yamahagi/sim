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

int index,indexnow;
index = split_bit(bdata,22,13);
int key[1025];
int key2[1025];
int key3[1025];

int i;
  float x;
  union {float f;int b;} keytable;
  union {float f;int b;} key2table;
  int a;
  int b;
  int c;
  for (i=0;i<2;i++){
	indexnow = index+i;
    x = 1.0 + (indexnow/1024.0);
    keytable.f = 2.0/x + 1.0/(4194304.0 * pow(x,3.0));
    key2table.f = 2.0/pow(x,2.0);
    a = keytable.b & 0b00000000011111111111111111111111;
    b = 4096 + ((key2table.b & 0b00000000011111111111100000000000) >> 11);
    if (((key2table.b & 0b01111111100000000000000000000000) >> 23) == 126){
      c = 1;
    }
    else {
      c = 0;
    }
	key[indexnow] = a;
	key2[indexnow] = b;
	key3[indexnow] = c;
  }

key[0] = 8388607;
key2[0] = 8190;
key3[0] = 0;

key[1024] = 0;
key2[1024] = 4096;
key3[1024] = 1;

//int a;
a = (split_bit(bdata,12,12)==1)? key[index+1] : key[index];

//int b;
b = split_bit(bdata,12,0);

int bneg12;
bneg12 = ~split_bit(bdata,12,0);

int bb;
bb = split_bit(bneg12,12,0)+1;

int bk;
bk = b*key2[index];

int bbk;
bbk = bb*key2[index+1];

//int c;
c = (split_bit(bdata,12,12)==1)? key3[index+1] : key3[index];

int a_reg;
int bk_reg;
int bbk_reg;
int adata_reg_1;
int bs_reg_1;
int be_reg_1;
int bdata12_reg;
int c_reg;

a_reg = a;
bk_reg = bk;
bbk_reg = bbk;
adata_reg_1 = adata;
bs_reg_1 = split_bit(bdata,31,31);
be_reg_1 = split_bit(bdata,30,23);
bdata12_reg = split_bit(bdata,12,12);
c_reg = c;

int inv;
inv = (bdata12_reg == 1)? ((c_reg==1)? a_reg+split_bit(bbk_reg,25,13):a_reg+split_bit(bbk_reg,25,12)) : ((c_reg==1)? a_reg-split_bit(bk_reg,25,13):a_reg-split_bit(bk_reg,25,12));

int adata_reg_2;
int bs_reg_2;
int be_reg_2;
int inv_reg;

adata_reg_2 = adata_reg_1;
bs_reg_2 = bs_reg_1;
be_reg_2 = 253-be_reg_1;
inv_reg = inv;

int a0;
a0 = (1<<13)+split_bit(adata_reg_2,22,10);

int b0;
b0 = (1<<13)+split_bit(inv_reg,22,10);

int a1;
a1 = split_bit(adata_reg_2,9,0);

int b1;
b1 = split_bit(inv_reg,9,0);

int eadd;
eadd = split_bit(adata_reg_2,30,23)+be_reg_2;

int a0b0;
int a1b0;
int a0b1;
int e;
int e_kuriage;
int s;
int notzero;

a0b0 = a0*b0;
a1b0 = a1*b0;
a0b1 = a0*b1;
e = (eadd<127)? 0 :eadd-127;
e_kuriage = (eadd<127)? 0 :eadd-126;
s = (split_bit(adata_reg_2,31,31))^(bs_reg_2);
if(split_bit(adata_reg_2,30,23)>0){
	notzero = 1;
}
else{
	notzero = 0;
}

int a0b1tasua1b0;
a0b1tasua1b0 = split_bit(a1b0,23,10)+split_bit(a0b1,23,10);

int kekka_L;
kekka_L = a0b1tasua1b0 + split_bit(a0b0,14,0);

int kekka_H_carry;
kekka_H_carry = split_bit(a0b0,27,15)+1;

int kekka_H_nocarry;
kekka_H_nocarry = split_bit(a0b0,27,15);

int carry;
carry = split_bit(kekka_L,15,15);

int kekka;
kekka = (carry==1)? (kekka_H_carry<<12)+split_bit(kekka_L,14,3) : (kekka_H_nocarry<<12)+split_bit(kekka_L,14,3);


int kotae;
kotae = (notzero==1)?( (split_bit(kekka,24,24)==1)? (s<<31)+(e_kuriage<<23)+split_bit(kekka,23,1) : (s<<31)+(e<<23)+split_bit(kekka,22,0)) :0;

int result;

result = kotae;
/*
printf("index %d\n",index);
printf("key[index] %d\n",key[index]);
printf("key2[index] %d\n",key2[index]);
printf("key3[index] %d\n",key3[index]);
printf("key[index+1] %d\n",key[index+1]);
printf("key2[index+1] %d\n",key2[index+1]);
printf("key3[index+1] %d\n",key3[index+1]);
printf("a %d\n",a);
printf("b %d\n",b);
print_bit(b);
printf("bb %d\n",bb);
print_bit(bb);
printf("bk %d\n",bk);
printf("bbk %d\n",bbk);
printf("c %d\n",c);
*/
return result;
}




