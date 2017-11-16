//
//  Times.hpp
//
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Times_hpp
#define Times_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Times : public Exp
{

public:
    Exp* lhs;
    Exp* rhs;
    Times(Exp* l, Exp* r);
    void accept(Visitor& v);
};

#endif /* Times_hpp */
