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

//一つ一つに命令が入る？
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
//コンディションレジスタ reg[30]
uint32_t pc;
//命令
uint32_t ir;
int32_t lr;
//何命令行ったか？
uint64_t cnt;

FILE *outputfile1; 

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
	reg[30] = 0;
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
		for(int i=0;i<12;i++){
			printf("reg[%d] %d\n",i+3,reg[i+3]);
		}
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
			_GRT = _IMM;
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
			lnk = pc + 1;
			pc = _LI;
                case BEQ:
			if(cdr==1) pc= _LI;
			break;
		case BLE:
			if(cdr==1||cdr==2) pc = _LI;
			break;
                case CMPD:
                        if (_GRT == _GRA){
				cdr = 1;
			}
                        else if (_GRT <= _GRA){
				cdr = 2;
			}
			else{
				cdr = 0;
			}
                        break;
                case IN:
                        c = getchar();
                        _GRT = c & 0xff;
                        break;
		//TODO テキストに出力
		case OUT:
  			outputfile1 = fopen("d.txt", "a");
  			if (outputfile1 == NULL) {
    			printf("cannot open\n");  
    			exit(1);                 
  			}
  			fprintf(outputfile1, "%d\n",_GRT);
  			fclose(outputfile1);
			break;
		case END:
			printf("終了");
			return 1;
		default	:	return 1;//break;
	}

	return 0;
}
