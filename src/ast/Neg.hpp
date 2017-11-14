//
//  Neg.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Neg_hpp
#define Neg_hpp

#include <stdio.h>
#include "Exp.hpp"

class Neg : public Exp
{
public:
    Exp expr;
    Neg(Exp e);
};


#endif /* Neg_hpp */
