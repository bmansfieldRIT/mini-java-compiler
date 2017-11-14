//
//  Print.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Print_hpp
#define Print_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"
#include "Statement.hpp"

class Print : public Statement
{
    
public:
    Exp* expr;
    Print(Exp* e);
    void accept(Visitor& v);
    
};

#endif /* Print_hpp */
