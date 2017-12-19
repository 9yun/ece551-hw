#include "IntMatrix.h"

IntMatrix::IntMatrix(){
  numRows=0;
  numColumns=0;
  rows=NULL;
}
IntMatrix::IntMatrix(int r, int c) :numRows(r),numColumns(c),rows(NULL){
  if(r > 0){
  numRows=r;
  numColumns=c;
  rows = new IntArray* [r];
  for(int i=0;i<r;i++){
    rows[i]=new IntArray(c);
  }
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  if(rhs.numRows>0){
  rows= new IntArray* [rhs.numRows];
  for(int i=0;i<rhs.numRows;i++){
    //why not *rows[i]=*rhs.rows[i]?
    //or *rows[i](*rhs.rows[i])?
    rows[i]= new IntArray(*(rhs.rows[i]));
  }
  numRows=rhs.numRows;
  numColumns=rhs.numColumns;
  }
  if(rhs.numRows==0){
    rows=NULL;
    numRows=0;
    numColumns=rhs.numColumns;
  }
  
  
}
IntMatrix::~IntMatrix() {
  for(int i=0;i<numRows;i++){
    delete rows[i];
  }
  delete []rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if(this!=&rhs){
    if(rhs.rows==NULL || rhs.numRows==0){
      for(int i=0;i<numRows;i++){
      delete rows[i];
      }
      delete []rows;
      rows=NULL;
      numRows=0;
      numColumns=rhs.numColumns;
      return *this;
    }
    
    IntArray **temp=new IntArray* [rhs.numRows];
    for(int i=0; i<rhs.numRows;i++){
      //why not *temp[i]=*rhs.rows[i]?
      temp[i]=new IntArray(*(rhs.rows[i]));
    }
    for(int i=0;i<numRows;i++){
      delete rows[i];
    }
    delete []rows;
    rows=temp;
    numRows=rhs.numRows;
    numColumns=rhs.numColumns;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(index < numRows && index >=0);
  return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(rows==NULL && rhs.rows==NULL){
    return true;
  }
  if(numRows==0 && rhs.numRows==0 && numColumns==rhs.numColumns){
    return true;
  }
  if(numRows==rhs.numRows && numColumns==0 && rhs.numColumns==0){
    return true;
  }

  if(numRows==rhs.numRows && numColumns==rhs.numColumns){
    for(int i=0;i<numRows;i++){
      if(*rows[i]!=*rhs.rows[i]){
	return false;
      }
    }
    
    return true;
  }
    else {return false;}
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows==rhs.numRows);
  assert(numColumns==rhs.numColumns);
  IntMatrix sum(numRows,numColumns);
  if(rows==NULL || numRows==0 || numColumns==0){
    sum=rhs;
  }
  
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      (*sum.rows[i])[j]=(*rows[i])[j]+(*rhs.rows[i])[j];
    } 
  }
  return sum;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if(rhs.getRows()==0){
    s<<"[ "<<" ]";
    return s;
  }
  s<<"[ ";
  //int a=rhs.getColumns();
  for(int i=0;i<rhs.getRows()-1;i++){
    s<<rhs[i];
    s<<",\n";
  }
  s<<rhs[rhs.getRows()-1];
  s<<" ]";
  return s;
}
