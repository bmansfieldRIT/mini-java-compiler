//
//  Minus.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Minus.hpp"
#include "Visitor.hpp"

Minus::Minus(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void Minus::accept(Visitor& v)
{
    v.visit(this);
}
