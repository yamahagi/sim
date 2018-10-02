#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>
#include "oc_sim.h"

//一つ一つに命令が入る？
uint32_t prom[ROM_NUM];
uint32_t ram[RAM_NUM];
int32_t reg[REG_NUM];
uint32_t freg[REG_NUM];
//コンディションレジスタ
int cdr;
uint32_t pc;
//命令
uint32_t ir;
int32_t lr;
//何命令行ったか？
uint64_t cnt;

extern uint32_t _finv(uint32_t);
extern uint32_t _fsqrt(uint32_t);
extern uint32_t _fadd(uint32_t, uint32_t);
extern uint32_t _fmul(uint32_t, uint32_t);
static inline void init(void) {
// register init
	reg[1] = 4*(RAM_NUM-1);
	reg[2] = prom[0];
// heap init
	for (pc = 1; pc*4 <= reg[2]; pc++) {
		ram[pc-1] = prom[pc];
	}
}

static inline int exec_op(uint32_t ir);


//命令がある限りpcを進めて命令を読んで実行
int simulate(void) {
	init();
	do{
		reg[0] = 0;
		ir = prom[pc];
#ifdef LOG_FLAG
		_print_ir(ir, log_fp);
#endif
#ifdef ANALYSE_FLAG
		analyse(ir);
#endif
		cnt++;
		pc++;
		if (!(cnt % 100000000)) { 
			warning("."); 

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
			_GRT = _GRS + _IMM;
			break;
		case SUBI:
			_GRT = _GRS - _IMM;
			break;
		case MULI:
			_GRT = _GRS * _IMM;
			break;
		case DIVI:
			_GRT = _GRS / _IMM;
			break;
		case ADD:
			_GRT = _GRS + _GRD;
			break;
		case SUB:
			_GRT = _GRS - _GRD;
			break;
		case MUL:
			_GRT = _GRS * _GRD;
			break;
		case DIV:
			_GRT = _GRS / _GRD;
			break;
		case LOAD:
			_GRD = ram[((_GRS + _GRT)/4)];
			break;
		case STORE:
			ram[((_GRS + _GRT)/4)] = _GRD;
			break;
		case JUMP:
			if (pc-1 == get_target(ir)) {
				return 1;
			}
			pc = get_target(ir);
			break;
		case JEQ:
			if (_GRS == _GRT) {
				pc += _IMM - 1;
			} else {
			}
			break;
		case AND:
			_GRT = _GRS & _GRD;
                        break;
		case OR:
			_GRT = _GRS | _GRD;
                        break;
		case OUT:
                        putchar(_GRS&0xff);
                        fflush(stdout);
                        break;
                case IN:
                        c = getchar();
                        _GRD = c & 0xff;
                        break;
                case CMPD:
                        if (_GRT < _GRS){
				cdr = 0;
			}
                        else if (_GRT > _GRS){
				cdr = 1;
			}
                        else if (_GRT = _GRS){
				cdr = 2;
			}
                        break;
		
		default	:	break;
	}

	return 0;
}
