#include<stdio.h>
#include<stdlib.h>


unsigned power(unsigned x, unsigned y);
int main(){
  unsigned result;
  result=power(0,0);
  if((result !=1)==1){
    printf("fail1.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  result=power(0,1);
  if((result !=0)==1){
    printf("fail2.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  result=power(-1,1);
  if(result !=4294967295){
    printf("fail3.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  result=power(1,0);
  if((result !=1)==1){
    printf("fail4.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  result=power(2,4);
  if((result !=16)==1){
    printf("fail5.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  result=power(30,2);
  if((result!=900)==1){
    printf("fail6.\n");
    exit(EXIT_FAILURE);
  }
  else{}
  printf("success!\n");
  exit(EXIT_SUCCESS);

}
