//
//  True.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//


#ifndef True_hpp
#define True_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class True : public Exp
{
    
public:
    True(void);
    void accept(Visitor& v);
    
};

#endif /* True_hpp */
