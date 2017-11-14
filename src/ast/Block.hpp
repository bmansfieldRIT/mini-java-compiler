//
//  Block.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include <vector>
#include "Statement.hpp"

class Visitor;

using namespace std;

class Block : public Statement
{
    
public:
    Block(vector<Statement*> b);
    vector<Statement*> body;
    void accept(Visitor& v);
    
};

#endif /* Block_hpp */
