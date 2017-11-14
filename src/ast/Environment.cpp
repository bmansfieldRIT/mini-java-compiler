//
//  Environment.cpp
//  
//
//  Created by Brian Mansfield on 4/10/17.
//
//

#include "Environment.hpp"

Environment::Environment() {
    error = false;
    declarationFlag = false;
    inMainClass = false;
    reportClassName = false;
}

void Environment::enterScope(void)
{
    map<string, Symbol*> env2;
    env.push_back(env2);
}

void Environment::exitScope(void)
{
    env.pop_back();
}

/*
 * Expressions
 */
void Environment::visit(True* e)
{
    e->sym = new Symbol(Symbol::BOOLEAN);
}

void Environment::visit(False* e)
{
    e->sym = new Symbol(Symbol::BOOLEAN);
}

void Environment::visit(This* e)
{
    // disallow the use of 'this' from a static context (the main method)
    if (inMainClass){
        std::cout << e->row << ":" << e->col << " error: 'this' used in main method\n";
        error = true;
    }
}

void Environment::visit(Not* e)
{
    e->expr->accept(*this);
}

void Environment::visit(IntLiteral* e)
{
    e->sym = new Symbol(Symbol::INT);
}

void Environment::visit(StringLiteral* e)
{
    e->sym = new Symbol(Symbol::STRING);
}

// is also a type
void Environment::visit(Var* e)
{

    if (!collectingMethods){
        bool foundVar = false;
        string varname = e->varID;
        int index = env.size() - 1;
        
        // search the stack of scopes to find the closest variable declaration
        while (index >= 0 && !foundVar){
            auto search = env[index].find(varname);
            if (search != env[index].end()){ // check current scope
                foundVar = true;
                
                if (!declarationFlag)
                    e->sym = search->second;
            }
            index -= 1;
        }
        if (!foundVar){
            std::cout << e->row << ":" << e->col << " error: Variable " << varname << " does not exist\n";
            error = true;
        }
        if (declarationFlag)        
            t_type = Symbol::IDENTIFIER;
        if (reportClassName){
            methodClassName = e->varID;
        }
    } else {
        t_type = Symbol::IDENTIFIER;
    }
}

void Environment::visit(New* e)
{
    e->func->accept(*this);
}

