//
//  Program.hpp
//  
//
//  Created by Brian Mansfield on 4/7/17.
//
//

#ifndef Program_hpp
#define Program_hpp

#include <stdio.h>

class Visitor;

#include <vector>
#include "MainClass.hpp"
#include "ClassDecl.hpp"

class Program
{
    
public:
    MainClass* main;
    vector<ClassDecl*> classes;
    Program(MainClass* m, vector<ClassDecl*> c);
    void accept(Visitor& v);
};

#endif /* Program_hpp */
