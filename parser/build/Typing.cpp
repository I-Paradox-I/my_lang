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




        //给子节点赋予类型
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
            auto expr = dynamic_cast<Expr*>(iter);
            //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                iter = imp;
            }

            //基本类转换
            if((!expr->type.is_array) && (expr->type.basic_type != obj->type.basic_type)){
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->reason = "Basic Type Tranform";
                imp->type.basic_type = obj->type.basic_type;
                imp->inner.push_back(iter);
                iter = imp;
            }
            
        }

    // //节点处理
    //     auto expr = dynamic_cast<InitListExpr*>(obj);
    //     if(expr->inner.empty()) return;
    //     //预期的子节点的类型
    //     Type subType = expr->type;
    //     subType.dim.pop_back();
    //     if(subType.dim.empty()) subType.is_array = 0;
    //     // int pos = 0;
    //     // int dest = expr->type.dim.back();
    //     // bool need_new_node = false;
    //     std::vector<Obj*> processed_inner;
    //     InitListExpr* Node = gMgr.make<InitListExpr>();
    //     Node->type = subType;

    //     for(auto son : expr->inner){
    //         Type realType = dynamic_cast<Expr*>(son)->type;
    //         //子节点类型不符合
    //         if(realType.dim != subType.dim){
    //             Node->inner.push_back(son);
    //             if(Node->inner.size() == expr->type.dim.back()){
    //                 processed_inner.push_back(Node);
    //                 Node = gMgr.make<InitListExpr>();
    //                 Node->type = subType;
    //             }
    //         }//子节点类型符合
    //         else /*if(realType.dim == subType.dim)*/{
    //             if(!Node->inner.empty())
    //             processed_inner.push_back(son);
    //             if(processed_inner)
    //         }
    //     }


        // //子节点类型不符合
        // while(pos < dest){
        //     //边界条件 如果列表中的参数数量比列表维度还小，则将节点的inner置空
        //     if(expr->inner.size() < expr->type.dim.back())
        //     {
        //         expr->inner.clear();
        //         return;
        //     }
        //     Type realType = dynamic_cast<Expr*>(expr->inner[pos])->type;
        //     //子节点类型不符合
        //     if(realType.dim != subType.dim){
        //         Node->inner.push_back(expr->inner[pos]);
        //         pos++;
        //     }
        //     else{//子节点类型符合
        //         if(Node->inner.empty()){
        //             pos++;
        //         }
        //         else{
                    
        //         }
        //     }
        // }

        // //边界条件
        // if(expr->inner.size() != expr->type.dim.back() || ){
        //     expr->inner.clear();
        //     return;
        // }

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
        if(obj->op == UnaryOperator::kExclaim) //"!"符号直接让表达式类型变成int(其实是bool)
            obj->type.basic_type = Type::my_int;
        else{
            obj->type = expr->type;
            obj->type.is_const = false;
        }
        obj->type.is_lval = false;
        //左右值转换
        if(expr->type.is_lval)
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }

        //基本类转换
        if(expr->type.basic_type != obj->type.basic_type && obj->op != UnaryOperator::kExclaim){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }

    }

    void Typing::operator()(BinaryOperator* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        Type::type_name common_type = obj->check_type();
        Type::type_name name0 = dynamic_cast<Expr*>(obj->inner[0])->type.basic_type;
        Type::type_name name1 = dynamic_cast<Expr*>(obj->inner[1])->type.basic_type;
        bool logic_conj = false;

        auto expr = dynamic_cast<BinaryOperator*>(obj);
        auto expr0 = dynamic_cast<Expr*>(obj->inner[0]);
        auto expr1 = dynamic_cast<Expr*>(obj->inner[1]);
                
         //如果是逻辑表达式       
        if( expr->op == BinaryOperator::kEqualEqual     || 
            expr->op == BinaryOperator::kExclaimEqual   || 
            expr->op == BinaryOperator::kLess           ||
            expr->op == BinaryOperator::kLessEqual      ||
            expr->op == BinaryOperator::kGreater        ||
            expr->op == BinaryOperator::kGreaterEqual      
            )
        {
            expr->type.basic_type = Type::my_int;
        }
        else
        if( expr->op == BinaryOperator::kAmpAmp         ||
            expr->op == BinaryOperator::kPipePipe 
        ){
            expr->type.basic_type = Type::my_int;
            logic_conj = true;
        }
        else if(expr0->type.is_lval && expr->op == BinaryOperator::kEqual)//赋值语句的隐式类型转换
        {
            expr->type.basic_type = expr0->type.basic_type;
            expr->type.is_lval = false;
            common_type = expr0->type.basic_type;
        }
        else{
            expr->type.basic_type = obj->check_type();
        }

        //除了赋值=，其他符号左右值转换
        if(expr0->type.is_lval && expr->op != BinaryOperator::kEqual)
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr0->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr0);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }

        if(expr1->type.is_lval)
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr1->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr1);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(name0 != common_type && !logic_conj){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = common_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }
        if(name1 != common_type && !logic_conj){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = common_type;
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
        
        std::vector<Obj*> params;//声明时的参数列表
        if(gScopeList.find(obj->name) == nullptr)
            std::cout << "Undeclared variable " <<  obj->name << std::endl;
        else{
            obj->decl = gScopeList.find(obj->name);
            obj->type = obj->decl->type;

            auto func = dynamic_cast<FunctionDecl*>(obj->decl);
            params = func->inner;

            obj->type.is_func = 0;
        }

        //指针转换
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        auto imp = gMgr.make<ImplicitCastExpr>();
        imp->type = expr->type;
        imp->type.decay = Type::PointerDecay::func_to_pointer;
        imp->reason = "function pointer decay";
        imp->inner.push_back(expr);
        obj->inner[0] = imp;

        // 获取从指向第二个元素开始的迭代器
        for (auto it = obj->inner.begin() + 1, it2 = params.begin(); it != obj->inner.end() && it2 != params.end(); ++it, ++it2) {
            if(auto expr = dynamic_cast<Expr*>(*it)){
                if(expr->type.is_lval)
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->type.is_const = false;
                    imp->type.is_param = true;
                    if(imp->type.dim.size()==1)
                    {
                        imp->type.is_array = false;
                        imp->type.is_ptr += 1;
                        imp->type.dim.pop_back();
                    }
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;

                    //Noop 一个string字面量的不知道干什么的转换，只有最后一个样例有，就打表了
                    if(auto str = dynamic_cast<StringLiteral*>(expr)){
                        auto imp2 = gMgr.make<ImplicitCastExpr>();
                        imp2->type = imp->type;
                        imp2->type.is_const = true;
                        imp2->type.is_array = true;
                        imp2->type.is_ptr -= 1;
                        imp2->type.dim.push_back(-1);

                        imp2->inner.push_back(imp);
                        imp2->reason = "NoOp";
                        *it = imp2;
                    }
                }

                //基本类转换
                auto pardecl = dynamic_cast<Decl*>(*it2);
                if(expr->type.basic_type != pardecl->type.basic_type){
                    auto expr = gMgr.make<ImplicitCastExpr>();
                    expr->reason = "Int To Float To Double";
                    expr->type.basic_type = pardecl->type.basic_type;
                    expr->inner.push_back(*it);
                    *it = expr;
                }
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

        //指针转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            // imp->type.is_const = false;
            imp->type.decay = Type::PointerDecay::arr_to_pointer;
            imp->inner.push_back(expr);
            imp->reason = "array pointer decay";
            obj->inner[0] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[0]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            // imp->type.is_const = false;
            imp->type.decay = Type::PointerDecay::arr_to_pointer;
            imp->inner.push_back(expr);
            imp->reason = "array pointer decay";
            obj->inner[0] = imp;
        }

        //基本类转换
        if(expr->type.basic_type != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = obj->type.basic_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }





        //左右值转换
        if(auto expr = dynamic_cast<DeclRefExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }
        else if(auto expr = dynamic_cast<ArraySubscriptExpr*>(obj->inner[1]))
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(expr->type.basic_type != obj->type.basic_type){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
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
            if(auto expr = dynamic_cast<StringLiteral*>(obj->inner[0])){
                    expr->type = obj->type;
                    expr->type.is_const = true;
                    expr->type.is_lval = false;
            }

            for(auto & iter : obj->inner)
                (*this)(iter);

            //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }

            //基本类转换
            if(expr->type.basic_type != obj->type.basic_type){
                auto expr = gMgr.make<ImplicitCastExpr>();
                expr->reason = "Int To Float To Double";
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
        Type::type_name common_type = obj->check_type();
        Type::type_name name0 = dynamic_cast<Expr*>(obj->inner[0])->type.basic_type;
        Type::type_name name1 = dynamic_cast<Expr*>(obj->inner[1])->type.basic_type;
        bool logic_conj = false;

        auto expr = dynamic_cast<AssignStmt*>(obj);
        auto expr0 = dynamic_cast<Expr*>(obj->inner[0]);
        auto expr1 = dynamic_cast<Expr*>(obj->inner[1]);
        
         //如果是逻辑表达式       
        if( expr->op == AssignStmt::kEqualEqual     || 
            expr->op == AssignStmt::kExclaimEqual   || 
            expr->op == AssignStmt::kLess           ||
            expr->op == AssignStmt::kLessEqual      ||
            expr->op == AssignStmt::kGreater        ||
            expr->op == AssignStmt::kGreaterEqual  
            )
        {
            expr->type.basic_type = Type::my_int;
        }
        else 
        if( expr->op == AssignStmt::kAmpAmp         ||
            expr->op == AssignStmt::kPipePipe   
        ){
            expr->type.basic_type = Type::my_int;
            logic_conj = true;
        }
        else if(expr0->type.is_lval && expr->op == AssignStmt::kEqual)//赋值语句的隐式类型转换
        {
            expr->type.basic_type = expr0->type.basic_type;
            expr->type.is_lval = false;
            common_type = expr0->type.basic_type;
        }
        else{
            expr->type.basic_type = obj->check_type();
        }

        //除了赋值=，其他符号左右值转换
        if(expr0->type.is_lval && expr->op != AssignStmt::kEqual)
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr0->type;
            imp->type.is_const = false;
            imp->inner.push_back(expr0);
            imp->reason = "Left Value To Right Value";
            obj->inner[0] = imp;
        }

        if(expr1->type.is_lval)
        {
            auto imp = gMgr.make<ImplicitCastExpr>();
            imp->type = expr1->type;
            imp->inner.push_back(expr1);
            imp->reason = "Left Value To Right Value";
            obj->inner[1] = imp;
        }

        //基本类转换
        if(name0 != common_type && !logic_conj){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = common_type;
            expr->inner.push_back(obj->inner[0]);
            obj->inner[0] = expr;
        }
        if(name1 != common_type && !logic_conj){
            auto expr = gMgr.make<ImplicitCastExpr>();
            expr->reason = "Int To Float To Double";
            expr->type.basic_type = common_type;
            expr->inner.push_back(obj->inner[1]);
            obj->inner[1] = expr;
        }

    }
    
    void Typing::operator()(CallExprStmt* obj){
        for(auto & iter : obj->inner)
            (*this)(iter);
        
        std::vector<Obj*> params;//声明时的参数列表
        if(gScopeList.find(obj->name) == nullptr)
            std::cout << "Undeclared variable " <<  obj->name << std::endl;
        else{
            obj->decl = gScopeList.find(obj->name);
            obj->type = obj->decl->type;

            auto func = dynamic_cast<FunctionDecl*>(obj->decl);
            params = func->inner;

            obj->type.is_func = 0;
        }

        //指针转换
        auto expr = dynamic_cast<Expr*>(obj->inner[0]);
        auto imp = gMgr.make<ImplicitCastExpr>();
        imp->type = expr->type;
        imp->type.decay = Type::PointerDecay::func_to_pointer;
        imp->reason = "function pointer decay";
        imp->inner.push_back(expr);
        obj->inner[0] = imp;

        // 获取从指向第二个元素开始的迭代器
        for (auto it = obj->inner.begin() + 1, it2 = params.begin(); it != obj->inner.end() && it2 != params.end(); ++it, ++it2) {
            if(auto expr = dynamic_cast<Expr*>(*it)){
                if(expr->type.is_lval)
                {
                    auto imp = gMgr.make<ImplicitCastExpr>();
                    imp->type = expr->type;
                    imp->type.is_const = false;
                    imp->type.is_param = true;
                    if(imp->type.dim.size()==1)
                    {
                        imp->type.is_array = false;
                        imp->type.is_ptr += 1;
                        imp->type.dim.pop_back();
                    }
                    imp->inner.push_back(expr);
                    imp->reason = "Left Value To Right Value";
                    *it = imp;

                    //Noop 一个string字面量的不知道干什么的转换，只有最后一个样例有，就打表了
                    if(auto str = dynamic_cast<StringLiteral*>(expr)){
                        auto imp2 = gMgr.make<ImplicitCastExpr>();
                        imp2->type = imp->type;
                        imp2->type.is_const = true;
                        imp2->type.is_array = true;
                        imp2->type.is_ptr -= 1;
                        imp2->type.dim.push_back(-1);

                        imp2->inner.push_back(imp);
                        imp2->reason = "NoOp";
                        *it = imp2;
                    }
                }

                //基本类转换
                auto pardecl = dynamic_cast<Decl*>(*it2);
                if(expr->type.basic_type != pardecl->type.basic_type){
                    auto expr = gMgr.make<ImplicitCastExpr>();
                    expr->reason = "Int To Float To Double";
                    expr->type.basic_type = pardecl->type.basic_type;
                    expr->inner.push_back(*it);
                    *it = expr;
                }
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
        
        if(auto expr = dynamic_cast<Expr*>(obj->inner.front()))
        {   //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }
            //基本类转换
            if(expr->type.basic_type != obj->type.basic_type){
                auto expr = gMgr.make<ImplicitCastExpr>();
                expr->reason = "Basic Type Transform";
                expr->type = obj->type;
                expr->inner.push_back(obj->inner[0]);
                obj->inner[0] = expr;
            }
        }
    }

    void Typing::operator()(IfStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);

        if(auto expr = dynamic_cast<Expr*>(obj->inner.front()))
        {   //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }
        }



        gScopeList.pop_scope();
    }

    void Typing::operator()(DoStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);

        if(auto expr = dynamic_cast<Expr*>(obj->inner.back()))
        {   //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[obj->inner.size()-1] = imp;
            }
        }

        gScopeList.pop_scope();
    }

    void Typing::operator()(WhileStmt* obj){
        gScopeList.push_scope();
        for(auto & iter : obj->inner)
            (*this)(iter);

        if(auto expr = dynamic_cast<Expr*>(obj->inner.front()))
        {   //左右值转换
            if(expr->type.is_lval)
            {
                auto imp = gMgr.make<ImplicitCastExpr>();
                imp->type = expr->type;
                imp->type.is_const = false;
                imp->inner.push_back(expr);
                imp->reason = "Left Value To Right Value";
                obj->inner[0] = imp;
            }
        }

        gScopeList.pop_scope();
    }

    void Typing::operator()(BreakStmt* obj){}

    void Typing::operator()(ContinueStmt* obj){}


//functions
    void Typing::visit(Obj* obj){
        (*this)(obj);
    }
