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

/* WAIT_ST */

int wadata = adata;
int wbdata = bdata;

int result = 0;

/* STAGE1 */

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
if (tashi1hiki0 == 1){
	kekka = split_bit(deka,24,0) + split_bit(chibi,24,0);
}
else{
	kekka = split_bit(deka,24,0) - split_bit(chibi,24,0);
}

int kijyun = 0;

while(1==1){
	
	if(split_bit(kekka,24-kijyun,24-kijyun)==1){
		if(kijyun==0){
			result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,23,1));
		}
		if(kijyun==1){
 	        	if(whiseiki2==1){
         	        result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,22,0));
        		}
        		else{
                	result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit(kekka,22,0));
        		}	
		}
		if(kijyun==24){
			 if(e2<kijyun-1){
                               result = 0;
                        }
                        else{
                                result = (s2<<31)+((split_bit(e2,7,0)+1-kijyun)<<23);
                        }

		}
		else{
			if(e2<kijyun-1){
         		       result = 0;
        		}		
        		else{
                		result = (s2<<31)+((split_bit(e2,7,0)+1-kijyun)<<23)+(split_bit(kekka,23-kijyun,0)<<(kijyun-1));
        		}
		}
		break;
	}
	kijyun+=1;
	if(kijyun==25){
		result = 0;
		break;
	}
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
if (tashi1hiki0 == 1){
	kekka = split_bit(deka,24,0) + split_bit(chibi,24,0);
}
else{
	kekka = split_bit(deka,24,0) - split_bit(chibi,24,0);
}

int kijyun = 0;

while(1==1){
        if(split_bit(kekka,24-kijyun,24-kijyun)==1){
                if(kijyun==0){
                        result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,23,1));
                }
                if(kijyun==1){
                        if(whiseiki2==1){
                        result = (s2<<31)+((split_bit(e2,7,0)+1)<<23)+(split_bit(kekka,22,0));
                        }
                        else{
                        result = (s2<<31)+((split_bit(e2,7,0))<<23)+(split_bit(kekka,22,0));
                        }
                }
                if(kijyun==24){
                         if(e2<kijyun-1){
                               result = 0;
                        }
                        else{
                                result = (s2<<31)+((split_bit(e2,7,0)+1-kijyun)<<23);
                        }

                }
                else{
                        if(e2<kijyun-1){
                               result = 0;
                        }
                        else{
                                result = (s2<<31)+((split_bit(e2,7,0)+1-kijyun)<<23)+(split_bit(kekka,23-kijyun,0)<<(kijyun-1));
                        }
                }
                break;
        }
        kijyun+=1;
        if(kijyun==25){
                result = 0;
                break;
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
		if(split_bit(wadata,22-i,22-i)==1){
			esyuuseib = i;
			bdata1 = split_bit(wbdata,22-i,0)<<(i+1);
			break;
		}	
		i+=1;
		if(i==22){
			if(split_bit(wadata,22-i,22-i)==1){
				esyuuseib = 22;
				bdata1 = 1<<23;
			}
			else{
				esyuuseib = 23;
                		bdata1 = 0;	
			}
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


int main(void){
float a = -0.4;
float b = 0.8;
float d = -0.8;
float c = float_get (fadd((int_get(a)),(int_get(b))));
float e = float_get (fsub((int_get(b)),(int_get(d))));
float f = float_get (fmul((int_get(b)),(int_get(d))));
printf("%f\n",c);
printf("%f\n",e);
printf("%f\n",f);

return 0;

}

