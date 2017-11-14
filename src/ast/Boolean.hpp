//
//  Boolean.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Boolean_hpp
#define Boolean_hpp

class Visitor;

#include <stdio.h>
#include "Type.hpp"

class Boolean : public Type
{
    
public:
    Boolean(void);
    void accept(Visitor& v);
    
};

#endif /* Boolean_hpp */
