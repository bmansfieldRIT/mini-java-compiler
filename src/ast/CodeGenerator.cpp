//
//  CodeGenerator.cpp
//  
//
//  Created by Brian Mansfield on 4/21/17.
//
//

#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator()
{
    label = 0; // unique counter id for jump labels
}

/*
 * Expressions
 */
void CodeGenerator::visit(True* e)
{
    *classfile << "\t" << "iconst_1 " << "\n";
}

void CodeGenerator::visit(False* e)
{
    *classfile << "\t" << "iconst_0 " << "\n";
}

void CodeGenerator::visit(This* e)
{
    // protection against hack
    if (!justgettingname)
        *classfile << "\t" << "aload_0 " << "\n";
}

void CodeGenerator::visit(Not* e)
{
    int label1 = ++label;
    int label2 = ++label;
    
    e->expr->accept(*this);
    *classfile << "\t" << "ifeq label" << label1 << "\n";
    *classfile << "\t" << "iconst_0 " << "\n";
    *classfile << "\t" << "goto label" << label2 << "\n";
    *classfile << "\tlabel" << label1 << ":" << "\n";
    *classfile << "\t" << "iconst_1 " << "\n";
    *classfile << "\tlabel" << label2 << ":" << "\n";
    
}

void CodeGenerator::visit(IntLiteral* e)
{
    // push an integer onto the stack
    *classfile << "\t" << "ldc " << e->value << "\n";
}

void CodeGenerator::visit(StringLiteral* e)
{
    // push a string onto the stack
    *classfile << "\t" << "ldc \"" << e->str << "\"" << "\n";
}

void CodeGenerator::visit(Var* e)
{
    int sz = varNames.size() - 1;
    
    if (justgettingname)
        newname = e->varID;
    else {
        
        for (int i = 0; i < varNames.size(); i++){
            if (varNames[sz - i] == e->varID){
                
                int slot = sz - i + 1;
                
                // determine type of variable and load it into memory
                if (e->sym->type == Symbol::STRING)
                    *classfile << "\t" << "aload_" << slot << "\n";
                else if (e->sym->type == Symbol::INT)
                    *classfile << "\t" << "iload_" << slot << "\n";
                else if (e->sym->type == Symbol::BOOLEAN)
                    *classfile << "\t" << "iload_" << slot << "\n";
                else
                    *classfile << "\t" << "iload_" << slot << "\n";
            }
        }
    }
}

void CodeGenerator::visit(New* e)
{
    if (justgettingname){
        justgettingname = true;
        e->func->accept(*this);
        justgettingname = false;
        
    } else {
        // bad hack because func is an expression, can't get name directly...
        // would need to change new->func to be either an id or an intarray
        justgettingname = true;
        e->func->accept(*this);
        justgettingname = false;
        
        // declare new object
        *classfile << "\t" << "new " << newname << "\n";
        
        // duplicate and initialize object
        *classfile << "\t" << "dup " << "\n";
        *classfile << "\t" << "invokespecial " << newname << "/<init>()V" << "\n";
    }
}

void CodeGenerator::visit(And* e)
{
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    *classfile << "\t" << "iand\n";
}

void CodeGenerator::visit(Or* e)
{
    int label1 = ++label;
    int label2 = ++label;
    
    // perform lazy evaluation
    e->lhs->accept(*this);
    *classfile << "\t" << "ifne label" << label1 << "\n";
    
    e->rhs->accept(*this);
    *classfile << "\t" << "ifne label" << label1 << "\n";
    *classfile << "\t" << "iconst_0" << "\n";
    *classfile << "\t" << "goto label" << label2 << "\n";
    
    *classfile << "\t" << "label" << label1 << ":" << "\n";
    *classfile << "\t" << "iconst_1" << "\n";
    
    *classfile << "\t" << "label" << label2 << ":" << "\n";

}

void CodeGenerator::visit(LessThan* e)
{
    // push both values onto the stack
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    int label1 = ++label;
    int label2 = ++label;
    
    // add the instruction
    *classfile << "\t" << "if_icmpge label" << label1 << "\n";
    *classfile << "\t" << "iconst_1" << "\n";
    *classfile << "\t" << "goto label" << label2 << "\n";
    *classfile << "\t" << "label" << label1 << ":" << "\n";
    *classfile << "\t" << "iconst_0" << "\n";
    *classfile << "\t" << "label" << label2 << ":" << "\n";
}

// need to add string handling with stringbuilder
void CodeGenerator::visit(Plus* e)
{
    // push both values onto the stack
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    // add the instruction
    *classfile << "\t" << "iadd\n";
}

void CodeGenerator::visit(Minus* e)
{
    // push both values onto the stack
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    // add the instruction
    *classfile << "\t" << "isub\n";
}

void CodeGenerator::visit(Times* e)
{
    // push both values onto the stack
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    // add the instruction
    *classfile << "\t" << "imul\n";
}

void CodeGenerator::visit(Division* e)
{
    // push both values onto the stack
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    // add the instruction
    *classfile << "\t" << "idiv\n";
}

