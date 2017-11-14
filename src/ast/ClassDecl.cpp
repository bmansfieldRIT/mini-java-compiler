//
//  ClassDecl.cpp
//  
//
//  Created by Brian Mansfield on 3/23/17.
//
//

#include "ClassDecl.hpp"
#include "Visitor.hpp"

ClassDecl::ClassDecl(Var* i, Var* e, vector<VarDecl*> vds, vector<MethDecl*> mds)
:   id(i), extID(e), vardecls(vds), methdecls(mds)
{}

void ClassDecl::accept(Visitor& v)
{
    v.visit(this);
}
