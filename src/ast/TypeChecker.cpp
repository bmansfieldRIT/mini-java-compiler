//
//  TypeChecker.cpp
//
//
//  Created by Brian Mansfield on 4/21/17.
//
//

#include "TypeChecker.hpp"

TypeChecker::TypeChecker() {
    error = false;
    t_error = false;
    type_t = Symbol::UNDEFINED;
}

/*
 * Expressions
 */
void TypeChecker::visit(True* e)
{
    type_t = Symbol::BOOLEAN;
}

void TypeChecker::visit(False* e)
{
    type_t = Symbol::BOOLEAN;
}

void TypeChecker::visit(This* e) {}

void TypeChecker::visit(Not* e)
{
    e->expr->accept(*this);
}

void TypeChecker::visit(IntLiteral* e)
{
    type_t = Symbol::INT;
}

void TypeChecker::visit(StringLiteral* e)
{
    type_t = Symbol::STRING;
}

void TypeChecker::visit(Var* e)
{
    type_t = e->sym->type;
}

void TypeChecker::visit(New* e) {}

// only type checks if both sides are of type boolean
void TypeChecker::visit(And* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::BOOLEAN || e->rhs->sym->type != Symbol::BOOLEAN){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::BOOLEAN);
}

// only type checks if both sides are of type boolean
void TypeChecker::visit(Or* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::BOOLEAN || e->rhs->sym->type != Symbol::BOOLEAN){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::BOOLEAN);
}

// only type checks if both sides are of type int
void TypeChecker::visit(LessThan* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::INT || e->rhs->sym->type != Symbol::INT){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::BOOLEAN);
}

// only type checks if both sides are of type int, int + string, string + int, or string + string
void TypeChecker::visit(Plus* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (!(e->lhs->sym->type == e->rhs->sym->type) &&
            !(e->lhs->sym->type == Symbol::STRING && e->rhs->sym->type == Symbol::INT) &&
            !(e->lhs->sym->type == Symbol::INT && e->rhs->sym->type == Symbol::STRING) &&
            !(e->lhs->sym->type == Symbol::STRING && e->rhs->sym->type == Symbol::STRING)){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    if (e->lhs->sym->type == Symbol::STRING || e->rhs->sym->type == Symbol::STRING){
        e->sym = new Symbol(Symbol::STRING);
    } else if (e->lhs->sym->type == Symbol::INT && e->rhs->sym->type == Symbol::INT){
        e->sym = new Symbol(Symbol::INT);
    }
}

// only type checks if both sides are of type int
void TypeChecker::visit(Minus* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::INT || e->rhs->sym->type != Symbol::INT){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }


    e->sym = new Symbol(Symbol::INT);
}

// only type checks if both sides are of type int
void TypeChecker::visit(Times* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::INT && e->rhs->sym->type != Symbol::INT){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::INT);
}

// only type checks if both sides are of type int
void TypeChecker::visit(Division* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != Symbol::INT && e->rhs->sym->type != Symbol::INT){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::INT);
}

// equality only type checks if both sides are of the same type
void TypeChecker::visit(Equality* e)
{
    if (!t_error){
        e->lhs->accept(*this);
        e->lhs->sym = new Symbol(type_t);

        e->rhs->accept(*this);
        e->rhs->sym = new Symbol(type_t);

        if (e->lhs->sym->type != e->rhs->sym->type){
            t_error = true;
            error = true;
            std::cout << e->row << ":" << e->col << " Error: Invalid operands\n";
        }
    }

    e->sym = new Symbol(Symbol::BOOLEAN);
}

// can't call length on string, etc.
void TypeChecker::visit(Length* e)
{
    e->expr->accept(*this);
    e->sym = new Symbol(Symbol::INT);
}

void TypeChecker::visit(FuncCall* e)
{
    type_t = e->id->sym->type;
    e->sym = new Symbol(type_t);

    for (int i = 0; i < e->expressions.size(); i++){
        e->expressions[i]->accept(*this);
    }
}

// size must be an int
void TypeChecker::visit(IntArray* e)
{
    e->size->accept(*this);
    e->sym = new Symbol(Symbol::INTARRAY);
}

/*
 *  Statements
 */
void TypeChecker::visit(Print* e)
{

    e->expr->accept(*this);

    if (type_t == Symbol::UNDEFINED || (type_t != Symbol::INT && type_t != Symbol::STRING && type_t != Symbol::BOOLEAN)){
        std::cout << e->expr->row << ":" << e->expr->col << " Error: Print statement contains invalid expression\n";
        error = true;
    } else {
        e->expr->sym = new Symbol(type_t);
    }
}

void TypeChecker::visit(If* e)
{
    e->expr->accept(*this);
    e->then->accept(*this);
    e->elze->accept(*this);
}

void TypeChecker::visit(Block* e)
{
    for (int i = 0; i < e->body.size(); i++){
        e->body[i]->accept(*this);
    }
}

void TypeChecker::visit(While* e)
{
    e->expr->accept(*this);
    e->state->accept(*this);
}

void TypeChecker::visit(Sidef* e)
{
    e->expr->accept(*this);
}

void TypeChecker::visit(Equals* e)
{
    if (e->id != NULL){
        e->id->accept(*this);
    } else {
        e->arr->accept(*this);
    }
    e->rhs->accept(*this);
}

void TypeChecker::visit(ArrayAccess* e)
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
void TypeChecker::visit(Boolean* e) {}
void TypeChecker::visit(IntArrayType* e) {}
void TypeChecker::visit(Integer* e) {}
void TypeChecker::visit(String* e) {}

/*
 *  Var Declaration
 */
void TypeChecker::visit(VarDecl* e) {}

/*
 *  Method Declaration
 */
void TypeChecker::visit(MethDecl* e)
{

    for (int i = 0; i < e->statements.size(); i++){
        e->statements[i]->accept(*this);
        t_error = false;
        type_t = Symbol::UNDEFINED;
    }

    e->ret->accept(*this);
    if (t_error){
        std::cout << e->ret->row << ":" << e->ret->col << " Error: Invalid return statement\n";
    }
}

/*
 *  Class Declaration
 */
void TypeChecker::visit(ClassDecl* e)
{
    for (int i = 0; i < e->methdecls.size(); i++){
        e->methdecls[i]->accept(*this);
    }
}

/*
 *  Main Class Declaration
 */
void TypeChecker::visit(MainClass* e)
{
    for (int i = 0; i < e->statements.size(); i++){
        e->statements[i]->accept(*this);
        t_error = false;
        type_t = Symbol::UNDEFINED;
    }
}

/*
 *  Program Declaration
 */
void TypeChecker::visit(Program* e)
{
    e->main->accept(*this);

    if (e->classes.size() > 0){
        for (int i = 0; i < e->classes.size(); i++){
            e->classes[i]->accept(*this);
        }
    }
}
