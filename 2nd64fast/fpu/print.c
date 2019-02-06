#include<stdio.h>
#include<stdlib.h>

int main(void){

for(int i=0;i<8;i++){

if(i==0){
printf("if(i==%d){\n",i);
printf("	result = split_bit(adata,%d,%d)==1 ? (((%d<<23)+split_bit(a_kuriage%d,%d,%d))) : ((%d<<23)+split_bit(adata,%d,%d));\n",7-i,7-i,158-i,30-i,30-i,8-i,158-i,30-i,8-i);
printf("}\n");
}
else{
printf("else if(i==%d){\n",i);
printf("	result = split_bit(adata,%d,%d)==1 ? (((%d<<23)+split_bit(a_kuriage%d,%d,%d))) : ((%d<<23)+split_bit(adata,%d,%d));\n",7-i,7-i,158-i,30-i,30-i,8-i,158-i,30-i,8-i);
printf("}\n");


}
}



}
