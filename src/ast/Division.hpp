//
//  Division.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef Division_hpp
#define Division_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Division : public Exp
{
public:
    Exp* lhs;
    Exp* rhs;
    Division(Exp* l, Exp* r);
    void accept(Visitor& v);
};

#endif /* Division_hpp */
