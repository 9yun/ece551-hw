#include<stdio.h>
#include<stdlib.h>

int unsigned power(int unsigned x,int unsigned y){
  if(y==0){
  if(x==0){
    return 1;
  }
  else{
    return 1;
  }
  }
  else{
    if(x==0){
      return 0;
    }
    else if(x<0){
    x=4294967296+x;
    return power(x,y);
  }
    else{
      return x*power(x,y-1);
    }
  }
}
