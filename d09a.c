#include <stdio.h>
#include <string.h>
unsigned long leng(char *s) {
  char *s2,save;
  int len,rep;
  unsigned long n=0;
  while ((s2=strchr(s,'('))) {
    n+=s2-s;
    sscanf(s2+1,"%dx%d",&len,&rep);
    while (*s2++!=')');
    s=s2+len;
    save=*s;
    *s=0;
    n+=leng(s2)*rep;
    *s=save;
  }
  return n+strlen(s);
}  
  
int main(int argc,char **argv) {
  FILE *f;
  char s[20000],*s2,c;
  int len,rep,count=0,max=0;
  f=fopen("d09a.txt","r");
  fgets(s,sizeof(s),f);
  if((s2=strchr(s,'\n')))*s2=0;
  s2=s;
  while ((c=*s2++)) {
    if (c=='(') {
      sscanf(s2,"%dx%d",&len,&rep);
      if (len>max) max=len;
      count+=len*rep;
      while (*s2++!=')');
      s2+=len;
    }
    else count++;
  }    
  fclose(f);
  printf("Part A string length=%d\n",count);
  printf("Part B string length=%lu\n",leng(s)); 
}
