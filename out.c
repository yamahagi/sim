#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

	char* a;
	if(argc == 2){
		a = argv[1];
	}
	if(argc < 2){
		char b[2] = {'\0'};
		a = b;
	}
	if(*a == '\0')
	{

		printf("1\n");
	}
	return 0;
}