void CodeGenerator::visit(Equality* e)
{
    int label1 = ++label;
    int label2 = ++label;
    
    e->lhs->accept(*this);
    e->rhs->accept(*this);
    
    if (e->lhs->sym->type == Symbol::INT){
        *classfile << "\t" << "if_icmpeq label" << label1 << "\n";
    } else {
        // need to push reference to stack instead of value above?
        *classfile << "\t" << "if_acmpeq label" << label1 << "\n";
    }
    
    // not equal
    *classfile << "\t" << "iconst_0" << "\n";
    *classfile << "\t" << "goto label" << label2 << "\n";
    
    // equal
    *classfile << "\t" << "label" << label1 << ":" << "\n";
    *classfile << "\t" << "iconst_1" << "\n";
    
    *classfile << "\t" << "label" << label2 << ":" << "\n";
    
}

void CodeGenerator::visit(Length* e)
{
}

void CodeGenerator::visit(FuncCall* e)
{

    // evaluate the expression to call the method on
    e->expr->accept(*this);
    
    // evaluate the arguments, push them onto the stack
    for (int i = 0; i < e->expressions.size(); i++)
        e->expressions[i]->accept(*this);
    
    // get the name of the class the method belongs to
    justgettingname = true;
    e->expr->accept(*this);
    justgettingname = false;
    
    // construct the method
    *classfile << "\t" << "invokevirtual " << newname << "/" << e->id->varID;
    
    
    // add the argument types
    *classfile << "(";
    for (int i = 0; i < e->expressions.size(); i++){
        if (e->expressions[i]->sym->type == Symbol::STRING)
            *classfile << "Ljava/lang/String;";
        else if (e->expressions[i]->sym->type == Symbol::INT)
            *classfile << "I";
        else if (e->expressions[i]->sym->type == Symbol::BOOLEAN)
            *classfile << "Ljava/lang/Boolean;";
    }
    *classfile << ")";
    
    // add the return type
    if (e->id->sym->type == Symbol::STRING)
        *classfile << "Ljava/lang/String;";
    else if (e->id->sym->type == Symbol::INT)
        *classfile << "I";
    else if (e->id->sym->type == Symbol::BOOLEAN)
        *classfile << "Ljava/lang/Boolean;";
    
    *classfile << "\n";
     
}

void CodeGenerator::visit(IntArray* e)
{
    // placeholder to remember hack, need to change to actual invocation of int array...
    if (justgettingname)
        newname = "INT ARRAY";
}

/*
 *  Statements
 */
void CodeGenerator::visit(Print* e)
{
    // push System.out onto the stack
    *classfile << "\t" << "getstatic java/lang/System/out Ljava/io/PrintStream;" << "\n";
    
    e->expr->accept(*this);
    
    // call the PrintStream.println() method.
    if (e->expr->sym->type == Symbol::STRING)
        *classfile << "\t" << "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V" << "\n";
    else if (e->expr->sym->type == Symbol::INT)
        *classfile << "\t" << "invokevirtual java/io/PrintStream/println(I)V" << "\n";
    else if (e->expr->sym->type == Symbol::BOOLEAN)
        *classfile << "\t" << "invokevirtual java/io/PrintStream/println(Ljava/lang/Boolean;)V" << "\n";
}

void CodeGenerator::visit(If* e)
{
    
    e->expr->accept(*this);
    
    int label1 = ++label;
    int label2 = ++label;
    
    *classfile << "\t" << "ifeq label" << label1 << "\n";
    e->then->accept(*this);
    *classfile << "\t" << "goto label" << label2 << "\n";
    
    *classfile << "\t" << "label" << label1 << ":" << "\n";
    e->elze->accept(*this);
    *classfile << "\t" << "label" << label2 << ":" << "\n";
}

void CodeGenerator::visit(Block* e)
{
    for (int i = 0; i < e->body.size(); i++)
        e->body[i]->accept(*this);
}

void CodeGenerator::visit(While* e)
{
    
    int label1 = ++label;
    int label2 = ++label;
    
    *classfile << "\t" << "label" << label1 << ":" << "\n";
    e->expr->accept(*this);

    *classfile << "\t" << "ifeq label" << label2 << "\n";
    e->state->accept(*this);
    *classfile << "\t" << "goto label" << label1 << "\n";
    
    *classfile << "\t" << "label" << label2 << ":" << "\n";
}

void CodeGenerator::visit(Sidef* e)
{
    e->expr->accept(*this);
}

// doesn't handle array access
void CodeGenerator::visit(Equals* e)
{
    if (!e->unused){
        e->rhs->accept(*this);
        
        int sz = varNames.size() - 1;
        for (int i = 0; i < varNames.size(); i++){
            if (varNames[sz - i] == e->id->varID){
                
                int slot = sz - i + 1;
                
                // determine type of variable and load it into memory
                if (e->id->sym->type == Symbol::STRING)
                    // invoke static?
                    *classfile << "\t" << "astore_" << slot << "\n";
                else if (e->id->sym->type == Symbol::INT)
                    *classfile << "\t" << "istore_" << slot << "\n";
                else if (e->id->sym->type == Symbol::BOOLEAN)
                    // invoke static?
                    *classfile << "\t" << "istore_" << slot << "\n";
            }
        }
    }
}

