#ifndef TOJSON_HPP
#define TOJSON_HPP
#include "asg.hpp"

class ToJson {
public:
//basic
    llvm::json::Value operator()(Expr* obj);
    
    llvm::json::Object operator()(Decl* obj);


//literals
    llvm::json::Value operator()(IntegerLiteral* obj);

    llvm::json::Value operator()(FloatingLiteral* obj);

    llvm::json::Value operator()(StringLiteral* obj);

    llvm::json::Value operator()(CharacterLiteral* obj);

//TranslationUnitDecl
    llvm::json::Object operator()(TranslationUnitDecl* obj);
//TypedefDecl
    llvm::json::Object operator()(TypedefDecl* obj);

//functions
    void print(Obj* obj);

    void visit(Obj* obj);
};

#endif // TOJSON_HPP