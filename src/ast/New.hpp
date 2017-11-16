//
//  New.hpp
//
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#ifndef New_hpp
#define New_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class New : public Exp
{

public:
    Exp* func;
    New(Exp* f);
    void accept(Visitor& v);
};

#endif /* New_hpp */
