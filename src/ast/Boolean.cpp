//
//  Boolean.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Boolean.hpp"
#include "Visitor.hpp"

Boolean::Boolean() {}

void Boolean::accept(Visitor& v)
{
    v.visit(this);
}
