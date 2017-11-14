//
//  MainClass.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "MainClass.hpp"
#include "Visitor.hpp"

MainClass::MainClass(Var* i, Var* a, vector<Statement*> s)
:   id(i), args(a), statements(s)
{}

void MainClass::accept(Visitor& v)
{
    v.visit(this);
}
