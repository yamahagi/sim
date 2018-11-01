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

int wadata;
int wbdata;

int result;

int adata1;
int bdata1;
int x02bai;
int x02jyou;

int adata2;
int bdata2;
int x02bai2;
int ax02s1;
int ax02e1;
int bdatakari;
int x2jyoukari;

int adata3;
int bdata3;
int x02bai3;
int64_t ax02jyoukekka;
int ax02jyous2;
int ax02jyoue2;

int adata4;
int bdata4;
int x02bai4;
int minusax02jyou;

int adata5;
int bdata5;
int invbs1;
int invbe1;
int invbdeka;
int invbchibi;
int invbtashi1hiki0;

int adata6;
int bdata6;
int invbkekka;
int invbs2;
int invbe2;

int adata7;
int bdata7;
int invb;

int s1;
int e1;
int adatakari;
int invbkari;
int esyuuseia;
int esyuuseib;

int64_t kekka;
int s2;
int e2;
int underflow;

/* WAIT_ST */

wadata = adata;
wbdata = bdata;

/* STAGE1 */

adata1 = wadata;
bdata1 = wbdata;

//TABLEを使わず直接呼び出します

int wsplit = split_bit(wbdata,22,12);
float x02baif = (2048.0 / ((float)wsplit + 2048.0)) + (2048.0 / (((float)wsplit+1.0) + 2048.0));
float x0 = x02baif/2.0;
float x02jyouf = x0*x0;

x02bai = *(int*)(&x02baif);
x02jyou = *(int*)(&x02jyouf);



/*  STAGE2 */

adata2 = adata1;
bdata2 = bdata1;
x02bai2 = x02bai;
ax02s1 = 0;
ax02e1 = 127+split_bit(x02jyou,30,23);
bdatakari = (1<<23)+split_bit(bdata1,22,0);
x2jyoukari = (1<<23)+split_bit(x02jyou,22,0);

/*  STAGE3  */

adata3 = adata2;
bdata3 = bdata2;
x02bai3 = x02bai2;
ax02jyous2 = ax02s1;
ax02jyoue2 = ax02e1 - 127;
int64_t bdatakari64 = bdatakari;
int64_t x2jyoukari64 = x2jyoukari;
ax02jyoukekka = bdatakari64 * x2jyoukari64;

/*  STAGE4  */
adata4 = adata3;
bdata4 = bdata3;
x02bai4 = x02bai3;
if(split_bit64(ax02jyoukekka,47,47)==1){

	if(ax02jyous2 == 1){
		minusax02jyou = ((split_bit(ax02jyoue2,7,0)+1)<<23)+(split_bit64(ax02jyoukekka,46,24));
	}
	else{
		minusax02jyou = (1<<31)+((split_bit(ax02jyoue2,7,0)+1)<<23)+(split_bit64(ax02jyoukekka,46,24));
	}
}
else{
	if(ax02jyous2 == 1){
		minusax02jyou = ((split_bit(ax02jyoue2,7,0))<<23)+(split_bit64(ax02jyoukekka,45,23));
	}
	else{
		minusax02jyou = (1<<31)+((split_bit(ax02jyoue2,7,0))<<23)+(split_bit64(ax02jyoukekka,45,23));
	}

}
/*  STAGE5  */
adata5 = adata4;
bdata5 = bdata4;

int idou;

if((split_bit(x02bai4,31,31))==(split_bit(minusax02jyou,31,31))){
	invbtashi1hiki0 = 1;
}
else{
	invbtashi1hiki0 = 0;
}

