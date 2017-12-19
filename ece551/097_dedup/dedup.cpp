#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<unordered_map>
#include<fstream>
#include<sstream>
#include<iterator>
#include<string>
#include<vector>
#include <experimental/filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

typedef std::unordered_map<std::string,std::string> stringmap;
//typedef std::unordered_map<size_t,std::string> keymap;
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

void read_file(stringmap* m,std::string filename){
  //std::cout << "test\n";
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
  std::string content = buf.str();
  //std::cout << content << "\n";
  stringmap::const_iterator found = m->find(content);
  if(found != m->end()){
      std::cout<<"#Removing "<<filename<<" (duplicate of "<<found->second<<")."<<std::endl<<"rm "<<filename<<std::endl;
    }
    else{
      m->insert({content,filename});
    }
    //std::cout << (*m).size() << "\n";
}


void traverse_file( stringmap* m,char *path){
  DIR *p;
  struct dirent *ent;
  p = opendir(path);
  char childpath[512];
  char file_path[512];
  if(p != NULL){
    //std::cout << "test\n";
    while((ent = readdir(p))!=NULL){
      if(!isfliter(ent->d_name)){
	if(ent->d_type & DT_DIR){
	  sprintf(childpath,"%s/%s",path,ent->d_name);
	  traverse_file(m,childpath);
	}
	else{  //std::cout << "test\n";
	  std::string filename(ent->d_name); 
	  sprintf(file_path,"%s/%s",path,ent->d_name);
	  std::string filepath(file_path);
	  //std::cout << filepath << "\n";
	  //m->push_back(filepath);
	  read_file(m,filepath);
	}
      }
    }
  }
  closedir(p);
  //std::cout << "test\n";
}
  /* namespace fs = std::experimental::filesystem;
  if(fs::exists(path)){
    std::vector<std::string > filename;
    fs::directory_iterator it(path), end;
    for(;it!=end;++it){
      if(fs::is_directory(it->path())){
	traverse_file(m,it->path());
      }
      if(fs::is_regular_file(*it)){
	filename.push_back(it->path().string());
      }
    }
    for(std::vector<std::string>::iterator it = filename.begin();it!=filename.end();++it){
      read_file(m,*it);
    }
  }*/
  /*
  std::vector<std::string> filenames;
  WIN32 _FIND_DATA info;
  std::string curr = path + "*.*";
  HANDLE ha = FindFirstFile(curr.c_str(),&info);
  if(ha != INVALID_HANDLE_VALUE){
    do{   
      if(info.attrib == _A_SUBDIR){
	tranverse_file(m,path);
      }
      if(info.attrib == _A_NORMAL){
	std::string temp(info.name);
	filnames.push_back(temp);
      }
    }while(!FindNextFile(handle,&info));
  }
  _findclose(handle);
  */
  



int main(int argc, char **argv){
  if(argc < 1){
    std::cout << "no input.\n";
  }
  //std::string t("test\n");
  std::cout << "#!/bin/bash\n";
  //stringmap files;
  //std::vector<std::string> file_names;
  for(int i=1;i<argc;i++){
    //std::cout << t;
    stringmap m;
    traverse_file(&m,argv[i]);
  }
  return EXIT_SUCCESS;
}
  /* std::cout<<"#!/bin/bash"<<std::endl;
  while(!file_names.empty()){
    std::string file_name = file_names.back();
    std::string content = read_file(file_name);
    stringmap::const_iterator found = files.find(content);
    if(found != files.end()){
      std::cout<<"#Removing "<<file_name<<" (duplicate of "<<found->second<<")."<<std::endl<<"rm "<<file_name<<std::endl;
    }
    else{
      files.insert({content,file_name});
    }
  }
  return EXIT_SUCCESS;
  }*/
