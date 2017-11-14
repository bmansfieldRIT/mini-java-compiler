//
//  ClassDecl.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef ClassDecl_hpp
#define ClassDecl_hpp

class Visitor;

#include <stdio.h>
#include <vector>
#include "Var.hpp"
#include "VarDecl.hpp"
#include "MethDecl.hpp"

using namespace std;

class ClassDecl
{
public:
    Var* id;
    Var* extID;
    vector<VarDecl*> vardecls;
    vector<MethDecl*> methdecls;
    
    ClassDecl(Var* i, Var* e, vector<VarDecl*> vds, vector<MethDecl*> mds);
    void accept(Visitor& v);
};

#endif /* ClassDecl_hpp */
