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
#include "ftools.h"
#include <math.h>

int32_t fless(int32_t srca,int32_t srcb){

int result;

if(split_bit(srca,30,23)>0){
	if(split_bit(srcb,30,23)>0){
		if(split_bit(srca,31,31)==1){
			if(split_bit(srcb,31,31)==1){
				if(split_bit(srca,30,0)>split_bit(srcb,30,0)){
					result = 1;
				}
				else{
					result = 0;
				}
			}
			else{
				result = 1;
			}
		}
		else{
			if(split_bit(srcb,31,31)==1){
				result = 0;
			}
			else{
				if(split_bit(srca,30,0)<split_bit(srcb,30,0)){
					result = 1;
				}
				else{
					result = 0;
				}
			}
		}
	}
	else{
		result = split_bit(srca,31,31);
	}
}
else{
	if(split_bit(srcb,30,23)>0){
		result = (~(split_bit(srcb,31,31)))&0x1;
	}
	else{
		result = 0;
	}
}

return result;
}
