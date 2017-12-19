#include<stdexcept>
#include<iostream>
#include"bstset.h"
#include<cstdio>
#include<cstdlib>


int main(){
  BstSet<int> m;
  //std::cout << "wrong here.\n";
  m.add(6);
  //std::cout << "wrong here.\n";
  m.add(4);
  m.add(5);
  m.add(3);
  m.add(2);
  m.add(1);
  m.print();
  m.remove(4);
  m.contains(4);
  m.contains(2);
  m.print();
  BstSet<int> n(m);
  n.print();
  BstSet<int> a;
  a = m;
  a.print();
  n.add(6);
  a = n;
  a.print();
}
