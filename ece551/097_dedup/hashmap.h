#include<iostream>
#include<functional>
#include<cstdlib>
#include<string>
#include<utility>
#include<vector>
#include<list>

template<typename K, typename V>
  class HashMap{
 private:
  std::vector<std::list<std::pair<K,V > > >* table;
 public:
  void add(const K& key,const V& value){
    std::hash<K> key_hash;
    //std::cout << key;
    size_t h = key_hash(key);
    //std::cout << h;
    h = h % table->size();
    //std::cout << h;
    removeFile(value, &(*table)[h]);
    //std::cout << (*table)[h].size();
    (*table)[h].push_front(std::pair<K,V>(key,value));
  }
  
 HashMap():table(NULL){
    std::list<std::pair<K,V > > temp;
    table = new std::vector<std::list<std::pair<K,V > > >(49999,temp);
  }
  ~HashMap(){
    delete table;
  }
 HashMap(const HashMap& rhs):table(NULL){
    std::list<std::pair<K,V > > temp;
    table = new std::vector<std::list<std::pair<K,V > > >(49999,temp);
  }
  
  void removeFile(const V& value, std::list<std::pair<K,V> > *li){
    //std::cout << li->size();;
    if(li->size()>0){
      std::cout << "#Removing " << std::get<1>(li->front()) << " (duplicate of " << value <<  ").";
      std::cout << "\n" << "\n" << "rm " << std::get<1>(li->front()) <<"\n"<<"\n";
      /*while(!li->empty()){
      li->pop_front();
      }*/
      li->pop_front();
      //std::cout << li.size();
    }
  }
};
