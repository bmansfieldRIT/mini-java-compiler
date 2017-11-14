SOURCE = \
	Main.cpp \
	Lexer/Lexer.cpp \
	Lexer/Lexer.hpp \
	Lexer/Token.cpp \
	Lexer/Token.hpp \
 	Lexer/CharStream.cpp \
	Lexer/CharStream.hpp \
	\
	ast/TreePrinter.cpp \
	ast/TreePrinter.hpp \
	ast/Visitor.hpp \
	ast/Tree.hpp \
	ast/Exp.hpp \
	ast/Type.hpp \
	\
	ast/True.cpp \
	ast/True.hpp \
	ast/False.cpp \
	ast/False.hpp \
	ast/This.cpp \
	ast/This.hpp \
	ast/Not.cpp \
	ast/Not.hpp \
	ast/IntLiteral.cpp \
	ast/IntLiteral.hpp \
	ast/StringLiteral.cpp \
	ast/StringLiteral.hpp \
	ast/Var.cpp \
	ast/Var.hpp \
	ast/New.cpp \
	ast/New.hpp \
	ast/And.cpp \
	ast/And.hpp \
	ast/Or.cpp \
	ast/Or.hpp \
	ast/LessThan.cpp \
	ast/LessThan.hpp \
	ast/Plus.cpp \
	ast/Plus.hpp \
	ast/Minus.cpp \
	ast/Minus.hpp \
	ast/Times.cpp \
	ast/Times.hpp \
	ast/Division.cpp \
	ast/Division.hpp \
	ast/Equality.cpp \
	ast/Equality.hpp \
	\
	ast/Print.cpp \
	ast/Print.hpp \
	ast/If.cpp \
	ast/If.hpp \
	ast/Block.cpp \
	ast/Block.hpp \
	ast/While.cpp \
	ast/While.hpp \
	ast/Sidef.cpp \
	ast/Sidef.hpp \
	ast/Equals.cpp \
	ast/Equals.hpp \
	ast/ArrayAccess.cpp \
	ast/ArrayAccess.hpp \
	ast/Length.cpp \
	ast/Length.hpp \
	ast/FuncCall.cpp \
	ast/FuncCall.hpp \
	ast/IntArray.cpp \
	ast/IntArray.hpp \
	\
	ast/Boolean.cpp \
	ast/Boolean.hpp \
	ast/IntArrayType.cpp \
	ast/IntArrayType.hpp \
	ast/Integer.cpp \
	ast/Integer.hpp \
	ast/String.cpp \
	ast/String.hpp \
	\
	ast/VarDecl.hpp \
	ast/VarDecl.cpp \
	ast/MethDecl.hpp \
	ast/MethDecl.cpp \
	ast/ClassDecl.hpp \
	ast/ClassDecl.cpp \
	ast/MainClass.hpp \
	ast/MainClass.cpp \
	ast/Program.hpp \
	ast/Program.cpp \
	\
	Parser.hpp \
	Parser.cpp \
	\
	ast/Environment.hpp \
	ast/Environment.cpp \
	ast/Symbol.hpp \
	ast/Symbol.cpp \
	ast/PrettyPrinter.hpp \
	ast/PrettyPrinter.cpp \
	ast/TypeChecker.hpp \
	ast/TypeChecker.cpp \
	\
	ast/CodeGenerator.hpp \
	ast/CodeGenerator.cpp \
	\
	ast/Optimization.hpp \
	ast/Optimization.cpp \

all: emjc

emjc: $(SOURCE)
	g++ -std=c++14 -o emjc $(SOURCE)
