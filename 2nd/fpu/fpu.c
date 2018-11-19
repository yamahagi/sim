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
ADDとSUBが何も考えずにそのまま移植したので大分コード長くなってしまってます
時間あったら書き直します
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
/*
printf("Lsub\n");
print_bit(Lsub);
*/	
int L;
L = split_bit(Lsub,12,0);

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
hiseiki_reg_2 = hiseiki_reg;
hiseiki_a_reg_2 = hiseiki_a_reg;
s2_reg = deka_s_reg;
e2_reg = deka_e_reg;
if(carry==1){
	kekka_reg =  (Hcarry<<13)+L;
}
else{
	kekka_reg =  (Hnocarry<<13)+L;
}
adata_reg_2 = adata_reg_1;
bdata_reg_2 = bdata_reg_1;

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
/*
printf("Lsub\n");
print_bit(Lsub);
*/	
int L;
L = split_bit(Lsub,12,0);

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
hiseiki_reg_2 = hiseiki_reg;
hiseiki_a_reg_2 = hiseiki_a_reg;
s2_reg = deka_s_reg;
e2_reg = deka_e_reg;
if(carry==1){
	kekka_reg =  (Hcarry<<13)+L;
}
else{
	kekka_reg =  (Hnocarry<<13)+L;
}
adata_reg_2 = adata_reg_1;
bdata_reg_2 = bdata_reg_1;

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

int s1;
int e1;
int adata1;
int bdata1;
int esyuuseia;
int esyuuseib;

int64_t  kekka;
int s2;
int e2;
int underflow;

/* WAIT_ST */

int wadata = adata;
int wbdata = bdata;

int result = 0;

/* STAGE1 */

if((split_bit(wadata,31,31)==1&&split_bit(wbdata,31,31)==0)||(split_bit(wadata,31,31)==0&&split_bit(wbdata,31,31)==1)){
	s1 = 1;
}
else{
	s1 = 0;
}
e1 = split_bit(wadata,30,23) + split_bit(wbdata,30,23);
int kijyun = 0;
if(split_bit(wadata,30,23) == 0){
	while(1==1){
                if(split_bit(wadata,22-kijyun,22-kijyun)==1){
                        esyuuseia = kijyun;
                        adata1 = split_bit(wadata,22-kijyun,0)<<(kijyun+1);
                        break;
                }
                kijyun+=1;
                if(kijyun==22){
			if(split_bit(wadata,22-kijyun,22-kijyun)==1){
				esyuuseia = 22;
         		        adata1 = 1<<23;
        		}
			else{
				 esyuuseia = 23;
                		 adata1 = 0;
			}
                        break;
                }
	}
}
else{
	esyuuseia = 0;
	adata1 = (1<<23)+split_bit(wadata,22,0);
}

int i=0;
if(split_bit(wbdata,30,23)==0){

	while(1==1){
		if(split_bit(wbdata,22-i,22-i)==1){
			esyuuseib = i;
			bdata1 = split_bit(wbdata,22-i,0)<<(i+1);
//			printf("i %d\n",i);
			break;
		}	
		i+=1;
		if(i==22){
			if(split_bit(wbdata,22-i,22-i)==1){
				esyuuseib = 22;
				bdata1 = 1<<23;
			}
			else{
				esyuuseib = 23;
                		bdata1 = 0;	
			}
//			printf("i %d\n",i);
			break;
		}
	}	
}
else{
	esyuuseib = 0;
	bdata1 = (1<<23)+split_bit(wbdata,22,0);
}

/* STAGE2 */

s2 = s1;
e2 = e1-127-esyuuseia-esyuuseib;
//printf("e2 %d\n",e2);
if(esyuuseia == 23 || esyuuseib == 23 || (e1 < (127 + esyuuseia + esyuuseib))){
	underflow = 1;
}
else{
	underflow = 0;
}
int64_t ak = adata1;
int64_t bk = bdata1;
kekka = ak*bk;
/*
 printf("kekka ");
                         for(int im=0;im<64;im++){
                                printf("%d",(*(int*)(&kekka)>>(63-im))&0x1);
                        }
                        printf("\n");

*/
/* STAGE3 */

if(underflow == 1){
	result = 0;
}
else if(split_bit64(kekka,47,47)==1){
	result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit64(kekka,46,24));
}
else{
	if(e2==0){
		result = (s2<<31)+(split_bit64(kekka,46,24));
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit64(kekka,45,23));
	}
}

return result;
}

/*
int main(void){
float a = -0.4;
float b = -0.8;
float d = -0.8;
float c = float_get (fadd((int_get(a)),(int_get(b))));
float e = float_get (fsub((int_get(b)),(int_get(a))));
float f = float_get (fmul((int_get(b)),(int_get(d))));
printf("%f\n",c);
printf("%f\n",e);
printf("%f\n",f);

return 0;

}
*/

