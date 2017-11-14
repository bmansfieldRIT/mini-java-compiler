//
//  IntArray.cpp
//  
//
//  Created by Brian Mansfield on 4/11/17.
//
//

#include "IntArray.hpp"
#include "Visitor.hpp"

IntArray::IntArray(Exp* e) 
:   size(e)
{}

void IntArray::accept(Visitor& v)
{
    v.visit(this);
}
