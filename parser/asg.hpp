class Mgr : public stdvector<stdunique_ptr<Obj {
  public:
  //  第三个参数用于静态检查参数是否正确，也可以省略。
  template<typename T,
  typename ... Args,
  typename = std::enable_if_t<std::is_constructible_v<T, Args ...>>>
  T* make(Args ... args)
  {
    auto ptr = stdmake_unique<T>(args);
    auto obj = ptr.get();
    emplace_back(stdmove(ptr));
    return obj;
  }
};




class 



union Type{
    std::int num;
    std::string str;
};

struct Obj {
virtual ~Obj() = default;
};

struct Decl : public Obj { 
std::string name; 
Type type; 
};

struct Expr : public Obj {
Type type;
};

struct IntegerLiteral : public Expr {
std::int64_t val;
}

struct DeclRefExpr : public Expr {
Decl* decl; 
};

struct BinaryExpr : public Expr {
enum { kAdd, kSub, kMul, kDiv } op; 
Expr *lft, *rht;
};
