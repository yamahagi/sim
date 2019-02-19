#ifndef __FUNCTION_H_INCLUDED_
#define __FUNCTION_H_INCLUDED_

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
#include "common.h"
#include "oc_sim.h"


void print_data(int32_t data){
        for(int i=0;i<32;i++){
                if(i==1||i==9) printf(" ");
                printf("%d",((data>>(31-i))&0x1));
        }
        printf("\n");
}

void print_data64(int64_t data){
        for(int i=0;i<64;i++){
                printf("%lld",((data>>(63-i))&0x1));
        }
        printf("\n");
}

void print_cdr(int cdr){

	if(cdr == eq){
		printf("eq\n");
	}
	else if (cdr == le){
                printf("le\n");
        }
	else{
                printf("フラグなし\n");
	}
}

void print_op(int32_t ir){

        int opcode =get_opcode(ir);
         switch(opcode){
                case ADDI:
                        printf("ADDI ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case SUBI:
                        printf("SUBI ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case ADD:
                        printf("ADD ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case SUB:
                        printf("SUB ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case SRAWI:
                        printf("SRAWI ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case SLAWI:
                        printf("SLAWI ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
			break;
                case XOR:
                        printf("XOR ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case AND:
                        printf("AND ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FADD:
                        printf("FADD ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FSUB:
                        printf("FSUB ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FMUL:
                        printf("FMUL ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FDIV:
                        printf("FDIV ");
                        printf("r%d r%d r%d\n",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FTOI:
                        printf("FTOI ");
                        printf("r%d r%d\n",get_rti(ir),get_rai(ir));
                        break;
                case ITOF:
                        printf("ITOF ");
                        printf("r%d r%d\n",get_rti(ir),get_rai(ir));
                        break;
                case FSQRT:
                        printf("FSQRT ");
                        printf("r%d r%d\n",get_rti(ir),get_rai(ir));
                        break;
		 case LOAD:
                        printf("LOAD ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case STORE:
                        printf("STORE ");
                        printf("r%d r%d %d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case LI:
                        printf("LI ");
                        printf("r%d %d\n",get_rti(ir),get_si(ir));
                        break;
                case LIW:
                        printf("LIW ");
                        printf("r%d %d\n",get_rtiw(ir),get_siw(ir));
                        break;
                case JUMP:
                        printf("JUMP ");
                        printf("%d\n",get_li(ir));
                        break;
                case BLR:
                        printf("BLR\n");
                        break;
                case BL:
                        printf("BL ");
                        printf("%d\n",get_li(ir));
                        break;
                case BLRR:
                        printf("BLRR ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case CMPD:
                        printf("CMPD ");
                        printf("r%d r%d \n",get_rai(ir),get_rbi(ir));
                        break;
		case CMPF:
                        printf("CMPF ");
                        printf("r%d r%d \n",get_rai(ir),get_rbi(ir));
                        break;
                case CMPDI:
                        printf("CMPDI ");
                        printf("r%d %d \n",get_rai(ir),get_si(ir));
                        break;
                case BEQ:
                        printf("BEQ ");
                        printf("%d\n",get_li(ir));
                        break;
                case BLE:
                        printf("BLE ");
                        printf("%d\n",get_li(ir));
                        break;
                 case BLT:
                        printf("BLT ");
                        printf("%d\n",get_li(ir));
                        break;
                 case BNE:
                        printf("BNE ");
                        printf("%d\n",get_li(ir));
                        break;
                 case BGE:
                        printf("BGE ");
                        printf("%d\n",get_li(ir));
                        break;
                 case BGT:
                        printf("BGT ");
                        printf("%d\n",get_li(ir));
                        break;
                case INLL:
                        printf("INLL ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case INLH:
                        printf("INLH ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case INUL:
                        printf("INUL ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case INUH:
                        printf("INUH ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case OUTLL:
                        printf("OUTLL ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case OUTLH:
                        printf("OUTLH ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case OUTUL:
                        printf("OUTUL ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case OUTUH:
                        printf("OUTUH ");
                        printf("r%d\n",get_rti(ir));
                        break;
                case NOP:
                        printf("NOP \n");
                        break;
                case END:
                        printf("END \n");
                        break;
		case FORK:
			printf("FORK ");
                        printf("core%d pc%d\n",get_rai(ir),get_si(ir));
                        break;
		case JOIN:
			printf("JOIN ");
                        printf("core%d\n",get_rai(ir));
                        break;
		case FETCH:
			printf("FETCH ");
                        printf("r%d core%d r%d\n",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                default : printf("not defined\n");
        }



}
void print_op_kaigyounasi(int32_t ir);

void print_prom(int64_t ir,int n){

	int getw = get_opcodew(ir);
	int getu = get_opcode((ir>>32)&0xffffffff);
	if(getw==LIW){
        	printf("%d: ",n);
		printf("LIW ");
                printf("r%d %d\n",get_rtiw(ir),get_siw(ir));
	}
	else if(getw==NOP&&getu==NOP){
//		printf("%d: ",n);
//              printf("上下NOP\n");
	}
	else{
		int iru =  (ir>>32)&0xffffffff;
		int ird =  (ir)&0xffffffff;
        	printf("%d: 1:",n);
		print_op_kaigyounasi(iru);
        	printf(", 2: ");
		print_op(ird);
	}	
}

void print_jmp(int64_t ir,int from,int to){

	int iru =  (ir>>32)&0xffffffff;;
	if(get_opcode(iru)==BLR){
        	printf("%d: ",from);
		printf("BLR %d\n",to);
	}
	else{
		printf("%d: ",from);
		print_op(iru);
	}
}

void print_cmpd(int64_t ir,int n){

	int iru = (ir>>32)&0xffffffff;
	int ird = ir&0xffffffff;
	int opcode_u = get_opcode(iru);
	printf("%d: ",n);
	if(opcode_u == CMPD || opcode_u == CMPF || opcode_u == CMPDI){
		print_op(iru);
	}
	else{
		print_op(ird);
	}

}

void print_op_kaigyounasi(int32_t ir){

        int opcode =get_opcode(ir);
         switch(opcode){
                case ADDI:
                        printf("ADDI ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case SUBI:
                        printf("SUBI ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case ADD:
                        printf("ADD ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case SUB:
                        printf("SUB ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case SRAWI:
                        printf("SRAWI ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case SLAWI:
                        printf("SLAWI ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
			break;
                case XOR:
                        printf("XOR ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case AND:
                        printf("AND ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FADD:
                        printf("FADD ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FSUB:
                        printf("FSUB ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FMUL:
                        printf("FMUL ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FDIV:
                        printf("FDIV ");
                        printf("r%d r%d r%d",get_rti(ir),get_rai(ir),get_rbi(ir));
                        break;
                case FTOI:
                        printf("FTOI ");
                        printf("r%d r%d",get_rti(ir),get_rai(ir));
                        break;
                case ITOF:
                        printf("ITOF ");
                        printf("r%d r%d",get_rti(ir),get_rai(ir));
                        break;
                case FSQRT:
                        printf("FSQRT ");
                        printf("r%d r%d",get_rti(ir),get_rai(ir));
                        break;
		 case LOAD:
                        printf("LOAD ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case STORE:
                        printf("STORE ");
                        printf("r%d r%d %d",get_rti(ir),get_rai(ir),get_si(ir));
                        break;
                case LI:
                        printf("LI ");
                        printf("r%d %d",get_rti(ir),get_si(ir));
                        break;
                case LIW:
                        printf("LIW ");
                        printf("r%d %d",get_rtiw(ir),get_siw(ir));
                        break;
                case JUMP:
                        printf("JUMP ");
                        printf("%d",get_li(ir));
                        break;
                case BLR:
                        printf("BLR");
                        break;
                case BL:
                        printf("BL ");
                        printf("%d",get_li(ir));
                        break;
                case BLRR:
                        printf("BLRR ");
                        printf("r%d",get_rti(ir));
                        break;
                case CMPD:
                        printf("CMPD ");
                        printf("r%d r%d",get_rai(ir),get_rbi(ir));
                        break;
		case CMPF:
                        printf("CMPF ");
                        printf("r%d r%d",get_rai(ir),get_rbi(ir));
                        break;
                case CMPDI:
                        printf("CMPDI ");
                        printf("r%d %d",get_rai(ir),get_si(ir));
                        break;
                case BEQ:
                        printf("BEQ ");
                        printf("%d",get_li(ir));
                        break;
                case BLE:
                        printf("BLE ");
                        printf("%d",get_li(ir));
                        break;
                 case BLT:
                        printf("BLT ");
                        printf("%d",get_li(ir));
                        break;
                 case BNE:
                        printf("BNE ");
                        printf("%d",get_li(ir));
                        break;
                 case BGE:
                        printf("BGE ");
                        printf("%d",get_li(ir));
                        break;
                 case BGT:
                        printf("BGT ");
                        printf("%d",get_li(ir));
                        break;
                case INLL:
                        printf("INLL ");
                        printf("r%d",get_rti(ir));
                        break;
                case INLH:
                        printf("INLH ");
                        printf("r%d",get_rti(ir));
                        break;
                case INUL:
                        printf("INUL ");
                        printf("r%d",get_rti(ir));
                        break;
                case INUH:
                        printf("INUH ");
                        printf("r%d",get_rti(ir));
                        break;
                case OUTLL:
                        printf("OUTLL ");
                        printf("r%d",get_rti(ir));
                        break;
                case OUTLH:
                        printf("OUTLH ");
                        printf("r%d",get_rti(ir));
                        break;
                case OUTUL:
                        printf("OUTUL ");
                        printf("r%d",get_rti(ir));
                        break;
                case OUTUH:
                        printf("OUTUH ");
                        printf("r%d",get_rti(ir));
                        break;
                case NOP:
                        printf("NOP");
                        break;
                case END:
                        printf("END");
                        break;
                default : printf("not defined\n");
        }
	printf(" ");


}
/*
void print_opcode(int64_t ir){

switch(get_opcode(ir)){
                case ADDI:
                        printf("ADDI ");
			printf("%x\n",ir);
			break;
                case SUBI:
                        printf("SUBI ");
			printf("%x\n",ir);
                        break;
                case ADD:
                        printf("ADD ");
			printf("%x\n",ir);
                        break;
                case SUB:
                        printf("SUB ");
			printf("%x\n",ir);
                        break;
                case FADD:
                        printf("FADD ");
			printf("%x\n",ir);
                        break;
                case FSUB:
                        printf("FSUB ");
			printf("%x\n",ir);
                        break;
                case FMUL:
                        printf("FMUL ");
			printf("%x\n",ir);
                        break;
		case FDIV:
                        printf("FDIV ");
			printf("%x\n",ir);
                        break;
                case SRAWI:
                        printf("SRAWI ");
			printf("%x\n",ir);
                        break;
                case SLAWI:
                        printf("SLAWI ");
			printf("%x\n",ir);
                        break;
                //メモリから代入 ram
                case LOAD:
                        printf("LOAD ");
			printf("%x\n",ir);
                        break;
                //メモリに代入
                case STORE:
                        printf("STORE ");
			printf("%x\n",ir);
                        break;
                case LI:
                        printf("LI ");
			printf("%x\n",ir);
                        break;
                case LIS:
                        printf("LIS ");
			printf("%x\n",ir);
                        break;
		case JUMP:
                        printf("JUMP ");
			printf("%x\n",ir);
                        break;
                case BLR:
                        printf("BLR ");
			printf("%x\n",ir);
                        break;
                case BL:
                        printf("BL ");
			printf("%x\n",ir);
                        break;
                case BLRR:
                        printf("BLRR ");
			printf("%x\n",ir);
                        break;
                case BEQ:
                        printf("BEQ ");
			printf("%x\n",ir);
                        break;
                case BLE:
                        printf("BLE ");
			printf("%x\n",ir);
                        break;
                case BLT:
                        printf("BLT ");
			printf("%x\n",ir);
                        break;
                case CMPD:
                        printf("CMPD ");
			printf("%x\n",ir);
                        break;
                case CMPF:
                        printf("CMPF ");
			printf("%x\n",ir);
                        break;
                case CMPDI:
                        printf("CMPDI ");
			printf("%x\n",ir);
                        break;
                case INLL:
                        printf("INLL ");
			printf("%x\n",ir);
                        break;
                case INLH:
                        printf("INLH ");
			printf("%x\n",ir);
                        break;
                case INUL:
                        printf("INUL ");
			printf("%x\n",ir);
                        break;
                case INUH:
                        printf("INUH ");
			printf("%x\n",ir);
                        break;
                case OUTLL:
                        printf("OUTLL ");
			printf("%x\n",ir);
                        break;
                case OUTLH:
                        printf("OUTLH ");
			printf("%x\n",ir);
            		break;
		case OUTUL:
                        printf("OUTUL ");
			printf("%x\n",ir);
            		break;
                case OUTUH:
                        printf("OUTUH ");
			printf("%x\n",ir);
            		break;
                case NOP:
                        printf("NOP ");
			printf("%x\n",ir);
			break;
                default :       
                        printf("don't exist ");
			printf("%x\n",ir);
        		break;
	}
}
*/

#endif
