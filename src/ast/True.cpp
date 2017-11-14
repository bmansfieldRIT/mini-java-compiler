//
//  True.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "True.hpp"
#include "Visitor.hpp"

True::True() {}

void True::accept(Visitor& v)
{
    v.visit(this);
}
