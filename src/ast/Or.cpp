//
//  Or.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Or.hpp"
#include "Visitor.hpp"

Or::Or(Exp* l, Exp* r)
: lhs(l), rhs(r)
{}

void Or::accept(Visitor& v)
{
    v.visit(this);
}
