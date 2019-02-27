#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "fpu/ftools.h"
#include "fpu/fpu.h"
#include "fpu/fdiv.h"
#include "fpu/fi.h"
#include "fpu/fless.h"
#include "fpu/feq.h"
#include "fpu/fsqrt.h"
#include "include/oc_sim.h"
#include "include/common.h"
#include "include/print_reg.h"

//一つ一つに命令が入る
uint64_t prom[ROMNUM];
uint32_t promjmp[ROMNUM][ROMNUM] = {0};
uint32_t promcmpd[ROMNUM][3] = {0};
//メモリ
uint32_t ram[RAMNUM];
int32_t ramfill[RAMNUM] = {-1};
int32_t ramnumber = 0;

/*
汎用レジスタ
%r0 ゼロレジスタ
%r1 スタックの先頭
%r2 スタックフレーム
%r3~%r14 int
%r15~%r26 float
%r31 リンクレジスタ
*/
int32_t reg[REGNUM];
uint32_t freg[REGNUM];
uint64_t count[256] = {0};
int cdr;
//命令
uint64_t ir;
uint32_t ir32;
//上32bit
uint32_t iru;
//下32bit
uint32_t ird;
int32_t lr;
//何命令行ったか？
uint64_t cnt;
uint32_t limit;

FILE *fpout; 
FILE *fpin;
struct timeval start;

Pc pc;
int64_t tmp;

void print_count(void);

void print_jmpd(uint32_t promjmp[ROMNUM][ROMNUM],uint32_t promcmpd[ROMNUM][3]){
printf("\n");
printf("========= jmpd result ==========\n\n");
for(int i=0;i<limit;i++){
	for(int j=0;j<limit;j++){
		if(promjmp[i][j]!=0){
			print_jmp(prom[i],i,j);
			printf("%d回実行\n",promjmp[i][j]);
		}
	}
		if(promcmpd[i][0]!=0||promcmpd[i][1]!=0||promcmpd[i][2]!=0){
			print_cmpd(prom[i],i);
			printf("ge %d回 eq %d回 le %d回\n",promcmpd[i][ge],promcmpd[i][eq],promcmpd[i][le]);
			}
}
printf("\n\n");
}
double elapsed_time(){
    struct timeval now;
    gettimeofday(&now, NULL);
    return (double)(now.tv_sec - start.tv_sec) + (double)(now.tv_usec - start.tv_usec)/1000000.0;
}

//レジスタの規定
static inline void init(void) {
    if(*outputfile == '\0'){
                    fpout = fopen("d.txt", "w");
            }
            else{
                    fpout = fopen(outputfile, "w");
            }
     if(*inputfile != '\0'){
	fpin = fopen(inputfile, "rb");
	}
// register init
	reg[0] = 0;
	reg[1] = 4*(RAMNUM-1);
	reg[2] = 0;
	lnk = 0;
	cdr = 0;
	cnt = 0;
// heap init なにこれ?
	pc.number = 0;
	pc.position = 0;
    gettimeofday(&start, NULL);

/*
	for (pc = 1; pc*4 <= reg[2]; pc++) {
		ram[pc-1] = prom[pc];
	}
*/
}

static inline int exec_op(uint32_t ir);

void print_reg(void){
	#ifndef SILENTREG
                printf("ゼロレジスタ %d\n",reg[0]);
                printf("スタックの先頭　%d\n",reg[1]);
                printf("スタックフレーム %d\n",reg[2]);
                printf("リンクレジスタ %d\n",reg[31]);
                printf("コンディションレジスタ ");
                print_cdr(cdr);
                //整数レジスタのint版とfloat版を表示
                for(int i=0;i<28;i++){
                        printf("reg[%d] int %d float %f\n",i+3,reg[i+3],*(float*)(&reg[i+3]));
                }
	#endif
}