void Environment::visit(And* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Or* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(LessThan* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Plus* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Minus* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Times* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Division* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Equality* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Environment::visit(Length* e)
{
    e->expr->accept(*this);
}

void Environment::visit(FuncCall* e)
{
    reportClassName = true;
    e->expr->accept(*this);
    reportClassName = false;
    
    
    // set the return value of a called method
    auto search = classes.find(methodClassName);
    //std::cout << "finding class";
    
    if (search == classes.end()){
        std::cout << e->id->row << ":" << e->id->col << " error: Class " << methodClassName << " does not exist\n";
        error = true;
    } else {
        
        map<string, Symbol*> classMethods = search->second;
        
        string methName = e->id->varID;
        auto msearch = classMethods.find(methName);
        
        if (msearch == (search->second).end()){
        
            std::cout << e->id->row << ":" << e->id->col << " error: Method " << e->id->varID << " does not exist in class "<< methodClassName << "\n";
            error = true;
        } else {
            Symbol* s = new Symbol((msearch->second)->type);
            e->id->sym = s;
        }
        
    }
    for (int i = 0; i < e->expressions.size(); i++){
        e->expressions[i]->accept(*this);
    }
}

void Environment::visit(IntArray* e)
{
    e->size->accept(*this);
}

/*
 *  Statements
 */
void Environment::visit(Print* e)
{
    e->expr->accept(*this);
}

void Environment::visit(If* e)
{
    e->expr->accept(*this);
    e->then->accept(*this);
    e->elze->accept(*this);
}

void Environment::visit(Block* e)
{
    enterScope();
    
    for (int i = 0; i < e->body.size(); i++){
        e->body[i]->accept(*this);
    }
    
    exitScope();
}

void Environment::visit(While* e)
{
    e->expr->accept(*this);
    e->state->accept(*this);
}

void Environment::visit(Sidef* e)
{
    e->expr->accept(*this);
}

void Environment::visit(Equals* e)
{
    
    if (e->id != NULL){
        e->id->accept(*this);
    } else {
        e->arr->accept(*this);
    }
    e->rhs->accept(*this);
    
}

void Environment::visit(ArrayAccess* e)
{
    if (e->expr1 != NULL){
        e->expr1->accept(*this);
    } else {
        e->var->accept(*this);
    }
    e->expr2->accept(*this);
}

/*
 * Types
 */
void Environment::visit(Boolean* e)
{
    t_type = Symbol::BOOLEAN;
}

void Environment::visit(IntArrayType* e)
{
    t_type = Symbol::INTARRAY;
}

void Environment::visit(Integer* e)
{
    t_type = Symbol::INT;
}

void Environment::visit(String* e)
{
    t_type = Symbol::STRING;
}

/*
 *  Var Declaration
 */
void Environment::visit(VarDecl* e)
{
    declarationFlag = true;
    e->type->accept(*this); // changes the current temporary type
    declarationFlag = false;
    
    string varname = e->id->varID;
    auto search = env[env.size() - 1].find(varname);
    if (search != env[env.size() - 1].end()){
        std::cout << e->id->row << ":" << e->id->col << " error: Variable " << varname << " already exists\n";
        error = true;
    } else {
        Symbol* s = new Symbol(t_type);
        env[env.size() - 1].insert(std::pair<string, Symbol*>(varname, s));
    }
    
}

/*
 *  Method Declaration
 */
void Environment::visit(MethDecl* e)
{
    // hack
    collectingMethods = true;
    e->methType->accept(*this);
    e->sym = new Symbol(t_type);
    collectingMethods = false;
    
    string methname = e->methID->varID;
    auto search = env[env.size() - 1].find(methname);
    if (search != env[env.size() - 1].end()){
        std::cout << e->methID->row << ":" << e->methID->col << " error: Method " << methname << " already declared\n";
        error = true;
    } else {
        Symbol* s = new Symbol(Symbol::METHOD);
        env[env.size() - 1].insert(std::pair<string, Symbol*>(methname, s));
    }
    
    enterScope();
    
    // could be replaced by a vector of varDecls eventually
    for (int i = 0; i < e->argTypes.size(); i++){
        declarationFlag = true;
        e->argTypes[i]->accept(*this); // changes the current temporary type
        declarationFlag = false;
        
        e->argVars[i]->sym = new Symbol(t_type);
        
        string varname = e->argVars[i]->varID;
        auto search = env[env.size() - 1].find(varname);
        if (search != env[env.size() - 1].end()){
            std::cout << e->argVars[i]->row << ":" << e->argVars[i]->col << " error: Variable " << varname << " has same name as other formal parameter\n";
            error = true;
        } else {
            Symbol* s = new Symbol(t_type);
            env[env.size() - 1].insert(std::pair<string, Symbol*>(varname, s));
        }
    }
    
    //std::cout << e->vardecls.size() << '\n';
    if (e->vardecls.size() > 0){
        for (int i = 0; i < e->vardecls.size(); i++){
            e->vardecls[i]->accept(*this);
        }
    }
    
    //std::cout << e->statements.size() << '\n';
    if (e->statements.size() > 0){
        for (int i = 0; i < e->statements.size(); i++){
            e->statements[i]->accept(*this);
        }
    }
    
    e->ret->accept(*this);

    exitScope();
}

/*
 *  Class Declaration
 */
void Environment::visit(ClassDecl* e)
{
    
    if (e->extID != NULL){
        string classname = e->extID->varID;
        auto search = env[0].find(classname);
        if (search == env[0].end()){
            std::cout << e->extID->row << ":" << e->extID->col << " error: Inherited class " << classname << " does not exist\n";
            error = true;
        }
        if (classname == mainClassName){
            std::cout << e->extID->row << ":" << e->extID->col << " error: in " << e->id->varID << ":  Classes cannot inherit from the main class\n";
            error = true;
        }
    }
    
    enterScope();
    

    for (int i = 0; i < e->vardecls.size(); i++){
        e->vardecls[i]->accept(*this);
    }

    map<string, Symbol*> methods;
    for (int i = 0; i < e->methdecls.size(); i++){
        e->methdecls[i]->accept(*this);
    }
    
    exitScope();
}

/*
 *  Main Class Declaration
 */
void Environment::visit(MainClass* e)
{
    inMainClass = true;
    
    if (e->statements.size() > 0){
        for (int i = 0; i < e->statements.size(); i++){
            e->statements[i]->accept(*this);
        }
    }
    
    inMainClass = false;
}

/*
 *  Program Declaration
 */
void Environment::visit(Program* e)
{
    enterScope();
    
    mainClassName = e->main->id->varID;
    Symbol* sy = new Symbol(Symbol::CLASS);
    env[0].insert(std::pair<string, Symbol*>(mainClassName, sy));

    collectingMethods = true;
    for (int i = 0; i < e->classes.size(); i++){
        map<string, Symbol*> methods;
        for (int j = 0; j < e->classes[i]->methdecls.size(); j++){
            
            // add this method/return type to a map of methods associated with this class
            string methName = e->classes[i]->methdecls[j]->methID->varID;
            e->classes[i]->methdecls[j]->methType->accept(*this);
            Symbol* s = new Symbol(t_type);
            methods.insert(std::pair<string, Symbol*>(methName, s));
        }
        // add the map of methods to a global map of classes->methods+method return types
        classes.insert(std::pair<string, map<string, Symbol*>>(e->classes[i]->id->varID, methods));
        

        // check for multiply defined classes
        string classname = e->classes[i]->id->varID;
        auto search = env[0].find(classname);
        if (search != env[0].end()){
            std::cout << e->classes[i]->id->row << ":" << e->classes[i]->id->col << " error: Class " << classname << " already exists\n";
            error = true;
        }
        Symbol* s = new Symbol(Symbol::CLASS);
        env[0].insert(std::pair<string, Symbol*>(classname, s));
        //std::cout << "inserting " << classname << '\n';
    }
    collectingMethods = false;
    
    // name check each class
    e->main->accept(*this);
    
    if (e->classes.size() > 0){
        for (int i = 0; i < e->classes.size(); i++){
            e->classes[i]->accept(*this);
        }
    }
}
