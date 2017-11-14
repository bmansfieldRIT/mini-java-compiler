#ifndef Token_hpp
#define Token_hpp

#include <string>

using namespace std;

class Token
{
    
public:
    
    int id;
    string strval;
    int intval;
    int row, col;
    
    static const int EOFILE;
    static const int BAD;
    static const int COLON;
    static const int SEMICOLON;
    static const int DOT;
    static const int COMMA;
    static const int EQSIGN;
    static const int EQUALS;
    static const int LPAREN;
    static const int RPAREN;
    static const int LBRACKET;
    static const int RBRACKET;
    static const int LBRACE;
    static const int RBRACE;
    static const int AND;
    static const int OR;
    static const int LESSTHAN;
    static const int PLUS;
    static const int MINUS;
    static const int TIMES;
    static const int DIV;
    static const int CLASS;
    static const int PUBLIC;
    static const int STATIC;
    static const int VOID;
    static const int STRING;
    static const int EXTENDS;
    static const int INT;
    static const int BOOLEAN;
    static const int WHILE;
    static const int IF;
    static const int ELSE;
    static const int MAIN;
    static const int RETURN;
    static const int LENGTH;
    static const int TRUE;
    static const int FALSE;
    static const int THIS;
    static const int NEW;
    static const int PRINTLN;
    static const int SIDEF;
    static const int ID;
    static const int STRINGLIT;
    static const int INTLIT;
    static const int BANG;

    Token()
    : id(0), strval(""), intval(0), row(0), col(0)
    {};
    
    Token(int identifier, string str, int i, int r, int c)
    : id(identifier), strval(str), intval(i), row(r), col(c)
    {};

};

#endif /* Token_hpp */
