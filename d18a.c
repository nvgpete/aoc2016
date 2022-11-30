#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[2][102],*s0,*s1,*t;
  int i,x,count=0;
  memset(s,'.',sizeof(s));
  f=fopen("d18a.txt","r");
  fgets(s[0]+1,101,f);
  fclose(f);
  s[0][101]='.'; // fgets uses /0 for last character
  for (x=1; x<=100; x++) count+=(s[0][x]=='.');
  s0=s[0];
  s1=s[1];
  for (i=1; i<400000; i++) {
    if (i==40) printf("Count(40)=%d\n",count);
    for (x=1; x<=100; x++) if (s0[x-1]!=s0[x+1]) s1[x]='^'; else count++;
    t=s0; s0=s1; s1=t;
    memset(s1,'.',102);
  }  
  printf("Count(400000)=%d\n",count);
}
