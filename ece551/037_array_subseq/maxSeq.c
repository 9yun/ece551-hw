#include<stdio.h>
#include<stdlib.h>
size_t max(size_t n,size_t m){
  if(n>=m){
    return n;
  }
  else{return m;}
}
 size_t maxSeq(int *array,size_t n){
   size_t size=1;
   size_t size_now=1;
   if(n<=0){
     size=0;
     return size;
   }   
   else if(n==1){
     return size;
   }
   else{
     for(int i=0;i<n-1;i++){
       if(array[i]<array[i+1]){
       size_now++;
       size=max(size,size_now);
        }
       else{
	 size=max(size,size_now);
	 size_now=1;
       }
     }
     return size;
   }
 }
