#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,*s3,*xp,ltrs[26],sort[6],c,xlat[100];
  int i,j,k,id,cnt[6],sum=0;
  f=fopen("d04a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    memset(ltrs,0,sizeof(ltrs));
    memset(cnt,0,sizeof(cnt));
    s3=strrchr(s,'-')+1;
    id=atoi(s3);
    xp=xlat;
    s2=s;
    while (s2<s3) {
      c=*s2++;
      if (c!='-') {
        ltrs[c-'a']++;
        *xp++=(c-'a'+id)%26+'a';
      } else *xp++=' ';  
    }
    s2=strchr(s2,'[')+1;
    sort[0]='a';
    cnt[0]=ltrs[0];
    for (i=1; i<26; i++) {
      j=0;
      while (j<5 && ltrs[i]<=cnt[j]) j++;
      for (k=4; k>j; k--) {
        sort[k]=sort[k-1];
        cnt[k]=cnt[k-1];
      }
      sort[j]=i+'a';
      cnt[j]=ltrs[i];
    }
    if (strncmp(sort,s2,5)==0) {
      sum+=id;
      *xp=0;
      printf("%d %s\n",id,xlat);
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  printf("Sum=%d\n",sum); 
}
