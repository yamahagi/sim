
#ifndef COMMONHEAD
#define COMMONHEAD
#define INSTNUM 64	// 6bit 63
#define REGNUM 32
#define ROMNUM (64 * 1024) // words(32bit)
//メモリのこと？
#define RAMNUM (1024 * 1024)

#define ADDI  0b000000
#define SUBI  0b000001
#define ADD  0b000010
#define SUB  0b000011

#define FADD  0b001000
#define FSUB  0b001001
#define FMUL  0b001010
#define FDIV  0b001011

#define SRAWI 0b010001
#define SLAWI 0b010010

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
#define BLT  0b101010
#define CMPD  0b101011
#define CMPF  0b101100
#define CMPDI  0b101101

#define INLL  0b110000
#define INLH  0b110001
#define INUL  0b110010
#define INUH  0b110011
#define OUTLL  0b110100
#define OUTLH  0b110101
#define OUTUL  0b110110
#define OUTUH  0b110111
#define END 0b111000

#endif
