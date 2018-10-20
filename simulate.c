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
#include "fpu/ftools.h"
#include "include/oc_sim.h"
#include "include/common.h"
#include "include/print_opcode.h"

//一つ一つに命令が入る
uint32_t prom[ROMNUM];
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
uint32_t pc;
//命令
uint32_t ir;
int32_t lr;
//何命令行ったか？
uint64_t cnt;


FILE *fpout; 

extern uint32_t _finv(int32_t);
extern uint32_t _fsqrt(int32_t);
extern uint32_t _fadd(int32_t, int32_t);
extern uint32_t _fmul(int32_t, int32_t);

void print_count(void);

//レジスタの規定
static inline void init(void) {
// register init
	reg[0] = 0;
	reg[1] = 4*(RAMNUM-1);
	reg[2] = prom[0];
	lnk = 0;
	cdr = 0;
// heap init なにこれ?
	pc = 0;
/*
	for (pc = 1; pc*4 <= reg[2]; pc++) {
		ram[pc-1] = prom[pc];
	}
*/
}

static inline int exec_op(uint32_t ir);


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
		cnt++;
		pc++;
		if (!(cnt % 10000000)) { 
			warning("."); 

		}
			
		float f;	
		
		//ゼロレジスタを表示	
#ifndef SILENT
		printf("実行命令 ");
		print_opcode(ir);
		printf("ゼロレジスタ %d\n",reg[0]);
		printf("スタックの先頭　%d\n",reg[1]);
		printf("スタックフレーム %d\n",reg[2]);
		printf("リンクレジスタ %d\n",reg[31]);
		//整数レジスタ
		for(int i=0;i<12;i++){
			printf("reg[%d] %d\n",i+3,reg[i+3]);
		}
		//浮動小数点レジスタ表示
		for(int i=0;i<12;i++){
			printf("reg[%d] %f\n",i+15,float_get(reg[i+15]));
		}
		//それ以外のレジスタ
		for(int i=0;i<4;i++){
			printf("reg[%d] %d\n",i+27,reg[i+27]);
		}
#endif
		if(ir == 0){
		printf("終了\n");	
		break;
		}
	} while (exec_op(ir)==0);
	return 0;
} 


