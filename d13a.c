#include <stdio.h>
#include <string.h>
#define BUNNY 1358
int wall(int x,int y) {
  return (__builtin_popcount(x*x+3*x+2*x*y+y+y*y+BUNNY))&1;
}
int main(int argc,char **argv) {
  unsigned char xy[100][100];
  int x=1,y=1,steps,count=0,last=0,first=0,xx[500],yy[500];
  memset(xy,0,sizeof(xy));
  xy[1][1]=1;
  while (x!=31 || y!=39) {
    if ((steps=xy[x][y])<=51) count++;
    steps++;
    if (xy[x+1][y]==0) {
      if (wall(x+1,y)) xy[x+1][y]=255;
      else {
        xx[last]=x+1;
        yy[last]=y;
        last++;
        xy[x+1][y]=steps;
      }
    }  
    if (xy[x][y+1]==0) {
      if (wall(x,y+1)) xy[x][y+1]=255;
      else {
        xx[last]=x;
        yy[last]=y+1;
        last++;
        xy[x][y+1]=steps;
      }
    }  
    if (x && xy[x-1][y]==0) {
      if (wall(x-1,y)) xy[x-1][y]=255;
      else {
        xx[last]=x-1;
        yy[last]=y;
        last++;
        xy[x-1][y]=steps;
      }
    }  
    if (y && xy[x][y-1]==0) {
      if (wall(x,y-1)) xy[x][y-1]=255;
      else {
        xx[last]=x;
        yy[last]=y-1;
        last++;
        xy[x][y-1]=steps;
      }
    }
    x=xx[first];
    y=yy[first];
    first++;
  }
#ifdef SHOW  
  for (x=0;x<45;x++) { 
    for (y=0; y<52; y++) {
      if (xy[x][y]==255) printf("## ");
      else if (xy[x][y]) printf("%2d ",xy[x][y]);
      else printf(".. ");
    }
    printf("\n");
  }
#endif  
  printf("Steps to (31,39)=%d, %d within 50 steps\n",xy[31][39]-1,count);
}
