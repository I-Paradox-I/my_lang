#include "ToJson.hpp"
//basic
    llvm::json::Value ToJson::operator()(Expr* obj){
        if (auto p = dynamic_cast<IntegerLiteral*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<DeclRefExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<BinaryExpr*>(obj))
            return (*this)(p);
    }
    
    llvm::json::Object ToJson::operator()(Decl* obj) {
        if (auto p = dynamic_cast<TranslationUnitDecl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<TypedefDecl*>(obj))
            return (*this)(p);
    }


//literals
    llvm::json::Value ToJson::operator()(IntegerLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        return temp;
    }

    llvm::json::Value ToJson::operator()(FloatingLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        return temp;
    }

    llvm::json::Value ToJson::operator()(StringLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        return temp;
    }

    llvm::json::Value ToJson::operator()(CharacterLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        return temp;
    }

//TranslationUnitDecl
    llvm::json::Object ToJson::operator()(TranslationUnitDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

//TypedefDecl
    llvm::json::Object ToJson::operator()(TypedefDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"name", obj->name},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

//functions
    void ToJson::print(Obj* obj){
        if (auto p = dynamic_cast<Decl*>(obj)){
            llvm::json::Object temp_decl = (*this)(p);
            llvm::outs() << temp_decl;
        }
        else if (auto p = dynamic_cast<Expr*>(obj)){
            llvm::json::Value temp_expr = (*this)(p);
            llvm::outs() << temp_expr;
        }
    }

    void ToJson::visit(Obj* obj){
        this->print(obj);
    }
