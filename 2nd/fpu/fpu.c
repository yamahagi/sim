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

/*
FADD、FSUB、FMULでそれぞれの関数定義に飛べます。
*/


/*     FADD       */
int32_t fadd(int32_t adata,int32_t bdata){

int hiseiki_a;
if((split_bit(adata,30,23)&0xff)>0){
	hiseiki_a = 0;
}
else{
	hiseiki_a = 1;
}

int hiseiki_b;
if((split_bit(bdata,30,23)&0xff)>0){
	hiseiki_b = 0;
}
else{
	hiseiki_b = 1;
}

int hiseiki;
if(hiseiki_a==0&&hiseiki_b==0){
	hiseiki = 0;
}
else{
	hiseiki = 1;
}

int tashi1hiki0;
if(split_bit(adata,31,31)==split_bit(bdata,31,31)){
	tashi1hiki0 = 1;
}
else{
	tashi1hiki0 = 0;
}

int sisuudeka_a;
if(split_bit(adata,30,23)>split_bit(bdata,30,23)){
        sisuudeka_a = 1;
}
else{
        sisuudeka_a = 0;
}

int sisuuonaji;
if(split_bit(adata,30,23)==split_bit(bdata,30,23)){
        sisuuonaji = 1;
}
else{
        sisuuonaji = 0;
}

int kasuudeka_a;
if(split_bit(adata,22,0)>split_bit(bdata,22,0)){
        kasuudeka_a = 1;
}
else{
        kasuudeka_a = 0;
}

int deka_a;
deka_a = sisuudeka_a|(sisuuonaji&kasuudeka_a);

int deka_s;
if(deka_a==1){
	deka_s = split_bit(adata,31,31);
}
else{
	deka_s = split_bit(bdata,31,31);
}

int deka_e;
if(deka_a==1){
	deka_e = split_bit(adata,30,23);
}
else{
	deka_e = split_bit(bdata,30,23);
}

int deka_m;
if(deka_a==1){
	deka_m = (1<<23)+split_bit(adata,22,0);
}
else{
	deka_m = (1<<23)+split_bit(bdata,22,0);
}

int ahikub;
ahikub = split_bit(adata,30,23)-split_bit(bdata,30,23);

int bhikua;
bhikua = split_bit(bdata,30,23)-split_bit(adata,30,23);

int chibi_m;
if(deka_a==1){
	if(ahikub>23){
		chibi_m = 0;
	}
	else{
		chibi_m = ((1<<23)+split_bit(bdata,22,0))>>ahikub;
	}
}
else{
	if(bhikua>23){
		chibi_m = 0;
	}
	else{
		chibi_m = ((1<<23)+split_bit(adata,22,0))>>bhikua;
	}
}

int hiseiki_reg;
int hiseiki_a_reg;
int tashi1hiki0_reg;
int deka_s_reg;
int deka_e_reg;
int deka_m_reg;
int chibi_m_reg;
int adata_reg_1;
int bdata_reg_1;

hiseiki_reg = hiseiki;
hiseiki_a_reg = hiseiki_a;
tashi1hiki0_reg = tashi1hiki0;
deka_s_reg = deka_s;
deka_e_reg = deka_e;
deka_m_reg = deka_m;
chibi_m_reg = chibi_m;
adata_reg_1 = adata;
bdata_reg_1 = bdata;
/*
int Hcarrysub;
if(tashi1hiki0_reg==1){
	Hcarrysub = ((split_bit(deka_m_reg,23,13))<<1)+1 +((split_bit(chibi_m_reg,23,13))<<1) + 1;
}
else{
	Hcarrysub = ((split_bit(deka_m_reg,23,13))<<1)-((split_bit(chibi_m_reg,23,13))<<1) - 1;
}

int Hcarry;
Hcarry = split_bit(Hcarrysub,12,1);

int Hnocarry;
if(tashi1hiki0_reg==1){
	Hnocarry = ((split_bit(deka_m_reg,23,13)))+((split_bit(chibi_m_reg,23,13)));
}
else{
	Hnocarry = ((split_bit(deka_m_reg,23,13)))-((split_bit(chibi_m_reg,23,13)));
}

int Lsub;
if(tashi1hiki0_reg==1){
	Lsub = split_bit(deka_m_reg,12,0)+split_bit(chibi_m_reg,12,0);
}
else{
	Lsub = ((1<<13)+split_bit(deka_m_reg,12,0))-split_bit(chibi_m_reg,12,0);
}

int carry;
if(tashi1hiki0_reg==1){
	carry = split_bit(Lsub,13,13);
}
else{
	if(split_bit(Lsub,13,13)==0){
		carry = 1;
	}
	else{
		carry = 0;
	}
}
*/

/*
printf("Lsub\n");
print_bit(Lsub);
*/	

/*
int L;
L = split_bit(Lsub,12,0);
*/

int hiseiki_reg_2;
int hiseiki_a_reg_2;
int s2_reg;
int e2_reg;
int kekka_reg;
int adata_reg_2;
int bdata_reg_2;
/*
printf("L\n");
print_bit(L);	
printf("Hcarry\n");
print_bit(Hcarry);	
printf("Hnocarry\n");
print_bit(Hnocarry);	
*/
hiseiki_reg_2 = hiseiki;
hiseiki_a_reg_2 = hiseiki_a;
s2_reg = deka_s;
e2_reg = deka_e;
if(tashi1hiki0==1){
	kekka_reg =  deka_m+chibi_m;
}
else{
	kekka_reg =  deka_m-chibi_m;
}
adata_reg_2 = adata;
bdata_reg_2 = bdata;

int kijyun=0;
int result;
/*
printf("kekka_reg\n");
print_bit(kekka_reg);
*/
if(hiseiki_reg_2==1){
	if(hiseiki_a_reg_2==1){
		result = bdata_reg_2;
	}
	else{
		result = adata_reg_2;
	}
}
else{
	while(1==1){
		if(split_bit(kekka_reg,24-kijyun,24-kijyun)==1){
			if(kijyun==0){
				result = (s2_reg<<31)+((e2_reg+1)<<23)+((split_bit(kekka_reg,23,1)));
			}
			else if(kijyun==1){
				result = (s2_reg<<31)+((e2_reg)<<23)+((split_bit(kekka_reg,22,0)));
			}	
			else if(kijyun==24){
				if(e2_reg<(kijyun-1)){
                                        result = 0;
                                }
                                else{
                                        result = (s2_reg<<31)+((e2_reg-(kijyun-1))<<23);
                                }

			}
			else{
				if(e2_reg<(kijyun-1)){
					result = 0;
				}
				else{
					result = (s2_reg<<31)+((e2_reg-(kijyun-1))<<23)+(split_bit(kekka_reg,23-kijyun,0)<<(kijyun-1));
				}
			}
			break;
		}
		if(kijyun==24){
			result = 0;
			break;
		}
		kijyun+=1;
	}
}

return result;
}


