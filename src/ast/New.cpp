//
//  New.cpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#include "New.hpp"
#include "Visitor.hpp"

New::New(Exp* f)
: func(f)
{}

void New::accept(Visitor& v)
{
    v.visit(this);
}
