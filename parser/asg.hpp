#ifndef ASG_HPP
#define ASG_HPP

#include <llvm/Support/JSON.h>
#include <vector>
#include <string>
#include <memory>
#include "ToJson.hpp"

class Mgr : public std::vector<std::unique_ptr<Obj>> {
  public:
  //  第三个参数用于静态检查参数是否正确，也可以省略。
  template<typename T,
  typename ... Args,
  typename std::enable_if<std::is_constructible<T, Args...>::value>::type>
  T* make(Args ... args)
  {
    auto ptr = std::make_unique<T>(args);
    auto obj = ptr.get();
    emplace_back(std::move(ptr));
    return obj;
  }

  ~Mgr(){
    for(int i = 0; i < size(); i++){
      at(i);
    }
  }
};

struct Type {
enum{my_int, my_float, my_longlong, my_double, my_char, my_string} my_type;
};


struct Obj {
virtual ~Obj() = default;
virtual void accept(ToJson& visitor) = 0;
};

struct Decl : public Obj { 
std::string name; 
Type type; 
void accept(ToJson & visitor) override {
    visitor(this);
}
};

struct Expr : public Obj {
Type type;
void accept(ToJson & visitor) override {
    visitor(this);
}
};

struct IntegerLiteral : public Expr {
std::int64_t val;
void accept(ToJson & visitor) override {
    visitor(this);
}
};

struct DeclRefExpr : public Expr {
Decl* decl; 
void accept(ToJson & visitor) override {
    visitor(this);
}
};

struct BinaryExpr : public Expr {
enum { kAdd, kSub, kMul, kDiv } op; 
Expr *lft, *rht;
void accept(ToJson & visitor) override {
    visitor(this);
}
};

#endif // ASG_HPP
