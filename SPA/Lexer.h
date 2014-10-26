#include <iostream>
#include <string>
#include "Token.h"


using namespace std;

enum token_type {
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
	SEMICOLON
};

class Lexer {

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	int lex();
	void setNewInput(string in);
	Lexer(string inputString);
	~Lexer();

private:
	void addChar();
	void getChar();
};