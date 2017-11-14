//
//  Integer.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Integer_hpp
#define Integer_hpp

class Visitor;

#include <stdio.h>
#include "Type.hpp"

class Integer : public Type
{
    
public:
    Integer(void);
    void accept(Visitor& v);
    
};

#endif /* Integer_hpp */
