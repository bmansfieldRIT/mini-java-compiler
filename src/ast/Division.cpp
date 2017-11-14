//
//  Division.cpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include "Division.hpp"
#include "Visitor.hpp"

Division::Division(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void Division::accept(Visitor& v)
{
    v.visit(this);
}
