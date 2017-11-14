//
//  Main.cpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#include <stdio.h>
#include "Parser.hpp"

Exp* Parser::parseExpE(vector<Token>& tokens, int& i){
    int tok = tokens[i].id;
    if(tok == Token::TRUE){
        i++;
        True* t = new True;
        Exp* r = parseExpEPrime(t, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if (tok == Token::FALSE){
        i++;
        False* f = new False;
        Exp* r = parseExpEPrime(f, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if (tok == Token::LPAREN){
        i++;
        Exp* ret = parseExpS(tokens, i);
        ret->row = tokens[i].row;
        ret->col = tokens[i].col;
        
        if (tokens[i].id == Token::RPAREN){
            i++;
            Exp* r = parseExpEPrime(ret, tokens, i);
            r->row = tokens[i].row;
            r->col = tokens[i].col;
            return r;
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Missing closing parenthesis\n";
            throw errorMsg;
        }
        
    } else if(tok == Token::INTLIT){
        IntLiteral* il = new IntLiteral( tokens[i].intval );
        i++;
        Exp* r = parseExpEPrime(il, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if(tok == Token::STRINGLIT){
        StringLiteral* sl = new StringLiteral( tokens[i].strval );
        i++;
        Exp* r = parseExpEPrime(sl, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if(tok == Token::BANG){
        i++;
        Not* n = new Not(parseExpS(tokens, i));
        n->row = tokens[i].row;
        n->col = tokens[i].col;
        Exp* r = parseExpEPrime(n, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if (tok == Token::ID){
        Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
        i++;
        Exp* r = parseExpEPrime(v, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if (tok == Token::THIS){
        i++;
        This* t = new This(tokens[i].row, tokens[i].col);
        t->row = tokens[i].row;
        t->col = tokens[i].col;
        
        Exp* r = parseExpEPrime(t, tokens, i);
        r->row = tokens[i].row;
        r->col = tokens[i].col;
        return r;
        
    } else if (tok == Token::NEW){
        i++;
        Exp* e = parseExpENew(tokens, i);
        e->row = tokens[i].row;
        e->col = tokens[i].col;
        
        New* n = new New(e);
        n->row = tokens[i].row;
        n->col = tokens[i].col;
        return n;
        
    } else {
        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
        throw errorMsg;
    }
}

Exp* Parser::parseExpENew(vector<Token>& tokens, int& i)
{
    int tok = tokens[i].id;
    if (tok == Token::INT){
        i++;
        tok = tokens[i].id;
        if (tok == Token::LBRACKET){
            i++;
            Exp* e = parseExpS(tokens, i);
            e->row = tokens[i].row;
            e->col = tokens[i].col;
            
            tok = tokens[i].id;
            if (tok == Token::RBRACKET){
                i++;
                IntArray* ia = new IntArray(e);
                ia->row = tokens[i].row;
                ia->col = tokens[i].col;
                
                return ia;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
            throw errorMsg;
        }
    } else if (tok == Token::ID){
        Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
        i++;
        tok = tokens[i].id;
        if(tok == Token::LPAREN){
            i++;
            tok = tokens[i].id;
            if (tok == Token::RPAREN){
                i++;
                return v;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
            throw errorMsg;
        }
    }  else {
        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid expression\n";
        throw errorMsg;
    }
}

Exp* Parser::parseExpEPrime(Exp* e1, vector<Token>& tokens, int& i){
    int tok = tokens[i].id;
    if (tok == Token::AND){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        And* a = new And(e1, e2);
        a->row = tokens[i].row;
        a->col = tokens[i].col;
        
        return a;
        
    } else if (tok == Token::OR){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Or* o = new Or(e1, e2);
        o->row = tokens[i].row;
        o->col = tokens[i].col;
        
        return o;
        
    } else if (tok == Token::LESSTHAN){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        LessThan* lt = new LessThan(e1, e2);
        lt->row = tokens[i].row;
        lt->col = tokens[i].col;
        
        return lt;
        
    } else if (tok == Token::PLUS){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Plus* p = new Plus(e1, e2);
        p->row = tokens[i].row;
        p->col = tokens[i].col;
        
        
        return p;
        
    } else if (tok == Token::MINUS){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Minus* m = new Minus(e1, e2);
        m->row = tokens[i].row;
        m->col = tokens[i].col;
        
        return m;
        
    } else if (tok == Token::TIMES){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Times* t = new Times(e1, e2);
        t->row = tokens[i].row;
        t->col = tokens[i].col;
        
        return t;
        
    } else if (tok == Token::DIV){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Division* d = new Division(e1, e2);
        d->row = tokens[i].row;
        d->col = tokens[i].col;
        
        return d;
        
    } else if (tok == Token::EQUALS){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        Equality* e = new Equality(e1, e2);
        e->row = tokens[i].row;
        e->col = tokens[i].col;
        
        return e;
        
    } else if (tok == Token::LBRACKET){
        i++;
        Exp* e2 = parseExpS(tokens, i);
        e2->row = tokens[i].row;
        e2->col = tokens[i].col;
        
        tok = tokens[i].id;
        
        if (tok == Token::RBRACKET){
            i++;
            ArrayAccess* arr = new ArrayAccess(e1, e2);
            arr->row = tokens[i].row;
            arr->col = tokens[i].col;
            
            return arr;
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Missing closing bracket";
            throw errorMsg;
        }
    } else if (tok == Token::DOT){
        i++;
        tok = tokens[i].id;
        if (tok == Token::LENGTH){
            Length* l = new Length(e1);
            l->row = tokens[i].row;
            l->col = tokens[i].col;
            
            i++;
            return l;
            
        } else if (tok == Token::ID){
            
            Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
            i++;
            tok = tokens[i].id;
            if (tok == Token::LPAREN){
                i++;
                tok = tokens[i].id;
                vector<Exp*> args;
                while (tok != Token::RPAREN){
                    if (tok == Token::COMMA){
                        i++;
                        tok = tokens[i].id;
                    }
                    Exp* e = parseExpS(tokens, i);
                    e->row = tokens[i].row;
                    e->col = tokens[i].col;
                    
                    tok = tokens[i].id;
                    args.push_back(e);
                } 
                i++;
                FuncCall* fc = new FuncCall(e1, v, args);
                return fc;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid function call after dot statement";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid function call after dot statement";
            throw errorMsg;
        }
    }
        
    return e1;
}

Exp* Parser::parseExpS(vector<Token>& tokens, int& i){
    Exp* e1 = parseExpE(tokens, i);
    return parseExpEPrime(e1, tokens, i);
}

Statement* Parser::parseStatementS(vector<Token>& tokens, int& i)
{
    int tok = tokens[i].id;
    if (tok == Token::PRINTLN){
        i++;
        Exp* e = parseExpS(tokens, i);
        
        tok = tokens[i].id;
        if (tok == Token::SEMICOLON){
            i++;
            Print* p = new Print(e);
            return p;
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: missing semicolon\n";
            throw errorMsg;
        }
        
    } else if (tok == Token::IF){
        
        i++;
        tok = tokens[i].id;
        if (tok == Token::LPAREN){
            i++;
            Exp* e = parseExpS(tokens, i);
            e->row = tokens[i].row;
            e->col = tokens[i].col;
            tok = tokens[i].id;
            if (tok == Token::RPAREN){
                i++;
                Statement* s1 = parseStatementS(tokens, i);
                tok = tokens[i].id;
                if (tok == Token::ELSE){
                    i++;
                    Statement* s2 = parseStatementS(tokens, i);
                    If* f = new If(e, s1, s2);
                    return f;
                } else {
                    If* f = new If(e, s1);
                    return f;
                }
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Missing closing parenthesis in If expression\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Missing opening parenthesis in If expression\n";
            throw errorMsg;
        }
    } else if (tok == Token::LBRACE){
        
        vector<Statement*> body;
        
        i++;
        tok = tokens[i].id;
        while (tok != Token::RBRACE){
            if (tok == Token::EOFILE){
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: block statement missing closing brace\n";
                throw errorMsg;
            }
            
            Statement* s = parseStatementS(tokens, i);
            if (s == NULL){
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid statement in block\n";
                throw errorMsg;
            }
            
            body.push_back( s );
            tok = tokens[i].id;
        }
        i++;
        Block* b = new Block(body);
        return b;
        
    } else if (tok == Token::WHILE){
        i++;
        tok = tokens[i].id;
        if (tok == Token::LPAREN){
            i++;
            Exp* e = parseExpS(tokens, i);
            e->row = tokens[i].row;
            e->col = tokens[i].col;
            
            tok = tokens[i].id;
            if (tok == Token::RPAREN){
                i++;
                Statement* s = parseStatementS(tokens, i);
                While* w = new While(e, s);
                return w;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: While statement missing closing parenthesis\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: While statement missing opening parenthesis\n";
            throw errorMsg;
        }
        
    } else if (tok == Token::SIDEF){
        i++;
        Exp* s = parseExpS(tokens, i);
        s->row = tokens[i].row;
        s->col = tokens[i].col;
        
        tok = tokens[i].id;
        if (tok == Token::SEMICOLON){
            i++;
            Sidef* sd = new Sidef(s);
            return sd;
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Sidef statement missing semicolon\n";
            throw errorMsg;
        }
        
    } else if (tok == Token::ID){
        Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
        
        i++;
        tok = tokens[i].id;
        
        if (tok == Token::EQSIGN){
            
            i++;
            Exp* e = parseExpS(tokens, i);
            e->row = tokens[i].row;
            e->col = tokens[i].col;
            
            tok = tokens[i].id;
            if (tok == Token::SEMICOLON){
                i++;
                Equals* eq = new Equals(v, e);
                return eq;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Equals statement missing semicolon\n";
                throw errorMsg;
            }
            
        } else if (tok == Token::LBRACKET){
            i++;
            Exp* e1 = parseExpS(tokens, i);
            e1->row = tokens[i].row;
            e1->col = tokens[i].col;
            
            tok = tokens[i].id;
            if (tok == Token::RBRACKET){
                ArrayAccess* arr = new ArrayAccess(v, e1);
                
                i++;
                tok = tokens[i].id;
                if (tok == Token::EQSIGN){
                    i++;
                    Exp* e2 = parseExpS(tokens, i);
                    e2->row = tokens[i].row;
                    e2->col = tokens[i].col;
                    
                    tok = tokens[i].id;
                    if (tok == Token::SEMICOLON){
                        i++;
                        Equals* eq = new Equals(arr, e2);
                        return eq;
                    } else {
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Array Access statement missing semicolon\n";
                        throw errorMsg;
                    }
                } else {
                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid statement\n";
                    throw errorMsg;
                }
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Array access statement missing closing bracket\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid statement\n";
            throw errorMsg;
        }
    }
    return NULL;
}

Type* Parser::parseType(vector<Token>& tokens, int& i)
{
    int tok = tokens[i].id;
    if (tok == Token::INT){
        i++;
        tok = tokens[i].id;
        if (tok == Token::LBRACKET){
            i++;
            tok = tokens[i].id;
            if (tok == Token::RBRACKET){
                i++;
                IntArrayType* iat = new IntArrayType();
                return iat;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Array Type missing closing bracket\n";
                throw errorMsg;
            }
            
        } else {
            Integer* it = new Integer();
            return it;
        }
        
    } else if (tok == Token::BOOLEAN){
        i++;
        Boolean* b = new Boolean();
        return b;
        
    } else if (tok == Token::STRING){
        i++;
        String* s = new String();
        return s;
        
    } else if (tok == Token::ID){
        if (tokens[i+1].id != Token::ID)
            return NULL;
        Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
        i++;
        return v;
        
    }
    
    return NULL;
}

VarDecl* Parser::parseVarDecl(vector<Token>& tokens, int& i)
{
    Type* t = parseType(tokens, i);
    int tok = tokens[i].id;
    if (t != NULL && tok == Token::ID){
        Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
        i++;
        tok = tokens[i].id;
        if (tok == Token::SEMICOLON){
            i++;
            VarDecl* vd = new VarDecl(t, v);
            return vd;
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Variable Declaration missing semicolon\n";
            throw errorMsg;
        }
    }
    return NULL;
}

MethDecl* Parser::parseMethodDecl(vector<Token>& tokens, int& i)
{
    
    vector<Type*> argTypes;
    vector<Var*> argVars;
    vector<VarDecl*> varDecls;
    vector<Statement*> statements;
    
    int tok = tokens[i].id;
    if (tok == Token::PUBLIC){
        i++;
        Type* methType = parseType(tokens, i);
        if (methType == NULL){
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid Type for method\n";
            throw errorMsg;
        }
        tok = tokens[i].id;
        if (tok == Token::ID){
            Var* methID = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
            
            i++;
            tok = tokens[i].id;
            if (tok == Token::LPAREN){
                
                i++;
                tok = tokens[i].id;
                
                int argcount = 0;
                while (tok != Token::RPAREN){
                    if (argcount > 0){
                        if (tok != Token::COMMA){
                            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Missing comma between method arguments\n";
                            throw errorMsg;
                        }
                        i++;
                        tok = tokens[i].id;
                    }
                    Type* argType = parseType(tokens, i);
                    if (argType == NULL){
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid Method argument type\n";
                        throw errorMsg;
                    }
                    tok = tokens[i].id;
                    if (tok == Token::ID){
                        Var* argID = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
                        argTypes.push_back(argType);
                        argVars.push_back(argID);
                        i++;
                        tok = tokens[i].id;
                    } else {
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid method argument\n";
                        throw errorMsg;
                    }
                    argcount++;
                }
                
                i++;
                tok = tokens[i].id;
                if (tok == Token::LBRACE){
                    i++;
                    tok = tokens[i].id;
                    Exp* ret = NULL;
                    
                    VarDecl* vd = parseVarDecl(tokens, i);
                    while (vd != NULL){
                        varDecls.push_back(vd);
                        vd = parseVarDecl(tokens, i);
                    }
                    
                    Statement* st = parseStatementS(tokens, i);
                    while (st != NULL){
                        statements.push_back(st);
                        st = parseStatementS(tokens, i);
                    }
                    
                    tok = tokens[i].id;
                    if (tok == Token::RETURN){
                        i++;
                        ret = parseExpS(tokens, i);
                        ret->row = tokens[i].row;
                        ret->col = tokens[i].col;
                        
                        tok = tokens[i].id;
                        if(tok == Token::SEMICOLON){
                            i++;
                            tok = tokens[i].id;
                            if (tok == Token::RBRACE){
                                i++;
                                MethDecl* md = new MethDecl(methType, methID, argTypes, argVars, varDecls, statements,  ret);
                                return md;
                            } else {
                                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Unreachable statements after return statement\n";
                                throw errorMsg;
                            }
                        } else {
                            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Return statement missing semicolon\n";
                            throw errorMsg;
                        }
                    } else {
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: method missing return statement\n";
                        throw errorMsg;
                    }
                    
                } else {
                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Sidef statement missing semicolon\n";
                    throw errorMsg;
                }
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Method missing opening parenthesis\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Method missing valid identifier\n";
            throw errorMsg;
        }
    }
    
    return NULL;
}

ClassDecl* Parser::parseClassDecl(vector<Token>& tokens, int& i)
{
    int tok = tokens[i].id;
    if (tok == Token::CLASS){
        i++;
        tok = tokens[i].id;
        if (tok == Token::ID){
            Var* v1 = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
            i++;
            tok = tokens[i].id;
            Var* v2 = NULL;
            if (tok == Token::EXTENDS){
                i++;
                tok = tokens[i].id;
                if (tok == Token::ID){
                    v2 = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
                    i++;
                    tok = tokens[i].id;
                } else {
                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid Extends statement in class definition\n";
                    throw errorMsg;
                }
            }
            
            vector<VarDecl*> varDecls;
            vector<MethDecl*> methDecls;
            if (tok == Token::LBRACE){
                i++;
                tok = tokens[i].id;
                while (tok != Token::RBRACE){
                    VarDecl* vd = parseVarDecl(tokens, i);
                    MethDecl* md = parseMethodDecl(tokens, i);
                    
                    if(vd != NULL)
                        varDecls.push_back(vd);
                    if(md != NULL)
                        methDecls.push_back(md);
                    if (vd == NULL && md == NULL){
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: statements outside method declaration\n";
                        throw errorMsg;
                    }
                    
                    
                    tok = tokens[i].id;
                }
                i++;
                ClassDecl* cd = new ClassDecl(v1, v2, varDecls, methDecls);
                return cd;
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: class definition missing opening brace\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid class identifier\n";
            throw errorMsg;
        }
    } else {
        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid class definition\n";
        throw errorMsg;
    }
}

MainClass* Parser::parseMainClass(vector<Token>& tokens, int& i)
{
    int tok = tokens[i].id;
    if (tok == Token::CLASS){
        i++;
        tok = tokens[i].id;
        if (tok == Token::ID){
            Var* v = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
            i++;
            tok = tokens[i].id;
            if (tok == Token::LBRACE){
                i++;
                tok = tokens[i].id;
                if (tok == Token::PUBLIC){
                    i++;
                    tok = tokens[i].id;
                    if (tok == Token::STATIC){
                        i++;
                        tok = tokens[i].id;
                        if (tok == Token::VOID){
                            i++;
                            tok = tokens[i].id;
                            if (tok == Token::MAIN){
                                i++;
                                tok = tokens[i].id;
                                if (tok == Token::LPAREN){
                                    i++;
                                    tok = tokens[i].id;
                                    if (tok == Token::STRING){
                                        i++;
                                        tok = tokens[i].id;
                                        if (tok == Token::LBRACKET){
                                            i++;
                                            tok = tokens[i].id;
                                            if (tok == Token::RBRACKET){
                                                i++;
                                                tok = tokens[i].id;
                                                if (tok == Token::ID){
                                                    Var* v2 = new Var(tokens[i].strval, tokens[i].row, tokens[i].col);
                                                    i++;
                                                    tok = tokens[i].id;
                                                    if (tok == Token::RPAREN){
                                                        i++;
                                                        tok = tokens[i].id;
                                                        if (tok == Token::LBRACE){
                                                            i++;
                                                            tok = tokens[i].id;
                                                            vector<Statement*> statements;
                                                            
                                                            while (tok != Token::RBRACE){
                                                                Statement* s = parseStatementS(tokens, i);
                                                                if (s == NULL){
                                                                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: bad statement in main method\n";
                                                                    throw errorMsg;
                                                                }
                                                                statements.push_back(s);
                                                                tok = tokens[i].id;
                                                            }
                                                            
                                                            i++;
                                                            tok = tokens[i].id;
                                                            if (tok == Token::RBRACE){
                                                                i++;
                                                                MainClass* mc = new MainClass(v, v2, statements);
                                                                return mc;
                                                                
                                                            } else {
                                                                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Main class definition missing closing brace\n";
                                                                throw errorMsg;
                                                            }
                                                        } else {
                                                            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                                            throw errorMsg;
                                                        }
                                                    } else {
                                                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                                        throw errorMsg;
                                                    }
                                                } else {
                                                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                                    throw errorMsg;
                                                }
                                            } else {
                                                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                                throw errorMsg;
                                            }
                                        } else {
                                            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                            throw errorMsg;
                                        }
                                    } else {
                                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                        throw errorMsg;
                                    }
                                } else {
                                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                    throw errorMsg;
                                }
                            } else {
                                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                                throw errorMsg;
                            }
                        } else {
                            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                            throw errorMsg;
                        }
                    } else {
                        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                        throw errorMsg;
                    }
                } else {
                    errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                    throw errorMsg;
                }
            } else {
                errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
                throw errorMsg;
            }
        } else {
            errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: invalid main class definition\n";
            throw errorMsg;
        }
    } else {
        errorMsg =  to_string(tokens[i].row) + ":" + to_string(tokens[i].col) + " Error: Invalid main class definition\n";
        throw errorMsg;
    }
}

Program* Parser::parseProgram(vector<Token>& tokens, int& i){
    
    vector<ClassDecl*> classes;
    
    MainClass* mc = parseMainClass(tokens, i);
    
    int tok = tokens[i].id;
    
    while (tok != Token::EOFILE && tok != Token::BAD){
        ClassDecl* cd = parseClassDecl(tokens, i);
        
        if (cd != NULL){
            classes.push_back(cd);
        }
        tok = tokens[i].id;
    }
    
    Program* prog = new Program(mc, classes);
    return prog;
}
