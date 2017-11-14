//
//  False.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "False.hpp"
#include "Visitor.hpp"

False::False() {}

void False::accept(Visitor& v)
{
    v.visit(this);
}
