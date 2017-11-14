//
//  While.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "While.hpp"
#include "Visitor.hpp"

While::While(Exp* e, Statement* s)
:   expr(e), state(s)
{}

void While::accept(Visitor& v)
{
    v.visit(this);
}
