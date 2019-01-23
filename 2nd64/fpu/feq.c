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

int32_t feq(int32_t adata,int32_t bdata){


if(adata==bdata||(split_bit(adata,30,23)==0&&split_bit(bdata,30,23)==0)){
	return 1;
}
else{
	return 0;
}


}
