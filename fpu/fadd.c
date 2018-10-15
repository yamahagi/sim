#include "oc_sim.h"
#include <unistd.h>

uint32_t _fadd(int32_t i1, int32_t i2) {

uint32_t s1 = (i1>>31)&x1;
uint32_t e1 = (i1>>23)&xff;
uint32_t m1 = (i1)&xfffff;
uint32_t s1 = (i2>>31)&x1;
uint32_t e1 = (i1>>23)&xff;
uint32_t m1 = (i1)&xfffff;

uint32_t m1a;
uint32_t m2a;

m1a = if (e1==0){m1;}
	else {0x800000|m1}
m2a = if (e2==0){m2;}
	else {0x800000|m2}
uint32_t e1a;
uint32_t e2a;

e1a = if(e1 == 0) 1; else e1;
e2a = if(e2 == 0) 1; else e2;

uint32_t e2ai;

e2ai = ~e2a;

uint32_t  te;

te = e1a+e2ai;

uint32_t ce;

ce = if (get_bit(te,8,8) == 1) 0 : 1;

uint32_t tde;
uint32_t te1;

te1 = te+1;
tde = if(get_bit(te,8,8) == 1)  get_bit(te1) else (~(get_bit(te,7,0)));

uint32_t de;

de = if (|(get_bit(tde,7,5))) 31 else get_bit(tde,4,0);

uint32_t sel;

sel = if (de == 0)  (if (m1a > m2a)  0 else 1) else ce;

uint32_t ms;
uint32_t mi;
uint32_t es;
uint32_t ei;
uint32_t ss;

ms = if(sel == 0)  m1a else m2a;
mi = if(sel == 0)  m2a else m1a;
es = if(sel == 0)  e1a else e2a;
ei = if(sel == 0)  e2a else e1a;
ss = if(sel == 0)  s1 else s2;

uint64_t mie;

mie = mi<<31;

uint64_t mia;

mia = (mie >> de);

uint32_t tstck;

tstck = |(get_bit64(mia,28,0));

uint32_t mye;

mye = if (s1 == s2)  ({ms,2'b0}+get_bit(mia,55,29)) else ({ms,2'b0}-get_bit(mia,55,29));

uint32_t esi;

esi = es+1;

uint32_t eyd;
uint32_t myd;
uint32_t stck;

eyd = if(get_bit(mye,26,26) == 1)  (if(esi == 255)  255 else esi) else es;
myd = if(get_bit(mye,26,26) == 1)  (if(esi == 255)  {2'b01,25'b0} else (mye >> 1)) else mye;
stck = if(get_bit(mye,26,26) == 1)  (tstck || mye[0]) else tstck;

uint32_t se;

se = if (get_bit(myd,25,25) == 1)  0 else (
 if (get_bit(myd,24,24) == 1)  1 else (
 if (get_bit(myd,23,23) == 1)  2 else (
 if (get_bit(myd,22,22) == 1)  3 else (
 if (get_bit(myd,21,21) == 1)  4 else (
 if (get_bit(myd,20,20) == 1)  5 else (
 if (get_bit(myd,19,19) == 1)  6 else (
 if (get_bit(myd,18,18) == 1)  7 else (
 if (get_bit(myd,17,17) == 1)  8 else (
 if (get_bit(myd,16,16) == 1)  9 else (
 if (get_bit(myd,15,15) == 1)  10 else (
 if (get_bit(myd,14,14) == 1)  11 else (
 if (get_bit(myd,13,13) == 1)  12 else (
 if (get_bit(myd,12,12) == 1)  13 else (
 if (get_bit(myd,11,11) == 1)  14 else (
 if (get_bit(myd,10,10) == 1)  15 else (
 if (get_bit(myd,9,9) == 1)  16else (
 if (get_bit(myd,8,8) == 1)  17else (
 if (get_bit(myd,7,7) == 1)  18 else (
 if (get_bit(myd,6,6) == 1)  19 else (
 if (get_bit(myd,5,5) == 1)  20 else (
 if (get_bit(myd,4,4) == 1)  21 else (
 if (get_bit(myd,3,3) == 1)  22 else (
 if (get_bit(myd,2,2) == 1)  23 else (
 if (get_bit(myd,1,1) == 1)  24 else (
 if (get_bit(myd,0,0) == 1)  25 else 26 )))))))))))))))))))))))));

//負に対応
int32_t eyf;

eyf = eyd-se;

uint32_t eyr;
uint32_t myf;

eyr = if(eyf > 0)  get_bit(eyf,7,0) else 0;
myf = if(eyf > 0)  (myd << se) else (myd << (get_bit(eyd,4,0)-1));

uint32_t myr;

myr = (((myf[1]==1)&&(myf[0]==0)&&(stck==0)&&(myf[2]==1)) || ((myf[1]==1)&&(myf[0]==0)&&(s1==s2)&&(stck==1)) || ((myf[1]==1)&&(myf[0]==1))) ? (myf[26:2]+25'b1) : myf[26:2];

uint32_t eyri;

eyri = eyr + 255;

uint32_t ey;
uint32_t my;

ey = if(get_bit(myr,24,24)==1)  eyri else (if(myr[23:0]==0)  0 else eyr);
my = if(get_bit(myr,24,24)==1) 0 else (if(get_bit(myr,23,0)==0)  0 else get_bit(myr,22,0));

uint32_t sy;

sy = if((ey==0)&&(my==0)) (s1&s2&0x1) else ss;

uint32_t[0:0] nzm1;
uint32_t[0:0] nzm2;

nzm1 = |(m1[22:0]);
nzm2 = |(m2[22:0]);

y = ((e1==255)&&(e2!=255)) ? {s1,8'd255,nzm1,m1[21:0]} : (
  ((e2==255)&&(e1!=255)) ? {s2,8'd255,nzm2,m2[21:0]} : (
  ((e1==255)&&(e2==255)&&nzm2) ? {s2,8'd255,1'b1,m2[21:0]} : (
  ((e1==255)&&(e2==255)&&nzm1) ? {s1,8'd255,1'b1,m1[21:0]} : (
  ((e1==255)&&(e2==255)&&(s1==s2)) ? {s1,8'd255,23'b0} : (
  ((e1==255)&&(e2==255)) ? {1'b1,8'd255,1'b1,22'b0} : {sy,ey,my})))));

ovf = ((((mye[26]==1)&&(esi==255)) || ((myr[24]==1)&&(eyri==255)))&&((e1!=255)&&(e2!=255))) ? 1 : 0;
