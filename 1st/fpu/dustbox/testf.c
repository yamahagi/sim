#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

int a = 0x800000;
float b = *(float*)(&a);
printf("%f\n",b);

for(int i=0;i<32;i++){
	printf("%d",((*(int*)&b)>>(31-i)&0x1));
}

return 0;
}
