//
//  Exp.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef Exp_hpp
#define Exp_hpp

#include <stdio.h>
#include "Tree.hpp"
#include "Symbol.hpp"

using namespace std;

class Exp : public Tree {
public:
    int row, col;
    Symbol* sym; // the definition of this occurence (using static scoping)
};

#endif /* Exp_hpp */
