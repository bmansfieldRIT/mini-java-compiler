//
//  IntLiteral.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "IntLiteral.hpp"
#include "Visitor.hpp"

IntLiteral::IntLiteral(int v)
:   value(v)
{}

void IntLiteral::accept(Visitor& v)
{
    v.visit(this);
}
