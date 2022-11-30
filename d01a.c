#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[1000],*s2,dir=0,turn,xy[1000][1000];
  int i,x=0,y=0,dist,fnd=0;
  memset(xy,0,sizeof(xy));
  f=fopen("d01a.txt","r");
  fgets(s,sizeof(s),f);
  if((s2=strchr(s,'\n')))*s2=0;
  s2=s;
  do {
    turn=*s2++;
    dist=atoi(s2);
    if (turn=='L') dir=(dir-1)&3;
     else dir=(dir+1)&3;
    switch (dir) {
      case 0: if (!fnd) for (i=1;i<=dist;i++) {
              if (xy[x+500][y+i+500]) {
                printf("part b distance=%d\n",abs(x)+abs(y+i));
                fnd=1;
                break;
              } else xy[x+500][y+i+500]=1;
            }    
            y+=dist;
            break;
      case 1: if (!fnd) for (i=1;i<=dist;i++) {
              if (xy[x+i+500][y+500]) {
                printf("part b distance=%d\n",abs(x+i)+abs(y));
                fnd=1;
                break;
              } else xy[x+i+500][y+500]=1;
            }    
            x+=dist;
            break;
      case 2: if (!fnd) for (i=1;i<=dist;i++) {
              if (xy[x+500][y-i+500]) {
                printf("part b distance=%d\n",abs(x)+abs(y-i));
                fnd=1;
                break;
              } else xy[x+500][y-i+500]=1;
            }    
            y-=dist;
            break;
      case 3: if (!fnd) for (i=1;i<=dist;i++) {
              if (xy[x-i+500][y+500]) {
                printf("part b distance=%d\n",abs(x-i)+abs(y));
                fnd=1;
                break;
              } else xy[x-i+500][y+500]=1;
            }    
            x-=dist;
    }
    while (*s2 && *s2++!=' ');
  } while (*s2); 
  fclose(f); 
  printf("part a distance=%d\n",abs(x)+abs(y));
}
