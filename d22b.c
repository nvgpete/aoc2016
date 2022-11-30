#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,xy[35][31];
  int  x,y,tot,use,avl;
  memset(xy,'.',sizeof(xy));
  for (y=0;y<35;y++) xy[y][30]=0;
  f=fopen("d22a.txt","r");
  fgets(s,sizeof(s),f);
  fgets(s,sizeof(s),f);
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    sscanf(s,"/dev/grid/node-x%d-y%d %dT %dT %dT",&x,&y,&tot,&use,&avl);
    if (tot>100) xy[y][x]='#';
    else if (use==0) xy[y][x]=' ';
    fgets(s,sizeof(s),f);
  }
  xy[0][29]='*';  
  fclose(f);
  for (y=0; y<35; y++) printf("%s\n",xy[y]); 
}
