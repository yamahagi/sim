#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

uint32_t get(int32_t a,int32_t start,int32_t last){


	int32_t target_last = a >> last;
	int32_t target_start=1;
	for(int i=0;i<start-last;i++){
		target_start = (target_start<<1)+1;
	}
	return target_last&target_start;
}
int64_t get64(int64_t a,int32_t start,int32_t last){


	int64_t target_last = a >> last;
	int64_t target_start=1;
	for(int i=0;i<start-last;i++){
		target_start = (target_start<<1)+1;
	}
	return target_last&target_start;
}

int main(void){

uint32_t a =  4294967295;;

uint32_t b;
int32_t c = a;

printf("%d\n",c);
for(int i=0;i<32;i++){
b =  get(c,0,0);
c = c >> 1;
printf("%d %d\n",i,b);
}
printf("a\n");
for(int i=0;i<32;i++){
b =  get(a,0,0);
a = a >> 1;
printf("%d %d\n",i,b);
}


return 0;


}
