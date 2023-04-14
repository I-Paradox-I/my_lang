#ifndef TOJSON_HPP
#define TOJSON_HPP
#include "asg.hpp"

class ToJson {
public:
//basic
    llvm::json::Value operator()(Obj* obj);

    llvm::json::Value operator()(Expr* obj);
    
    llvm::json::Object operator()(Decl* obj);

    llvm::json::Object operator()(Stmt* obj);


//Expr
    llvm::json::Value operator()(IntegerLiteral* obj);

    llvm::json::Value operator()(FloatingLiteral* obj);

    llvm::json::Value operator()(StringLiteral* obj);

    llvm::json::Value operator()(CharacterLiteral* obj);
 
    llvm::json::Value operator()(InitListExpr* obj);

    llvm::json::Value operator()(ParenExpr* obj);

    llvm::json::Value operator()(UnaryOperator* obj);

    llvm::json::Value operator()(BinaryOperator* obj);

//Decl
    llvm::json::Object operator()(TranslationUnitDecl* obj);

    llvm::json::Object operator()(EmptyDecl* obj);

    llvm::json::Object operator()(VarDecl* obj);

    llvm::json::Object operator()(ParmVarDecl* obj);

    llvm::json::Object operator()(FunctionDecl* obj);


//Stmt
    llvm::json::Object operator()(CompoundStmt* obj);

    llvm::json::Object operator()(NullStmt* obj);
    
    llvm::json::Object operator()(DeclStmt* obj);

    llvm::json::Object operator()(ReturnStmt* obj);

    llvm::json::Object operator()(IfStmt* obj);

    llvm::json::Object operator()(DoStmt* obj);

    llvm::json::Object operator()(WhileStmt* obj);

    llvm::json::Object operator()(BreakStmt* obj);

    llvm::json::Object operator()(ContinueStmt* obj);



//inner functions
    void print(Obj* obj);

    void visit(Obj* obj);
};

#endif // TOJSON_HPP