#include "election.h"
#include<stdlib.h>
#include<stdio.h>

//include any other headers you need here...
int power(int a,int b){
  int c=1;
  if(b==0){
    return c;
  }
  for(int i=1;i<=b;i++){
    c=a*c;
  }
  return c;
}


state_t parseLine(const char * line) {
  state_t states;
  for(int i=0; i<MAX_STATE_NAME_LENGTH;i++){
    states.name[i] = 0;
  }
    int i=0;
    while(line[i]!=':'){
      if(line[i]=='\0'){
	fprintf(stderr,"format wrong.\n");
	exit(EXIT_FAILURE);
      }
      states.name[i]=line[i];
      i++;
    }
    states.name[i]='\0';
    int j=i+1;
    while(line[j]!=':'){
      if(line[j]=='\0'){
	fprintf(stderr,"format wrong.\n");
	exit(EXIT_FAILURE);
      }
      j++;
    }
    char pop[j-i];
    for(int a=i+1;a<j;a++){
      pop[a-i-1]=line[a];
    }
    pop[j-i]='\0';
    uint64_t curr=0;
    for(int a=0;a<j-i-1;a++){
      if((pop[a]>'9')||(pop[a]<'0')==1){
	fprintf(stderr,"format wrong.\n");
	exit(EXIT_FAILURE);
      }
      curr+= power(10,j-a-i-2)*(pop[a]-48);
  }
    states.population=curr;
    unsigned int vote=0;
    int k=j+1;
    while(line[k]!='\0'){
      if(line[k]==':'){
	fprintf(stderr,"format wrong.\n");
	exit(EXIT_FAILURE);
      }
      k++;
    }
    if(line[k-1]=='\n'){
      fprintf(stderr,"format is wrong.\n");
  }
    char elec[k-j];
    for(int b=j+1;b<k;b++){
      elec[b-j-1]=line[b];
  }
    elec[k-j]='\0';
    for(int b=0;b<k-j-1;b++){
      if((elec[b]>'9')||(elec[b]<'0')==1){
	fprintf(stderr,"format wrong.\n");
	exit(EXIT_FAILURE);
      }
      vote+=power(10,k-j-b-2)*(elec[b]-48);
  }
    states.electoralVotes=vote;
    return states;
}
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  unsigned int sum=0;
  for(int i=0;i<nStates;i++){
    if((stateData[i].population)<(voteCounts[i]*2)){
      sum+=stateData[i].electoralVotes;
    }
  }
  return sum;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  double portion=0;
  for(size_t i=0;i<nStates;i++){
    portion=voteCounts[i]/(double)stateData[i].population;
    portion=portion*100;
    if((portion>=49.50)&&(portion<=50.50)==1){
      fprintf(stdout,"%s requires a recount (Candidate A has %.2f%% of the vote)\n",stateData[i].name,portion);
    }
  }
}  
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  double largest=0;
  state_t *p=&stateData[0];
  double portion=0;
  for(int i=0;i<nStates;i++){
    portion=voteCounts[i]/(double)stateData[i].population;
    portion=portion*100;
    if(largest<portion){
      largest=portion;
      p=&stateData[i];
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n",p->name,largest);
}
