//
//  IntArrayType.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef IntArrayType_hpp
#define IntArrayType_hpp

class Visitor;

#include <stdio.h>
#include "Type.hpp"

class IntArrayType : public Type
{
    
public:
    IntArrayType(void);
    void accept(Visitor& v);
    
};

#endif /* IntArrayType_hpp */
