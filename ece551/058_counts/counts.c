#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t *counts=malloc(sizeof(*counts));
  counts->known=NULL;
  counts->size_unknown=0;
  counts->size=0;
  return counts;
}


void addCount(counts_t * c, const char * name) {
  if(name==NULL){
    c->size_unknown++;
  }
  else{
    int match=1;
    for(int i=0;i<c->size;i++){
      if(strcmp(name,c->known[i].string)==0){
	c->known[i].count++;
	match=0;
      }
      else{}
    }
    if(match==0){}
    else{
      c->known=realloc(c->known,(c->size+1)*sizeof(*(c->known)));
      c->size++;
      c->known[c->size-1].count=1;
      c->known[c->size-1].string=malloc((strlen(name)+1)*sizeof(*(c->known[c->size-1].string)));
      strcpy(c->known[c->size-1].string,name);
    }
  }
}


void printCounts(counts_t * c, FILE * outFile) {
  for(size_t i=0;i<c->size;i++){
    fprintf(outFile,"%s: %d\n",c->known[i].string,c->known[i].count);
  }
  if(c->size_unknown==0){}
  else{
    fprintf(outFile,"<unknown> : %d\n",c->size_unknown);
  }
}

void freeCounts(counts_t * c) {
  for(size_t i=0;i<c->size;i++){
    free(c->known[i].string);
  }
  free(c->known);
  free(c);
}
