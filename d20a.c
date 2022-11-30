#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int i,last=0,count=0;
  unsigned a1,a2,best=0,lo[1100],hi[1100];
  f=fopen("d20a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%u-%u",&a1,&a2);
    i=last;
    while (i && lo[i-1]>a1) { // sort list by first IP
      lo[i]=lo[i-1];
      hi[i]=hi[i-1];
      i--;
    }
    lo[i]=a1;
    hi[i]=a2;
    last++;  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  a1=0;
  for (i=0;i<last;i++) {
    if (a1<lo[i]) {
      if (best==0) best=a1;
      count+=lo[i]-a1;
    }  
    if (a1<=hi[i]) a1=hi[i]+1;
    if (a1==0) break;
  }
  if (a1) count+=(1L<<32)-a1;
  printf("Lowest=%u\n",best);
  printf("Open=%d\n",count);    
}
