#include <stdio.h>
#include <string.h>
int main(int argc,char **argv) {
  FILE *f;
  char s[100],*s2,scr[12][100];
  int r,c,row,col,count;
  memset(scr,' ',sizeof(scr));
  f=fopen("d08a.txt","r");
  fgets(s,sizeof(s),f);
  while (!feof(f)) {
    if((s2=strchr(s,'\n')))*s2=0;
    if (s[1]=='e') {
      sscanf(s,"rect %dx%d",&col,&row);
      for (r=0;r<row;r++) for (c=0;c<col;c++) scr[r][c]='#';
    } else if (s[7]=='r') {
      sscanf(s,"rotate row y=%d by %d",&row,&col);
      memmove(scr[row]+col,scr[row],50);
      memmove(scr[row],scr[row]+50,col);
    } else {
      sscanf(s,"rotate column x=%d by %d",&col,&row);   
      for (r=5; r>=0; r--) scr[r+row][col]=scr[r][col];
      for (r=0; r<row; r++) scr[r][col]=scr[r+6][col];
    }  
    fgets(s,sizeof(s),f);
  }  
  fclose(f);
  count=0;
  printf("\n");
  for (r=0;r<6;r++) { 
    for (c=0;c<50;c++) {
      printf("%c",scr[r][c]);
      if (scr[r][c]=='#') count++;
    }
    printf("\n");
  }    
  printf("\n%d filled pixels\n",count);
}