void print_mem(void){
	#ifndef SILENTMEM
                printf("メモリ\n");
                for(int i=0;i<ramnumber;i++){
                        printf("ram[%d] = int %d float %f\n",ramfill[i],ram[ramfill[i]],*(float*)(&ram[ramfill[i]]));
                }
	#endif
}

//命令がある限りpcを進めて命令を読んで実行
int simulate(void) {
	int opcode;
	init();
	do{
		cnt+=1;
		//LIWは特別扱い
		ir = prom[pc.number];
		int op_liw = get_opcodew(prom[pc.number]);
		iru = (prom[pc.number]>>32)&(0xffffffff);
#ifndef SILENT
		if(cnt ==0) printf("初期状態\n");
		printf("pc %d\n",pc.number);
#endif 
/*
#ifdef LOG_FLAG
		_print_ir(iru, log_fp);
		_print_ir(ird, log_fp);
#endif
*/
#ifdef ANALYSE_FLAG
		analyse(iru);
		analyse(ird);
#endif
		if (!(cnt % 10000000)) { 
        		warning("."); 
                if(!(cnt % 1000000000)){
        			warning("time %.3f [sec],operation_count = %llu \n",elapsed_time(),cnt); 
                }
		}
			
		float f;	
		

		//ゼロレジスタを表示	

//一つ目の命令読み込み
if(op_liw!=LIW){

		ir32 = iru;
		opcode = get_opcode(ir32);
#ifndef SILENT
		printf("実行命令 ");
		print_op(ir32);
#endif
		//命令実行後ではなく命令実行時の現在のレジスタ状態を表示
#ifndef SILENTREG
		print_reg();
#endif
#ifndef SILENTMEM
		print_mem();
#endif
		
		if(ir32 == 0){
		printf("終了u\n");	
		break;
		}
	
		if(exec_op(ir32)!=0){
			break;
		}
}
else{
#ifndef SILENT
	printf("実行命令 ");
        print_prom(prom[pc.number],pc.number);
#endif
	//命令実行後ではなく命令実行時の現在のレジスタ状態を表示
#ifndef SILENTREG
		print_reg();
#endif
#ifndef SILENTMEM
		print_mem();
#endif
	_GRTW = ((_SIW&0xffffffff));
        pc.number+=3;             
}


	} while (cnt<=20000000000);
	fclose(fpin);
	return 0;
} 