if(((split_bit(x02bai4,30,23))>(split_bit(minusax02jyou,30,23)))||((split_bit(x02bai4,30,23))==(split_bit(minusax02jyou,30,23)) && ((split_bit(x02bai4,22,0))>=(split_bit(minusax02jyou,22,0))))){
	idou = ((split_bit(x02bai4,30,23))-(split_bit(minusax02jyou,30,23)));
	invbs1 = (split_bit(x02bai4,31,31));
	invbe1 = (split_bit(x02bai4,30,23));
	invbdeka = (1<<23)+(split_bit(x02bai4,22,0));
	if(idou<32){
		invbchibi = ((1<<23)+(split_bit(minusax02jyou,22,0)))>>((split_bit(x02bai4,30,23))-(split_bit(minusax02jyou,30,23)));
	}
	else{
		invbchibi = 0;
	}
}
else{
	idou = ((split_bit(minusax02jyou,30,23))-(split_bit(x02bai4,30,23)));
	invbs1 = (split_bit(minusax02jyou,31,31));
	invbe1 = (split_bit(minusax02jyou,30,23));
	invbdeka = (1<<23)+(split_bit(minusax02jyou,22,0));
	if(idou<32){
		invbchibi = ((1<<23)+(split_bit(x02bai4,22,0)))>>((split_bit(minusax02jyou,30,23))-(split_bit(x02bai4,30,23)));
	}
	else{
		invbchibi=0;
	}
}

/*  STAGE6  */

adata6 = adata5;
bdata6 = bdata5;
invbs2 = invbs1;
invbe2 = invbe1;

if (invbtashi1hiki0 == 1){
	invbkekka = split_bit(invbdeka,24,0) + split_bit(invbchibi,24,0);
}
else{
	invbkekka = split_bit(invbdeka,24,0) - split_bit(invbchibi,24,0);
}

/*  STAGE7  */
adata7 = adata6;
bdata7 = bdata6;

int kijyun = 0;

while(1==1){
           if(split_bit(invbkekka,24-kijyun,24-kijyun)==1){
           	if(kijyun == 0){
			invb = (invbs2<<31)+((split_bit(invbe2,7,0)+1-kijyun)<<23)+split_bit(invbkekka,23-kijyun,1);
		}
		else{
			invb = (invbs2<<31)+((split_bit(invbe2,7,0)+1-kijyun)<<23)+(split_bit(invbkekka,23-kijyun,0)<<(kijyun-1));
                }
		break;
           }
           kijyun+=1;
           if(kijyun==24){
                if(split_bit(invbkekka,24-kijyun,24-kijyun)==1){
        		invb = (invbs2<<31)+((split_bit(invbe2,7,0)+1-kijyun)<<23);
		}
		else{
			invb = 0;
		}
		break;
           }
}

/* STAGE8 */

if(split_bit(adata7,31,31)!=(split_bit(bdata7,31,31))){
	s1 = 1;
}
else{
	s1 = 0;
}
e1 = split_bit(adata7,30,23) + 127 + split_bit(invb,30,23);
esyuuseib = split_bit(bdata,30,23);
kijyun = 0;
if(split_bit(adata7,30,23) == 0){
        while(1==1){
                if(split_bit(adata7,22-kijyun,22-kijyun)==1){
                        esyuuseia = kijyun;
                        adatakari = split_bit(adata7,22-kijyun,0)<<(kijyun+1);
                        break;
                }
                kijyun+=1;
                if(kijyun==22){
        		if(split_bit(adata7,22-kijyun,22-kijyun)==1){
                		esyuuseia = 22;
                		adatakari = 1<<23;
        		}
			else{
				esyuuseia = 23;
                		adatakari = 0;
			}
		        break;
                }
        }
}
else{
        esyuuseia = 0;
        adatakari = (1<<23)+split_bit(adata7,22,0);
}

invbkari = (1<<23) + split_bit(invb,22,0);

/* STAGE9 */
s2 = s1;
if(esyuuseia == 23 || (e1<(esyuuseib + esyuuseia + 127))){
	underflow = 1;
}
else{
	underflow = 0;
}
e2 = e1 - esyuuseia - esyuuseib -127;

int64_t adatakari64 = adatakari;
int64_t invbkari64 = invbkari;

kekka = adatakari64 * invbkari64;

/* STAGE10 */

if(underflow == 1){
	result = 0;
}
else{
	if(split_bit64(kekka,47,47) == 1){
		result = (s2<<31)+((split_bit(e2,7,0)+1)<<23) +(split_bit64(kekka,46,24));
	}
	else{
		if(e2==0){
			result = (s2<<31) + (split_bit64(kekka,46,24));
		}
		else{
			result = (s2<<31)+((split_bit(e2,7,0))<<23) +(split_bit64(kekka,45,23));
		}
	}
}


return result;

}
