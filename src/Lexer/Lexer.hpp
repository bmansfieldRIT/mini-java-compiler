//
//  Lexer.hpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include "Token.hpp"
#include "CharStream.hpp"

using namespace std;

class Lexer
{
    
public:
    ofstream outputFile;
    vector<Token> tokens;
    void initKeywords(map<string, int>& kw);
    void initSymbols(map<char, int>& sym);
    void printTokens(vector<Token>& tok, string filename);
    void lexNext(CharStream& cs, bool skip);
    vector<Token> lexFile(char* filename);
    Lexer(void);
    
private:
    vector<char> buffer;
    char current, lookahead;
    int index;
    
};
    
#endif /* Lexer_hpp */
