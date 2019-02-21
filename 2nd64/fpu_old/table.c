#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void){
  FILE *f;
  f = fopen("table.txt","w");
  if (f == NULL) {
    printf("cannot open\n");
    exit(1);
  }
  int i;
  int j;
  float x0;
  union {float x02bai; int x02baibit;} hoge;
  union {float x02jyou; int x02jyoubit;} fuga;
  for (i=0;i<2048;i++){
    hoge.x02bai = (2048.0 / (i + 2048.0)) + (2048.0 / ((i+1.0) + 2048.0));
    x0 = hoge.x02bai / 2.0;
    fuga.x02jyou = x0 * x0;
    fprintf(f,"else if (split_bit(wbdata,22,12) == %d){  \n  x02bai = 0b", i);
    for( j = 31; j >= 0; j-- ){
      fprintf(f,"%d", ( hoge.x02baibit >> j ) & 1 );
    }
    fprintf(f,";\n  x02jyou = 0b" );
    for( j = 31; j >= 0; j-- ){
      fprintf(f,"%d", ( fuga.x02jyoubit >> j ) & 1 );
    }
    fprintf(f,";}\n" );
  }
  fclose(f);
  return 0;
}
