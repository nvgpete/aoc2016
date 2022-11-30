#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#define START "mmsxrhfx"
int best=999,worst=0;
char bstr[100];
void next(char *s,int x,int y) {
  unsigned char s2[16];
  int k;
  k=strlen(s);
  s[k+1]=0;
  if (x==3 && y==3) {
    if (k>worst) worst=k;
    if (k<best) {
      best=k;
      strncpy(bstr,s+8,100);
    }
    return;
  }      
  MD5((unsigned char *)s,strlen(s),s2);
  if (y && (s2[0]>>4)>10) {
    s[k]='U';
    next(s,x,y-1);
  }
  if (y<3 && (s2[0]&15)>10) {
    s[k]='D';
    next(s,x,y+1);
  }
  if (x && (s2[1]>>4)>10) {
    s[k]='L';
    next(s,x-1,y);
  }
  if (x<3 && (s2[1]&15)>10) {
    s[k]='R';
    next(s,x+1,y);
  }
  s[k]=0;
  return;
}
  
int main(int argc,char **argv) {
  char s[650]; 
  strcpy(s,START);
  next(s,0,0);
  printf("Path=%s\n",bstr);        
  printf("Longest Path=%d\n",worst-8);        
}
