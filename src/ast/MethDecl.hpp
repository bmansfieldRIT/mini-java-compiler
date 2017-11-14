//
//  MethDecl.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef MethDecl_hpp
#define MethDecl_hpp

class Visitor;

#include <stdio.h>
#include <vector>
#include "Type.hpp"
#include "Var.hpp"
#include "VarDecl.hpp"
#include "Statement.hpp"
#include "Exp.hpp"
#include "Symbol.hpp"

using namespace std;

class MethDecl 
{
    
public:
    Type* methType;
    Var* methID;
    vector<Type*> argTypes;
    vector<Var*> argVars;
    vector<VarDecl*> vardecls;
    vector<Statement*> statements;
    Exp* ret;
    Symbol* sym;
    
    MethDecl(Type* methT, Var* methVar, vector<Type*> argTs, vector<Var*> argVs, vector<VarDecl*> varDs, vector<Statement*> stmnts, Exp* r); // all fields
    
    void accept(Visitor& v);
    
};

#endif /* MethDecl_hpp */
