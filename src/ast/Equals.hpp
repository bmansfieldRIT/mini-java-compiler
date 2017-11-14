//
//  Equals.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Equals_hpp
#define Equals_hpp

class Visitor;

#include <stdio.h>
#include "Statement.hpp"
#include "Var.hpp"
#include "Exp.hpp"
#include "ArrayAccess.hpp"

class Equals : public Statement
{
    
public:
    Var* id;
    Exp* rhs;
    ArrayAccess* arr;
    bool unused;
    Equals(Var* i, Exp* r);
    Equals(ArrayAccess* i, Exp* r);
    void accept(Visitor& v);
    
};

#endif /* Equals_hpp */
