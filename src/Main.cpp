//
//  Main.cpp
//  
//
//  Created by Brian Mansfield on 3/24/17.
//
//

#include <iostream>
#include <string>
#include <map>
#include "Parser.hpp"
#include "Lexer/Lexer.hpp"
#include "ast/TreePrinter.hpp"
#include "ast/PrettyPrinter.hpp"
#include "ast/Environment.hpp"
#include "ast/TypeChecker.hpp"
#include "ast/CodeGenerator.hpp"
#include "ast/Optimization.hpp"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    bool lex = false;
    bool ast = false;
    bool help = false;
    bool name = false;
    bool ppfl = false;
    bool type = false;
    bool cgen = false;
    bool opt = false;
    
    string helpMsg = "Options: --help, --lex, --ast, --pp, --name, --type, --cgen, --opt\n";

    string lexFlag("--lex");
    string helpFlag("--help");
    string astFlag("--ast");
    string ppFlag("--pp");
    string nameFlag("--name");
    string typeFlag("--type");
    string cgenFlag("--cgen");
    string optFlag("--opt");
    
    int fileindx = argc-1;

    // checking for flags
    if (argc <= 2){
        help = true;
    } else {
        
        for (int i = 0; i < argc; i++){
            char* arg = argv[i];
            if (arg == helpFlag){
                help = true;
            } else if (arg == lexFlag){
                lex = true;
            } else if (arg == astFlag){
                ast = true;
            } else if (arg == ppFlag){
                ppfl = true;
            } else if (arg == nameFlag){
                name = true;
            } else if (arg == typeFlag){
                type = true;
            } else if (arg == cgenFlag){
                cgen = true;
            } else if (arg == optFlag){
                opt = true;
            }
        }
    }
    
    char* filename = argv[fileindx];
    
    if (help){
        std::cout << helpMsg;
    }
    
    int index = 0;
    
    try {
        
        Lexer l;
        vector<Token> lexTokens = l.lexFile(filename);
        
        string file(filename);
        
        if (lex){
            l.printTokens(lexTokens, filename);
        }

        Parser p;
        Program* prog;
        std::cout << "Parsing tokens...\n";
        prog = p.parseProgram(lexTokens, index);
        std::cout << "Finished parse tree...\n";
        
        if (ast){
            std::cout << "Printing parse tree...\n";
            TreePrinter tp(file + ".ast");
            prog->accept(tp);
            std::cout << "Finished Printing parse tree...\n";
        }
        
        if (ppfl){
            std::cout << "Pretty Printing parse tree...\n";
            PrettyPrinter pp;
            prog->accept(pp);
            std::cout << "Finished Pretty Printing parse tree...\n";
        }
        
        std::cout << "Beginning name analysis...\n";
        Environment e;
        prog->accept(e);
        if (name){
            if (!e.error){
                std::cout << "Valid eMiniJava Program\n";
            }
        }
        std::cout << "Finished name analysis...\n";
        
        std::cout << "Beginning type checking...\n";
        TypeChecker t;
        prog->accept(t);
        if (type){
            if (!t.error){
                std::cout << "Valid eMiniJava Program\n";
            }
        }
        std::cout << "Finished type checking...\n";
        
        if (opt){
            std::cout << "Beginning Optimization (Dead Code Removal)...\n";
            Optimization o;
            prog->accept(o);
            std::cout << "Finished Optimization...\n";
        }
        
        CodeGenerator cg;
        prog->accept(cg);
        
        string command = "java -jar jasmin.jar ";
        for (int i = 0; i < cg.classes.size(); i++){
            command += cg.classes[i];
            command += ".j ";
        }
        
        system(command.c_str());
        
    } catch (const string& msg) {
        std::cout << msg;
    }
    
    return 0;
}
