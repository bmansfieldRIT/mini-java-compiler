//
//  Equality.cpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include "Equality.hpp"
#include "Visitor.hpp"

Equality::Equality(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void Equality::accept(Visitor& v)
{
    v.visit(this);
}
