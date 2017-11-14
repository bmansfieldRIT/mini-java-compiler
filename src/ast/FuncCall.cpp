//
//  FuncCall.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "FuncCall.hpp"
#include "Visitor.hpp"

FuncCall::FuncCall(Exp* e, Var* i, vector<Exp*> args)
:   expr(e), id(i), expressions(args)
{}

void FuncCall::accept(Visitor& v)
{
    v.visit(this);
}
