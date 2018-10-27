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
#include <math.h>

//高速化したくて関数呼び出し減らすために作ったけど意味あるのか？

int32_t fsub(int32_t b,int32_t c){
	uint32_t sb = (b>>31)&0x1;
        uint32_t expb = (b>>23)&0xff;
        uint32_t fracb = b&0x7fffff;
	uint32_t sc = (c>>31)&0x1;
        uint32_t expc = (c>>23)&0xff;
        uint32_t fracc = c&0x7fffff;

        float ab = 0;
        float ac = 0;
        int i;
        int j;
        for(i=0;i<23;i++){
                float b = 0.5;
                if (((fracb>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ab+=b;
                }
		b=0.5;
                if (((fracc>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ac+=b;
                }
        }

        int expb1 = expb-127;
        int expc1 = expc-127;
        float kb=1.0;
        float kc=1.0;
        if(expb1>=0){
                for(i=0;i<expb1;i++){
                        kb*=2;
                }
        }
        else{
                for(i=0;i<(-expb1);i++){
                        kb/=2;
                }
        }
        if(expc1>=0){
                for(i=0;i<expc1;i++){
                        kc*=2;
                }
        }
        else{
                for(i=0;i<(-expc1);i++){
                        kc/=2;
                }
        }

        float lb;
	float lc;

        if(sb==0){
                lb = kb*(1+ab);
        }
        else{
                lb = -kb*(1+ab);
        }
        if(sc==0){
                lc = kc*(1+ac);
        }
        else{
                lc = -kc*(1+ac);
        }
	float l;
	l = lb-lc;

	union { float f; int i; } a;
    a.f = l;

    int32_t d=0;
    for( i = 31; i >= 0; i-- ){
        d = d | (((a.i>>i)&1)<<i);
    }

    /* 指数部（ 1ビット ）、指数部（ 8ビット ）、仮数部（ 23ビット ）を取り出し>ます */

    return d;
}
int32_t fadd(int32_t b,int32_t c){
	uint32_t sb = (b>>31)&0x1;
        uint32_t expb = (b>>23)&0xff;
        uint32_t fracb = b&0x7fffff;
	uint32_t sc = (c>>31)&0x1;
        uint32_t expc = (c>>23)&0xff;
        uint32_t fracc = c&0x7fffff;

        float ab = 0;
        float ac = 0;
        int i;
        int j;
        for(i=0;i<23;i++){
                float b = 0.5;
                if (((fracb>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ab+=b;
                }
		b=0.5;
                if (((fracc>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ac+=b;
                }
        }

        int expb1 = expb-127;
        int expc1 = expc-127;
        float kb=1.0;
        float kc=1.0;
        if(expb1>=0){
                for(i=0;i<expb1;i++){
                        kb*=2;
                }
        }
        else{
                for(i=0;i<(-expb1);i++){
                        kb/=2;
                }
        }
        if(expc1>=0){
                for(i=0;i<expc1;i++){
                        kc*=2;
                }
        }
        else{
                for(i=0;i<(-expc1);i++){
                        kc/=2;
                }
        }

        float lb;
	float lc;

        if(sb==0){
                lb = kb*(1+ab);
        }
        else{
                lb = -kb*(1+ab);
        }
        if(sc==0){
                lc = kc*(1+ac);
        }
        else{
                lc = -kc*(1+ac);
        }
	float l;
	l = lb*lc;

	union { float f; int i; } a;
    a.f = l;

    int32_t d=0;
    for( i = 31; i >= 0; i-- ){
        d = d | (((a.i>>i)&1)<<i);
    }

    /* 指数部（ 1ビット ）、指数部（ 8ビット ）、仮数部（ 23ビット ）を取り出し>ます */

    return d;
}
int32_t fmul(int32_t b,int32_t c){
	uint32_t sb = (b>>31)&0x1;
        uint32_t expb = (b>>23)&0xff;
        uint32_t fracb = b&0x7fffff;
	uint32_t sc = (c>>31)&0x1;
        uint32_t expc = (c>>23)&0xff;
        uint32_t fracc = c&0x7fffff;

        float ab = 0;
        float ac = 0;
        int i;
        int j;
        for(i=0;i<23;i++){
                float b = 0.5;
                if (((fracb>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ab+=b;
                }
		b=0.5;
                if (((fracc>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ac+=b;
                }
        }

        int expb1 = expb-127;
        int expc1 = expc-127;
        float kb=1.0;
        float kc=1.0;
        if(expb1>=0){
                for(i=0;i<expb1;i++){
                        kb*=2;
                }
        }
        else{
                for(i=0;i<(-expb1);i++){
                        kb/=2;
                }
        }
        if(expc1>=0){
                for(i=0;i<expc1;i++){
                        kc*=2;
                }
        }
        else{
                for(i=0;i<(-expc1);i++){
                        kc/=2;
                }
        }

        float lb;
	float lc;

        if(sb==0){
                lb = kb*(1+ab);
        }
        else{
                lb = -kb*(1+ab);
        }
        if(sc==0){
                lc = kc*(1+ac);
        }
        else{
                lc = -kc*(1+ac);
        }
	float l;
	l = lb+lc;

	union { float f; int i; } a;
    a.f = l;

    int32_t d=0;
    for( i = 31; i >= 0; i-- ){
        d = d | (((a.i>>i)&1)<<i);
    }

    /* 指数部（ 1ビット ）、指数部（ 8ビット ）、仮数部（ 23ビット ）を取り出し>ます */

    return d;
}

int32_t fdiv(int32_t b,int32_t c){
	uint32_t sb = (b>>31)&0x1;
        uint32_t expb = (b>>23)&0xff;
        uint32_t fracb = b&0x7fffff;
	uint32_t sc = (c>>31)&0x1;
        uint32_t expc = (c>>23)&0xff;
        uint32_t fracc = c&0x7fffff;

        float ab = 0;
        float ac = 0;
        int i;
        int j;
        for(i=0;i<23;i++){
                float b = 0.5;
                if (((fracb>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ab+=b;
                }
		b=0.5;
                if (((fracc>>(23-i-1))&0x1)==1){
                        for(j=0;j<i;j++){
                                b = b/2;
                        }
                ac+=b;
                }
        }

        int expb1 = expb-127;
        int expc1 = expc-127;
        float kb=1.0;
        float kc=1.0;
        if(expb1>=0){
                for(i=0;i<expb1;i++){
                        kb*=2;
                }
        }
        else{
                for(i=0;i<(-expb1);i++){
                        kb/=2;
                }
        }
        if(expc1>=0){
                for(i=0;i<expc1;i++){
                        kc*=2;
                }
        }
        else{
                for(i=0;i<(-expc1);i++){
                        kc/=2;
                }
        }

        float lb;
	float lc;

        if(sb==0){
                lb = kb*(1+ab);
        }
        else{
                lb = -kb*(1+ab);
        }
        if(sc==0){
                lc = kc*(1+ac);
        }
        else{
                lc = -kc*(1+ac);
        }
	float l;
	l = lb/lc;

	union { float f; int i; } a;
    a.f = l;

    int32_t d=0;
    for( i = 31; i >= 0; i-- ){
        d = d | (((a.i>>i)&1)<<i);
    }

    /* 指数部（ 1ビット ）、指数部（ 8ビット ）、仮数部（ 23ビット ）を取り出し>ます */

    return d;
}
