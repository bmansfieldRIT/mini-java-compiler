//
//  Parser.hpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#ifndef Parser_h
#define Parser_h

#include <vector>
#include <string>
#include <fstream>

#include "Lexer/Token.hpp"
#include "Lexer/Lexer.hpp"

// expressions
#include "ast/IntLiteral.hpp"
#include "ast/StringLiteral.hpp"
#include "ast/True.hpp"
#include "ast/False.hpp"
#include "ast/Not.hpp"
#include "ast/This.hpp"
#include "ast/Var.hpp" // also a type
#include "ast/New.hpp"

#include "ast/And.hpp"
#include "ast/Or.hpp"
#include "ast/Plus.hpp"
#include "ast/Minus.hpp"
#include "ast/Times.hpp"
#include "ast/Division.hpp"
#include "ast/LessThan.hpp"
#include "ast/Equality.hpp"
#include "ast/FuncCall.hpp"
#include "ast/Length.hpp"
#include "ast/IntArray.hpp"

// statements
#include "ast/Print.hpp"
#include "ast/If.hpp"
#include "ast/Block.hpp"
#include "ast/While.hpp"
#include "ast/Sidef.hpp"
#include "ast/ArrayAccess.hpp"
#include "ast/Equals.hpp"

// types
#include "ast/Boolean.hpp"
#include "ast/IntArrayType.hpp"
#include "ast/Integer.hpp"
#include "ast/String.hpp"

// program declaration headers
#include "ast/VarDecl.hpp"
#include "ast/MethDecl.hpp"
#include "ast/ClassDecl.hpp"
#include "ast/MainClass.hpp"
#include "ast/Program.hpp"

class Parser 
{
    
public:
    
    ofstream outputFile;
    string errorMsg;
    
    Exp* parseExpE(vector<Token>& tokens, int& i);
    Exp* parseExpENew(vector<Token>& tokens, int& i);
    Exp* parseExpEPrime(Exp* e1, vector<Token>& tokens, int& i);
    Exp* parseExpS(vector<Token>& tokens, int& i);
    
    Statement* parseStatementS(vector<Token>& tokens, int& i);
    
    Type* parseType(vector<Token>& tokens, int& i);
    
    Program* parseProgram(vector<Token>& tokens, int& i);
    MainClass* parseMainClass(vector<Token>& tokens, int& i);
    ClassDecl* parseClassDecl(vector<Token>& tokens, int& i);
    VarDecl* parseVarDecl(vector<Token>& tokens, int& i);
    MethDecl* parseMethodDecl(vector<Token>& tokens, int& i);
    
};

#endif /* Parser_hpp */
