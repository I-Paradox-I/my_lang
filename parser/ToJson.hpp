#ifndef TOJSON_HPP
#define TOJSON_HPP
#include "asg.hpp"

class ToJson {
public:
    llvm::json::Value operator()(Expr* obj){
        if (auto p = dynamic_cast<IntegerLiteral*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<DeclRefExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<BinaryExpr*>(obj))
            return (*this)(p);
    }
    llvm::json::Object operator()(Decl* obj) {
        llvm::json::Object temp;
        return temp;
    }

};

#endif // TOJSON_HPP