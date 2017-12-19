#include<stdlib.h>
#include<stdio.h>
size_t maxSeq(int *array,size_t n);
void size_check(int *array,size_t n,size_t exp_size){
  size_t size;
  size=maxSeq(array,n);
  if(size!=exp_size){
    printf("faik\n");
     exit(EXIT_FAILURE);
  }
  else{
    printf("pass\n");
  }
}
int main(){
  int array[]={1,2,3,4,5,6};
  size_check(array,6,6);
  int array0[]={-1,1};
  size_check(array0,2,2);
  int myarray[6]= {1,1,1,1,1,1};
  size_check(myarray,6,1);
  int myarray1[0];
  size_check(myarray1,0,0);
  int myarray2[1]= {1};
  size_check(myarray2,1,1);
  int myarray3[5]={2147483645,1,-1,-3,-4};
  size_check(myarray3,5,1);
  int myarray4[]={1,2,2,3,4};
  size_check(myarray4,5,3);
  exit(EXIT_SUCCESS);
}
