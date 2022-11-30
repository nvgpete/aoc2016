#include <stdio.h>
#include <string.h>
#define OUTPUT 1000
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int outb[24],lo[220],hi[220],t1[220],t2[220],v,b1,b2,tk1,tk2,stk[20],sptr=0;
  memset(t1,0,sizeof(t1));
  memset(t2,0,sizeof(t2)); 
  f=fopen("d10a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if (*s=='v') {
      sscanf(s,"value %d goes to bot %d",&v,&b1);
      if (t1[b1]) {
        t2[b1]=v;
        stk[sptr++]=b1;
      } else t1[b1]=v; 
    } else if ((s2=strstr(s,"output"))) {
      if (strstr(s2+6,"output")) {
        sscanf(s,"bot %d gives low to output %d and high to output %d",&v,&b1,&b2);
        hi[v]=b2+OUTPUT;
      } else {
        sscanf(s,"bot %d gives low to output %d and high to bot %d",&v,&b1,&b2);
        hi[v]=b2;
      }
      lo[v]=b1+OUTPUT;
    } else {
      sscanf(s,"bot %d gives low to bot %d and high to bot %d",&v,&b1,&b2);
      lo[v]=b1;
      hi[v]=b2;
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  while (sptr) {
    sptr--;
    v=stk[sptr];
    if (t1[v]<t2[v]) { tk1=t1[v]; tk2=t2[v]; }
    else {tk1=t2[v]; tk2=t1[v]; }
    if (tk1==17 && tk2==61) {
      printf("%d sorts 17 and 61\n",v);
    }
    if ((b1=lo[v])<OUTPUT) {
      if (t1[b1]) {
        t2[b1]=tk1;
        stk[sptr++]=b1;
      } else t1[b1]=tk1;
    } else outb[b1-OUTPUT]=tk1;       
    if ((b2=hi[v])<OUTPUT) {
      if (t1[b2]) {
        t2[b2]=tk2;
        stk[sptr++]=b2;
      } else t1[b2]=tk2;
    } else outb[b2-OUTPUT]=tk2;
    t1[v]=t2[v]=0;
  }          
  printf("product=%d\n",outb[0]*outb[1]*outb[2]);
}
