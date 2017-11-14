//
//  Length.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Length.hpp"
#include "Visitor.hpp"

Length::Length(Exp* e) 
:   expr(e)
{}

void Length::accept(Visitor& v)
{
    v.visit(this);
}
