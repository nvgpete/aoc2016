#include <stdio.h>
#include <string.h>
#define SCRAMBLE "fbgdceah"
int main(int argc,char **argv) {
  FILE *f;
  char c,c2,s[100],*s2,*s3,pw[9]="abcdefgh",pw2[9];
  char opc[105];
  int op1[105],op2[105];
  int i,j,k,k2,k3,last=0,xlat[8]={7,7,2,6,1,5,0,4};
  f=fopen("d21a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if (strncmp(s,"swap p",6)==0) {
      sscanf(s,"swap position %d with position %d",op1+last,op2+last);
      opc[last++]='P';
    } else if (strncmp(s,"swap l",6)==0) {  
      sscanf(s,"swap letter %c with letter %c",&c,&c2);
      op1[last]=c; op2[last]=c2;
      opc[last++]='L';
    } else if (strncmp(s,"rotate",6)==0) {
      if (s[7]=='r') { 
        sscanf(s,"rotate right %d",op1+last);
        opc[last++]='R';
      } else if (s[7]=='l') { 
        sscanf(s,"rotate left %d",&i);
        op1[last]=(-i)&7;
        opc[last++]='R';
      } else {
        sscanf(s,"rotate based on position of letter %c",&c);
        op1[last]=c;
        opc[last++]='S';
      }  
    } else if (s[0]=='r') {  
      sscanf(s,"reverse positions %d through %d",op1+last,op2+last);
      opc[last++]='V';
    } else {
      sscanf(s,"move position %d to position %d",op1+last,op2+last);
      opc[last++]='M';
    }
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  for (k2=1; k2>=0; k2--) {
    for (k3=0;k3<last;k3++) {
      k=(k2) ? k3 : last-k3-1;
      switch (opc[k]) {
        case 'P': // swap by position, symmetric 
          c=pw[op1[k]]; pw[op1[k]]=pw[op2[k]]; pw[op2[k]]=c;
          break;
        case 'L':  // swap by letter, symmetric
          s2=strchr(pw,op1[k]); s3=strchr(pw,op2[k]);
          *s3=op1[k]; *s2=op2[k];
          break;
        case 'R':  // rotate right/left -> left/right
          i=(k2) ? op1[k] : (-op1[k]) & 7;
        case 'S':  // rotate by position, use xlat[] for inverse
          if (opc[k]=='S') {
            i=(strchr(pw,op1[k])-pw);
            if (k2) {
              i++;
              if (i>4) i++;
              i&=7;
            } else i=xlat[i];
          }
          for (j=0; j<8; j++) pw2[(j+i)&7]=pw[j];
          strncpy(pw,pw2,8);
          break;
        case 'V': // reverse substring, symmetric 
          i=op1[k];
          j=op2[k];
          while (i<j) {
            c=pw[i]; pw[i]=pw[j]; pw[j]=c;
            i++;
            j--;
          }
          break;
        case 'M':  // move by position, op1 <-> op2
          if (k2) {
            i=op1[k];
            j=op2[k];
          } else {  
            j=op1[k];
            i=op2[k];
          }  
          c=pw[i];
          while (j<i) { pw[i]=pw[i-1]; i--; }
          while (j>i) { pw[i]=pw[i+1]; i++; }
          pw[j]=c;
      }    
    }
    if (k2) printf("scrambled password=%s\n",pw);
    else printf("unscrambled password=%s\n",pw);
    strcpy(pw,SCRAMBLE);
  }
}     
