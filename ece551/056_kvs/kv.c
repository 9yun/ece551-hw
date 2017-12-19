#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvpair_t *split(kvpair_t *array1,char **curr,size_t length){
  for(int i=0;i<length;i++){
    int j=0;
    while(curr[i][j]!='='){
      /* if(curr[i][j]=='\0'){
	fprintf(stderr,"wrong1.\n");
	exit(EXIT_FAILURE);
	}*/
      j++;
    }
    if(j==0){
      fprintf(stderr,"wrong2.\n");
      exit(EXIT_FAILURE);
    }
    array1[i].key=malloc((j+1)*sizeof(*(array1[i].key)));
    for(int a=0;a<j;a++){
      array1[i].key[a]=curr[i][a];
    }
    array1[i].key[j]='\0';
    int k=j+1;
    while(curr[i][k]!='\n'){
      k++;
    }
    if(k==j+1){
      fprintf(stderr,"wrong3.\n");
    }
    array1[i].value=malloc((k-j)*sizeof(*(array1->value)));
    for(int a=0;a<k-j-1;a++){
      array1[i].value[a]=curr[i][a+j+1];
    }
    array1[i].value[k-j-1]='\0';
  }
  return array1;
}


kvarray_t * add(kvarray_t *array,kvpair_t *array1,size_t length){
  array->pair=array1;
  array->length=length;
  return array;
}



kvarray_t * readKVs(const char * fname) {
  FILE *f=fopen(fname,"r");
  if(f==NULL){
    fprintf(stderr,"cannot open file.\n");
    exit(EXIT_FAILURE);
  }
  char **curr=NULL;
  char *line=NULL;
  size_t sz;
  size_t count=0;

  while(getline(&line,&sz,f)>=0){
    curr=realloc(curr,(count+1)*sizeof(*curr));
    curr[count]=line;
    line=NULL;
    count++;
  }
  free(line);
  kvarray_t *array=malloc(sizeof(*array));
  array->pair=NULL;
  array->length=count;
  //printf("%zu\n",length);
  kvpair_t *array1=malloc(array->length*sizeof(*array1));
  array1=split(array1,curr,array->length);
  for(int i=0;i<array->length;i++){
    free(curr[i]);
  }
  free(curr);
  array=add(array,array1,array->length);
  if(fclose(f)!=0){
    exit(EXIT_FAILURE);
  }
  return array;
}



void freeKVs(kvarray_t *pairs){
  for(int i=0;i<pairs->length;i++){
    free(pairs->pair[i].key);
    free(pairs->pair[i].value);
  }
  free(pairs->pair);
  free(pairs);
}



void printKVs(kvarray_t *pairs){
  for(int i=0;i<pairs->length;i++){
    printf("key = '%s' value = '%s'\n",pairs->pair[i].key,pairs->pair[i].value);
  }
}



char *lookupValue(kvarray_t *pairs, const char *key){
  if((pairs==NULL)||(key==NULL)){
    fprintf(stderr,"no input file.\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<(pairs->length);i++){
    int match=strcmp(pairs->pair[i].key,key);
    if(match==0){
      // printf("%s\n",pairs->pair[i].value);
      return pairs->pair[i].value;
    }
    else{}
  }
  //printf("no key is found.\n");
  return NULL;
}


