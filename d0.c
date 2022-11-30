#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2;
  f=fopen("d.txt"XX,"r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;

    fgets(s,sizeof(s),f);
  }  
  fclose(f); 
}
