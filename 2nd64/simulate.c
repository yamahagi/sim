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
#include "include/oc_sim.h"
#include "include/common.h"

//一つ一つに命令が入る
uint64_t prom[ROMNUM];
uint32_t promjmp[ROMNUM][ROMNUM] = {0};
uint32_t promcmpd[ROMNUM][3] = {0};
//メモリ
uint32_t ram[RAMNUM];
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
uint32_t count[256] = {0};
int cdr;
//命令
uint64_t ir;
//リンクレジスタ
int32_t lr;
//何命令行ったか？
uint32_t cnt;
uint32_t limit;


FILE *fpout; 
struct timeval start;

int pc;

int tmp;

void print_count(void);

void print_jmp(uint32_t promjmp[ROMNUM][ROMNUM]){
printf("========= jump result ==========\n\n");
for(int i=0;i<limit;i++){
	for(int j=0;j<limit;j++){
		if(promjmp[i][j]!=0){
				print_prom((prom[i]),i);
			printf("%d回実行\n",promjmp[i][j]);
		}
	}
}
printf("\n\n");
}

void print_cmpd(uint32_t promcmpd[ROMNUM][3]){
printf("========= cmpd result ==========\n\n");
for(int i=0;i<limit;i++){
		if(promcmpd[i][0]!=0||promcmpd[i][1]!=0||promcmpd[i][2]!=0){
				print_prom((prom[i]),i);
			printf("ge %d回 eq %d回 le %d回\n",promcmpd[i][ge],promcmpd[i][eq],promcmpd[i][le]);
			}
}
printf("\n\n");
}

