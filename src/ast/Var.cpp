//
//  Var.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Var.hpp"
#include "Visitor.hpp"

Var::Var(string id, int r, int c)
:   varID(id), row(r), col(c), sym(NULL)
{}

void Var::accept(Visitor& v)
{
    v.visit(this);
}
