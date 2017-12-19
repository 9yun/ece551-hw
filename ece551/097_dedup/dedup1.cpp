#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<time.h>
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<queue>
#include<stdexcept>
#include<functional>
#include<unordered_map>




//flit the . and .. directory
bool isfliter(const char * dirname){
  std::string temp(dirname);
  if(temp.length()==1 && temp[0]=='.'){
    return true;
  }
  if(temp.length()==2 && temp[0]=='.' && temp[1]=='.'){
    return true;
  }
  return false;
}
//is the dirname represent a dir
bool isdir(const char * dirname){
  struct stat dir;
  if(lstat(dirname,&dir)==-1){
    //throw exception
  }
  if(S_ISDIR(dir.st_mode)){
    return true;
  }
  else{
    return false;
  }
}
//transfer const char * to char * remember to delete temp after used it
std::string updatepath(std::string dirname,const char * filename){
  std::string src2("/");
  std::string src3(filename);
  std::string dest=dirname+src2+src3;
  return dest;
}
//open a directory , divide sub dir and file, update path and store sub dir into queue for next opendirectory
void opendirectory(std::string dirname, std::vector<std::string> * files){
  DIR * dir;
  struct dirent * ptr=NULL;// char[] d_name
  std::queue<std::string> store;
  store.push(dirname);
  while(!store.empty()){
    std::string nd=store.front();
    dir = opendir(nd.c_str());
    store.pop();
    while((ptr = readdir(dir))!=NULL){
      if(!isfliter(ptr->d_name)){
	std::string temp = updatepath(nd,ptr->d_name);
	//std::cout << ptr->d_name << "\n";
	if(isdir(temp.c_str())){
	  store.push(temp);
	}
	else{
	  (*files).push_back(temp);
	}
      }
    }
    free(dir);
  }
}



std::string openfile(std::string filename){
  std::ifstream ifs(filename.c_str(),std::ifstream::in);
  std::ostringstream buf;
  char ch;
  if(ifs.is_open()){
    while(buf&&ifs.get(ch)){
      buf.put(ch);
    }
  }
  else{
  }
  ifs.close();
  return buf.str();
}

typedef std::unordered_map<std::string,std::string> stringmap;
int main(int argc,char* argv[]){
  stringmap filemap;//content:filename
  std::vector<std::string> files;
  for(int i=1;i<argc;i++){

    opendirectory(argv[i],&files);

  }//  std::cout<<files.size()<<std::endl;
  std::cout<<"#!/bin/bash"<<std::endl;
  while(!files.empty()){
    std::string filepath=files.back();
    files.pop_back();
    //std::cout<<filepath<<std::endl;
    std::string content=openfile(filepath);
    stringmap::const_iterator got = filemap.find(content);
    if(got != filemap.end()){
      std::cout<<"#Removing "<<filepath<<" (duplicate of "<<got->second<<")."<<std::endl<<"rm "<<filepath<<std::endl;
    }
    else{
      filemap.insert({content,filepath});
    }
  }
  //std::cout<<filemap.size()<<std::endl;
}
