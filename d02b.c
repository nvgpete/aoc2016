#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char c,s[550],*s2,res[10],pad[5][5]={{0,0,'1',0,0},{0,'2','3','4',0},{'5','6','7','8','9'},{0,'A','B','C',0},{0,0,'D',0,0}};
  int nxt=0,i,j;
  f=fopen("d02a.txt","r");
  fgets(s,sizeof(s),f);
  i=0;
  j=2;
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    s2=s;
    while ((c=*s2++)) {
      switch (c) {
        case 'L': if (i && pad[j][i-1]) i--; break;
        case 'R': if (i<4 && pad[j][i+1]) i++; break;
        case 'U': if (j && pad[j-1][i]) j--; break;
        case 'D': if (j<4 && pad[j+1][i]) j++;
      }
    }
    res[nxt++]=pad[j][i];    
    fgets(s,sizeof(s),f);
  }  
  res[nxt]=0;
  printf("combination=%s\n",res);
  fclose(f); 
}
