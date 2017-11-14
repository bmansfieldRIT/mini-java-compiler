//
//  IntArray.hpp
//  
//
//  Created by Brian Mansfield on 4/11/17.
//
//

#ifndef IntArray_hpp
#define IntArray_hpp

class Visitor;

#include <stdio.h>
#include "Exp.hpp"

class IntArray : public Exp
{
    
public:
    Exp* size;
    IntArray(Exp* e);
    void accept(Visitor& v);
    
};

#endif /* IntArray_hpp */
