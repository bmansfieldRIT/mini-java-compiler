//
//  VarDecl.hpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#ifndef VarDecl_hpp
#define VarDecl_hpp

class Visitor;

#include <stdio.h>
#include "Type.hpp"
#include "Var.hpp"
#include "Tree.hpp"

class VarDecl : public Tree
{
    
public:
    Type* type;
    Var* id;
    VarDecl(Type* t, Var* v);
    void accept(Visitor& v);
    
};

#endif /* VarDecl_hpp */
