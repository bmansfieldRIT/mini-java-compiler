//
//  Program.cpp
//  
//
//  Created by Brian Mansfield on 4/7/17.
//
//

#include "Program.hpp"
#include "Visitor.hpp"

Program::Program(MainClass* m, vector<ClassDecl*> c)
:   main(m), classes(c)
{}

void Program::accept(Visitor& v){
    v.visit(this);
}
