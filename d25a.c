#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,ops[35],ops2[35];
  int i,j,b,count,last=0,pc,op1[35],op2[35],rg[4];
  f=fopen("d25a.txt","r");
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
  for (i=0;;i++) {
    pc=rg[1]=rg[2]=rg[3]=0;
    rg[0]=i;
    count=0;
    while (pc<last) {
      switch (ops[pc]) {
         case 'c' : if (op2[pc]<1000) break;
                    rg[op2[pc]-1000]=(op1[pc]>=1000) ? rg[op1[pc]-1000] : op1[pc];
                    break;
         case 'i' : if (op1[pc]<1000) break;
                    rg[op1[pc]-1000]++;
                    break;           
         case 'd' : if (op1[pc]<1000) break;
                    rg[op1[pc]-1000]--;
                    break;
         case 'o' : j=(op1[pc]>=1000) ? rg[op1[pc]-1000] : op1[pc];
                    if (count) { 
                      b=1-b;
                      if (b==j) count++;
                       else pc=last;
                      if (count==20) pc=last; 
                    } else {   
                      b=j;
                      count=1;
                    }  
                    break;  
         case 't' : j=(op1[pc]>=1000) ? rg[op1[pc]-1000]+pc : op1[pc]+pc;
                    if (j>=0 && j<last) {
                      if (ops[j]=='i') ops[j]='d';
                       else if (ops[j]=='d' || ops[j]=='t') ops[j]='i';
                       else if (ops[j]=='c') ops[j]='j';
                       else if (ops[j]=='j') ops[j]='c';
                    }
                    break;                         
         case 'j' : j=(op2[pc]>=1000) ? rg[op2[pc]-1000] : op2[pc]; 
                    if (op1[pc]>=1000) { if (rg[op1[pc]-1000]) pc+=j-1; }
                     else if (op1[pc]) pc+=j-1;
      }
      pc++;
    }
    if (count==20) {
      printf("reg a=%d\n",i);
      break;
    }  
  }                             
}
