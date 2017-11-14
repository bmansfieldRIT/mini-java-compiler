//
//  Tree.hpp
//  
//
//  Created by Brian Mansfield on 4/3/17.
//
//

#ifndef Tree_hpp
#define Tree_hpp

class Visitor;

#include <stdio.h>

class Tree
{
    
public:
    virtual void accept(Visitor& v) = 0;
    
};

#endif /* Tree_hpp */
