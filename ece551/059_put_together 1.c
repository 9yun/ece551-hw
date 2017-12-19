#include<stdio.h>
#include<stdlib.h>

int main(){
  const char li[]="hello\n";
  const char *li1="hello\n";
  char *s="hello\n";
  char p[]="hello\n";
  char w[]={"hello\n"};
  // char *a={'h','e','l','l','o','\n'};
  //  int *arr={1,1,1,1};
   int arr1[]={1,1,1,};
  char **c={"apple","banana" ,"red"};
  char c1[][]={"apple" ,"banana","red"};
  double **num={{1.1,1.1}{2.2,2.2}};
  printf("%s%s\n%s\n%s\n%d\n%d\n",li,s,p,w,arr,arr1);
  for(int i=0;i<3;i++){
    printf("%s\n",c[i],c1[i]);
  }
  for(int i=0;i<2;i++){
    for(int j=0;j<4;j++){
    printf("%f\n",num[i][j]);
    }
    }
  printf("%s%s",li,li1);
}
