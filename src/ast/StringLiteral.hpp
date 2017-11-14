//
//  StringLiteral.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef StringLiteral_hpp
#define StringLiteral_hpp

class Visitor;

#include <stdio.h>
#include <string>
#include "Exp.hpp"

using namespace std;

class StringLiteral : public Exp
{
    
public:
    string str;
    StringLiteral(string s);
    void accept(Visitor& v);
    
};

#endif /* StringLiteral_hpp */
