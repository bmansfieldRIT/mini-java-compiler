//
//  This.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "This.hpp"
#include "Visitor.hpp"

using namespace std;

This::This(int r, int c) 
:   row(r), col(c)
{}

void This::accept(Visitor& v)
{
    v.visit(this);
}
