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
#define WAIT_ST 0
#define STAGE1 1
#define STAGE2 2
#define STAGE3 3

/*
FADD、FSUB、FMUL、FDIVでそれぞれの関数定義に飛べます。
*/


/*     FADD       */
int32_t fadd(int32_t adata,int32_t bdata){

int s1;
int e1;
int deka;
int chibi;
int tashi1hiki0;
int whiseiki1;

int kekka;
int s2;
int e2;
int whiseiki2;

int wadata = adata;
int wbdata = bdata;

int result = 0;

if(split_bit(wadata,30,23)==0&&split_bit(wbdata,30,23)==0){
	whiseiki1 = 1;
}
else{
	whiseiki1 = 0;
}

if(split_bit(wadata,31,31) == split_bit(wbdata,31,31)){
	tashi1hiki0 = 1;
}
else{
	tashi1hiki0 = 0;
}

if(split_bit(wadata,30,23)>split_bit(wbdata,30,23) || (split_bit(wadata,30,23)==split_bit(wbdata,30,23) && split_bit(wadata,22,0)==split_bit(wbdata,22,0))){

	s1 = split_bit(wadata,31,31);
	e1 = split_bit(wadata,30,23);
	if(split_bit(wadata,30,23)==0){
		deka = split_bit(wadata,22,0);
	}
	else{
		deka = 0x800000|split_bit(wadata,22,0);
	}
	if(split_bit(wbdata,30,23)==0){
                chibi = split_bit(wbdata,22,0)>>(split_bit(wadata,30,23)-split_bit(wbdata,30,23));
        }
        else{
                chibi = (0x800000|split_bit(wbdata,22,0))>>(split_bit(wadata,30,23)-split_bit(wbdata,30,23));
        }
}
else{
	s1 = split_bit(wbdata,31,31);
	e1 = split_bit(wbdata,30,23);
	if(split_bit(wbdata,30,23)==0){
		deka = split_bit(wbdata,22,0);
	}
	else{
		deka = 0x800000|split_bit(wbdata,22,0);
	}
	if(split_bit(wadata,30,23)==0){
                chibi = split_bit(wadata,22,0)>>(split_bit(wbdata,30,23)-split_bit(wadata,30,23));
        }
        else{
                chibi = (0x800000|split_bit(wadata,22,0))>>(split_bit(wbdata,30,23)-split_bit(wadata,30,23));
        }

}	

whiseiki2 = whiseiki1;
s2 = s1;
e2 = e1;
int kijyun = 1;
if (tashi1hiki0 == 1){
	kekka = split_bit(deka,24,0) + split_bit(chibi,24,0);
}
else{
	kekka = split_bit(deka,24,0) - split_bit(chibi,24,0);
}

if(split_bit(kekka,24,24) == 1){
	result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,23,1));
}
else if(split_bit(kekka,23,23) == 1){
        if(whiseiki2==1){
		result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,22,0));
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit(kekka,22,0));
	}
}
else if(split_bit(kekka,22,22) == 1){
        if(e2<1){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-1)<<23)+(split_bit(kekka,21,0)<<1);
	}
}
else if(split_bit(kekka,21,21) == 1){
        if(e2<2){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-2)<<23)+(split_bit(kekka,20,0)<<2);
	}
}
else if(split_bit(kekka,20,20) == 1){
        if(e2<3){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-3)<<23)+(split_bit(kekka,19,0)<<3);
	}
}
else if(split_bit(kekka,19,19) == 1){
        if(e2<4){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-4)<<23)+(split_bit(kekka,18,0)<<4);
	}
}
else if(split_bit(kekka,18,18) == 1){
        if(e2<5){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-5)<<23)+(split_bit(kekka,17,0)<<5);
	}
}
else if(split_bit(kekka,17,17) == 1){
        if(e2<6){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-6)<<23)+(split_bit(kekka,16,0)<<6);
	}
}
else if(split_bit(kekka,16,16) == 1){
        kijyun = 7;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,15,15) == 1){
        kijyun = 8;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,14,14) == 1){
        kijyun = 9;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,13,13) == 1){
        kijyun = 10;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,12,12) == 1){
        kijyun = 11;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,11,11) == 1){
        kijyun = 12;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,10,10) == 1){
        kijyun = 13;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,9,9) == 1){
        kijyun = 14;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,8,8) == 1){
        kijyun = 15;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,7,7) == 1){
        kijyun = 16;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,6,6) == 1){
        kijyun = 17;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,5,5) == 1){
        kijyun = 18;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,4,4) == 1){
        kijyun = 19;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,3,3) == 1){
        kijyun = 20;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,2,2) == 1){
        kijyun = 21;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,1,1) == 1){
        kijyun = 22;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,0,0) == 1){
        kijyun = 23;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23);
	}
}
else{
	result = 0;
}

