#pragma once
#include <iostream>
#include <string>
#include "Lexeme.h"


using namespace std;

	enum TOKEN_TYPE {
		IDENT,
		CONSTANT,
		ERROR,
		LETTER,
		DIGIT,
		WHITESPACE,
		EOL,
		PLUS,
		TIMES,
		EQ,
		INT_LIT,
		SEMICOLON,
		OPEN_BLOCK,		// {
		CLOSE_BLOCK,	// }
	};

class Lexer {

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	Lexeme lex();
	void setNewInput(string in);
	Lexer();
	Lexer(string inputString);
	~Lexer();

private:
	void addChar();
	void getChar();
};