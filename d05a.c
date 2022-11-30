#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
int main(int argc,char **argv) {
  char s2[20]="reyedfim",p1[9],p2[9]="xxxxxxxx";
  unsigned char s[16];
  int i=0,j=0,k,n;
  do {
    i++;
    sprintf(s2+8,"%d",i);
    MD5((unsigned char *)s2,strlen(s2),s);
    if ((*s | *(s+1) | (*(s+2) & 0xf0))==0) {
      k=*(s+2)&15;
      if (j<8) {
        if (k<10) p1[j]=k+'0';
        else p1[j]+=k-10+'a';
        j++;
      }
      if (k<8 && p2[k]=='x') {
        n=*(s+3)>>4;
        if (n<10) p2[k]=n+'0';
        else p2[k]=n-10+'a';
      }  
    }
  } while (strchr(p2,'x'));
  p1[8]=0;
  printf("password 1=%s\n",p1);        
  printf("password 2=%s\n",p2);        
}