return result;
}

/*     FSUB      */
int32_t fsub(int32_t adata,int32_t bdata){

int s1;
int e1;
int deka;
int chibi;
int tashi1hiki0;
int whiseiki1;

int kekka;
int s2;
int e2;
int whiseiki2;

int wadata = adata;
int wbdata;
if(split_bit(bdata,31,31)==1){
		wbdata = split_bit(bdata,30,0);
}
else{
		wbdata = (1<<31)+split_bit(bdata,30,0);
}

int result = 0;

if(split_bit(wadata,30,23)==0&&split_bit(wbdata,30,23)==0){
	whiseiki1 = 1;
}
else{
	whiseiki1 = 0;
}

if(split_bit(wadata,31,31) == split_bit(wbdata,31,31)){
	tashi1hiki0 = 1;
}
else{
	tashi1hiki0 = 0;
}

if(split_bit(wadata,30,23)>split_bit(wbdata,30,23) || (split_bit(wadata,30,23)==split_bit(wbdata,30,23) && split_bit(wadata,22,0)>=split_bit(wbdata,22,0))){

	s1 = split_bit(wadata,31,31);
	e1 = split_bit(wadata,30,23);
	if(split_bit(wadata,30,23)==0){
		deka = split_bit(wadata,22,0);
	}
	else{
		deka = 0x800000|split_bit(wadata,22,0);
	}
	if(split_bit(wbdata,30,23)==0){
                chibi = split_bit(wbdata,22,0)>>(split_bit(wadata,30,23)-split_bit(wbdata,30,23));
        }
        else{
                chibi = (0x800000|split_bit(wbdata,22,0))>>(split_bit(wadata,30,23)-split_bit(wbdata,30,23));
        }
}
else{
	s1 = split_bit(wbdata,31,31);
	e1 = split_bit(wbdata,30,23);
	if(split_bit(wbdata,30,23)==0){
		deka = split_bit(wbdata,22,0);
	}
	else{
		deka = 0x800000|split_bit(wbdata,22,0);
	}
	if(split_bit(wadata,30,23)==0){
                chibi = split_bit(wadata,22,0)>>(split_bit(wbdata,30,23)-split_bit(wadata,30,23));
        }
        else{
                chibi = (0x800000|split_bit(wadata,22,0))>>(split_bit(wbdata,30,23)-split_bit(wadata,30,23));
        }

}	

whiseiki2 = whiseiki1;
s2 = s1;
e2 = e1;
int kijyun = 1;
if (tashi1hiki0 == 1){
	kekka = split_bit(deka,24,0) + split_bit(chibi,24,0);
}
else{
	kekka = split_bit(deka,24,0) - split_bit(chibi,24,0);
}

if(split_bit(kekka,24,24) == 1){
	result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,23,1));
}
else if(split_bit(kekka,23,23) == 1){
        if(whiseiki2==1){
		result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,22,0));
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit(kekka,22,0));
	}
}
else if(split_bit(kekka,22,22) == 1){
        if(e2<1){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-1)<<23)+(split_bit(kekka,21,0)<<1);
	}
}
else if(split_bit(kekka,21,21) == 1){
        if(e2<2){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-2)<<23)+(split_bit(kekka,20,0)<<2);
	}
}
else if(split_bit(kekka,20,20) == 1){
        if(e2<3){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-3)<<23)+(split_bit(kekka,19,0)<<3);
	}
}
else if(split_bit(kekka,19,19) == 1){
        if(e2<4){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-4)<<23)+(split_bit(kekka,18,0)<<4);
	}
}
else if(split_bit(kekka,18,18) == 1){
        if(e2<5){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-5)<<23)+(split_bit(kekka,17,0)<<5);
	}
}
else if(split_bit(kekka,17,17) == 1){
        if(e2<6){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-6)<<23)+(split_bit(kekka,16,0)<<6);
	}
}
else if(split_bit(kekka,16,16) == 1){
        kijyun = 7;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,15,15) == 1){
        kijyun = 8;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,14,14) == 1){
        kijyun = 9;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,13,13) == 1){
        kijyun = 10;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,12,12) == 1){
        kijyun = 11;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,11,11) == 1){
        kijyun = 12;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,10,10) == 1){
        kijyun = 13;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,9,9) == 1){
        kijyun = 14;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,8,8) == 1){
        kijyun = 15;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,7,7) == 1){
        kijyun = 16;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,6,6) == 1){
        kijyun = 17;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,5,5) == 1){
        kijyun = 18;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,4,4) == 1){
        kijyun = 19;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,3,3) == 1){
        kijyun = 20;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,2,2) == 1){
        kijyun = 21;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,1,1) == 1){
        kijyun = 22;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23)+(split_bit(kekka,22-kijyun,0)<<kijyun);
	}
}
else if(split_bit(kekka,0,0) == 1){
        kijyun = 23;
	if(e2<kijyun){
		result = 0;
	}
	else{
		result = (s2<<31)+((split_bit(e2,7,0)-kijyun)<<23);
	}
}
else{
	result = 0;
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

int wadata = adata;
int wbdata = bdata;

int result = 0;

if((split_bit(wadata,31,31)==1&&split_bit(wbdata,31,31)==0)|(split_bit(wadata,31,31)==0&&split_bit(wbdata,31,31)==1)){
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
                        break;
                }
        }
        if(kijyun==22&&split_bit(wadata,22-kijyun,22-kijyun)==1){
                esyuuseia = 22;
                adata1 = 1<<23;
        }
        else if(kijyun==22){
                esyuuseia = 23;
                adata1 = 0;
        }
}
else{
	esyuuseia = 0;
	adata1 = (1<<23)+split_bit(wadata,22,0);
}

