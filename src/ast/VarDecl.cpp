//
//  VarDecl.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "VarDecl.hpp"
#include "Visitor.hpp"

VarDecl::VarDecl(Type* t, Var* v)
:   type(t), id(v)
{}

void VarDecl::accept(Visitor& v)
{
    v.visit(this);
}
