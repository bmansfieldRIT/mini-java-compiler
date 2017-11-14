//
//  Optimization.hpp
//  
//
//  Created by Brian Mansfield on 4/21/17.
//
//

#include "Optimization.hpp"

Optimization::Optimization()
{
}

/*
 * Expressions
 */
void Optimization::visit(True* e)
{
}

void Optimization::visit(False* e)
{
}

void Optimization::visit(This* e)
{
}

void Optimization::visit(Not* e)
{
    e->expr->accept(*this);
}

void Optimization::visit(IntLiteral* e)
{
}

void Optimization::visit(StringLiteral* e)
{
}

void Optimization::visit(Var* e)
{
    for (int i = 0; i < unused.size(); i++){
        if (unused[i]->id->varID == e->varID){
            unused.erase(unused.begin() + i); // remove this variable from the unused list
            used.push_back(unused[i]);
            addtoused = true;
        }
    }
}

void Optimization::visit(New* e)
{
    e->func->accept(*this);
}

void Optimization::visit(And* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Or* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(LessThan* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Plus* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Minus* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Times* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Division* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Equality* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
}

void Optimization::visit(Length* e)
{
    e->expr->accept(*this);
}

void Optimization::visit(FuncCall* e)
{
    e->id->accept(*this);
    e->expr->accept(*this);
}

void Optimization::visit(IntArray* e)
{
    e->size->accept(*this);
}

/*
 *  Statements
 */
void Optimization::visit(Print* e)
{
    e->expr->accept(*this);
}

void Optimization::visit(If* e)
{
    e->expr->accept(*this);
    e->then->accept(*this);
    e->elze->accept(*this);
}

void Optimization::visit(Block* e)
{
    for (int i = 0; i < e->body.size(); i++)
        e->body[i]->accept(*this);
}

void Optimization::visit(While* e)
{
    e->expr->accept(*this);
    e->state->accept(*this);
}

void Optimization::visit(Sidef* e)
{
    e->expr->accept(*this);
}

void Optimization::visit(Equals* e)
{
    e->rhs->accept(*this);
    if (e->arr != NULL)
        e->arr->accept(*this);
    
    // check if assignment is preceeded by an unused previous assignment of the same variable
    for (int i = 0; i < unused.size(); i++){
        if (unused[i]->id->varID == e->id->varID){
            unused[i]->unused = true; //  mark previous assignment as dead, unused
            unused.erase(unused.begin() + i);
        }
    }
    
    // push new assignment into unused vector
    if (!addtoused)
        unused.push_back(e);
    addtoused = false;
    
}

void Optimization::visit(ArrayAccess* e)
{
    // unsure how arrayaccess fits in with larger picture
}

/*
 * Types
 */
void Optimization::visit(Boolean* e)
{
}

void Optimization::visit(IntArrayType* e)
{
}

void Optimization::visit(Integer* e)
{
}

void Optimization::visit(String* e)
{
}

/*
 *  Var Declaration
 */
void Optimization::visit(VarDecl* e)
{
}

/*
 *  Method Declaration
 */
void Optimization::visit(MethDecl* e)
{
    for (int i = 0; i < e->statements.size(); i++){
        e->statements[i]->accept(*this);
    }
    e->ret->accept(*this);
}

/*
 *  Class Declaration
 */
void Optimization::visit(ClassDecl* e)
{
    for (int i = 0; i < e->methdecls.size(); i++){
        e->methdecls[i]->accept(*this);
    }
    for (int i = 0; i < unused.size(); i++){
        unused[i]->unused = true; //  mark remaining unused variables as dead
    }
    
}

/*
 *  Main Class Declaration
 */
void Optimization::visit(MainClass* e)
{
    for (int i = 0; i < e->statements.size(); i++){
        e->statements[i]->accept(*this);
    }
    for (int i = 0; i < unused.size(); i++){
        unused[i]->unused = true; //  mark remaining unused variables as dead
    }
}

/*
 *  Program Declaration
 */
void Optimization::visit(Program* e)
{
    e->main->accept(*this);
    
    for (int i = 0; i < e->classes.size(); i++){
        e->classes[i]->accept(*this);
    }
}
