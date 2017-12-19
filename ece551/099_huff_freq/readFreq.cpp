#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <vector>
#include <iostream>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}


uint64_t * readFrequencies(const char * fname) {
  FILE *f = fopen(fname,"r");
  int size_arr = 257;
  uint64_t *fre_arr = new uint64_t[size_arr];
  for(int i=0;i<size_arr;i++){
    fre_arr[i]=0;
  }
  
  int c;
  
  while((c=fgetc(f))!=EOF){
    for(int i=0;i<size_arr;i++){
      if(c == i){
	fre_arr[i] = fre_arr[i]+1;
      }
    }
  }
  fclose(f);
  fre_arr[256] = 1;
  return fre_arr;
}
