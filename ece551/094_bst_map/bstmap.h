#include<cstdlib>
#include<stdexcept>
#include"map.h"
#include<iostream>

template<typename K, typename V>
  class BstMap:public Map<K,V>{
 private:
  class Node{
  public:
    Node *left;
    Node *right;
    K k;
    V v;
  Node():left(NULL),right(NULL){}
  Node(Node *l, Node *r, K k1, V v1):left(l),right(r),k(k1),v(v1){}
  };
  Node *root;
 public:
 
  virtual const V & lookup(const K& key)  const throw(std::invalid_argument){
    Node *temp = root;
    Node **curr = &temp;
    while(*curr != NULL){
      if(key == (*curr)->k){
	return (*curr)->v; 
      }
      else if(key < (*curr)->k){
	curr = &(*curr)->left;
      }
      else{
	curr = &(*curr)->right;
      }
    }
    //std::cout << "wrong here.\n";
    throw std::invalid_argument("No key found.\n");
  }
  virtual void add(const K & key, const V & value){
    Node **curr = &root;
    while(*curr != NULL){
      if(key == (*curr)->k){
	(*curr)->v = value;
	break;
      }
      else if(key < (*curr)->k){
	curr = &(*curr)->left;
      }
      else{
	curr = &(*curr)->right;
      }
    }
    if(*curr == NULL){
      *curr = new Node(NULL,NULL,key,value);
    }
  }
  /*virtual void remove(const K& key){
    Node **curr = &root;
    while(*curr != NULL){
      if(key == (*curr)->k){
	break;
      }
      else if(key < (*curr)->k){
	curr = &(*curr)->left; 
      }
      else{
	curr = &(*curr)->right;
      }
    }
    //std::cout << (*curr)->k;
    if(*curr != NULL){
      remove_help(curr);
    }
    }*/
  virtual void remove(const K& key){
    remove_help(&root,key);
  }

  void remove_help(Node **ans,const K& key){
    if(*ans != NULL){
      if((*ans)->k > key){
	remove_help(&(*ans)->left,key);
      }
      else if((*ans)->k < key){
	remove_help(&(*ans)->right,key);
      }
      else{
	deleteNode(ans);
      }
    }
  }
  void deleteNode(Node **curr){
    Node *temp = *curr;
    if((*curr)->left == NULL){
      *curr = (*curr)->right;
      delete temp;
    }
    else if((*curr)->right == NULL){
      *curr = (*curr)->left;
      delete temp;
    }
    else{
      
      temp = find_leftRightMost(*curr);
      
      (*curr)->k = temp->k;
      
      (*curr)->v = temp->v;
      
      remove_help(&(*curr)->left,temp->k);
    }
  }
  Node* find_leftRightMost(Node* ans){
    ans = ans->left;
    while(ans -> right != NULL){
      ans = ans->right;
    }
    //std::cout << ans ;
    return ans;
  }
 BstMap():root(NULL){}
 BstMap(const BstMap &rhs){
   root = NULL;
   constructor_help(rhs.root);  
 }
  BstMap & operator = (const BstMap &rhs){
    if(this != &rhs){
      BstMap temp(rhs);
      destructor_help(root);
      root = NULL;
      root = temp.root;
      temp.root = NULL;
    }
    return *this;
  }
  void constructor_help(Node *curr){
    if(curr != NULL){
      add(curr->k,curr->v);
      //     std::cout << (curr)->k;
      //std::cout << "wrong\n";
      constructor_help(curr->left);
      constructor_help(curr->right);
    }
  }
  ~BstMap<K,V>(){
    destructor_help(root);
    root = NULL;
  }
 void destructor_help(Node *curr){
    if(curr != NULL){
      destructor_help(curr->left);
      destructor_help(curr->right);
      delete curr;
    }
  }
 void print(){
   print_help(root);
 }
 void print_help(Node *curr){
   if(curr != NULL){
     // std::cout << "test\n";
     std::cout << curr->k << " " << curr->v << "\n";
     print_help(curr->left);
     print_help(curr->right);
   }
 }
};

