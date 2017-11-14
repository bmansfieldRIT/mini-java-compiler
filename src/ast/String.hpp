//
//  String.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef String_hpp
#define String_hpp

class Visitor;

#include <stdio.h>
#include "Type.hpp"

class String : public Type
{
    
public:
    String(void);
    void accept(Visitor& v);
    
};

#endif /* String_hpp */
