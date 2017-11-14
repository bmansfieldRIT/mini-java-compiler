#include "Lexer.hpp"

using namespace std;

Lexer::Lexer()
:   index(0)
{}

void Lexer::initKeywords(map<string, int>& kw)
{
    kw["eof"] = Token::EOFILE;
    kw["bad"] = Token::BAD;
    kw["class"] = Token::CLASS;
    kw["public"] = Token::PUBLIC;
    kw["static"] = Token::STATIC;
    kw["void"] = Token::VOID;
    kw["String"] = Token::STRING;
    kw["extends"] = Token::EXTENDS;
    kw["int"] = Token::INT;
    kw["boolean"] = Token::BOOLEAN;
    kw["while"] = Token::WHILE;
    kw["if"] = Token::IF;
    kw["else"] = Token::ELSE;
    kw["main"] = Token::MAIN;
    kw["return"] = Token::RETURN;
    kw["length"] = Token::LENGTH;
    kw["true"] = Token::TRUE;
    kw["false"] = Token::FALSE;
    kw["this"] = Token::THIS;
    kw["new"] = Token::NEW;
    kw["System.out.println"] = Token::PRINTLN;
    kw["sidef"] = Token::SIDEF;
}

void Lexer::initSymbols(map<char, int>& sym)
{
    sym[':'] = Token::COLON;
    sym[';'] = Token::SEMICOLON;
    sym['.'] = Token::DOT;
    sym[','] = Token::COMMA;
    sym['('] = Token::LPAREN;
    sym[')'] = Token::RPAREN;
    sym['['] = Token::LBRACKET;
    sym[']'] = Token::RBRACKET;
    sym['{'] = Token::LBRACE;
    sym['}'] = Token::RBRACE;
    sym['<'] = Token::LESSTHAN;
    sym['+'] = Token::PLUS;
    sym['-'] = Token::MINUS;
    sym['*'] = Token::TIMES;
    sym['!'] = Token::BANG;
}

void Lexer::printTokens(vector<Token>& tok, string filename)
{
    //std::cout << "Outputting tokens to .Lexed file...\n";
    
    string f_filename = filename + ".lexed";
    outputFile.open(f_filename);
    
    for (int i = 0; i < tok.size(); i++){
        outputFile << tok[i].row << ":" << tok[i].col;
        switch(tok[i].id){
            case 0:
                outputFile << " EOF()\n";
                break;
            case 1:
                outputFile << " BAD()\n";
                break;
            case 2:
                outputFile << " COLON()\n";
                break;
            case 3:
                outputFile << " SEMICOLON()\n";
                break;
            case 4:
                outputFile << " DOT()\n";
                break;
            case 5:
                outputFile << " COMMA()\n";
                break;
            case 6:
                outputFile << " EQSIGN()\n";
                break;
            case 7:
                outputFile << " EQUALS()\n";
                break;
            case 8:
                outputFile << " LPAREN()\n";
                break;
            case 9:
                outputFile << " RPAREN()\n";
                break;
            case 10:
                outputFile << " LBRACKET()\n";
                break;
            case 11:
                outputFile << " RBRACKET()\n";
                break;
                
            case 12:
                outputFile << " LBRACE()\n";
                break;
            case 13:
                outputFile << " RBRACE()\n";
                break;
            case 14:
                outputFile << " AND()\n";
                break;
            case 15:
                outputFile << " OR()\n";
                break;
                
            case 16:
                outputFile << " LESSTHAN()\n";
                break;
            case 17:
                outputFile << " PLUS()\n";
                break;
            case 18:
                outputFile << " MINUS()\n";
                break;
            case 19:
                outputFile << " TIMES()\n";
                break;
                
            case 20:
                outputFile << " DIV()\n";
                break;
            case 21:
                outputFile << " CLASS()\n";
                break;
            case 22:
                outputFile << " PUBLIC()\n";
                break;
            case 23:
                outputFile << " STATIC()\n";
                break;
                
            case 24:
                outputFile << " VOID()\n";
                break;
            case 25:
                outputFile << " STRING()\n";
                break;
            case 26:
                outputFile << " EXTENDS()\n";
                break;
            case 27:
                outputFile << " INT()\n";
                break;
                
            case 28:
                outputFile << " BOOLEAN()\n";
                break;
            case 29:
                outputFile << " WHILE()\n";
                break;
            case 30:
                outputFile << " IF()\n";
                break;
            case 31:
                outputFile << " ELSE()\n";
                break;
                
            case 32:
                outputFile << " MAIN()\n";
                break;
            case 34:
                outputFile << " RETURN()\n";
                break;
            case 33:
                outputFile << " LENGTH()\n";
                break;
            case 35:
                outputFile << " TRUE()\n";
                break;
                
            case 36:
                outputFile << " FALSE()\n";
                break;
            case 37:
                outputFile << " THIS()\n";
                break;
            case 38:
                outputFile << " NEW()\n";
                break;
            case 39:
                outputFile << " PRINTLN()\n";
                break;
                
            case 40:
                outputFile << " SIDEF()\n";
                break;
            case 41:
                outputFile << " ID(" << tok[i].strval << ")\n";
                break;
            case 42:
                outputFile << " STRINGLIT(" << tok[i].strval << ")\n";
                break;
            case 43:
                outputFile << " INTLIT(" << tok[i].intval << ")\n";
                break;
                
            case 44:
                outputFile << " BANG()\n";
                break;
        }
    }
    //std::cout << "Finished outputting lex tokens...\n";
    outputFile.close();
}

