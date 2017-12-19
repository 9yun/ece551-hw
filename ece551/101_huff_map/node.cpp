#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  if(sym != NO_SYM){
    assert(left == NULL && right == NULL);
    theMap.insert(std::pair<unsigned,BitString>(sym,b));
  }
  else{
    std::map<unsigned,BitString> *m = &theMap;
    BitString l = (b.plusZero());    
    left->buildMap(l,*m);
    BitString r = (b.plusOne());
    right->buildMap(r,*m);
  }
}

