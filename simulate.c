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
#include "include/oc_sim.h"
#include "include/common.h"

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
%r30 コンディションレジスタ
%r31 リンクレジスタ
*/
int32_t reg[REGNUM];
uint32_t freg[REGNUM];
int cdr;
//コンディションレジスタ reg[30]
uint32_t pc;
//命令
uint32_t ir;
int32_t lr;
//何命令行ったか？
uint64_t cnt;

FILE *fpout; 

extern uint32_t _finv(uint32_t);
extern uint32_t _fsqrt(uint32_t);
extern uint32_t _fadd(uint32_t, uint32_t);
extern uint32_t _fmul(uint32_t, uint32_t);

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
		if(cnt ==0) printf("初期状態\n");
		printf("pc %d\n",pc);
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
	
		//TODO 浮動小数点周りのprint
		//ゼロレジスタを表示	
		printf("ゼロレジスタ %d\n",reg[0]);
		printf("スタックの先頭　%d\n",reg[1]);
		printf("スタックフレーム %d\n",reg[2]);
		printf("リンクレジスタ %d\n",reg[30]);
		printf("コンディションレジスタ %d\n",reg[31]);
		//整数レジスタ
		for(int i=0;i<12;i++){
			printf("reg[%d] %d\n",i+3,reg[i+3]);
		}
		//浮動小数点レジスタ表示(float配列にしてもいいのか？)
		for(int i=0;i<12;i++){
			printf("reg[%d] %d\n",i+15,reg[i+15]);
		}
		if(ir == 0){
		printf("終了");	
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
	opcode = get_opcode(ir);

	switch(opcode){
		case ADDI:
			_GRT = _GRA + _SI;
			break;
		case SUBI:
			_GRT = _GRA - _SI;
			break;
		case MULI:
			_GRT = _GRA * _SI;
			break;
		case DIVI:
			_GRT = _GRA / _SI;
			break;
		case ADD:
			_GRT = _GRA + _GRB;
			break;
		case SUB:
			_GRT = _GRA - _GRB;
			break;
		case MUL:
			_GRT = _GRA * _GRB;
			break;
		case DIV:
			_GRT = _GRA / _GRB;
			break;
		//TODO 浮動小数点レジスタ
		case AND:
			_GRT = _GRA & _GRB;
                        break;
		case OR:
			_GRT = _GRA | _GRB;
                        break;
		//メモリから代入 ram
		case LOAD:
			_GRT = ram[(_GRA + _SI)];
			break;
		//メモリに代入
		case STORE:
			ram[((_GRA + _SI))] = _GRT;
			break;
		case LI:
			_GRT = _SI;
			break; 	
		case LIS:
			_GRT = (_SI<<16) | (_GRT & ((1<<16)-1)) ;
			break; 	
		case JUMP:
			/*
			if (pc-1 == get_li(ir)) {
				return 1;
			}
			*/
			pc = get_li(ir);
			break;
		case BLR:
			if(pc == lnk) return 1;
			pc = lnk;
			break;
		case BL:
			lnk = pc ;
			pc = _LI;
                case BEQ:
			if(cdr==eq) pc= _LI;
			break;
		case BLE:
			if(cdr==eq||cdr==le) pc = _LI;
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
                        break;
                case INLL:
                        c = getchar();
                        _GRT = (_GRT & 0xffffff00)||(c & 0xff);
                        break;
                case INLH:
                        c = getchar();
                        _GRT = (_GRT & 0xffff00ff)||(c<<8 & 0xff00);
                        break;
                case INUL:
                        c = getchar();
                        _GRT = (_GRT & 0xff00ffff)||(c<<16 & 0xff0000);
                        break;
                case INUH:
                        c = getchar();
                        _GRT = (_GRT & 0x00ffffff)||(c<<24 & 0xff000000);
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
            break;
		case END:
			printf("終了");
			return 1;
		default	:	return 1;//break;
	}

	return 0;
}
