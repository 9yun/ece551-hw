#include<math.h>
#include"function.h"
#include<iostream>
#include<cstdlib>
#include<cstdio>
//#include"search.cpp"

int binarySearchForZero(Function<int, int> *f,int low, int high);


void check(Function<int, int> *f, int low, int high, int expc, const char *s){
  int max = log10(high - low)/log10(2)+1;
  std::cout << "max:" << max;
  CountedIntFn *test = new CountedIntFn(max, f, s);
  //std::cout << max << "\n";
  int ans = binarySearchForZero(test, low, high);
  std::cout << "ans:" << ans;
  int num = test->invoke(ans);
  std::cout << "num:" << num;
  /*  if(num <= 0){
    exit(EXIT_FAILURE);
    }*/
  if(num > max){
    std::cout << s;
    delete test;
    exit(EXIT_FAILURE);
  }
  else if(ans == expc){
    std::cout << "right.\n";
    delete test;
  }
  else{
    std::cout << "compute wrong.\n";
    delete test;
    exit(EXIT_FAILURE);
  }
}


class SinFunction: public Function<int, int> {
public:
  virtual int invoke(int arg){
    return 1000000 * (sin(arg/100000.0)-0.5);
  }
};

class IntFunction: public Function<int ,int>{
public:
  virtual int invoke(int arg){
    return arg-2;
  }
};


class IntFunction1: public Function<int, int>{
public:
  virtual int invoke(int arg){
    return 10*arg+5;
  }
};


int main(){
  Function<int, int> *a = new SinFunction();
  Function<int, int> *b = new IntFunction();
  Function<int, int> *c = new IntFunction1();
  int low = 1;
  int high = 500;
  const char * s = "all positive.\n";
  const char * s1 = "all negative.\n";
  const char * s2 = "part positive part negetive.\n"; 
  check(b, low, high, 2, s);
  //std::cout << s;
  low = -10;
  high = 0;
  check(b, low, high, -1, s1);
  low = -10;
  high = 10;
  check(b, low, high, 2, s2);
  low = 0;
  high = 150000;
  check(a, low, high, 52359, s);
  low = -3;
  high = 2;
  check(c, low, high, -1, s);
  delete a;
  delete b;
  delete c;
  return EXIT_SUCCESS;
}  
