//
//  Equals.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "Equals.hpp"
#include "Visitor.hpp"

Equals::Equals(Var* i, Exp* r)
:   id(i), rhs(r), arr(NULL)
{
    unused = false;
}

Equals::Equals(ArrayAccess* aa, Exp* r)
:   arr(aa), rhs(r), id(NULL)
{
    unused = false;
}

void Equals::accept(Visitor& v)
{
    v.visit(this);
}


