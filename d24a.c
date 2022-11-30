#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  struct leg { 
          unsigned char now,used;
          short dist;
        };
  FILE *f;
  char s[42][188],*s2;
  int last=0,fnd,w,x,y,i,j,k,n,cc,xy[41][185],dd[8][8],xx[7500],yy[7500];
  int best=99999,best2=99999;
  struct leg stk[5000],nxt,nn;
  f=fopen("d24a.txt","r");
  fgets(s[last],sizeof(s[0]),f);
  while (!feof(f)) {
    if((s2=strchr(s[last],'\n')))*s2=0;
    last++;
    fgets(s[last],sizeof(s[0]),f);
  }  
  fclose(f);
  w=strlen(s[0]);
  for (i=0; i<7; i++) {
    memset(xy,0,sizeof(xy));
    for (y=0;y<last;y++) for (x=0;x<w;x++) {
      cc=s[y][x];
      if (cc=='#') xy[y][x]=999;
      else if (cc!='.') {
        if (cc-'0'==i) {
          j=x;
          k=y;
        }
        else if (cc-'0'>i) xy[y][x]='0'-cc;  
      }
    }
    fnd=(1<<(i+1))-1;
    xx[0]=j;
    yy[0]=k;
    xy[k][j]=1;
    j=0;
    k=1;
    while (fnd!=255) {
      x=xx[j]; y=yy[j++];
      cc=xy[y][x];
      if ((n=xy[y+1][x])<1) {
        if (n<0) {
          dd[i][-n]=dd[-n][i]=cc;
          fnd+=1<<(-n);
        }
        xx[k]=x;
        yy[k++]=y+1;
        xy[y+1][x]=cc+1;
      }       
      if ((n=xy[y-1][x])<1) {
        if (n<0) {
          dd[i][-n]=dd[-n][i]=cc;
          fnd+=1<<(-n);
        }
        xx[k]=x;
        yy[k++]=y-1;
        xy[y-1][x]=cc+1;
      }       
      if ((n=xy[y][x+1])<1) {
        if (n<0) {
          dd[i][-n]=dd[-n][i]=cc;
          fnd+=1<<(-n);
        }
        xx[k]=x+1;
        yy[k++]=y;
        xy[y][x+1]=cc+1;
      }       
      if ((n=xy[y][x-1])<1) {
        if (n<0) {
          dd[i][-n]=dd[-n][i]=cc;
          fnd+=1<<(-n);
        }
        xx[k]=x-1;
        yy[k++]=y;
        xy[y][x-1]=cc+1;
      }
    }
  }    
  stk[0].now=0;
  stk[0].used=1;
  stk[0].dist=0;
  last=1;
  while (last) {
    nxt=stk[--last];
    if (nxt.dist>best2) continue;
    if (nxt.used==255) {
      if (nxt.dist<best) best=nxt.dist;
      if (nxt.dist+dd[0][(int)nxt.now]<best2) best2=nxt.dist+dd[0][(int)nxt.now];
      continue;
    }  
    for (i=1;i<8;i++) if (((1<<i) & nxt.used)==0) {
      nn=nxt;
      nn.dist+=dd[(int)nn.now][i];
      if (nn.dist>best2) continue;
      nn.now=i;
      nn.used+=(1<<i);
      j=last;
      while (j && nn.dist>stk[j-1].dist) {
        stk[j]=stk[j-1];
        j--;
      }
      stk[j]=nn;
      last++;
    }
  }
  printf("best=%d\n",best);    
  printf("best ending at start=%d\n",best2);    
}
