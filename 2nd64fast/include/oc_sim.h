
#ifndef _SIM_HEAD
#define _SIM_HEAD
#include "common.h"
#include <stdint.h>

typedef struct currentposition
{       
        //現在の位置を表す
        //numberはpromにおけるarrayの番号
        //上32bitならpositionは0 下ならposition 1
        //pc = 2*number+positionで表される
    int number;
    int position;

}Pc;


extern uint64_t prom[ROMNUM];
extern uint32_t promjmp[ROMNUM][ROMNUM];
extern uint32_t promcmpd[ROMNUM][3];
extern uint32_t ram[RAMNUM];
extern int32_t ramfill[RAMNUM];
extern int32_t ramnumber;
extern int32_t reg[REGNUM];
extern uint32_t freg[REGNUM];
extern Pc pc;
//extern int pc;
extern uint64_t count[256];
extern int cdr;
extern uint64_t ir;
extern uint32_t ir32;
extern int32_t lr;
extern uint64_t cnt;
extern uint32_t limit;
extern char* outputfile;
extern char* inputfile;

/*
[31:26] opcode get_opcode
[25:21] RT get_rti(ir) _GRT
[20:16] RA get_rai(ir) _GRA
[15:11] RB get_rbi(ir) _GRB
[15:0]  SI get_si(ir)  _SI
[20:0] IMM get_imm(ir) _IMM
[25:0] LI get_li(ir)  _LI


[63:58] opcode get_opcodew
[57:53] RTW get_rtiw(ir) _GRTW
[31:0] SIW get_siw(ir) _SIW

*/
//命令
#define get_opcodew(ir) ((uint32_t)(((ir)>>58)&0x3f))
//命令
#define get_opcode(ir32) ((uint32_t)(((ir32)>>26)&0x3f))
//代入先 RT 
#define get_rti(ir32) ((uint32_t)(((ir32)>>21)&0x1f))
//RA 元レジスタ1
#define get_rai(ir32) ((uint32_t)(((ir32)>>16)&0x1f))
//RB 元レジスタ2
#define get_rbi(ir32) ((uint32_t)(((ir32)>>11)&0x1f))
//LI ジャンプ先
#define get_li(ir32) ((uint32_t)(((ir32)&0x3ffffff)))
//コンディションレジスタ reg[30]
//#define cdr reg[30]
//リンクレジスタ reg[31]
#define lnk reg[31]

// ge 0 eq 1 le 2
#define ge 0
#define eq 1
#define le 2

/*
#define get_shamt(ir) ((uint32_t)(((ir)>>6)&0x1f))
#define get_funct(ir) ((uint32_t)((ir)&0x3f))
#define get_target(ir) ((uint32_t)((ir)&0x3ffffff))
*/
//IMM 即値
#define get_imm(ir32) ((uint32_t)(((ir32)&0x1fffff)))
//SI 即値
#define get_si(ir32) \
	(int32_t)((ir32&0xffff)-2*(0x8000*((ir32>>15)&0x1)))
//SIW 即値
#define get_siw(ir) \
	(int32_t)((ir&0xffffffff)-2*(0x80000000*((ir>>31)&0x1)))
//RTW 代入先
#define get_rtiw(ir)	(uint32_t)((ir>>53)&0x1f)
////////////////////////////////////////////////////////////////////////
// register access
////////////////////////////////////////////////////////////////////////
#define _GRT reg[get_rti(ir32)]
#define _GRTW reg[get_rtiw(ir)]
#define _GRA reg[get_rai(ir32)]
#define _GRB reg[get_rbi(ir32)]
/*
#define _FRS freg[get_rti(ir)]
#define _FRT freg[get_rai(ir)]
#define _FRD freg[get_rbi(ir)]
*/
#define _SI get_si(ir32)
#define _SIW get_siw(ir)
#define _IMM get_imm(ir32)
#define _LI get_li(ir32)
////////////////////////////////////////////////////////////////////////


extern const char *InstMap[INSTNUM];
extern const char *SFunctMap[INSTNUM];
extern const char *FFunctMap[INSTNUM];
extern const char *IOFunctMap[INSTNUM];

void analyse(uint32_t);
void print_analysis(FILE*);
extern FILE* err_fp;
#define warning(fmt, ...) \
	fprintf(err_fp, fmt, ##__VA_ARGS__)
#define warning_nl() warning("\n")

void _print_ir(uint32_t,FILE*);
#define print_ir(x) _print_ir(x, err_fp)

inline uint32_t eff_dig(int dig, uint32_t num);
inline uint32_t sra_eff(int rsw, int dig, uint32_t num);

#define fmthex "%08x"
#define fmtidx "%d"
#define fmtimm "imm=%d"
#define fmtlabel "label=%d"
#define fmtdec "%d"
#define fmtinst "%s "
#define print_fmt_i fmtinst
#define print_fmt_if fmtinst"f"fmtidx"="fmthex
#define print_fmt_ig fmtinst"g"fmtidx"="fmtdec
#define print_fmt_ii fmtinst""fmtimm
#define print_fmt_il fmtinst""fmtlabel
#define print_fmt_iff fmtinst"f"fmtidx"="fmthex", f"fmtidx"="fmthex
#define print_fmt_ifg fmtinst"f"fmtidx"="fmthex", g"fmtidx"="fmtdec
#define print_fmt_ifi fmtinst"f"fmtidx"="fmthex", "fmtimm
#define print_fmt_igf fmtinst"g"fmtidx"="fmtdec", f"fmtidx"="fmthex
#define print_fmt_igg fmtinst"g"fmtidx"="fmtdec", g"fmtidx"="fmtdec
#define print_fmt_igi fmtinst"g"fmtidx"="fmtdec", "fmtimm
#define print_fmt_igl fmtinst"g"fmtidx"="fmtdec", "fmtlabel
#define print_fmt_ifff \
fmtinst"f"fmtidx"="fmthex", f"fmtidx"="fmthex", f"fmtidx"="fmthex
#define print_fmt_iffl \
fmtinst"f"fmtidx"="fmthex", f"fmtidx"="fmthex", "fmtlabel
#define print_fmt_ifgg \
fmtinst"f"fmtidx"="fmthex", g"fmtidx"="fmtdec", g"fmtidx"="fmtdec
#define print_fmt_ifgi \
fmtinst"f"fmtidx"="fmthex", g"fmtidx"="fmtdec", "fmtimm
#define print_fmt_iggg \
fmtinst"g"fmtidx"="fmtdec", g"fmtidx"="fmtdec", g"fmtidx"="fmtdec
#define print_fmt_iggi \
fmtinst"g"fmtidx"="fmtdec", g"fmtidx"="fmtdec", "fmtimm
#define print_fmt_iggl \
fmtinst"g"fmtidx"="fmtdec", g"fmtidx"="fmtdec", "fmtlabel
extern FILE* log_fp;
#endif
