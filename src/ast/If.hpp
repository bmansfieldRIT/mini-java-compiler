//
//  If.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef If_hpp
#define If_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"
#include "Statement.hpp"

class If : public Statement
{
    
public:
    If(Exp* e, Statement* t, Statement* z);
    If(Exp* e, Statement* t);
    Exp* expr;
    Statement* then;
    Statement* elze;
    void accept(Visitor& v);
    
};

#endif /* If_hpp */
