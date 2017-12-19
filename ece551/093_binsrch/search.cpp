#include"function.h"
//#include"test-bsearch.cpp"
#include<cstdlib>
#include<cstdio>


int binarySearchForZero(Function<int, int> *f,int low, int high){
  int half = (low + high)/2;
  while((high - low) > 1){
    int j = f->invoke(half);
    if(j > 0){
      high = half;
    }
    else if(j == 0){
      return half;
    }
    else{
      low = half;
    }
    half = (low + high)/2;
    //std::cout << half;
 }
  if(high - low == 1){
    return low;
  }
  return half;
}
