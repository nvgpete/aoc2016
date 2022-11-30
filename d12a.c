#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,ops[25];
  int i,last=0,pc,op1[25],op2[25],rg[4];
  f=fopen("d12a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s;
    ops[last]=*s2;
    s2+=4;
    if (*s2>='a' && *s2<='d') op1[last]=1000+*s2-'a';
    else op1[last]=atoi(s2);
    while (*s2 && *s2!=' ') s2++;
    while  (*s2 && *s2==' ') s2++;
    if (*s2) {
      if (*s2>='a' && *s2<='d') op2[last]=1000+*s2-'a';
      else op2[last]=atoi(s2);
    }
    last++;  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (i=0; i<2; i++) {
    pc=rg[0]=rg[1]=rg[3]=0;
    rg[2]=i;
    while (pc<last) {
      switch (ops[pc]) {
         case 'c' : if (op1[pc]>=1000) rg[op2[pc]-1000]=rg[op1[pc]-1000];
                    else rg[op2[pc]-1000]=op1[pc];
                    break;
         case 'i' : rg[op1[pc]-1000]++;
                    break;           
         case 'd' : rg[op1[pc]-1000]--;
                    break;           
         case 'j' : if (op1[pc]>=1000) { if (rg[op1[pc]-1000]) pc+=op2[pc]-1; }
                     else if (op1[pc]) pc+=op2[pc]-1;
      }
      pc++;
    }
    printf("part %c=%d\n",'a'+i,rg[0]);
  }                             
}
