//
//  MainClass.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef MainClass_hpp
#define MainClass_hpp

class Visitor;

#include <stdio.h>
#include <vector>
#include "Var.hpp"
#include "Statement.hpp"

class MainClass
{
    
public:
    Var* id;
    Var* args;
    vector<Statement*> statements;
    MainClass(Var* i, Var* a, vector<Statement*> s);
    void accept(Visitor& v);
};

#endif /* MainClass_hpp */
