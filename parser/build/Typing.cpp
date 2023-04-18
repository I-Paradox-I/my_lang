#include "Typing.hpp"
#include <iostream>

ScopeList gScopeList; //作用域
Type gFuncTempType; //用来function与内部return语句的类型对应
//basic
    void Typing::operator()(Obj* obj){
             if (auto p = dynamic_cast<Expr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<Decl*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<Stmt*>(obj))(*this)(p);
    }

    void Typing::operator()(Expr* obj){
             if (auto p = dynamic_cast<IntegerLiteral*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<FloatingLiteral*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<StringLiteral*>(obj))(*this)(p);            
        else if (auto p = dynamic_cast<CharacterLiteral*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<InitListExpr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ParenExpr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<UnaryOperator*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<BinaryOperator*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<DeclRefExpr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<CallExpr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ArraySubscriptExpr*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ImplicitCastExpr*>(obj))(*this)(p);

    }
    
    void Typing::operator()(Decl* obj) {
             if (auto p = dynamic_cast<TranslationUnitDecl*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<VarDecl*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ParmVarDecl*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<FunctionDecl*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<EmptyDecl*>(obj))(*this)(p);
    }

    void Typing::operator()(Stmt* obj) {
             if (auto p = dynamic_cast<CompoundStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<NullStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<DeclStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<AssignStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<CallExprStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ReturnStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<IfStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<DoStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<WhileStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<BreakStmt*>(obj))(*this)(p);
        else if (auto p = dynamic_cast<ContinueStmt*>(obj))(*this)(p);
    }







//Expr
    void Typing::operator()(IntegerLiteral* obj){}

    void Typing::operator()(FloatingLiteral* obj){}

    void Typing::operator()(StringLiteral* obj){}

    void Typing::operator()(CharacterLiteral* obj){}
 
    void Typing::operator()(InitListExpr* obj){
        
        //检查是否需要类型推断，需要，说明给的数字不全，本实验中直接不要这些子节点了
        auto expr = dynamic_cast<InitListExpr*>(obj);
        if(expr->inner.size() != expr->type.dim.back()){
            expr->inner.clear();
            return;
        }
        else if(expr->type.dim.size()>=2){
            for(auto & iter : obj->inner){
                if(dynamic_cast<InitListExpr*>(iter));
                else{
                    expr->inner.clear();
                    return;
                }
            }
        }




        for(auto & iter : obj->inner){
            if(auto expr = dynamic_cast<InitListExpr*>(iter)){
                expr->type = obj->type;
                expr->type.dim.pop_back();
                if(expr->type.dim.empty()) expr->type.is_array = 0;
            }
        }
        
        for(auto & iter : obj->inner)
            (*this)(iter);

        for(auto & iter : obj->inner){
            //左右值转换
            if(auto expr = dynamic_cast<DeclRefExpr*>(iter))
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                iter = imp;
            }
            else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(iter))
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                iter = imp;
            }

            //基本类转换
            auto p = dynamic_cast<Expr*>(iter);
            if((!p->type.is_array) && (p->type.basic_type != obj->type.basic_type)){
                auto expr = gMgr.make<ImplicitCastExpr>();
                expr->reason = "Basic Type Tranform";
                expr->type.basic_type = obj->type.basic_type;
                expr->inner.push_back(p);
                iter = expr;
            }
        }

    }

    void Typing::operator()(ParenExpr* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        obj->type = expr->type;
    }

    void Typing::operator()(UnaryOperator* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        obj->type = expr->type;
    }

    void Typing::operator()(BinaryOperator* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        obj->type.basic_type = obj->check_type();
        Type::type_name name0 = dynamic_cast<Expr*>(obj->inner[0])->type.basic_type;
        Type::type_name name1 = dynamic_cast<Expr*>(obj->inner[1])->type.basic_type;
        
        //左右值转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }

        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(name0 != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }
        if(name1 != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[1]);
            obj->inner[1] = expr;
        }
    }

    void Typing::operator()(DeclRefExpr* obj){
        if(gScopeList.find(obj->name) == nullptr)
            std::cout << "Undeclared variable " <<  obj->name << std::endl;
        else{
            obj->decl = gScopeList.find(obj->name);
            obj->type = obj->decl->type;
            obj->type.is_lval = 1;
        }
    }

    void Typing::operator()(CallExpr* obj){
        for(auto & iter : obj->inner)
           (*this)(iter);

        if(gScopeList.find(obj->name) == nullptr)
            std::cout << "Undeclared function " <<  obj->name << std::endl;
        else{
            obj->decl = gScopeList.find(obj->name);
            obj->type = obj->decl->type;
            obj->type.is_func = 0;
        }

        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        auto imp = gMgr.make<ImplicitCastExpr>();
        imp->type = expr->type;
        imp->type.decay = Type::PointerDecay::func_to_pointer;
        imp->reason = "function pointer decay";
        imp->inner.push_back(expr);
        obj->inner[0] = imp;

        // 获取指向第二个元素的迭代器
        for (auto it = obj->inner.begin() + 1; it != obj->inner.end(); ++it) {
            if(auto expr = dynamic_cast<DeclRefExpr*>(*it))
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;
                }
                else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(*it))
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;
                }

                //基本类转换
                if(expr->type.basic_type != obj->type.basic_type){
                    auto expr = gMgr.make<ImplicitCastExpr>();
                    expr->reason = "Int/Float To Double";
                    expr->type.basic_type = obj->type.basic_type;
                    expr->inner.push_back(*it);
                    *it = expr;
                }
        }

    }

    void Typing::operator()(ArraySubscriptExpr* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        obj->type = expr->type;
        obj->type.is_param = false;
        // assert(!obj->type.dim.empty());
        obj->type.dim.pop_back();
        if(obj->type.dim.empty()) obj->type.is_array = 0;

        //左右值转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->type.decay = Type::PointerDecay::arr_to_pointer;
            imp->inner.push_back(expr);
            imp->reason = "array pointer decay";
            obj->inner[0] = imp;
        }

        //基本类转换
        if(expr->type.basic_type != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }





        //左右值转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(expr->type.basic_type != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[1]);
            obj->inner[1] = expr;
        }

    }

    void Typing::operator()(ImplicitCastExpr* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
    }

