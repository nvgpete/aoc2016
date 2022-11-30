#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef SORT
#define SIZE 5000
#define HBITS 16
#else
#define SIZE 2000000
#define HBITS 23
#endif
#define MM 4210987661U
struct silo {
          unsigned char fc[3],fg[3],flr,steps;
        };
unsigned char fnd[1<<HBITS];
unsigned ap[1<<HBITS];
struct silo todo[SIZE];
int first=0,last=1,max=0;

int ok (struct silo p) {
  int i;
  unsigned char fc0=0,fg0=0;
  for (i=0;i<3;i++) {
    fc0+=p.fc[i]; fg0+=p.fg[i];
    if (p.fg[i]==0) continue;
    if ((p.fc[i]&p.fg[i])!=p.fc[i]) return 0;
  }  
  if ((fg0^=127)==0) return 1;
  fc0^=127;
  return ((fc0&fg0)==fc0); 
}
    
void insert(struct silo p) {
  int k,i;
  if (ok(p)) {
    todo[last++]=p;
    if (last==SIZE) last=0;
    if (first==last) {
      printf("Buffer too small at step %d\n",p.steps);
      k=0;
      for (i=0;i<sizeof(fnd);i++) if (fnd[i]!=255) k++;
      printf("first=%d, last=%d, max hash used=%d\n",first,last,k);
      exit(0);
    }
    k=(last-first>=0) ? last-first : last-first+SIZE;
    if (k>max) max=k;  
  }
}  

