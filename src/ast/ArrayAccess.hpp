//
//  ArrayAccess.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef ArrayAccess_hpp
#define ArrayAccess_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"
#include "Var.hpp"
#include "Statement.hpp"

class ArrayAccess : public Exp, public Statement
{
public:
    Exp* expr1;
    Exp* expr2;
    Var* var;
    ArrayAccess(Exp* e1, Exp* e);
    ArrayAccess(Var* e1, Exp* e);
    void accept(Visitor& v);
};

#endif /* ArrayAccess_hpp */
