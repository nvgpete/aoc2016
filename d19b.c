#include <stdio.h>
#include <string.h>
#define ELVES 3012210
//#define ELVES 5
int list[ELVES];
int main(int argc,char **argv) {
  int n,m,last=ELVES;
  for (n=0; n<ELVES/2; n++) {
    list[n]=n+1+ELVES/2;
    list[n+(ELVES+1)/2]=n+1;
  }
  if (ELVES & 1) list[ELVES/2]=ELVES;
  m=2-(ELVES & 1);
  while (last>m) {
    n=0;
    while (m<last) {
      list[n++]=list[m];
      m+=3;
    }
    m-=last;
    last=n;  
  }
  if (last==2) list[0]=list[1];
  printf("Last elf standing=%d\n",list[0]);  
}
