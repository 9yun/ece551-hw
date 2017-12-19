#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<iterator>
#include<string>
int main(int argc, char** argv){
  if(argc < 1){
    perror("no input.\n");
    return EXIT_FAILURE;
  }
  else if(argc == 1){
    std::vector<std::string> cinArray;
    //std::string cin_str;
    //if(std::cin.eof()){
    std::string cin_temp;
    while(getline(std::cin,cin_temp)){
      //std::cin.getline(cin_str,100);
      cinArray.push_back(cin_temp);
    }
    std::sort(cinArray.begin(),cinArray.end());
    //std::cout<<"\n";
    for(std::vector<std::string>::iterator it=cinArray.begin();it!=cinArray.end();++it){
      std::cout << *it << "\n";
    }
  }
  else {
  for(int i=1;i<argc;i++){
    std::ifstream readFile(argv[i]);
    std::vector<std::string> strArray;
    std::string temp;
    if(readFile.is_open()){
      if(readFile.good()){
	while(getline(readFile,temp)){
	  strArray.push_back(temp);
	}
      }
      else{
	perror("file is null.\n");
	return EXIT_FAILURE;
      }
      readFile.close();
    }
    else{
      perror("cannot open file.\n");
      return EXIT_FAILURE;
    }
    
    std::sort(strArray.begin(),strArray.end());
    for(std::vector<std::string>::iterator it =strArray.begin();it!=strArray.end();++it){
      std::cout<<*it<<"\n";
    }
  }
  return EXIT_SUCCESS;
  }
}
