#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef SORT
#define SIZE 10000
#define HBITS 16
#else
#define SIZE 2000000
#define HBITS 23
#endif
#define MM 4210987661U
struct silo {
          unsigned char fc[3],fg[3],best,steps; // high bit of fc set for elevator floor
        };                                      // best=theoretical fewest steps to end
unsigned char fnd[1<<HBITS];
unsigned ap[1<<HBITS];
struct silo todo[SIZE];
int last=1,max=0;
void print(struct silo p) {
  char c=0,g=0;
  int i,j;
  for (i=2;i>=0;i--) {
    if (p.fc[i]&128) printf("* "); else printf("  ");
    c|=p.fc[i];
    g|=p.fg[i];
    for (j=0;j<7;j++) {
      if(p.fc[i]&(1<<j)) printf("c%d ",j);
      if(p.fg[i]&(1<<j)) printf("g%d ",j);
    }
    printf("\n");
  }
  c^=255; g^=127;
  if(c&128) printf("* "); else printf("  ");
  for (j=0;j<7;j++) {
    if(c&(1<<j)) printf("c%d ",j);
    if(g&(1<<j)) printf("g%d ",j);
  }
  printf("\n%d %d\n",p.best,last);
}   
      
int ok (struct silo p) {
  int i;
  unsigned char fc0=0,fg0=0;
  for (i=0;i<3;i++) {
    fc0+=p.fc[i]&127; fg0+=p.fg[i]; // &127 masks floor
    if (p.fg[i]==0) continue; // no gens, floor i+2
    if ((p.fc[i]&p.fg[i])!=(p.fc[i]&127)) return 0; // return 0 if lone chips found, floor i+2
  }  
  if ((fg0^=127)==0) return 1; // no gens, floor 1
  fc0^=127; 
  return ((fc0&fg0)==fc0); // check for lone chips, floor 1 
}
    
void insert(struct silo p) { // insert, sort on best 
  int k=last;
  if (ok(p)) {
    while (k && todo[k-1].best<p.best) {
      todo[k]=todo[k-1];
      k--;
    }   
    todo[k]=p;
    last++;
    if (last==SIZE) {
      printf("Buffer too small at step %d, best=%d\n",p.steps,p.best);
      exit(0);
    }
    if (last>max) max=last;
  }
}  

int main(int argc,char **argv) {
  struct silo pnew,p={{0,30,0},{30,0,0},51,0}; // 51=theoretical fewest steps
  unsigned char flr,b,bb,c,g,cg,jj[7];
  unsigned aptr,ap2;
  int i,j;
  memset(fnd,255,sizeof(fnd));
  memset(ap,0,sizeof(ap));
  todo[0]=p;
  while ((todo[last-1].fc[2]&todo[last-1].fg[2])!=127) {
    if (last==0) exit(0);
    p=todo[--last];
    flr=0;
    for (i=1; i<4; i++) if (p.fc[i-1]&128) flr=i;
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
    aptr+=flr<<28;
    ap2=(aptr*MM)&((1<<HBITS)-1);
    while (ap[ap2&((1<<HBITS)-1)] && ap[ap2&((1<<HBITS)-1)]!=aptr) {
      ap2++;
      if (ap2==(1<<(HBITS+1))) {
        printf("Hash overflow at step %d, last=%d\n",p.steps,last);
        exit(0);
      }  
    }
    ap2&=((1<<HBITS)-1);
    if (fnd[ap2]<=p.steps) continue;
    ap[ap2]=aptr;
    fnd[ap2]=p.steps;
    if (flr) p.fc[flr-1]&=127; 
    c=(flr) ? p.fc[flr-1] : (p.fc[0]+p.fc[1]+p.fc[2])^127;
    g=(flr) ? p.fg[flr-1] : (p.fg[0]+p.fg[1]+p.fg[2])^127;
    cg=c&g;
    if (flr!=3) { // up first
      if (cg) for (i=0;i<7;i++) if ((b=cg&(1<<i))) {
        pnew=p;
        pnew.fc[flr]|=b+128;
        pnew.fg[flr]|=b;
        if (flr) {
          pnew.fc[flr-1]^=b;
          pnew.fg[flr-1]^=b;
        }
        pnew.steps++;
        insert(pnew);
        break;   
      }
      if (c) for (i=0; i<7; i++) if ((b=c&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=c&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.fc[flr]|=bb+128;
          if (flr) pnew.fc[flr-1]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.fc[flr]|=b+128;
        if (flr) pnew.fc[flr-1]^=b;
        pnew.steps++;
        pnew.best+=2;
        insert(pnew);   
      }
      if (g) for (i=0; i<7; i++) if ((b=g&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=g&(1<<j))) {
          bb|=b; 
          pnew=p;
          pnew.fc[flr]|=128;
          pnew.fg[flr]|=bb;
          if (flr) pnew.fg[flr-1]^=bb;
          pnew.steps++;
          insert(pnew);   
        }
        pnew=p;
        pnew.fc[flr]|=128;
        pnew.fg[flr]|=b;
        if (flr) pnew.fg[flr-1]^=b;
        pnew.steps++;
        pnew.best+=2;
        insert(pnew);   
      }
    }
    if (flr) { //down
      if (cg) for (i=0;i<7;i++) if ((b=cg&(1<<i))) {
        pnew=p;
        if (flr>1) {
          pnew.fc[flr-2]|=b+128;
          pnew.fg[flr-2]|=b;
        }  
        pnew.fc[flr-1]^=b;
        pnew.fg[flr-1]^=b;
        pnew.steps++;
        pnew.best+=2;
        insert(pnew);
        break;   
      }
      if (c) for (i=0; i<7; i++) if ((b=c&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=c&(1<<j))) {
          bb|=b; 
          pnew=p;
          if (flr>1) pnew.fc[flr-2]|=bb+128;
          pnew.fc[flr-1]^=bb;
          pnew.steps++;
          pnew.best+=2;
          insert(pnew);   
        }
        pnew=p;
        if (flr>1) pnew.fc[flr-2]|=b+128;
        pnew.fc[flr-1]^=b;
        pnew.steps++;
        insert(pnew);   
      }
      if (g) for (i=0; i<7; i++) if ((b=g&(1<<i))) { 
        for (j=i+1; j<7; j++) if ((bb=g&(1<<j))) {
          bb|=b; 
          pnew=p;
          if (flr>1) {
            pnew.fc[flr-2]|=128;
            pnew.fg[flr-2]|=bb;
          }  
          pnew.fg[flr-1]^=bb;
          pnew.steps++;
          pnew.best+=2;
          insert(pnew);   
        }
        pnew=p;
        if (flr>1) {
          pnew.fc[flr-2]|=128;
          pnew.fg[flr-2]|=b;
        }  
        pnew.fg[flr-1]^=b;
        pnew.steps++;
        insert(pnew);   
      }    
    }
  }
  j=0;
  for (i=0;i<sizeof(fnd);i++) if (fnd[i]!=255) j++;
  printf("%d steps, %d positions, max buff used=%d\n",todo[last-1].steps,j,max);
}
