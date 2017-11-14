//
//  Block.cpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include <stdio.h>
#include <iostream>
#include "Block.hpp"
#include "Visitor.hpp"

Block::Block(vector<Statement*> b)
:   body(b)
{}

void Block::accept(Visitor& v)
{
    v.visit(this);
}
