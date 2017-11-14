//
//  False.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef False_hpp
#define False_hpp

class Visitor;

#include <string>
#include <stdio.h>
#include "Exp.hpp"

using namespace std;

class False : public Exp
{
    
public:
    False(void);
    void accept(Visitor& v);
    
};

#endif /* False_hpp */
