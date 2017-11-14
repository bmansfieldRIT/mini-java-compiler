//
//  FuncCall.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef FuncCall_hpp
#define FuncCall_hpp

class Visitor;

#include <stdio.h>
#include <vector>
#include "Exp.hpp"
#include "Var.hpp"

using namespace std;

class FuncCall : public Exp
{
    
public:
    Exp* expr;
    Var* id;
    Symbol* sym;
    vector<Exp*> expressions;
    FuncCall(Exp* e, Var* i, vector<Exp*> args);
    void accept(Visitor& v);
    
};

#endif /* FuncCall_hpp */
