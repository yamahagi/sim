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

extern int32_t fadd(int32_t adata,int32_t bdata);
extern int32_t fsub(int32_t adata,int32_t bdata);
extern int32_t fmul(int32_t adata,int32_t bdata);
