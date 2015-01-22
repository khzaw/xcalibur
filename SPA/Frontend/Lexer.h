#pragma once
#include <iostream>
#include <string>
#include "Lexeme.h"
/*
NAME: LETTER(LETTER|DIGIT)
INTERGER: DIGIT+

procedure: 'procedure' proc_name '{' stmtLst '}'
stmtLst: stmt+
stmt: assign|while
while: 'while' var_name '{' stmtLst '}'
assign: var_name '=' expr ';'
expr: expr '+' factor | factor
factor: var_name | const_value
var_name: NAME
proc_name: NAME
const_value: INTEGER
*/

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
		TAB_CHAR,		// \t
		HEX,
		OPEN_PARENTHESES,
		CLOSE_PARENTHESES,
		COMMA,
		APOSTROPHE,
		SIMPLE_IDENT,
		MINUS,
		UNDERSCORE,
		PROG_LINE
	};

	static string TOKEN_TYPE_STRINGS[] = {
		"IDENT",
		"CONSTANT",
		"ERROR",
		"LETTER",
		"DIGIT",
		"WHITESPACE",
		"EOL",
		"PLUS",
		"TIMES",
		"EQ",
		"INT_LIT",
		"SEMICOLON",
		"OPEN_BLOCK",
		"CLOSE_BLOCK",
		"TAB_CHAR",
		"HEX",
		"OPEN_PARENTHESES",
		"CLOSE_PARENTHESES",
		"COMMA",
		"APOSTROPHE",
		"SIMPLE_IDENT",
		"MINUS",
		"UNDERSCORE",
		"PROG_LINE"
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