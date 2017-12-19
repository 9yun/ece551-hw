#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>

template<typename T>
class LinkedList{
  class Node{
  public:
    T data;
    Node *next;
    Node *prev;
  Node():next(NULL),prev(NULL){}
    explicit Node(T data1, Node*next1, Node*prev1):data(data1),next(next1),prev(prev1){}
    ~Node(){}
  };
  Node *head;
  Node *tail;
  int size;
  void empty_list(){
    head = NULL;
    tail = NULL;
    size = 0;
  }
 public:
  void addFront(const T &item){
    //head = new(item, head, NULL);
    //if(tail == NULL){
    //tail = head;
    // }
    //else{
    //head->next->prev = head->next;
    //}
    if(head==NULL){
      head=new Node(item,NULL,NULL);
      tail=head;
      size ++;
    }
    else{
      Node *temp=head;
      head=new Node(item,temp,NULL);
      temp->prev=head;
      size++;
    }
  }
  void addBack(const T &item){
    /*
      tail = new(item, NULL, tail);
      if(head =NULL){
      head = tail;
      }
      else{
      tail->prev->next = tail->prev;
      }
     */
    if(tail==NULL){
      tail=new Node(item,NULL,NULL);
      head = tail;
      size++;
    }
    else{
      Node *temp=tail;
      tail=new Node(item,NULL,temp);
      temp->next=tail;
      size++;
    }
  }
  //Node *remove_help(const T&item,Node *current)
  Node *find_help(const T &item){
    Node **curr = &head;
    if(head==NULL){
      return NULL;
    }
    while( (*curr)->data != item){
      curr = &(*curr)->next;
      if((*curr) == NULL){
	return NULL;
      }
    }
    return *curr;
  }
  bool remove(const T &item){
    Node *ans= find_help(item);
    if(ans == NULL){
      return false;
    }
    else{
      if(ans->prev == NULL && ans->next == NULL){
	/*tail = ans->prev;
	tail->next = NULL;
	delete ans;
	return true;*/
	head = NULL;
	tail = NULL;
	delete ans;
	size --;
	return true;
      }
      if(ans->prev == NULL){
	head = ans->next;
	head->prev = NULL;
	delete ans;
	size --;
	return true;
      }
      if(ans->next ==NULL){
	tail = ans->prev;
	tail->next = NULL;
	delete ans;
	size --;
	return true;
      }
      else{
	ans->prev->next = ans->next;
	ans->next->prev = ans->prev;
	delete ans;
	size --;
	return true;
      }
    }
  }
  T& operator[](int index){
    assert(index >=0 && index < size);
    if(head == NULL){
      throw std::out_of_range("No node exist.\n");
    }
    Node *temp = head;
    for(int i=0;i<index;i++){
      temp=temp->next;
    }
    return (temp)->data;
  }
  const T& operator[](int index) const{
    assert(index >= 0 && index < getSize());
    if(head == NULL){
      throw std::out_of_range("No node exist.\n");
    }
    const Node *temp=head;
    for(int i=0;i<index;i++){
      temp=(temp)->next;
    }
    return temp->data;
  } 
  int find(const T& item) {
    Node *ans = find_help(item);
    if(ans == NULL){
      return -1;
    }
    else{
      int index=0;
      while(ans != NULL){
	ans = ans->prev;
	index++;
      }
      return index-1;
    }
  }
  
 LinkedList():head(NULL),tail(NULL),size(0){}
 LinkedList(const LinkedList &rhs){
   tail = new Node(rhs.tail->data,NULL,NULL);
   head = tail;
   size = 1;
   Node *curr = rhs.tail->prev;
   while(curr != NULL){
     addFront(curr->data);
     curr = curr->prev;
   }
 }
  LinkedList& operator = (const LinkedList & rhs){
    if(this!=&rhs){
      LinkedList temp(rhs);
      while(head != NULL){
	Node *temp=head->next;
	delete head;
	head=temp;
      }
      head = NULL;
      tail = NULL;
      size = 0;
      head = temp.head;
      tail = temp.tail;
      temp.empty_list();
      size = rhs.size;
    }
    return *this;
  }
  ~LinkedList(){
    while(head != NULL){
      Node *temp=head->next;
      delete head;
      head=temp;
    }
    head = NULL;
    tail = NULL;
    size = 0;
  }
  int getSize() const {
    return size;
  }
};


#endif
