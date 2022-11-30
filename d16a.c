#include <stdio.h>
#include <string.h>
#ifdef PARTB
#define SIZE 35651584
#else
#define SIZE 272
#endif
  char s[SIZE];
int main(int argc,char **argv) {
  char *s2,*s3;
  int len;
  strcpy(s,"11110010111001001");
  len=strlen(s);
  while (len<SIZE) {
    s2=s+len;
    *s2--='0';
    s3=s+len+1;
    while (s2>=s && s3-s<SIZE) *s3++=(*s2--)^1;
    len=2*len+1;
  }
  len=SIZE;
  while ((len & 1)==0) {
    for (s2=s,s3=s;s3-s<len;s2++,s3+=2) *s2=(*s3==*(s3+1))+'0';
    len>>=1;
  }
  s[len]=0;  
  printf("checksum=%s\n",s); 
}
