#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char c,s[150],*s2,aba[4]="   ",inb[100],outb[100];
  int tls=0,ssl=0,ok1,ok2,bracket;
  f=fopen("d07a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s;
    bracket=0;
    ok1=0;
    ok2=0;
    inb[0]=0;
    outb[0]=0;
    while ((c=*s2++)) {
      if (c=='[') bracket=1;
       else if (c==']') bracket=0;
       else if (c==*s2 && *(s2-2)==*(s2+1) && c!=*(s2+1) && ok1>=0) {
         if (bracket) ok1=-1;
         else ok1=1;
       } else if (ok2==0 && c==*(s2+1) && c!=*s2) {
         if (bracket) {
           aba[2]=c;
           aba[1]=*s2;
           if(strstr(outb,aba+1)) ok2=1;
           strcat(inb,aba);
         } else {  
           aba[1]=c;
           aba[2]=*s2;
           if(strstr(inb,aba+1)) ok2=1;
           strcat(outb,aba);
         }
       }    
    }
    if (ok1==1) tls++;
    if (ok2) ssl++;    
    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
  printf("%d support TLS\n",tls);
  printf("%d support SSL\n",ssl);
}
