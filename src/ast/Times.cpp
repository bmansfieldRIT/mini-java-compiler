//
//  Times.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Times.hpp"
#include "Visitor.hpp"

Times::Times(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void Times::accept(Visitor& v)
{
    v.visit(this);
}
