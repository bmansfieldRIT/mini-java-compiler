//
//  Equality.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef Equality_hpp
#define Equality_hpp

#include <stdio.h>
#include "Exp.hpp"

class Visitor;

class Equality : public Exp
{
    
public:
    Exp* lhs;
    Exp* rhs;
    Equality(Exp* l, Exp* r);
    void accept(Visitor& v);
    
};

#endif /* Equality_hpp */
