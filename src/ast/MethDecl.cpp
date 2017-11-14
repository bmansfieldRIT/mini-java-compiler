//
//  MethDecl.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "MethDecl.hpp"
#include "Visitor.hpp"

using namespace std;

MethDecl::MethDecl(Type* methT, Var* methVar, vector<Type*> argTs, vector<Var*> argVs, vector<VarDecl*> varDs, vector<Statement*> stmnts, Exp* r) // all fields
:   methType(methT), methID(methVar), argTypes(argTs), argVars(argVs), vardecls(varDs), statements(stmnts), ret(r)
{}

void MethDecl::accept(Visitor& v)
{
    v.visit(this);
}
