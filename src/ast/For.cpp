//
//  For.cpp
//
//
//  Created by Brian Mansfield on 3/22/17.
//
//

#include "For.hpp"

For::For(SingleStatement i,
    Exp e,
    SingleStatement s,
    Statement b)
    :
    init(i), expr(e), step(s), body(b)
{}
