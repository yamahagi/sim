#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int32_t get_bit(int32_t a,int32_t start,int32_t last){


	int32_t target_last = a >> last;
	int32_t target_start=1;
	for(int i=0;i<start-last;i++){
		target_start = (target_start<<1)+1;
	}
	return target_last&target_start;
}
int64_t get_bit64(int64_t a,int32_t start,int32_t last){


	int64_t target_last = a >> last;
	int64_t target_start=1;
	for(int i=0;i<start-last;i++){
		target_start = (target_start<<1)+1;
	}
	return target_last&target_start;
}

int main(void){

int32_t a =  127;

uint32_t c = a;

printf("%u",c);

int b = get_bit(a,0,0);
int b1 = get_bit(a,1,1);
int b2 = get_bit(a,2,2);
int b3 = get_bit(a,3,3);
int b4 = get_bit(a,4,4);
int b5 = get_bit(a,5,5);
int b6 = get_bit(a,6,6);
int b7 = get_bit(a,7,7);
int b8 = get_bit(a,8,8);

printf("%d\n",b);
printf("%d\n",b1);
printf("%d\n",b2);
printf("%d\n",b3);
printf("%d\n",b4);
printf("%d\n",b5);
printf("%d\n",b6);
printf("%d\n",b7);
printf("%d\n",b8);



}