int main(int argc,char **argv) {
  struct silo pnew,p={{0,30,0},{30,0,0},0,0};
  unsigned char b,bb,c,g,cg,jj[7];
  unsigned aptr,ap2;
  int i,j;
  memset(fnd,255,sizeof(fnd));
  memset(ap,0,sizeof(ap));
  todo[0]=p;
  while ((todo[first].fc[2]&todo[first].fg[2])!=127) {
    p=todo[first++];
    if (first==SIZE) first=0;
    aptr=0;
    memset(jj,0,7);
    for (i=1; i<4; i++) {
      for (j=0; j<7; j++) {
#ifdef SORT
        if (p.fc[i-1]&(1<<j)) jj[j]+=i;
        if (p.fg[i-1]&(1<<j)) jj[j]+=i<<2;
#else        
        if (p.fc[i-1]&(1<<j)) aptr+=i<<(j*4);
        if (p.fg[i-1]&(1<<j)) aptr+=i<<(j*4+2);
#endif        
      }  
    }
#ifdef SORT    
    aptr=jj[0]<<(((jj[0]>jj[1])+(jj[0]>jj[2])+(jj[0]>jj[3])+(jj[0]>jj[4])+(jj[0]>jj[5])+(jj[0]>jj[6]))*4);  
    aptr+=jj[1]<<(((jj[1]>=jj[0])+(jj[1]>jj[2])+(jj[1]>jj[3])+(jj[1]>jj[4])+(jj[1]>jj[5])+(jj[1]>jj[6]))*4);  
    aptr+=jj[2]<<(((jj[2]>=jj[0])+(jj[2]>=jj[1])+(jj[2]>jj[3])+(jj[2]>jj[4])+(jj[2]>jj[5])+(jj[2]>jj[6]))*4);  
    aptr+=jj[3]<<(((jj[3]>=jj[0])+(jj[3]>=jj[1])+(jj[3]>=jj[2])+(jj[3]>jj[4])+(jj[3]>jj[5])+(jj[3]>jj[6]))*4);  
    aptr+=jj[4]<<(((jj[4]>=jj[0])+(jj[4]>=jj[1])+(jj[4]>=jj[2])+(jj[4]>=jj[3])+(jj[4]>jj[5])+(jj[4]>jj[6]))*4);  
    aptr+=jj[5]<<(((jj[5]>=jj[0])+(jj[5]>=jj[1])+(jj[5]>=jj[2])+(jj[5]>=jj[3])+(jj[5]>=jj[4])+(jj[5]>jj[6]))*4);  
    aptr+=jj[6]<<(((jj[6]>=jj[0])+(jj[6]>=jj[1])+(jj[6]>=jj[2])+(jj[6]>=jj[3])+(jj[6]>=jj[4])+(jj[6]>=jj[5]))*4);  
#endif    
    aptr+=p.flr<<28;
    ap2=(aptr*MM)&((1<<HBITS)-1);
    while (ap[ap2&((1<<HBITS)-1)] && ap[ap2&((1<<HBITS)-1)]!=aptr) {
      ap2++;
      if (ap2==(1<<(HBITS+1))) {
        printf("Hash overflow at step %d, first=%d, last=%d\n",p.steps,first,last);
        exit(0);
      }  
    }
    ap2&=((1<<HBITS)-1);
    if (fnd[ap2]<=p.steps) continue;
    ap[ap2]=aptr;
    fnd[ap2]=p.steps;
    c=(p.flr) ? p.fc[p.flr-1] : (p.fc[0]+p.fc[1]+p.fc[2])^127;
    g=(p.flr) ? p.fg[p.flr-1] : (p.fg[0]+p.fg[1]+p.fg[2])^127;
    cg=c&g;
    if (p.flr!=3) { // up first
      if (cg) for (i=0;i<7;i++) if ((b=cg&(1<<i))) {
        pnew=p;
        pnew.flr++;
        pnew.fc[p.flr]|=b;
        pnew.fg[p.flr]|=b;
        if (p.flr) {
          pnew.fc[p.flr-1]^=b;
          pnew.fg[p.flr-1]^=b;
        }
        pnew.steps++;
        insert(pnew);
        break;   
      }
      if (c) for (i=0; i<7; i++) if ((b=c&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=c&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.flr++;
          pnew.fc[p.flr]|=bb;
          if (p.flr) pnew.fc[p.flr-1]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.flr++;
        pnew.fc[p.flr]|=b;
        if (p.flr) pnew.fc[p.flr-1]^=b;
        pnew.steps++;
        insert(pnew);   
      }
      if (g) for (i=0; i<7; i++) if ((b=g&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=g&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.flr++;
          pnew.fg[p.flr]|=bb;
          if (p.flr) pnew.fg[p.flr-1]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.flr++;
        pnew.fg[p.flr]|=b;
        if (p.flr) pnew.fg[p.flr-1]^=b;
        pnew.steps++;
        insert(pnew);   
      }
    }
    if (p.flr) { //down
      if (cg) for (i=0;i<7;i++) if ((b=cg&(1<<i))) {
        pnew=p;
        pnew.flr--;
        if (pnew.flr) {
          pnew.fc[pnew.flr-1]|=b;
          pnew.fg[pnew.flr-1]|=b;
        }  
        pnew.fc[pnew.flr]^=b;
        pnew.fg[pnew.flr]^=b;
        pnew.steps++;
        insert(pnew);
        break;   
      }
      if (c) for (i=0; i<7; i++) if ((b=c&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=c&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.flr--;
          if (pnew.flr) pnew.fc[pnew.flr-1]|=bb;
          pnew.fc[pnew.flr]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.flr--;
        if (pnew.flr) pnew.fc[pnew.flr-1]|=b;
        pnew.fc[pnew.flr]^=b;
        pnew.steps++;
        insert(pnew);   
      }
      if (g) for (i=0; i<7; i++) if ((b=g&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=g&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.flr--;
          if (pnew.flr) pnew.fg[pnew.flr-1]|=bb;
          pnew.fg[pnew.flr]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.flr--;
        if (pnew.flr) pnew.fg[pnew.flr-1]|=b;
        pnew.fg[pnew.flr]^=b;
        pnew.steps++;
        insert(pnew);   
      }    
    }
  }
  j=0;
  for (i=0;i<sizeof(fnd);i++) if (fnd[i]!=255) j++;
  printf("%d steps, %d positions, max buff used=%d\n",todo[first].steps,j,max);
}
