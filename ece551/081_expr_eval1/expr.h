#include<string.h>
#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<sstream>
#include<stdio.h>

class Expression{
 public:
  //Expression(std::string give):exp(give){}
  virtual std::string toString() const=0;
  virtual ~Expression(){}
  virtual long evaluate() const =0;
  //virtual long getNum() const =0;
};


class NumExpression: public Expression{
 public:
  double num;
 NumExpression(long giveNum):num(giveNum){}
  virtual std::string toString() const{
    std::stringstream stream;
    std::string result;
    stream << num;
    stream >> result;
    return result;
  }
  //long getNum() const{
  //return num;
  virtual ~NumExpression(){}
  virtual long evaluate() const{
    return num;
  }
};

class ope_exp:public Expression{
 protected:
  Expression *left;
  Expression *right;
 public:
 ope_exp(Expression * lhs,Expression * rhs):left(lhs),right(rhs){}
  virtual ~ope_exp(){
    delete left;
    delete right;
  }
  virtual std::string ope_dec() const =0;
  virtual std::string toString() const {
    std::string infix;
    infix.push_back('(');
    infix+=left->toString();
    //infix+=ope_dec();
    infix+=right->toString();
    infix.push_back(')');
    return infix;
  }
  
  //long string 
};
class PlusExpression: public ope_exp{
 public:
 PlusExpression(Expression *lhs,Expression *rhs): ope_exp(lhs,rhs){}
  virtual std::string ope_dec() const{
    std::string ope;
    ope+=" + ";
    return ope;
  }
  virtual std::string toString() const{
    std::string plus=ope_exp::toString();
    size_t n= left->toString().size();
    plus.insert(n+1,ope_dec());
    return plus;
  }
  virtual long evaluate() const{
    return left->evaluate()+right->evaluate();
  }
};

class MinusExpression: public ope_exp{
 public:
 MinusExpression(Expression *lhs,Expression *rhs):ope_exp(lhs,rhs){}
  virtual std::string ope_dec() const {
    std::string ope;
    ope+=" - ";
    return ope;
  }
  virtual std::string toString() const{
    std::string minus=ope_exp::toString();
    size_t n=left->toString().size();
    minus.insert(n+1,ope_dec());
    return minus;
  }
  virtual long evaluate() const{
    return left->evaluate()-right->evaluate();
  }
};

class TimesExpression: public ope_exp{
 public:
 TimesExpression(Expression *lhs,Expression *rhs):ope_exp(lhs,rhs){}
  virtual std::string ope_dec() const{
    std::string ope;
    ope+=" * ";
    return ope;
  }
  virtual std::string toString() const{
    std::string mul=ope_exp::toString();
    size_t n=left->toString().size();
    mul.insert(n+1,ope_dec());
    return mul;
  }
  virtual long evaluate() const{
    return left->evaluate()*right->evaluate();
  }
};

class DivExpression : public ope_exp{
 public:
 DivExpression(Expression *lhs,Expression *rhs):ope_exp(lhs,rhs){}
  
  virtual std::string ope_dec() const {
    std::string ope;
    ope+=" / ";
    return ope;
  }
  virtual std::string toString() const{
    std::string div=ope_exp::toString();
    size_t n=left->toString().size();
    div.insert(n+1,ope_dec());
    return div;
  }
  virtual long evaluate() const{
    //std::stringstream stream;
    return left->evaluate()/right->evaluate();
    
  }
};
