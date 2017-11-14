//
//  Or.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Or_hpp
#define Or_hpp

#include <stdio.h>
#include "Exp.hpp"

class Visitor;

class Or : public Exp
{
    
public:
    Exp* lhs;
    Exp* rhs;
    Or(Exp* lhs, Exp* rhs);
    void accept(Visitor& v);
    
};

#endif /* Or_hpp */
