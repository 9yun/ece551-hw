#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

template<typename T> class Matrix;
template<typename T> std::ostream & operator <<(std::ostream &s,const Matrix<T> &rhs);
template<typename T>
class Matrix{
 private:
  int numRows;
  int numColumns;
  std::vector<T> **rows;
 public:
 Matrix():numRows(0),numColumns(0),rows(NULL){
  }
 Matrix(int r,int c):numRows(r),numColumns(c),rows(NULL){
    if(r>0){
      rows = new std::vector<T>* [r];
      for(int i=0;i<r;i++){
	rows[i] = new std::vector<T> (c);
      }
    }
  }
 Matrix(const Matrix & rhs):numRows(rhs.numRows),numColumns(rhs.numColumns),rows(NULL){
     if(rhs.numRows>0){
       rows= new std::vector<T>* [rhs.numRows];
       for(int i=0;i<rhs.numRows;i++) {
	 rows[i]=new std::vector<T>(*rhs.rows[i]);
       }
       
     }
   }
   ~Matrix(){
     for(int i=0;i<numRows;i++){
       delete rows[i];
     }
     delete []rows;
   }
   Matrix & operator=(const Matrix &rhs){
     if(this!=&rhs){
       if(rhs.rows==NULL){
	 for(int i=0;i<numRows;i++){
	   delete rows[i];
	 }
	 delete []rows;
	 rows=NULL;
	 numRows=0;
	 numColumns=rhs.numColumns;
       }
       std::vector<T> **temp = new std::vector<T>* [rhs.numRows];
       for(int i=0;i<rhs.numRows;i++){
	 temp[i]=new std::vector<T>(*rhs.rows[i]);
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
   int getRows() const{
     return numRows;
   }
   int getColumns() const{
     return numColumns;
   }
   const std::vector<T> &operator[](int index) const{
     assert(index >=0 && index < numRows);
     return *rows[index];
   }
   std::vector<T> & operator[](int index) {
     assert(index < numRows && index >=0);
     return *rows[index];
   }
   bool operator==(const Matrix<T> &rhs) const{
     if(rows==NULL && rhs.rows==NULL){
       return true;
     }
     else if(numRows == rhs.numRows && numColumns == rhs.numColumns){
       for(int i=0;i<numRows;i++){
	 if(*rows[i]!=*rhs.rows[i]){
	   return false;
	 }
       }
       return true;
     }
     else{return false;}
   }
   Matrix operator+(const Matrix & rhs) const{
     assert(numRows==rhs.numRows && numColumns==rhs.numColumns);
     Matrix sum(numRows,numColumns);
     if(rows==NULL){
       sum=*this;
     }
     for(int i=0;i<numRows;i++){
       for(int j=0;j<numColumns;j++){
	 (sum[i])[j]=(*rows[i])[j]+(rhs[i])[j];
       }
     }
     return sum;
   }
   template<typename X> friend std::ostream & operator <<(std::ostream &s,const Matrix<X> &rhs);
};


template<typename T>
std::ostream &operator<<(std::ostream &s,const Matrix <T> &rhs){
  if(rhs.getRows()==0){
    s<<"[ "<<" ]";
    return s;
  }
  s<<"[ ";
  if(rhs.getColumns()==0){
    for(int i=0;i<rhs.getRows()-1;i++){
      s<<"{"<<"}"<<"\n";
    }
    s<<"{"<<"}"<<" ]";
    return s;
  }
  for(int i=0;i<rhs.getRows()-1;i++){
   
      s<<"{";
      for(int j=0;j<rhs.getColumns()-1;j++){
	s<<rhs[i][j]<<", ";
      }
      s<<rhs[i][rhs.getColumns()-1]<<"},"<<"\n";
    }
  s<<"{";
  for(int i=0;i<rhs.getColumns()-1;i++){
    s<<rhs[rhs.getRows()-1][i]<<", ";
  }
  s<<rhs[rhs.getRows()-1][rhs.getColumns()-1]<<"}";
  s<<" ]";
  return s;
}
#endif
