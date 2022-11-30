#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,ss[10];
  int i,j,min,max,k,k1,cnt[8][26];
  memset(cnt,0,sizeof(cnt));
  f=fopen("d06a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    for (i=0; i<8; i++) cnt[i][s[i]-'a']++;
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (i=0; i<8; i++) {
    max=cnt[i][0];
    min=cnt[i][0];
    k=0;
    k1=0;
    for (j=1; j<26; j++) {
      if (cnt[i][j]>max) {
        max=cnt[i][j];
        k=j;
      }
      if (cnt[i][j]<min) {
        min=cnt[i][j];
        k1=j;
      }
    }  
    s[i]=k+'a';
    ss[i]=k1+'a';
  }
  s[8]=0;
  ss[8]=0;
  printf("decoded part a=%s\n",s);     
  printf("decoded part b=%s\n",ss);     
}
