
#ifndef COMMONHEAD
#define COMMONHEAD
#define INSTNUM 64	// 6bit 63
#define REGNUM 32
#define ROMNUM (64 * 1024) // words(32bit)
//メモリのこと？
#define RAMNUM (256 * 1024)

#define ADDI  0b00000
#define SUBI  0b00001
#define MULI  0b00010
#define DIVI  0b00011
#define ADD  0b01000
#define SUB  0b01001
#define MUL  0b01010
#define DIV  0b01011
#define LOAD  0b11000
#define STORE  0b11001
#define JUMP   0b100000
#define BEQ  0b101000
#define BLE  0b101001
#define AND  0b010000
#define OR  0b010001
#define IN  0b110000
#define OUT  0b110001
#define CMPD  0b101010
//#define CMPDI   failwith yet implemented
#define LI  0b011010

#endif
