//
//  For.hpp
//  
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#ifndef For_hpp
#define For_hpp

#include <stdio.h>
#include "Statement.hpp"
#include "SingleStatement.hpp"
#include "Exp.hpp"

class For : public Statement
{
public:
    For(SingleStatement i, Exp e, SingleStatement s, Statement statement);
    SingleStatement init;
    Exp expr;
    SingleStatement step;
    Statement body;
};

#endif /* For_hpp */
