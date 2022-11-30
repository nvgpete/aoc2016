#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int n=0,m,pos[6],start[6];
  f=fopen("d15a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"Disc #%d has %d positions; at time=0, it is at position %d",&m,pos+n,start+n);
    n++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  m=0;
  while (1) {
    for (n=0;n<6;n++) if ((m+start[n]+n+1)%pos[n]) break;
    if (n==6) break;
    m++;
  }
  printf("Part a time =%d\n",m);
  n=pos[0]*pos[1]*pos[2]*pos[3]*pos[4]*pos[5];
  while ((m+7)%11) m+=n;
  printf("Part b time=%d\n",m);  
}
