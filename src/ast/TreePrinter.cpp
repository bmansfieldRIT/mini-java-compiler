//
//  TreePrinter.cpp
//
//
//  Created by Brian Mansfield on 4/3/17.
//
//

#include "TreePrinter.hpp"

TreePrinter::TreePrinter(string f)
:   filename(f)
{
    out.open(f);
}

/*
 * Expressions
 */
void TreePrinter::visit(True* e)
{
    out << "TRUE";
}

void TreePrinter::visit(False* e)
{
    out << "FALSE";
}

void TreePrinter::visit(This* e)
{
    out << "THIS";
}

void TreePrinter::visit(Not* e)
{
    out << "(NOT ";
    e->expr->accept(*this);
    out << ")";
}

void TreePrinter::visit(IntLiteral* e)
{
    out << "(INT-LIT " << e->value << ")";
}

void TreePrinter::visit(StringLiteral* e)
{
    out << "(STR-LIT " << e->str << ")";
}

// is also a type
void TreePrinter::visit(Var* e)
{
    out << "(ID " << e->varID << ")";
}

void TreePrinter::visit(New* e)
{
    out << "(NEW ";
    e->func->accept(*this);
    out << ")";
}

void TreePrinter::visit(And* e)
{
    out << "(AND ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Or* e)
{
    out << "(OR ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(LessThan* e)
{
    out << "(LESS-THAN ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Plus* e)
{
    out << "(PLUS ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Minus* e)
{
    out << "(MINUS ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Times* e)
{
    out << "(TIMES ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Division* e)
{
    out << "(DIV ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Equality* e)
{
    out << "(EQUALITY ";
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(Length* e)
{
    out << "(LENGTH ";
    e->expr->accept(*this);
    out << ")";
}

void TreePrinter::visit(FuncCall* e)
{
    out << "(FUNC-CALL ";
    e->expr->accept(*this);
    e->id->accept(*this);
    for (int i = 0; i < e->expressions.size(); i++){
        e->expressions[i]->accept(*this);
    }
    out << ")";
}

void TreePrinter::visit(IntArray* e)
{
    out << "(INT-ARRAY ";
    e->size->accept(*this);
    out << ")";
}

/*
 *  Statements
 */
void TreePrinter::visit(Print* e)
{
    out << "(PRINT ";
    e->expr->accept(*this);
    out << ")";
}

void TreePrinter::visit(If* e)
{
    out << "(IF ";
    e->expr->accept(*this);
    out << " THEN ";
    e->then->accept(*this);

    if (e->elze != NULL){
        out << " ELSE ";
        e->elze->accept(*this);
    }

    out << ")\n";
}

void TreePrinter::visit(Block* e)
{
    out << "(BLOCK " << '\n';
    for (int i = 0; i < e->body.size(); i++){
        e->body[i]->accept(*this);
    }
    out << ")\n";
}

void TreePrinter::visit(While* e)
{
    out << "(WHILE ";
    e->expr->accept(*this);
    e->state->accept(*this);
    out << ")";
}

void TreePrinter::visit(Sidef* e)
{
    out << "(SIDEF ";
    e->expr->accept(*this);
    out << ")";
}

void TreePrinter::visit(Equals* e)
{
    out << "(EQUALS ";
    if (e->arr != NULL){
        e->arr->accept(*this);

    } else {
        e->id->accept(*this);
    }
    e->rhs->accept(*this);
    out << ")";
}

void TreePrinter::visit(ArrayAccess* e)
{
    out << "(ARRAY-ACCESS ";
    if (e->var != NULL){
        e->var->accept(*this);

    } else {
        e->expr1->accept(*this);
    }
    e->expr2->accept(*this);
    out << ")";
}

/*
 * Types
 */
void TreePrinter::visit(Boolean* e)
{
    out << "BOOLEAN";
}

void TreePrinter::visit(IntArrayType* e)
{
    out << "INT-ARRAY";
}

void TreePrinter::visit(Integer* e)
{
    out << "INT";
}

void TreePrinter::visit(String* e)
{
    out << "STRING";
}

/*
 *  Var Declaration
 */
void TreePrinter::visit(VarDecl* e)
{
    out << "(VAR-DECL ";
    e->type->accept(*this);
    e->id->accept(*this);
    out << ")\n";
}

/*
 *  Method Declaration
 */
void TreePrinter::visit(MethDecl* e)
{
    out << "(METH-DECL ";
    e->methType->accept(*this);
    e->methID->accept(*this);

    if (e->argTypes.size() > 0){
        out << "(TY-ID-LIST ";

        for (int i = 0; i < e->argTypes.size(); i++){
            out << "(";
            e->argTypes[i]->accept(*this);
            e->argVars[i]->accept(*this);
            out << ")";
        }
        out << ")" << '\n';
    }

    out << "\n(BLOCK\n";
    for (int i = 0; i < e->vardecls.size(); i++){
        e->vardecls[i]->accept(*this);
    }

    for (int i = 0; i < e->statements.size(); i++){
        if (e->statements[i] != NULL){
            e->statements[i]->accept(*this);
        }
    }

    out << "(RETURN ";
    e->ret->accept(*this);
    out << ")))\n";

}

/*
 *  Class Declaration
 */
void TreePrinter::visit(ClassDecl* e)
{

    out << "(CLASS-DECL ";
    e->id->accept(*this);

    if (e->extID != NULL){
        out << "(EXTENDS ";
        e->extID->accept(*this);
        out << ")\n";
    }

    if (e->vardecls.size() > 0 || e->methdecls.size() > 0){
        out << "(BLOCK\n";
        if (e->vardecls.size() > 0){
            for (int i = 0; i < e->vardecls.size(); i++){
                e->vardecls[i]->accept(*this);
            }
        }

        if (e->methdecls.size() > 0){
            for (int i = 0; i < e->methdecls.size(); i++){
                e->methdecls[i]->accept(*this);
            }
        }
        out << "))\n";
    }
}

/*
 *  Main Class Declaration
 */
void TreePrinter::visit(MainClass* e)
{
    out << "(MAIN-CLASS ";

    e->id->accept(*this);
    e->args->accept(*this);

    if (e->statements.size() > 0){
        out << "(BLOCK\n";
        for (int i = 0; i < e->statements.size(); i++){
            e->statements[i]->accept(*this);
        }
        out << "))\n";
    }
}

/*
 *  Program Declaration
 */
void TreePrinter::visit(Program* e)
{
    out << "(PROGRAM ";
    e->main->accept(*this);
    
    if (e->classes.size() > 0){
        for (int i = 0; i < e->classes.size(); i++){
            e->classes[i]->accept(*this);
        }
    }
    out << ")\n";
}
