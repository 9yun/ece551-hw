#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

int fre_highest(FILE *f){
  int c;
  int max=0;
  int num[26]={0};
  while((c=fgetc(f))!=EOF){
    if(isalpha(c)){
      c=tolower(c);
      c=c-'a';
      num[c]++;
    }
  }
  for(int i=1;i<26;i++){
    if(num[max]<num[i]){
      max=i;
    }
    else{
    }
  }
  if(num[max]==0){
    fprintf(stderr,"input file no character.\n");
    exit(EXIT_FAILURE);
  }
  return max+97;
}
int breaker(int a){
  int key;
  a=a-'e';
  if(a<0){
    a=a+26;
    key=a;
    return key;
  }
  else{
    key=a;
    return key;
  }
}
int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"invalid input number %d!\n",argc);
    exit(EXIT_FAILURE);
  }
  int a;
  int key;
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"cannot open file.\n");
    exit(EXIT_FAILURE);
  }
  a=fre_highest(f);
  key=breaker(a);
  fprintf(stdout,"%d\n",key);
  if(fclose(f)!=0){
    perror("cannot close file.\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
