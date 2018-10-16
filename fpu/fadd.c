#include "oc_sim.h"
#include <unistd.h>

int32_t _fadd(int32_t i1, int32_t i2) {

uint32_t s1 = (i1>>31)&0x1;
uint32_t e1 = (i1>>23)&0xff;
uint32_t m1 = (i1)&0x7fffff;
uint32_t s2 = (i2>>31)&0x1;
uint32_t e2 = (i2>>23)&0xff;
uint32_t m2 = (i2)&0x7fffff;

uint32_t m1a;
uint32_t m2a;

if (e1==0){m1a = m1;}
	else {m1a = 0x800000|m1}
if (e2==0){m2a = m2;}
	else {m2a = 0x800000|m2}
uint32_t e1a;
uint32_t e2a;

if(e1 == 0) e1a = 1; else e1a = e1;
if(e2 == 0) e2a = 1; else e2a = e2;

uint32_t e2ai;

e2ai = ~e2a;

uint32_t  te;

te = e1a+e2ai;

uint32_t ce;

if (get(te,8,8) == 1) ce = 0; else ce = 1;

uint32_t tde;
uint32_t te1;

te1 = te+1;
if(get(te,8,8) == 1)  tde = get(te1,7,0); else tde = (~(get(te,7,0)));

uint32_t de;

if ((get(tde,7,5))>0) de = 31; else de = get(tde,4,0);

uint32_t sel;

if (de == 0)  (if (m1a > m2a)  sel = 0; else sel=1;) else sel = ce;

uint32_t ms;
uint32_t mi;
uint32_t es;
uint32_t ei;
uint32_t ss;

if(sel == 0)  ms = m1a else ms = m2a;
if(sel == 0)  mi = m2a else mi = m1a;
if(sel == 0)  es = e1a else es = e2a;
if(sel == 0)  ei = e2a else ei = e1a;
if(sel == 0)  ss = s1 else ss = s2;

uint64_t mie;

mie = mi<<31;

uint64_t mia;

mia = (mie >> de);

uint32_t tstck;

if(get64(mia,28,0)>0) tstck = 1; else tstck = 0;

uint32_t mye;

if (s1 == s2)  mye = {ms,2'b0}+get(mia,55,29); else mye =  ({ms,2'b0}-get(mia,55,29));

uint32_t esi;

esi = es+1;

uint32_t eyd;
uint32_t myd;
uint32_t stck;

if(get(mye,26,26) == 1)  (if(esi == 255)  eyd = 255 else eyd = esi) else eyd = es;
if(get(mye,26,26) == 1)  (if(esi == 255)  myd = {2'b01,25'b0} else myd = (mye >> 1)) else myd = mye;
if(get(mye,26,26) == 1) stck = (tstck || get(mye,0,0)) else stck = tstck;

uint32_t se;

 if (get(myd,25,25) == 1)  se = 0; else (
 if (get(myd,24,24) == 1) se = 1; else (
 if (get(myd,23,23) == 1) se = 2; else (
 if (get(myd,22,22) == 1)  se =3; else (
 if (get(myd,21,21) == 1)  se =4; else (
 if (get(myd,20,20) == 1)  se =5; else (
 if (get(myd,19,19) == 1)  se =6; else (
 if (get(myd,18,18) == 1)  se =7; else (
 if (get(myd,17,17) == 1)  se =8; else (
 if (get(myd,16,16) == 1)  se =9; else (
 if (get(myd,15,15) == 1)  se =10; else (
 if (get(myd,14,14) == 1)  se =11; else (
 if (get(myd,13,13) == 1)  se =12; else (
 if (get(myd,12,12) == 1)  se =13; else (
 if (get(myd,11,11) == 1)  se =14; else (
 if (get(myd,10,10) == 1)  se =15; else (
 if (get(myd,9,9) == 1)  se =16;else (
 if (get(myd,8,8) == 1)  se =17;else (
 if (get(myd,7,7) == 1)  se =18; else (
 if (get(myd,6,6) == 1)  se =19; else (
 if (get(myd,5,5) == 1)  se =20; else (
 if (get(myd,4,4) == 1)  se =21; else (
 if (get(myd,3,3) == 1)  se =22; else (
 if (get(myd,2,2) == 1)  se =23; else (
 if (get(myd,1,1) == 1)  se =24; else (
 if (get(myd,0,0) == 1)  se =25; else se =26; )))))))))))))))))))))))));

//負に対応
int32_t eyf;

eyf = eyd-se;

uint32_t eyr;
uint32_t myf;

if(eyf > 0)  eyr=get(eyf,7,0) else eyr=0;
if(eyf > 0)  myf=(myd << se) else myf=(myd << (get(eyd,4,0)-1));

uint32_t myr;

if (((get(myf,1,1)==1)&&(get(myf,0,0)==0)&&(stck==0)&&(get(myf,2,2)==1)) || ((get(myf,1,1)==1)&&(get(myf,0,0)==0)&&(s1==s2)&&(stck==1)) || ((get(myf,1,1)==1)&&(get(myf,0,0)==1)))
myr = (get(myf,26,2)+0x1ffffff);
else myr = get(myf,26,2);

uint32_t eyri;

eyri = eyr + 0xff;

uint32_t ey;
uint32_t my;

if(get(myr,24,24)==1)  ey = eyri; else (if(get(myr,23,0)==0)  ey = 0; else ey = eyr;)
if(get(myr,24,24)==1) my=0 else (if(get(myr,23,0)==0)  my=0; else my=get(myr,22,0);)

uint32_t sy;

if((ey==0)&&(my==0)) sy=(s1&s2&0x1); else sy = ss;

uint32_t nzm1;
uint32_t nzm2;

nzm1 = if(get(m1,22,0)>0) 1; else 0;
nzm2 = if(get(m2,22,0)>0) 1; else 0;

uint32_t y;
uint32_t ovf;

  if((e1==255)&&(e2!=255))  y={s1,8'd255,nzm1,m1[21:0]}; else (
  if((e2==255)&&(e1!=255))  y={s2,8'd255,nzm2,m2[21else0]}; else (
  if((e1==255)&&(e2==255)&&nzm2)  y={s2,8'd255,1'b1,m2[21else0]}; else (
  if((e1==255)&&(e2==255)&&nzm1)  y={s1,8'd255,1'b1,m1[21else0]}; else (
  if((e1==255)&&(e2==255)&&(s1==s2))  y={s1,8'd255,23'b0}; else (
  if((e1==255)&&(e2==255))  y={1'b1,8'd255,1'b1,22'b0}; else y={sy,ey,my};)))));

if((((get(mye,26,26)==1)&&(esi==255)) || ((get(myr,24,24)==1)&&(eyri==255)))&&((e1!=255)&&(e2!=255))) ovf =  1 else ovf = 0;