int i=0;
if(split_bit(wbdata,30,23)==0){

	//ifをfor文で代用したつもり
	while(1==1){
		if(split_bit(wadata,22-i,22-i)==1){
			esyuuseib = i;
			bdata1 = split_bit(wbdata,22-i,0)<<(i+1);
			break;
		}	
		i+=1;
		if(i==22){
			break;
		}
	}	
	if(i==22&&split_bit(wadata,22-i,22-i)==1){
		esyuuseib = 22;
		bdata1 = 1<<23;
	}
	else if(i==22){
		esyuuseib = 23;
		bdata1 = 0;
	}
}
else{
	esyuuseib = 0;
	bdata1 = (1<<23)+split_bit(wbdata,22,0);
}

s2 = s1;
e2 = e1-127-esyuuseia-esyuuseib;
if(esyuuseia == 23 || esyuuseib == 23 || (e1 < (127 + esyuuseia + esyuuseib))){
	underflow = 1;
}
else{
	underflow = 0;
}
int64_t ak = adata1;
int64_t bk = bdata1;
kekka = ak*bk;

if(underflow == 1){
	result = 0;
}
else if(split_bit64(kekka,47,47)==1){
		printf("47\n");
	result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit64(kekka,46,24));
}
else{
	if(e2==0){
		printf("e20\n");
		result = (s2<<31)+(split_bit64(kekka,46,24));
	}
	else{
		printf("else\n");
		result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit64(kekka,45,23));
	}
}

return result;
}
/*
int main(void){
float a = 0.4;
float b = 0.4;
float d = 0.8;
float c = float_get (fadd((int_get(a)),(int_get(b))));
float e = float_get (fsub((int_get(b)),(int_get(d))));
float f = float_get (fmul((int_get(b)),(int_get(d))));
printf("%f\n",c);
printf("%f\n",e);
printf("%f\n",f);

return 0;

}
*/
