#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  int a,b,c,pos=0;
  f=fopen("d03a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d %d %d",&a,&b,&c);
    pos+=(a+b>c && b+c>a && a+c>b);
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("%d possible triangles\n",pos); 
}
