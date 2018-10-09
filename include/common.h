
#ifndef COMMONHEAD
#define COMMONHEAD
#define INSTNUM 64	// 6bit 63
#define REGNUM 32
#define ROMNUM (64 * 1024) // words(32bit)
//メモリのこと？
#define RAMNUM (256 * 1024)

#define ADDI  0b000000
#define SUBI  0b000001
#define MULI  0b000010
#define DIVI  0b000011

#define ADD  0b001000
#define SUB  0b001001
#define MUL  0b001010
#define DIV  0b001011

#define AND  0b010000
#define OR  0b010001

#define LOAD  0b011000
#define STORE  0b011001
#define LI  0b011010

#define JUMP   0b100000
#define BLR	0b100001
#define BL	0b100010

#define BEQ  0b101000
#define BLE  0b101001
#define CMPD  0b101010

#define IN  0b110000
#define OUT  0b110001
//#define CMPDI   failwith yet implemented
#define END 0b111000

#endif
