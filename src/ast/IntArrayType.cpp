//
//  IntArrayType.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "IntArrayType.hpp"
#include "Visitor.hpp"

IntArrayType::IntArrayType() {}

void IntArrayType::accept(Visitor& v)
{
    v.visit(this);
}
