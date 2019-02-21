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

extern float float_get(int32_t b);

extern int32_t int_get(float b);

extern int32_t split_bit(int32_t data,int32_t start,int32_t end);
extern int32_t split_bit64(int64_t data,int32_t start,int32_t end);
extern void print_bit(int32_t data);
extern void print_sqrtbit(int32_t data);
extern void print_bit64(int64_t data);
