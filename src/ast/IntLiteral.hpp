//
//  IntLiteral.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef IntLiteral_hpp
#define IntLiteral_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class IntLiteral : public Exp
{
    
public:
    int value;
    IntLiteral(int v);
    void accept(Visitor& v);
    
};

#endif /* IntLiteral_hpp */
