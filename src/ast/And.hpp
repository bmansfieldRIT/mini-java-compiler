//
//  And.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef And_hpp
#define And_hpp

#include <stdio.h>
#include "Exp.hpp"

class Visitor;

class And : public Exp
{
    
public:
    Exp* lhs;
    Exp* rhs;
    And(Exp* lhs, Exp* rhs);
    void accept(Visitor& v);
    
};

#endif /* And_hpp */
