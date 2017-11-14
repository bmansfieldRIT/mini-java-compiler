//
//  Visitor.hpp
//  
//
//  Created by Brian Mansfield on 4/3/17.
//
//

#ifndef Visitor_hpp
#define Visitor_hpp

#include <stdio.h>

class True;
class False;
class This;
class Not;
class IntLiteral;
class StringLiteral;
class Var;
class New;

class And;
class Or;
class LessThan;
class Plus;
class Minus;
class Times;
class Division;
class Equality;
class Length;
class FuncCall;
class IntArray;

class Print;
class If;
class Block;
class While;
class Sidef;
class Equals;
class ArrayAccess;

class Boolean;
class IntArrayType;
class Integer;
class String;

class VarDecl;
class MethDecl;
class ClassDecl;
class MainClass;
class Program;

class Visitor
{
    
public:
    
    // Expressions
    virtual void visit(True* e) = 0;
    virtual void visit(False* e) = 0;
    virtual void visit(This* e) = 0;
    virtual void visit(Not* e) = 0;
    virtual void visit(IntLiteral* e) = 0;
    virtual void visit(StringLiteral* e) = 0;
    
    virtual void visit(Var* e) = 0;
    virtual void visit(New* e) = 0;
    
    virtual void visit(And* e) = 0;
    virtual void visit(Or* e) = 0;
    virtual void visit(LessThan* e) = 0;
    virtual void visit(Plus* e) = 0;
    virtual void visit(Minus* e) = 0;
    virtual void visit(Times* e) = 0;
    virtual void visit(Division* e) = 0;
    virtual void visit(Equality* e) = 0;
    virtual void visit(Length* e) = 0;
    virtual void visit(FuncCall* e) = 0;
    virtual void visit(IntArray* e) = 0;
    
    // Statements
    virtual void visit(Print* e) = 0;
    virtual void visit(If* e) = 0;
    virtual void visit(Block* e) = 0;
    virtual void visit(While* e) = 0;
    virtual void visit(Sidef* e) = 0;
    virtual void visit(Equals* e) = 0;
    virtual void visit(ArrayAccess* e) = 0;
    
    // Types
    virtual void visit(Boolean* e) = 0;
    virtual void visit(IntArrayType* e) = 0;
    virtual void visit(Integer* e) = 0;
    virtual void visit(String* e) = 0;
    
    virtual void visit(VarDecl* e) = 0;
    virtual void visit(MethDecl* e) = 0;
    virtual void visit(ClassDecl* e) = 0;
    virtual void visit(MainClass* e) = 0;
    virtual void visit(Program* e) = 0;
    
};

#endif /* Visitor_hpp */
