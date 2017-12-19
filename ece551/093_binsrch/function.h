#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include<iostream>
#include<cstdio>
#include<cstdlib>


template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};


class CountedIntFn : public Function<int,int>{
 protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
 public:
 CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
    f(fn),
    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};
/*
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
*/
#endif
