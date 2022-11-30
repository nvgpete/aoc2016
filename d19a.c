#include <stdio.h>
#include <string.h>
#define ELVES 3012210
//#define ELVES 5
int main(int argc,char **argv) {
  int n,m,last=(ELVES+1)/2,list[(ELVES+1)/2];
  for (n=0; n<last; n++) list[n]=2*n+1;
  m=(ELVES & 1);
  while (last>1) {
    n=0;
    while (m<last) {
      list[n++]=list[m];
      m+=2;
    }
    m-=last;
    last=n;  
  }
  printf("Last elf standing=%d\n",list[0]);  
}
