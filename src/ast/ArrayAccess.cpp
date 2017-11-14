//
//  ArrayAccess.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "ArrayAccess.hpp"
#include "Visitor.hpp"

ArrayAccess::ArrayAccess(Exp* e1, Exp* e2)
:   expr1(e1), expr2(e2), var(NULL)
{}

ArrayAccess::ArrayAccess(Var* v, Exp* e2)
:   var(v), expr2(e2), expr1(NULL)
{}

void ArrayAccess::accept(Visitor& v)
{
    v.visit(this);
}
