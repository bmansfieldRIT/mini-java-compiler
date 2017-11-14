//
//  Sidef.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Sidef_hpp
#define Sidef_hpp

class Visitor;

#include <stdio.h>
#include "Statement.hpp"
#include "Exp.hpp"

class Sidef : public Statement
{
    
public:
    Exp* expr;
    Sidef(Exp* e);
    void accept(Visitor& v);
    
};

#endif /* Sidef_hpp */