//Decl
    void Typing::operator()(TranslationUnitDecl* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);
        gScopeList.pop_scope();
    }

    void Typing::operator()(EmptyDecl* obj){}


    void Typing::operator()(VarDecl* obj){
        gScopeList.push_decl(obj);
        if(!obj->inner.empty()){
            auto expr = dynamic_cast<Expr*>(obj->inner[0]);
            if(auto expr = dynamic_cast<InitListExpr*>(obj->inner[0])){
                    expr->type = obj->type;
            }

            for(auto & iter : obj->inner)
                (*this)(iter);

            //左右值转换
            if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[0]))
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }
            else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[0]))
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }

            //基本类转换
            if(expr->type.basic_type != obj->type.basic_type){
                auto expr = gMgr.make<ImplicitCastExpr>();
                expr->reason = "Int/Float To Double";
                expr->type.basic_type = obj->type.basic_type;
                expr->inner.push_back(obj->inner[0]);
                obj->inner[0] = expr;
            }
        }
    }

    void Typing::operator()(ParmVarDecl* obj){
        if(!obj->name.empty())
            gScopeList.push_decl(obj);
        for(auto & iter : obj->inner)
            (*this)(iter);
    }

    void Typing::operator()(FunctionDecl* obj){
        gScopeList.push_decl(obj);
        gScopeList.push_scope();

        // if(obj->defined && (obj->type.basic_type != Type::my_void)){
        //     if(auto stmt = dynamic_cast<CompoundStmt*>(obj->inner.back())){
        //         for (auto stmt : stmt->inner) {
        //             // 检查语句类型是否为返回语句
        //             if (auto returnstmt = dynamic_cast<ReturnStmt*>(stmt)) {
        //                 // 将类型赋值给返回语句
        //                 returnstmt->type = obj->type;
        //                 returnstmt->type.is_func = 0;
        //                 returnstmt->type.params.clear();
        //             }
        //         }
        //     }
        // }
        //函数内部不能定义函数！！！所以gFuncTempType这样实现是可行的

        //用于将类型赋予最后的return语句，便于return 语句的类型比较
        gFuncTempType = obj->type;
        for(auto & iter : obj->inner)
            (*this)(iter);
        gScopeList.pop_scope();
    }


