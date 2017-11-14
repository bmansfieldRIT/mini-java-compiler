//
//  Symbol.cpp
//  
//
//  Created by Brian Mansfield on 4/10/17.
//
//

#include "Symbol.hpp"

const int Symbol::STRING = 0;
const int Symbol::INT = 1;
const int Symbol::INTARRAY = 2;
const int Symbol::BOOLEAN = 3;
const int Symbol::IDENTIFIER = 4;
const int Symbol::CLASS = 5;
const int Symbol::METHOD = 6;
const int Symbol::UNDEFINED = 7;

Symbol::Symbol(int s)
:   type(s)
{}
