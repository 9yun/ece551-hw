#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void check_matrix(char example[10][10],int n,int m){
   if(m!=n*n+n){
   printf("m wrong!\n");
   exit(EXIT_FAILURE);
   }
    for(int i=0;i<n;i++){
    char *end=strchr(example[i],'\n');
    if(*end!='\n'){
      fprintf(stderr,"null wrong.\n");
      exit(EXIT_FAILURE);
    }
  }
  }


int main(int argc, char **argv){
  if(argc!=2){
    fprintf(stderr,"argc wrong.\n");
    exit(EXIT_FAILURE);
  }
  if(strcmp(argv[1]," ")==0){
    fprintf(stderr,"input wrong.\n");
    exit(EXIT_FAILURE);
  }
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"f wrong.\n");
    exit(EXIT_FAILURE);
  }
  char matrix[10][10];
  char rotate[10][10];
  int i,j,c,count;
  count=0;
  while((c=getc(f))!=EOF){
    i=count/11;
    j=count%11;
    matrix[i][j]=c;
    count++;
  }
  if((i!=9)||(j!=10)==1){
    fprintf(stderr,"line wrong!\n");
    exit(EXIT_FAILURE);
  }

  check_matrix(matrix,10,count);
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++){
      rotate[j][9-i]=matrix[i][j];
    }
  }
  for(int a=0;a<10;a++){
    for(int b=0;b<10;b++){
      if(b==9){
	fprintf(stdout,"%c\n",rotate[a][b]);
      }
      else{
	fprintf(stdout,"%c",rotate[a][b]);
      }
    }
  }
  if(fclose(f)!=0){
    printf("close wrong\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
