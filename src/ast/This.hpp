//
//  This.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef This_hpp
#define This_hpp

class Visitor;

#include <stdio.h>
#include <string>
#include "Exp.hpp"

using namespace std;

class This : public Exp
{
public:
    int row, col;
    This(int r, int c);
    void accept(Visitor& v);
};

#endif /* This_hpp */
