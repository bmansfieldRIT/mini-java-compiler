//
//  While.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef While_hpp
#define While_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"
#include "Statement.hpp"

class While : public Statement
{
    
public:
    While(Exp* e, Statement* s);
    Exp* expr;
    Statement* state;
    void accept(Visitor& v);
};

#endif /* While_hpp */
