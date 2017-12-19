//This file is for Step 1.
//You should do
#include<stdlib.h>
#include<stdio.h>
//  Step 1 (A): write seq1
int seq1(int x){
  int y=-3;
    y=y+4*x;
    return y;
}
void printSeqRange1(int low,int high){
  if(low>=high){
    printf("\n");
  }
  else{
    int i;
    int r;
    for(i=low;i<high;i++){
      r=seq1(i);
      printf("%d,",r);
    }
    r=seq1(high);
    printf("%d\n",r);
  }
}
int main(){
  int a;
  int b;
  for(a=-3;a<=3;a++){
  b=seq1(a);
  printf("seq1(%d)=%d\n", a,b);
  }
  int c;
  int d;
  c=-1;
  d=5;
  printf("printSeqRange1(%d,%d)\n",c,d);
  printSeqRange1(c,d);
  c=-3;
  d=10;
  printf("printSeqRange1(%d,%d)\n",c,d);
  printSeqRange1(c,d);
  c=0;
  d=0;
  printf("printSeqRange1(%d,%d)\n",c,d);
  printSeqRange1(c,d);
  c=6;
  d=2;
  printf("printSeqRange1(%d,%d)\n",c,d);
  printSeqRange1(c,d);
}
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
// 
// Be sure to #include any header files you need!