//LIW以外の命令を実行
static inline int exec_op(uint32_t ira) {
	uint8_t opcode, funct;
	char c;
	int in;
	float ra=0.0;
	float rb=0.0;
	float rt=0.0;
	float resultf = 0.0;
	uint32_t si;
	opcode = get_opcode(ira);
    	int p;
	FILE *fp;

	switch(opcode){
		//メモリに代入
		case LOAD:
			_GRT = ram[(_GRA + _SI)];
			pc.number+=5;
			break;
		case STORE:
			ram[((_GRA + _SI))] = _GRT;
			pc.number+=1;
			break;
		case FMUL:
			_GRT = fmul(_GRA,_GRB);
			pc.number+=5;
			break;
                case CMPDI:
                        if (_GRA == _SI){
				cdr = eq;
			}
                        else if (_GRA < _SI){
				cdr = le;
			}
			else{
				cdr = 0;
			}
			pc.number += 1;
                        break;
                case BEQ:
			if(cdr==eq){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
		case FADD:
			_GRT = fadd(_GRA,_GRB);
			pc.number+=5;
			break;
		case FSUB:
			_GRT = fsub(_GRA,_GRB);
			pc.number+=5;
			break;
		case ADDI:
			_GRT = _GRA + _SI;
			pc.number+=3;
			break;
		case SUBI:
			_GRT = _GRA - _SI;
			pc.number+=3;
			break;
		case ADD:
			_GRT = _GRA + _GRB;
			pc.number+=3;
			break;
		case SUB:
			_GRT = _GRA - _GRB;
			pc.number+=3;
			break;
		case SRAWI:
			//_GRAはint32_tなので多分これで大丈夫
			_GRT = _GRA>>_SI;
			pc.number+=3;
                        break;
		case SLAWI:
			_GRT = _GRA<<_SI;
			pc.number+=3;
                        break;
		case XOR:
			_GRT = _GRA^_GRB;
			pc.number+=3;
                        break;
		case AND:
			_GRT = _GRA&_GRB;
			pc.number+=3;
                        break;
		case FDIV:
			_GRT = fdiv(_GRA,_GRB);
			pc.number+=7;
			break;
		case FTOI:
			_GRT = ftoi(_GRA);
			pc.number+=4;
			break;
		case ITOF:
			_GRT = itof(_GRA);
			pc.number+=4;
			break;
		case FSQRT:
			_GRT = fsqrt(_GRA);
			pc.number+=4;
			break;
		case LI:
			si = _SI;
			if(((si>>15)&0x1)==1){
				_GRT = (0xffff0000|(si&0xffff));
			}
			else if(((si>>15)&0x1)==0){
				_GRT = (0xffff&si);
			}
			pc.number+=3;
			break; 	
		case JUMP:
			pc.number = get_li(ira);
			break;
		case BLR:
			if(pc.number == lnk) return 1;
			pc.number = lnk;
			break;
		case BL:
			lnk = pc.number+1;
			pc.number = _LI;
			break;
		case BLRR:
			lnk = pc.number+1;
			pc.number =_GRT;
			break;
                case CMPD:
                        if (_GRA == _GRB){
				cdr = eq;
			}
                        else if (_GRA < _GRB){
				cdr = le;
			}
			else{
				cdr = 0;
			}
			pc.number += 1;
                        break;
                case CMPF:
                        if (feq(_GRA,_GRB)==1){
				cdr = eq;
			}
                        else if (fless(_GRA,_GRB)==1){
				cdr = le;
			}
			else{
				cdr = 0;
			}
			pc.number += 1;
                        break;
		case BLE:
			if(cdr==eq||cdr==le){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
		case BLT:
			if(cdr==le){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
		case BNE:
			if(cdr!=eq){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
		case BGE:
			if(cdr!=le){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
		case BGT:
			if(cdr!=le&&cdr!=eq){
			pc.number = _LI;
			}
			else{
			pc.number += 1;
			}	
			break;
                case INLL:
			fread(&p, 1, 1, fpin);
                        _GRT = (_GRT & 0xffffff00)|(p & 0xff);
			pc.number+=3;
                        break;
                case INLH:
			fread(&p, 1, 1, fpin);
                        _GRT = (_GRT & 0xffff00ff)|(p<<8 & 0xff00);
			pc.number+=3;
			pc.position = 0;
                        break;
                case INUL:
			fread(&p, 1, 1, fpin);
            		_GRT = (_GRT & 0xff00ffff)|(p<<16 & 0xff0000);
			pc.number+=3;
                        break;
                case INUH:
			fread(&p, 1, 1, fpin);
            		_GRT = (_GRT & 0x00ffffff)|(p<<24 & 0xff000000);
			pc.number+=3;
                        break;
		case OUTLL:
  			fprintf(fpout, "%c",(_GRT>>0)&0xff);
			pc.number+=1;
			break;
		case OUTLH:
  			fprintf(fpout, "%c",(_GRT>>8)&0xff);
			pc.number+=1;
	                break;
		case OUTUL:
  			fprintf(fpout, "%c",(_GRT>>16)&0xff);
			pc.number+=1;
            		break;
		case OUTUH:
	  		fprintf(fpout, "%c",(_GRT>>24)&0xff);
			pc.number+=1;
            		break;
		case NOP:
			count[opcode]+=1;
			pc.number+=1;
			break;
		case END:
			count[opcode]+=1;
			return 1;
		default	:	return 1;//break;
	}

	return 0;
}

