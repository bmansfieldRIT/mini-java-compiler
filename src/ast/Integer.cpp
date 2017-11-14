//
//  Integer.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Integer.hpp"
#include "Visitor.hpp"

Integer::Integer() {}

void Integer::accept(Visitor& v)
{
    v.visit(this);
}
