//
//  Length.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Length_hpp
#define Length_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class Length : public Exp
{
    
public:
    Exp* expr;
    Length(Exp* e);
    void accept(Visitor& v);
    
};

#endif /* Length_hpp */
