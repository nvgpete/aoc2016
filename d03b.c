#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f2;
  char s[100],*s2;
  int a,b,c,d,e,f,g,h,i,pos=0;
  f2=fopen("d03a.txt","r");
  fgets(s,sizeof(s),f2);
  while (!feof(f2)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d %d %d",&a,&d,&g);
    fgets(s,sizeof(s),f2);
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d %d %d",&b,&e,&h);
    fgets(s,sizeof(s),f2);
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"%d %d %d",&c,&f,&i);
    pos+=(a+b>c && b+c>a && a+c>b);
    pos+=(d+e>f && e+f>d && d+f>e);
    pos+=(g+h>i && h+i>g && g+i>h);
    fgets(s,sizeof(s),f2);
  }  
  fclose(f2);
  printf("%d possible triangles\n",pos); 
}
