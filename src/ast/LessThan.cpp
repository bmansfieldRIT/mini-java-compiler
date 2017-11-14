//
//  LessThan.cpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include "LessThan.hpp"
#include "Visitor.hpp"

LessThan::LessThan(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void LessThan::accept(Visitor& v)
{
    v.visit(this);
}