//Stmt
    void Typing::operator()(CompoundStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);
        gScopeList.pop_scope();
    }

    void Typing::operator()(NullStmt* obj){}
    
    void Typing::operator()(DeclStmt* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
    }

    void Typing::operator()(AssignStmt* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        obj->type.basic_type = obj->check_type();
        Type::type_name name0 = dynamic_cast<Expr*>(obj->inner[0])->type.basic_type;
        Type::type_name name1 = dynamic_cast<Expr*>(obj->inner[1])->type.basic_type;
        
        //左右值转换
        // if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[0]))
        // {
        //     auto imp = gMgr.make<ImplicitCastExpr>();
        //     imp->type = expr->type;
        //     imp->inner.push_back(expr);
        //     imp->reason = "Left Value To Right Value";
        //     obj->inner[0] = imp;
        // }
        // else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[0]))
        // {
        //     auto imp = gMgr.make<ImplicitCastExpr>();
        //     imp->type = expr->type;
        //     imp->inner.push_back(expr);
        //     imp->reason = "Left Value To Right Value";
        //     obj->inner[0] = imp;
        // }

        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(name0 != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }
        if(name1 != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int/Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[1]);
            obj->inner[1] = expr;
        }

    }
    
    void Typing::operator()(CallExprStmt* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        if(gScopeList.find(obj->name) == nullptr)
            std::cout << "Undeclared variable " <<  obj->name << std::endl;
        else{
            obj->decl = gScopeList.find(obj->name);
            obj->type = obj->decl->type;
            obj->type.is_func = 0;
        }
        
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        auto imp = gMgr.make<ImplicitCastExpr>();
        imp->type = expr->type;
        imp->type.decay = Type::PointerDecay::func_to_pointer;
        imp->reason = "function pointer decay";
        imp->inner.push_back(expr);
        obj->inner[0] = imp;

        // 获取指向第二个元素的迭代器
        for (auto it = obj->inner.begin() + 1; it != obj->inner.end(); ++it) {
            if(auto expr = dynamic_cast<DeclRefExpr*>(*it))
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;
                }
                else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(*it))
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;
                }

                //基本类转换
                if(expr->type.basic_type != obj->type.basic_type){
                    auto expr = gMgr.make<ImplicitCastExpr>();
                    expr->reason = "Int/Float To Double";
                    expr->type.basic_type = obj->type.basic_type;
                    expr->inner.push_back(*it);
                    *it = expr;
                }
        }
    }

    void Typing::operator()(ReturnStmt* obj){
        obj->type = gFuncTempType;
        obj->type.is_func = 0;
        obj->type.params.clear();
        
        for(auto & iter : obj->inner)
            (*this)(iter);

        if(obj->inner.empty()) return;//void类无返回值
        //左右值转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner.front()))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner.front()))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }
        //基本类转换
        Type::type_name name0 = dynamic_cast<Expr*>(obj->inner[0])->type.basic_type;
        if(name0 != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Basic Type Transform";
            expr->type = obj->type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }
    }

    void Typing::operator()(IfStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);
        
        gScopeList.pop_scope();
    }

    void Typing::operator()(DoStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);
        gScopeList.pop_scope();
    }

    void Typing::operator()(WhileStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);
        gScopeList.pop_scope();
    }

    void Typing::operator()(BreakStmt* obj){}

    void Typing::operator()(ContinueStmt* obj){}


//functions
    void Typing::visit(Obj* obj){
        (*this)(obj);
    }
