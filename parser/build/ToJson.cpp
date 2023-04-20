#include "ToJson.hpp"
//basic
    llvm::json::Value ToJson::operator()(Obj* obj){
        if (auto p = dynamic_cast<Expr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<Decl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<Stmt*>(obj))
            return (*this)(p);
        return "Not specified Obj.";
    }

    llvm::json::Value ToJson::operator()(Expr* obj){
        if (auto p = dynamic_cast<IntegerLiteral*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<FloatingLiteral*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<StringLiteral*>(obj))
            return (*this)(p);            
        if (auto p = dynamic_cast<CharacterLiteral*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<InitListExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ParenExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<UnaryOperator*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<BinaryOperator*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<DeclRefExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ArraySubscriptExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ImplicitCastExpr*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<CallExpr*>(obj))
            return (*this)(p);
        // if (auto p = dynamic_cast<BinaryExpr*>(obj))
        //     return (*this)(p);
        return "Not specified Expr.";
    }
    
    llvm::json::Object ToJson::operator()(Decl* obj) {
        if (auto p = dynamic_cast<TranslationUnitDecl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<VarDecl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ParmVarDecl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<FunctionDecl*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<EmptyDecl*>(obj))
            return (*this)(p);
        return llvm::json::Object {{"Not specified decl.", 0}};
    }

    llvm::json::Object ToJson::operator()(Stmt* obj) {
        if (auto p = dynamic_cast<CompoundStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<NullStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<DeclStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<AssignStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<CallExprStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ReturnStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<IfStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<DoStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<WhileStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<BreakStmt*>(obj))
            return (*this)(p);
        if (auto p = dynamic_cast<ContinueStmt*>(obj))
            return (*this)(p);
        return llvm::json::Object {{"Not specified stmt.", 0}};
    }





//Decl
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


    llvm::json::Object ToJson::operator()(EmptyDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        return temp;
    }


    llvm::json::Object ToJson::operator()(VarDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        if(!obj->name.empty()) temp["name"] = obj->name;
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(ParmVarDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };

        if(obj->type.is_param && obj->type.is_array) temp["type"] = llvm::json::Object{{"desugaredQualType", obj->type.print()},{"qualType", obj->type.print()},};
        else temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        if(!obj->name.empty()) temp["name"] = obj->name;
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(FunctionDecl* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        if(!obj->name.empty()) temp["name"] = obj->name;
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }



//Expr
    llvm::json::Value ToJson::operator()(IntegerLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        return temp;
    }

    llvm::json::Value ToJson::operator()(FloatingLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        return temp;
    }

    llvm::json::Value ToJson::operator()(StringLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->value;
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        return temp;
    }

    llvm::json::Value ToJson::operator()(CharacterLiteral* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        temp["value"] = obj->val;
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        return temp;
    }

    llvm::json::Value ToJson::operator()(InitListExpr* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }    

    llvm::json::Value ToJson::operator()(ParenExpr* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Value ToJson::operator()(UnaryOperator* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Value ToJson::operator()(BinaryOperator* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Value ToJson::operator()(DeclRefExpr* obj){
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        if(obj->type.is_param && obj->type.is_array) temp["type"] = llvm::json::Object{{"desugaredQualType", obj->type.print()},{"qualType", obj->type.print()},};
        else temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        return temp;
    }

    llvm::json::Value ToJson::operator()(CallExpr* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Value ToJson::operator()(ArraySubscriptExpr* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Value ToJson::operator()(ImplicitCastExpr* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(obj->type.is_param && obj->type.is_array) temp["type"] = llvm::json::Object{{"desugaredQualType", obj->type.print()},{"qualType", obj->type.print()},};
        else temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

//Stmt
    llvm::json::Object ToJson::operator()(CompoundStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(NullStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        return temp;
    }

    llvm::json::Object ToJson::operator()(DeclStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(AssignStmt* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(CallExprStmt* obj){
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        if(!obj->type.print().empty()) temp["type"] = llvm::json::Object{{"qualType", obj->type.print()},};
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(ReturnStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
        };
        if(!obj->inner.empty()){
            temp["inner"] = llvm::json::Array{};
            for(auto & it: obj->inner){
                temp.get("inner")->getAsArray()->push_back((*this)(it));
            }
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(IfStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(DoStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(WhileStmt* obj) {
        llvm::json::Object temp{
            {"kind", obj->kind},
            {"inner", llvm::json::Array{}}
        };
        for(auto & it: obj->inner){
            temp.get("inner")->getAsArray()->push_back((*this)(it));
        }
        return temp;
    }

    llvm::json::Object ToJson::operator()(BreakStmt* obj) {
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        return temp;
    }
 
    llvm::json::Object ToJson::operator()(ContinueStmt* obj) {
        llvm::json::Object temp;
        temp["kind"] = obj->kind;
        return temp;
    }

//functions
    void ToJson::print(Obj* obj){
        auto p = dynamic_cast<Decl*>(obj);
        llvm::json::Object temp_decl = (*this)(p);
        llvm::outs() << llvm::json::Value(std::move(temp_decl));
    }

    void ToJson::visit(Obj* obj){
        this->print(obj);
    }
