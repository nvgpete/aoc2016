#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
int main(int argc,char **argv) {
  char s2[20]="ahsbgdzn";
//  char s2[20]="abc";
  char sh[34],*ss,cc[25000];
  unsigned char s[16];
  int i=0,j,k,n,ok[90],last=0;
  sh[32]=sh[33]=0;
  do {
    sprintf(s2+8,"%d",i);
    MD5((unsigned char *)s2,strlen(s2),s);
    for (j=0,ss=sh;j<16;j++) {
      *ss++=(s[j]>>4) + (((s[j]>>4)<10) ? '0' : 'a'-10);
      *ss++=(s[j]&15) + (((s[j]&15)<10) ? '0' : 'a'-10);
    }
#ifdef PARTB
    for (n=0;n<2016;n++) {
      MD5((unsigned char *)sh,32,s);
      for (j=0,ss=sh;j<16;j++) {
        *ss++=(s[j]>>4) + (((s[j]>>4)<10) ? '0' : 'a'-10);
        *ss++=(s[j]&15) + (((s[j]&15)<10) ? '0' : 'a'-10);
      }
    }  
#endif
    ss=sh;
    while (*(ss+2) && (*ss!=*(ss+1) || *ss!=*(ss+2))) ss++;
    if (*(ss+2)) { 
      cc[i]=*ss;
      while (*(ss+4) && (*ss!=*(ss+1) || *ss!=*(ss+2) || *ss!=*(ss+3) || *ss!=*(ss+4))) ss++;
      if (*(ss+4)) {
        for (k=(i<1000) ? 0 : i-1000;k<i;k++) if (cc[k]==*ss) {
          j=last;
          while (j && ok[j-1]>k) { ok[j]=ok[j-1]; j--;}
          ok[j]=k;
          last++;
          cc[k]=0;
        }  
      }
    }  else cc[i]=0;  
    i++;
  } while (last<64 ||  i-ok[last]<1000);
  printf("%d\n",ok[63]);
}
