#ifndef ASG_HPP
#define ASG_HPP

#include <llvm/Support/JSON.h>
#include <llvm/ADT/APFloat.h>
#include <stack>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include <any>


//base classes
struct Obj {
virtual ~Obj() = default;
};


struct Type  : public Obj {
    enum{my_default, my_void, my_int, my_long, my_float, my_double, my_char} basic_type = my_default;
    bool is_const = false;
    int is_ptr = 0;
    bool is_func = false;
    bool is_array = false;
    std::vector<int> dim;
    std::vector<std::string> params;
    std::string print(){
        std::string name;
        if(is_const) name = name + "const ";
        switch(basic_type){
            case(my_void):
                name = name + "void ";
                break;
            case(my_int):
                name = name + "int ";
                break;
            case(my_long):
                name = name + "long ";
                break;
            case(my_float):
                name = name + "float ";
                break;
            case(my_double):
                name = name + "double ";
                break;
            case(my_char):
                name = name + "char ";
                break;
            default:
                break;
        }
        if(is_ptr){
            int temp = is_ptr;
            while(temp--) name = name + "*";
        } 
        if(is_array){
            for(int i = dim.size()-1; i >= 0; i--){
                name = name + "[" + std::to_string(dim[i]) + "]";
            }
        }
        if(is_func){
            name = name + "(";
            for(int i = 0; i < params.size(); i++){
                if(i == params.size() - 1)
                {   
                    name = name + params[i];
                }
                else
                {
                    name = name + params[i];
                    name += ", ";
                }                    
            }
            name = name + ")";
        }
        if(name[name.size()-1] == ' ') name.pop_back();
        return name;
    }
};


struct Decl : public Obj { 
Type type; 
std::string name; 
};

struct Expr : public Obj {
Type type;
};

struct Stmt : public Obj {
Type type;
};



//Expressions

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


struct InitListExpr : public Expr {
    std::string kind = "InitListExpr";
    std::vector<Obj*> inner;
    void reverse(){
        std::reverse(inner.begin(), inner.end());
    }
};

struct ParenExpr : Expr{
    std::string kind = "ParenExpr";
    std::vector<Obj*> inner;
};

struct UnaryOperator : Expr{
    std::string kind = "UnaryOperator";
    enum { kPlus, kMinus, kExclaim} op; 
    std::vector<Obj*> inner;
};

struct BinaryOperator : Expr{
    std::string kind = "BinaryOperator";
    enum { kPlus, kMinus, kMultiply, kDivide, kMod, kEqual, kLess, kGreater, kEqualEqual, kLessEqual, kGreaterEqual, kAmpAmp, kPipePipe} op;
    std::vector<Obj*> inner;
};

// struct DeclRefExpr : public Expr {
//     Decl* decl; 
// };

// struct BinaryExpr : public Expr {
//     enum { kPlus, kMinus, kMul, kDiv } op; 
//     Expr *lft, *rht;
// };



//Declarations
struct TranslationUnitDecl: public Decl {
    std::string kind = "TranslationUnitDecl";
    std::vector<Obj*> inner;
};

struct DeclarationSeq : public Decl {
    std::vector<Obj*> seq;
    void reverse(){
        std::reverse(seq.begin(), seq.end());
    }
};

struct ParamsList : public Decl {
    std::vector<Obj*> seq;
    void reverse(){
        std::reverse(seq.begin(), seq.end());
    }
};

struct ParmVarDecl : public Decl {
    std::string kind = "ParmVarDecl";
    std::vector<Obj*> inner;
    std::string process_type(){
        std::string str = this->type.print();
        if(this->type.is_array){
            size_t pos = str.find("["); // 查找第一个'['的位置
            if (pos != std::string::npos) {
                size_t count = std::count(str.begin(), str.end(), '['); // 统计字符串中'['的个数
                if (count >= 2) {
                    str.replace(pos, 3, "(*)"); // 将第一个'['及其后面两个字符替换成"(*)"
                } else if (count == 1) {
                    str.replace(pos, 3, "*"); // 将第一个'['及其后面两个字符替换成"*"
                }
            }
        }
        return str;
    }
};

struct Declaration : public Decl {};

struct EmptyDecl : public Declaration{
    std::string kind = "EmptyDecl";
};

struct VarDecl: public Decl {
    std::string kind = "VarDecl";
    std::vector<Obj*> inner;
};

struct FunctionDecl: public Decl {
    std::string kind = "FunctionDecl";
    std::vector<Obj*> inner;
};


struct VarDeclSeq: public Decl {
    std::vector<Obj*> seq;
    void reverse(){
        std::reverse(seq.begin(), seq.end());
    }
};

struct DeclaratorList: public Decl {
    std::vector<Obj*> seq;
    void reverse(){
        std::reverse(seq.begin(), seq.end());
    }
};


//Statements
struct CompoundStmt: public Stmt {
    std::string kind = "CompoundStmt";
    std::vector<Obj*> inner;
};

struct StmtSeq: public Stmt {
    std::vector<Obj*> seq;
    void reverse(){
        std::reverse(seq.begin(), seq.end());
    }
};


struct NullStmt: public Stmt {
    std::string kind = "NullStmt";
};

struct DeclStmt: public Stmt {
    std::string kind = "DeclStmt";
    std::vector<Obj*> inner;
};

struct ReturnStmt: public Stmt {
    std::string kind = "ReturnStmt";
    std::vector<Obj*> inner;
};

struct IfStmt: public Stmt {
    std::string kind = "IfStmt";
    std::vector<Obj*> inner;
};

struct DoStmt: public Stmt {
    std::string kind = "DoStmt";
    std::vector<Obj*> inner;
};

struct WhileStmt: public Stmt {
    std::string kind = "WhileStmt";
    std::vector<Obj*> inner;
};

struct BreakStmt: public Stmt {
    std::string kind = "BreakStmt";
};

struct ContinueStmt: public Stmt {
    std::string kind = "ContinueStmt";
};


class ScopeList : std::vector<std::unordered_map<std::string, Decl*>>{
    public:
        void push_scope(){
            emplace_back();
        }
        void pop_scope(){
            pop_back();
        }
        void push_decl(Decl* ident){
            back()[ident->name] = ident;
        }
        Decl* find(const std::string& name){
            for(auto it = rbegin(); it != rend(); ++it){
                auto iter = it->find(name);
                if(iter != it->end()){
                    return iter->second;
                }
            }
            return nullptr;
        }
};


//manager
class Mgr : public std::vector<std::unique_ptr<Obj>> {
  public:
  //  第三个参数用于静态检查参数是否正确，也可以省略。
  template<typename T>
  T* make()
  {
    auto ptr = std::make_unique<T>();
    auto obj = ptr.get();
    emplace_back(std::move(ptr));
    return obj;
  }

};


#endif // ASG_HPP
