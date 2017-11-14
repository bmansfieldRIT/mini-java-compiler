//
//  Plus.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Plus.hpp"
#include "Visitor.hpp"

Plus::Plus(Exp* l, Exp* r)
: lhs(l), rhs(r)
{}

void Plus::accept(Visitor& v)
{
    v.visit(this);
}