void CodeGenerator::visit(ArrayAccess* e)
{
}

/*
 * Types
 */
void CodeGenerator::visit(Boolean* e)
{
}

void CodeGenerator::visit(IntArrayType* e)
{
}

void CodeGenerator::visit(Integer* e)
{
}

void CodeGenerator::visit(String* e)
{
}

/*
 *  Var Declaration
 */
void CodeGenerator::visit(VarDecl* e)
{
    // need a way to track/pop values back off scope?
    varNames.push_back(e->id->varID);
}

/*
 *  Method Declaration
 */
void CodeGenerator::visit(MethDecl* e)
{
    for (int i = 0; i < e->argVars.size(); i++){
        varNames.push_back(e->argVars[i]->varID);
    }
    
    // declare method
    *classfile << ".method public " << e->methID->varID << "(";
    
    
    // int arrays? variables?
    for (int i = 0; i < e->argVars.size(); i++){
        if (e->argVars[i]->sym->type == Symbol::STRING)
            *classfile << "Ljava/lang/String";
        else if (e->argVars[i]->sym->type == Symbol::INT)
            *classfile << "I";
        else if (e->argVars[i]->sym->type == Symbol::BOOLEAN)
            *classfile << "Ljava/lang/Boolean";
    }
    *classfile << ")";
    
    // establish method return type
    if (e->sym->type == Symbol::STRING)
        *classfile << "Ljava/lang/String" << "\n";
    else if (e->sym->type == Symbol::INT)
        *classfile << "I" << "\n";
    else if (e->sym->type == Symbol::BOOLEAN)
        *classfile << "Ljava/lang/Boolean" << "\n";
        
    // overestimate stack and local limits
    *classfile << ".limit locals " << "10" << "\n";
    *classfile << ".limit stack " << "10" << "\n";
    
    for (int i = 0; i < e->vardecls.size(); i++)
        e->vardecls[i]->accept(*this);
    
    for (int i = 0; i < e->statements.size(); i++)
        e->statements[i]->accept(*this);
    
    e->ret->accept(*this);
     
    *classfile << "\t";
    
    // return type
    if (e->sym->type == Symbol::STRING)
        *classfile << "areturn" << "\n";
    else if (e->sym->type == Symbol::INT)
        *classfile << "ireturn" << "\n";
    else if (e->sym->type == Symbol::BOOLEAN)
        *classfile << "ireturn" << "\n";
    
    *classfile << ".end method" << "\n";
}

/*
 *  Class Declaration
 */
void CodeGenerator::visit(ClassDecl* e)
{
    ofstream jas;
    string mname = e->id->varID;
    jas.open(mname + ".j");
    
    classfile = &jas;
    
    // check for extended classes
    *classfile << ".class public " << mname << "\n";
    if (e->extID == NULL){
        *classfile << ".super java/lang/Object" << "\n";
        
        // default object init method
        *classfile << ".method public <init>()V" << "\n";
        *classfile << "\t" << "aload_0" << "\n";
        *classfile  << "\t"<< "invokenonvirtual java/lang/Object/<init>()V" << "\n";
        *classfile  << "\t"<< "return" << "\n";
        *classfile << ".end method" << "\n";
        
    } else {
        *classfile << ".super " << e->extID->varID << "\n";
        
        // super object init method
        *classfile << ".method public <init>()V" << "\n";
        *classfile << "\t" << "aload_0" << "\n";
        *classfile << "\t"<< "invokenonvirtual " << e->extID->varID << "/<init>()V" << "\n";
        *classfile << "\t" << "return" << "\n";
        *classfile << "\t" << ".end method" << "\n";
    }
    
    for (int i = 0; i < e->methdecls.size(); i++)
        e->methdecls[i]->accept(*this);
    
    classes.push_back(mname);
    
    jas.close();
}

/*
 *  Main Class Declaration
 */
void CodeGenerator::visit(MainClass* e)
{
    ofstream jas;
    string mname = e->id->varID;
    jas.open(mname + ".j");
    
    classfile = &jas;
    
    *classfile << ".class public " << mname << "\n";
    *classfile << ".super java/lang/Object" << "\n";
    
    *classfile << ".method public static main([Ljava/lang/String;)V" << "\n";
    
    // overestimate stack and local limits
    *classfile << ".limit locals " << "10" << "\n";
    *classfile << ".limit stack " << "10" << "\n";
    
    for (int i = 0; i < e->statements.size(); i++){
        e->statements[i]->accept(*this);
    }
    
    // method signature is always void
    *classfile << "\t" << "return" << "\n";
    *classfile << ".end method" << "\n";
    
    classes.push_back(mname);
    
    jas.close();
}

/*
 *  Program Declaration
 */
void CodeGenerator::visit(Program* e)
{
    e->main->accept(*this);
    
    for (int i = 0; i < e->classes.size(); i++){
        e->classes[i]->accept(*this);
    }
}