static inline int exec_op(uint32_t ir) {
	uint8_t opcode, funct;
	union {
		uint32_t i;
		float f;
	} a, b, out;
	char c;
	float ra=0.0;
	float rb=0.0;
	float resultf = 0.0;
	int32_t si;
	opcode = get_opcode(ir);
	

	switch(opcode){
		case ADDI:
			_GRT = _GRA + _SI;
			count[opcode]+=1;
			break;
		case SUBI:
			_GRT = _GRA - _SI;
			count[opcode]+=1;
			break;
		case MULI:
			_GRT = _GRA * _SI;
			count[opcode]+=1;
			break;
		case DIVI:
			_GRT = _GRA / _SI;
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
		case MUL:
			_GRT = _GRA * _GRB;
			count[opcode]+=1;
			break;
		case DIV:
			_GRT = _GRA / _GRB;
			count[opcode]+=1;
			break;
		case FADD:
			ra = float_get(_GRA);
			rb = float_get(_GRB);
			resultf = ra+rb;
			_GRT = int_get(resultf);
			count[opcode]+=1;
			break;
		case FSUB:
			ra = float_get(_GRA);
			rb = float_get(_GRB);
			resultf = ra-rb;
			_GRT = int_get(resultf);
			count[opcode]+=1;
			break;
		case FMUL:
			ra = float_get(_GRA);
			rb = float_get(_GRB);
			resultf = ra*rb;
			_GRT = int_get(resultf);
			count[opcode]+=1;
			break;
		case FDIV:
			ra = float_get(_GRA);
			rb = float_get(_GRB);
			resultf = ra/rb;
			_GRT = int_get(resultf);
			count[opcode]+=1;
			break;
		case AND:
			_GRT = _GRA & _GRB;
			count[opcode]+=1;
                        break;
		case OR:
			_GRT = _GRA | _GRB;
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
				_GRT = (0xffff0000|si);
			}
			else if(((si>>31)&0x1)==0){
				_GRT = (0xffff&si);
			}
			count[opcode]+=1;
			break; 	
		case LIS:
			_GRT = (_SI<<16) | (_GRT & ((1<<16)-1)) ;
			count[opcode]+=1;
			break; 	
		case JUMP:
			/*
			if (pc-1 == get_li(ir)) {
				return 1;
			}
			*/
			pc = get_li(ir);
			count[opcode]+=1;
			break;
		case BLR:
			if(pc == lnk) return 1;
			pc = lnk;
			count[opcode]+=1;
			break;
		case BL:
			lnk = pc ;
			pc = _LI;
			count[opcode]+=1;
			break;
                case BEQ:
			if(cdr==eq) pc= _LI;
			count[opcode]+=1;
			break;
		case BLE:
			if(cdr==eq||cdr==le) pc = _LI;
			count[opcode]+=1;
			break;
                case CMPD:
                        if (_GRT == _GRA){
				cdr = eq;
			}
                        else if (_GRT <= _GRA){
				cdr = le;
			}
			else{
				cdr = 0;
			}
			count[opcode]+=1;
                        break;
                case INLL:
                        c = getchar();
                        _GRT = (_GRT & 0xffffff00)||(c & 0xff);
			count[opcode]+=1;
                        break;
                case INLH:
                        c = getchar();
                        _GRT = (_GRT & 0xffff00ff)||(c<<8 & 0xff00);
			count[opcode]+=1;
                        break;
                case INUL:
                        c = getchar();
                        _GRT = (_GRT & 0xff00ffff)||(c<<16 & 0xff0000);
			count[opcode]+=1;
                        break;
                case INUH:
                        c = getchar();
                        _GRT = (_GRT & 0x00ffffff)||(c<<24 & 0xff000000);
			count[opcode]+=1;
                        break;
		case OUTLL:
			if(*outputfile == '\0'){
  				fpout = fopen("d.txt", "a");
			}
			else{
  				fpout = fopen(outputfile, "a");
  			}
			if (fpout == NULL) {
    				printf("cannot open\n");  
    				exit(1);                 
  			}
			
  			fprintf(fpout, "%d\n",_GRT&0xff);
  			fclose(fpout);
			count[opcode]+=1;
			break;
		case OUTLH:
  			if(*outputfile == '\0'){
                                fpout = fopen("d.txt", "a");
                        }
                        else{
                                fpout = fopen(outputfile, "a");
                        }
			if (fpout == NULL) {
    			printf("cannot open\n");  
    			exit(1);                 
  			}
  			fprintf(fpout, "%d\n",(_GRT>>8)&0xff);
  			fclose(fpout);
			count[opcode]+=1;
            break;
		case OUTUL:
			if(*outputfile == '\0'){
                                fpout = fopen("d.txt", "a");
                        }
                        else{
                                fpout = fopen(outputfile, "a");
                        }
  			if (fpout == NULL) {
    			printf("cannot open\n");  
    			exit(1);                 
  			}
  			fprintf(fpout, "%d\n",(_GRT>>16)&0xff);
  			fclose(fpout);
			count[opcode]+=1;
            break;
		case OUTUH:
  			
  			if(*outputfile == '\0'){
                                fpout = fopen("d.txt", "a");
                        }
                        else{
                                fpout = fopen(outputfile, "a");
                        }
			if (fpout == NULL) {
    			printf("cannot open\n");  
    			exit(1);                 
  			}
  			fprintf(fpout, "%d\n",(_GRT>>24)&0xff);
  			fclose(fpout);
			count[opcode]+=1;
            break;
		case END:
			printf("終了\n");
			count[opcode]+=1;
			return 1;
		default	:	return 1;//break;
	}

	return 0;
}

