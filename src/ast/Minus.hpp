//
//  Minus.hpp
//
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Minus_hpp
#define Minus_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Minus : public Exp
{
public:
    Exp* lhs;
    Exp* rhs;
    Minus(Exp* l, Exp* r);
    void accept(Visitor& v);
};

#endif /* Minus_hpp */