/*     FSUB       */
int32_t fsub(int32_t adata,int32_t bdata){

int hiseiki_a;
if((split_bit(adata,30,23)&0xff)>0){
	hiseiki_a = 0;
}
else{
	hiseiki_a = 1;
}

int hiseiki_b;
if((split_bit(bdata,30,23)&0xff)>0){
	hiseiki_b = 0;
}
else{
	hiseiki_b = 1;
}

int hiseiki;
if(hiseiki_a==0&&hiseiki_b==0){
	hiseiki = 0;
}
else{
	hiseiki = 1;
}

int tashi1hiki0;
if(split_bit(adata,31,31)!=split_bit(bdata,31,31)){
	tashi1hiki0 = 1;
}
else{
	tashi1hiki0 = 0;
}

int sisuudeka_a;
if(split_bit(adata,30,23)>split_bit(bdata,30,23)){
        sisuudeka_a = 1;
}
else{
        sisuudeka_a = 0;
}

int sisuuonaji;
if(split_bit(adata,30,23)==split_bit(bdata,30,23)){
        sisuuonaji = 1;
}
else{
        sisuuonaji = 0;
}

int kasuudeka_a;
if(split_bit(adata,22,0)>split_bit(bdata,22,0)){
        kasuudeka_a = 1;
}
else{
        kasuudeka_a = 0;
}

int deka_a;
deka_a = sisuudeka_a|(sisuuonaji&kasuudeka_a);

int deka_s;
if(deka_a==1){
	deka_s = split_bit(adata,31,31);
}
else{
	if(split_bit(bdata,31,31)==1){
		deka_s = 0;
	}
	else{
		deka_s = 1;
	}
}

int deka_e;
if(deka_a==1){
	deka_e = split_bit(adata,30,23);
}
else{
	deka_e = split_bit(bdata,30,23);
}

int deka_m;
if(deka_a==1){
	deka_m = (1<<23)+split_bit(adata,22,0);
}
else{
	deka_m = (1<<23)+split_bit(bdata,22,0);
}

int ahikub;
ahikub = split_bit(adata,30,23)-split_bit(bdata,30,23);

int bhikua;
bhikua = split_bit(bdata,30,23)-split_bit(adata,30,23);

int chibi_m;
if(deka_a==1){
	if(ahikub>23){
		chibi_m = 0;
	}
	else{
		chibi_m = ((1<<23)+split_bit(bdata,22,0))>>ahikub;
	}
}
else{
	if(bhikua>23){
		chibi_m = 0;
	}
	else{
		chibi_m = ((1<<23)+split_bit(adata,22,0))>>bhikua;
	}
}
/*
int hiseiki_reg;
int hiseiki_a_reg;
int tashi1hiki0_reg;
int deka_s_reg;
int deka_e_reg;
int deka_m_reg;
int chibi_m_reg;
int adata_reg_1;
int bdata_reg_1;

hiseiki_reg = hiseiki;
hiseiki_a_reg = hiseiki_a;
tashi1hiki0_reg = tashi1hiki0;
deka_s_reg = deka_s;
deka_e_reg = deka_e;
deka_m_reg = deka_m;
chibi_m_reg = chibi_m;
adata_reg_1 = adata;
if(split_bit(bdata,31,31)==1){
	bdata_reg_1 = split_bit(bdata,30,0);
}
else{
	bdata_reg_1 = (1<<31)+split_bit(bdata,30,0);
}

int Hcarrysub;
if(tashi1hiki0_reg==1){
	Hcarrysub = ((split_bit(deka_m_reg,23,13))<<1)+1 +((split_bit(chibi_m_reg,23,13))<<1) + 1;
}
else{
	Hcarrysub = ((split_bit(deka_m_reg,23,13))<<1)-((split_bit(chibi_m_reg,23,13))<<1) - 1;
}

int Hcarry;
Hcarry = split_bit(Hcarrysub,12,1);

int Hnocarry;
if(tashi1hiki0_reg==1){
	Hnocarry = ((split_bit(deka_m_reg,23,13)))+((split_bit(chibi_m_reg,23,13)));
}
else{
	Hnocarry = ((split_bit(deka_m_reg,23,13)))-((split_bit(chibi_m_reg,23,13)));
}

int Lsub;
if(tashi1hiki0_reg==1){
	Lsub = split_bit(deka_m_reg,12,0)+split_bit(chibi_m_reg,12,0);
}
else{
	Lsub = ((1<<13)+split_bit(deka_m_reg,12,0))-split_bit(chibi_m_reg,12,0);
}

int carry;
if(tashi1hiki0_reg==1){
	carry = split_bit(Lsub,13,13);
}
else{
	if(split_bit(Lsub,13,13)==0){
		carry = 1;
	}
	else{
		carry = 0;
	}
}
printf("Lsub\n");
print_bit(Lsub);
int L;
L = split_bit(Lsub,12,0);
*/
int hiseiki_reg_2;
int hiseiki_a_reg_2;
int s2_reg;
int e2_reg;
int kekka_reg;
int adata_reg_2;
int bdata_reg_2;
/*
printf("L\n");
print_bit(L);	
printf("Hcarry\n");
print_bit(Hcarry);	
printf("Hnocarry\n");
print_bit(Hnocarry);	
*/
hiseiki_reg_2 = hiseiki;
hiseiki_a_reg_2 = hiseiki_a;
s2_reg = deka_s;
e2_reg = deka_e;
if(tashi1hiki0==1){
	kekka_reg =  deka_m+chibi_m;
}
else{
	kekka_reg =  deka_m-chibi_m;
}
adata_reg_2 = adata;
if(split_bit(bdata,31,31)==1){
	bdata_reg_2 = split_bit(bdata,30,0);
}
else{
	bdata_reg_2 = (1<<31)+split_bit(bdata,30,0);
}

int kijyun=0;
int result;
/*
printf("kekka_reg\n");
print_bit(kekka_reg);
*/
if(hiseiki_reg_2==1){
	if(hiseiki_a_reg_2==1){
		result = bdata_reg_2;
	}
	else{
		result = adata_reg_2;
	}
}
else{
	while(1==1){
		if(split_bit(kekka_reg,24-kijyun,24-kijyun)==1){
			if(kijyun==0){
				result = (s2_reg<<31)+((e2_reg+1)<<23)+((split_bit(kekka_reg,23,1)));
			}
			else if(kijyun==1){
				result = (s2_reg<<31)+((e2_reg)<<23)+((split_bit(kekka_reg,22,0)));
			}	
			else if(kijyun==24){
				if(e2_reg<(kijyun-1)){
                                        result = 0;
                                }
                                else{
                                        result = (s2_reg<<31)+((e2_reg-(kijyun-1))<<23);
                                }

			}
			else{
				if(e2_reg<(kijyun-1)){
					result = 0;
				}
				else{
					result = (s2_reg<<31)+((e2_reg-(kijyun-1))<<23)+(split_bit(kekka_reg,23-kijyun,0)<<(kijyun-1));
				}
			}
			break;
		}
		if(kijyun==24){
			result = 0;
			break;
		}
		kijyun+=1;
	}
}

return result;
}

