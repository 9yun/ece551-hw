#include "IntArray.h"
#include <assert.h>
#include <ostream>


IntArray::IntArray() {
  data=NULL;
  numElements=0;
}
IntArray::IntArray(int n) {
  data=new int[n];
  for(int i=0;i<n;i++){
    data[i]=0;
  }
  numElements=n;
}

IntArray::IntArray(const IntArray & rhs)  {
  if(rhs.numElements==0){
    data=NULL;
    numElements=0;
  }
  data=new int[rhs.numElements];
  for(int i=0;i<rhs.numElements;i++){
    data[i]=rhs.data[i];
  }
  numElements=rhs.numElements;
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if(this!=&rhs){
    if(rhs.numElements==0){
      delete []data;
      data=NULL;
      numElements=0;
    }
    int *temp=new int[rhs.numElements];
    for(int i=0;i<rhs.numElements;i++){
      temp[i]=rhs.data[i];
    }
    delete []data;
    data=temp;
    numElements=rhs.numElements;
  }
  return *this;
}
const int & IntArray::operator[](int index) const {
  assert(index<numElements);
  const int &a=data[index];
  return a;
}
int & IntArray::operator[](int index) {
  assert(index<numElements);
  int &a=data[index];
  return a;
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  bool a;
  if(numElements==0 && rhs.numElements==0){
    return true;
  }
  if(numElements==rhs.numElements){
    for(int i=0;i<numElements;i++){
      if(data[i]!=rhs.data[i]){
	a =false;
	break;
      }
      a=true;
    }
    return a;
  }
  return false;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  bool a;
  if(numElements==0 && rhs.numElements==0){
    return false;
  }
  if(numElements==rhs.numElements){
    for(int i=0;i<numElements;i++){
      if(data[i]!=rhs.data[i]){
        a=true;
	break;
      }
      a=false;
    }
    return a;
  }
  return true;
}

/*IntArray IntArray::operator+(const IntArray &rhs) const {
  assert(numElements==rhs.numElements);
  if(this->size()==0){
    return *this;
  }
  IntArray sum(numElements);
  for(int i=0;i<numElements;i++){
    sum.data[i]=data[i]+rhs.data[i];
  }
  return sum;
  }*/
std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  if(rhs.size()==0){
    s << "{"<<"}";
    return s;
  }
  s << "{";
  for(int i=0;i<rhs.size()-1;i++){
    s << rhs[i]<<", ";
  }
  s<<rhs[rhs.size()-1]<<"}";
  return s;
}
