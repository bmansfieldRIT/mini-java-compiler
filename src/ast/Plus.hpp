//
//  Plus.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Plus_hpp
#define Plus_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Plus : public Exp
{
    
public:
    Exp* lhs;
    Exp* rhs;
    Plus(Exp* l, Exp* r);
    void accept(Visitor& v);
};

#endif /* Plus_hpp */
