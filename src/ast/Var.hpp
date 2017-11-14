//
//  Var.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef Var_hpp
#define Var_hpp

class Visitor;

#include <stdio.h>
#include <string>
#include "Exp.hpp"
#include "Type.hpp"
#include "Symbol.hpp"

using namespace std;

class Var : public Type, public Exp
{
    
public:
    string varID;
    int row, col;
    Symbol* sym; // the definition of this occurence (using static scoping)
    Var(string id, int r, int c);
    void accept(Visitor& v);
};

#endif /* Var_hpp */