// bool skip = don't add current to the buffer
void Lexer::lexNext(CharStream& cs, bool skip = false)
{
    cs.next();
    index++;
    
    current = cs.getCurrent();
    lookahead = cs.lookAhead();
    
    if (!skip)
        buffer.push_back(current);
    
}

vector<Token> Lexer::lexFile(char* filename)
{
    
    map<string, int> keywords;
    map<char, int> symbols;
    vector<Token> tokens;
    string temp;
    int fIndx;
    
    initKeywords(keywords);
    initSymbols(symbols);
    
    //std::cout << "Creating character stream...\n";
    CharStream cs(filename);
    
    //std::cout << "Tokenizing character stream...\n";
    while (cs.next()){
        
        buffer.clear();
        current = cs.getCurrent();
        lookahead = cs.lookAhead();
        
        fIndx = index;
        
        if (isalpha(current)){
            buffer.push_back(current);
            
            while (isalpha(lookahead) || isdigit(lookahead) || lookahead == '_'){
                lexNext(cs);
            }
            
            temp = string(buffer.begin(), buffer.end());
            
            // determine if we have a println statement
            if (temp  == "System"){
                if (lookahead == '.'){
                    lexNext(cs);
                    while (isalpha(lookahead)){
                        lexNext(cs);
                    }
                    
                    temp = string(buffer.begin(), buffer.end());
                    
                    if (temp == "System.out"){
                        if (lookahead == '.'){
                            lexNext(cs);
                            while (isalpha(lookahead) || isdigit(lookahead)){
                                lexNext(cs);
                            }
                            temp = string(buffer.begin(), buffer.end());
                            if (temp == "System.out.println"){
                                tokens.push_back(Token(Token::PRINTLN, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                            }
                        } else
                            tokens.push_back(Token(Token::ID, temp, 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                    } else
                        tokens.push_back(Token(Token::ID, temp, 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                } else
                    tokens.push_back(Token(Token::ID, temp, 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
            } else {
                
                auto search = keywords.find(temp);
                
                // if token is keyword, add as keyword
                if (search != keywords.end()){
                    tokens.push_back(Token(search->second, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                } else {
                    // token is an indentifier
                    tokens.push_back(Token(Token::ID, temp, 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                }
            }
            
        } else if (isdigit(current)){ // check numeric symbols
            
            buffer.push_back(current);
            lookahead = cs.lookAhead();
            while (isdigit(lookahead)){
                lexNext(cs);
            }
            
            temp = string(buffer.begin(), buffer.end());
            tokens.push_back(Token(Token::INTLIT, "", stoi(temp), cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
            
        } else if (current == '"'){ // string literal 
            //string errorMsg = "Error: Invalid string literal\n";
            //throw errorMsg;
            
            lexNext(cs);
            
            while (current != '"'){
                if (lookahead == '"'){
                    lexNext(cs, true);
                } else {
                    lexNext(cs);
                }
            }
             
            temp = string(buffer.begin(), buffer.end());
             
            // pushing this token seems to cause a runtime error
            tokens.push_back(Token(Token::STRINGLIT, temp, 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
            
        } else if (!isspace(current) && current != '\n') {
            
            // search the one character symbol table for a quick tokenization
            // if no match is found, we must lookahead to match the remaining symbols
            auto search = symbols.find(current);
            if (search != symbols.end()){ // if search found a match
                tokens.push_back(Token(search->second, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
            } else {
                
                switch (current){
                    case '&':
                        if (lookahead == '&'){
                            tokens.push_back(Token(Token::AND, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                            cs.next();
                        }
                        break;
                    case '|':
                        if (lookahead == '|'){
                            tokens.push_back(Token(Token::OR, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                            cs.next();
                        }
                        break;
                    case '=':
                        if (lookahead == '='){
                            tokens.push_back(Token(Token::EQUALS, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                            lexNext(cs);
                        } else {
                            tokens.push_back(Token(Token::EQSIGN, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                        }
                        break;
                    case '/':
                        if (lookahead == '/'){
                            lexNext(cs, true);
                            while (lookahead != '\n'){
                                lexNext(cs, true);
                            }
                        } else if (lookahead == '*'){
                            lexNext(cs, true);
                            bool eoc = false; // end of comment block flag
                            while (!eoc){
                                if (lookahead == '*'){
                                    lexNext(cs, true);
                                    if (lookahead == '/'){
                                        eoc = true;
                                        lexNext(cs, true);
                                    }
                                } else {
                                    lexNext(cs, true);
                                }
                            }
                        } else {
                            tokens.push_back(Token(Token::DIV, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                        }
                        break;
                    default:
                        tokens.push_back(Token(Token::BAD, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
                        break;
                }
            }
        }
        index++;
    }
    tokens.push_back(Token(Token::EOFILE, "", 0, cs.getBufferRow(fIndx), cs.getBufferCol(fIndx)));
    
    //std::cout << "Finished tokenizing character stream...\n";
    
    return tokens;
}
