//
//  String.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "String.hpp"
#include "Visitor.hpp"

String::String() {}

void String::accept(Visitor& v)
{
    v.visit(this);
}
