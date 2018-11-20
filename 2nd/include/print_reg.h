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

void print_opcode(int32_t ir){

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
