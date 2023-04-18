#ifndef TYPING_HPP
#define TYPING_HPP
#include "asg.hpp"

extern Mgr gMgr;

class Typing {
public:
//basic
    void operator()(Obj* obj);

    void operator()(Expr* obj);
    
    void operator()(Decl* obj);

    void operator()(Stmt* obj);


//Expr
    void operator()(IntegerLiteral* obj);

    void operator()(FloatingLiteral* obj);

    void operator()(StringLiteral* obj);

    void operator()(CharacterLiteral* obj);
 
    void operator()(InitListExpr* obj);

    void operator()(ParenExpr* obj);

    void operator()(UnaryOperator* obj);

    void operator()(BinaryOperator* obj);

    void operator()(DeclRefExpr* obj);

    void operator()(CallExpr* obj);

    void operator()(ArraySubscriptExpr* obj);

    void operator()(ImplicitCastExpr* obj);

//Decl
    void operator()(TranslationUnitDecl* obj);

    void operator()(EmptyDecl* obj);

    void operator()(VarDecl* obj);

    void operator()(ParmVarDecl* obj);

    void operator()(FunctionDecl* obj);


//Stmt
    void operator()(CompoundStmt* obj);

    void operator()(NullStmt* obj);
    
    void operator()(DeclStmt* obj);

    void operator()(AssignStmt* obj);
    
    void operator()(CallExprStmt* obj);

    void operator()(ReturnStmt* obj);

    void operator()(IfStmt* obj);

    void operator()(DoStmt* obj);

    void operator()(WhileStmt* obj);

    void operator()(BreakStmt* obj);

    void operator()(ContinueStmt* obj);



//inner functions
    void print(Obj* obj);

    void visit(Obj* obj);
};

#endif // TYPING_HPP