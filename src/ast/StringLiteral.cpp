//
//  StringLiteral.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "StringLiteral.hpp"
#include "Visitor.hpp"

StringLiteral::StringLiteral(string s)
:   str(s)
{}

void StringLiteral::accept(Visitor& v)
{
    v.visit(this);
}
