//
//  Environment.hpp
//  
//
//  Created by Brian Mansfield on 4/10/17.
//
//

#ifndef Environment_hpp
#define Environment_hpp

#include <stdio.h>

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "Symbol.hpp"

#include "Visitor.hpp"
#include "Tree.hpp"

#include "True.hpp"
#include "False.hpp"
#include "This.hpp"
#include "Not.hpp"
#include "IntLiteral.hpp"
#include "StringLiteral.hpp"
#include "Var.hpp"

#include "New.hpp"
#include "And.hpp"
#include "Or.hpp"
#include "LessThan.hpp"
#include "Plus.hpp"
#include "Minus.hpp"
#include "Times.hpp"
#include "Division.hpp"
#include "Equality.hpp"
#include "Length.hpp"
#include "FuncCall.hpp"
#include "IntArray.hpp"

#include "Print.hpp"
#include "If.hpp"
#include "Block.hpp"
#include "While.hpp"
#include "Sidef.hpp"
#include "Equals.hpp"
#include "ArrayAccess.hpp"

#include "Boolean.hpp"
#include "IntArrayType.hpp"
#include "Integer.hpp"
#include "String.hpp"

#include "VarDecl.hpp"
#include "MethDecl.hpp"
#include "ClassDecl.hpp"
#include "MainClass.hpp"
#include "Program.hpp"

using namespace std;

class Environment : public Visitor
{
    
public:
    
    // Constructor
    Environment(void);
    vector<map<string, Symbol*>> env;
    map<string, map<string, Symbol*>> classes;
    int t_type;
    bool error, declarationFlag, inMainClass, reportClassName, collectingMethods;
    string mainClassName;
    string methodClassName;
    
    void enterScope(void);
    void exitScope(void);
    
    // Expressions
    void visit(True* e);
    void visit(False* e);
    void visit(This* e);
    void visit(Not* e);
    void visit(IntLiteral* e);
    void visit(StringLiteral* e);
    void visit(Var* e);
    void visit(New* e);
    
    void visit(And* e);
    void visit(Or* e);
    void visit(LessThan* e);
    void visit(Plus* e);
    void visit(Minus* e);
    void visit(Times* e);
    void visit(Division* e);
    void visit(Equality* e);
    void visit(Length* e);
    void visit(FuncCall* e);
    void visit(IntArray* e);
    
    // Statements
    void visit(Print* e);
    void visit(If* e);
    void visit(Block* e);
    void visit(While* e);
    void visit(Sidef* e);
    void visit(Equals* e);
    void visit(ArrayAccess* e);
    
    // Types
    void visit(Boolean* e);
    void visit(IntArrayType* e);
    void visit(Integer* e);
    void visit(String* e);
    
    // Declarations
    void visit(VarDecl* e);
    void visit(MethDecl* e);
    void visit(ClassDecl* e);
    void visit(MainClass* e);
    void visit(Program* e);
    
};

#endif /* Environment_hpp */
