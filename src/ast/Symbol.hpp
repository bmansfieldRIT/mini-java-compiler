//
//  Symbol.hpp
//  
//
//  Created by Brian Mansfield on 4/10/17.
//
//

#ifndef Symbol_hpp
#define Symbol_hpp

#include <stdio.h>

class Symbol
{
public:
    static const int STRING;
    static const int INT;
    static const int INTARRAY;
    static const int BOOLEAN;
    static const int IDENTIFIER;
    static const int CLASS;
    static const int METHOD;
    static const int UNDEFINED;
    
    int type;
    Symbol(int s);
};

#endif /* Symbol_hpp */
