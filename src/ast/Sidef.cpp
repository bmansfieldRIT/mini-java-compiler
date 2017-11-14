//
//  Sidef.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Sidef.hpp"
#include "Visitor.hpp"

Sidef::Sidef(Exp* e)
: expr(e)
{}

void Sidef::accept(Visitor& v)
{
    v.visit(this);
}