/*     FMUL      */
int32_t fmul(int32_t adata,int32_t bdata){

int a0;
a0 = (1<<13)+split_bit(adata,22,10);

int b0;
b0 = (1<<13)+split_bit(bdata,22,10);

int a1;
a1 = split_bit(adata,9,0);

int b1;
b1 = split_bit(bdata,9,0);

int hoge;
hoge = a0*b1;

int fuga;
fuga = a1*b0;

int a0b0;
int a1b0;
int a0b1;
int e;
int e_kuriage;
int s;
int notzero;
int flag;

int eadd;
eadd = split_bit(adata,30,23)+split_bit(bdata,30,23);

a0b0 = a0*b0;
a1b0 = a1*b0;
a0b1 = a0*b1;

if(eadd<127){
	e_kuriage = 0;
}
else{
	e_kuriage = eadd-126;
}

if(eadd<127){
	e = 0;
}
else{
	e = eadd-127;
}

if(split_bit(adata,31,31)!=split_bit(bdata,31,31)){
	s = 1;
}
else{
	s = 0;
}

if((split_bit(adata,30,23)>0)&&(split_bit(bdata,30,23)>0)){
	notzero = 1;
}
else{
	notzero = 0;
}

int a0b1tasua1b0;
a0b1tasua1b0=split_bit(a1b0,23,10)+split_bit(a0b1,23,10);

int kekka_L;
kekka_L = a0b1tasua1b0 + split_bit(a0b0,14,0);

int kekka_H_carry;
kekka_H_carry = split_bit(a0b0,27,15)+1;

int kekka_H_nocarry;
kekka_H_nocarry = split_bit(a0b0,27,15);

int carry = split_bit(kekka_L,15,15);

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
		kotae = (s<<31)+(e_kuriage<<23)+split_bit(kekka,23,1);
	}
	else{
		kotae = (s<<31)+(e<<23)+split_bit(kekka,22,0);
	}
}
else{
		kotae = 0;
}

return kotae;

}


