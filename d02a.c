#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char c,s[550],*s2,res[10],pad[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
  int nxt=0,i,j;
  f=fopen("d02a.txt","r");
  fgets(s,sizeof(s),f);
  i=j=1;
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s;
    while ((c=*s2++)) {
      switch (c) {
        case 'L': if (i) i--; break;
        case 'R': if (i<2) i++; break;
        case 'U': if (j) j--; break;
        case 'D': if (j<2) j++;
      }
    }
    res[nxt++]=pad[j][i];    
    fgets(s,sizeof(s),f);
  }  
  res[nxt]=0;
  printf("combination=%s\n",res);
  fclose(f); 
}
