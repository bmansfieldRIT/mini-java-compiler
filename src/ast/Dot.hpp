//
//  Dot.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Dot_hpp
#define Dot_hpp

#include <stdio.h>
#include "Exp.hpp"
#include "FuncCall.hpp"

class Dot : public Exp 
{
public:
    Exp expr;
    FuncCall func;
    Dot(Exp e, FuncCall f);
};

#endif /* Dot_hpp */
