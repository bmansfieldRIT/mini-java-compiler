//
//  Not.hpp
//
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#ifndef Not_hpp
#define Not_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Not : public Exp
{

public:
    Exp* expr;
    Not(Exp* e);
    void accept(Visitor& v);
};

#endif /* Not_hpp */