void print_jmpd(uint32_t promjmp[ROMNUM][ROMNUM],uint32_t promcmpd[ROMNUM][3]){
printf("========= jmpd result ==========\n\n");
for(int i=0;i<limit;i++){
	for(int j=0;j<limit;j++){
		if(promjmp[i][j]!=0){
				print_prom((prom[i]),i);
			printf("To %d %d回実行\n",j,promjmp[i][j]);
		}
	}
		if(promcmpd[i][0]!=0||promcmpd[i][1]!=0||promcmpd[i][2]!=0){
				print_prom((prom[i]),i);
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
                    fpout = fopen("d.txt", "a");
            }
            else{
                    fpout = fopen(outputfile, "a");
            }
// register init
	reg[0] = 0;
	reg[1] = 4*(RAMNUM-1);
	reg[2] = prom[0];
	lnk = 0;
	cdr = 0;
	tmp = 0;
// heap init なにこれ?
	pc = 0;
    gettimeofday(&start, NULL);
/*
	for (pc = 1; pc*4 <= reg[2]; pc++) {
		ram[pc-1] = prom[pc];
	}
*/
}

static inline int exec_op(uint64_t ir);


//命令がある限りpcを進めて命令を読んで実行
int simulate(void) {
	init();
	do{
		

		ir = prom[pc];
#ifndef SILENT
		if(cnt ==0) printf("初期状態\n");
		printf("pc %d\n",pc);
#endif 

#ifdef LOG_FLAG
		_print_ir(ir, log_fp);
#endif
#ifdef ANALYSE_FLAG
		analyse(ir);
#endif
		if (!(cnt % 1000000)&&(cnt!=0)) { 
        		warning("."); 
                if(!(cnt % 100000000)){
        			warning("time %.3f [sec],operation_count = %ld hp = %d \n",elapsed_time(),cnt,ram[0]); 
		}
		break;
		}
			
		float f;	
		

		//ゼロレジスタを表示	
#ifndef SILENT


		printf("実行命令 ");
		print_op(ir);
		//命令実行後ではなく命令実行時の現在のレジスタ状態を表示
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
		if(ir == 0){
		printf("終了u\n");	
		break;
		}

		pc++;
	
		if(exec_op(ir)!=0){
			break;
		}
		cnt++;



	} while (1==1);
	print_jmpd(promjmp,promcmpd);
	return 0;
} 


static inline int exec_op(uint64_t ir) {
	uint8_t opcode, funct;
	union {
		uint32_t i;
		float f;
	} a, b, out;
	char c;
	float ra=0.0;
	float rb=0.0;
	float rt=0.0;
	float resultf = 0.0;
	int32_t si;
	opcode = get_opcodew(ir);
    	int p;
	

	switch(opcode){
		case ADDI:
			_GRT = _GRA + _SI;
			count[opcode]+=1;
			break;
		case SUBI:
			_GRT = _GRA - _SI;
			count[opcode]+=1;
			break;
		case ADD:
			_GRT = _GRA + _GRB;
			count[opcode]+=1;
			break;
		case SUB:
			_GRT = _GRA - _GRB;
			count[opcode]+=1;
			break;
		case SRAWI:
			//_GRAはint32_tなので多分これで大丈夫
			_GRT = _GRA>>_SI;
			count[opcode]+=1;
                        break;
		case SLAWI:
			_GRT = _GRA<<_SI;
			count[opcode]+=1;
                        break;
		case FADD:
			_GRT = fadd(_GRA,_GRB);
			count[opcode]+=1;
			break;
		case FSUB:
			_GRT = fsub(_GRA,_GRB);
			count[opcode]+=1;
			break;
		case FMUL:
			_GRT = fmul(_GRA,_GRB);
			count[opcode]+=1;
			break;
		case FDIV:
			_GRT = fdiv(_GRA,_GRB);
			count[opcode]+=1;
			break;
		case FTOI:
			_GRT = ftoi(_GRA);
			count[opcode]+=1;
			break;
		case ITOF:
			_GRT = itof(_GRA);
			count[opcode]+=1;
			break;
		//メモリから代入 ram
		case LOAD:
			_GRT = ram[(_GRA + _SI)];
			count[opcode]+=1;
			break;
		//メモリに代入
		case STORE:
			ram[((_GRA + _SI))] = _GRT;
			count[opcode]+=1;
			break;
		case LI:
			si = _SI;
			if(((si>>31)&0x1)==1){
				_GRT = (0xffff0000|(si&0xffff));
			}
			else if(((si>>31)&0x1)==0){
				_GRT = (0xffff&si);
			}
			count[opcode]+=1;
			break; 	
		case LIW:
			//_GRT = (_SI<<16) | (_GRT & ((1<<16)-1)) ;
			_GRTW = ((_SIW&0xffffffff));
			count[opcode]+=1;
			break; 	
		case JUMP:
			/*
			if (pc-1 == get_li(ir)) {
				return 1;
			}
			*/
			promjmp[pc-1][get_li(ir)]+=1;
			pc = get_li(ir);
			count[opcode]+=1;
			break;
		case BLR:
			if(pc == lnk-1) return 1;
			promjmp[pc-1][lnk]+=1;
			pc = lnk;
			count[opcode]+=1;
			break;
		case BL:
			promjmp[pc-1][_LI]+=1;
			lnk = pc;
			pc = _LI;
			count[opcode]+=1;
			break;
		case BLRR:
			promjmp[pc-1][_GRT]+=1;
			lnk = pc;
			pc =_GRT;
			count[opcode]+=1;
			break;
                case CMPD:
                        if (_GRA == _GRB){
				cdr = eq;
				promcmpd[pc-1][eq]+=1;
			}
                        else if (_GRA < _GRB){
				cdr = le;
				promcmpd[pc-1][le]+=1;
			}
			else{
				cdr = 0;
				promcmpd[pc-1][ge]+=1;
			}
			count[opcode]+=1;
                        break;
                case CMPF:
			ra = *(float*)(&(_GRA));
			rb = *(float*)(&(_GRB));
                        if (ra == rb){
				cdr = eq;
				promcmpd[pc-1][eq]+=1;
			}
                        else if (ra < rb){
				cdr = le;
				promcmpd[pc-1][le]+=1;
			}
			else{
				cdr = 0;
				promcmpd[pc-1][ge]+=1;
			}
			count[opcode]+=1;
                        break;
                case CMPDI:
                        if (_GRA == _SI){
				cdr = eq;
				promcmpd[pc-1][eq]+=1;
			}
                        else if (_GRA < _SI){
				cdr = le;
				promcmpd[pc-1][le]+=1;
			}
			else{
				cdr = 0;
				promcmpd[pc-1][ge]+=1;
			}
			count[opcode]+=1;
                        break;
                case BEQ:
			if(cdr==eq){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
		case BLE:
			if(cdr==eq||cdr==le){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
		case BLT:
			if(cdr==le){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
		case BNE:
			if(cdr!=eq){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
		case BGE:
			if(cdr!=le){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
		case BGT:
			if(cdr!=le&&cdr!=eq){
			promjmp[pc-1][_LI]+=1;
			pc = _LI;
			}
			count[opcode]+=1;
			break;
                case INLL:
                        scanf("%d",&p);
                        _GRT = (_GRT & 0xffffff00)|(p & 0xff);
			count[opcode]+=1;
                        break;
                case INLH:

                        scanf("%d",&p);
                        _GRT = (_GRT & 0xffff00ff)|(p<<8 & 0xff00);
			count[opcode]+=1;
                        break;
                case INUL:
            scanf("%d",&p);
            _GRT = (_GRT & 0xff00ffff)|(p<<16 & 0xff0000);
			count[opcode]+=1;
                        break;
                case INUH:
            scanf("%d",&p);
            _GRT = (_GRT & 0x00ffffff)|(p<<24 & 0xff000000);
			count[opcode]+=1;
                        break;
		case OUTLL:
  			fprintf(fpout, "%d\n",(_GRT>>0)&0xff);
			count[opcode]+=1;
			break;
		case OUTLH:
  			fprintf(fpout, "%d\n",(_GRT>>8)&0xff);
			count[opcode]+=1;
            break;
		case OUTUL:
  			fprintf(fpout, "%d\n",(_GRT>>16)&0xff);
			count[opcode]+=1;
            break;
		case OUTUH:
  		fprintf(fpout, "%d\n",(_GRT>>24)&0xff);
			count[opcode]+=1;
            break;
		case NOP:
			count[opcode]+=1;
			break;
		case END:
			count[opcode]+=1;
			return 1;
		default	:	return 1;//break;
	}

	return 0;
}

