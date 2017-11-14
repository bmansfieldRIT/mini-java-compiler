//
//  If.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "If.hpp"
#include "Visitor.hpp"

If::If(Exp* e, Statement* t, Statement* z)
:   expr(e), then(t), elze(z)
{}

If::If(Exp* e, Statement* t)
:   expr(e), then(t), elze(NULL)
{}

void If::accept(Visitor& v)
{
    v.visit(this);
}
