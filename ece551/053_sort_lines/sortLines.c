#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}


char ** read_file(FILE *f,size_t *p){
  char **lines=NULL;
  char *curr=NULL;
  size_t sz;
  while(getline(&curr,&sz,f)>=0){
    lines=realloc(lines,(*p+1)*sizeof(lines));
    lines[*p]=curr;
    curr=NULL;
    *p=*p+1;
  }
  // printf("%zu\n",*p);
  free(curr);
  return lines;
}

void  print_file(char **lines,size_t num){
  for(size_t i=0;i<num;i++){
    fprintf(stdout,"%s\n",lines[i]);
    free(lines[i]);
  }
  free(lines);
} 

int main(int argc, char ** argv) {
  if(argc==1){
    char **lines=NULL;
    size_t num=0;
    char *curr=NULL;
    size_t sz=0;
    while(getline(&curr,&sz,stdin)>=0){
      lines=realloc(lines,(num+1)*sizeof(*lines));
      lines[num]=curr;
      curr=NULL;
      num++;
    }
    // printf("%zu\n",num);
    if(num==0){
      fprintf(stderr,"no input.\n");
      exit(EXIT_FAILURE);
    }
    free(curr);
    sortData(lines,num);
    print_file(lines,num);
  }
  else{
  for(int j=1;j<argc;j++){
    FILE *f1=fopen(argv[j],"r");
    if(f1==NULL){
      fprintf(stderr,"no input file.\n");
      exit(EXIT_FAILURE);
    }
    char **line=NULL;
    size_t nums=0;
    line=read_file(f1,&nums);
    sortData(line,nums);
    print_file(line,nums);
    if(nums==0){
      fprintf(stderr,"file no input.\n");
      exit(EXIT_FAILURE);
    }
    // printf("%zu\n",nums);
    if(fclose(f1)!=0){
      exit(EXIT_FAILURE);
    }
  }
  }
  return EXIT_SUCCESS;
}
