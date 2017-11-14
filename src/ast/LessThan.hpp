//
//  LessThan.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef LessThan_hpp
#define LessThan_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class LessThan : public Exp
{
    
public:
    Exp* lhs;
    Exp* rhs;
    LessThan(Exp* l, Exp* r);
    void accept(Visitor& v);
    
};

#endif /* LessThan_hpp */
