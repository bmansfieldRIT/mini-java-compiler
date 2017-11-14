//
//  Print.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Print.hpp"
#include "Visitor.hpp"

Print::Print(Exp* e)
:   expr(e)
{}

void Print::accept(Visitor& v)
{
    v.visit(this);
}
