//
//  And.cpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include <stdio.h>
#include "And.hpp"
#include "Visitor.hpp"

And::And(Exp* l, Exp* r)
:   lhs(l), rhs(r)
{}

void And::accept(Visitor& v)
{
    v.visit(this);
}
