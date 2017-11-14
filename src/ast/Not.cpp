//
//  Not.cpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#include "Not.hpp"
#include "Visitor.hpp"

Not::Not(Exp* e)
:   expr(e)
{}

void Not::accept(Visitor& v)
{
    v.visit(this);
}
