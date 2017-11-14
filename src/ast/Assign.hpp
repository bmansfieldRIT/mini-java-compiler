//
//  Assign.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef Assign_hpp
#define Assign_hpp

#include <stdio.h>
#include <string>
#include "SingleStatement.hpp"
#include "Exp.hpp"

using namespace std;

class Assign : public SingleStatement
{
public:
    string varID;
    Exp expr;
    Assign(string varID, Exp expr);
};

#endif /* Assign_hpp */
