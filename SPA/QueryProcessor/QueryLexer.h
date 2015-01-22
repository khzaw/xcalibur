#pragma once
#include <iostream>
#include "..\Frontend\Lexer.h"
#include "..\Frontend\Lexeme.h"

using namespace std;

class QueryLexer : public Lexer {
public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	Lexeme lex();
	void setNewInput(string in);
	QueryLexer();
	QueryLexer(string inputString);
	~QueryLexer();

private:
	void addChar();
	void getChar();
};
