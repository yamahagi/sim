
#ifndef COMMONHEAD
#define COMMONHEAD
#define INSTNUM 64	// 6bit 63
#define REGNUM 32
#define ROMNUM (64 * 1024) // words(32bit)
//メモリのこと？
#define RAMNUM (1024 * 1024)

#define ADDI  0b000000
#define SUBI  0b000001
#define MULI  0b000010
#define DIVI  0b000011

#define ADD  0b001000
#define SUB  0b001001
#define MUL  0b001010
#define DIV  0b001011
#define FADD  0b001100
#define FSUB  0b001101
#define FMUL  0b001110
#define FDIV  0b001111

#define AND  0b010000
#define OR  0b010001
#define SRAWI 0b010010
#define SLAWI 0b010011

#define LOAD  0b011000
#define STORE  0b011001
#define LI  0b011010
#define LIS  0b011011

#define JUMP   0b100000
#define BLR	0b100001
#define BL	0b100010
#define BLRR	0b100011

#define BEQ  0b101000
#define BLE  0b101001
#define CMPD  0b101010
#define CMPD  0b101011
#define BLE  0b101100

#define INLL  0b110000
#define INLH  0b110001
#define INUL  0b110010
#define INUH  0b110011
#define OUTLL  0b110100
#define OUTLH  0b110101
#define OUTUL  0b110110
#define OUTUH  0b110111
//#define CMPDI   failwith yet implemented
#define END 0b111000

#endif
