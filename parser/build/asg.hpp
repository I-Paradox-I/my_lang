#ifndef ASG_HPP
#define ASG_HPP

#include <llvm/Support/JSON.h>
#include <llvm/ADT/APFloat.h>
#include <vector>
#include <string>
#include <memory>
#include <any>

struct Type {
enum{IntegerLiteral, FloatingLiteral} type_;
};


struct Obj {
virtual ~Obj() = default;
};

struct Decl : public Obj { 
Type type; 
std::string name; 
};

struct Expr : public Obj {
Type type;
};


struct IntegerLiteral : public Expr {
    std::string kind = "IntegerLiteral";
    std::string value;
    std::int64_t val;
    // IntegerLiteral(std::string value, std::int64_t val, std::string kind = "IntegerLiteral"):kind(kind), value(value), val(val) {}

};

struct FloatingLiteral : public Expr {
    std::string kind = "FloatingLiteral";
    std::string value;
    double val;
    // FloatingLiteral(std::string value, double val, std::string kind = "FloatingLiteral"):kind(kind), value(value), val(val) {}
};

struct StringLiteral : public Expr {
    std::string kind = "StringLiteral";
    std::string value;
    
    // StringLiteral(std::string value, std::string kind = "StringLiteral"):kind(kind), value(value) {}
};

struct CharacterLiteral : public Expr {
    std::string kind = "CharacterLiteral";
    std::string value;
    char val;

    // CharacterLiteral(std::string value, char val, std::string kind = "CharacterLiteral"):kind(kind), value(value), val(val) {}
};


struct DeclRefExpr : public Expr {
    Decl* decl; 
};

struct BinaryExpr : public Expr {
    enum { kAdd, kSub, kMul, kDiv } op; 
    Expr *lft, *rht;
};



struct TranslationUnitDecl: public Decl {
    std::string kind = "TranslationUnitDecl";
    std::vector<Decl*> inner;
};

struct TypedefDecl: public Decl {
    std::string kind = "TypedefDecl";
    std::vector<Decl*> inner;
};




//manager
class Mgr : public std::vector<std::unique_ptr<Obj>> {
  public:
  //  第三个参数用于静态检查参数是否正确，也可以省略。
  template<typename T,
  typename ... Args,
  typename std::enable_if<std::is_constructible<T, Args...>::value>::type>
  T* make(Args ... args)
  {
    auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
    auto obj = ptr.get();
    emplace_back(std::move(ptr));
    return obj;
  }

};


#endif // ASG_HPP
