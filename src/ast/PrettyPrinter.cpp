//
//  PrettyPrinter.cpp
//  
//
//  Created by Brian Mansfield on 4/10/17.
//
//

#include "PrettyPrinter.hpp"

PrettyPrinter::PrettyPrinter() {}

/*
 * Expressions
 */
void PrettyPrinter::visit(True* e)
{
    std::cout << "true";
}

void PrettyPrinter::visit(False* e)
{
    std::cout << "false";
}

void PrettyPrinter::visit(This* e)
{
    std::cout << "this";
}

void PrettyPrinter::visit(Not* e)
{
    std::cout << "!";
    e->expr->accept(*this);
}

void PrettyPrinter::visit(IntLiteral* e)
{
    std::cout << e->value;
}

void PrettyPrinter::visit(StringLiteral* e)
{
    std::cout << "\"" << e->str << "\"";
}

// is also a type
void PrettyPrinter::visit(Var* e)
{
    std::cout << e->varID;
}

void PrettyPrinter::visit(New* e)
{
    std::cout << "new ";
    e->func->accept(*this);
}

void PrettyPrinter::visit(And* e)
{
    
    e->lhs->accept(*this);
    std::cout << " && ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Or* e)
{
    e->lhs->accept(*this);
    std::cout << " || ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(LessThan* e)
{
    e->lhs->accept(*this);
    std::cout << " < ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Plus* e)
{
    e->lhs->accept(*this);
    std::cout << " + ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Minus* e)
{
    e->lhs->accept(*this);
    std::cout << " - ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Times* e)
{
    e->lhs->accept(*this);
    std::cout << " * ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Division* e)
{
    e->lhs->accept(*this);
    std::cout << " / ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Equality* e)
{
    e->lhs->accept(*this);
    std::cout << " == ";
    e->rhs->accept(*this);
}

void PrettyPrinter::visit(Length* e)
{
    e->expr->accept(*this);
    std::cout << ".length();";
}

void PrettyPrinter::visit(FuncCall* e)
{
    
    e->expr->accept(*this);
    std::cout << ".";
    e->id->accept(*this);
    std::cout << "(";
    for (int i = 0; i < e->expressions.size(); i++){
        e->expressions[i]->accept(*this);
    }
    std::cout << ");";
}

void PrettyPrinter::visit(IntArray* e)
{
    e->size->accept(*this);
}

/*
 *  Statements
 */
void PrettyPrinter::visit(Print* e)
{
    std::cout << "System.out.println(";
    e->expr->accept(*this);
    std::cout << "); ";
}

void PrettyPrinter::visit(If* e)
{
    std::cout << "if (";
    e->expr->accept(*this);
    std::cout << ")\n";
    e->then->accept(*this);
    std::cout << "\n ";
    if (e->elze != NULL){
        std::cout << " else ";
        e->elze->accept(*this);
    }
    
    std::cout << "\n}\n";
}

void PrettyPrinter::visit(Block* e)
{
    std::cout << "{";
    for (int i = 0; i < e->body.size(); i++){
        e->body[i]->accept(*this);
    }
    std::cout << "}";
}

void PrettyPrinter::visit(While* e)
{
    std::cout << "while(";
    e->expr->accept(*this);
    std::cout << ")\n";
    e->state->accept(*this);
    std::cout << "\n";
}

void PrettyPrinter::visit(Sidef* e)
{
    std::cout << "sidef(";
    e->expr->accept(*this);
    std::cout << ");\n";
}

void PrettyPrinter::visit(Equals* e)
{
    
    if (e->arr != NULL){
        e->arr->accept(*this);
        
    } else {
        e->id->accept(*this);
    }
    std::cout << " = ";
    e->rhs->accept(*this);
    std::cout << ";\n";
}

void PrettyPrinter::visit(ArrayAccess* e)
{
    if (e->var != NULL){
        e->var->accept(*this);
        
    } else {
        e->expr1->accept(*this);
    }
    std::cout << "[";
    e->expr2->accept(*this);
    std::cout << "]";
}

/*
 * Types
 */
void PrettyPrinter::visit(Boolean* e)
{
    std::cout << "boolean ";
}

void PrettyPrinter::visit(IntArrayType* e)
{
    std::cout << "int[] ";
}

void PrettyPrinter::visit(Integer* e)
{
    std::cout << "int ";
}

void PrettyPrinter::visit(String* e)
{
    std::cout << "String ";
}

/*
 *  Var Declaration
 */
void PrettyPrinter::visit(VarDecl* e)
{
    e->type->accept(*this);
    e->id->accept(*this);
    std::cout << ";";
}

/*
 *  Method Declaration
 */
void PrettyPrinter::visit(MethDecl* e)
{
    e->methType->accept(*this);
    e->methID->accept(*this);
    
    std::cout << "(";
    if (e->argTypes.size() > 0){
        for (int i = 0; i < e->argTypes.size(); i++){
            e->argTypes[i]->accept(*this);
            e->argVars[i]->accept(*this);
            std::cout << ", ";
        }
    }
    std::cout << "){\n";
    
    for (int i = 0; i < e->vardecls.size(); i++){
        std::cout << "\t\t";
        e->vardecls[i]->accept(*this);
        std::cout << "\n";
    }
    
    for (int i = 0; i < e->statements.size(); i++){
        if (e->statements[i] != NULL){
            std::cout << "\t\t";
            e->statements[i]->accept(*this);
            std::cout << "\n";
        }
    }
    
    std::cout << "\t\treturn ";
    e->ret->accept(*this);
    std::cout << ";\n\t}";
    
}

/*
 *  Class Declaration
 */
void PrettyPrinter::visit(ClassDecl* e)
{
    
    std::cout << "class ";
    e->id->accept(*this);
    
    if (e->extID != NULL){
        std::cout << " extends ";
        e->extID->accept(*this);
    }
    
    std::cout << "{\n";
    
    if (e->vardecls.size() > 0){
        for (int i = 0; i < e->vardecls.size(); i++){
            std::cout << "\t";
            e->vardecls[i]->accept(*this);
            std::cout << "\n";
        }
    }
    
    if (e->methdecls.size() > 0){
        for (int i = 0; i < e->methdecls.size(); i++){
            std::cout << "\t";
            e->methdecls[i]->accept(*this);
            std::cout << "\n";
        }
        
    }
    std::cout << "}\n";
}

/*
 *  Main Class Declaration
 */
void PrettyPrinter::visit(MainClass* e)
{
    std::cout << "class ";
    e->id->accept(*this);
    std::cout << " {\n";
    std::cout << "\tpublic static void main (String[] args){\n";
    
    if (e->statements.size() > 0){
        for (int i = 0; i < e->statements.size(); i++){
            std::cout << "\t\t";
            e->statements[i]->accept(*this);
        }
        std::cout << "\n";
    }
    std::cout << "\t}\n";
    std::cout << "}\n";
}

/*
 *  Program Declaration
 */
void PrettyPrinter::visit(Program* e)
{
    e->main->accept(*this);
    
    if (e->classes.size() > 0){
        for (int i = 0; i < e->classes.size(); i++){
            e->classes[i]->accept(*this);
            std::cout << "\n";
        }
    }
}
